// 20142468 Kyungyoung Heo
// 주의사항
// 1. blkmap.h에 정의되어 있는 상수 변수를 우선적으로 사용해야 함
// 2. blkmap.h에 정의되어 있지 않을 경우 본인이 만들어서 사용하면 됨

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include "blkmap.h"

extern FILE *devicefp;

//
// flash memory를 처음 사용할 때 필요한 초기화 작업, 예를 들면 address mapping table에 대한
// 초기화 등의 작업을 수행한다. 따라서, 첫 번째 ftl_write() 또는 ftl_read()가 호출되기 전에
// main()함수에서 반드시 먼저 호출이 되어야 한다.
//

int addressMappingTable[DATABLKS_PER_DEVICE];
int freeblock = BLOCKS_PER_DEVICE - 1;	// free block은 N-1번째로 초기화

void ftl_open(){
	//
	// address mapping table 생성 및 초기화 등을 진행
    // mapping table에서 lbn과 pbn의 수는 blkmap.h에 정의되어 있는 DATABLKS_PER_DEVICE
    // 수와 같아야 하겠지요? 나머지 free block 하나는 overwrite 시에 사용하면 됩니다.
	// pbn 초기화의 경우, 첫 번째 write가 발생하기 전을 가정하므로 예를 들면, -1로 설정을
    // 하고, 그 이후 필요할 때마다 block을 하나씩 할당을 해 주면 됩니다. 어떤 순서대로 할당하는지는
    // 각자 알아서 판단하면 되는데, free block들을 어떻게 유지 관리할 지는 스스로 생각해 보기
    // 바랍니다.
	for(int i=0; i<DATABLKS_PER_DEVICE; i++){
		addressMappingTable[i] = -1;
	}
	// BLOCK_PER_DEVICE 개의 table row 생성
	return;
}

//
// file system이 ftl_write()를 호출하면 FTL은 flash memory에서 주어진 lsn과 관련있는
// 최신의 데이터(512B)를 읽어서 sectorbuf가 가리키는 곳에 저장한다.
// 이 함수를 호출하기 전에 이미 sectorbuf가 가리키는 곳에 512B의 메모리가 할당되어 있어야 한다.
// 즉, 이 함수에서 메모리를 할당받으면 안된다.
//
void ftl_read(int lsn, char *sectorbuf){
	int lbn, offset, pbn, ppn;

	lbn = lsn / PAGES_PER_BLOCK;
	offset = lsn % PAGES_PER_BLOCK;
	pbn = addressMappingTable[lbn];

	ppn = pbn * PAGES_PER_BLOCK + offset;

	dd_read(ppn, sectorbuf);
	printf("read ppn = %d\n",ppn);
	return;
}

//
// file system이 ftl_write()를 호출하면 FTL은 flash memory에 sectorbuf가 가리키는 512B
// 데이터를 저장한다. 당연히 flash memory의 어떤 주소에 저장할 것인지는 block mapping 기법을
// 따라야한다.
//

void ftl_write(int lsn, char *sectorbuf){
	int lbn, offset, pbn, ppn, freeparity, newpbn;
	char chkbuf[PAGE_SIZE];
	lbn = lsn / PAGES_PER_BLOCK;
	offset = lsn % PAGES_PER_BLOCK;
	pbn = addressMappingTable[lbn];

	if(pbn == -1){	// address mapping table is not initialized
		// assign first empty block
		for(int i=0; i<DATABLKS_PER_DEVICE; i++){
			if(addressMappingTable[i] == -1){
				pbn = i;
				addressMappingTable[i] = i;
				break;
			}
		}
		ppn = pbn * PAGES_PER_BLOCK + offset;
		sectorbuf[SECTOR_SIZE] = 1;
		dd_write(ppn, sectorbuf);
		printf("write page first time lsn = %d, ppn = %d\n", lsn, ppn);
	}
	// address mapping table is initialized
	else{
		ftl_read(lsn, chkbuf);
		freeparity = chkbuf[SECTOR_SIZE];
		if(freeparity == -1){	// free page
			// assign to page
			ppn = pbn * PAGES_PER_BLOCK + offset;
			sectorbuf[SECTOR_SIZE] = 1;
			dd_write(ppn, sectorbuf);
			printf("write in free page lsn = %d, ppn = %d\n", lsn, ppn);
		}
		else{	// in-place update
			newpbn = freeblock * PAGES_PER_BLOCK;
			printf("pbn = %d\n",pbn);
			for(int i=0; i<PAGES_PER_BLOCK; i++){
				if(i == offset)
					continue;
				dd_read(pbn * PAGES_PER_BLOCK + i, chkbuf);
				// spare를 확인하고 write를 결정.
				dd_write(newpbn + i, chkbuf);
			}

			addressMappingTable[lbn] = freeblock;
			
			// 의문 1. freeblock에 원래 block을 복사할 때 dd_read, dd_write해야하나?
			// dd_read, dd_write하는 방향으로 구현함.
			// 새로운 page는 다시 dd_Write. 흠... 이건 좀 아닌 것 같다. 질문하고 확인해볼 것.

			dd_write(newpbn + offset, sectorbuf);

			dd_erase(pbn);
			printf("write in-place update lsn = %d, freeblock = %d, erase pbn = %d newpbn = %d\n",lsn, freeblock, pbn, newpbn);
			freeblock = pbn;
		}
	}
	return;
}

void print(){
	for(int i=0; i<DATABLKS_PER_DEVICE; i++){
		printf("%d %d\n", i, addressMappingTable[i]);
	}
}
/*
	page = sector(512) + spare(16)
	spare
	0: free page이면 -1, 아니면 1
	1: 
*/

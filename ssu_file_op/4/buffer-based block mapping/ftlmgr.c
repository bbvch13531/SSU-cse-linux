// 주의사항
// 1. blkmap.h에 정의되어 있는 상수 변수를 우선적으로 사용해야 함
// 2. blkmap.h에 정의되어 있지 않을 경우 본인이 만들어서 사용하면 됨

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include "blkmap.h"
// 필요한 경우 헤더 파일을 추가

extern FILE *devicefp;
int addressMappingTable[DATABLKS_PER_DEVICE];
int freeblock = BLOCKS_PER_DEVICE - 1;
int count = 0;
//
// flash memory를 처음 사용할 때 필요한 초기화 작업, 예를 들면 address mapping table에 대한
// 초기화 등의 작업을 수행한다. 따라서, 첫 번째 ftl_write() 또는 ftl_read()가 호출되기 전에
// main()함수에서 반드시 먼저 호출이 되어야 한다.
//
void ftl_open(){
	//
	// address mapping table 생성 및 초기화 등을 진행
    // mapping table에서 lbn과 pbn의 수는 blkmap.h에 정의되어 있는 DATABLKS_PER_DEVICE
    // 수와 같아야 하겠지요? 나머지 free block 하나는 overwrite 발생 시에 사용하면 됩니다.
	// pbn 초기화의 경우, 첫 번째 write가 발생하기 전을 가정하므로 예를 들면, -1로 설정을
    // 하고, 그 이후 필요할 때마다 block을 하나씩 할당을 해 주면 됩니다. 어떤 순서대로 할당하는지는
    // 각자 알아서 판단하면 되는데, free block들을 어떻게 유지 관리할 지는 스스로 생각해 보기
    // 바랍니다.
	for(int i=0; i<DATABLKS_PER_DEVICE; i++){
		addressMappingTable[i] = -1;
	}

	return;
}

//
// file system이 ftl_write()를 호출하면 FTL은 flash memory에서 주어진 lsn과 관련있는
// 최신의 데이터(512B)를 읽어서 sectorbuf가 가리키는 곳에 저장한다.
// 이 함수를 호출하기 전에 이미 sectorbuf가 가리키는 곳에 512B의 메모리가 할당되어 있어야 한다.
// 즉, 이 함수에서 메모리를 할당받으면 안된다.
//
// Read the lastest data from block.
// backward scanning from block.

void ftl_read(int lsn, char *sectorbuf){
	int lbn, offset, pbn, ppn;
	int is_find_in_buf = 0;
	char chkbuf[PAGE_SIZE];

	lbn = lsn / NONBUF_PAGES_PER_BLOCK;
	offset = lsn % NONBUF_PAGES_PER_BLOCK;
	
	pbn = addressMappingTable[lbn];

	// printf("ftl_read: lsn=%d, lbn=%d, offset=%d, pbn=%d\t\t",lsn, lbn, offset, pbn);
	// Search pbn in page's spare area

	// Backward scanning
	// read buffer page
	for(int i = PAGES_PER_BLOCK - 1; i >= PAGES_PER_BLOCK - BUF_PAGES_PER_BLOCK; i--){
		// block number
		// 6번 블록의 버퍼 페이지들을 모두 접근
		// 0*6, 0*6 + 1, 1*6 + 2, ... 
		// AWESOME CODE
		ppn = pbn * PAGES_PER_BLOCK + i;

		dd_read(ppn, chkbuf);
		// printf("chkbuf ppn=%d, spare lsn=%d %s\n", ppn, chkbuf[SECTOR_SIZE], chkbuf);

		if(chkbuf[SECTOR_SIZE] == lsn){
			memcpy(sectorbuf, chkbuf, SECTOR_SIZE);
			is_find_in_buf = 1;
			
			// printf("read lsn = %d, chkbuf lsn = %d find data in buffer page\n", lsn, chkbuf[SECTOR_SIZE]);
			return;	// 수정해야 하는 경우도 있을까?
		}
	}

	// read non-buffer page
	// calculate physical page number from pbn and offset
	// ppn = pbn * PAGES_PER_BLOCK + offset;
	if(is_find_in_buf == 0){
		ppn = pbn * PAGES_PER_BLOCK + offset;
		// printf("read lsn=%d, ppn=%d\n",lsn, ppn);
		dd_read(ppn, chkbuf);
		memcpy(sectorbuf, chkbuf, SECTOR_SIZE);

		// read page
	}
	// compare spare area
	// if identical
	// break; 
	
	return;
}

//
// file system이 ftl_write()를 호출하면 FTL은 flash memory에 sectorbuf가 가리키는 512B
// 데이터를 저장한다. 당연히 flash memory의 어떤 주소에 저장할 것인지는 
// buffer-based block mapping 기법을 따라야한다.
//
void ftl_write(int lsn, char *sectorbuf){
	int lbn, offset, pbn, ppn;
	int newpbn, key;
	char chkbuf[PAGE_SIZE];
	char data[PAGE_SIZE];
	int is_read[PAGES_PER_BLOCK]={0,};	// 버퍼에서 최신 데이터를 찾으면 1, 아니면 0

	lbn = lsn / NONBUF_PAGES_PER_BLOCK;
	offset = lsn % NONBUF_PAGES_PER_BLOCK;

	pbn = addressMappingTable[lbn];
	
	// // AWESOME CODE
	// ppn = pbn * PAGES_PER_BLOCK + offset;

	// VERY IMPORTANT CODE
	memset(data, 0, PAGE_SIZE);
	memcpy(data, sectorbuf, PAGE_SIZE);
	data[SECTOR_SIZE] = lsn;
	// write initial data
	if(pbn == -1){
		// assign first empty block
		for(int i=0; i<DATABLKS_PER_DEVICE; i++){
			if(addressMappingTable[i] == -1){
				pbn = i;
				addressMappingTable[i] = i;
				break;
			}
		}

		// ppn = pbn * NONBUF_PAGES_PER_BLOCK + offset; 가 아닌 이유는 buffer page 저장해야 하기 때문!
		
		// ppn = pbn * PAGES_PER_BLOCK + offset;
		// data[SECTOR_SIZE] = lbn;

		// AWESOME CODE
		ppn = pbn * PAGES_PER_BLOCK + offset;
		// printf("\n\nfirst block write \nppn = %d, pbn = %d, data = %s\t\t before write spare=%d\n",ppn, pbn, data, data[SECTOR_SIZE]);
		
		dd_write(ppn, data);
	}
	// write to block
	else{
		// write into empty page 

		ppn = pbn * PAGES_PER_BLOCK + offset;
		dd_read(ppn, chkbuf);
		if(chkbuf[SECTOR_SIZE] == -1){
			// printf("read chkbuf, ppn = %d, %s\t\t before write spare=%d\n",ppn, data, data[SECTOR_SIZE]);
			dd_write(ppn, data);
		}
		else{
			// write buf
			for(int i = PAGES_PER_BLOCK - 1; i >= PAGES_PER_BLOCK - BUF_PAGES_PER_BLOCK; i--){
				// check if enable to write in buf
				ppn = pbn * PAGES_PER_BLOCK + i;
				dd_read(ppn, chkbuf);

				// empty buf page.
				if(chkbuf[SECTOR_SIZE] == -1){
					// write into buf
					// printf("write into buf. ppn = %d %s\n",ppn, data);
					dd_write(ppn, data);
					return ;	
				}
			}

			// in-place-update
			// freeblock
			newpbn = freeblock * PAGES_PER_BLOCK;
			// printf("in-place-update freeblock=%d, pbn=%d, newpbn=%d, lbn=%d, lsn=%d, offset=%d data=%s\n", freeblock, pbn, newpbn, lbn, lsn, offset, data);
			
			/*
			for(int i=0; i<NONBUF_PAGES_PER_BLOCK; i++){
				if(i == offset) continue;



				// dd_read로 읽을 때 버퍼의 데이터를 확인해서 최신 데이터만 dd_write해줘야함.
				for(int j = PAGES_PER_BLOCK - 1; j >= PAGES_PER_BLOCK - BUF_PAGES_PER_BLOCK; j--){

					ppn = pbn * PAGES_PER_BLOCK + j;
					dd_read(ppn, chkbuf);
					printf("tmp read %d %s %d\n", pbn * PAGES_PER_BLOCK + j, chkbuf, chkbuf[SECTOR_SIZE]);
					if(chkbuf[SECTOR_SIZE] == lsn){
						// memcpy(sectorbuf, chkbuf, SECTOR_SIZE);
						
						dd_write(ppn, chkbuf);
						break;
						// return ;	// 이렇게 끝내도 되겠지?
					}
				}


				// if(chkbuf[SECTOR_SIZE] != -1)
				// 	dd_write(newpbn + i, chkbuf);
			}
			*/
			for(int i=0; i<PAGES_PER_BLOCK; i++){
				ppn = pbn * PAGES_PER_BLOCK + i;
				dd_read(ppn, chkbuf);
				key = chkbuf[SECTOR_SIZE];
				// printf("%d %s %d \n", i, chkbuf, key);
				// if(chkbuf[SECTOR_SIZE] == lsn) continue;
				// printf("%dth tmp read %d %s %d\n",i, pbn * PAGES_PER_BLOCK + i, chkbuf, chkbuf[SECTOR_SIZE]);
				dd_write(newpbn + (key % NONBUF_PAGES_PER_BLOCK), chkbuf);
				
			}
			addressMappingTable[lbn] = freeblock;
			// printf("write new block %d %s\n", newpbn + offset, data);
			dd_write(newpbn + offset, data);
			// printf("in-place update  %d => %d ppn=%d\n", lbn, addressMappingTable[lbn], newpbn+offset);

			dd_erase(pbn);
			count++;
			freeblock = pbn;
		}
	}


	return;
}
// void printcnt(){
// 	printf("count = %d",count);
// }
// void printTable(){
// 	printf("-----------TABLE----------\n");
// 	for(int i=0; i<5; i++){
// 		printf("%8d  =>%5d\n",i, addressMappingTable[i]);
// 	}
// 	printf("freeblock =>%5d\n",freeblock);
// }
/*
wjdtkdw정상적으로 저장할 수 있는 주소?
buffer page는 정상적인 페이지가 아니어서 ppn이 없다?

file system이 갖고있는 가상메모리가 있다.
lsn이 0,1,2,3...
freeblock은 빠지고 flash memory에서 buffer page를 제외한 non-buffet page

가상메모리 공간의 크기는 각각 블록에서 non-buffer page 사이즈를 더한 것과 같다.

block erase count 만 채점한다.
write 수는 포함하지 않을거야!!! 이런 부분에서는ㄴ 다를 수 있기 떄문이징.
erase 수는 항상 같을거야. 정상적으로 동작하면 erase 수는 같기 때문이얌.
30:40
*/
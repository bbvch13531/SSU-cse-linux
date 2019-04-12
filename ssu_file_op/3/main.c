// 20142468 Kyungyoung Heo
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "blkmap.h"

FILE *devicefp;

/****************  prototypes ****************/
void ftl_open();
void ftl_write(int lsn, char *sectorbuf);
void ftl_read(int lsn, char *sectorbuf);

void testFtl1();
void testFtl2();
void testFtl3();
//
// 이 함수는 file system의 역할을 수행한다고 생각하면 되고,
// file system이 flash memory로부터 512B씩 데이터를 저장하거나 데이터를 읽어 오기 위해서는
// 본인이 구현한 FTL의 ftl_write()와 ftl_read()를 호출하면 됨
//
int main(int argc, char *argv[]){
	char *blockbuf;
    char sectorbuf[PAGE_SIZE], newdata[PAGE_SIZE], readbuf[PAGE_SIZE];
	int lsn, i;

    devicefp = fopen("flashmemory", "w+b");
	if(devicefp == NULL){
		printf("file open error\n");
		exit(1);
	}
	   
    //
    // flash memory의 모든 바이트를 '0xff'로 초기화한다.
    // 
    blockbuf = (char *)malloc(BLOCK_SIZE);
	memset(blockbuf, 0xFF, BLOCK_SIZE);

	for(i = 0; i < BLOCKS_PER_DEVICE; i++){
		fwrite(blockbuf, BLOCK_SIZE, 1, devicefp);
	}

	free(blockbuf);

	ftl_open();    // ftl_read(), ftl_write() 호출하기 전에 이 함수를 반드시 호출해야 함
    for(int i=0; i<SECTOR_SIZE; i++){
        sectorbuf[i] = 'a';
		newdata[i] = 'b';
    }
	
	for(int i=0; i<12; i++){
		sectorbuf[0] = 'a'+i;
		ftl_write(i, sectorbuf);
		print();
		printf("\n");
	}
	
	ftl_write(11, newdata);
	for(int i=0; i<12; i++){
		ftl_read(i, readbuf);
		// dd_read(i,readbuf);
		printf("%d %s\n",i, readbuf);
	}
	// ftl_read(11, readbuf);
	// printf("%d %s\n",11, readbuf);
	// dd_read(0,readbuf);
	//
	// ftl_write() 및 ftl_read() 테스트를 위한 코드를 자유자재로 만드세요
	//
	
	fclose(devicefp);

	return 0;
}

void testFtl1(){

}
void testFtl2(){

}
void testFtl3(){
	
}
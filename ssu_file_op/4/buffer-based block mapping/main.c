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

//
// 이 함수는 file system의 역할을 수행한다고 생각하면 되고,
// file system이 flash memory로부터 512B씩 데이터를 저장하거나 데이터를 읽어 오기 위해서는
// 본인이 구현한 FTL의 ftl_write()와 ftl_read()를 호출하면 됨
//
int main(int argc, char *argv[])
{
	char *blockbuf;
    char sectorbuf[SECTOR_SIZE];
	int lsn, i;

    devicefp = fopen("flashmemory", "w+b");
	if(devicefp == NULL)
	{
		printf("file open error\n");
		exit(1);
	}
	   
    //
    // flash memory의 모든 바이트를 '0xff'로 초기화한다.
    // 
    blockbuf = (char *)malloc(BLOCK_SIZE);
	memset(blockbuf, 0xFF, BLOCK_SIZE);

	for(i = 0; i < BLOCKS_PER_DEVICE; i++)
	{
		fwrite(blockbuf, BLOCK_SIZE, 1, devicefp);
	}

	free(blockbuf);

	ftl_open();    // ftl_read(), ftl_write() 호출하기 전에 이 함수를 반드시 호출해야 함

	//
	// ftl_write() 및 ftl_read() 테스트를 위한 코드를 자유자재로 만드세요
	ftl_write(0,"A0");
	ftl_write(1,"A1");
	ftl_write(2,"A2");

	ftl_write(3,"A3");
	ftl_write(4,"A4");
	ftl_write(5,"B0");

	ftl_write(6,"B1");
	ftl_write(7,"B2");
	ftl_write(8,"B3");

	ftl_write(9,"B4");
	ftl_write(10,"C0");
	ftl_write(11,"C1");

	ftl_write(12,"C2");
	ftl_write(13,"C3");
	ftl_write(14,"C4");

	ftl_write(0,"0XX");
	ftl_write(1,"1XX");
	ftl_write(2,"2XX");

	ftl_write(3,"3XX");
	ftl_write(4,"4XX");
	ftl_write(5,"5XX");

	ftl_write(6,"6XX");
	ftl_write(7,"7XX");
	ftl_write(8,"8XX");

	ftl_write(9,"9XX");
	ftl_write(10,"10XX");
	ftl_write(11,"11XX");

	ftl_write(12,"12XX");
	ftl_write(13,"13XX");
	ftl_write(14,"14XX");


	printf("-------------1AOO\n");
	ftl_write(1, "AOO");
	
	printf("-------------6BUU\n");
	ftl_write(6, "BUU");
	printf("-------------11CWW\n");
	ftl_write(11, "CWW");
	printf("-------------12DDD 13YYY\n");
	ftl_write(12, "DDD");
	ftl_write(13, "YYY");
	printf("-------------\n");

	char pagebuf[PAGE_SIZE];
	for(int i=0; i<=14; i++){
		ftl_read(i, pagebuf);
		printf("i = %d, %s\n",i, pagebuf);
	}
	fclose(devicefp);

	return 0;
}

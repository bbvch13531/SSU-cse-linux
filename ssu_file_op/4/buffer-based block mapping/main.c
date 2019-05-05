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

	// ftl_write(9,"B4");
	// ftl_write(10,"C0");
	// ftl_write(11,"C1");

	// ftl_write(12,"C2");
	// ftl_write(13,"C3");
	// ftl_write(14,"C4");
	
	printTable();

	ftl_write(0,"0XX");
	ftl_write(1,"1XX");
	ftl_write(2,"2XX");
	
	printTable();
	ftl_write(0,"NEW");

	printTable();

	ftl_write(3,"3XX");
	ftl_write(4,"4XX");

	// ftl_read(3, sectorbuf);
	// printf("READ 3, %s\n",sectorbuf);
	
	// ftl_read(4, sectorbuf);
	// printf("READ 4, %s\n",sectorbuf);
	
	ftl_write(5,"5XX");

	printTable();

	// ftl_write(6,"6XX");
	// ftl_write(7,"7XX");
	// // ftl_write(8,"8XX");

	// printTable();

	// ftl_write(9,"9XX");
	// ftl_write(10,"10XX");
	// ftl_write(11,"11XX");

	// printTable();

	// ftl_write(12,"12XX");
	// ftl_write(13,"13XX");
	// ftl_write(14,"14XX");

	// printTable();

	// printf("-------------1AOO\n");
	// ftl_write(1, "AOO");
	
	// printf("-------------6BUU\n");
	// ftl_write(6, "BUU");
	// printf("-------------11CWW\n");
	// ftl_write(11, "CWW");
	// printf("-------------12DDD 13YYY\n");
	// ftl_write(12, "DDD");
	// ftl_write(13, "YYY");
	// printTable();
	printf("-------------\n");
	for(int i=0; i<=8; i++){
		ftl_read(i, sectorbuf);
		printf("i = %d, %s\n",i, sectorbuf);
	}


	fclose(devicefp);

	return 0;
}

/*
freeblock =>   31
read lsn=0, ppn=8
i = 0, 4XX
read lsn=1, ppn=9
i = 1, AOO
read lsn=2, ppn=10
i = 2, A4
read lsn=3, ppn=0
i = 3, A4
read lsn=4, ppn=1
i = 4, 4XX
i = 5, 5XX
i = 6, BUU
read lsn=7, ppn=5
i = 7, 7XX
read lsn=8, ppn=6
i = 8, 8XX


*/
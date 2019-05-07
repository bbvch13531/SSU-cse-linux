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
void printppn(void);
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
	
	// printTable();

	ftl_write(0,"000");
	
	printppn();
	ftl_write(1,"111");
	printppn();

	printf("\t\t\twrite 2 2XX\n");
	ftl_write(2,"222");
	printppn();

	// printTable();
	printf("\t\t\twrite 0 NEW\n");
	ftl_write(0,"NEW");
	printppn();

	// printTable();

	ftl_write(3,"333");
	printppn();
	ftl_write(4,"444");
	printppn();
	
	ftl_write(5,"555");
	printppn();

	// printTable();

	ftl_write(6,"666");
	printppn();
	ftl_write(7,"777");
	
	printppn();
	ftl_write(6, "NEWWW");
	printppn();
	ftl_write(7, "uuu");
	printppn();
	ftl_write(5, "ttt");
	printppn();
	ftl_write(8,"888");
	printppn();

	// printTable();

	ftl_write(9,"999");
	printppn();
	ftl_write(10,"zzz");
	printppn();
	ftl_write(8,"YEAHHHHHHHHHHH");
	printppn();
	ftl_write(11,"yyy");
	printppn();

	// printTable();

	ftl_write(12,"www");
	printppn();
	ftl_write(13,"vvv");
	printppn();
	ftl_write(14,"qqq");
	printppn();

	// printTable();
	ftl_write(1, "AAA");
	ftl_write(6, "BBB");
	ftl_write(11, "CCC");
	ftl_write(12, "DDD");
	ftl_write(13, "YYY");
	// printTable();
	printf("-------------\n");
	for(int i=0; i<=14; i++){
		ftl_read(i, sectorbuf);
		printf("i = %d, %s\n",i, sectorbuf);
	}

	fclose(devicefp);
	printcnt();
	return 0;
}
void printppn(){
	char pagebuf[PAGE_SIZE]={0,};
	printf("\n------------------------\n");
	for(int i=0; i<=20; i++){
		dd_read(i, pagebuf);
		if(i%PAGES_PER_BLOCK == 0)
			printf("\n");
		printf("i = %d, ",i);
		for(int j=0; j<3; j++)
			printf("%c",pagebuf[j]);
		printf("\n");
	}
	printf("\n");
	for(int i=124; i<=127; i++){
		dd_read(i, pagebuf);
		printf("i = %d, ",i);
		for(int j=0; j<3; j++)
			printf("%c",pagebuf[j]);
		printf("\n");
	}
	printf("\n------------------------\n");
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
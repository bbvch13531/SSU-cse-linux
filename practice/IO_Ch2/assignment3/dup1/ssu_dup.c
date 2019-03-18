#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000
#define BUFFER_SIZE 1024

int main(void){
	struct timeval begin_t, end_t;
	char buf[BUFFER_SIZE];
	char *fname = "ssu_test.txt";
	int count;
	int fd1, fd2;

    gettimeofday(&begin_t, NULL);
	if((fd1 = open(fname, O_RDONLY, 0644)) < 0){	
		fprintf(stderr, "open error for %s\n",fname);
		exit(1);
	}
	fd2 = dup(fd1);		// fd1 을 dup해서 fd2에 리턴
	count = read(fd1, buf, 12);		// fd1에서 12바이트 읽고 buf에 저장
	buf[count] = 0;
	printf("fd1's printf : %s\n", buf);
	lseek(fd1, 1, SEEK_CUR);	// fd1의 현재 포인터에서 1바이트 lseek
	count = read(fd2, buf, 12);
	buf[count] = 0;
	printf("fd2's printf : %s\n", buf);

	gettimeofday(&end_t, NULL);
	end_t.tv_sec -= begin_t.tv_sec;
	if(end_t.tv_usec < begin_t.tv_usec){
		end_t.tv_sec--;
		end_t.tv_usec += SEC_TO_MICRO;
	}
	end_t.tv_usec -= begin_t.tv_usec;
	printf("Runtime: %ld:%ld\n",end_t.tv_sec, end_t.tv_usec);
    exit(0);
}
		

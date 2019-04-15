#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000

int main(void){
	struct timeval begin_t, end_t;
	char *fname = "ssu_test.txt";
	int fd;

    gettimeofday(&begin_t, NULL);

	if((fd = creat(fname, 0666)) < 0){
		printf("creat error for %s\n",fname);
		exit(1);
	}

	printf("First printf is on the screen.\n");
	gettimeofday(&end_t, NULL);
	end_t.tv_sec -= begin_t.tv_sec;
	if(end_t.tv_usec < begin_t.tv_usec){
		end_t.tv_sec--;
		end_t.tv_usec += SEC_TO_MICRO;
	}
	end_t.tv_usec -= begin_t.tv_usec;
	printf("Runtime: %ld:%ld\n",end_t.tv_sec, end_t.tv_usec);
	
	dup2(fd, 1);	// stdout 을 fd로 duplicate
	printf("Second printf is in this file.\n");
	
    exit(0);
}

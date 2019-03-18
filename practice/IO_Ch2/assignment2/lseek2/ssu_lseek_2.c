#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000
#define CREAT_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "1234567890";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char** argv){
	struct timeval begin_t, end_t;
	char *fname = "ssu_hole.txt";
	int fd;

	gettimeofday(&begin_t, NULL);
	if((fd = creat(fname, CREAT_MODE)) < 0){
		fprintf(stderr, "Creat error for %s\n",fname);
		exit(1);
	}

	if(write(fd, buf1, 12) != 12){	// fd 를 12바이트만큼 읽고 buf1에 저장
		fprintf(stderr, "buf1 write error\n");
		exit(1);
	}
	if(lseek(fd, 15000, SEEK_SET) < 0){		// fd를 15000만큼 lseek
		fprintf(stderr, "lseek error\n");
		exit(1);
	}
	if(write(fd, buf2, 12) != 12){	// fd 를 12바이트만큼 읽고 buf2에 저장
		fprintf(stderr, "buf2 write error\n");
		exit(1);
	}
	
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

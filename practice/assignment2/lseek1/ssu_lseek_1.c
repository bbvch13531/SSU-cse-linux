#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000

int main(int argc, char** argv){
	struct timeval begin_t, end_t;

	char *fname = "ssu_test.txt";
	off_t fsize;
	int fd;
	gettimeofday(&begin_t, NULL);
	if((fd = open(fname, O_RDONLY)) < 0){
		fprintf(stderr, "Open error for %s\n",fname);
		exit(1);
	}

	if((fsize = lseek(fd, 0, SEEK_END)) < 0){	// fd의 처음부터 파일의 끝까지 lseek
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	printf("The size of <%s> is %ld bytes.\n", fname, fsize);
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

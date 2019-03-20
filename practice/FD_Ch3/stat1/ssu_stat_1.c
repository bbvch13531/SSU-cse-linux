#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000

int main(int argc, char* argv[]){

	struct timeval begin_t, end_t;
    struct stat statbuf;

    gettimeofday(&begin_t, NULL);
    if(argc != 2){
        fprintf(stderr, "Usage: %s <file>\n",argv[0]);
        exit(1);
    }

    if((stat(argv[1], &statbuf)) < 0){
        fprintf(stderr, "stat error\n");
        exit(1);
    }

    printf("%s is %lld bytes\n", argv[1], statbuf.st_size);  
    gettimeofday(&end_t, NULL);

	end_t.tv_sec -= begin_t.tv_sec;
	if(end_t.tv_usec < begin_t.tv_usec){
		end_t.tv_sec--;
		end_t.tv_usec += SEC_TO_MICRO;
	}
	end_t.tv_usec -= begin_t.tv_usec;
	printf("Runtime: %ld:%d\n",end_t.tv_sec, end_t.tv_usec);  
    exit(0);
}
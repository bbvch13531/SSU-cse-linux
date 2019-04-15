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
    int fd;
    int length;

    gettimeofday(&begin_t, NULL);

    if((fd = open(fname, O_RDONLY, 0644)) < 0){
        fprintf(stderr, "open error for %s\n", fname);
        exit(1);
    }
    if(dup2(1, 4) != 4){    // stdout을 4에 dup
        fprintf(stderr, "dup2 call failed\n");
        exit(1);
    }

    while(1){
        length = read(fd, buf, BUFFER_SIZE);

        if(length <= 0)
            break;
        write(4, buf, length);  // fd에 buf를 write
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
		

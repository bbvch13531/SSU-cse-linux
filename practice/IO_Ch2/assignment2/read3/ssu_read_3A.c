#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

int main(void){
    struct timeval begin_t, end_t;
    char c;
    int fd;

    gettimeofday(&begin_t, NULL);
    if((fd = open("ssu_test.txt", O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n","ssu_test.txt");
        exit(1);
    }

    while(1){
        if(read(fd, &c, 1) > 0){
            putchar(c);
        }
        else 
            break;
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
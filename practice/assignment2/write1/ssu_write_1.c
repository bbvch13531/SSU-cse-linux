#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    struct timeval begin_t, end_t;

    char buf[BUFFER_SIZE];
    int length;

    gettimeofday(&begin_t, NULL);
    
    length = read(0, buf, BUFFER_SIZE);
    write(1, buf, length);  // stdout에 buf를 write

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
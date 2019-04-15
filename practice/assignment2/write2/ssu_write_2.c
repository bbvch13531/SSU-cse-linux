#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000
#define S_MODE 0644
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    struct timeval begin_t, end_t;

    char buf[BUFFER_SIZE];
    int length;
    int fd1, fd2;

    gettimeofday(&begin_t, NULL);
    
    if(argc != 3){
        fprintf(stderr, "Usage : %s filein fileout\n", argv[0]);
        exit(1);
    }
    if((fd1 = open(argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n",argv[1]);
        exit(1);
    }

    if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_MODE)) < 0){
        fprintf(stderr, "open error for %s\n",argv[2]);
        exit(1);
    }
    
    while((length = read(fd1, buf, BUFFER_SIZE)) > 0){  // size만큼 fd1에서 읽어서 buf에 저장
        write(fd2, buf, length);    // buf에 length만큼 fd2에 write
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
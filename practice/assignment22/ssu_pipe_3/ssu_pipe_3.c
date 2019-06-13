#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void){
    char buf[BUFFER_SIZE];
    int pipe_fd[2];
    int pid;

    if(pipe(pipe_fd) < 0){  // 파이프 생성
        fprintf(stderr, "pipe error");
        exit(1);
    }

    if((pid = fork()) < 0){
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if(pid == 0){  //자식 프로세스
        close(pipe_fd[0]);

        while(1){
            memset(buf, 0x00, BUFFER_SIZE);
            sprintf(buf, "Hello Mother Process. My name is %d\n", getpid());
            write(pipe_fd[1], buf, strlen(buf));    // 파이프에 write
            sleep(1);
        }
    }
    else{   // 부모 프로세스
        close(pipe_fd[1]);

        while(1){
            memset(buf, 0x00, BUFFER_SIZE);
            read(pipe_fd[0], buf, BUFFER_SIZE); // 파이프에 read
            fprintf(stderr, "%s", buf);
        }
    }
    exit(0);
}
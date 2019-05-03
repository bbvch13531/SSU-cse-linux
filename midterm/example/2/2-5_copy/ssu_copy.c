#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    int rfd, wfd;
    int length = 0, offset = 0, count = 0;
    char buf[BUFFER_SIZE];
    ssize_t size;
    
    if((rfd = open(argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n",argv[1]);
        exit(1);
    }
    if((wfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0){
        fprintf(stderr, "open error for %s\n",argv[2]);
        exit(1);
    }
    
    size = read(rfd, buf, BUFFER_SIZE);
    write(wfd, buf, size);

    close(rfd);
    close(wfd);

    exit(0);
}
// argv[1] 을 읽어서 argv[2]를 만드는 프로그램.
// read 와 write를 사용하라.
/*
실행결과
buf = Linux System Programming!
Unix System Programming!
Linux Mania
Unix Mania
buf = Unix System Programming!
Linux Mania
Unix Mania
buf = Linux Mania
Unix Mania
line number = 3
*/
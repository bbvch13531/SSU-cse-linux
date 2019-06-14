#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void){
    char *filename = "ssu_test.txt";
    int fd1, fd2;
    int flag;

    if((fd1 = open("filename", O_RDWR | O_APPEND, 0644)) < 0){
        fprintf(stderr, "open error for %s\n", filename);
        exit(1);
    }

    if(fcntl(fd1, F_SETFD, FD_CLOEXEC) == -1){
        exit(1);
    }

    
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    char *fname = "ssu_test.txt";
    int fd;

    // fname을 644로 creat, fd를 리턴받아서 에러처리.
    if((fd = creat(fname, 0644)) < 0){
        fprintf(stderr, "creat error for %s\n",fname);
        exit(1);
    }
    else{
        // fd를 닫는다.
        close(fd);
        // RD,WR모드로 fname을 open
        fd = open(fname, O_RDWR);
        printf("Successed!\n<%s> is new readable and writable\n", fname);
    }
    exit(0);
}

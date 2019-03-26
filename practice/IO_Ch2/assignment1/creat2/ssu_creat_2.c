#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "calTime.h"

int main(int argc, char **argv){
    struct timeval begin_t, end_t;
    char *fname = "ssu_test.txt";
    int fd;

    gettimeofday(&begin_t, NULL);
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
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "calTime.h"

int main(int argc, char **argv){
    struct timeval begin_t, end_t;
    char *fname = "ssu_test.txt";
    int fd;
    
    gettimeofday(&begin_t, NULL);
    // fname을 666로 creat, fd를 리턴받아서 에러처리.
    if((fd = creat(fname, 0666)) < 0){
        fprintf(stderr, "creat error for %s\n",fname);
        exit(1);
    }
    else{
        printf("Success!\nFilename : %s\nDescriptor : %d\n", fname, fd);
        close(fd);
    }
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}

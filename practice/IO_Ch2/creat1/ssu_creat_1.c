#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
    char *fname = "ssu_test.txt";
    int fd;

    // fname을 666로 creat, fd를 리턴받아서 에러처리.
    if((fd = creat(fname, 0666)) < 0){
        fprintf(stderr, "creat error for %s\n",fname);
        exit(1);
    }
    else{
        printf("Success!\nFilename : %s\nDescriptor : %d\n", fname, fd);
        close(fd);
    }
    exit(0);
}
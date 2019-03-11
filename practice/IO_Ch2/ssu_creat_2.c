#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    char *fname = "ssu_test.txt";
    int fd;

    if((fd = creat(fname, 0644)) < 0){
        fprintf(stderr, "creat error for %s\n",fname);
        exit(1);
    }
    else{
        close(fd);
        fd = open(fname, O_RDWR);
        printf("Successed!\n<%s> is new readable and writable\n", fname);
    }
    exit(0);
}

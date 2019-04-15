#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "calTime.h"

int main(int argc, char **argv) {
    struct timeval begin_t, end_t;
    int fd;

    gettimeofday(&begin_t, NULL);
    if(argc != 3){
        fprintf(stderr, "usage: %s <oldname> <newname>\n", argv[0]);
        exit(1);
    }
    
    if((fd = open(argv[1], O_RDONLY)) < 0) {
        fprintf(stderr, "first open error for %s\n", argv[1]);
        exit(1);
    }
    else {
        close(fd);
    }

    if(rename(argv[1], argv[2]) < 0) {
        fprintf(stderr, "rename error\n");
        exit(1);
    }

    if((fd = open(argv[1], O_RDONLY)) < 0) {
        printf("second open error for %s\n", argv[1]);
    }
    else {
        fprintf(stderr, "It's very strange!\n");
        exit(1);
    }

    if((fd = open(argv[2], O_RDONLY)) < 0) {
        fprintf(stderr, "third open error for %s\n", argv[2]);
        exit(1);
    }

    printf("Everything is good!\n");
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "calTime.h"

int main(int argc, char **argv) {
    struct timeval begin_t, end_t;
    
    gettimeofday(&begin_t, NULL);
    if(argc != 3){
        fprintf(stderr, "usage: %s <oldname> <newname>\n", argv[0]);
        exit(1);
    }
    // link two files
    if(link(argv[1], argv[2]) < 0) {
        fprintf(stderr, "link error\n");
        exit(1);
    }
    else {
        printf("step1 passed.\n");
    }
    // remove first arg
    if(remove(argv[1]) > 0) {
        fprintf(stderr, "remove error\n");
        remove(argv[2]);
        exit(1);
    }
    else {
        printf("step2 passed\n");
    }
    printf("Success!\n");
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
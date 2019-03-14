#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "calTime.h"

int main(void){
    struct timeval begin_t, end_t;
    char *fname = "ssu_test.txt";
    int fd;
    
    gettimeofday(&begin_t, NULL);
    // fname을 ReadOnly로 open. fd가 0보다 작으면 에러
    if((fd = open(fname, O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n", fname);
        exit(1);
    }
    else
        printf("Success!\nFilename : %s\nDescriptor : %d \n", fname, fd);
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}

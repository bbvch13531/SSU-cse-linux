#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "calTime.h"

#define BUFFER_SIZE 1024

int main(void){
    struct timeval begin_t, end_t;
    char buf[BUFFER_SIZE];

    gettimeofday(&begin_t, NULL);
    while(fgets(buf, BUFFER_SIZE, stdin) != NULL){  // stdin에서 buf로 읽는다.
        if(fputs(buf, stdout) == EOF){
            fprintf(stderr, "standard output error\n");
            exit(1);
        }
    }
    if(ferror(stdin)){  // stdin을 error로 설정
        fprintf(stderr, "standard input error\n");
        exit(1);
    }
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "calTime.h"

int main(int argc, char ** argv){
    struct timeval begin_t, end_t;
    pid_t pid;
    char character, first, last;
    long i;

    gettimeofday(&begin_t, NULL);
    
    if((pid = fork()) > 0){ // fork 실행 부모 프로세스
        first = 'A';    
        last = 'Z';
    }
    else if(pid == 0){  // 자식 프로세스
        first = 'a';
        last = 'z';
    }
    else{ // 실패시
        fprintf(stderr, "%s\n", argv[0]);
        exit(1);
    }

    for(character = first; character <= last; character++){
        for(i=0; i<=100000; i++)
            ;
        write(1, &character, 1);    // stdout에 문자 출력
    }
    printf("\n");
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
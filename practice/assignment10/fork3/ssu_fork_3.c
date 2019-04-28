#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "calTime.h"

static void ssu_charatatime(char *str);

int main(int argc, char ** argv){
    struct timeval begin_t, end_t;
    pid_t pid;

    gettimeofday(&begin_t, NULL);
    
    if((pid = fork()) < 0){
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if(pid == 0){  // 자식 프로세스
        ssu_charatatime("output from child\n");
    }
    else{   // 부모 프로세스
        ssu_charatatime("output from parent\n");
    }
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}

static void ssu_charatatime(char *str){
    char *ptr;
    int print_char;
    
    setbuf(stdout, NULL);   // 버퍼 없음.

    for(ptr = str; (print_char = *ptr++) != 0;){
        putc(print_char, stdout);   // 출력
        usleep(10);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "calTime.h"

static void ssu_charatatime(char *str);

int main(int argc, char ** argv){
    struct timeval begin_t, end_t;
    pid_t pid;

    gettimeofday(&begin_t, NULL);
    
    if((pid = fork()) > 0){
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if(pid == 0){
        ssu_charatatime("output from child\n");
    }
    else{
        ssu_charatatime("output from parent\n");
    }
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}

static void ssu_charatatime(char *str){
    char *ptr;
    int print_char;
    
    setbuf(stdout, NULL);

    for(ptr = str; (print_char = *ptr++) != 0;){
        putc(print_char, stdout);
        usleep(10);
    }
}
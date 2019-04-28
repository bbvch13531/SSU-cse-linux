#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "calTime.h"

int main(void){
    struct timeval begin_t, end_t;
    
    gettimeofday(&begin_t, NULL);
    
    if(fork() == 0){    // fork
        execl("/bin/echo", "echo", "this is", "message one", (char *)0);
    }
    if(fork() == 0){    // fork
        execl("/bin/echo", "echo", "this is", "message two", (char *)0);
    }
    printf("parent: waiting for children\n");
    while(wait((int *)0) != -1); // 자식 프로세스가 종료될 때까지 기다림

    printf("parent: all children terminated\n");
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    
    exit(0);
}

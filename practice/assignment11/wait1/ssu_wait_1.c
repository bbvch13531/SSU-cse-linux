#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "calTime.h"

void ssu_echo_exit(int status);

int main(void){
    struct timeval begin_t, end_t;
    pid_t pid;
    int status;

    gettimeofday(&begin_t, NULL);
    
    if((pid = fork()) < 0){
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if(pid == 0){
        exit(7);
    }
    if(wait(&status) != pid){
        fprintf(stderr, "wait error\n");
        exit(1);
    }

    ssu_echo_exit(status);

    if((pid = fork()) < 0){
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if(pid == 0){
        status /= 0;
    }
    if(wait(&status) != pid){
        fprintf(stderr, "wait error\n");
        exit(1);
    }
    ssu_echo_exit(status);

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    
    exit(0);
}

void ssu_echo_exit(int status){
    if(WIFEXITED(status))
        printf("normal termination, exit status - %d\n", WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
    WCOREDUMP(status) ? " (core file generated)" : "");
#else
    "");
#endif
    else if(WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}
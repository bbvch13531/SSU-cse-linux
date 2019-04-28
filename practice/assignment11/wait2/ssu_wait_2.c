#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "calTime.h"

#define EXIT_CODE 1

int main(void){
    struct timeval begin_t, end_t;
    pid_t pid;
    int ret_val, status;

    gettimeofday(&begin_t, NULL);
    
    if((pid = fork() == 0)){    // 자식 프로세스
        printf("child: pid = %d ppid = %d exit_code = %d\n", getpid(), getppid(), EXIT_CODE);
        exit(EXIT_CODE);
    }
    printf("parent: waiting for child = %d\n", pid);
    ret_val = wait(&status);    // wait에 현재 상태 전달
    printf("parent: return value = %d, ", ret_val);
    printf(" child's status = %x", status);
    printf(" and shifted = %x\n", (status >> 8));
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    
    exit(0);
}

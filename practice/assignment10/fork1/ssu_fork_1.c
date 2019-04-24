#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "calTime.h"
char glob_str[] = "write to standard output\n";
int glob_val = 10;

int main(void){
    struct timeval begin_t, end_t;
    pid_t pid;
    int loc_val;
    
    gettimeofday(&begin_t, NULL);
    loc_val = 100;
    if(write(STDOUT_FILENO, glob_str, sizeof(glob_str) - 1) != sizeof(glob_str) - 1){   // stdout에 write
        fprintf(stderr, "write error\n");
        exit(1);
    }

    printf("before fork\n");

    if((pid = fork()) < 0){ // fork 실행
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if(pid == 0){  // 자식 프로세스
        glob_val++; // 변수를 증가시킨다
        loc_val++;
    }
    else    // 부모 프로세스
        sleep(3);
    
    printf("pid = %d, glob_val = %d, loc_val = %d\n", getpid(), glob_val, loc_val); // 프로세스에서 변수 출력 확인
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
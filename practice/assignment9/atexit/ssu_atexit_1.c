#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"

void ssu_out(void);

int main(void){
    struct timeval begin_t, end_t;
    gettimeofday(&begin_t, NULL);
    if(atexit(ssu_out)){    // atexit로 ssu_out을 설정한다.
        fprintf(stderr, "atexit error\n");
        exit(1);
    }
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
    return 0;
}

void ssu_out(void){
    printf("atexit succeeded!\n");  // 종료되기 전 실행될 함수
}

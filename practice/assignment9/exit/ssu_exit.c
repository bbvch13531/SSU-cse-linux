#include <stdio.h>
#include <unistd.h>
#include "calTime.h"
int main(void){
    struct timeval begin_t, end_t;
    
    gettimeofday(&begin_t, NULL);
    printf("Good afternoon");

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);    // 라이브러리함수 exit 호출
}
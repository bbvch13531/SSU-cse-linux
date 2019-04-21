#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"

#define BUFFER_SIZE 1024

int main(void){
    struct timeval begin_t, end_t;
    char buf[BUFFER_SIZE];
    int a,b,i;
    gettimeofday(&begin_t, NULL);

    setbuf(stdout, buf);    // buf를 stdout의 버퍼로 설정
    scanf("%d %d", &a, &b); // 숫자 두개 입력받기

    for(int i=0; buf[i] != '\n'; i++)
        putchar(buf[i]);    // 버퍼 출력
    
    putchar('\n');
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
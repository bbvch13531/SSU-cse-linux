#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "calTime.h"

#define BUFFER_SIZE 1024

int main(void){
    struct timeval begin_t, end_t;
    char buf[BUFFER_SIZE];

    gettimeofday(&begin_t, NULL);
    setbuf(stdout, buf);    // buf를 stdout의 버퍼로 설정
    printf("Hello, ");
    sleep(1);
    printf("OSLAB!!");
    sleep(1);
    printf("\n");
    sleep(1);
    
    setbuf(stdout, NULL);   // stdout의 버퍼를 NULL로 설정
    printf("HOW");
    sleep(1);
    printf(" are");
    sleep(1);
    printf(" you?");
    sleep(1);
    printf("\n");
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);

    exit(0);
}
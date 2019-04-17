#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"

#define BUFFER_SIZE 1024

int main(void){
    struct timeval begin_t, end_t;
    char buf[BUFFER_SIZE];
    int a,b,i;
    gettimeofday(&begin_t, NULL);

    setbuf(stdout, buf);
    scanf("%d %d", &a, &b);

    for(int i=0; buf[i] != '\n'; i++)
        putchar(buf[i]);
    
    putchar('\n');
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
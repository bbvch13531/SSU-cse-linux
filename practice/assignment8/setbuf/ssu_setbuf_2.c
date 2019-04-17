#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(void){
    char buf[BUFFER_SIZE];
    int a,b,i;

    setbuf(stdout, buf);
    scanf("%d %d", &a, &b);

    for(int i=0; buf[i] != '\n'; i++)
        putchar(buf[i]);
    
    putchar('\n');
    exit(0);
}
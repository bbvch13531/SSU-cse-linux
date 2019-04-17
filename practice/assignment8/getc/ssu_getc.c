#include <stdio.h>
#include <stdlib.h>

#include "calTime.h"

int main(void){
    struct timeval begin_t, end_t;

    int character;
    gettimeofday(&begin_t, NULL);

    while((character = getc(stdin)) != EOF){
        if(putc(character, stdout) == EOF){
            fprintf(stderr, "standard output error\n");
            exit(1);
        }
    }
    if(ferror(stdin)){
        fprintf(stderr, "standard input error\n");
        exit(1);
    }
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
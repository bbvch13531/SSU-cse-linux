#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"

#define BUFFER_SIZE 1024

int main(int argc, char **argv){
    struct timeval begin_t, end_t;
    char buf[BUFFER_SIZE];
    FILE *fp;

    gettimeofday(&begin_t, NULL);
    if(argc != 2){
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    if((fp = fopen(argv[1], "w+")) == NULL){
        fprintf(stderr, "fopen error for %s\n", argv[1]);
        exit(1);
    }
    fputs("Input String >>", stdout);
    gets(buf);
    fputs(buf, fp);
    rewind(fp);
    fgets(buf, sizeof(buf), fp);
    puts(buf);
    fclose(fp);
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
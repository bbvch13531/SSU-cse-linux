#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"

int main(int argc, char **argv){
    char *fname = "ssu_test.txt";
    FILE *fp;
    long fsize;
    struct timeval begin_t, end_t;
    
    gettimeofday(&begin_t, NULL);
    
    if((fp = fopen(fname, "r")) == NULL){
        fprintf(stderr, "fopen error for %s\n", fname);
        exit(1);
    }

    fseek(fp, 0, SEEK_END); // 파일의 맨 끝으로 이동
    fsize = ftell(fp);  // 파일 포인터의 정보 가져오기
    printf("The size of <%s> is %ld bytes\n", fname, fsize);
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    
    exit(0);
}
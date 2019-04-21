#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"

int main(int argc, char **argv){
    char *fname = "ssu_test.txt";
    FILE *fp;
    long position;
    int character;
    struct timeval begin_t, end_t;
    
    gettimeofday(&begin_t, NULL);

    if((fp = fopen(fname, "r")) == NULL){   // 파일 열기
        fprintf(stderr, "fopen error for %s\n", fname);
        exit(1);
    }

    printf("Input number >>");
    scanf("%ld", &position);
    fseek(fp, position - 1, SEEK_SET);  // 파일 포인터 이동
    character = getc(fp);   // 문자 읽어서 저장
    printf("%ldth character => %c\n", position, character); // 문자 출력
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    
    exit(0);
}
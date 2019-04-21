#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"

#define MAX_LINE 4096

int main(int argc, char **argv){
    struct timeval begin_t, end_t;
    char buf[MAX_LINE];
    char name[L_tmpnam];
    FILE *fp;

    gettimeofday(&begin_t, NULL);
    printf("temp file 1 : %s\n",tmpnam(NULL)); // tmpfile 생성
    tmpnam(name);   // 이름으로 tmpfile 생성
    printf("temp file 2 : %s\n",name);

    if((fp = tmpfile()) == NULL){   // 파일 읽고 fp에 파일포인터 저장
        fprintf(stderr, "tmpfile error\n");
        exit(1);
    }

    fputs("tmpfile created temporary file.\n", fp); //파일에 문자열 쓰기
    fseek(fp, 0, SEEK_SET); // 파일포인터 처음으로 되돌리기

    if(fgets(buf, sizeof(buf), fp) == NULL){    // 파일 읽고 buf에 저장
        fprintf(stderr, "fgets error\n");
        exit(1);
    }

    fputs(buf, stdout); // buf를 출력
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
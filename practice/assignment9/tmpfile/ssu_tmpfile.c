#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"

#define BUFFER_SIZE 1024

int main(int argc, char **argv){
    struct timeval begin_t, end_t;
    char buf[BUFFER_SIZE];
    char name[L_tmpnam];
    FILE *fp;

    gettimeofday(&begin_t, NULL);
    printf("Temporary filename <<%s>>\n", tmpnam(name));    // tmpfile의 이름 출력

    if((fp = tmpfile()) == NULL){   // tmpfile 생성하고 fp에 파일포인터 저장
        fprintf(stderr, "tmpfile create error!\n");
        exit(1);
    }

    fputs("create tmpfile success!!\n", fp);
    rewind(fp); // fp를 처음으로 되돌리기.
    fgets(buf, sizeof(buf), fp);    // 파일을 읽고 buf에 저장
    puts(buf);  // buf를 출력
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
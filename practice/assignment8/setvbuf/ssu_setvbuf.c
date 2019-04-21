#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "calTime.h"

#define BUFFER_SIZE 1024
void ssu_setbuf(FILE *fp, char *buf);

int main(void){
    struct timeval begin_t, end_t;
    char buf[BUFFER_SIZE];
    char *fname = "/dev/pts/1";
    FILE *fp;

    gettimeofday(&begin_t, NULL);
    if((fp = fopen(fname, "w")) == NULL){   //파일 열기
        fprintf(stderr, "fopen error for %s\n", fname);
        exit(1);
    }

    ssu_setbuf(fp, buf);    // 파일의 버퍼를 buf로 설정
    fprintf(fp, "Hello, "); 
    sleep(1);
    fprintf(fp, "UNIX!");
    sleep(1);
    fprintf(fp, "\n");
    sleep(1);
    // 출력하고 1초씩 쉬기

    ssu_setbuf(fp, NULL);       // 파일의 버퍼를 NULL로 설정
    fprintf(fp, "HOW");
    sleep(1);
    fprintf(fp, "ARE");
    sleep(1);
    fprintf(fp, "YOU?");
    sleep(1);
    fprintf(fp, "\n");
    sleep(1);
    // 출력하고 1초씩 쉬기

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}

void ssu_setbuf(FILE *fp, char *buf){
    size_t size;
    int fd;
    int mode;

    fd = fileno(fp);    // 파일의 fileno를 fd에 저장

    if(isatty(fd)){
        mode = _IOLBF;
    }
    else{
        mode = _IOFBF;
    }

    if(buf == NULL){
        mode = _IONBF;
        size = 0;
    }
    else{
        size = BUFFER_SIZE;
    }

    setvbuf(fp, buf, mode, size);   // setvbuf를 설정한다.
}

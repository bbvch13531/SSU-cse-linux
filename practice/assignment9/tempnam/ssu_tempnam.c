#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"

int main(int argc, char **argv){
    struct timeval begin_t, end_t;
    char *arg_directory = NULL;
    char *arg_prefix = NULL;

    gettimeofday(&begin_t, NULL);

    if(argc != 3){  // 인자 에러처리
        fprintf(stderr, "usage: %s <directory> <prefix>\n", argv[0]);
        exit(1);
    }

    arg_directory = argv[1][0] != ' ' ? argv[1] : NULL; //첫 글자로 판별해서 null이 아니면 저장
    arg_prefix = argv[2][0] != ' ' ? argv[2] : NULL;    //첫 글자로 판별해서 null이 아니면 저장
    printf("created : %s\n", tempnam(arg_directory, arg_prefix));   // tempnam으로 dir에 prefix를 가지는 임시파일 생성

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    
    exit(0);
}
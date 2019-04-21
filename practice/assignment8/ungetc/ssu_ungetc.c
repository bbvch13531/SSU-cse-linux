#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "calTime.h"

int main(void){
    struct timeval begin_t, end_t;
    char operator;
    int character;
    FILE *fp;
    int number = 0;

    gettimeofday(&begin_t, NULL);
    if((fp = fopen("ssu_expr.txt", "r")) == NULL){  // 파일 열기
        fprintf(stderr, "fopen eror for ssu_Expr.txt\n");
        exit(1);
    }

    while(!feof(fp)){   //파일의 EOF를 만날 때까지 반복
        while((character = fgetc(fp)) != EOF && isdigit(character)) //글자를 읽어서 숫자이면
            number = 10 * number + character - 48;  // string을 숫자로 만들기

        fprintf(stdout, " %d\n", number);   // stdout에 출력
        number = 0;

        if(character != EOF){   // EOF가 아니면
            ungetc(character, fp);  // 파일에 다시 되돌린다.
            operator = fgetc(fp);
            printf("Operator => %c\n",operator);
        }
    }
    fclose(fp);
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
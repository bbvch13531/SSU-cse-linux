#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"
#define BUFFER_MAX 256

int main(void){

    struct timeval begin_t, end_t;
    char command[BUFFER_MAX];
    char *prompt = "Prompt>>";

    gettimeofday(&begin_t, NULL);
    while(1){
        fputs(prompt, stdout);  // prompt를 출력

        if(fgets(command, sizeof(command), stdin) == NULL)  // stdin에서 입력을 받는다
            break;
        system(command);    // command 실행
    }
    fprintf(stdout, "Good bye...\n");
    fflush(stdout); // 버퍼 비우기

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
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
        fputs(prompt, stdout);

        if(fgets(command, sizeof(command), stdin) == NULL)
            break;
        system(command);
    }
    fprintf(stdout, "Good but...\n");
    fflush(stdout);

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
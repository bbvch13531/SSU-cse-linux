#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "calTime.h"
void ssu_addone(void);
extern char **environ;
char glob_var[] = "HOBBY=swimming";

int main(void){
    int i;
    struct timeval begin_t, end_t;
    gettimeofday(&begin_t, NULL);
    
    for(i=0; environ[i] != NULL; i++){
        printf("environ[%d] : %s\n", i, environ[i]);
    }

    putenv(glob_var);
    ssu_addone();
    printf("My hobby is %s\n", getenv("HOBBY"));
    printf("My lover is %s\n", getenv("LOVER"));
    strcpy(glob_var+6, "fishing");

    for(i=0; environ[i] != NULL; i++){
        printf("envion[%d] : %s\n", i, environ[i]);
    }
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}

void ssu_addone(void){
    char auto_var[10];

    strcpy(auto_var, "LOVER=js");
    putenv(auto_var);
}
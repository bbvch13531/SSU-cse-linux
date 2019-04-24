#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "calTime.h"

int main(void){
    struct timeval begin_t, end_t;
    
    gettimeofday(&begin_t, NULL);
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    
    exit(0);
}
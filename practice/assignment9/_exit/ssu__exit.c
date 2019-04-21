#include <stdio.h>
#include <unistd.h>
#include "calTime.h"
int main(void){
    struct timeval begin_t, end_t;
    
    gettimeofday(&begin_t, NULL);

    printf("Good afternoon?");
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    _exit(0);   // _exit를 직접 호출
    
}
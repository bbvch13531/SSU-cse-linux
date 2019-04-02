#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000

void ssu_runtime(struct timeval* begin_t, struct timeval* end_t){
    end_t->tv_sec -= begin_t->tv_sec;

    if(end_t->tv_usec < begin_t->tv_usec){
        end_t->tv_sec--;
        end_t->tv_usec += SEC_TO_MICRO;
    }

    end_t->tv_usec -= begin_t->tv_usec;
    printf("Runtime: %ld:%d\n",end_t->tv_sec, end_t->tv_usec);
}

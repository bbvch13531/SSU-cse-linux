#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include "calTime.h"
#define ssu_show(limit) ssu_show_limit(limit, #limit)

void ssu_show_limit(int rlim_type, char *rlim_name);

int main(void){
    struct timeval begin_t, end_t;

    gettimeofday(&begin_t, NULL);
    printf("\tresource soft limit hard limit\t\n\n");
    ssu_show(RLIMIT_CPU);       // RLIMIT_CPU 를 확인한다
    ssu_show(RLIMIT_FSIZE); // RLIMIT_FSIZE 를 확인한다
    ssu_show(RLIMIT_DATA);  // RLIMIT_DATA 를 확인한다
    ssu_show(RLIMIT_STACK); // RLIMIT_STACK 를 확인한다
    ssu_show(RLIMIT_CORE);  // RLIMIT_CORE 를 확인한다

    #ifdef RLIMIT_RSS // 만약 RLIMIT_RSS 가 정의되어 있으면 RLIMIT_RSS를 확인한다.
        ssu_show(RLIMIT_RSS);
    #endif

    #ifdef RLIMIT_MEMLOCK // 만약 RLIMIT_MEMLOCK 가 정의되어 있으면 RLIMIT_MEMLOCK를 확인한다.
        ssu_show(RLIMIT_MEMLOCK);
    #endif

    #ifdef RLIMIT_NPROC // 만약 RLIMIT_NPROC 가 정의되어 있으면 RLIMIT_NPROC를 확인한다.
        ssu_show(RLIMIT_NPROC);
    #endif

    #ifdef RLIMIT_OFILE // 만약 RLIMIT_OFILE 가 정의되어 있으면 RLIMIT_OFILE를 확인한다.
        ssu_show(RLIMIT_OFILE);
    #endif

    #ifdef RLIMIT_NOFILE // 만약 RLIMIT_NOFILE 가 정의되어 있으면 RLIMIT_NOFILE를 확인한다.
        ssu_show(RLIMIT_NOFILE);
    #endif

    #ifdef RLIMIT_VMEM // 만약 RLIMIT_VMEM 가 정의되어 있으면 RLIMIT_VMEM를 확인한다.
        ssu_show(RLIMIT_VMEM);
    #endif

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}

void ssu_show_limit(int rlim_type, char *rlim_name){
    struct rlimit rlim;
    char cur[11], max[11];

    getrlimit(rlim_type, &rlim);    // rlim_type을 가져와서 rlim에 저장

    if(rlim.rlim_cur == RLIM_INFINITY)
        strcpy(cur, "infinity");
    else
        sprintf(cur, "10ld", rlim.rlim_cur);

    if(rlim.rlim_max == RLIM_INFINITY)
        strcpy(cur, "infinity");
    else
        sprintf(max, "10ld", rlim.rlim_max);

    printf("%15s : %10s %10s\n", rlim_name, cur, max);  // 가져온 정보를 출력
}
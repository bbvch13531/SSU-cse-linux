#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *ssu_thread(void *arg);    // 쓰레드 함수

int main(void){
    pthread_t tid;

    if(pthread_create(&tid, NULL, ssu_thread, NULL) != 0){ // 쓰레드 생성
        fprintf(stderr, "pthread_create error\n");
        exit(1);
    }
    printf("%u\n", (unsigned int) tid);

    if(pthread_create(&tid, NULL, ssu_thread, NULL) != 0){ // 쓰레드 생성
        fprintf(stderr, "pthread_create error\n");
        exit(1);
    }

    printf("%u\n", (unsigned int)tid);
    sleep(1);

    exit(0);
}

void *ssu_thread(void *arg){
    pthread_t tid;

    tid = pthread_self();   // 호출한 쓰레드의 tid
    printf("->%u\n", (unsigned int)tid);
    return NULL;
}
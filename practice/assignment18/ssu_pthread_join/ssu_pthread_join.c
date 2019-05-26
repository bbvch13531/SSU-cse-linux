#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *ssu_thread(void *arg);

int main(void){
    pthread_t tid1, tid2;
    int thread1 = 1, thread2 = 2;
    int status;

    if(pthread_create(&tid1, NULL, ssu_thread, &thread1) != 0){ // 쓰레드 생성
        fprintf(stderr, "pthread_create error\n");
        exit(1);
    }

    if(pthread_create(&tid2, NULL, ssu_thread, &thread2) != 0){ // 쓰레드 생성
        fprintf(stderr, "pthread_create error\n");
        exit(1);
    }

    pthread_join(tid1, (void *)&status);    // 쓰레드가 종료할 때까지 대기
    pthread_join(tid2, (void *)&status);    // 쓰레드가 종료할 때까지 대기

    exit(0);
}

void *ssu_thread(void *arg){
    int thread_index;
    int i;

    thread_index = *((int *)arg);

    for(i=0; i<5; i++){
        printf("%d : %d\n", thread_index, i);
        sleep(1);
    }
    
    return NULL;
}
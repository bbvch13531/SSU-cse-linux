#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>

void *sleep_interval(void *arg);
int main(int argc, char **argv){
    
    pthread_t tid[5];
    int status[5];
    int time1 = 3, time2 = 6;

    pthread_create(&tid[0], NULL, sleep_interval, (void *)&time1);
    pthread_create(&tid[1], NULL, sleep_interval, (void *)&time2);
    // pthread_join(tid[0], (void *)&status[0]);
    // pthread_join(tid[1], (void *)&status[1]);
    // pthread_join(tid[2], (void *)&status[2]);
    // pthread_join(tid[3], (void *)&status[3]);
    // pthread_join(tid[4], (void *)&status[4]);

    // pause();
    while(1){
        printf("input:");
        scanf("%d", &status[0]);
        printf("input is %d\n",status[0]);
    }
    exit(0);
}

void *sleep_interval(void *arg){
    int interval = *(int *)arg;
    while(1){
        printf("%dth thread, sleep: %d\n", interval/2, interval);
        sleep(interval);
        printf("sleep for %d, wakeup ", interval);
    }
}
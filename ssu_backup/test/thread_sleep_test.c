#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>

void *sleep_interval(void *arg);


char filename1[50] = "thread_sleep_test1.txt";
char filename2[50] = "thread_sleep_test2.txt";
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
    char msg1[30];
    char msg2[30];
    FILE *fp;
    if(interval == 3)
        fp = fopen(filename1, "w+");
    else
        fp = fopen(filename2, "w+");
        
    sprintf(msg1, "%dth thread, sleep: %d\n", interval/2, interval);
    sprintf(msg2, "sleep for %d, wakeup ", interval);

    while(1){
        fwrite(msg1, sizeof(msg1), 1, fp);
        sleep(interval);
        fwrite(msg2, sizeof(msg2), 1, fp);
    }
}
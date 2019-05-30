#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>

void *sleep_interval(void *arg);


char filename1[50] = "thread_sleep_test1.txt";
char filename2[50] = "thread_sleep_test2.txt";
FILE *fp1;
int main(int argc, char **argv){
    
    pthread_t tid[5];
    int status[5];
    int time1 = 1, time2 = 2;
    fp1 = fopen(filename1, "w+");

    pthread_create(&tid[0], NULL, sleep_interval, (void *)&time1);
    pthread_create(&tid[1], NULL, sleep_interval, (void *)&time2);
    pthread_join(tid[0], (void *)&status[0]);
    pthread_join(tid[1], (void *)&status[1]);
    // pthread_join(tid[2], (void *)&status[2]);
    // pthread_join(tid[3], (void *)&status[3]);
    // pthread_join(tid[4], (void *)&status[4]);

    // pause();
    // while(1){
        printf("input:");
        scanf("%d", &status[0]);
        printf("input is %d\n",status[0]);
    // }
    fclose(fp1);
    exit(0);
}

void *sleep_interval(void *arg){
    int interval = *(int *)arg;
    char msg1[30];
    char msg2[30];
    FILE *fp;
    // if(interval == 3){
    //     fp = fopen(filename1, "w+");
    //     printf("interval 3\n");
    // }
    // else{
    //     fp = fopen(filename2, "w+");
    //     printf("interval 6\n");
    // }
        
    sprintf(msg1, "%dth thread, sleep: %d\n", interval/2, interval);
    sprintf(msg2, "sleep for %d, wakeup ", interval);

    for(int i=0; i<5; i++){
        fwrite(msg1, strlen(msg1), 1, fp1);
        sleep(interval);
        fwrite(msg2, strlen(msg2), 1, fp1);
        printf("%d: %dthfwrite finished\n",interval, i);
        fflush(fp1);
        fflush(fp1);
    }

    // while(1){
    // }
}
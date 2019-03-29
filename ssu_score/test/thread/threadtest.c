#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>

#define THREAD_NUM 3

void sigint_handler(int signo);
void *ssu_thread(void *arg);

struct thread_data {
    int thread_index;
    char *message;
};
int counter = 0;
struct thread_data threadArr[THREAD_NUM];
char *messages[THREAD_NUM];
pthread_t tid[5], mtid;
int main(int argc, char** argv){
    
    int fd,sum;
    signal( SIGALRM, sigint_handler);
    
    pid_t pid;


    messages[0]="whileTRUE1";
    messages[1]="whileTRUE3";
    messages[2]="whileTRUE3";

    for(int i=0; i<3; i++){
        sum = sum + i;
        threadArr[i].message = messages[i];
        threadArr[i].thread_index = i;
        printf("hello %d\n", i);

        if(pthread_create(&(tid[i]), NULL, ssu_thread, (void *)&threadArr) != 0){
            fprintf(stderr, "pthread_create error\n");
            exit(1);
        }        
        alarm(3);
    }

    for(int i=0; i<3; i++){
        pthread_join(tid[i], NULL);
    }

    pid = getpid();
    mtid = pthread_self();

    printf("main thread: pid %d tid %d\n",(int)pid, (unsigned int)mtid);

    exit(0);
}

void *ssu_thread(void *arg){    
    pthread_t tid;
    pid_t pid;

    struct thread_data *data;
    char *message, cmd[50]="./";
    int thread_index;

    pid = getpid();
    tid = pthread_self();
    
    data = (struct thread_data *)arg;
    thread_index = data->thread_index;
    message = data -> message;

    printf("new thread: pid %d tid %d\n",(int)pid, (unsigned int)tid);
    
    strcat(cmd, message);
    
    system(cmd);
    printf("%s is finished\n",message);
    return NULL;
}

void sigint_handler(int signo){
    printf("alarm\n");
    
    pthread_exit(NULL);
}
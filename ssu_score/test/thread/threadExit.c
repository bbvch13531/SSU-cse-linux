#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>


void sigint_handler(int signo);
void *ssu_thread(void *arg);

struct thread_data {
    int thread_index;
    char *message;
};
int counter = 0;
struct thread_data threadArr;
char *messages;
pthread_t tid, mtid;
int main(int argc, char** argv){
    
    int fd,sum;
    signal( SIGALRM, sigint_handler);
    
    pid_t pid;

    messages="whileTRUE1";

    threadArr.message = messages;
    threadArr.thread_index = 999;
    printf("start\n");


    pid = getpid();
    mtid = pthread_self();

    printf("main thread: pid %d tid %d\n",(int)pid, (unsigned int)mtid);


    if(pthread_create(&tid, NULL, ssu_thread, (void *)&threadArr) != 0){
        fprintf(stderr, "pthread_create error\n");
        exit(1);
    }       

    pthread_join(tid, NULL);
    

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
    alarm(3);
    // system(cmd);
    print("sleep 10\n");
    sleep(10);

    printf("%s is finished\n",message);
    return NULL;
}

void sigint_handler(int signo){
    fprintf(stdout,"alarm\n");
    fprintf(stdout,"tid = %d",(unsigned int)pthread_self());
    pthread_detach(pthread_self());
    // pthread_cancel(tid);
    pthread_exit(NULL);
    pthread_kill(tid, 0);
}
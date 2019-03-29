#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

void *watchdog(void *arg);
void *whilethread(void *arg);
int main(int argc, char **argv){
    pthread_t wtid, tid;
    sigset_t sigset;
    int sig_no = 0;

    signal(SIGALRM, SIG_IGN);

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGALRM);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    // SIGALRM을 sigset에 설정 
    // thread의 pthread_sigmask를 SIGALRM을 ㅗ설정
    pthread_sigmask(SIG_BLOCK, &sigset, NULL);

    // thread func안에서 sigwait... SIGALRM 받으면 쓰레드 종료!
    //sigwait(&sigset, &sig_no)
    alarm(3);
    
    pthread_create(&wtid, NULL, (void *)watchdog, NULL);
    pthread_detach(wtid);

    pthread_create(&tid, NULL, (void *)whilethread, NULL);
    pthread_detach(tid);


    exit(0);
}

void *watchdog(void *arg){
    sigset_t all_sigs;

    sigfillset(&all_sigs);
    sigprocmask(SIGALRM, &all_sigs, NULL);
}
void *whilethread(void *arg){
    while(1);
}
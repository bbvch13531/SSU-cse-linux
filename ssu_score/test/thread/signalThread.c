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
void cleanup(void *arg);
void sg_handler(int nSigNum);

int tidNum;
pthread_t wtid, tid;

int main(int argc, char **argv){
    sigset_t sigset;

    int sig_no = 0;

    signal(SIGALRM, sg_handler);

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGALRM);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    printf("*Process PID = %d\n", getpid());

    // SIGALRM을 sigset에 설정 
    // thread의 pthread_sigmask를 SIGALRM으로 설정
    pthread_sigmask(SIG_BLOCK, &sigset, NULL);

    // thread func안에서 sigwait... SIGALRM 받으면 쓰레드 종료!
    //sigwait(&sigset, &sig_no)

    // wtid 에서 sigwait으로 SIGALRM 받으면 whilethread의 tid로 종료시키자!
    pthread_create(&wtid, NULL, (void *)watchdog, NULL);

    printf("whilethread starts\n");
        pthread_create(&tid, NULL, (void *)whilethread, NULL);
        pthread_join(tid, NULL);
    
//    pthread_cancel(tidNum); //tid 에 종료 요청 보내기
  //  pthread_cond_signal(&cond);
    pthread_join(wtid, NULL);

    printf("After main ends!\n");
    
    exit(0);
}

void *watchdog(void *arg){
    sigset_t alrm_sigs;
    int nErrno, nSigNum;
    int flag = 0;
    sigemptyset(&alrm_sigs);
    sigaddset(&alrm_sigs, SIGALRM);
    // sigprocmask(SIGALRM, &alrm_sigs, NULL);

    while(1){
        if(flag == 1) break;
        nErrno = sigwait(&alrm_sigs, &nSigNum);
        if(nErrno >  0){
            perror("sigwait error\n");
            return NULL;
        }
        // signal no. 에 따라 signal handler 함수 호출 혹은 종료
        switch(nSigNum){
            case SIGALRM:
                printf("[signal SIGALRM]\n");
                sg_handler(nSigNum);
                // exit(EXIT_SUCCESS);
            default:
                printf("default\n");
                flag = 1;
            break;
        }
    }
    pthread_exit(0);
    printf("watchdog ends!\n");
}
void *whilethread(void *arg){
    tidNum = pthread_self();
    // pthread_cleanup_push(cleanup, NULL);
    printf("while thread tidNum = %u\n",tidNum);
    
    alarm(3);
    // 쓰레드에 대한 취소요청을 허용한다. 
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    
    // 쓰레드 종료시 호출될 함수 등록
    for(int i=0; i<10000; i++){
        sleep(1);
        printf("for 10000 %d\n", i);
    }
    printf("while thread ends!\n");
    // pthread_cleanup_pop(0);
}

void sg_handler(int nSigNum){
    printf("Thread tid : %lu, tidNum = %d\n",pthread_self(), tidNum);

    pthread_cancel(tid);
    // pthread_kill(tid, SIGKILL);
    // syscall(SYS_tkill, tidNum, 9);
    // tkill(tidNum, SIGTERM);

}
void cleanup(void *arg){
    printf("thread ends!\n");
}
//https://stackoverflow.com/questions/32283171/signal-handler-in-a-separate-pthread-using-timer-create

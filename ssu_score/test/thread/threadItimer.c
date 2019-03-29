#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

void itimer_event_thread(void *params);

int main(int argc, char **argv){
    pthread_t thread;
    sigset_t sigset;
    int sig_no = 0;
    int rc;

    signal(SIGALRM, SIG_IGN);

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGALRM);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    pthread_sigmask(SIG_BLOCK, &sigset, NULL);

    rc = pthread_create(&thread, NULL, (void *)itimer_event_thread, NULL);
    if(rc){
        printf("itimer_event_thread : %s\n",strerror(errno));
    }
    else{
        (void) pthread_detach(thread);
    }
    while(1)
        usleep(1000);
    exit(0);
}
void itimer_event_thread(void *params){
    struct itimerval itimer;
    sigset_t sigset;
    int sig_no = 0;
    struct timeval now;
    unsigned int time_gap_sec = 0, time_gap_usec = 0;

    printf("%s() start!\n",__func__);

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGALRM);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    pthread_sigmask(SIG_UNBLOCK, &sigset, NULL);

    itimer.it_value.tv_sec = 0;
    itimer.it_value.tv_usec = 100 * 1000;
    itimer.it_interval = itimer.it_value;

    if(setitimer(ITIMER_REAL, &itimer, NULL) != 0){
        printf("Could not start interval timer : $s", strerror(errno));
        exit(1);
    }

    // wait signal forever

    while(1){
        if(sigwait(&sigset, &sig_no) != 0){
            printf("Failed to wait for next clock tick\n");
        }

        switch(sig_no){
            case SIGALRM:
                gettimeofday(&now, NULL);
                fprintf(stdin,"now = %ld.%06ld, gap = %ld.%06ld\n",
                    now.tv_sec, now.tv_usec, now.tv_sec-time_gap_sec, now.tv_usec-time_gap_usec);
                time_gap_sec = now.tv_sec;
                time_gap_usec = now.tv_usec;
                break;
            
            default:
                printf("unexpected signal %d\n",sig_no);
        }
    }


}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *ssu_thread(void *arg);

int main(void){
	pthread_t tid;
	pid_t pid;

	if(pthread_create(&tid, NULL, ssu_thread, NULL) != 0){	// 새 쓰레드 생성
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	pid = getpid();	//프로세스 id
	tid = pthread_self();	// 쓰레드 id
	printf("Main Thread: pid %u tid %u \n", (unsigned int)pid, (unsigned int)tid);
	sleep(1);

	exit(0);
}

void *ssu_thread(void *arg){	// 쓰레드에서 실행하는 함수
	pthread_t tid;
	pid_t pid;

	pid = getpid();
	tid = pthread_self();
	printf("New Thread: pid %u tid %u \n", (unsigned int)pid, (unsigned int)tid);
	
	return NULL;
}

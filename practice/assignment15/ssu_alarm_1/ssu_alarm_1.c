#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo);

int count = 0;

int main(void){
	signal(SIGALRM, ssu_signal_handler);	// 시그널 핸들러 지정
	alarm(1);

	while(1);

	exit(0);
}

void ssu_signal_handler(int signo){
	printf("alarm %d\n", count++);	// 시그널 발생할 때 출력
	alarm(1);
}


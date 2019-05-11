#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo);	// 시그널 핸들러

void (*ssu_func)(int);	// 실행할 함수

int main(void){
	ssu_func = signal(SIGINT, ssu_signal_handler);	// SIGINT의 핸들러 등록

	while(1){
		printf("precess running...\n");
		sleep(1);
	}

	exit(0);
}

void ssu_signal_handler(int signo){
	printf("SIGINT 시그널 발생.\n");
	printf("SIGINT를 SIG_DFL로 재설정 함.\n");
	signal(SIGINT, ssu_func);
}

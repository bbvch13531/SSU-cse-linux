#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo){
	printf("ssu_signal_handler control\n");
}

int main(void){
	struct sigaction sig_act;
	sigset_t sig_set;

	sigemptyset(&sig_act.sa_mask);	// sig_act를 초기화
	sig_act.sa_flags = 0;	// flag를 0으로 설정
	sig_act.sa_handler = ssu_signal_handler;	//시그널 핸들러 지정
	sigaction(SIGUSR1, &sig_act, NULL);	// action을 지정
	printf("before first kill()\n");

	kill(getpid(), SIGUSR1);	// 현재 프로세스에 SIGUSR1 전달
	sigemptyset(&sig_set);	//sigset 초기화
	sigaddset(&sig_set, SIGUSR1);	//sigset에 SIGUSR1 추가
	sigprocmask(SIG_SETMASK, &sig_set, NULL);	// sigset을 마스크로 설정
	printf("before second kill()\n");
	kill(getpid(), SIGUSR1);	// 현재 프로세스에 SIGUSR1 전달
	printf("after second kill()\n");
	exit(0);
}

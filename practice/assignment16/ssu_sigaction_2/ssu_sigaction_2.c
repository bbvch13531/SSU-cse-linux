#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_check_pending(int signo, char *signame);
void ssu_signal_handler(int signo);

int main(void){
	struct sigaction sig_act;
	sigset_t sig_set;

	sigemptyset(&sig_act.sa_mask);	// sigact 초기화
	sig_act.sa_flags = 0;
	sig_act.sa_handler = ssu_signal_handler;	// 시그널 핸들러 지정

	if(sigaction(SIGUSR1, &sig_act, NULL) != 0){	// 시그널 액션 설정
		fprintf(stderr, "sigaction() error\n");
		exit(1);
	}
	else{
		sigemptyset(&sig_set);	// sigset 초기화
		sigaddset(&sig_set, SIGUSR1);	// sigset에 SIGUSR1 추가

		if(sigprocmask(SIG_SETMASK, &sig_set, NULL) != 0){	//sigset을 마스킹
			fprintf(stderr, "sigprocmask() error\n");
			exit(1);
		}
		else{
			printf("SIGUSR1 signals are now blocked\n");
			kill(getpid(), SIGUSR1);	//현재 프로세스에 SIGUSR1 전달
			printf("after kill()\n");
			ssu_check_pending(SIGUSR1, "SIGUSR1");
			sigemptyset(&sig_set);	//sigset 초기화
			sigprocmask(SIG_SETMASK, &sig_set, NULL);	// sigset을 마스킹
			printf("SIGUSR1 signals are no longer blocked\n");
			ssu_check_pending(SIGUSR1, "SIGUSR1");
		}
	}
	exit(0);
}

void ssu_check_pending(int signo, char *signame){
	sigset_t sig_set;

	if(sigpending(&sig_set) != 0)
		printf("sigpending() error\n");
	else if(sigismember(&sig_set, signo))
		printf("a %s signal is pending\n", signame);
	else
		printf("%s signals are not pending\n", signame);
}

void ssu_signal_handler(int signo){
	printf("in ssu_signal_handler function\n");
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

static void ssu_signal_handler1(int signo);
static void ssu_signal_handler2(int signo);

sigjmp_buf jmp_buf1;
sigjmp_buf jmp_buf2;

int main(void){
	struct sigaction act_sig1;
	struct sigaction act_sig2;
	int i, ret;

	printf("My PID is %d\n", getpid());
	ret = sigsetjmp(jmp_buf1, 1);	// setjmp 설정

	if(ret == 0){
		act_sig1.sa_handler = ssu_signal_handler1;	// 시그널 핸들러 설정
		sigaction(SIGINT, &act_sig1, NULL);		// sigaction 설정
	}
	else if(ret == 3)
		printf("-----------------------\n");

	printf("starting\n");
	sigsetjmp(jmp_buf2, 2);
	act_sig2.sa_handler = ssu_signal_handler2;	// 시그널 핸들러 설정
	sigaction(SIGUSR1, &act_sig2, NULL);	// sigaction 설정

	for(i=0; i<20; i++){
		printf("i = %d\n", i);
		sleep(1);
	}

	exit(0);
}
static void ssu_signal_handler1(int signo){
	fprintf(stderr, "\nInterrupted\n");
	siglongjmp(jmp_buf1, 3);	// longjmp 설정
}

static void ssu_signal_handler2(int signo){
	fprintf(stderr, "\nSIGUSR1\n");
	siglongjmp(jmp_buf2, 3);	// longjmp 설정
}
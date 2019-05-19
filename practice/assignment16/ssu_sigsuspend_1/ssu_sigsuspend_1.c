#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void){
	sigset_t old_set, sig_set;

	sigemptyset(&sig_set);	// sigset 초기화
	sigaddset(&sig_set, SIGINT);	// SIGINT 추가
	sigprocmask(SIG_BLOCK, &sig_set, &old_set);
	sigsuspend(&old_set);	// oldset을 suspend
	exit(0);
}

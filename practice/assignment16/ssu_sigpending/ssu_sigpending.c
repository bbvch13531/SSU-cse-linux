#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void){
	sigset_t pendingset, sig_set;
	int count = 0;

	sigfillset(&sig_set);	// sigset을 채운다.
	sigprocmask(SIG_SETMASK, &sig_set, NULL);	// sigset을 sigset_t로 설정

	while(1){
		printf("count: %d\n", count++);
		sleep(1);

		if(sigpending(&pendingset) == 0){	// pendingset을 pending
			if(sigismember(&pendingset, SIGINT)){	// pendingset에 sigint가 있는지 확인
				printf("SIGINT가 블록되어 대기 중. 무한 루프를 종료.\n");
				break;
			}
		}
	}
	exit(0);
}

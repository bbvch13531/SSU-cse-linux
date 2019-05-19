#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

static void ssu_func(int signo);
void ssu_print_mask(const char *str);

int main(void){
	sigset_t new_mask, old_mask, wait_mask;
	ssu_print_mask("program start: ");

	if(signal(SIGINT, ssu_func) == SIG_ERR){	// SIGINT에 대한 시그널 핸들러 설정
		fprintf(stderr, "signal(SIGINT) error\n");
		exit(1);
	}

	sigemptyset(&wait_mask);	// wait_mask 초기화
	sigaddset(&wait_mask, SIGUSR1);	// wait_mask에 SIGUSR1을 mask
	sigemptyset(&new_mask);		// new_mask 초기화
	sigaddset(&new_mask, SIGINT);	// new_mask에 SIGINT를 mask

	if(sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0){	// new_mask로 sigset_t를 설정
		fprintf(stderr, "SIG_BLOCK() error\n");
		exit(1);
	}

	ssu_print_mask("int critical region: ");

	if(sigsuspend(&wait_mask) != -1){	// wait_mask를 panding
		fprintf(stderr, "sigsuspend() error\n");
		exit(1);
	}

	ssu_print_mask("after return from sigsuspend :");

	if(sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0){	// old_mask로 sigset_t를 설정
		fprintf(stderr, "SIG_SETMASK() error\n");
		exit(1);
	}

	ssu_print_mask("program exit: ");

	exit(0);
}

static void ssu_func(int signo){
	ssu_print_mask("\nin ssu_func: ");
}

void ssu_print_mask(const char *str){
	sigset_t sig_set;
	int err_num;

	err_num = errno;

	if(sigprocmask(0, NULL, &sig_set) < 0){		// sigset_t를 NULL로 설정
		fprintf(stderr, "sigprocmask() error\n");
		exit(1);
	}
	printf("%s", str);
		// 해당하는 시그널을 출력
	if(sigismember(&sig_set, SIGINT))
		printf("SIGINT ");

	if(sigismember(&sig_set, SIGQUIT))
		printf("SIGQUIT ");

	if(sigismember(&sig_set, SIGUSR1))
		printf("SIGUSR1 ");

	if(sigismember(&sig_set, SIGALRM))
		printf("SIGALRM ");

	printf("\n");
	errno = err_num;
}

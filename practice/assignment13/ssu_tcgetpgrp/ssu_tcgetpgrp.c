#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <termios.h>

#define STDIN_NUMBER 0

static void ssu_sig_hup(int signum);
static void ssu_print_ids(char *name);

int main(void){
	pid_t pid;
	char ch;

	ssu_print_ids("parent");	// 부모의 정보 출력
	if((pid = fork()) < 0){	// 프로세스 생성
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid > 0){	// 부모 프로세스
		sleep(3);
		exit(0);
	}
	else{	// 자식 프로세스
		ssu_print_ids("child");		// 자식의 정보 출력
		signal(SIGHUP, ssu_sig_hup);	// 시그널 처리
		kill(getpid(), SIGTSTP);	// 프로세스 종료
		ssu_print_ids("child");		// 자식의 정보 출력

		if(read(STDIN_FILENO, &ch, 1) != 1)
			fprintf(stderr, "read error\n");
	exit(0);

	}
}

static void ssu_sig_hup(int signum){
	printf("ssu_SIG_HUP received, pid = %d\n", getpid());
}
static void ssu_print_ids(char *name){
	printf("[%s] : pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n", name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_NUMBER));
	fflush(stdout);
}

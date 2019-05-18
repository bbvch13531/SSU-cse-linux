#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define LINE_MAX 2048

static void ssu_alarm(int signo);

int main(void){
	char buf[LINE_MAX];
	int n;

	if(signal(SIGALRM, ssu_alarm) == SIG_ERR){ // 시그널 핸들러 설정
		fprintf(stderr, "SIGALRM error\n");
		exit(1);
	}
	alarm(5);	// 10초 알람 설정

	if((n = read(STDIN_FILENO, buf, LINE_MAX)) < 0){
		fprintf(stderr, "read() error\n");
		exit(1);
	}

	alarm(0);
	write(STDOUT_FILENO, buf, n);	// 읽은 버퍼를 출력
	exit(0);
}

static void ssu_alarm(int signo){
	printf("ssu_alarm() called!\n");
}

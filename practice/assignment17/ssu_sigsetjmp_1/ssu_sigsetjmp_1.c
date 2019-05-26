#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

void ssu_signal_handler(int signo);	//시그널 핸들러

jmp_buf jump_buffer;

int main(void){
	signal(SIGINT, ssu_signal_handler); // 시그널 핸들러 설정

	while(1){
		if(setjmp(jump_buffer) == 0){	// setjmp 설정
			printf("Hit Ctrl-c at anytime ...\n");
			pause();	// 프로그램 멈춤
		}
	}

	exit(0);
}

void ssu_signal_handler(int signo){
	char character;

	signal(signo, SIG_IGN);
	printf("Did you hit Ctrl-c?\n" "Do you really want to quit? [y/n]");
	character = getchar();

	if(character == 'y' || character == 'Y')
		exit(0);
	else{
		signal(SIGINT, ssu_signal_handler);	// 다시 시그널 핸들러 설정
		longjmp(jump_buffer, 1);	// longjmp 함수 사용
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void ssu_signal_handler(int signo);

int main(void){
	if(signal(SIGINT, ssu_signal_handler) == SIG_ERR){	// SIGINT 핸들러 등록
		fprintf(stderr, "cannot handle SIGINT\n");
		exit(1);
	}

	if(signal(SIGTERM, ssu_signal_handler) == SIG_ERR){	// SIGTERM 핸들러 등록
		fprintf(stderr, "cannot handle SIGTERM\n");
		exit(1);
	}

	if(signal(SIGPROF, ssu_signal_handler) == SIG_ERR){	// SIGPROF 핸들러 등록
		fprintf(stderr, "cannot handle SIGPROF\n");
		exit(1);
	}

	if(signal(SIGHUP, ssu_signal_handler) == SIG_ERR){	// SIGHUP 핸들러 등록
		fprintf(stderr, "cannot handle SIGHUP\n");
		exit(1);
	}

	while(1)
		pause();

	exit(0);
}

static void ssu_signal_handler(int signo){
	if(signo == SIGINT)	// 시그널 출력
		printf("caught SIGINT\n");
	else if(signo == SIGTERM)
		printf("caught SIGTERM\n");
	else{
		fprintf(stderr, "unexpected signal\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

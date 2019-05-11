#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void ssu_signal_handler(int signo);

int main(void){
	if(signal(SIGINT, ssu_signal_handler) == SIG_ERR){
		fprintf(stderr, "cannot handle SIGINT\n");
		exit(1);
	}

	if(signal(SIGTERM, ssu_signal_handler) == SIG_ERR){
		fprintf(stderr, "cannot handle SIGTERM\n");
		exit(1);
	}

	if(signal(SIGPROF, ssu_signal_handler) == SIG_ERR){
		fprintf(stderr, "cannot handle SIGPROF\n");
		exit(1);
	}

	if(signal(SIGHUP, ssu_signal_handler) == SIG_ERR){
		fprintf(stderr, "cannot handle SIGHUP\n");
		exit(1);
	}

	while(1)
		pause();

	exit(0);
}

static void ssu_signal_handler(int signo){
	if(signo == SIGINT)
		printf("caught SIGINT\n");
	else if(signo == SIGTERM)
		printf("caught SIGTERM\n");
	else{
		fprintf(stderr, "unexpected signal\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
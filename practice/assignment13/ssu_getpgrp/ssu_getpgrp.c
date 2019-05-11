#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	pid_t pgid;
	pid_t pid;

	pid = getpid();	// 현재 프로세스 번호 가져온다.
	pgid = getpgrp();	// 현재 프로세스 그룹 번호 가져온다.
	printf("pid: %d, pgid: %d\n", pid, pgid);
	exit(0);
}

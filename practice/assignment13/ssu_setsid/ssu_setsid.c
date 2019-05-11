#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	pid_t pid;

	if((pid = fork()) < 0){	// 새 프로세스 생성
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid != 0)	// 부모 프로세스인 경우 종료
		exit(1);

	printf("before pid = %d, sid = %d\n", getpid(), getsid(getpid()));	// 프로세스 번호와 세션번호 출력
	setsid();
	printf("after pid = %d, sid = %d\n", getpid(), getsid(getpid()));	// 프로세스 번호와 세션번호 출력

	exit(0);
}

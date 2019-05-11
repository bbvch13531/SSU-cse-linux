#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
	pid_t pgid;
	pid_t pid;
	
	if(argc < 2){
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		exit(1);
	}
	pid = getpid();	// 현재 프로세스 번호 가져온다.
	pgid = getpgid(atoi(argv[1]));	// 인자로 받은 파일의 프로세스 그룹 번호 가져온다.
	printf("pid: %d, pgid: %d\n", pid, pgid);
	exit(0);
}

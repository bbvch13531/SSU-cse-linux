#include <stdio.h>
#include <stdlib.h>

int main(void){
	printf("abort terminate this program\n");
	abort();	// abort 함수. 프로그램 종료
	printf("this line is never reached\n");

	exit(0);
}

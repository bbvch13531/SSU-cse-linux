#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void ssu_timestamp(char *str);

int main(void){
	unsigned int ret;

	ssu_timestamp("before sleep()");
	ret = sleep(10);	// 10초 sleep
	ssu_timestamp("after sleep()");
	printf("sleep() returned %d\n");
	exit(0);
}

void ssu_timestamp(char *str){
	time_t time_val;

	time(&time_val);
	printf("%s th time is %s\n", str, ctime(&time_val));
}
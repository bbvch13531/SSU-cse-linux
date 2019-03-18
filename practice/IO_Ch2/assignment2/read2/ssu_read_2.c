#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000
#define BUFFER_SIZE 1024

int main(int argc, char ** argv){
    struct timeval begin_t, end_t;
	char buf[BUFFER_SIZE];
	char *fname = "ssu_test.txt";
    int count;
    int fd1, fd2;

    gettimeofday(&begin_t, NULL);
    fd1 = open(fname, O_RDONLY, 0644);  // 파일을 644로 읽고 fd1을 설정
    fd2 = open(fname, O_RDONLY, 0644);  // 파일을 644로 읽고 fd2를 설정

    if(fd1 < 0 || fd2 < 0){
        fprintf(stderr, "open error for %s\n", fname);
        exit(1);
    }

    count = read(fd1, buf, 25);     // fd1에서 25바이트 읽고 buf에 저장
    buf[count] = 0;
    printf("fd1's first printf : %s\n", buf);
    lseek(fd1, 1, SEEK_CUR);    // 현재 포인터에서 1만큼 이동
    
    count = read(fd1, buf, 24);     // fd1에서 24바이트 읽고 buf에 저장
    buf[count] = 0;
    printf("fd1's second printf : %s\n", buf);
    
    count = read(fd2, buf, 25);     // fd2에서 25바이트 읽고 buf에 저장
    buf[count] = 0;
    printf("fd2's first printf : %s\n", buf);

    lseek(fd2, 1, SEEK_CUR);    // 현재 포인터에서 1만큼 이동
    count = read(fd2, buf, 24);     // fd2에서 24바이트 읽고 buf에 저장
    buf[count] = 0;
    printf("fd2's second printf : %s\n", buf);
     
    gettimeofday(&end_t, NULL);
    end_t.tv_sec -= begin_t.tv_sec;
	if(end_t.tv_usec < begin_t.tv_usec){
		end_t.tv_sec--;
		end_t.tv_usec += SEC_TO_MICRO;
	}
	end_t.tv_usec -= begin_t.tv_usec;
	printf("Runtime: %ld:%ld\n",end_t.tv_sec, end_t.tv_usec);
}
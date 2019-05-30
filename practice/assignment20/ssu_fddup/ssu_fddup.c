#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void){
    int testfd;
    int fd;

    fd = open("test.txt", O_CREAT);

    testfd = fcntl(fd, F_DUPFD, 5);
    printf("testfd :%d\n", testfd);
    testfd = fcntl(fd, F_DUPFD, 5); // fd 5 는 이미 사용됨
    printf("testfd :%d\n", testfd);

    getchar();
}
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define SIZE 10
#define BLOCK_SIZE 10

char buf1[BLOCK_SIZE+1], buf2[BLOCK_SIZE+1], tmp[BLOCK_SIZE+1];

int main(int argc, char** argv){
    int fd,cnt=0;
    int len, offset;
    char *data;

    if(argc != 4){
        exit(1);
    }

    fd = open(argv[1], O_RDWR);
    offset = atoi(argv[2]);
    data = argv[3];

    lseek(fd, offset, SEEK_SET);

    // offset 부터 EOF까지 파일의 데이터를 10바이트 이동
    // cur 부터 10바이트 읽어서 buf1에 저장
    len = read(fd, buf1, BLOCK_SIZE);
    // printf("buf1 = %s, len = %d\n", buf1, len);

    while(1){
        // printf("cnt: %d\n",cnt++);
        if((len = read(fd, buf2, BLOCK_SIZE)) < 10){
            lseek(fd, -1 * len, SEEK_CUR);
            write(fd, buf1, BLOCK_SIZE);
            write(fd, buf2, len);
            // printf("buf1 = %s, buf2 = %s, len = %d\tread2\n",buf1, buf2, len);
            break;
        }
        // printf("buf2 = %s\n", buf2);
        lseek(fd, -1 * BLOCK_SIZE, SEEK_CUR);
        write(fd, buf1, BLOCK_SIZE);
        
        if((len = read(fd, buf1, BLOCK_SIZE)) < 10){
            lseek(fd, -1 * len, SEEK_CUR);
            write(fd, buf2, BLOCK_SIZE);
            write(fd, buf1, len);
            // printf("buf1 = %s, buf2 = %s, len = %d\tread1\n",buf1, buf2, len);
            break;
        }
        // printf("buf1 = %s\n", buf1);
        lseek(fd, -1 * BLOCK_SIZE, SEEK_CUR);
        write(fd, buf2, BLOCK_SIZE);
    }

    // offset에 buf write
    // printf("ERROR : %s\n",strerror(errno));
    lseek(fd, offset, SEEK_SET);
    write(fd, data, BLOCK_SIZE);

    printf("Insert susscessed!");
    return 0;
}
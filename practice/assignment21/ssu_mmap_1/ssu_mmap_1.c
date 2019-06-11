#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char **argv){
    int fdin, fdout;
    void *src, *dst;
    struct stat statbuf;

    if(argc != 3){
        printf("usage: %s <fromfile> <tofile>", argv[0]);
        exit(1);
    }    

    if((fdin = open(argv[1], O_RDONLY)) < 0){   //fdin open
        printf("can't open %s for reading", argv[1]);
        exit(1);
    }

    if((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0){ // fdout open
        printf("can't creat %s for reading", argv[2]);
        exit(1);
    }

    if(fstat(fdin, &statbuf) < 0){  // statbuf 저장
        printf("fstat() error");
        exit(1);
    }

    if(lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1){  // 마지막으로 포인터 이동
        printf("lseek() error");
        exit(1);
    }
    if(write(fdout, "", 1) != 1){   // 마지막에 공백 추가
        printf("write() error");
        exit(1);
    }

    if((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED){ // mmap으로 읽기
        printf("mmap() error for input");
        exit(1);
    }

    if((dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0)) == MAP_FAILED){   // mmap으로 쓰기
        printf("mmap() error for output");
        exit(1);
    }
    
    memcpy(dst, src, statbuf.st_size);
    return 0;
}
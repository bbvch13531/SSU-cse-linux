#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#ifndef MAP_FILE
#define MAP_FILE 0
#endif

void serror(char *str){ // 에러 출력 함수
    fprintf(stderr, "%s\n", str);
    exit(1);
}

int main(int argc, char **argv){
    int fdin, fdout;
    void *inp, *outp;
    struct stat statbuf;

    if(argc != 3)
        serror("usage: a.out [source file] [target file]");

    if((fdin = open(argv[1], O_RDONLY)) < 0)    // fdin open
        serror("can't open file for reading");

    if((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0){ // fdout open
        serror("can't creat file for reading");
    }

    if(fstat(fdin, &statbuf) < 0)   // statbuf 저장
        serror("fstat error");

    if(lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1)   //파일의 마지막으로 이동
        serror("lseek() error");

    if(write(fdout, "", 1) != 1)    //공백 추가
        serror("write() error");

    if((inp = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == (caddr_t)-1) //mmap으로 read, shared memory
        serror("mmap error for input");
    

    if((outp = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0)) == (caddr_t)-1)  // mmap으로 read, write, shared memory
        serror("mmap error for output");

    memcpy(outp, inp, statbuf.st_size);
    return 0;
}
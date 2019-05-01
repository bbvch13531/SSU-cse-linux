#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>

#define EOF -1
#define CHAR 0
#define DIGIT 1
#define OTHERS 2

int flag = 0; // opt flag
char targetfilename[50];
int main(int argc, char **argv){
    int opt;
    // Handling options
    /*
        j
        c
        p
        f
        l
        r
    */
    if(argc <2){
        printf("usage: ./ssu_convert <filename>\n");
        exit(1);
    }
    sprintf(targetfilename, "%s", argv[1]);

    while((opt = getopt(argc, argv, "jcpflr")) != -1){
        switch(opt){
            case 'r':
                break;
            case 'j':
                break;
            case 'c':
                break;
            case 'p':
                break;
            case 'f':
                break;
            case 'l':
                break;
        }
    }
    // 자바파일 읽는다.
    // 파싱한다.
    // 버퍼에 넣는다.
    // makefile 만든다
    // C파일 만든다
    // 


    // 옵션 없는 경우
    if(flag == 0){
        printf("%s.c convert Success!\n", targetfilename);
    }
    if(flag == 1){

    }
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024
#define WORD_MAX 100

int main(void){
    int fd;
    int length = 0, offset = 0, count = 0;
    char *fname = "ssu_test.txt";
    char buf[WORD_MAX][BUFFER_SIZE];
    
    if((fd = open(fname, O_RDONLY, 0644)) < 0){
        fprintf(stderr, "open error for %s\n",fname);
        exit(1);
    }

    while((length = read(fd, buf[count], BUFFER_SIZE)) > 0){
        buf[count][length] = '\0';
        for(int i=0; i<BUFFER_SIZE; i++){
            if(buf[count][i] == '\n'){
                if(i==0)
                    break;
                
                offset = offset + i + 1;    // 이 부분 중요!
                
                lseek(fd, offset, SEEK_SET);    // 이 부분 중요!
                count++;
            }
        }
    }
    close(fd);

    for(int i=0; i<count; i++){
        printf("buf = %s\n",buf[i]);
    }
    printf("line number = %d\n",count);
    exit(0);
}

/*
실행결과
buf = Linux System Programming!
Unix System Programming!
Linux Mania
Unix Mania
buf = Unix System Programming!
Linux Mania
Unix Mania
buf = Linux Mania
Unix Mania
line number = 3
*/
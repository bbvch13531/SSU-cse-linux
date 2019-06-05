#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    int flag;
    
    if((flag = fcntl(STDOUT_FILENO, F_DUPFD)) == -1){   // 에러가 발생하는 코드
        fprintf(stderr, "Error : Copying File Descriptor\n");
        exit(1);
    }
    printf("CLOSE ON EXEC flag is = %d\n", flag);   // 실행되지 않음.
    exit(0);
}
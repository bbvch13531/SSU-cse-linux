#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MSG "message will be written to Terminal\n"

int main(void){
    int new_fd;
    
    if((new_fd = fcntl(STDOUT_FILENO, F_DUPFD, 3)) == -1){  // stdout 을 dup
        fprintf(stderr, "Error : Copying File Descriptor\n");
        exit(1);
    }
    close(STDOUT_FILENO);   // stdout을 close한다.
    write(3, MSG, strlen(MSG)); // dup한 new_fd에 write. 터미널 출력
    exit(0);
}
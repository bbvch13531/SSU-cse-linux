// SSU_20142468 Kyungyoung Heo
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 1024

int main(int argc, char** argv){
    int fd_wr, fd_rd;
    char buff[BUFF_SIZE];
    char *str = "Hello dup2!";

    
    fd_wr = open("./dup2test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    fd_rd = dup2(fd_wr,1);
    /*
        File Descriptor:
            0 : Standard input
            1 : Standard output
            2 : Standard error
        Change File Descriptor pointing STDOUT to fd_wr
    */
    
    printf("fd_wr = %d, fd_rd = %d\n",fd_wr,fd_rd);
    system("ls -d */");
    // ls directory only, system() 사용 금지됨.
    
    close(fd_wr);
    close(fd_rd);
    exit(0);
}
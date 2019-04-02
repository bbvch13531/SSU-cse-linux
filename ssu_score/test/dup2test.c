// SSU_20142468 Kyungyoung Heo
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 1024

int main(int argc, char** argv){
    int fd_wr, fd_rd, saved_stdout;
    char buff[BUFF_SIZE];
    char *str = "Hello dup2!";

    saved_stdout = dup(1);
    fd_wr = open("./dup2test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    dup2(fd_wr,1);
    /*
        File Descriptor:
            0 : Standard input
            1 : Standard output
            2 : Standard error
        Change File Descriptor pointing STDOUT to fd_wr
    */
    
    // printf("fd_wr = %d, fd_rd = %d\n",fd_wr,fd_rd);
    printf("Hello!");
    // system("ls -d */");
    // ls directory only, system() 사용 금지됨.
    // dup2(1, fd_wr);
    fflush(stdout);
    dup2(saved_stdout, 1);
    printf("World!");
    // close(fd_rd);
    close(fd_wr);
    exit(0);
}
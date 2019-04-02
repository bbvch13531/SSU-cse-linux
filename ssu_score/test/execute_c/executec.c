#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 1024
int main(int argc, char** argv){


    int fd_wr, fd_rd, fd_err_wr, fd_err_rd;
    char buff[BUFF_SIZE];
    char *str = "Hello dup2!";

    fd_wr = open("./executec_test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    fd_err_wr = open("./executec_err_test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    fd_rd = dup2(fd_wr,1);
    fd_err_rd = dup2(fd_err_wr,2);
    /*
        File Descriptor:
            0 : Standard input
            1 : Standard output
            2 : Standard error
        Change File Descriptor pointing STDOUT to fd_wr
    */
    system("gcc -o example1.stdexe example1.c");
    system("./example1.stdexe");
    exit(0);
}
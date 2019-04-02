#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SIZE 100

int main(int argc, char** argv){
    int rd_fd, wr_fd;
    int len;
    char buf[SIZE+1];

    if(argc != 3){
        exit(1);
    }

    rd_fd = open(argv[1], O_RDONLY);
    wr_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    while(len = read(rd_fd, buf, SIZE) > 0){
        write(wr_fd, buf, SIZE);
    }

    return 0;
}

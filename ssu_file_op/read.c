#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SIZE 10

int main(int argc, char** argv){
    int rd_fd, wr_fd;
    int len, offset;
    char buf[SIZE+1];

    if(argc != 3){
        exit(1);
    }

    rd_fd = open(argv[1], O_RDONLY);
    offset = atoi(argv[2]);

    lseek(rd_fd, offset, SEEK_SET);

    read(rd_fd, buf, SIZE);
    write(1, buf, SIZE);

    return 0;
}

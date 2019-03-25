#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SIZE 10

int main(int argc, char** argv){
    int rd_fd;
    int len, offset;
    char *buf;

    if(argc != 4){
        exit(1);
    }

    rd_fd = open(argv[1], O_RDWR);
    offset = atoi(argv[2]);
    buf = argv[3];
    lseek(rd_fd, offset, SEEK_SET);
    write(rd_fd, buf, SIZE);

    return 0;
}

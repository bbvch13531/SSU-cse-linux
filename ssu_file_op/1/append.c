#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SIZE 10

int main(int argc, char** argv){
    int wd_fd;
    char *buf;

    if(argc != 3){
        exit(1);
    }

    wd_fd = open(argv[1], O_RDWR);
    buf = argv[2];
    // printf("%s\n",buf);
    lseek(wd_fd, 0, SEEK_END);
    write(wd_fd, buf, SIZE);

    return 0;
}

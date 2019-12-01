#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(void){
    int fd;

    fd = open("a.txt", O_CREAT | O_EXCL);

    if(fd < 0){
        printf("Opening file : Failed\n");
        printf("Errno is : %d\n", errno);
        printf("Error description is : %s\n", strerror(errno));
    }
    else{
        printf("Opening file : Success\n");
    }
    exit(0);
}
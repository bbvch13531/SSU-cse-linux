#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void){
    char *fname = "ssu_test.txt";
    int fd;
    // fname을 ReadOnly로 open. fd가 0보다 작으면 에러
    if((fd = open(fname, O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n", fname);
        exit(1);
    }
    else
        printf("Success!\nFilename : %s\nDescriptor : %d \n", fname, fd);

    exit(0);
}

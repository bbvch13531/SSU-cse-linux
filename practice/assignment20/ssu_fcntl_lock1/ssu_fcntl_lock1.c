#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define NAMESIZE 50
#define MAXTRIES 5

struct employee{
    char name[NAMESIZE];
    int salary;
    int pid;
};

int main(int argc, char *argv[]){
    struct flock lock;
    struct employee record;
    int fd, sum=0, try=0;

    sleep(10);
    
    if((fd = open(argv[1], O_RDONLY)) == -1){
        perror(argv[1]);
        exit(1);
    }

    lock.l_type
}
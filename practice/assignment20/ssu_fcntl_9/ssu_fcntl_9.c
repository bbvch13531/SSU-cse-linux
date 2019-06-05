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

int main(int argc, char **argv){
    struct flock lock;
    struct employee record;
    int fd, sum=0, try=0;

    sleep(10);

    if((fd = open(argv[1], O_RDONLY)) == -1){   // open
        perror(argv[1]);
        exit(1);
    }

    lock.l_type = F_RDLCK;  // read lock
    lock.l_whence = 0;
    lock.l_start = 0l;
    lock.l_len = 0l;
    
    while(fcntl(fd, F_SETLK, &lock) == -1){ // 락 설정
        if(errno == EACCES){
            if(try++ < MAXTRIES){       // 계속 시도
                sleep(1);
                continue;
            }
            printf("%s busy -- try later\n", argv[1]);
            exit(2);
        }
        perror(argv[1]);
        exit(3);
    }
    sum = 0;
    while(read(fd, (char *)&record, sizeof(record)) > 0){   // read
        printf("Employee: %s, Salary: %d\n", record.name, record.salary);
        sum += record.salary;
    }
    printf("\nTotal salary: %d\n", sum);

    lock.l_type = F_UNLCK;  // unlock
    fcntl(fd, F_SETLK, &lock);
    close(fd);
}

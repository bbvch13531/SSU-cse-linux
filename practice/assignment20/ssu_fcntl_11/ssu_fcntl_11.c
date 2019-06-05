#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define NAMESIZE 50

struct employee{
    char name[NAMESIZE];
    int salary;
    int pid;
};

int main(int argc, char **argv){
    struct flock lock;
    struct employee record;
    int fd, recnum, pid;
    long position;

    if((fd = open(argv[1],O_RDWR)) == -1 ){ // open
        perror(argv[1]);
        exit(1);
    }

    pid = getpid();

    for(;;){
        printf("\nEnter record number: ");
        scanf("%d", &recnum);

        if(recnum<0)
            break;

        position = recnum * sizeof(record);
        lock.l_type = F_WRLCK;  //write lock
        lock.l_whence = 0;  // 파일의 일부만 락 설정
        lock.l_start = position;
        lock.l_len = sizeof(record);

        if(fcntl(fd, F_SETLKW, &lock) == -1){   // lock
            perror(argv[1]);
            exit(2);
        }

        lseek(fd, position, 0);

        if(read(fd, (char*)&record, sizeof(record)) == 0){  //read
                printf("record %d not found\n", recnum);
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);
                continue;
        }

        printf("Employee: %s, salary: %d\n", record.name, record.salary);
        record.pid = pid;
        printf("Enter new salary: ");
        scanf("%d", &record.salary);

        lseek(fd, position, 0);
        write(fd, (char *)&record, sizeof(record));

        lock.l_type = F_UNLCK;      // unlock
        fcntl(fd, F_SETLK, &lock);  // lock check
    }
    close(fd);
}







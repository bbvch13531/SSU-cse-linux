#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include "ssu_employee.h"

#define SEC_TO_MICRO 1000000

int main(int argc, char *argv[]){
    struct timeval begin_t, end_t;

    struct ssu_employee record;
    int fd;

    gettimeofday(&begin_t, NULL);
    
    if(argc < 2){
        fprintf(stderr, "Usage : %s filein fileout\n", argv[0]);
        exit(1);
    }

    if((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) < 0){
        fprintf(stderr, "open error for %s\n",argv[1]);
        exit(1);
    }
    
    while(1){
        printf("Enter employee name <SPACE> salary: ");
        scanf("%s",record.name);   

        if(record.name[0] == '.')   // .이 입력되면 break
            break;

        scanf("%d",&record.salary);
        record.pid = getpid();  // pid를 저장
        write(fd, (char *)&record, sizeof(record)); // record를 fd에 저장
    }
    close(fd);
    gettimeofday(&end_t, NULL);

	end_t.tv_sec -= begin_t.tv_sec;
	if(end_t.tv_usec < begin_t.tv_usec){
		end_t.tv_sec--;
		end_t.tv_usec += SEC_TO_MICRO;
	}
	end_t.tv_usec -= begin_t.tv_usec;
	printf("Runtime: %ld:%ld\n",end_t.tv_sec, end_t.tv_usec);
    exit(0);
}
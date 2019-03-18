#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"
#include <sys/time.h>

#define SEC_TO_MICRO 1000000

int main(int argc, char ** argv){
    struct timeval begin_t, end_t;
	struct ssu_employee record;
	int fd;
	int record_num;

    gettimeofday(&begin_t, NULL);
	if(argc < 2){
		fprintf(stderr, "Usage : %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDONLY)) < 0){
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	while(1){
		printf("Enter record number : ");
		scanf("%d", &record_num);

		if(record_num < 0)	// -1 이면 끝
			break;
		
		if(lseek(fd, (long)record_num * sizeof(record), 0) < 0){ // record num * record 크기 만큼 lseek
			fprintf(stderr, "lseek error\n");
			exit(1);
		}

		if(read(fd, (char *)&record, sizeof(record)) > 0){	// 해당하는 record 를 read
			printf("Employee : %s Salary : %d\n", record.name, record.salary);
		}
		else{	// 못찾은 경우
			printf("Record %d not found\n",record_num);
		}
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

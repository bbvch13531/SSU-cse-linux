#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000

struct stat statbuf;
void ssu_checkfile(char *fname, time_t *time);
int main(int argc, char* argv[]){

	struct timeval begin_t, end_t;
    time_t intertime;

    gettimeofday(&begin_t, NULL);
    if(argc != 2){
        fprintf(stderr, "Usage: %s <file>\n",argv[0]);
        exit(1);
    }

    if((stat(argv[1], &statbuf)) < 0){  // argv[1]의 stat정보를 statbuf에 저장
        fprintf(stderr, "stat error\n");
        exit(1);
    }
    intertime = statbuf.st_mtime; // 수정시간을 저장
    while(1){
        ssu_checkfile(argv[1], &intertime); // 수정시간이 달라졌는지 확인
        sleep(10);
    }

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

void ssu_checkfile(char *fname, time_t *time){
    if(stat(fname, &statbuf) < 0){
        fprintf(stderr, "Warning : ssu_checkfile() error!\n");
        exit(1);
    }
    else{
        if(statbuf.st_mtime != *time){
            printf("Warning : %s was modified!\n",fname);
            *time = statbuf.st_mtime;
        }
    }

}
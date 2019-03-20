#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000

int main(int argc, char* argv[]){

	struct timeval begin_t, end_t;
    int i;
    
    gettimeofday(&begin_t, NULL);
    if(argc < 2){
        fprintf(stderr, "Usage: %s <file1> <file2> .. <fileN>\n",argv[0]);
        exit(1);
    }

    for(i=1; i<argc; i++){
        if(access(argv[i], F_OK) < 0){
            fprintf(stderr, "%s doesn't exist\n",argv[i]);
            continue;
        } 

        if(access(argv[i], R_OK) == 0)
            printf("User can read %s\n",argv[i]);
        
        if(access(argv[i], W_OK) == 0)
            printf("User can write %s\n",argv[i]);
        
        if(access(argv[i], X_OK) == 0)
            printf("User can execute %s\n",argv[i]);
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
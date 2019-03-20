#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000
#define TABLE_SIZE (sizeof(table)/sizeof(*table))

int main(int argc, char* argv[]){

	struct timeval begin_t, end_t;
    struct {
        char *text;
        int mode;
    } table[] = {
        {"exists", 0},
        {"execute", 1},
        {"write", 2},
        {"read", 4}
    };
    int i;
    
    gettimeofday(&begin_t, NULL);
    if(argc < 2){
        fprintf(stderr, "Usage: %s <file>\n",argv[0]);
        exit(1);
    }

    for(int i=0; i<TABLE_SIZE; i++){
        if(access(argv[1], table[i].mode) != -1){
            printf("%s -ok\n",table[i].text);            
        }
        else{
            printf("%s\n",table[i].text);
        }
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
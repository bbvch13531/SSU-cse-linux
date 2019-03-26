#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "calTime.h"

#define MODE_EXEC (S_IXUSR | S_IXGRP | S_IXOTH)

int main(int argc, char** argv){
    struct timeval begin_t, end_t;
    struct stat statbuf;

    gettimeofday(&begin_t, NULL);
    
    if(argc < 2){
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n",argv[0]);
        exit(1);
    }
    // stat 구조체
    for(int i = 1; i < argc; i++){
        if(stat(argv[i], &statbuf) < 0){
            fprintf(stderr, "%s : stat error\n",argv[i]);
            continue;
        }
    
        // statbuf bit masking
        statbuf.st_mode |= MODE_EXEC;
        statbuf.st_mode ^= (S_IXGRP | S_IXOTH);
        
        // chmod change
        if(chmod(argv[i], statbuf.st_mode) < 0){
            fprintf(stderr, "%s : chmod error\n",argv[i]);
        }
        else {
            printf("%s : file permission was changed.\n",argv[i]);
        }
    }
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);

    exit(0);
}
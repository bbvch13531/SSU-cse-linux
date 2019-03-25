#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "calTime.h"

#define MODE_EXEC (S_IXUSR | S_IXGRP | S_IXOTH)
int main(void){
    struct timeval begin_t, end_t;
    struct stat statbuf;
    
    char *fname1 = "ssu_file1";
    char *fname2 = "ssu_file2";

    gettimeofday(&begin_t, NULL);

    if(stat(fname1, &statbuf) < 0){
        fprintf(stderr, "stat error %s\n", fname1);
    }
    
    if(chmod(fname1, (statbuf.st_mode & ~S_IXGRP) | S_ISUID)){
        fprintf(stderr, "chmod error %s\n", fname1);
    }

    if(chmod(fname2, S_IRUSR | S_IWUSR | S_IFGRP | S_IROTH | S_IXOTH) < 0){
        fprintf(stderr, "chmod error %s\n",fname2);
    }
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);

    exit(0);
}
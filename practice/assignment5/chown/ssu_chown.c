#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "calTime.h"

int main(void){
    struct timeval begin_t, end_t;
    struct stat statbuf;
    char *fname = "ssu_myfile";
    int fd;

    gettimeofday(&begin_t, NULL);
    
    // open fname
    if((fd = open(fname, O_RDWR | O_CREAT, 0600)) < 0){
        fprintf(stderr, "open error for %s\n",fname);
        exit(1);        
    }
    close(fd);
    stat(fname, &statbuf);  // get statbuf
    printf("# 1st stat call # UID: %d\tGID: %d\n", statbuf.st_uid, statbuf.st_gid);

    // chown change
    if(chown(fname, 501, 300) < 0){
        fprintf(stderr, "chown error for %s\n",fname);
        exit(1);
    }

    stat(fname, &statbuf);  // get statbuf
    printf("# 2nd stat call # UID: %d\tGID: %d\n",statbuf.st_uid, statbuf.st_gid);

    // unlink fname
    if(unlink(fname) < 0){
        fprintf(stderr, "unlink error for %s\n", fname);
        exit(1);
    }

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);

    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utime.h>
#include "calTime.h"

int main(int argc, char * argv[]){
    struct timeval begin_t, end_t;
    struct utimbuf time_buf;
    struct stat statbuf;
    int fd, i;
    gettimeofday(&begin_t, NULL);
    
    for(i = 1; i < argc; i++){
        if(stat(argv[i], &statbuf) < 0){
            fprintf(stderr, "stat error for %s\n",argv[i]);
            continue;
        }

        if((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0){
            fprintf(stderr, "open error for %s\n",argv[i]);
            continue;
        }

        close(fd);
        time_buf.actime = statbuf.st_atime;
        time_buf.modtime = statbuf.st_mtime;

        if(utime(argv[i], &time_buf) < 0){
            fprintf(stderr, "utime error for %s\n",argv[i]);
            continue;
        }
    }
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
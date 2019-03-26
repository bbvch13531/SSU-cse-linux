#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "calTime.h"

int main(int argc, char **argv){
    struct timeval begin_t, end_t;
    char *fname = "ssu_dump.txt";

    gettimeofday(&begin_t, NULL);
    // open fname
    if(open(fname, O_RDWR) < 0){
        fprintf(stderr, "open error for %s\n",fname);
        exit(1);
    }
    // unlink fname
    if(unlink(fname) < 0){
        fprintf(stderr, "unlink error for %s\n",fname);
        exit(1);
    }
    printf("File unlinked\n");
    sleep(20);
    printf("Done\n");

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
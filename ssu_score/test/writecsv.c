// SSU_20142468 Kyungyoung Heo

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    char *fname = "writecsv.csv";
    double a=1.0, b=2.0;
    char buf[10]="1.1.txt";
    char dtoc[10];

    int fd; 
    if((fd = creat(fname, 0644)) < 0){
        fprintf(stderr, "creat error\n");
        exit(1);
    }

    for(int i=0; i<5; i++){
        write(fd, buf, strlen(buf));
        write(fd, ", ", 2);

        snprintf(dtoc, 5, "%3lf", a);
        printf("dtoc = %s\n",dtoc);
        write(fd, dtoc, strlen(dtoc));
        write(fd, "\n", 1);
    }
    exit(0);
}
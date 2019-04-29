#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
    FILE *fp = 0;
    char filename = "q3java.txt";

    // true
    // fp = open(filename, O_RDWR, O_APPEND);

    // flase
    if((fp = open(filename, O_RDWR, O_CREAT)) == -1){
        fprintf(stderr, "open error for %s\n",filename);
        exit(1);
    }

    fwrite(fp, 1, sizeof("2019 OSLAB\n"), "2019 OSLAB\n");
    fwrite(fp, 1, sizeof("Linux System Programming\n"), "Linux System Programming\n");

    fflush(fp);
    printf("DONE\n");

    if(fp != NULL)
        close(fp);
    exit(0);
}
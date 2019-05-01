#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void){
    FILE *fp;
    char filename[50] = "q3java.txt";

    // true
    // fp = fopen(filename, "a");

    // false
    if((fp = fopen(filename, "a")) == NULL){
        fprintf(stderr, "open error for %s\n",filename);
        exit(1);
    }

    fwrite("2019 OSLAB\n", 1, 12, fp);
    fwrite("Linux System Programming\n", 1, 26, fp);

    fflush(fp);
    printf("DONE\n");

    if(fp != NULL)
        fclose(fp);
    exit(0);
}
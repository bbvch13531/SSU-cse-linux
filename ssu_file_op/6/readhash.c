#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void){
    char recordbuf[15];
    int header;
    FILE *fp = fopen("student.hsh", "r+");

    fread(&header, 4, 1, fp);
    printf("N=%d\n",header);
    while(1){
        fread(recordbuf, 14, 1, fp);
        if(feof(fp))
            break;
        printf("%s %d\n", recordbuf, *(recordbuf +10));
    }
    return 0;
}
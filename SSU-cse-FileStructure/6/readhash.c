#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void){
    char recordbuf[15];
    int header,i=0, addr;
    FILE *fp = fopen("student.hsh", "r+");

    fread(&header, 4, 1, fp);
    printf("N=%d\n",header);
    while(1){
        fread(recordbuf, 14, 1, fp);
        if(feof(fp))
            break;
        memcpy(&addr, recordbuf+10, 4);
        recordbuf[10] = '\0';
        printf("%03d %s %d\n",i, recordbuf, addr);
        i++;
    }
    return 0;
}
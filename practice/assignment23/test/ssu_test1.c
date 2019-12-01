#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void){
    FILE *fp;

    fp = fopen("./a.c", "r"); // a.c가 존재한다고 가정
    printf("error = %d\n", errno);
    fclose(fp);
    printf("error = %d\n", errno);

    fp = fopen("./b.c", "r"); // b.c가 존재하지 않는다고 가정
    printf("error = %d\n", errno);
    fclose(fp);
    printf("error = %d\n", errno);

    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void){
    char arr[3]="12";
    printf("%s",arr[-1]);
    return 0;
}
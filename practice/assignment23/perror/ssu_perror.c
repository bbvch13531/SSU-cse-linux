#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void){
    FILE *pFile;

    pFile = fopen("nofile.nofile", "rb");
    
    if(pFile == NULL){
        perror("The following error occurred");
    }
    else{
        fclose(pFile);
    }
    return 0;
}
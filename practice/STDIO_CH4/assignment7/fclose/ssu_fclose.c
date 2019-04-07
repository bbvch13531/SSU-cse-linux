#include <stdio.h>
#include <stdlib.h>

int main(void){
    char *fname = "ssu_test.txt";
    FILE *fp;

    printf("First printf : Hello, OSLAB!!\n");

    if((fp = fopen(fname, "r")) == NULL){
        fprintf(stderr, "open error for %s\n",fname);
        exit(1);
    }
    else{
        printf("Success!\n");
        printf("Opening  \"%s\" in \"r\" mode!\n", fname);
    }
    exit(0);
}
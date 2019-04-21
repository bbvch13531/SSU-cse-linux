#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"
#define BUFFER_SIZE 1024

int main(int argc, char **argv){
    struct timeval begin_t, end_t;
    char *fname = "ssu_test.dat";
    char name[BUFFER_SIZE];
    FILE *fp;
    int age;
    
    gettimeofday(&begin_t, NULL);
    fp = fopen(fname, "r"); 
    fscanf(fp, "%s%d", name, &age); // 파일에서 name, age 받아오기
    fclose(fp);

    fp = fopen(fname, "w");
    fprintf(fp, "%s is %d years old\n", name, age); // 파일에 name, age 출력하기
    fclose(fp);
    
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include "calTime.h"
struct ssu_pirate{
    unsigned long booty;
    unsigned int beard_length;
    char name[128];
};

int main(void){
    struct timeval begin_t, end_t;
    struct ssu_pirate blackbeard = {950, 48, "Edward Teach"}, pirate;
    char *fname = "ssu_data";
    FILE *fp1, *fp2;

    gettimeofday(&begin_t, NULL);
    if((fp2 = fopen(fname, "w")) == NULL){  // 파일 열기
        fprintf(stderr, "fopen error for %s\n",fname);
        exit(1);
    }

    if(fwrite(&blackbeard, sizeof(struct ssu_pirate), 1, fp2) != 1){    // 파일에 blackbeard 쓰기
        fprintf(stderr, "fwrite error fp2\n");
        exit(1);
    }

    if(fclose(fp2)){
        fprintf(stderr, "fclose error\n");
        exit(1);
    }

    if((fp1 = fopen(fname, "r")) == NULL){  // 파일 열기
        fprintf(stderr, "fopen error\n");
        exit(1);
    }

    if(fread(&pirate, sizeof(struct ssu_pirate), 1, fp1) != 1){    // 파일에 pirate 쓰기
        fprintf(stderr, "fwrite error\n");
        exit(1);
    }

    if(fclose(fp1)){
        fprintf(stderr, "fclose error\n");
        exit(1);
    }

    printf("name = \"%s\" booty=%lu beard_length=%u\n",pirate.name, pirate.booty, pirate.beard_length); // 출력해서 확인
    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}

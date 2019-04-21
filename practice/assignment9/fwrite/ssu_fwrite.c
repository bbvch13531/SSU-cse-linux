#include <stdio.h>
#include <stdlib.h>

#include "calTime.h"


struct ssu_id{
    char name[64];
    int id;
};
int main(void){
    struct timeval begin_t, end_t;
    struct ssu_id test1, test2;
    char *fname = "ssu_exam.dat";
    FILE *fp;

    gettimeofday(&begin_t, NULL);
    if((fp = fopen(fname, "w")) == NULL){   // 파일 읽기
        fprintf(stderr, "fopen error for %s\n",fname);
        exit(1);
    }

    printf("Input ID >> ");
    scanf("%d", &test1.id);
    printf("Input name >> ");
    scanf("%s", test1.name);

    if(fwrite(&test1, sizeof(struct ssu_id), 1, fp) != 1){  // 파일에 test1 쓰기
        fprintf(stderr, "fwrite error\n");
        exit(1);
    }

    fclose(fp);

    if((fp = fopen(fname, "r")) == NULL){
        fprintf(stderr, "fopen error for %s\n",fname);
        exit(1);
    }

    if(fread(&test2, sizeof(struct ssu_id), 1, fp) != 1){   // 파일을 읽어서 test2에 저장
        fprintf(stderr, "fread error\n");
        exit(1);
    }
    
    printf("\nID    name\n");
    printf("============\n");
    printf("%d      %s\n", test2.id, test2.name);   // 출력해서 확인

    fclose(fp);

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
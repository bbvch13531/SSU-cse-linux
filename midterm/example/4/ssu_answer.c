#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUF_SIZE 256
#define STD_NUM 3
#define Q_SIZE 10

typedef struct _student{
	char name[10];
	int score;
	char res[BUF_SIZE];
} Student;

char answer[BUF_SIZE] = "1233423413";

int main(void){
	char *ssu_answer = "ssu_answer.txt";
	char *ssu_res = "ssu_res.txt";
	char tmp_score[BUF_SIZE];
	FILE *fp;
	int i, j=0;
	Student list[STD_NUM];

	if((fp = fopen("ssu_answer.txt", "rb")) == NULL){
		fprintf(stderr, "fopen error\n");
		exit(1);
	}

	for(j=0; j<STD_NUM; j++){
		list[j].score = 0;
		if(fgets(list[j].name, BUF_SIZE, fp) == NULL){
			fprintf(stderr, "fgets error\n");
			exit(1);
		}
		i = 0;

		while(list[j].name[i] != '\n')
			i++;
		list[j].name[i] = 0;

		i = 0;
		if(fgets(list[j].res, BUF_SIZE, fp) == NULL){
			fprintf(stderr, "fgets error\n");
			exit(1);
		}
		while(list[j].res[i] != '\n')
			i++;
		list[j].res[i] = 0;
	
		for(i=0; i<Q_SIZE; i++){
			if(list[j].res[i] == answer[i]){
				list[j].score += 10;
				list[j].res[i] = 'O';
			}
			else
				list[j].res[i] = 'X';
		}
		printf("%s %d %s\n", list[j].name, list[j].score, list[j].res);
	}
	fclose(fp);

	if((fp = fopen(ssu_res, "wb")) == NULL){
		fprintf(stderr, "fopen error\n");
		exit(1);
	}

	for(i = 0; i<STD_NUM; i++){
		if(fputs(list[i].name, fp) == NULL){
			fprintf(stderr, "fputs error\n");
			exit(1);
		}

		sprintf(tmp_score, " |%d| ", list[i].score);

		if(fputs(tmp_score, fp) == NULL){
			fprintf(stderr, "fputs error\n");
			exit(1);
		}
		if(fputs(list[i].res, fp) == NULL){
			fprintf(stderr, "fputs error\n");
			exit(1);
		}

	}
	fclose(fp);
	exit(0);
}

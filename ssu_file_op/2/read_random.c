#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include "record.h"
// 필요하면 header file 추가 가능

#define SUFFLE_NUM	10000	// 이 값은 마음대로 수정할 수 있음

void GenRecordSequence(int *list, int n);
void swap(int *a, int *b);

//
// argv[1]: 레코드 파일명
// argv[2]: 레코드 파일에 저장되어 있는 전체 레코드 수
//
int main(int argc, char **argv){
	FILE *fp;
	int *read_order_list;
	int num_of_records;
	int nextOffset;
	char fname[100];
	char id[11], name[31], address[71], univ[31], dept[41], others[71];

	Student student;
	struct timeval begin, end;

	strcpy(fname, argv[1]);
	num_of_records = atoi(argv[2]);
	
	gettimeofday(&begin, NULL);
	fp = fopen(fname, "r+");
	read_order_list = (int *)malloc(sizeof(int) * num_of_records);

	// 이 함수를 실행하면 'read_order_list' 배열에 읽어야 할 레코드 번호들이 순서대로 나열되어 저장됨
	// 'num_of_records'는 레코드 파일에 저장되어 있는 전체 레코드의 수를 의미함
	GenRecordSequence(read_order_list, num_of_records);
	// printf("Gen finished!\n");
	// 'read_order_list'를 이용하여 표준 입력으로 받은 레코드 파일로부터 레코드를 random하게 읽어들이고,
    // 이때 걸리는 시간을 측정하는 코드 구현함

	for(int i=0; i<num_of_records; i++){
		nextOffset = read_order_list[i];
		// printf("offset = %d \n", nextOffset);
		fseek(fp, 256 * nextOffset, SEEK_SET);

		fread(id, 1, 11, fp);
		strcpy(student.id, id);
		// printf("id = %s\n",id);

		fread(name, 1, 31, fp);
		strcpy(student.name, name);
		// printf("name = %s\n",namegi);

		fread(address, 1, 71, fp);
		strcpy(student.address, address);
		// printf("address = %s\n",address);

		fread(univ, 1, 31, fp);
		strcpy(student.univ, univ);
		// printf("univ = %s\n",univ);

		fread(dept, 1, 41, fp);
		strcpy(student.dept, dept);
		// printf("dept = %s\n",dept);

		fread(others, 1, 71, fp);
		strcpy(student.others, others);
		// printf("others = %s\n",others);

		// printf("student = %s %s %s %s %s %s\n",student.id, student.name, student.address, student.univ, student.dept,student.others);
	
	}
	gettimeofday(&end, NULL);
	printf("%ld us", (end.tv_sec*1000 + end.tv_usec) - (begin.tv_sec*1000 + begin.tv_usec));
	
	return 0;
}

void GenRecordSequence(int *list, int n){
	int i, j, k;

	srand((unsigned int)time(0));

	for(i=0; i<n; i++){
		list[i] = i;
	}
	
	for(i=0; i<SUFFLE_NUM; i++){
		j = rand() % n;
		k = rand() % n;
		swap(&list[j], &list[k]);
	}

	return;
}

void swap(int *a, int *b){
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;

	return;
}

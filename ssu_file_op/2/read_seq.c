#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "record.h"
// 필요하면 header file 추가 가능

//
// argv[1]: 레코드 파일명
// argv[2]: 레코드 파일에 저장되어 있는 전체 레코드 수
//
int main(int argc, char **argv)
{
	FILE * fp;
	int num;
	char fname[100], buf[100];
	char id[11], name[31], address[71], univ[31], dept[41], others[71];
	Student student;
	strcpy(fname, argv[1]);
	num = atoi(argv[2]);
	time_t begin, end;
	double seconds;

	fp = fopen(fname, "r");

	begin = time(NULL);
	for(int i=0; i<num; i++){

		fread(id, 1, 11, fp);
		strcpy(student.id, id);
		// printf("id = %s\n",id);

		fread(name, 1, 31, fp);
		strcpy(student.name, name);
		// printf("name = %s\n",name);

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
		
		// fread(buf, 1, 1, fp);
	}
	end = time(NULL);
	seconds = difftime(begin, end);
	printf("%.f us", seconds);
	// 표준입력으로 받은 레코드 파일로부터 전체 레코드를 "순차적"으로 읽어들이고,
	// 이때 걸리는 시간을 측정하는 코드 구현함.
	// 파일 i/o 시간 비용 측정 실험이므로 읽어들인 레코드를 굳이 학생 구조체 
	// 변수에 저장할 필요는 없음.


	return 0;
}

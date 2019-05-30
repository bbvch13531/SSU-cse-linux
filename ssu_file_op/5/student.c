#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "student.h"

#define MAXN 1000010
// 학생 레코드 파일에 레코드를 저장하기 전에 구조체 STUDENT에 저장되어 있는 데이터를 레코드 형태로 만든다.
void pack(char *recordbuf, const STUDENT *s);

// 학생 레코드 파일로부터 레코드를 읽어 온 후 구조체 STUDENT로 변환한다.
void unpack(const char *recordbuf, STUDENT *s);

// 학생 레코드 파일로부터 레코드 번호에 해당하는 레코드를 읽어서 레코드 버퍼에 저장한다.
void readRecord(FILE *fp, char *recordbuf, int rn);

//
// 저장
// 학생 레코드 파일에서 삭제 레코드의 존재 여부를 검사한 후 삭제 레코드가 존재하면 이 공간에
// 새로운 레코드를 저장하면, 만약 삭제 레코드가 존재하지 않거나 조건에 부합하는 삭제 레코드가 존재하지 않으면
// 파일의 맨 마지막에 저장한다.
void add(FILE *fp, const STUDENT *s);

//
// 검색
// 학생 레코드 파일에서 sequential search 기법으로 주어진 학번 키값과 일치하는 레코드를 찾는다.
// 출력은 반드시 주어진 print 함수를 사용한다.
// 검색 레코드가 존재하면 레코드 번호 rn을, 그렇지 않으면 -1을 리턴한다.
int search(FILE *fp, const char *keyval);

//
// 삭제
// 학생 파일에서 주어진 학번 키값과 일치하는 레코드를 찾은 후 해당 레코드를 삭제 처리한다.
void delete(FILE *fp, const char *keyval);

void printRecord(const STUDENT *s, int n);

void read_index_file(void);
void update_index_file();

FILE *idx_fp;
int index_file_table[MAXN];
short record_num, sizeof_record_dat;
int main(int argc, char *argv[]){
	FILE *record_fp;
	int param_opt;
	STUDENT std;
	char findkeyval[12];

	record_fp = fopen(RECORD_FILE_NAME, "rb+");	// 제출시 w+로 수정해야함.
	idx_fp = fopen(INDEX_FILE_NAME, "rb+");

	while((param_opt = getopt(argc, argv, "a:d:s:")) != -1){
		read_index_file();
		switch(param_opt){
			case 'a':
				// printf("a\n");
				strcpy(std.id, argv[2]);
				strcpy(std.name, argv[3]);
				strcpy(std.dept, argv[4]);
				strcpy(std.year, argv[5]);
				strcpy(std.addr, argv[6]);
				strcpy(std.phone, argv[7]);
				strcpy(std.email, argv[8]);

				add(record_fp, &std);
				break;
			case 'd':
				printf("d\n");
				break;
			case 's':
				// printf("s\n");
				strcpy(findkeyval, argv[2]);
				search(record_fp, findkeyval);
				break;
			case  '?':
				printf("usage: %s [option] [field_value1] ...\n", argv[0]); // optopt 사용
			break;
		}
	}
	

	// printf("%s %s %s\n\n", std.id, std.name, std.addr);
	
	// read_index_file();
	return 0;
}

void pack(char *recordbuf, const STUDENT *s){
	char buf[256];
	
	// 필드를 '|'로 구분한다
	sprintf(buf, "%s|%s|%s|%s|%s|%s|%s", s->id, s->name, s->addr, s->year, s->dept, s->phone, s->email);

	strcpy(recordbuf, buf);
}

void unpack(const char *recordbuf, STUDENT *s){
	char buf[256];
	int j=0, nth=0;
	for(int i=0; i<strlen(recordbuf); i++){
		buf[j] = recordbuf[i];
		if(recordbuf[i] == '|'){
			if(nth == 0)	strcpy(s->id, buf);
			else if(nth == 1)	strcpy(s->name, buf);
			else if(nth == 2)	strcpy(s->addr, buf);
			else if(nth == 3)	strcpy(s->year, buf);
			else if(nth == 4)	strcpy(s->dept, buf);
			else if(nth == 5)	strcpy(s->phone, buf);
			else if(nth == 6)	strcpy(s->email, buf);
			j = 0;
		}
	}
}

void readRecord(FILE *fp, char *recordbuf, int rn){

}

void add(FILE *fp, const STUDENT *s){
	// STUDENT를 pack한다.
	// index file을 참조해서 빈 공간을 찾는다.
	// record_fp의 빈 공간에 write한다.
	// index file을 갱신한다.
	int record_size;
	short header = 0;
	char numbuf[5];
	char recordbuf[256], writebuf[5];


	// STUDENT 구조체를 pack
	pack(recordbuf, s);
	// record_size를 계산한다.
	record_size = strlen(recordbuf);
	printf("record size = %d %s\n",record_size, recordbuf);
	// printf("pack beford add : %s\n",recordbuf);

	// fp 를 처음으로 이동
	fseek(fp, 0, SEEK_END);
	// student.dat의 사이즈를 계산한다.
	sizeof_record_dat = ftell(fp);
	printf("sizeof record dat = %d\n",sizeof_record_dat);

	// 레코드 갯수를 1 증가시키고 다시 idx_fp에 write 한다.
	record_num++;
	snprintf(numbuf, 3, "%2d", record_num);
	printf("record num ++ %s\n", numbuf);
	fseek(idx_fp, 0, SEEK_SET);
	fwrite(numbuf, 2, 1, idx_fp);

	// 초기화하는 경우
	if(record_num == 1){
		// record_num 은 1이지만 삭제 레코드가 존재하는 경우 예외 처리.
		header = 0;
		fwrite(&header, 2, 1, fp);

		fwrite(recordbuf, record_size, 1, fp);
		fwrite("0", 2, 1, idx_fp);

		return ;
	}

	// fp 를 처음으로 이동
	fseek(idx_fp, 0, SEEK_SET);
	// 
	short newsize = sizeof_record_dat + record_size;
	snprintf(writebuf, 3, "%2d", sizeof_record_dat + record_size);
	printf("writebuf = %s\n",writebuf);
	fseek(idx_fp, record_num * 2, SEEK_SET);
	fwrite(&newsize, 2, 1, idx_fp);
	// fwrite(writebuf, 2, 1, idx_fp);
	// 레코드 갯수 +1 으로 갱신한다.
	// 레코드 위치에 새로 추가한다.

	fseek(fp, sizeof_record_dat, SEEK_SET);
	fwrite(recordbuf, record_size, 1, fp);
/*
	read_index_file();

	// TODO
	// Add record at deleted space

	// Header

	// Append record to student.dat
*/
}

int search(FILE *fp, const char *keyval){
	// for(int i=0; i<)
}

void delete(FILE *fp, const char *keyval){

}

void printRecord(const STUDENT *s, int n){
	int i;

	for(i=0; i<n; i++){
		printf("%s|%s|%s|%s|%s|%s|%s\n", s[i].id, s[i].name, s[i].dept, s[i].year, s[i].addr, s[i].phone, s[i].email);
	}
}

void read_index_file(void){
	int n, i=0, num=0;
	char buf[5], ch;

	fseek(idx_fp, 0, SEEK_SET);
	
	fread(buf, 2, 1, idx_fp);

	record_num = atoi(buf);

	while((ch = fgetc(idx_fp)) != EOF){
		if(ch == ' '){
			index_file_table[i] = num;
			printf("num = %d\n",num);
			i++;
			num = 0;
		}
		else num = 10 * num + ch - 48;
		printf("ch = %c i = %d\n",ch, i);
	}
	index_file_table[i] = num;
	printf("num = %d\n",num);
}
void update_index_file(){

}
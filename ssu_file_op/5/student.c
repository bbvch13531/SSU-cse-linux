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
int main(int argc, char *argv[]){
	FILE *record_fp;
	int param_opt;
	STUDENT std;

	record_fp = fopen(RECORD_FILE_NAME, "r+");	// 제출시 w+로 수정해야함.
	idx_fp = fopen(INDEX_FILE_NAME, "r+");

	while((param_opt = getopt(argc, argv, "a:d:s:")) != -1){
		switch(param_opt){
			case 'a':
				break;
			case 'd':
				break;
			case 's':
				break;
			case  '?':
				printf("usage: %s [option] [field_value1] ...\n", argv[0]); // optopt 사용
			break;
		}
	}
	strcpy(std.id, "20142468");
	strcpy(std.name, "Kyungyoung Heo");
	strcpy(std.addr, "Seoul");
	strcpy(std.year, "2019");
	strcpy(std.dept, "Computer Science and Engineering");
	strcpy(std.phone, "010-2454-3664");
	strcpy(std.email, "bbvch13531@gmail.com");

	// add(record_fp, &std);
	read_index_file();
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
	int record_num, record_size;
	char numbuf[5];
	char recordbuf[127];

	record_size = sizeof(s);
	pack(recordbuf, s);

	printf("pack beford add : %s\n",recordbuf);

	fseek(idx_fp, 0, SEEK_SET);
	fread(numbuf, 2, 1, idx_fp);

	record_num = atoi(numbuf);
	printf("record num = %d\n", record_num);

	read_index_file();
	// index file의 첫 2바이트에서 레코드 갯수를 읽어온다.
	// 레코드 갯수 +1 으로 갱신한다.
	// 레코드 위치에 새로 추가한다. 

	// TODO
	// Add record at deleted space

	// Header
	recordbuf
	// Append record to student.dat

}

int search(FILE *fp, const char *keyval){

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

	n = atoi(buf);

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
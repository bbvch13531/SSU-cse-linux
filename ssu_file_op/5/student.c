#include <stdio.h>
#include <unistd.h>
#include "student.h"

//
// 학생 레코드 파일에 레코드를 저장하기 전에 구조체 STUDENT에 저장되어 있는 데이터를 레코드 형태로 만든다.
// 
void pack(char *recordbuf, const STUDENT *s);


// 
// 학생 레코드 파일로부터 레코드를 읽어 온 후 구조체 STUDENT로 변환한다.
//
void unpack(const char *recordbuf, STUDENT *s);

//
// 학생 레코드 파일로부터 레코드 번호에 해당하는 레코드를 읽어서 레코드 버퍼에 저장한다.
//
void readRecord(FILE *fp, char *recordbuf, int rn);

//
// 저장
// 학생 레코드 파일에서 삭제 레코드의 존재 여부를 검사한 후 삭제 레코드가 존재하면 이 공간에
// 새로운 레코드를 저장하면, 만약 삭제 레코드가 존재하지 않거나 조건에 부합하는 삭제 레코드가 존재하지 않으면
// 파일의 맨 마지막에 저장한다.
//
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


int main(int argc, char *argv[]){
	FILE *record_fp, *idx_fp;  // �л� ���ڵ� ������ ���� ������
	int param_opt;
	STUDENT std;

	record_fp = fopen("RECORD_FILE_NAME", "w+");
	idx_fp = fopen("INDEX_FILE_NAME", "w+");

	while((param_opt = getopt(argc, argv, "a:d:s:")) != -1){
		switch(param_opt){
			case 'a':
				break;
			case 'd':
				break;
			case 's':
				break;
			case  '?':
				printf("usage: \n"); // optopt 사용
			break;
		}
	}

	return 0;
}

void pack(char *recordbuf, const STUDENT *s){

}

void unpack(const char *recordbuf, STUDENT *s){

}

void readRecord(FILE *fp, char *recordbuf, int rn){

}

void add(FILE *fp, const STUDENT *s){
	// STUDENT를 pack한다.
	// index file을 참조해서 빈 공간을 찾는다.
	// record_fp의 빈 공간에 write한다.
	// index file을 갱신한다.
	
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

#include <stdio.h>
#include <unistd.h>
#include "student.h"

//
// �л� ���ڵ� ���Ͽ� ���ڵ带 �����ϱ� ���� ����ü STUDENT�� ����Ǿ� �ִ� �����͸� ���ڵ� ���·� �����.
// 
void pack(char *recordbuf, const STUDENT *s);


// 
// �л� ���ڵ� ���Ϸκ��� ���ڵ带 �о� �� �� ����ü STUDENT�� ��ȯ�Ѵ�.
//
void unpack(const char *recordbuf, STUDENT *s);

//
// �л� ���ڵ� ���Ϸκ���  ���ڵ� ��ȣ�� �ش��ϴ� ���ڵ带 �о ���ڵ� ���ۿ� �����Ѵ�.
//
void readRecord(FILE *fp, char *recordbuf, int rn);

//
//�˰�����: ����
//�л� ���ڵ� ���Ͽ��� ���� ���ڵ��� ���� ���θ� �˻��� �� ���� ���ڵ尡 �����ϸ� �� ������
//���ο� ���ڵ带 �����ϸ�, ���� ���� ���ڵ尡 �������� �ʰų� ���ǿ� �����ϴ� ���� ���ڵ尡
//�������� ������  ������ �Ǹ������� �����Ѵ�.
//
void add(FILE *fp, const STUDENT *s);

//
//�˰�����: �˻�
//�л� ���ڵ� ���Ͽ��� sequential search ������� �־��� �й� Ű���� ��ġ�ϴ� ���ڵ带 ã�´�.
//����� ����� �־��� print �Լ��� ����Ѵ�.
//�˻� ���ڵ尡 �����ϸ� ���ڵ� ��ȣ rn��, �׷��� ������ -1�� �����Ѵ�.
//
int search(FILE *fp, const char *keyval);

//
//�˰�����: ����
//�л� ���Ͽ��� �־��� �й� Ű���� ��ġ�ϴ� ���ڵ带 ã�� �� �ش� ���ڵ带 ���� ó���Ѵ�.
//
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "student.h"

#define HEADER_SIZE 2
// 학생 레코드 파일에 레코드를 저장하기 전에 구조체 STUDENT에 저장되어 있는 데이터를 레코드 형태로 만든다.
void pack(char *recordbuf, const STUDENT *s);

// 학생 레코드 파일로부터 레코드를 읽어 온 후 구조체 STUDENT로 변환한다.
void unpack(const char *recordbuf, STUDENT *s);

// 학생 레코드 파일로부터 레코드 번호에 해당하는 레코드를 읽어서 레코드 버퍼에 저장한다.
void readRecord(char *recordbuf, int rn);

//
// 저장
// 학생 레코드 파일에서 삭제 레코드의 존재 여부를 검사한 후 삭제 레코드가 존재하면 이 공간에
// 새로운 레코드를 저장하면, 만약 삭제 레코드가 존재하지 않거나 조건에 부합하는 삭제 레코드가 존재하지 않으면
// 파일의 맨 마지막에 저장한다.
void add(const STUDENT *s);

//
// 검색
// 학생 레코드 파일에서 sequential search 기법으로 주어진 학번 키값과 일치하는 레코드를 찾는다.
// 출력은 반드시 주어진 print 함수를 사용한다.
// 검색 레코드가 존재하면 레코드 번호 rn을, 그렇지 않으면 -1을 리턴한다.
int search(const char *keyval);

//
// 삭제
// 학생 파일에서 주어진 학번 키값과 일치하는 레코드를 찾은 후 해당 레코드를 삭제 처리한다.
void delete(const char *keyval);

void printRecord(const STUDENT *s, int n);

void read_index_file(void);
void update_index_file();

FILE *idx_fp, *record_fp;
short record_num=0, sizeof_record_dat;
int main(int argc, char *argv[]){
	int param_opt;
	STUDENT std;
	char findkeyval[12];

	if((idx_fp = fopen(INDEX_FILE_NAME, "r+b")) == NULL){
		idx_fp = fopen(INDEX_FILE_NAME, "w+b");
	}
	if((record_fp = fopen(RECORD_FILE_NAME, "r+b")) == NULL){
		record_fp = fopen(RECORD_FILE_NAME, "w+b");
	}

    while((param_opt = getopt(argc, argv, "a:d:s:")) != -1){
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

				add(&std);
				break;
			case 'd':
				// printf("d\n");
				strcpy(findkeyval, argv[2]);
                delete(findkeyval);
				break;
			case 's':
				// printf("s\n");
				strcpy(findkeyval, argv[2]);
				search(findkeyval);
				break;
			case  '?':
				printf("usage: %s [option] [field_value1] ...\n", argv[0]); // optopt 사용
			break;
		}
	}
	fclose(record_fp);
	fclose(idx_fp);
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
		buf[j++] = recordbuf[i];
		if(recordbuf[i] == '|'){
            buf[j-1] = 0;
			if(nth == 0)	strcpy(s->id, buf);
			else if(nth == 1)	strcpy(s->name, buf);
			else if(nth == 2)	strcpy(s->dept, buf);
			else if(nth == 3)	strcpy(s->year, buf);
			else if(nth == 4)	strcpy(s->addr, buf);
			else if(nth == 5)	strcpy(s->phone, buf);
			else if(nth == 6)	strcpy(s->email, buf);
			j = 0;
            nth++;
		}
	}
    // printf("unpack : recordbuf=%s s.id=%s\n\n", recordbuf, s->id);
}


void readRecord(char *recordbuf, int rn){
	short recordaddr=0, nextaddr=0;
    int sizeof_record;
    char ch, readbuf[MAX_RECORD_SIZE+1];

    // rn번째 record의 주소를 recordaddr에 저장, 다음 레코드의 주소를 nextaddr에 저장
    fseek(idx_fp, 2 + (rn) * 2, SEEK_SET);
    fread(&recordaddr, sizeof(short), 1, idx_fp);
    fread(&nextaddr, sizeof(short), 1, idx_fp);

    // 현재 레코드의 크기 계산
    if(nextaddr == 0)
        sizeof_record = recordaddr;
    else
        sizeof_record = nextaddr - recordaddr;
    // printf("recordaddr %d next %d  size %d\n", recordaddr, nextaddr, sizeof_record);
    // recordaddr주소로 이동 후 한 글자를 읽는다.
    fseek(record_fp, 2 + recordaddr, SEEK_SET);
    fread(&ch, 1, 1, record_fp);

    if(ch == '*')
        return ;
    
    // 레코드의 크기만큼 읽는다.
    if(recordaddr == 0){
        fseek(record_fp, 2 + recordaddr, SEEK_SET);    
    }
    else
        fseek(record_fp, recordaddr, SEEK_SET);
    fread(recordbuf, sizeof_record, 1, record_fp);
    // printf("recordaddr : %d, readrecord : %s\n", recordaddr, recordbuf);
}

void printRecord(const STUDENT *s, int n){
	int i;
    // printf("printRecord : ");
	for(i=0; i<n; i++){
		printf("%s|%s|%s|%s|%s|%s|%s\n", s[i].id, s[i].name, s[i].dept, s[i].year, s[i].addr, s[i].phone, s[i].email);
	}
}

void add(const STUDENT *s){
    int record_size, last_addr;
    short header;

	char recordbuf[MAX_RECORD_SIZE + 1], numbuf[5];

    // 
	pack(recordbuf, s);
    record_size = strlen(recordbuf);
	// printf("record size = %d %s\n",record_size, recordbuf);
	

	fseek(idx_fp, 0, SEEK_SET);
	fread(&record_num, 2, 1, idx_fp);

    // printf("record num = %hd\n",record_num);
	// 레코드 갯수를 1 증가시키고 다시 idx_fp에 write 한다.
    record_num++;
    // printf("record++ num = %hd\n",record_num);
    fseek(idx_fp, 0, SEEK_SET);
    fwrite(&record_num, sizeof(record_num), 1, idx_fp);

    // 초기화하는 경우
    if(record_num == 1){
		// record_num 은 1이지만 삭제 레코드가 존재하는 경우 예외 처리.
		header = 0;
		fwrite(&header, 2, 1, record_fp);

		fwrite(recordbuf, record_size, 1,record_fp);
        short tmp = 0;
        fseek(idx_fp, 0, SEEK_END);
		fwrite(&tmp, 2, 1, idx_fp);

		return ;
    }

    // 새로 추가할 레코드의 시작주소를 last_addr에 저장
	fseek(record_fp, 0, SEEK_END);
	last_addr = ftell(record_fp);
    // printf("last addr = %d\n",last_addr);

	// fseek(idx_fp, 0, SEEK_SET);
    
    fseek(idx_fp, 0, SEEK_END);
    fwrite(&last_addr, sizeof(short), 1, idx_fp);


	fseek(record_fp, last_addr, SEEK_SET);
	fwrite(recordbuf, record_size, 1, record_fp);
}

int search(const char *keyval){
    STUDENT std;
    
    char readid[15], recordbuf[MAX_RECORD_SIZE+1];

    // 반복문 돌면서
    // record_fp에서 id를 읽는다.
    // 삭제된 레코드는 제외
    // id와 keyval을 비교해서
    // readRecord를 호출하고
    // printRecord로 실행
    fseek(idx_fp, 0, SEEK_SET);
	fread(&record_num, 2, 1, idx_fp);
    for(int i=0; i<record_num; i++){

        readRecord(recordbuf, i);
        unpack(recordbuf, &std);
        sprintf(readid, "%s", std.id);
        // printf("keyval = %s, readid = %s\n", keyval, readid);
        if(strcmp(readid, keyval) == 0 ){
            printRecord(&std, 1);
            break;
        }
    }
	return 0;
}

void delete(const char *keyval){
}

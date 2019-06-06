#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "student.h"

#define RECORD_SIZE 120
#define HASH_SIZE 14

int N;
FILE *hfp, *rfp;

/*
void pack(char *recordbuf, const STUDENT *s){
	char buf[256];
	
	// 필드를 '|'로 구분한다
	sprintf(buf, "%s%s%s%s%s%s%s", s->id, s->name, s->addr, s->year, s->dept, s->phone, s->email);

	strcpy(recordbuf, buf);
	printf("pack : recordbuf=%s\n\n",recordbuf);
}

void unpack(const char *recordbuf, STUDENT *s){
	char buf[256];
	strncpy(s->id, recordbuf, 10);
	strncpy(s->name, recordbuf+10, 20);
	strncpy(s->addr, recordbuf+30, 30);
	strncpy(s->year, recordbuf+60, 1);
	strncpy(s->dept, recordbuf+61, 19);
	strncpy(s->phone, recordbuf+80, 15);
	strncpy(s->email, recordbuf+95, 25);
    printf("unpack : recordbuf=%s s.id=%s\n\n", recordbuf, s->id);
}
*/

//
// 학생 레코드 파일로부터 레코드 번호에 해당하는 레코드를 읽어 레코드버퍼에 저장한다.
//
void readStudentRec(FILE *fp, char *recordbuf, int rn){
	fseek(fp, rn * 120, SEEK_SET);
	fread(recordbuf, 120, 1, fp);
}

//
// Hash file로부터 rn의 레코드 번호에 해당하는 레코드를 읽어 레코드 버퍼에 저장한다.
//
void readHashRec(FILE *fp, char *recordbuf, int rn){
	fseek(fp, rn*14, SEEK_SET);
	fread(recordbuf, 14, 1, fp);
}

//
// Hash file로부터 rn의 레코드 번호에 해당하는 위치에 레코드 버퍼의 레코드를 저장한다.
//
void writeHashRec(FILE *fp, const char *recordbuf, int rn){
	char checkbuf[30];
	
	fseek(fp, rn * HASH_SIZE + 4, SEEK_SET);
	printf("-------------------\nwriteHashRec\n");
	for(int i=0; i<N; i++){
		memset(checkbuf, 0, 30);
		fread(checkbuf, 10, 1, fp);
		checkbuf[10] = '\0';
		// printf("%s %ld\n", checkbuf, ftell(fp));
		// key번째 hash file을 읽고 collision을 확인
		// 이미 데이터가 있는 경우
		if(strlen(checkbuf) == 0 || checkbuf[0] == '*' ){
			break;
		}
		rn += 1;
		if(rn == N)
			rn = 0;
		fseek(fp, rn * HASH_SIZE + 4, SEEK_SET);
	}

	fseek(fp, rn * HASH_SIZE + 4, SEEK_SET);
	printf("write %s %d to %d\n", recordbuf, *(recordbuf+10), ftell(fp));
	fwrite(recordbuf, HASH_SIZE, 1, fp);
}

//
// n의 크기를 갖는 hash file에서 주어진 학번 키값을 hashing하여 주소값(레코드 번호)를 리턴한다.
//
int hashFunction(const char *sid, int n){
	int hashnum, len;

	len = strlen(sid);
	hashnum = (sid[len-1] * sid[len-2]) % N;
	printf("--------------------\nhashFunction\nA=%d(%c), B=%d(%c), hashnum=%d\n",sid[len-1], sid[len-1], sid[len-2], sid[len-2], hashnum);
	return hashnum;
}

void openHash(void){
	hfp = fopen("student.hsh", "r+");
	fread(&N, 4, 1, hfp);
	printf("------------------\nopenHash\nN=%d\n", N);
}

//
// n의 크기를 갖는 hash file을 생성한다.
// Hash file은 fixed length record 방식으로 저장되며, 레코드의 크기는 14바이트이다. 
// (student.h 참조)
//
void makeHashfile(int n){
	// Hash file을 생성할 때 이 파일의 맨 앞부분에 4바이트 헤더를 둔다.
	// 여기에는 hash file의 크기 n을 저장한다. 이것은 search()와 (필요하면) delete()를 위한 것이다.
	STUDENT std;
	char idbuf[30], namebuf[50];
	char recordbuf[130], hashbuf[30];
	int cnt=0, key;
	printf("--------------------\nmakeHashFile\n");
	hfp = fopen("student.hsh", "w+");
	fwrite(&n, 4, 1, hfp);
	
	while(!feof(rfp)){
		// fseek(rfp, cnt * RECORD_SIZE, SEEK_SET);
		fread(recordbuf, 120, 1, rfp);
		if(feof(rfp))
			break;
		// strncpy(idbuf, recordbuf, 10);
		memcpy(idbuf, recordbuf, 10);

		idbuf[10] = '\0';
		key = hashFunction(idbuf, n); 
		// sprintf(hashbuf, "%s%d", idbuf, key);
		memcpy(hashbuf, idbuf, 10);
		memcpy(hashbuf+10, (void*)&key, 4);

		writeHashRec(hfp, hashbuf, key);

		cnt++;
		printf("idbuf=%s, cnt=%d, hashbuf=%s %d\n",idbuf, cnt, hashbuf, *(hashbuf+10));
	}
}

//
// 주어진 학번 키값을 hash file에서 검색한다.
// 그 결과는 주어진 학번 키값이 존재하는 hash file에서의 주소(레코드 번호)와 search length이다.
// 검색한 hashfile에서의 주소는 rn에 저장하며, 이때 hash file에 주어진 학번 키값이
// 존재하지 않으면 rn에 -1을 저장한다. (search()는 delete()에서도 활용할 수 있음)
// search length는 함수의 리턴값이며,  상관없이 search length는 항상 계산되어야 한다.
//
int search(const char *sid, int *rn){
	int search_length = 0, key;
	char readbuf[30], sidbuf[15];
	printf("--------------------\nsearch func\n");

	key = hashFunction(sid, N);

	while(!feof(hfp)){
		fseek(hfp, key * 14+4, SEEK_SET);
		fread(readbuf, 14, 1, hfp);
		strncpy(sidbuf, readbuf, 10);
		
		sidbuf[10] = '\0';
		// 비어있는 레코드. 검색 실패
		if(strcmp(sidbuf, "") == 0){
			*rn = -1;
			break;
		}
		if(strcmp(sid, sidbuf) == 0){
			*rn = key;
			break;
		}

		search_length++;
		key++;
		if(key == N)
			key = 0;
	}

	return search_length;
}

//
// Hash file에 주어진 학번 키값과 일치하는 레코드를 찾은 후 해당 레코드를 삭제 처리한다.
// 이때 학생 레코드 파일에서 레코드 삭제는 필요하지 않다.
//
void delete(const char *sid){
	int key, rn;
	char readbuf[30], sidbuf[15];
	char tombstone[15] = "*";
	
	search(sid, &rn);
	printf("------------------------\ndelete\nrn = %d\n",rn);
	if(rn != -1){
		fseek(hfp, (rn * 14)+4, SEEK_SET);
		fwrite(tombstone, 1, 1, hfp);
	}
}

//
// rn은 hash file에서의 레코드 번호를, sl은 search length를 의미한다.
//
void printSearchResult(int rn, int sl){
	printf("%d %d\n", rn, sl);
}

int main(int argc, char *argv[]){
	// 학생 레코드 파일은 student.h에 정의되어 있는 STUDENT_FILE_NAME을,
	// hash file은 HASH_FILE_NAME을 사용한다.
	// N 을 인자로 받아서 사용한다.
	// 검색 기능을 수행할 때 출력은 반드시 주어진 printSearchResult() 함수를 사용한다.

	int param_opt, rn, search_length=0;
	char sid[15], hashbuf[20], recordbuf[130];

	if(argc != 3){
		printf("Usage: a.out [option] [hash_table_size] or [sid]\n");
		exit(0);
	}

	if(access("student.dat", F_OK) != 0){
		rfp = fopen("student.dat", "r+");
	}
	rfp = fopen("student.dat", "r+");

	while((param_opt = getopt(argc, argv, "c:s:d:")) != -1){
		switch(param_opt){
			case 'c':
				N = atoi(argv[2]);
				makeHashfile(N);

				break;

			case 's':
				strcpy(sid, argv[2]);
				openHash();
				printf("search %s\n",sid);
				search_length = search(sid, &rn);
				// printf("record num = %d, search_length = %d\n", rn, search_length);
				printSearchResult(rn, search_length);
				break;

			case 'd':
				strcpy(sid, argv[2]);
				openHash();
				delete(sid);

				break;
		}
	}
	return 0;
}

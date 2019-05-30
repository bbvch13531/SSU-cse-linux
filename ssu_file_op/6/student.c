#include <stdio.h>
#include "student.h"

//
// 학생 레코드 파일로부터 레코드 번호에 해당하는 레코드를 읽어 레코드버퍼에 저장한다.
//
void readStudentRec(FILE *fp, char *recordbuf, int rn)
{
}

//
// Hash file로부터 rn의 레코드 번호에 해당하는 레코드를 읽어 레코드 버퍼에 저장한다.
//
void readHashRec(FILE *fp, char *recordbuf, int rn)
{
}

//
// Hash file로부터 rn의 레코드 번호에 해당하는 위치에 레코드 버퍼의 레코드를 저장한다.
//
void writeHashRec(FILE *fp, const char *recordbuf, int rn)
{
}

//
// n의 크기를 갖는 hash file에서 주어진 학번 키값을 hashing하여 주소값(레코드 번호)를 리턴한다.
//
int hashFunction(const char *sid, int n)
{
}

//
// n의 크기를 갖는 hash file을 생성한다.
// Hash file은 fixed length record 방식으로 저장되며, 레코드의 크기는 14바이트이다. 
// (student.h 참조)
//
void makeHashfile(int n)
{
	// Hash file을 생성할 때 이 파일의 맨 앞부분에 4바이트 헤더를 둔다.
	// 여기에는 hash file의 크기 n을 저장한다. 이것은 search()와 (필요하면) delete()를 위한 것이다.
}

//
// 주어진 학번 키값을 hash file에서 검색한다.
// 그 결과는 주어진 학번 키값이 존재하는 hash file에서의 주소(레코드 번호)와 search length이다.
// 검색한 hashfile에서의 주소는 rn에 저장하며, 이때 hash file에 주어진 학번 키값이
// 존재하지 않으면 rn에 -1을 저장한다. (search()는 delete()에서도 활용할 수 있음)
// search length는 함수의 리턴값이며,  상관없이 search length는 항상 계산되어야 한다.
//
int search(const char *sid, int &rn)
{
}

//
// Hash file에 주어진 학번 키값과 일치하는 레코드를 찾은 후 해당 레코드를 삭제 처리한다.
// 이때 학생 레코드 파일에서 레코드 삭제는 필요하지 않다.
//
void delete(const char *sid)
{
}

//
// rn은 hash file에서의 레코드 번호를, sl은 search length를 의미한다.
//
void printSearchResult(int rn, int sl)
{
	printf("%d %d\n", rn, sl);
}

int main(int argc, char *argv[])
{
	// 학생 레코드 파일은 student.h에 정의되어 있는 STUDENT_FILE_NAME을,
	// hash file은 HASH_FILE_NAME을 사용한다.

	// 검색 기능을 수행할 때 출력은 반드시 주어진 printSearchResult() 함수를 사용한다.
}

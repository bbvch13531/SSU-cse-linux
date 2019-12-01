# ssu_convert
설계과제 2 개요 : Soongsil Converter
Linux System Programming, School of CSE, Soongsil University, Spring 2019
◯ 개요
- Java 언어 프로그램을 C 언어 프로그램으로 자동 변환
◯ 목표
- 유닉스/리눅스 시스템에서 제공하는 여러 함수를 사용하여 텍스트 파일에서 읽어 들인 문자열을 비
교하고 그에 상응하는 문자열을 별도의 파일에 작성함으로써 시스템 프로그래밍 설계 및 응용 능력
을 향상
◯ 팀 구성
- 개인별 프로젝트
◯ 개발환경
- OS : Ubuntu 16.04
- Tools : vi(m), gcc, gdb
◯ 보고서 제출 방법
- 설계과제는 ” 보고서 .hwp“(개요 , 상세설계, 구현방법, 결과 및 소스코드와 실행결과가 함께 있는 워
드(hwp 또는 MS-Word) 파일 )와 ”소스코드 “ (makefile, obj, *.c, *.h 등 컴파일하고 실행하기 위한
모든
- 모든

파일 )를 제출해야 함
설계과제

결과물은

“#P 설계과제번호_ 학번_ 버전 .zip”(예 . #P2_20160000_v1.0.zip)형태로

파일

이름을 명명하고, zip프로그램으로 압축하여 제출해야 함 .
- 압축파일 내 “보고서” 디렉토리와 “소스코드 ” 디렉토리 2개 만들어 제출해야 함
- 제출한 압축 파일을 풀었을 때 해당 디렉토리에서 컴파일 및 실행이 되어야 함. 해당 디렉토리에서
컴파일이나 실행되지 않을 경우 , 기본과제 및 설계과제 제출 방법을 따르지 않는 경우 감점 20% 외
추가 20% 감점
- 기타 내용은 syllabus

참고

◯ 제출 기한
- 5 월 1일 (월) 오후 11 시 59 분 59초 (서버 시간이 30 분 정도 빠를 수 있기 때문에 1 시간 지연 허용)
◯ 보고서 양식
- 보고서는 다음과 같은 양식으로 작성
1. 과제 개요 // 위 개요를 더 상세하게 작성
2. 설계 // 함수 기능별 흐름도 (순서도 ) 반드시 포함
3. 구현 // 함수 프로토타입 반드시 포함
4. 테스트 및 결과 // 테스트 프로그램의 실행 결과 캡쳐 및 분석
5. 소스코드 // 주석

◯ Ubuntu 16.04 에서 Java 설치 및 실행
- openjdk7 설치

- 1 -

$ sudo add-apt-repository ppa:openjdk-r/ppa
$ sudo apt-get update
$ sudo apt-get install openjdk-7-jdk
$ java – version
실행 예시 <java 버전 확인>

- Java 환경변수 지정
$ sudo vi /etc/enviro nment
JAVA_HOME = “/usr/lib/jvm/java-7-openjdk-amd64”
**** Pat h 확인 후 위와 같이 environment에 추가 ****
$ source /etc/environment
$ echo $JAVA_HOME
실행 예시 <java 환경 변수 지정 확인>

- Java 소스 파일 생성 및 실행
SSU_example.java
class SSU_example{
public static void main(String[] args){
System.o ut.printf("Hello, Java in Ubuntu\n");
}
}
실행 예시 <java 소스 생성 및 컴파일 과정>

◯ 설계 및 구현
- ssu_convert <FILENA ME> [OPTION]
1) <FILENAME> : 변환할 JAVA 언어로 작성된 프로그램 파일명. 절대경로와 상대경로 모두 입력 가능
해야함. 존재하지 않는 파일을 대상으로 할 경우 예외처리
- ssu_convert 는 다음과 같은 Java 프로그램 파일을 C 언어 프로그램으로 변환시킬 수 있어야 함
! q1.java – 짝수 및 홀수 합 구하는 프로그램
"

표준 입출력 함수
- 2 -

"

If-else(if)-else 문

"

for 문

! q2.java – Stack 구현 프로그램
"

q1.java 에서 사용된 기능 포함

"

함수 호출

"

전처리기

! q3.java - *.txt 파일 생성 프로그램
"

q1.java, q2.java 에서 사용된 기능 포함

"

파일 입출력

"

java 프고르매 파일에서 IOException은 C 언어 프로그램에서 파일이 존재하지 않는 예외인 경
우만 처리

- header 자동 생성 (개발자가 미리 만든 참조 헤더 테이블 이용 )
예시 < 변환 시 참조되는 헤더 테이블>
open #include <sys/types.h> #include <sys/stat.h> #include <fcntl.h>
read #include <unistd.h>
exit #include <stdlib.h>
! ssu_convert는 Java 언어 프로그램을 C

언어 프로그램으로 변환 시 개발자가 만든 (헤더 테이블

은 자동으로 생성하지 않고 별도로 참조되는 테이블로 만들어야 함 ) 헤더 테이블을 참조하며 프
로그램에서 필요한 헤더는 자동으로 생성해야 함
! header는 위 형식을 그대로 지키되 개발자가 필요한 함수들과 헤더를 자유롭게 추가 및 삭제 가
능
- makefile 자동 생성
변환할 java 프로그램 파일
q1.java

q2.java

q3.java

변환된 C 프로그램 파일

public class q1

q1.c

class Stack

Stack.c

public class q2

q2.c

public class q3

q3.c

실행 예시 <ssu_convert 수행 결과 파일>

! 변환된 C 언어 프로그램 파일을 컴파일 할 수 있는 ‘ 파일명 _Makefile’도 함께 생성되어야 함
! java 언어 프로그램에서 사용되는 표준출력함수는 ‘System.out.printf(“format-string”[, arg1, arg2,
...]);’ 만 허용하며 표준출력함수는 C 언어 프로그램에서 printf로 변경되어야 함
! Java

언어

프로그램에서

사용되는

표준
- 3 -

입력

함수는

‘Scanner

변수이름

=

new

Scanner(System.in)’ ‘변수이름.nextInt’만 허용하며 표준출력함수는 C 언어 프로그램에서 scanf 로
변경되어야 함
! Java 언어 프로그램에서 사용되는 syntax가 C 언어 프로그램에서 사용되지 않으면 무시
예시 <C 언어에서 제공되지 않는 Java 프로그램 코드>
impo rt java.util.Scanner;
Scanner scn = new Scanner(System.in);

- 옵션 [OPTION]
! 옵션이 없는 경우
실행 예. 옵션 없는 경우

! -j 옵션 : 변환할 Java 언어 프로그램 코드 출력
실행 예. –j 옵션

- 4 -

! -c 옵션 : 변환된 C 언어 프로그램 출력
실행 예. –c 옵션

! -p : Java 언어 프로그램에서 사용된 함수들을 C 언어 프로그램에서 대응되는 함수와 함께 출력
실행 예. – p 옵션

! -f 옵션 : Java 언어 프로그램 파일 및 C 언어 프로그램 파일의 파일 크기 출력
실행 예. –f 옵션

- 5 -

! -l 옵션 : Java 언어 프로그램 파일 및 C 언어 프로그램 파일의 라인 수 출력
실행 예. –l 옵션

! -r 옵션 : 자식 프로세스를 생성하여 Java 언어 프로그램이 변환되는 과정을 한 줄 한줄 출력.
단, Java 언어 프로그램의 매 statement 가 C 언어 프로그램으로 변환되어 출력되고 터미널 화면
이 clea r 되고 다시 다음 statement 변환 및 출력. 단 , clear 는 system 함수 사용 가능
! 변환이 완료되면 ‘파일명.c converting is finished!’ 출력
실행 예. –r 옵션

- 기타
! 모든 옵션은 동시에 사용 가능해야 함 . 단 여러 개의 옵션을 함께 사용할 때는 –r 옵션이 가장
먼저 출력되어야 함
실행 예. 여러 옵션을 동시에 사용할 경우

! 존재하지 않는 파일 또는 옵션 사용 시 에러 처리
! clear를 제외하고 system()함수 사용 금지
! 게시판을 통해 변환되어야 하는 Java 언어 프로그램 이용

- 6 -

< 참고> 과제 구현에 필요한 함수(필수 사용 아님)
1. fork() : 리눅스 시스템에서 새로운 프로세스를 생성할 때 사용하는 함수 p.233
#include <unistd.h>
pid_t fork(void);
리턴값 : 자식 프로세스의 경우 0, 부모 프로세스의 경우 자식의 프로세스 ID,
오류 시 – 1을 리턴하고 errno가 설정됨
fork_getpid_example.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int..main(void)
{
int pid;
pid = fo rk();
if (pid > 0) {
printf(“Parent : %d -> fork() -> : %d\n”, getpid(), pid);
sleep(1);
}
else if (pid == 0)
printf(“Child : %d\n”, getpid());
else if (pid == -1) {
perror(“fo rk error : ”);
exit(0);
}
exit(0);
}
실행결과
oslab@o slab-lo calhost:~$ ./fo rk_getpid_example
Parent : 10220 -> fork() -> 10221
Child : 10221
2. gettimeofday() : p.519
3. strstr() : 문자열에서 부분 문자열의 위치를 찾는 함수
#include <string.h>
char *strst r(const char * str1, char const * str2);
리턴값 : 찾고자 하는 문자열이 발견된 첫번째 위치의 포인터를 반환합니다. 찾지 못하면 NULL을 반환
strstr_example.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main( void)
{

- 7 -

char *str = "Linux System Programming";
printf("%s\n", strstr(str, "Linux"));
exit(0);
}
실행결과
oslab@o slab-lo calhost:~$ ./strstr_example
Linux System Programming
4. system() : p.270
#include <stdlib.h>
int system(const char* string);
리턴값 : 성공시 0 이 아닌 값, 실패시 0
5. fopen() : 파일을 오픈하여 파일과 관련된 스트림을 생성하고 버퍼를 할당 p.160
#include <stdio.h>
FILE *fopen(const char * pathname, const char * mode);
리턴값: 성공 시 파일 포인터, 에러 시 NULL을 리턴하고 errno가 설정됨
ssu_test.txt
Linux System Programming!
Unix System Programming!
Linux Mania
Unix Mania
fopen_example.c
#include <stdio.h>
#include <stdlib.h>
int..main(void)
{
char* fname = “ssu_test.txt ”;
char *mode = “r”;
if(fopen(f name, mode) == NULL){
fprintf(stderr, “fopen error for %s\n”, fname);
exit(1);
}
else
printf(“Sucess!\nFilename: <%s>, mode <%s>\n”, fname, mode);
exit(0);
}
실행결과
oslab@o slab-lo calhost:~$ ./fopen_example
Success!
Filename: <ssu_test.txt >, mode: <r>

- 8 -

◯ 보고서 제출 시 유의 사항
- 보고서 제출 마감은 제출일 자정까지 (1 시간 지연 허용)
- 지연 제출 시 감점 : 1 일 지연 시 마다 30% 감점, 3일 지연 후부터는 미제출 처리
- 압축 오류, 파일 누락 관련 감점 syllabus 참고
◯ 구현 점수
가. 헤더 파일 작성 6
나. q1.java 를 c 프로그램으로 변환 10
다. q2.java 를 c 프로그램으로 변환 20
라. q3.java 를 c 프로그램으로 변환 20
마. -j 옵션 구현 5
바. -c 옵션 구현 5
사. -p 옵션 구현 8
아. -f 옵션 구현 5
자. -l 옵션 구현 5
차. -r 옵션 구현 8
카. c 파일에 각 라인에 맞게 탭 구성 8
◯ 필수 구현 사항 : 가, 나, 다, 라 , 마, 바 , 아, 자

- 9 -

1. 헤더 추가
2. makefile구현
3. 옵션 처리
4. 2번 완벽하게 ㄱㄱ

## Q&A
### 설계과제2 질문있습니다.
구기성 2019-04-18 18:59 조회71
설계과제 체점시 해당 샘플코드 3개가 정상적으로 변환이 되면 점수를 받는건가요?
좋아요 0  싫어요 0 인쇄
전체 2

유정주 유정주 2019-04-18 19:07
샘플코드와 크게 다르지 않은 코드로 테스트한다고 합니다.
삭제  편집  답글 좋아요 0  싫어요 0
Oslab oslab 2019-04-18 22:53
샘플코드와 크게 다르지 않고 변수가 선언된 위치나 '{ }'의 위치가 변경되었을 때의 상황 같은 단순한 것들만 추가로 테스트 될 예정

### 설계과제2 q3
박산해 2019-04-18 21:59 조회63
q3 구현시 
File file = new File("q3java.txt");
FileWriter writer = new FileWriter(file, false);
여기에서 writer 나 file 의 변수 이름을 마음대로 바꿔서 변환해도 되나요??
좋아요 0  싫어요 0 인쇄
전체 2

Oslab oslab 2019-04-18 22:13
상관없음

### 설계과제 2번 질문입니다.
백해용 2019-04-19 01:03 조회55
q3.java의 writer.write("abc")는 writer.write("abc" + "def")이런 상황
혹은 writer.write(a + "bc") 이런 코드는 존재하지 않고
오직 writer.write("abc")만으로 가정하고 코드를 작성해도 괜찮나요?
좋아요 0  싫어요 0 인쇄
전체 1

Oslab oslab 2019-04-19 10:28
고려하지 않아도 됨

### 설계과제 2 옵션순서에 대해 질문드립니다.
남윤원 2019-04-19 14:24 조회45
명세서를 보면 여러 개의 옵션을 함께 사용할 때는 -r 옵션이 가장 먼저 출력되어야 한다라고만 되어 있는데,
나머지 옵션의 경우에는 저희가 임의로 우선순위를 설정하여 출력해도 되는지 궁금합니다.

예를 들어, -j옵션과 -c옵션의 경우 
변환할 java code가 먼저 출력되고 변환된 c 언어 프로그램이 먼저 출력되는 것이 상식적으로 타당해 보입니다만,
-f옵션이나 -p옵션 그리고 -l옵션의 경우는 순서의 연관성이 크게 보이지 않았습니다. 
-j옵션과 -c 옵션 앞뒤 어디든 -p옵션이나 -l옵션이 붙어도 상관없을것 같은데, 혹시나 해서 질문을 올립니다.
-r 옵션을 제외한 나머지 옵션의 우선순위는 개발자가 임의로 지정해도 될까요?

* 추가질문 : 만약 -j옵션과 -c옵션을 연달아 출력하고자 할 때, 두 출력값 사이를 ----------------- 등으로 구분짓고 싶습니다.
이렇게 옵션 간의 출력값을 구분지어도 될지 문의드립니다.
좋아요 0  싫어요 0 인쇄
전체 2

유정주 유정주 2019-04-19 14:35
상관 없을 것 같습니다. 추가 질문 또한 설계과제1의 전례를 봤을 때 상관 없을 듯합니다.
삭제  편집  답글 좋아요 1  싫어요 0
Oslab oslab 2019-04-19 15:09
상관없음

### 설계과제 2번 makefile
차동주 2019-04-19 15:00 조회61
명세에 보면 "변환된 언어 프로그램 파일을 컴파일 할 수 있는 파일명 도 함께 생성되어야 함" 이라 돼있는데 여기서 컴파일 후 만들어지는 c파일의 실행파일명은 저희가 원하는대로 하면 되는건가요?
좋아요 0  싫어요 0 인쇄
전체 2

Oslab oslab 2019-04-19 15:28
c파일명과 동일하게 작성바람


### 설계과제2 질문드립니다.
정지수 2019-04-19 15:46 조회76
-r 옵션실행 예시에는 변환 시작과 동시에 헤더가 작성되는 거 같은데

.c파일 변환시 헤더를 변환 마지막에서 넣어도 되는지 궁금합니다.
좋아요 0  싫어요 0 인쇄
전체 2

유정주 유정주 2019-04-19 16:12
같은 질문이 올라왔었는데 순서는 큰 상관 없이 변환되는 과정만 보이면 된다고 합니다.
삭제  편집  답글 좋아요 0  싫어요 0
유정주 유정주 2019-04-19 16:13
"헤더가 출력되는 시점은 상관없음. 변환되는 과정을 보이기만 하면 됨" 이라고 답변이 달렸습니다.


### 설계과제2 옵션 질문드립니다
차영철 2019-04-15 20:26 조회78
1. -p 옵션의 경우 변환 내용에 생성자(File, FileWriter처럼 C에 대응될 수 있는)를 함께 출력해야하나요?
2. q2.java처럼 n개의 c 파일으로 변환될 수 있는 java 파일은 모든 옵션들을 변환한 n개의 파일만큼 출력해줘야하는지 궁금합니다
또한 출력 시점 역시 답변 부탁드립니다

-p 옵션의 경우 q2.java를 변환 중 stack.c 부분이 변환이 끝나면 바로 -p 옵션에 해당하는 내용 출력하는 것도 인정하는지
혹은 n개의 파일로 변환이 모두 끝나고 각 파일의 변환 내용을 파일별로 보여줘야하는지
ex) q2.java
Stack.c convert Success!
1 System.out.printf() -> printf()
q2.c convert Success!
1 System.out.printf() -> printf()
혹은 n개의 파일로 변환이 모두 끝나고 모든 파일의 변환 내용을 한 번에 보여줘야하는지
ex) q2.java
stack.c convert Success!
q2.c convert Success!
1 System.out.printf() -> printf()
(모든 파일에서 겹치는건 제외)
좋아요 0  싫어요 0 인쇄
전체 3

유정주 유정주 2019-04-15 20:54
1. 라이브러리 함수만 출력해도 된다는 댓글을 본적이 있습니다.
2. 모든 변환이 끝난 후 통합하여 처리하는 게 좋아보입니다. 즉, q2.c ... finished! 문장이 출력된 후 stack.c와 q2.c의 옵션 결과를 한꺼번에 출력해야 할 것 같습니다(물론 중복되는건 한 번만 출력).
2-1. 변환 완료 되었다는 문구는 메인함수(q1, q2, q3)만 출력해도 될 것 같습니다.
* 변환 완료 문구가 바뀌었다는 안내가 공지사항에 있으니 혹시 읽지 못하셨으면 읽어보시고 문구 수정하시면 될 듯 합니다.
삭제  편집  답글 좋아요 2  싫어요 0
차영철 차영철 2019-04-15 21:18
그럼 1의 경우 헤더테이블에 정의한 함수(printf(), scanf() 같은, exit() 제외)로 변환되는 함수만 출력해도 된다고 이해해도 될지요
삭제  편집  답글 좋아요 0  싫어요 0
유정주 유정주 2019-04-15 21:37
저는 사용자 정의 함수와 생성자를 제외한 함수는 모두 출력 했습니다.(write, flush, close 등)


### 설계과제 2 질문있습니다
차영철 2019-04-15 14:40 조회75
명세에
q2.java – Stack 구현 프로그램
" 전처리기
라고 쓰여있는데 public static final (자료형)을 #define으로만 변환해야하고 extern const (자료형)으로 변환하지 말라는 뜻인가요?
extern const (자료형)으로 대체 변환해도 되는지 질문드립니다
좋아요 0  싫어요 0 인쇄
전체 2

함승우 함승우 2019-04-15 19:17
저도 이게 궁금했는데 static const로 변경해도 되는지 알고싶습니다.
삭제  편집  답글 좋아요 0  싫어요 0
Oslab oslab 2019-04-15 19:22
\#define 으로 변환 권장


### q3 파일이 존재하지 않을 경우 예외처리 하라는 말이 이해가 되지 않습니다.
유정주 2019-04-13 22:58 조회104
q3 프로그램은 텍스트 파일 생성 프로그램인데 파일이 없을 때 예외처리 하라는 것이 이해가 되지 않습니다.
예시의 q3java.txt가 없을 경우 어떤 예외 처리를 해줘야 하나요?
아니면 q3java.txt가 아닌 다른 파일이라면 어떤 파일이 없을 때 예외처리를 해줘야하는건가요?
좋아요 0  싫어요 0 인쇄
전체 8

김한재 김한재 2019-04-13 23:49
<명세 3page 부분> 
● q3.java 프로그램 파일에서 IOException은 C언어 프로그램에서 파일이 존재하지 않는 예외인 경우에만 처리를 말씀하시는 것이라면, q3.java에서 File 객체를 생성하는 과정에서 대상이 되는 파일이 없는 경우에 대해서만 예외처리 하라는 뜻인것 같습니다.
q3.java를 기준으로 보면 q3java.txt 파일이 없을때가 예외처리 하라는 의미로,
만약 File file = new File("q3testjava.txt") 였다면 q3testjava.txt가 없을 때에 대한 예외처리를 하란 뜻으로 보입니다.
삭제  편집  답글 좋아요 1  싫어요 0

유정주 유정주 2019-04-14 00:28
예외처리에서 무슨 기능을 실행해야할까요? *.txt를 생성하는 프로그램인데 txt가 존재하지 않는다고 종료시키는건 아닐텐데
삭제  편집  답글 좋아요 0  싫어요 0

김한재 김한재 2019-04-14 00:57
FileWriter에 Flag 상황에 따라서, 파일이 없으면 쓸 수 없는 경우가 발생할 수가 있습니다.

True면 기존 파일의 내용 이후부터 쓰여져야 하는데 아마 그것에 대한 처리가 아닐까 싶습니다.
삭제  편집  답글 좋아요 1  싫어요 0

유정주 유정주 2019-04-14 01:11
음.. 그러면 Flag가 true일 때는 종료를 시키고 false일 때는 그냥 진행시키면 되는걸까요?
삭제  편집  답글 좋아요 0  싫어요 0

김한재 김한재 2019-04-14 01:26
flag가 true인 경우에는 파일이 없을때에 대해서 종료 처리를 해야하는 것으로 보이고 false일 때는 새로 생성해야하는게 맞는것 같습니다.
이 부분이 좀 모호해서 답변을 좀 기다려봐야 겠네요.
삭제  편집  답글 좋아요 1  싫어요 0

유정주 유정주 2019-04-14 12:06
늦은 밤에 감사합니다.
삭제  편집  답글 좋아요 0  싫어요 0

유정주 유정주 2019-04-14 14:40
new File()이 파일을 생성하는 의미로 생각이 되서 우선 파일이 오픈되지 않았을 경우 종료하게 예외처리 진행했는데 만약 이게 아니라면 댓글 달아주시면 감사하겠습니다
삭제  편집  답글 좋아요 0  싫어요 0

Oslab oslab 2019-04-15 10:20
맞음


### 옵션관련 질문있습니다
차동주 2019-04-13 22:45 조회52
2번 STACK예제의 경우, 
stack.c 와 q2.c로 c파일 2개로 변환됩니다.
2개의 c파일로 변환됐을때 l옵션, f옵션 을 입력했을때
1. stack.c 파일의 정보(파일의 크기, 파일의 line수) 와 q2.c 파일의 정보를 두개다 출력한다.
2. q2.c의 파일정보 (파일의 크기, 파일의 line수)만 출력한다
어떤식으로 진행하면 되는가요?
좋아요 0  싫어요 0 인쇄
전체 3

유정주 유정주 2019-04-13 22:55
변환이 두 개의 파일로 된 것이므로 둘 다 출력해야 할 것 같습니다.
삭제  편집  답글 좋아요 0  싫어요 0

김한재 김한재 2019-04-13 23:52
C언어 프로그램 파일의 라인수라고 한 것으로 보면, 파일이 두 개 모두 C언어 프로그램 파일이기 때문에 두개 모두 출력하는게 맞는 것 같네요.
순서는 모르겠습니다.


유정주 2019-04-12 18:52
설계과제1에서 연산자 처리를 일반적인 수식만 처리한 것처럼 이번에도 일반적으로 작성한 코드만 주어지지 않을까 싶습니다.
삭제  편집  답글 좋아요 0  싫어요 0

Oslab oslab 2019-04-12 19:26
위 학생의 말처럼 공지사항에 올린 자바 파일과 크게 벗어나지 않고 일반적으로 작성된 코드로만 채점이 되어짐

### 설계과제 2번 자바파일에 대해서
송민구 2019-04-11 23:48 조회85
저희가 변환해야할 자바 파일에 대해서 모든 세미콜론(;) 이나 중괄호의 시작 끝({,}) 뒤에는 
개행이 항상 나온다고 가정하고 프로젝트를 진행해도 되는지 아니면 사용자가 라인의 숫자를 
줄이기 위해서 if (i % 2 == 0) { even +=1; } 같은 코드가 나올 수 있고, 이 역시도 변환이 가능하도록
프로젝트를 진행해야하는지 질문 드립니다.
좋아요 0  싫어요 0 인쇄
전체 1

Oslab oslab 2019-04-12 01:04
변환 가능해야함


### 설계과제 2번 r 옵션
최영림 2019-04-11 21:18 조회73
명세서에 다음과 같이 서술되어 있는데,

"Java 언어 프로그램이 변환되는 과정을 한 줄 한 줄 출력. 단, Java 언어 프로그램의 매 statement가 C언어 프로그램으로 변환되어 출력되고 터미널 화면이 clear되고 다시 다음 statement 변환 및 출력....."

1. 한 줄 한 줄 출력한다는 것이 자바 코드 매 줄마다 c 코드가 어떻게 출력되는지 바로바로 띄워줘야하는건가요?

2. 자바 언어가 변환되어 출력되고 터미널 화면이 clear되고 다시 다음 statement 변환 및 출력이라는 말은 어떻게 받아들여야 하나요?

이상입니다.
좋아요 0  싫어요 0 인쇄
전체 1

Oslab oslab 2019-04-12 01:06
1.맞음 2. java와 c파일의 진행되는 과정을 계속해서 한 줄 씩 더 출력해야하기 때문에 clear를 해야한다는 의미임

ssu_convert <FILENAME> <OPTION>

import java.util.Scanner;

public class q1{
	public static void main(String[] args){
		Scanner scn = new Scanner(System.in);

		System.out.printf("Enter the number : ");

		int num;
		num = scn.nextInt();
		int even=0, odd=0;

		for(int i=1; i<=num; i++){ // Checking...
			if(i % 2 == 0){
				even+=i;
			}
			else{
				odd+=i;
			}
		}

		System.out.printf("Sum of Even number : %d\n", even);
		System.out.printf("Sum of Odd number : %d\n", odd);

		return ;
	}
}


class Stack{

	int top;
	int[] stack;

	public static final int STACK_SIZE = 10;

	public Stack(){
		top = -1;
		stack = new int[STACK_SIZE];
	}

	public int peek(){
		return stack[top];
	}

	public void push(int value){
		stack[++top] = value;
		System.out.printf(stack[top] + " PUSH !\n");
	}

	public int pop(){
		System.out.printf(stack[top] + " POP !\n");
		return stack[top--];
	}

	public void printStack(){
		System.out.printf("\n-----STACK LIST-----\n");

		for(int i=top; i>=0; i--){
			System.out.printf("%d\n",stack[i]);
		}

		System.out.printf("-----END OF LIST-----\n");
	}
}

public class q2{

	public static void main(String args[]){

		Stack st = new Stack();

		st.push(5);
		st.push(2);
		st.push(3);
		st.push(4);
		st.push(1);

		st.printStack();

		st.pop();
		st.pop();
		st.push(15);

		System.out.printf("TOP OF STACK : %d\n", st.peek());

		st.printStack();

		st.pop();
		st.pop();
		st.pop();
		st.pop();

		st.push(30);

		st.printStack();
	}
}


import java.io.File;
import java.io.IOException;
import java.io.FileWriter;

public class q3{
	public static void main(String[] args) throws IOException{


		File file = new File("q3java.txt");

		/****** 두번째 매개변수 ******/
		/****** true : 기존 파일의 내용 이후부터 쓰여짐 ******/
		/****** false : 처음부터 쓰여짐 ******/

		FileWriter writer = new FileWriter(file, false);

		writer.write("2019 OSLAB\n");
		writer.write("Linux System Programming\n");

		writer.flush();
		System.out.printf("DONE\n");

		if(writer != null)
			writer.close();

	}
}



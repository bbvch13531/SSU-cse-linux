# ssu_score specification

ssu_score는 정답 파일을 기준으로 학생들이 제출한 답안 파일을 채점하는 프로그램이다.

## ssu_score syntax
` ssu_score <STD_DIR> <ANS_DIR> [OPTION]`
1. <STD_DIR> : 채점 대상이 될 학생이 제출한 답안 디렉토리 (서브디렉토리 포함, 최대 100개)
2. <ANS_DIR> : 채점 기준이 될 정답이 있는 디렉토리. 하나의 문제당 하나의 서브디렉토리를 포함.
    빈칸 채우기 문제의 경우 정답 리스트 (복수정답은 콜론으로 구분)
    프로그램실행 문제의 경우 문제번호.c 문제번호.exe 문제번호.stdout 파일 포함

## Subscription
출제되는 문제 유형은 1.빈칸 채우기 문제와 2.프로그램 작성 문제이다.

답안 파일 형태 (input format)
빈칸채우기 : 문제번호.txt
프로그램 작성 : 문제번호.c

## 빈칸 채우기
- 하나의 빈칸 채우기 문제는 여러 개의 서브 문제로 구성될 수 있다. 
    학생들의 답안도 여러 개의 서브 문제로 구성될 수 있다. (예 1-1.txt, 1-2.txt)
- 출제되는 문제 수는 최대 100문제
- 맞으면 정답 파일에서 주어진 점수를 부여, 틀리면 0점
- 다수의 답이 정답이 될 경우 정답파일에 ':' 으로 구분하며 다수의 답을 모두 정답으로 채점.
- 연산자 사용으로 다수의 답이 정답이 되는 경우도 처리해야함.
    단, 피연산자들의 순서가 바뀌었을 때 결과 값이 달라지는 문제는 지원하지 않음.
- 연산자 우선순위를 기반으로 한 괄호도 정답으로 처리
- 문자열 간 공백은 구분하지 않음 -> 컴파일 에러가 나지 않는 공백은 정답처리


답안파일을 파일입출력으로 읽어와서 정답파일과 비교.

## 프로그램 작성
- 답안 파일을 컴파일 후 실행파일은 "./STD/학번/문제번호.exe" 이름으로 저장
- 정답 파일을 컴파일 후 실행파일은 "./ANS/문제번호/문제번호.exe" 이름으로 저장
- 정답 파일 "./ANS/문제번호/문제번호.c", 실행파일 "./ANS/문제번호/문제번호.exe", 실행결과를 "./ANS/문제번호/문제번호.stdout" 으로 저장
- 답안 파일 "./STD/학번/문제번호.c", 실행파일 "./STD/학번/문제번호.exe", 실행결과를 "./STD/학번/문제번호.stdout" 으로 저장
- "./ANS/문제번호/문제번호.stdout"을 학번 디렉토리를 순회하면서 "./STD/학번/문제번호.stdout" 과 비교하면서 결과만 우선 채점
- 실행결과의 대소문자와 공백을 구분하지 않음.
- 실행결과 채점시 warning은 -0.1점, error는 0점 처리 (#define 으로 정의 - 변경이 용이하게)
- 답안 프로그램의 실행이 5초 이상 걸리는 경우 0점 처리 (#define 으로 정의 - 변경이 용이하게)
- 실행결과 파일의 크기에 상관없이 채점 가능해야 함.

## 점수 테이블 생성
- 점수 테이블 파일은 "./ANS/score_table.csv" 로 생성
- 점수 테이블 파일이 "./ANS/"에 존재해야 하며, 존재하지 않은 경우 "./ANS/score_table.csv" 이름으로 새로 생성
- 사용자가 문제번호와 점수를 설정하고 이를 저장할 수 있어야 함.
- ssu_score 프로그램이 종료하면 자동 생성되어야 하며, (1) 학번 (2) 문제번호당 채점 점수 (3) 총점을 구해야 한다.

```
$ ./ssu_score STUDENT TRUESET
score_table.csv file doesn't exist in TRUEDIR!
1. input black question and program question's score. ex) 0.5 1
2. input all question's score. ex) Input value of 1-1: 0.1
select type >> 1
Input value of black question : 0.8
Input value of program question : 1.2

$ ./ssu_score STUDENT TRUESET
score_table.csv file doesn't exist in TRUEDIR!
1. input black question and program question's score. ex) 0.5 1
2. input all question's score. ex) Input value of 1-1: 0.1
select type >> 2
Input of 1-1.txt: 0.3
Input of 1-2.txt: 0.5
Input of 1-3.txt: 0.3
Input of 1-4.txt: 0.4
Input of 1-5.txt: 0.2
```

## Options

1. Without option

```
$ ./ssu_score STUDENT TRUESET
score_table.csv file doesn't exist in TRUEDIR!
1. input black question and program question's score. ex) 0.5 1
2. input all question's score. ex) Input value of 1-1: 0.1
select type >> 1
Input value of black question : 0.5
Input value of program question : 1
grading student's test papers..
20190001 is finished..
20190002 is finished..
20190003 is finished..
20190004 is finished..
20190005 is finished..
```

2. -e option : -e [DIRNAME] : DIRNAME/학번/문제번호_error.txt에 에러 메시지가 출력

```
$ ./ssu_score STUDENT TRUESET -e error
grading student's test papers..
20190001 is finished..
20190002 is finished..
20190003 is finished..
20190004 is finished..
20190005 is finished..

$ ls error/20190005/
11_error.txt 13_error.txt 14_error.txt

$ cat error/20190005/11_error.txt
[ERROR MESSAGE가 출력]
```

의문 : 에러가 안나는 경우? -> 아마도 빈 파일

3. -p option : 채점을 진행하면서 각 학생의 점수 출력 및 전체 평균 출력

```
$ ./ssu_score STUDENT TRUESET -p
grading student's test papers..
20190001 is finished.. score : 46.8
20190002 is finished.. score : 52.8
20190003 is finished.. score : 52.4
20190004 is finished.. score : 39.3
20190005 is finished.. score : 52.8
20190006 is finished.. score : 52.8
Total average : 49.1
```

4. -t option : -t [QNAMES] QNAME을 문제 번호로 하는 문제는 컴파일 시 -lpthread 옵션 추가 

```
$ ./ssu_score STUDENT TRUESET -p -t 12 15
grading student's test papers..
20190001 is finished.. score : 46.8
20190002 is finished.. score : 52.8
20190003 is finished.. score : 52.4
20190004 is finished.. score : 39.3
20190005 is finished.. score : 52.8
20190006 is finished.. score : 52.8
Total average : 49.1
```

실행결과의 score가 달라졌는데 lpthread가 어떻게 동작해서 달라진건지 모르겠음.

5. -h option : help, 사용법 출력 

```
$ ./ssu_score -h
Usage : ssu_score <STUDENTDIR> <TRUESETDIR> [OPTION]
Option :
 -e <DIRNAME>       print error on 'DIRNAME/ID/qname_error.txt' file
 -t <QNAMES>        compile QNAME.c with -lpthread option
 -h                 print usage
 -p                 print student's score and total average
 -c <IDS>           print ID's score
```

6. -c option : -c [STUDENTIDS] 채점결과 파일이 있는 경우 해당 학생들의 점수 출력
<STUDENTDIR> <TRUESETDIR>가 없어도 사용 가능

```
$ ./ssu_score -c 20190000 20190001 20190002
20190001's score :46.8
20190002's score :46.8
```
20190000은 존재하지 않는 학생, 출력하지 않는다.


## 기타
- 모든 옵션은 동시에 쓸 수 있음. -h 도 동시에 쓸 수 있으나 사용법을 출력 후 ssu_score가 종료
- 최대로 받을 수 있는 가변인자의 개수는 5개로 제한, 그 이상의 가변인자를 받으면 메시지를 출력하고 수행에는 반영하지 않도록 구현.
    5개가 넘는 경우, 5번째 가변인자까지만 실행한다. (p.9 실행 예 참고)
- 존재하지 않는 디렉토리 혹은 파일을 대상으로 할 경우 에러 처리
- 실행결과 및 에러 메시지를 파일에 출력 시 system()함수 사용 금지
- 점수 출력은 소수점 둘째자리까지 출력
- popen(), fork(), exec() 계열 함수 사용 금지

의문: 실행 순서는 어떻게 하지?? -> 알아서 잘 정해야 할듯.

## 참고
### 과제 구현에 필요한 함수
1. difftime()
2. gettimeofday() p.519
3. getopt() 
4. system()

## 채점사항
- 가. 빈칸 채우기 문제 채점 기능 : 40
- 나. 프로그램 작성 문제 채점 기능 : 40
- 다. 5초 이상 수행되는 문제 예외처리 기능 : 8
- 라. -e 옵션 : 3
- 마. -p 옵션 : 3
- 바. -t 옵션 : 2
- 사. -h 옵션 : 2
- 아. -c 옵션 : 2
- 자. gettimeofday()를 사용하여 프로그램의 수행 시간 측정 - 모든 과제 동일, 미구현시 -5
- 차. 금지한 함수 사용시 한 개 함수 사용 당 -30
필수 구현 사항: 가, 나, 라, 마, 바, 자


## Architect

### 개발 계획
1. 어떻게 짜야할지 순서 먼저 생각
2. 모듈별로 나누기
3. 각 모듈 어떻게 구현할지 교재, 검색, 예제 등 공부
4. 모듈별로 완성하고 테스트하고 통합시키기
5. 디버깅


`/STD_DIR/학번`을 탐색. 

/STD_DIR/ 안에 어떤 학번이 있는지 ls로 받아와서 char[]로
`{"20190001","20190002","20190003"}` 으로 만든다.

1-1.txt
1-2.txt
2-1.txt
2-2.txt
3.c
4.c
5.c 순서대로 채점 

`/STD_DIR/학번/1-1.txt` 과 `/ANS/1.txt` 를 비교

fopen해서 char[] 로 저장하고 strcmp로 비교
피연산자를 연산자 우선순위에 따라서 분류하고 스택에 후위표기법으로 넣는다.
대소문자는 구분, 공백은 구분 X
일치하면 점수 추가

0303

처음 과제 나온 날임. 명세서가 눈에 잘 안들어와서 다시 정리하면서 읽는 중. 구현할 때 처리해야할 의문점들이 생긴다.
system()을 사용하지 못하기 때문에 dup2()를 사용해야 할 것 같다.


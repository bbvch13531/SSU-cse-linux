# ssu_score specification

ssu_score는 정답 파일을 기준으로 학생들이 제출한 답안 파일을 채점하는 프로그램이다.

## ssu_score syntax
` ssu_score <STD_DIR> <ANS_DIR> [OPTION]`
1. <STD_DIR> : 채점 대상이 될 학생이 제출한 답안 디렉토리 (서브디렉토리 포함, 최대 100개)
2. <ANS_DIR> : 채점 기준이 될 정답이 있는 디렉토리. 하나의 문제당 하나의 서브디렉토리를 포함.
    빈칸 채우기 문제의 경우 정답리 스트 (복수정답은 콜론으로 구분)
    프로그램실행 문제의 경우 문제번호.c 문제번호.exe 문제번호.stdout 파일 포함

## Subscription
출제되는 문제 유형은 1.빈칸 채우기 문제와 2.프로그램 작성 문제이다.

답안 파일 형태 (input)
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


## Architect
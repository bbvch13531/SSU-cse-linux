# ssu_backup

# 기능

## 프롬프트 명령

1. add
2. remove
3. compare
4. recover
5. list
6. ls
7. vi(m)
8. exit

## add
` add <FILENAME> [PERIOD] [OPTION] `
[OPTION] : 
    -m
    -n
    -t
    -d
모두 동시에 사용 가능

백업 리스트 구조체

typedef struct _backup_list{
    backup_list *next;
    char pathname[256];
    int interval;
    int options[4]; // 옵션 설정되면 1 아니면 0
    int number; // -n 옵션
    int time;   // -t 옵션

} backup_list;
 .
## remove
` remove <FILENAME> [OPTION] `
[OPTION] : 
    -a

백업 중단해야함. 어떻게? - 시그널?

백업할때
    fopen해서
    버퍼로 읽고
    다른 파일 fopen해서
    버퍼를 write 해야 한다.

int copy(char *pathname, Backup_list *list){
    fopen1()
    fopen2()
    fread()
    fwrite()
    list의 백업 주기를 확인
}

쓰레드를 만든다.
전달할 정보 - i 번째 리스트.
함수 - backup(): copy를 호출함.

리스트에 visit check해야함. -> 쓰레드가 할당 되었는지 아닌지 체크.
안되었으면 새로 쓰레드 만들어야함.

쓰레드 배열
tid_t threads[]

tail pointer?


0531

1. thread_test 예제 테스트
2. 로그파일 만드는 예제 테스트
3. Add 설계
4. 
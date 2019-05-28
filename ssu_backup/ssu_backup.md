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


## remove
` remove <FILENAME> [OPTION] `
[OPTION] : 
    -a

백업 중단해야함. 어떻게? - 시그널?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/stat.h>

#define BACKUP_DIR "BACKUP_DIR"

/*
// add 기능
*/
void add(char *pathname, int argc, char **argv);

/*
//  주어진 문자열이 몇개의 단어인지 계산하는 함수
*/
int count_words(char *string);

/*
//  주어진 문자열의 cmd를 리턴하는 함수
//  return:
//          add
//          remove
//          compare
//          recover
//          list
//          ls
//          vi
//          vim
//          exit
*/
void getcmd(char *string, char *cmd);
/*
//  사용법 출력하고 종료하는 함수
*/
void print_usage_and_exit(void);

/*
//  백업 디렉터리 생성하는 함수
*/          
void create_backup_dir(char *pathname);

char backup_pathname[256];
int main(int argc, char **argv){
    int cnt;
    char inputbuf[256], cmd[10];
    // 인자가 없는 경우
    if(argc == 1){
        create_backup_dir("./");
    }
    // 인자가 1개인 경우
    else if(argc == 2){
        create_backup_dir(argv[1]);
    }
    // 인자를 2개 이상 입력한 경우
    else if(argc > 2){
        // usage 출력 후 종료
        print_usage_and_exit();
    }

    while(1){
        printf("20142468>");
        gets(inputbuf);
        printf("%s\n", inputbuf);
        getcmd(inputbuf, cmd);
        cnt = count_words(inputbuf);
        printf("cmd = %s, cnt = %d\n",cmd, cnt);
    }
    exit(0);
}

void add(char *pathname, int argc, char **argv){

}

void getcmd(char *string, char *cmd){
    int len = strlen(string);

    for(int i=0; i<len; i++){
        if(string[i] == ' '){
            cmd[i] = '\0';
            return;
        }
        cmd[i] = string[i];
    }
}

int count_words(char *string){
    int len = strlen(string);
    int cnt = 0;
    for(int i=0; i<len; i++){
        if(string[i] == ' ')
            cnt++;
    }
    return cnt + 1;
}

void create_backup_dir(char *pathname){
    struct dirent **dentry;
    struct stat statbuf;

    if(access(pathname, F_OK) != 0){
        fprintf(stderr, "Directory not exist\n");
        print_usage_and_exit();
    }

    if(lstat(pathname, &statbuf) < 0){
        fprintf(stderr, "lstat error\n");
        print_usage_and_exit();
    }

    if(!S_ISDIR(statbuf.st_mode)){
        fprintf(stderr, "pathname is not directory\n");
        print_usage_and_exit();
    }
    if(access(pathname, R_OK) != 0 || access(pathname, W_OK) != 0 || access(pathname, X_OK) != 0){
        fprintf(stderr, "Permission denied\n");
        print_usage_and_exit();
    }

    chdir(pathname);

    mkdir(BACKUP_DIR, 0644);

    strcpy(backup_pathname, pathname);
    strcat(backup_pathname, BACKUP_DIR);
}

void print_usage_and_exit(void){
    // ./ssu_backup 잘못된 인자로 실행시 사용법 출력 후 종료
    printf("Usage: ./ssu_backup [PATHNAME]\n");
    exit(0);
}
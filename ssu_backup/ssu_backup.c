#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include "backup_list.h"

#define BACKUP_DIR "BACKUP_DIR"

/*
// add 기능
*/
void add(int argc, char **argv);

/*
//  주어진 문자열이 몇개의 단어인지 계산하는 함수
*/
int count_words(char *string);

/*
//  주어진 문자열의 cmd를 구하는 함수
//  cmd:
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
//
*/
void setup_argv(char *str, char **argv);

/*
//  사용법 출력하고 종료하는 함수
*/
void print_usage_and_exit(void);

/*
//  백업 디렉터리 생성하는 함수
*/          
void create_backup_dir(char *pathname);

/*
//   파일 복사하는 함수
*/
int copy(char *pathname1, char *pathname2);
char backup_pathname[256];

Backup_list list_head;

int main(int argc, char **argv){
    int cnt;
    char inputbuf[256], cmd[10];
    char *argv_param[256];
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

        fgets(inputbuf, 255, stdin);
        printf("%s\n", inputbuf);

        getcmd(inputbuf, cmd);
        setup_argv(inputbuf, argv_param);
        cnt = count_words(inputbuf);

        printf("cmd = %s, cnt = %d\n",cmd, cnt);

        if(strcmp(cmd, "add") == 0){
            add(cnt, argv_param);
        }
        else if(strcmp(cmd, "remove") == 0){
            
        }
        else if(strcmp(cmd, "compare") == 0){

        }
        else if(strcmp(cmd, "recover") == 0){

        }
        else if(strcmp(cmd, "list") == 0){

        }
        else if(strcmp(cmd, "ls") == 0){
            system("ls");
        }
        else if(strcmp(cmd, "vi") == 0 || strcmp(cmd, "vim") == 0){
            system("vim");
        }
        else if(strcmp(cmd, "exit") == 0){
            // 자원 해제.
            // 쓰레드 종료.
            break;
        }
    }
    exit(0);
}

void add(int argc, char **argv){
    char pathname = argv[1];
    int period;
    struct stat statbuf;

    printf("add func\n");
    period = atoi(argv[2]);
    // 파일이 존재하지 않는 경우
    if(access(pathname, F_OK) != 0){
        printf("file not exists\n");
        return ;
    }

    if(5 <= period && period <= 10){
        printf("period should be greater than or equal to 5 and less than or equal to 10\n");
        return ;
    }
    //  lstat
    if(lstat(pathname, &statbuf) < 0){
        fprintf(stderr, "lstat error\n");
        return ;
    }

    // 정규파일이 아닌 경우
    if(!S_ISREG(statbuf.st_mode)){
        fprintf(stderr, "file is not regular file\n");
        return ;
    }

    // 백업리스트에 이미 존재하는 경우
    if(find_backup_list(pathname, &list_head) == 1){
        fprintf(stderr, "file already exist in backup list\n");
        return ;
    }
    // argv[1] filename
    // argv[2]가 5이상 10이하이면 period
    // 아니면 option
    // getopt

    // update_thread
}

int copy(char *pathname1, char *pathname2){
    int len;
    char buf[25];
    int fd1, fd2;

    fd1 = open(pathname1, O_RDONLY);
    fd2 = open(pathname2, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    while((len = read(fd1, buf, 10)) > 0){
        write(fd2, buf, len);
        // printf("len = %d buf = %s\n",len, buf);
    }
}

void setup_argv(char *str, char **argv){
    int len = strlen(str);
    int j = 0, n = 0;
    char buf[128];

    for(int i=0; i<len; i++){
        if(str[i] == ' ' || i == len-1){
            buf[j] = '\0';
            j=0;
            // malloc
            argv[n] = (char *)malloc(sizeof(strlen(buf)));
            strcpy(argv[n], buf);
            n++;
        }
        else
            buf[j++] = str[i];
    }

    for(int i=0; i<n; i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    return ;
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

    // 디렉토리가 존재하지 않는 경우
    if(access(pathname, F_OK) != 0){
        fprintf(stderr, "Directory not exist\n");
        print_usage_and_exit();
    }
    
    //  lstat
    if(lstat(pathname, &statbuf) < 0){
        fprintf(stderr, "lstat error\n");
        print_usage_and_exit();
    }

    // 디렉토리가 아닌 경우
    if(!S_ISDIR(statbuf.st_mode)){
        fprintf(stderr, "pathname is not directory\n");
        print_usage_and_exit();
    }

    // 권한이 없는 경우
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

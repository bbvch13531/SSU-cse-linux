#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
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
//  backup_list를 update하고 쓰레드를 실행/종료하는 함수
*/
void update_thread(void);

/*
//  string을 argc, argv로 만드는 함수
*/
void setup_argv(char *str, char **argv);

/*
//  사용법 출력하고 종료하는 함수
*/
void print_usage_and_exit(void);

/*
//  정규파일, 디렉토리 확인하는 함수
*/
int is_reg_or_dir(struct stat statbuf, int opt);

/*
//  쓰레드에서 실행할 함수
*/
void * thread_func(void *arg);

/*
//
*/
void make_postfix(time_t timer, char *postfix1, char *postfix2);
/*
//  백업 디렉터리 생성하는 함수
*/          
void create_backup_dir(char *pathname);

/*
//   파일 복사하는 함수
*/
time_t copy(char *pathname1, char *pathname2);

char backup_pathname[256];

struct Backup_list list_head;
FILE *log_file_fp;
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
        // 백업 리스트의 정보를 가지고 쓰레드를 업데이트
        // update_thread_from_backup_list();
    }
    exit(0);
}

int is_reg_or_dir(struct stat statbuf, int opt){
    // opt == 1 정규파일인지 확인
    if(opt == 1){
        if(!S_ISREG(statbuf.st_mode)){ 
            printf("Not regular file\n");
            return -1;
        }
        else
            return 1;
    }
    // opt == 2 디렉토리인지 확인
    else if(opt == 2){
        if(!S_ISDIR(statbuf.st_mode)){
            printf("Not directory\n");
            return -1;
        }
        else
            return 1;
    }
}
void add(int argc, char **argv){
    char *pathname = argv[1];
    int period;
    int opt, opt_number, opt_time;
    struct stat statbuf;
    struct Node new_node;

    memset(&new_node, 0, sizeof(struct Node));
    // period 가 정수가 아닐 경우.
    for(int i=0; i<strlen(argv[2]); i++){
        if(!isdigit(argv[2][i])){
            printf("period should be Integer\n");
            return ;
        }
    }
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

    // -d 옵션에서 처리해야함.
    // // 정규파일이 아닌 경우
    // if(!S_ISREG(statbuf.st_mode)){
    //     fprintf(stderr, "file is not regular file\n");
    //     return ;
    // }

    printf("before search func\n");
    // 백업리스트에 이미 존재하는 경우
    if(search_backup_list(pathname, &list_head) != -1){
        fprintf(stderr, "file already exist in backup list\n");
        return ;
    }
    // argv[1] filename
    // argv[2]가 5이상 10이하이면 period
    // 아니면 option
    // getopt

    // update_thread

    printf("add func\n");

    // 옵션이 있는 경우
    if(argc > 3){
        while((opt = getopt(argc, argv, "mn:t:d")) != -1){
            switch(opt){
                case 'm':
                    if(is_reg_or_dir(statbuf, 1) == -1) return;
                    printf("add -m\n");
                    // mtime이 수정된 경우에만 백업 실행
                    strcpy(new_node.pathname, pathname);
                    new_node.interval = period;
                    new_node.mtime = statbuf.st_mtime;
                    new_node.options[0] = 1;

                    append_backup_list(new_node, &list_head);
                    break;

                case 'n':
                    if(is_reg_or_dir(statbuf, 1) == -1) return;
                    opt_number = atoi(optarg);
                    printf("add -n\n");
                    // 백업한 파일의 최대 갯수: opt_number
                    strcpy(new_node.pathname, pathname);
                    new_node.interval = period;
                    new_node.mtime = statbuf.st_mtime;
                    new_node.options[1] = 1;
                    new_node.number = opt_number;

                    append_backup_list(new_node, &list_head);
                    break;

                case 't':
                    if(is_reg_or_dir(statbuf, 1) == -1) return;
                    opt_time = atoi(optarg);
                    printf("add -t\n");

                    strcpy(new_node.pathname, pathname);
                    new_node.interval = period;
                    new_node.mtime = statbuf.st_mtime;
                    new_node.options[2] = 1;
                    new_node.time = opt_time;

                    append_backup_list(new_node, &list_head);
                    break;

                case 'd':
                    if(is_reg_or_dir(statbuf, 2) == -1) return;
                    printf("add -d\n");
                    // append_dir_backup();
                    break;

                case '?':

                    break;
            }
        }
    }
    // 옵션 없이 add 실행하는 경우
    else {
        strcpy(new_node.pathname, pathname);
        new_node.interval = period;
    }
    update_thread();

}

void update_thread(void){
    //backup_pathname
    struct Node *np;
    int size = list_head.size;
    int tid;
    for(int i=0; i<size; i++){
        np = get(i, &list_head);
        
        // To add Node from thread
        if(np->saved_count == 0){
            pthread_create(&tid, NULL, thread_func, (void *)np);
        }
        // To remove Node from thread
        else if(np->saved_count == -1){
            // 쓰레드 종료.

            pthread_cancel(np->tid);
        }
    }
}

void *thread_func(void *arg){
    struct Node *np = (struct Node *)arg;
    time_t timer;
    char yypostfix[10], hhpostfix[10];


    // 처음 생성될 때.
    // 로그파일에 added 기록
    if(np->saved_count == 0){

    }
    // 삭제할 때
    // 로그파일에 deleted 기록
    else if(np->saved_count == -1){

    }
    
    timer = copy(np->pathname, backup_pathname);
    make_postfix(timer, yypostfix, hhpostfix);
    
    // 로그파일에 로그 남기기.
    // fwrite()

}

time_t copy(char *pathname1, char *pathname2){
    int len;
    char buf[513];
    int fd1, fd2;
    time_t timer;

    fd1 = open(pathname1, O_RDONLY);
    fd2 = open(pathname2, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    while((len = read(fd1, buf, 512)) > 0){
        write(fd2, buf, len);
        // printf("len = %d buf = %s\n",len, buf);
    }

    timer = time(NULL);
    return timer;
}

void make_postfix(time_t timer, char *postfix1, char *postfix2){
    struct tm *cur_time;
    int year, mon, mday, hour, min, sec;

    // char postfix[256];
    char yymmdd[10], hhmmss[10];

    cur_time = localtime(&timer);

    year = cur_time->tm_year;
    mon = cur_time->tm_mon;
    mday = cur_time->tm_mday;
    hour = cur_time->tm_hour;
    min = cur_time->tm_min;
    sec = cur_time->tm_sec;

    year += 1900;
    year %= 100;
    mon += 1;

    sprintf(yymmdd, "%02d%02d%02d", year, mon, mday);
    sprintf(hhmmss, "%02d%02d%02d", hour, min, sec);

    strcpy(postfix1, yymmdd);
    strcpy(postfix2, hhmmss);
    // sprintf(postfix, "%s%s", yymmdd, hhmmss);
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
    chdir(BACKUP_DIR);
    log_file_fp = fopen("backup_file.log", "w+");

    strcpy(backup_pathname, pathname);
    strcat(backup_pathname, BACKUP_DIR);
}

void print_usage_and_exit(void){
    // ./ssu_backup 잘못된 인자로 실행시 사용법 출력 후 종료
    printf("Usage: ./ssu_backup [PATHNAME]\n");
    exit(0);
}

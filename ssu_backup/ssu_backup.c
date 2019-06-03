#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>
#include <errno.h>
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
//  remove 기능
*/
void remove_list(int argc, char **argv);


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
//
*/
void write_log(char *pathname, int option);

/*
//
*/
void get_filename_only(char *origin, char *filename);

/*
//  백업 디렉터리 생성하는 함수
*/          
void create_backup_dir(char *pathname);

/*
//
*/
void delete_timeout_files(char *backupname, int backup_time);

/*
//   파일 복사하는 함수
*/
time_t copy(char *pathname1, char *pathname2);


char backup_pathname[256];

struct Backup_list list_head;
FILE *log_file_fp;
int log_file_fd;
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
        // printf("%s\n", inputbuf);

        getcmd(inputbuf, cmd);
        setup_argv(inputbuf, argv_param);
        cnt = count_words(inputbuf);

        printf("cmd = %s, cnt = %d\n",cmd, cnt);

        if(strcmp(cmd, "add") == 0){
            add(cnt, argv_param);
        }
        else if(strcmp(cmd, "remove") == 0){
            remove_list(cnt, argv_param);
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
        else if(strcmp(cmd, "print") == 0){
            print_backup_list(&list_head);
            printf("size=%d\n",list_head.size);
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
    return -1;
}

void add(int argc, char **argv){
    char *pathname = argv[1];
    char realpathname[1024];
    int period;
    int opt, opt_number, opt_time;
    struct stat statbuf;
    struct Node new_node;

    memset(&new_node, 0, sizeof(struct Node));
    // period 가 정수가 아닐 경우.
    if(argc < 3){
        printf("Usage: add <FILENAME> <PERIOD> [OPTION]\n");
        return ;
    }
    for(int i=0; i<strlen(argv[2]); i++){
        if(!isdigit(argv[2][i])){
            printf("period should be Integer\n");
            return ;
        }
    }
    period = atoi(argv[2]);
    realpath(pathname, realpathname);
    printf("pathname = %s %s\n",pathname, realpathname);
    
    // 파일이 존재하지 않는 경우
    if(access(pathname, F_OK) != 0){
        printf("file not exists\n");
        return ;
    }

    if(5 > period || period > 10){
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

    // printf("add func\n");

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
                    
                    for(int i=0; i<strlen(optarg); i++){
                        if(!isdigit(optarg[i])){
                            printf("period should be Integer\n");
                            return ;
                        }
                    }
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
        new_node.mtime = statbuf.st_mtime;
        append_backup_list(new_node, &list_head);
    }

    print_backup_list(&list_head);
    write_log(realpathname, 0);
    // printf("before update_thread\n");
    update_thread();
    printf("after update_thread\n");
}


void remove_list(int argc, char **argv){
    struct Node *node;
    char pathname[256];
    int size = list_head.size;
    if(argc != 2){
        printf("Usage: remove <FILENAME> [OPTION]\n");
        return ;
    }

    if(strcmp(argv[1], "-a") == 0){
        
            for(int i=0; i<size; i++){
                node = get(i, &list_head);
                pthread_cancel(node->tid);
            }
            remove_all(&list_head);
            print_backup_list(&list_head);
        // else{
        //     printf("Usage: remove <FILENAME> [OPTION]\n%s\n",argv[1]);
        //     return ;
        // }
    }

    else{
        strcpy(pathname, argv[1]);
        int search_res = search_backup_list(pathname, &list_head);
        
        if(search_res == -1){
            printf("File is not exist in backup list\n");
            return ;
        }
        node = get(search_res, &list_head);
        pthread_cancel(node->tid);
        remove_from_list(pathname, &list_head);
    }
}


int is_mtime_changed(char *pathname, struct stat originstat){
    struct stat statbuf;

    if(lstat(pathname, &statbuf) < 0){
        fprintf(stderr, "lstat error\n");
        return 0;
    }

    if(statbuf.st_mtime != originstat.st_mtime){
        return 1;
    }
    else
        return 0;
}

void update_thread(void){
    //backup_pathname
    struct Node *np;
    int size = list_head.size;
    pthread_t tid;

    for(int i=0; i<size; i++){
        np = get(i, &list_head);
        // printf("np=%s, count = %d\n", np->pathname, np->saved_count);
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
    struct stat statbuf;
    time_t timer;
    char yypostfix[10], hhpostfix[10];
    char backup_filename[256], filename_only[512], writebuf2[512];
    char realpath1[256];
    int interval = np->interval, will_copy = 0;
    // 처음 생성될 때.
    // 로그파일에 added 기록
    printf("thread func\n");

    // printf("backup_filename=%s\n",backup_filename);

    // save before mtime
    if(lstat(np->pathname, &statbuf) < 0){
        fprintf(stderr, "lstat error\n");
        pthread_exit(NULL);
    }
    
    while(1){
        make_postfix(timer, yypostfix, hhpostfix);
        get_filename_only(np->pathname, filename_only);
        
        strcpy(backup_filename, backup_pathname);
        strcat(backup_filename, "/");
        strcat(backup_filename, filename_only);
        strcat(backup_filename, "_");
        strcat(backup_filename, yypostfix);
        strcat(backup_filename, hhpostfix);

        // -m option
        if(np->options[0] == 1){
            int mtime_flag = is_mtime_changed(np->pathname, statbuf);

            // 파일이 수정되거나 처음 추가된 파일인 경우
            if(mtime_flag == 1 || np->saved_count == 0){
                will_copy = 1;
                // copy(np->pathname, backup_filename);

                // update stat       
                if(lstat(np->pathname, &statbuf) < 0){
                    fprintf(stderr, "lstat error\n");
                    pthread_exit(NULL); 
                }
            }
        }

        // -n option
        if(np->options[1] == 1){
            int max_count = np->number;
            if(np->saved_count < max_count){
                will_copy = 1;
                // copy(np->pathname, backup_filename);
            }
        }

        // -t option
        if(np->options[2] == 1){
            // pathname로 시작하는 기존 백업 파일 찾기
            // 백업 파일의 생성시간과 현재 시간을 비교
            // np->time 이상이면 삭제
            will_copy = 1;
            // copy(np->pathname, backup_filename);

            delete_timeout_files(np->pathname, np->time);
        }

        // -d option
        if(np->options[3] == 1){
            // 인자로 받은 디렉터리 탐색
            // 디렉터리의 모든 파일을 append
            // copy
        }
        else{
            if(np->saved_count == -1){
                // timer = delete(np->pathname, backup_pathname);
            }
            // 삭제할 때
            // 로그파일에 deleted 기록
            else{
                printf("path1=%s path2=%s\n", np->pathname, backup_filename);
                will_copy = 1;
                // copy(np->pathname, backup_filename);
            }
        }
        if(will_copy == 1){
            np->tid = pthread_self();
            copy(np->pathname, backup_filename);
        }
        np->saved_count++;

        sleep(interval);
    }
    // 로그파일에 로그 남기기.
    // fwrite()
    realpath(np->pathname, realpath1);
    pthread_exit(NULL); 
}

void delete_timeout_files(char *backupname, int backup_time){
    struct dirent **dentry;
    struct stat statbuf;
    int dircnt=0;
    time_t cur_time = time(NULL);
    char filename[256];

    if((dircnt = scandir(backup_pathname, &dentry, NULL, NULL)) == -1){
        fprintf(stderr, "opendir: chdir error for %s\n",backup_pathname);
        exit(1);
    }
    chdir(backup_pathname);
    for(int i=0; i<dircnt; i++){
        strcpy(filename, dentry[i]->d_name);
        if(strcmp(filename, "..") == 0 || strcmp(filename, ".") == 0)
            continue;

        // printf("file %d=%s\n", i, filename);
        if(lstat(filename, &statbuf) < 0){
            fprintf(stderr, "lstat error\n");
            printf("%s\n",strerror(errno));
            print_usage_and_exit();
        }
        if(strstr(filename, backupname) != NULL){
            if(statbuf.st_ctime + backup_time < cur_time ){
                int res = remove(filename);
                if(res == 0){
                    // remove logging
                    // write_log(filename, 1);
                    printf("file removed successfully\n");
                }
                else
                    printf("file not removed\n");
            }
        }
        // printf("file %d=%s, ctime=%d, cur_time=%d, backup_time=%d\n", i, filename, statbuf.st_ctime, cur_time, backup_time);
    }
    // chdir(backup_pathname);

    chdir("../");
}

time_t copy(char *pathname1, char *pathname2){
    int len;
    char buf[513];
    int fd1, fd2;
    time_t timer;
    // char testpathname2[256] = "./BACKUP_DIR/aaa.txt_700101090000";
    fd1 = open(pathname1, O_RDONLY);
    fd2 = open(pathname2, O_RDWR | O_CREAT | O_TRUNC, 0777);

    // printf("fd2 = %d\n",fd2);
    write_log(pathname1, 1);

    while((len = read(fd1, buf, 512)) > 0){
        write(fd2, buf, len);
        printf("len = %d buf = %s\n",len, buf);
    }
    close(fd1);
    close(fd2);

    return timer;
}

void write_log(char *pathname, int option){
    char yymmdd[10], hhmmss[10];
    char writebuf1[512], writebuf2[256];
    time_t timer = time(NULL);

    make_postfix(timer, yymmdd, hhmmss);
    realpath(pathname, writebuf2);
    sprintf(writebuf1, "[%s %s] %s ", yymmdd, hhmmss, writebuf2);

    // add
    if(option == 0){
        strcat(writebuf1, "added\n");
    }
    // copy
    else if(option == 1){
        strcat(writebuf1, "generated\n");
    }
    // delete
    else if(option == 2){
        strcat(writebuf1, "deleted\n");
    }
    // recover
    else if(option == 3){
        strcat(writebuf1, "recovered\n");
    }
    // fwrite(writebuf1, )
    // write()
    write(log_file_fd, writebuf1, strlen(writebuf1));
}

void make_postfix(time_t timer, char *postfix1, char *postfix2){
    struct tm *cur_time;
    int year, mon, mday, hour, min, sec;
    // char postfix[256];
    char yymmdd[10], hhmmss[10];

    timer = time(NULL);
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

void get_filename_only(char *origin, char *filename){
    int len = strlen(origin);
    char buf[256], tmp;
    int j=0;
    printf("%s\n",origin);
    for(int i=len-1; i>=0; i--){
        if(origin[i] == '/'){
            printf("buf in for = %s\n",buf);
            break;
        }
        buf[j++] = origin[i];
    }
    for(int i=0; i<j/2; i++){
        tmp = buf[i];
        buf[i] = buf[j-i-1];
        buf[j-i-1] = tmp;
    }
    
    printf("buf = %s\n",buf);

    strcpy(filename, buf);
}

void setup_argv(char *str, char **argv){
    int len = strlen(str);
    int j = 0, n = 0;
    char buf[256];

    for(int i=0; i<len; i++){
        if(str[i] == ' ' || i == len-1){
            buf[j] = '\0';
            j=0;
            // malloc
            // printf("strlen %d\n",strlen(buf)+1);
            argv[n] = (char *)malloc(strlen(buf) +1);
            strcpy(argv[n], buf);
            // printf("buf = %s argv[%d] = %s %d\n", buf, n, argv[n], strlen(buf));
            n++;
            memset(buf, 0, 256);
        }
        else{
            // printf("%c\n", str[i]);
            buf[j++] = str[i];
        }
    }

    // for(int i=0; i<n; i++){
    //     printf("argv[%d] = %s\n", i, argv[i]);
    // }
    return ;
}

void getcmd(char *string, char *cmd){
    int len = strlen(string);

    for(int i=0; i<len; i++){
        if(string[i] == ' ' || string[i] =='\n'){                                                                                                                           
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

    mkdir(BACKUP_DIR, 0777);
    chdir(BACKUP_DIR);
    // log_file_fp = fopen("backup_file.log", "w+");
    log_file_fd = open("backup_file.log", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    // system("pwd");
    strcpy(backup_pathname, pathname);
    strcat(backup_pathname, BACKUP_DIR);

    chdir("..");
}

void print_usage_and_exit(void){
    // ./ssu_backup 잘못된 인자로 실행시 사용법 출력 후 종료
    printf("Usage: ./ssu_backup [PATHNAME]\n");
    exit(0);
}

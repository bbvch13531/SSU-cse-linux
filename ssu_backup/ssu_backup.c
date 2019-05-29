#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/stat.h>

/*
//  사용법 출력하고 종료하는 함수
*/
void print_usage_and_exit(void);

/*
//  백업 디렉터리 생성하는 함수
//  return:
//          -1: lstat error
//          
*/          
int create_backup_dir(char *pathname);

int main(int argc, char **argv){
    
    
    exit(0);
}

int create_backup_dir(char *pathname){
    struct dirent **dentry;
    struct stat statbuf;
    DIR *dirp;

    int dircnt;
    if(access(pathname, F_OK) != 0){
        fprintf(stderr, "Directory not exist\n");
        print_usage_and_exit();
    }
    if(access(pathname, R_OK) != 0 || access(pathname, W_OK) != 0 || access(pathname, X_OK) != 0){
        fprintf(stderr, "Permission denied\n");
        print_usage_and_exit();
    }

    if(!S_ISDIR(statbuf.st_mode)){
        fprintf(stderr, "pathname is not directory\n");
        print_usage_and_exit();
    }

    if(lstat(pathname, &statbuf) < 0){
        fprintf(stderr, "lstat error\n");
        print_usage_and_exit();
    }

    // 디렉터리 인자가 주어지지 않은 경우
    if(strcmp(pathname, "") == 0){
        mkdir("../BACKUP_DIR", 0644);
        
    }
    else{
       
    }
}

void print_usage_and_exit(void){
    // ./ssu_backup 잘못된 인자로 실행시 사용법 출력 후 종료
    printf("Usage: ./ssu_backup [PATHNAME]\n");
    exit(0);
}
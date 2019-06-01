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
#include "../../backup_list.h"

void update_thread();

void *copy(void*arg);

struct Backup_list list;
struct Node dummy[5] ={
    {"aaa", 1, {0,0,0,0}, 0, 0},
    {"bbb", 2, {0,0,0,0}, 0, 0},
    {"ccc", 3, {0,0,0,0}, 0, 0},
    {"ddd", 4, {0,0,0,0}, 0, 0},
    {"eee", 5, {0,0,0,0}, 0, 0}
};

FILE *fp;

int main(void){
    int input;
    int tmptid;

    init(&list);

    while(1){
        printf("20142468>");
        scanf("%d",&input);
        // input은 1부터 5까지
        if(input == -1) break;
        else{
            printf("add start");
            append_backup_list(dummy[input], &list);
            pthread_create(&tmptid, NULL, copy, NULL);

        }
    }
    exit(0);
}

void update_thread(){

}

void *copy(void *arg){
    
}
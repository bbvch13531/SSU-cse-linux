#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include "../../backup_list.h"

void update_thread();
void calc_time(char *timebuf);
void *copy(void*arg);

struct Backup_list list;
struct Node dummy[5] ={
    {NULL, "aaa.txt", 2, {0,0,0,0}, 0, 0},
    {NULL, "bbb.txt", 4, {0,0,0,0}, 0, 0},
    {NULL, "ccc.txt", 6, {0,0,0,0}, 0, 0},
    {NULL, "ddd.txt", 8, {0,0,0,0}, 0, 0},
    {NULL, "eee.txt", 10, {0,0,0,0}, 0, 0}
};

int log_fd;

int main(void){
    int input;
    int tmptid;

    init(&list);
    log_fd = open("backup.log", O_RDWR | O_CREAT | O_TRUNC, 0644);

    while(1){
        printf("20142468>");
        scanf("%d",&input);
        // input은 1부터 5까지
        if(input == -1) break;
        else{
            printf("add start\n");
            append_backup_list(dummy[input], &list);
            pthread_create(&tmptid, NULL, copy, (void *)&dummy[input]);

        }
    }
    exit(0);
}

void update_thread(){

}

void *copy(void *arg){
    struct Node node;
    int read_fd;
    int len;
    pthread_t tid = pthread_self();
    char readbuf[51], timebuf[256], outputbuf[50];

    node = *(struct Node *)arg;
    
    read_fd = open(node.pathname, O_RDONLY);
    // printf("%s\n",node.pathname);
    len = read(read_fd, readbuf, 50);
    strcat(readbuf, "\n");

    sprintf(outputbuf," in thread %d\n", node.interval);
    printf("%s",outputbuf);

    for(int i=0; i<10; i++){
        sleep(node.interval);
        calc_time(timebuf);
        strcat(timebuf, outputbuf);
        // strcat(timebuf, tid + '0');
        
        write(log_fd, timebuf, strlen(timebuf));
    }
}

void calc_time(char *timebuf){
    time_t timer;
    struct tm *cur_time;
    char yymmdd[10], hhmmss[10];
    int year, mon, mday, hour, min, sec;

    timer = time(NULL);
    cur_time = localtime(&timer);

    year = cur_time->tm_year;
    mon = cur_time->tm_mon;
    mday = cur_time->tm_mday;
    hour = cur_time->tm_hour;
    min = cur_time->tm_min;
    sec = cur_time->tm_sec;

    year %= 100;
    mon += 1;

    sprintf(yymmdd, "%02d%02d%02d", year, mon, mday);
    sprintf(hhmmss, "%02d%02d%02d", hour, min, sec);
    sprintf(timebuf, "%s%s", yymmdd, hhmmss);
}
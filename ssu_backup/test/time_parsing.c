#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void){
    time_t timer;
    struct tm *cur_time;
    int year, mon, mday, hour, min, sec;

    char pathname = "/home/projects/test1.txt";
    char postfix[256];
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
    sprintf(postfix, "%s%s", yymmdd, hhmmss);

    printf("yymmss=%s, hhmmss=%s, postfix=%s\n",yymmdd, hhmmss, postfix);
    printf("year: %2d month: %02d day: %d hour: %d min: %d sec: %d\n", year, mon, mday, hour, min, sec);
    return 0;
    
}
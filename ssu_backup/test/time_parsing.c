#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void){
    time_t timer;
    struct tm *cur_time;
    int year, mon, mday, hour, min, sec;

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
    printf("year: %2d month: %02d day: %d hour: %d min: %d sec: %d\n", year, mon, mday, hour, min, sec);
    return 0;
    
}
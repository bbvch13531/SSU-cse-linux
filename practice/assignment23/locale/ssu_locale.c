#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int main(void){
    time_t now;
    struct tm *l_time;
    char string[256];

    setlocale(LC_TIME, "");
    now = time((time_t *)NULL);
    l_time = localtime(&now);
    strftime(string, sizeof(string), "%c", l_time);

    printf("%s\n", string);
    exit(0);
}
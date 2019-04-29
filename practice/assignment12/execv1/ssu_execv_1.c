#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include "calTime.h"

double ssu_maketime(struct timeval *time);
void term_stat(int stat);
void ssu_print_child_info(int stat, struct rusage *rusage);

int main(void){
    pid_t pid;
    int status;

    if((pid = fork()) == 0){
        char *args[]
    exit(0);
}

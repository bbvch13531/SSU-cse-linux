#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "calTime.h"

int main(void){
    struct timeval begin_t, end_t;
    
    gettimeofday(&begin_t, NULL);

    printf("Process ID\t\t= %d\n", getpid());   // 프로세스 id
    printf("Parent process ID\t\t= %d\n", getppid());   // 부모 프로세스 id
    printf("Real user ID\t\t= %d\n", getuid()); // real user id
    printf("Effective user ID\t\t= %d\n", geteuid());   // effective user id
    printf("Real group ID\t\t= %d\n", getgid());    //real group id
    printf("Effective group ID\t\t= %d\n", getegid());  // effective group id

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);
    exit(0);
}
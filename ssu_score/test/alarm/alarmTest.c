#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int signo);
int counter = 0;
int main(int argc, char** argv){
    
    int fd;
    signal( SIGALRM, sigint_handler);

    alarm(3);
    printf("whileTRUE 1\n");
    system("./whileTRUE");
    
    alarm(3);
    printf("whileTRUE 2\n");
    system("./whileTRUE2");
    
    alarm(3);
    printf("whileTRUE 3\n");
    system("./whileTRUE3");

    exit(0);
}
void sigint_handler(int signo){
    printf("alarm %d\n",counter);
    counter++;
    exit(0);
}
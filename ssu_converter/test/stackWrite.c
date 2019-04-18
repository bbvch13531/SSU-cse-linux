#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define EOF -1
#define CHAR 0
#define DIGIT 1
#define OTHERS 2

// string stack

void pop(void);
void push(char*);
char* top(void);
int size(void);
int isEmpty();

int idx=0;
char buf[2000], stk[2000][500];
FILE *fp;

int main(int argc, char **argv){
    
    push("abc");
    push("def");
    
    printf("%s\n",top());
    pop();
    push("ghr");
    printf("%s\n",top());
    pop();
    printf("%s\n",top());
    pop();

    return 0;
}

void pop(void){
    stk[idx-1][0] = 0;
    idx--;
}
void push(char *c){
    strcpy(stk[idx], c);
    idx++;
}
char* top(void){
    return stk[idx-1];
}
int isEmpty(void){
    if(idx == 0) return 1;
    else return 0;
}
int size(void){
    return idx-1;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "stack.h"

stack stk1, stk2;

typedef struct Op{
    char op;
    int rank;
} Op;
int main(void){
    
    char test1[2048] = "pthread_create(&tid2, NULL, &ssu_thread2,NULL) < 0";
    char test2[2048] = "pthread_create(&tid2, NULL, ssu_thread2, NULL) != 0";
    char test11[2048] = "(start = times(&tms_start)) == 0";
    char test22[2048] = "(start=times(&tms_start))==-1 : (start=times(&tms_start))<0";

    char buf1[110][2048], buf2[2048];
    int cnt = 0, len;
    Op op[100]={
        {'+', 0}, {'-', 1},{'(', 2},{')', 3},{'[', 4}, {']', 5}, {'.', 6},{'!', 7}, {'~', 8}, {'*', 9}, {'&', 10},{'/', 11}, 
        {'%', 12},{'<', 13}, {'>', 14},{'=', 15},{'^', 16}, {'|', 17}
    };
    // char ops[100][10] = {
    //     "++", "--", "[", "]", ".", "->", 6
    //     "+", "-", "!", "~", "*", "&", 6
    //     "/", "%%", 2
    //     "<<", ">>", 2
    //     "<", "<=", ">", ">=", 4
    //     "==", "!=", 2
    //     "^", 
    //     "|",
    //     "&&", 
    //     "||", 4
    //     "=", "+=", "-=", "*=", "/=", "%%=", "<<=", ">>=", "&=", "^=", "|=", 11
    //     "," 1
    // };

    
    
    // char text1[50] = "abc+asdf+1+53+4";
    // tok1 = strtok(text1,"+");
    // while(tok1 != NULL){
    //     printf("%s\n",tok1);
    //     tok1 = strtok(NULL, "+");
    // }
    len = strlen(test1);
    int oplen, offset;
    char *i, *start = test1, *end;
    
    for(int j=0; j<40; j++){
        oplen = strlen(op[j].op);

        if((end = strstr(test1, op[j].op)) != NULL){
            //start부터 end까지 잘라서 buf1[cnt]에 넣는다.
            printf("end = %s\n",end);
            memcpy(buf1[cnt], start, end - start);
            printf("start = %s %d\n",start, end - start);            
            // printf("buf = %s\n",buf1[cnt]);
            offset = end - start;
            for(int k=0; k<oplen; k++){
                buf1[cnt][offset +k] = 0;
            }
            start = end;
            cnt++;
        }
    
    }
    for(int j=0; j<cnt; j++){
        printf("%s\n",buf1[j]);
    }
    return 0;
}
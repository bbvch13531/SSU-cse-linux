#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "sys/types.h"
#include "stack.h"

void regexExample(void);
void stackExample(void);
int main(int argc, char** argv){
    
    stackExample();
    regexExample();
    
    exit(0);
}
void regexExample(void){
    char *expression = "a =open(aks||sk&&(a > 10),fp,mode++)afds123";
    char *expression1 = "___ abc123def ___ ghi456 ___";
    char *regexString = "([^a-z]+)([^0-9]+)";
    
    // "([^0-9]+)"; non digit, each character
    // "([^0-9])"; non digit, each word
    
    // "([a-z]+)"; 문자만 읽기.
    // "[a-z]*([0-9]+)([a-z]*)";
    int maxGroup = 10;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroup];
    unsigned int m = 0;
    char *cursor;

    if(regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf("Could not compile regex\n");
        return;
    }

    cursor = expression;
    for(m=0; m<maxGroup; m++){
        if(regexec(&regexCompiled, cursor, maxGroup, groupArray, 0))
            break;
        unsigned int g = 0, offset = 0;
        for(g=0; g<maxGroup; g++){
            if(groupArray[g].rm_so == (size_t)-1){
                break;
            }
            if(g==0){
                offset = groupArray[g].rm_eo;
            }

            char cursorCopy[strlen(cursor) + 1];
            strcpy(cursorCopy, cursor);
            cursorCopy[groupArray[g].rm_eo] = 0;
            printf("Match %u, Group %u: [%2u -%2u]: %s\n", m, g,
             groupArray[g].rm_so, groupArray[g].rm_eo, cursorCopy+groupArray[g].rm_so);
        }
        cursor += offset;
    }
    regfree(&regexCompiled);
    return;
}
void stackExample(void){
    stack s;
    char * asd;
    
    printf("hello stack");
    init(&s);
    push(&s,"123");
    asd = top(&s);    
    printf("%s",asd);

    return;
}
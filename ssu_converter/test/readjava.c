#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
// q1.java를 읽고 문자열을 자르는 테스트
#include <sys/stat.h>
void readtest1(void);

char buf[100][100];
FILE *fp;

int main(int argc, char **argv){
    int n, buflen=0,idx=0;
    char ch;
    char * str;
    char tokens[] = {"() {}.;,\"\n"};
    fp = fopen("../javafile/q1.java", "r");
    
    
    readtest1();
    // while((n = fread(&ch,sizeof(char),1,fp)) > 0){
    //     if(ch == '\n'){
    //         buflen = 0;
    //         idx++;
    //     }
        
    //     buf[idx][buflen] = ch;
    //     buflen++;

    //     // printf("%s",buf);
    //     // if(ch == '\n') break;
    //     // '\n'을 구분자로 읽으면 될듯?
    // }
    // for(int i=0; i<20; i++){
    //     printf("%s",buf[i]);
    // }
    // str = strtok(buf, tokens);
    // while(str != NULL){
    //     printf("%s\n",str);
    //     str = strtok(NULL, tokens);
    // }
    return 0;
}
void readtest1(void){
    char buf1[2000], chbuf[500];
    char ch;
    char * str;
    char tokens[] = {"() {}.;,\"\n"};
    int n, len, chlen;
    while((n = fread(buf1,sizeof(char),2000,fp)) > 0){
        
        // if(ch == '\n') break;
        // '\n'을 구분자로 읽으면 될듯?
    }
    len = strlen(buf1);
    printf("%s\n",buf1);
    chlen = 0;
    for(int i=0; i<len; i++){
        ch = buf1[i];

        // ch가 delimeter인지 확인
        
        chbuf[chlen] = ch;
        chlen++;

        // chbuf가 keyword인지 확인.
        if(){

        }
    }
    // str = strtok(buf1, tokens);
    // while(str != NULL){
    //     printf("tok = %c, %s\n",, str);
    //     str = strtok(NULL, tokens);
    // }
    // strtok로 하면 delimeter이 NULL이 된다.
    // strchr 사용해야함.
}
char delimeters[][10]={
    " ",
    "(",
    ")",
    "{",
    "}",
    "[",
    "]",
    
}
char keywords[][20]={
    "import",
    "public",
    "static",
    "void",
    "main",
    "class",
    "String",
    "Scanner",
    "System",
    "out",
    "in",
    "printf",
    "int",
    "for",
    "if",
    "else",
    "return",
    "final",
    "void",
    "Stack",
    "throws",
    "IOException",
    "File",
    "FileWriter",
    "null"
}
/*
public class q1 q1이름의 c파일을 만들어야 함.
token:
    ' ' 공백
    () 소괄호
    { } 중괄호
    [ ] 대괄호
    .
    ;
    "
    \n 
    연산자들
    +
    =
    <
    %
    !

keywords

"import",
"public",
"static",
"void",
"main",
"class",
"String",
"Scanner",
"System",
"out",
"in",
"printf",
"int",
"for",
"if",
"else",
"return",
"final",
"void",
"Stack",
"throws",
"IOException",
"File",
"FileWriter",
"null"
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
// q1.java를 읽고 문자열을 자르는 테스트
#include <sys/stat.h>

#define EOF -1
#define CHAR 0
#define DIGIT 1
#define OTHERS 2

void readtest1(void);
int readchar(int);
void addchar(char);
char buf[2000];
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
    char chbuf[500];
    char ch;
    char * str;
    char tokens[] = {"() {}.;,\"\n"};
    int n, len, chlen;
    int i = 0;
    while((n = fread(buf,sizeof(char),2000,fp)) > 0){
        
        // if(ch == '\n') break;
        // '\n'을 구분자로 읽으면 될듯?
    }
    len = strlen(buf);
    printf("%s\n",buf);
    chlen = 0;
    

    while(1){
        if((ch = readchar(i)) != EOF){
            if(ch == CHAR){                
                while(1){
                    i++;
                    ch = readchar(i);
                    
                }
            }
            else if(ch == DIGIT){
                
            }
        }
        else{

            break;
        }
    }
    // str = strtok(buf, tokens);
    // while(str != NULL){
    //     printf("tok = %c, %s\n",, str);
    //     str = strtok(NULL, tokens);
    // }
    // strtok로 하면 delimeter이 NULL이 된다.
    // strchr 사용해야함.
}

int readchar(int idx){
    int charType, res;
    char ch;

    ch = buf[idx];
    
    if(isalpha(ch)){
        charType = CHAR;
    }
    else if(isdigit(ch)){
        // digit이 아닐 때까지 읽는다.
        charType = DIGIT;
    }
    else{
        //특수문자

        // if 특수문자이면
        charType = OTHERS;

        // EOF이면
        charType = -1;
    }
    return charType;
}

void addchar(char ch){

}

char delimeters[][10]={
    ' ',
    '(',
    ')',
    '{',
    '}',
    '[',
    ']',
    '.',
    ';',
    ',',
    '\n',
    '+',
    '=',
    '<',
    '%%',   // '%'
    '!',
    '/'
};  //25

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
}   //25
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

대응하는 관계
public static void main(String[] args)
int main(void)

System.out.printf("")
printf("")

AAA = scn.nextInt();
scanf("%d",&AAA);


*/
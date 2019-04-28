#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
// q1.java를 읽고 문자열을 자르는 테스트
#include <sys/stat.h>

#define EOF -1
#define CHAR 0
#define DIGIT 1
#define OTHERS 2

int charType(char);
int isReserved(char *);
void javaToC();

int words;
char buf[2000], word[500];
char cstr[1000][50];
FILE *fp, *wfp;

// 이전에 읽은 string을 비교해야함!!
int main(int argc, char **argv){
    int n, len,buflen,idx=0;
    char ch;
    char *fname = "output.txt";
    char * token;
    fp = fopen("../javafile/q1.java", "r");
    wfp = fopen(fname, "w");
    // fread(buf,sizeof(char),2000,fp);
    // len = strlen(buf);

    // do{
    //     ch = fgetc(fp);
    //     printf("%c",ch);

    // } while(ch != EOF);

    while((ch = fgetc(fp)) != EOF){
        // printf("%c",ch);
        if(charType(ch) == CHAR){

            word[idx++] = ch;
            word[idx] = 0;

            while(1){
                ch = fgetc(fp);
                if(charType(ch) == CHAR || charType(ch) == DIGIT){
                    word[idx] = ch;
                    idx++;
                }
                else{
                    word[idx] = 0;
                    idx = 0;
                    printf("C = %s\n",word);
                    ungetc(ch, fp);
                    fwrite(word, sizeof(char), strlen(word), wfp);
                    
                    strcpy(cstr[words], word);
                    words++;
                    
                    strcat(buf, word);
                    if(isReserved(word) == 1){
                        // printf("Reserved\n");
                    }
                    break;
                }
            }
        }
        else if(charType(ch) == DIGIT){
            word[idx++] = ch;
            word[idx] = 0;

            while(1){
                ch = fgetc(fp);
                if(charType(ch) == DIGIT){
                    word[idx++] = ch;
                    word[idx] = 0;
                }
                else{
                    word[idx] = 0;
                    idx = 0;
                    printf("D = %s\n",word);
                    fwrite(word, sizeof(char), strlen(word), wfp);

                    strcpy(cstr[words], word);
                    words++;
                    
                    strcat(buf, word);
                    break;
                }
            }
        }
        
        else if(charType(ch) == OTHERS){
            word[idx++] = ch;
            word[idx] = 0;
            idx = 0;
            if(ch == '\n'){
                printf("--------------------\n");
            }
            else
                printf("O = %s\n",word);
            fwrite(word, sizeof(char), strlen(word), wfp);
            strcat(buf, word);

            strcpy(cstr[words], word);
            words++;
        }
        else{
            printf("EOF\n");
            break;
            //EOFs
        }
    }

    // \n 으로 잘라서 cstr에 넣기.
    
    // token = strtok(buf, "\n");
    // while(token != NULL){
    //     strcpy(cstr[words], token);
    //     printf("%d : %s\n",words, cstr[words]);
    //     words++;
    //     token = strtok(NULL, "\n");
    // }
    for(int i=0; i<words; i++){
        printf("%s\n",cstr[i]);
    }
    javaToC();
    return 0;
}
void javaToC(void){
    for(int i=0; i<words; i++){
        if(strcmp(cstr[i], "import") == 0){
            if(strcmp(cstr[i+1], "java.util.Scanner") == 0){

            }
            else if(strcmp(cstr[i+1], "java.io.File") == 0){

            }
            else if(strcmp(cstr[i+1], "java.io.IOException") == 0){

            }
            else if(strcmp(cstr[i+1], "java.io.FileWriter") == 0){

            }
        }
    }
}
int charType(char c){
    if(isalpha(c)){
        return CHAR;
    }
    else if(isdigit(c)){
        // digit이 아닐 때까지 읽는다.
        return DIGIT;
    }
    else if(c == -1){
        return EOF;
    }
    else{
        return OTHERS;
    }
}
int isReserved(char *c){
    
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
    };   //25

    for(int i=0; i<25; i++){
        if(strcmp(keywords[i], c) == 0){
            // printf("%s\n",c);
            return 1;
        }
    }
    return 0;
}

/*
import로 시작한다.
    java.util.Scanner
        scanf사용
    java.io.IOException;

    java.io.FileWriter;
        file IO

class 로 시작한다.

public 로 시작한다.
    class
        { 전까지 뒤에 오는 문자가 클래스 이름
    static
        void
            main 
                메인함수

Scanner로 시작한다.
    scn 변수 저장
     = new Scanner(System.in); 이 있는지 확인

int 로 시작
Stack
File
FileWriter
for
if
System.out.printf
    문자열을 저장 후 printf()로 바꾼다. 
return

그 외의 경우는 변수로 시작.
*/
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
int findWord(int line, char *word);
// return index of word

int wordsAtLine[100], lines=0;

char buf[2000], word[500];
char cstr[100][50][50];
FILE *fp, *wfp;

// 이전에 읽은 string을 비교해야함!!
int main(int argc, char **argv){
    int n, len,buflen,idx=0;
    char ch;
    char *fname = "output.txt";
    char * token;
    fp = fopen("../javafile/q2.java", "r");
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
                if(ch == '\n')
                    lines++;
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
                    
                    strcpy(cstr[lines][wordsAtLine[lines]], word);
                    
                    wordsAtLine[lines]++;

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
                if(ch == '\n')
                    lines++;
                if(ch == ' ' || ch == '\t') // get nonspace char
                    continue;
                if(charType(ch) == DIGIT){
                    word[idx++] = ch;
                    word[idx] = 0;
                }
                else{
                    word[idx] = 0;
                    idx = 0;
                    printf("D = %s\n",word);
                    ungetc(ch, fp);
                    fwrite(word, sizeof(char), strlen(word), wfp);

                    strcpy(cstr[lines][wordsAtLine[lines]], word);
                    
                    wordsAtLine[lines]++;
                    
                    strcat(buf, word);
                    break;
                }
                
            }
        }
        
        else if(charType(ch) == OTHERS){
            if(ch == '\n')
                lines++;
            if(ch == ' ' || ch == '\t')
                continue;
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

            strcpy(cstr[lines][wordsAtLine[lines]], word);
                    
            wordsAtLine[lines]++;
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
    // printf("%d\n",lines);
    // for(int j=0; j<lines; j++){
    //     int len = wordsAtLine[j];
    //     for(int i=0; i<len; i++){
    //         printf("%s\n",cstr[j][i]);
    //     }
    //     printf("------------------\n");
    // }
    int inputLine;
    printf("Input line to print :");
    scanf("%d",&inputLine);
    inputLine-=1;
    for(int i=0; i<wordsAtLine[inputLine]; i++){
        printf("%s\n",cstr[inputLine][i]);
    }
    javaToC();
    return 0;
}
void javaToC(void){
    int len, keyIdx;
    char nextWord[50], searchWord[50];
    char filrWriterVar[50], fileVar[50], stackVar[50], scanVar[50];
    for(int i=0; i<lines; i++){
        len = wordsAtLine[i];
        for(int j=0; j<len; j++){
            strcpy(nextWord, cstr[i][j]);   // 처리할 단어 nextWord

            // import 처리
            if(strcmp(nextWord, "import") == 0){   
                // 같은 line에서 특정 헤더 검색
                if(findWord(i, "Scanner") != -1){

                }
                else if (findWord(i, "File") != -1){

                }
                else if(findWord(i, "IOException") != -1){

                }
                else if(findWord(i, "FileWriter") != -1){

                }
                  
            }

            // class 처리
            else if(strcmp(nextWord, "class") == 0){
                
                if(findWord(i, "public") != -1){
                    // public class
                    // cstr[i][j+1] 이 public class 이름
                }
                else{
                    // other class ex) Stack
                    // cstr[i][j+1] 이 class 이름
                }
            }
            
            
            // public method 처리
            else if(strcmp(nextWord, "public") == 0){
                if(findWord(i, "static") != -1 && findWord(i, "void") != -1 && findWord(i, "main") != -1){
                    // main method
                }
                else if(findWord(i, "(") != -1 && findWord(i, ")") != -1){
                    // public method
                }
                else if(findWord(i, "final") != -1 && findWord(i, "static") != -1){
                    // public static final int STACK_SIZE = 10; 처리
                }
            }
            else if(strcmp(nextWord, "Scanner") == 0){
                // 변수이름 cstr[i][j+1]
                // j+2 =
                // j+3 new
                // j+4 Scanner
                // j+5 (
                // j+6 System
                // j+7 .
                // j+8 in
                // j+9 )
            }           
            // Scanner.nextInt()
            else if(strcmp(nextWord, "nextInt") == 0){
            }

            else if(strcmp(nextWord, "int") == 0){
                // 변수이름 cstr[i][j+1]
                
                // if any
                // j+2 =
                // j+3 DIGIT

                // if any
                // j+4 ,
                // j+5 변수이름
                // j+6 DIGIT

                // , 로 계속 이어질 수 있음.
                // ; 읽을 때까지 반복.
            }

            // for
            else if(strcmp(nextWord, "for") == 0){
                // 
            }

            // if
            else if(strcmp(nextWord, "if") == 0){
                
            }
            // else
            else if(strcmp(nextWord, "else") == 0){
                
            }

            // printf
            else if(strcmp(nextWord, "printf") == 0){
                
            }
            // return
            else if(strcmp(nextWord, "return") == 0){
                
            }
            // File
            else if(strcmp(nextWord, "File") == 0){
                
            }
            // FileWriter
            else if(strcmp(nextWord, "FileWriter") == 0){
                // 인자 true, false 확인해야함.
                // 변수이름.
            }
            else if
        }
    }
}
int findWord(int line, char *word){
    // return index of word
    char buf[50];
    
    for(int i=0; i<wordsAtLine[line]; i++){
        strcpy(buf, cstr[line][i]);
        if(strcmp(buf, word) == 0){
            return i;
        }
    }
    return -1;
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>

#define EOF -1
#define CHAR 0
#define DIGIT 1
#define OTHERS 2

int charType(char);
void parsefile(void);



int wordsAtLine[100], lines=0, wline=0;

char buf[2000], word[500];

char cstr[100][100][50]; // 읽어온 string cstr[line개수][word개수][word의 크기]
char wbuf[100][500];    // .c파일에 쓸 write buf[line의 개수][line의 크기]
char filename[50], nextWord[50], searchWord[50];
char stackclassVar[50], filrWriterVar[50], fileVar[50], stackVar[50], scannerVar[50], inputVar[50];

int flag = 0; // opt flag
char targetfilename[50];    // q1.java, q2.java, q3.java in argc[1]

char headerkey[10][20];
char headervalue[10][100];

/*
// [0] FileWriter : fopen   open #include <fcntl.h>
// [1] always. exit #include <stdlib.h>
// [2] always. printf #include <stdio.h>
*/

FILE *fp, *wfp, *cfp;
FILE *hfp;  // header table file pointer
FILE *mfp;  // makefile file pointer


int main(int argc, char **argv){
    int opt;
    // Handling options
    /*
        j
        c
        p
        f
        l
        r
    */
    if(argc <2){
        printf("usage: ./ssu_convert <filename>\n");
        exit(1);
    }
    sprintf(targetfilename, "%s", argv[1]);
    fp = fopen(targetfilename, "r");
    while((opt = getopt(argc, argv, "jcpflr")) != -1){
        switch(opt){
            case 'r':
                break;
            case 'j':
                break;
            case 'c':
                break;
            case 'p':
                break;
            case 'f':
                break;
            case 'l':
                break;
        }
    }
    // 자바파일 읽는다.
    // 파싱한다.
    parsefile();
    for(int i=0; i<lines; i++){
        for(int j=0; j<wordsAtLine[i]; j++){
            printf("%s\n", cstr[i][j]);
        }
    }
    // 버퍼에 넣는다.
    // makefile 만든다
    // C파일 만든다
    // 


    // 옵션 없는 경우
    if(flag == 0){
        printf("%s.c convert Success!\n", targetfilename);
    }
    if(flag == 1){

    }
    exit(0);
}


void parsefile(void){
    char ch;
    int idx = 0;
    while((ch = fgetc(fp)) != EOF){
    // printf("%c",ch);
    if(charType(ch) == CHAR){

        word[idx++] = ch;
        word[idx] = 0;

        while(1){
            ch = fgetc(fp);
            if(ch == '\n'){
                lines++;
                continue;
            }
            if(charType(ch) == CHAR || charType(ch) == DIGIT){
                word[idx] = ch;
                idx++;
            }
            else{
                word[idx] = 0;
                idx = 0;
                ungetc(ch, fp);

                strcpy(cstr[lines][wordsAtLine[lines]], word);
                
                wordsAtLine[lines]++;
                strcat(buf, word);

                break;
            }
        }
    }
    else if(charType(ch) == DIGIT){
        word[idx++] = ch;
        word[idx] = 0;

        while(1){
            ch = fgetc(fp);
            if(ch == '\n'){
                lines++;
                continue;
            }
            
            if(charType(ch) == DIGIT){
                word[idx++] = ch;
                word[idx] = 0;
            }
            else{
                word[idx] = 0;
                idx = 0;
                ungetc(ch, fp);

                strcpy(cstr[lines][wordsAtLine[lines]], word);
                
                wordsAtLine[lines]++;
                strcat(buf, word);
                break;
            }
            
        }
    }
    
    else if(charType(ch) == OTHERS){
        if(ch == '\n'){
            lines++;
            continue;
        }
        
        word[idx++] = ch;
        word[idx] = 0;
        idx = 0;

        strcat(buf, word);

        strcpy(cstr[lines][wordsAtLine[lines]], word);
        wordsAtLine[lines]++;
    }
    else{
        printf("EOF\n");
        break;
        //EOF
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
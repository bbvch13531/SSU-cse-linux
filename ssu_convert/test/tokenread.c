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
void writeC();
void readHeaderTable();
void createMakefile();
int findWord(int line, char *word);
// return index of word

int wordsAtLine[100], lines=0, wline=0;

char buf[2000], word[500];

char cstr[100][100][50]; // 읽어온 string cstr[line개수][word개수][word의 크기]
char wbuf[100][500];    // .c파일에 쓸 write buf[line의 개수][line의 크기]
char filename[50], nextWord[50], searchWord[50];
char stackclassVar[50], filrWriterVar[50], fileVar[50], stackVar[50], scannerVar[50], inputVar[50];

char intvar[5][10];
int intvarinit[5];
int intcnt=0;

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

// 이전에 읽은 string을 비교해야함!!
int main(int argc, char **argv){
    int n, len,buflen,idx=0;
    char ch;
    char *fname = "output.txt";
    char headertable[50] ="headerTable.txt";     
    char * token;

    fp = fopen("../javafile/q3.java", "r");
    wfp = fopen(fname, "w");
    cfp = fopen("test.c", "w");
    hfp = fopen(headertable, "r");
    
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
                    // printf("C = %s\n",word);
                    ungetc(ch, fp);
                    
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
                    // printf("D = %s\n",word);
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
            /*
            if(ch == '\n'){
                printf("--------------------\n");
            }
            else{
                printf("O = %s\n",word);
            }
            */
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
    // printf("Input line to print :");
    // scanf("%d",&inputLine);
    // inputLine-=1;
    // for(int i=0; i<wordsAtLine[inputLine]; i++){
    //     printf("%s\n",cstr[inputLine][i]);
    // }
    readHeaderTable();
    javaToC();
    writeC();
    return 0;
}
void javaToC(void){
    int len, keyIdx;
    int wlen;
    char cmp1[50], cmp2[50], cmp3[50], cmp4[50], cmp5[50], cmp6[50], cmp7[50], cmp8[50], cmp9[50];


    strcpy(headerkey[1], "exit");
    strcpy(headerkey[2], "printf");

    for(int i=0; i<lines; i++){
        len = wordsAtLine[i];

        memset(cmp1, 0, 50);
        memset(cmp2, 0, 50);
        memset(cmp3, 0, 50);
        memset(cmp4, 0, 50);
        memset(cmp5, 0, 50);
        memset(cmp6, 0, 50);
        memset(cmp7, 0, 50);
        memset(cmp8, 0, 50);
        memset(cmp9, 0, 50);

        strcpy(cmp1, cstr[i][0]);
        if(len>=8)
            strncpy(cmp9, cstr[i][8], 50);
        if(len>=7)
            strncpy(cmp8, cstr[i][7], 50);
        if(len>=6)
            strncpy(cmp7, cstr[i][6], 50);
        if(len>=5)
            strncpy(cmp6, cstr[i][5], 50);
        if(len>=4)
            strncpy(cmp5, cstr[i][4], 50);
        if(len>=3)
            strncpy(cmp4, cstr[i][3], 50);
        if(len>=2)
            strncpy(cmp3, cstr[i][2], 50);
        if(len>=1)
            strncpy(cmp2, cstr[i][1], sizeof(cmp2));
        // strstr을 사용하면 현재 키워드의 위치를 알 수 있지만
        // 원하는 단어를 찾기 위해서 parsing이 이후에 필요하다.
        // 지금 구현방법과 크게 달라지지 않을듯.

        printf("%d %d \n1:%s \n2:%s \n3:%s \n4:%s \n5:%s \n6:%s \n7:%s \n8:%s \n9:%s\n", i, len, cmp1, cmp2, cmp3, cmp4, cmp5, cmp6, cmp7, cmp8, cmp9);
        // printf("%d %d\n", i, len);
        
        // cmp1 == import
        if(strcmp(cmp1, "import") == 0){
            if(strcmp(cmp7, "Scanner") == 0){
                strcpy(headerkey[2], "printf");
            }
            else if(strcmp(cmp7, "FileWriter") == 0){
                strcpy(headerkey[0], "open");
            }
        }
        // cmp1 == public
        else if(strcmp(cmp1, "public") == 0){
            // cmp2 == class
            if(strcmp(cmp3, "class") == 0){
                // filename is q1, q2, q3
                strcpy(filename, cmp5);
            }
            // cmp2 == static
            
        }    
        // cmp1 == class
        else if(strcmp(cmp1, "class") == 0){
            // cmp3 == Stack
            if(strcmp(cmp3, "Stack") == 0){
                printf("스택\n");
            }
        }
        else if(strcmp(cmp1, "\t") == 0){

            if(strcmp(cmp2, "public") == 0){
                if(strcmp(cmp4, "static") == 0){
                        // cmp3 == void
                        if(strcmp(cmp6, "void") == 0){
                            // cmp4 == main
                            if(strcmp(cmp8, "main") == 0){
                                // copy int main(void){
                                strcpy(wbuf[wline], "\tint main(void){");
                                printf("%d %d %d\n", i, len, wline);
                                
                                wline++;
                            }
                        }
                    }
                    // cmp2 == int || cmp2 == void. public functions
                    else if(strcmp(cmp4, "int") == 0 || strcmp(cmp4, "void") == 0){

                    }
                    // cmp2 == 'Stack' initializer
                    else if(strcmp(cmp4, stackclassVar) == 0){

                    }  
            }
            // cmp1 == System
            else if(strcmp(cmp2, "\t") == 0){
                if(strcmp(cmp3, "Scanner") == 0){
                    continue;
                }
                else if(strcmp(cmp3, "System") == 0){
                    // cmp3 == out
                    if(strcmp(cmp5, "out") == 0){
                        // cmp5 == printf
                        if(strcmp(cmp7, "printf") == 0){
                            // printf("%s\n", cstr[i][6]);
                            printf("프린트\n");
                            
                            // printf("") 인 경우
                            if(strcmp(cstr[i][8], "\"") == 0){
                                strcat(wbuf[wline], "\t\t");
                                for(int j=6; j<len; j++){
                                    strcat(wbuf[wline], cstr[i][j]);
                                }
                                // printf("프린트\n%s\n",wbuf[wline]);  
                                printf("wbuf = %s\n",wbuf[wline]);
                                                      
                                wline++;
                            }
                            // printf(stack[top] + "") 인 경우
                            else {

                            }
                        }
                    }
                }
                else if(strcmp(cmp9, "nextInt") == 0){
                    printf("스캔에프\n");
                    strcat(wbuf[wline], "\t\tscanf(\"%d\", &");
                    strcat(wbuf[wline], cmp3);
                    strcat(wbuf[wline], ");");

                    
                    wline++;
                }
                // cmp1 == Stack q2 main에서 Stack st = new Stack()하는 부분.
                else if(strcmp(cmp3, "Stack") == 0){

                }
                // File
                else if(strcmp(cmp3, "File") == 0){
                    strcat(wbuf[wline], "\t\tFILE *fp;");
                    wline++;

                    strcat(wbuf[wline], "\t\tchar filename[100] = \"");
                    for(int j=13; j<len-2; j++){
                        strcat(wbuf[wline], cstr[i][j]);
                    }
                    strcat(wbuf[wline], ";");
                    
                    wline++;
                }
                // FileWriter
                else if(strcmp(cmp3, "FileWriter") == 0){
                    // 두번째 인자가 false
                    strcat(wbuf[wline], "\t\tif((fp = fopen(filename, \"");
                    if(strcmp(cstr[i][len-3], "false") == 0){
                        strcat(wbuf[wline], "w\"");
                    }
                    // 두번째 인자가 true
                    else if(strcmp(cstr[i][len-2], "true") == 0){
                        strcat(wbuf[wline], "a\"");
                    }
                    strcat(wbuf[wline], ")) == -1){");
                    wline++;
                    strcat(wbuf[wline], "\t\t\tfprintf(stderr, \"open error for %s\\n\",filename);");
                    wline++;
                    strcat(wbuf[wline], "\t\t\texit(1);");
                    wline++;
                    strcat(wbuf[wline], "\t\t}");
                    wline++;
                    
                }
                // writer.write
                else if(strcmp(cmp5, "write") == 0){
                    int size=0;
                    char strsize[10];
                    strcat(wbuf[wline], "\t\tfwrite(\"");
                    for(int j=7; j<len - 3; j++){
                        size += strlen(cstr[i][j]);
                        strcat(wbuf[wline], cstr[i][j]);
                    }
                    printf("size = %d\n",size);
                    sprintf(strsize, "%d",size-1);
                    strcat(wbuf[wline], "\", 1, ");
                    strcat(wbuf[wline], strsize);
                    strcat(wbuf[wline], ", fp);");
                    wline++;

                }
                //writer.flush
                else if(strcmp(cmp5, "flush") == 0){
                    strcat(wbuf[wline], "\t\tfflush(fp);");
                    wline++;
                }
                else if(strcmp(cmp5, "writer") == 0){
                    for(int j=0; j<len; j++){
                        if(j == 4){
                            strcat(wbuf[wline], "fp");
                        }
                        else if(j == 9){
                            strcat(wbuf[wline], "NULL");
                        }
                        else{
                            strcat(wbuf[wline], cstr[i][j]);
                        }
                    }
                    wline++;
                }
                else if(strcmp(cmp6, "close") == 0){
                    printf("closeclose\n");
                    strcat(wbuf[wline], "\t\t\tfclose(fp);");
                    wline++;
                }
                else if(strcmp(cmp3, "return") == 0){
                    continue;
                }
                else {
                    for(int j=0; j<len; j++){
                        strcat(wbuf[wline], cstr[i][j]);
                    }
                    wline++;
                }
            }
            else{
                strcat(wbuf[wline], "\t\treturn 0;");
                wline++;
                for(int j=0; j<len; j++){
                    strcat(wbuf[wline], cstr[i][j]);
                }
                printf("wbuf = %s\n",wbuf[wline]);
                wline++;
            }
        }

        
        /* comment out
        for(int j=0; j<len; j++){
            strcpy(nextWord, cstr[i][j]);   // 처리할 단어 nextWord
            
            
            
            
            
            // import 처리
            if(strcmp(nextWord, "import") == 0){
                // 같은 line에서 특정 헤더 검색
                if(findWord(i, "Scanner") != -1){
                    strcpy(headerkey[0], "Scanner");
                }
                else if (findWord(i, "File") != -1){
                    strcpy(headerkey[0], "");
                }
                else if(findWord(i, "IOException") != -1){

                }
                else if(findWord(i, "FileWriter") != -1){

                }
                otherflag = 0;
            }

            // class 처리
            else if(strcmp(nextWord, "class") == 0){
                
                if(findWord(i, "public") != -1){
                    // public class
                    // cstr[i][j+1] 이 public class 이름
                    strcpy(filename, cstr[i][j+1]);
                    
                }
                else{
                    // other class ex) Stack
                    // cstr[i][j+1] 이 class 이름
                    strcpy(stackclassVar, cstr[i][j+1]);
                }
                otherflag = 0;
            }
            
            // public method 처리
            else if(strcmp(nextWord, "public") == 0){
                if(findWord(i, "static") != -1 && findWord(i, "void") != -1 && findWord(i, "main") != -1){
                    // main method
                    strcpy(wbuf[wline], "int main(void){");
                    wline++;                    
                    break;
                }
                else if(findWord(i, "(") != -1 && findWord(i, ")") != -1){
                    // public method
                    if(strcmp(stackclassVar, cstr[i][j+1]) == 0){
                    // 생성자인지 확인

                    }
                }
                else if(findWord(i, "final") != -1 && findWord(i, "static") != -1){
                    // public static final int STACK_SIZE = 10; 처리
                }
            }
            else if(strcmp(nextWord, "Scanner") == 0){
                // 변수이름 cstr[i][j+1]
                strcpy(scannerVar, cstr[i][j+1]);

            }           
            // Scanner.nextInt()
            else if(strcmp(nextWord, "nextInt") == 0){
                
                // 스캐너 변수가 일치하는지 확인
                if(strcmp(cstr[i][j-2], scannerVar) == 0){
                    // scanf("")
                    strcpy(inputVar, cstr[i][j-4]);
                    printf("input var is %s %s\n", inputVar, cstr[i][j-4]);

                    // scanf("%d", &inputVar);
                    otherflag = 0;
                }
            }

            // for(int i=1; i<=num; i++){ 를 처리해야함.
            // int가 첫번째 단어일 때만 처리. 그 외엔 continue;
            else if(strcmp(nextWord, "int") == 0){
                if(j!=0)    // for구문 내에서 int 변수 선언한 경우.
                    continue;                
                // 변수이름 cstr[i][j+1]
                
                char ch[10];
                int k = 0; 
                while(strcmp(ch, ";") != 0){                    
                    strcpy(ch, cstr[i][j+k+1]); // 다음 단어를 복사                    
                    if(strcmp(ch, ";") == 0)
                        break;
                    if(strcmp(ch, ",") == 0){   // ch 가 , 인 경우 
                        if(strcmp(cstr[i][j+k-1], "=")){  // 앞에 있는 단어가 [변수이름] = [값] 형태인 경우
                            
                            strcpy(intvar[intcnt], cstr[i][j+k-2]);
                            // 변수 이름 저장

                            intvarinit[intcnt] = atoi(cstr[i][j+k]);
                            // 변수 값 저장
                            intcnt++;
                        }
                        else{   // 앞에 있는 단어가 [변수이름] 형태인 경우
                            strcpy(intvar[intcnt], cstr[i][j+k]);
                            // 변수 이름 저장
                            intcnt++;
                        }
                    }
                    k++;
                }
                otherflag = 0;
                // , 로 계속 이어질 수 있음.
                // [변수이름] = [값] 형태 또는 [변수이름] 형태
                // ; 읽을 때까지 반복.
            }

            // printf
            else if(strcmp(nextWord, "printf") == 0){
                if(strcmp(cstr[i][j+2], "\"") == 0){
                    // + 가 없다면
                    // " "사이를 읽어온다.
                    int k=1;
                    char ch[50];
                    while(1){
                        if(strcmp(cstr[i][j+k+2], "\"") == 0)
                            break;
                        strcat(wbuf[wline], cstr[i][j+k+2]);                        
                    }                    
                }
                else{
                    // + 가 있다면
                    // stack[top]
                    // if(strcmp(cstr[i][j+2], "stack"))
                    // stack[i]
                    // 변수 이름 바뀌면 처리 못한다.
                    // int top 은 무조건 변수이름 top,
                    // int[] stack은 무조건 변수이름 stack으로 고정
                }
                wline++;
                break;
            }
            
            // File
            else if(strcmp(nextWord, "File") == 0){
                
            }
            // FileWriter
            else if(strcmp(nextWord, "FileWriter") == 0){
                // 인자 true, false 확인해야함.
                // 변수이름.
            }
            else{
                
            }
        }
        if(otherflag == 1){
            for(int k=0; k<wordsAtLine; k++)
                strcat(wbuf[wline], cstr[i][k]);
            wline++;
        }
        comment out */

        fputs("\n", cfp);
        printf("\n");
    }
    printf("----------------\n");
    printf("filename : %s\n", filename);
    for(int i=0; i<wline; i++){
        printf("%s\n",wbuf[i]);
    }
}

void readHeaderTable(void){
    char ch;
    char word[10];
    char headerread[100];
    int len=0;
    int firstword = 1;

    while((ch = fgetc(hfp)) != EOF){
        if(firstword == 1){
            // 공백 전까지 글자 입력받아서 word에 저장
            while(ch != ' '){
                word[len] = ch;
                len++;
                ch = fgetc(hfp);
            }
            word[len] = 0;
            firstword = 0;
            len = 0;
            printf("\n");
        }
        else{
            // 개행 전까지 글자 입력받아서 headerread에 저장
            while(ch != '\n'){
                if(ch == '#'){
                    headerread[len] = '\n';
                    len++;  
                }
                headerread[len] = ch;
                len++;
                ch = fgetc(hfp);
                if(ch == -1)
                    break;
            }
            headerread[len] = 0;
            firstword = 1;
            len = 0;
            printf("\n");
            // 개행이면 firstword = 1
        }

        printf("%s %s\n",word,headerread);
        if(strcmp(word, "open") == 0){
            strcpy(headervalue[0], headerread);
        }
        else if(strcmp(word, "exit") == 0){
            strcpy(headervalue[1], headerread);
        }
        if(strcmp(word, "printf") == 0){
            strcpy(headervalue[2], headerread);
        }
        
        
    }
    // 공백 이전까지 글자 읽는다.
    
    // 읽은 단어가
    // open
    // exit
    // printf
}

void writeC(){
    // 헤더 검사해서 #include 추가.
    if(strcmp(headerkey[0], "open") == 0){
        //write headerread[0]
        fwrite(headervalue[0], 1, strlen(headervalue[0]), wfp);
    }
    if(strcmp(headerkey[1], "exit") == 0){
        //write headervalue[1]
        fwrite(headervalue[1], 1, strlen(headervalue[1]), wfp);
    }
    if(strcmp(headerkey[2], "printf") == 0){
        //write headervalue[2]
        fwrite(headervalue[2], 1, strlen(headervalue[2]), wfp);
    }
    fwrite("\n", 1, 1, wfp);
    for(int i=0; i<wline; i++){
        fwrite(wbuf[i], 1, strlen(wbuf[i]), wfp);
        fwrite("\n", 1, 1, wfp);
    }
    createMakefile();
}

void createMakefile(){
    char makefilename[100];
    char writebuf[2000];
    sprintf(makefilename, "%s_Makefile", filename);
    mfp = fopen(makefilename, "w+");
    
    sprintf(writebuf, "%s: %s.c\n\tgcc -o %s.out %s.c", filename, filename, filename, filename);

    fwrite(writebuf, 1, strlen(writebuf), mfp);
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

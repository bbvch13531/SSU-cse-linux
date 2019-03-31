// SSU_20142468 Kyungyoung Heo

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>

#define NAME_LEN 200
#define TIMEOUT 2

typedef struct {
    char name[NAME_LEN];
    int fd;
    int id;
    int type;
} AnsFile;

typedef struct {
    char stdName[NAME_LEN];
    AnsFile file[110];
} StdFile;

typedef struct {
    int tid;
} Thread_Data;

void showHelp(void);
int checkScoreTable(char *pathname);
int selectType(void);
void selectProblemPoint(int scoreType, double* scorePoints);
void fillScoreTable(int csvfd, AnsFile *ansFile, int scoreType, double *scorePoints);

void readDIR(int type, char *pathname);
int strToNum(char *name);
void runStdProgram(char *pathname);
void runAnsProgram(char *pathname);
void printANSProgram(char *pathname);
void printSTDProgram(char *pathname);

int compareResult(char *pathname);
// thread
void *watchdog(void *arg);
void *workerThread(void *arg);
void cleanup(void *arg);

// signal
void sig_handler(int nSigNum);

int flag = 0;   // opt flag
int fd_ans[110]; // ANS/files, STD/num/files의 fd를 저장
char ansDirname[110][200];
int problemNum = 0, studentNum = 0; // number of problem and students
int csvfd; // score_table.csv 's fd
AnsFile ansFile[110];
StdFile stdFile[110];

pthread_t tid, wtid;
int main(int argc, char** argv){
    int opt;
    int scoreType;
    int tmp;
    double scorePoints[110];
    char *student_dir, *answer_dir;
    char tmpstr[200];

    if(argc < 3){
        fprintf(stderr, "Usage : %s <STD_DIR> <ANS_DIR>", argv[0]);
        exit(1);
    }

    student_dir = argv[2];
    answer_dir = argv[3];
    
    printf("STD = %s ANS = %s\n",student_dir, answer_dir);

    while((opt = getopt(argc, argv, "epthc")) != -1){
        switch(opt){
            case 'e':
                flag |= 1;
                
                break;
            case 'p':
                flag |= 2;
                break;
            case 't':
                flag |= 4;
                break;
            case 'h':
                flag |= 8;
                break;
            case 'c':
                flag |= 16;
                break;
            case '?':
                flag |= 32;
                printf("Unknown flag : %c\n", optopt);
                break;
        }
    }
    printf("%x\n",flag);
    
    /*
    if(flag & 1){
        printf("e\n");
    }
    if(flag & 2){
        printf("p\n");
    }
    if(flag & 4){
        printf("t\n");
    }
    if(flag & 8){
        printf("h\n");
        showHelp();
    }
    if(flag & 16){
        printf("c\n");
    }
    */

    //  score_table.csv 파일이 있는지 확인. 없으면 생성 
    
    csvfd = checkScoreTable(answer_dir);
    
    
    readDIR(1, answer_dir);

    // ANS_DIR 읽고 어떤 문제가 있는지 저장 (.txt, .c 구분)
    // readANS(answer_dir);
    
    // for(int i=0; i<problemNum; i++){
    //     printf("%d %s %d %d\n",i, ansFile[i].name, ansFile[i].type, ansFile[i].id);
    // }
    
    readDIR(2, student_dir);

    system("pwd");
    // for(int i=0; i<problemNum; i++){
    //     printf("name: %s type: %d\n",ansFile[i].name, ansFile[i].type);
    // }
    // STD 의 .c파일을 컴파일하고 실행시킴.
    
    // for(int i=0; i<studentNum; i++){
    //     printf("%s\n",stdFile[i].stdName);
    //     for(int j=0; j<problemNum; j++){
    //         printf("%s\n",stdFile[i].file[j].name);
    //     }
    // }

    // runAnsProgram(answer_dir);
    scoreType = selectType();
    selectProblemPoint(scoreType,scorePoints);

    fillScoreTable(csvfd, ansFile, scoreType, scorePoints);

    lseek(csvfd, 0,SEEK_SET);
    char ch;
    while(1){
        
        if(read(csvfd, &ch, 1) > 0){
            putchar(ch);
        }
        else break;
        // printf("%s",buf1);
    }
    // printf("%d",scorePoints[1]);
    
    printf("runAnsProgram end!\n");
    runStdProgram(student_dir);
    
    // ANS와 STD를 비교
    
    compareResult(student_dir);


    
    //  문제 배점 입력
    //  STD, ANS 디렉토리 읽음
    //  .txt면 바로 비교
    //  .c면 컴파일 후 실행, 실행결과를 비교
    //  std의 .c를 컴파일 후 실행파일을 저장, 실행결과를 파일에 저장
    //  ans의 .c파일도 똑같이!
    exit(0);
}

void showHelp(){
    printf("Usage : ssu_score <STUDENTDIR> <TRUEDIR> [OPTION]\n\
            Option :\n\
              -e <DIRNAME>      print error on 'DIRNAME/ID/qname_error.txt' file\n\
              -t <QNAMES>       compile QNAME.C with -lpthread option\n\
              -h                print usage\n\
              -p                print student's score and total average\n\
              -c <IDS>          print ID's score\n");
    return;
}

/*
    Returns score_table.csv file descriptor
    If not exists, create new csv file and return its file descriptor
*/
int checkScoreTable(char *pathname){
    int fd;
    char table[200];
    memcpy(table, pathname, NAME_LEN);
    // printf("scoretable : %s\n",pathname);
    strcat(table, "/score_table.csv");
    printf("checkScoreTable\n");
    system("pwd");
    if((fd = open(table, O_RDWR)) < 0){
        printf("score_table.csv file doens't exist in TRUEDIR!\n");
        if((fd = creat(table, 0644)) < 0){
            fprintf(stderr, "creat error for %s\n", table);
            exit(1);
        }
    }

    
    return fd;
}

int selectType(){
    int type;

    printf("1. input blank question and program question's score. ex) 0.5 1\n");
    printf("2. input all question's score. ex) Input value of 1-1: 0.1\n");
    printf("select type >> ");
    scanf("%d", &type);

    return type;
}

void selectProblemPoint(int scoreType, double scorePoints[]){
    double blank, program;

    // If scoreType is 1, use first two elements of scorePoints
    if(scoreType == 1){
        printf("Input value of blank question : ");
        scanf("%lf", &blank);
        printf("Input value of program question : ");
        scanf("%lf", &program);

        scorePoints[0] = blank;
        scorePoints[1] = program;

    }
    // scoreType is 2, get every problem's scorePoints
    else{
        for(int i=0; i<problemNum; i++){
            printf("Input of %s: \n",ansFile[i].name);
            // scorePoints[i] = i * 0.1;
            scanf("%lf",&scorePoints[i]);
        }
    }

    // for(int i=0; i<problemNum; i++){
    //     printf("%2lf\n",scorePoints[i]);
    // }
}
void fillScoreTable(int csvfd, AnsFile *ansFile, int scoreType, double *scorePoints){
    // csvFileDes 로 열고
    char dtoc[30]="";

    for(int i=0; i<problemNum; i++){
        if(strcmp(ansFile[i].name, "") == 0) continue;
        write(csvfd, ansFile[i].name, strlen(ansFile[i].name));
        write(csvfd, ", ", 2);

        if(scoreType == 1){
            // 빈칸, 프로그램 문제 구분
            if(ansFile[i].type == 1){ // blank
                snprintf(dtoc, 10, "%3lf", scorePoints[0]);
                write(csvfd, dtoc, strlen(dtoc));
                // printf("%s is type %d, score is %lf\n", ansFile[i].name, ansFile[i].type, scorePoints[0]);
            }
            else if (ansFile[i].type == 2){   // program
                snprintf(dtoc, 10, "%3lf", scorePoints[1]);
                write(csvfd, dtoc, strlen(dtoc));
                // printf("%s is type %d, score is %lf\n", ansFile[i].name, ansFile[i].type, scorePoints[1]);
            }
        }
        else{
            snprintf(dtoc, 10, "%3lf", scorePoints[i]);
            write(csvfd, dtoc, strlen(dtoc));
            // printf("%s is type %d, score is %lf\n", ansFile[i].name, ansFile[i].type, scorePoints[i]);
        }
        write(csvfd, "\n",1);
    }
    // ansFIle의 이름 받아와서 행 만들고
    // scoreType에 따라서 scorePoint의 내용을 csv파일에 쓴다.
}
void readDIR(int type, char *pathname){
    struct dirent **namelist1, **namelist2;
    struct stat statbuf1, statbuf2;
    char ansName[50], fileName[50];
    int dircnt=0,filecnt=0, cnt1, cnt2;
    printf("%s\n",pathname);
    
    if((dircnt = scandir(pathname, &namelist1, NULL, alphasort)) == -1){
        fprintf(stderr, "opendir: chdir error for %s\n",pathname);
        printf("%s\n",strerror(errno));
        exit(1);
    }
    if(type == 1){
        problemNum = dircnt;
        // printf("problemNum = %d\n",problemNum);
    }
    else{
        studentNum = dircnt;
    }
    cnt1 = 0;
    for(int i=0; i<dircnt; i++){
        chdir(pathname);
        // system("pwd");
        strcpy(ansName, namelist1[i]->d_name);
        
        if(strcmp(".", ansName) == 0 || strcmp("..", ansName) == 0)
            continue;
        
        if(strcmp(ansName, "score_table.csv") == 0) continue;
        // printf("%s\n",namelist1[i]->d_name);
        if(stat(ansName, &statbuf1) == -1){
            fprintf(stderr, "stat error for %s\n", ansName);
            printf("%s\n",strerror(errno));
            exit(1);
        }
        
        if(S_ISDIR(statbuf1.st_mode)){
            // printf("%s\n",ansName);
            if(type == 1){
                strcpy(ansDirname[i], ansName);
            }
            else {
                strcpy(stdFile[i].stdName, ansName);
            }
            // system("pwd");
            // chdir(ansName);    // change dir to child dir
            if((filecnt = scandir(ansName, &namelist2, NULL, alphasort)) == -1){
                fprintf(stderr, "opendir: chdir error for %s\n",ansName);
                printf("%s\n",strerror(errno));
                exit(1);
            }
            cnt2 = 0;
           
            
           
            for(int j=0; j<filecnt; j++){
                
                strcpy(fileName, namelist2[j]->d_name);
                
                if(strcmp(".", fileName) == 0 || strcmp("..", fileName) == 0)
                continue;
                // if(strstr(fileName, ".stdexe") || strstr(fileName, ".stdout")){
                //     continue;
                // }
                chdir(ansName);
                // system("pwd");
                if(stat(fileName, &statbuf2) == -1){
                    fprintf(stderr, "stat error for %s\n", fileName);
                    printf("%s\n",strerror(errno));
                    exit(1);
                }
                // printf("%s\n",fileName);
                
                if(S_ISREG(statbuf2.st_mode)){
                    if(type == 1){  // ANS_DIR
                        
                        if(strstr(fileName, ".txt")){
                            ansFile[i].fd = open(namelist2[j]->d_name, O_RDONLY);
                            memcpy(ansFile[i].name, namelist2[j]->d_name, NAME_LEN);

                            ansFile[i].id = strToNum(ansFile[i].name);
                            ansFile[i].type = 1;
                        }
                        else if(strstr(fileName, ".c")){  // .c file 
                            ansFile[i].fd = open(namelist2[j]->d_name, O_RDONLY);
                            memcpy(ansFile[i].name, namelist2[j]->d_name, NAME_LEN);
                            ansFile[i].type = 2;

                            ansFile[i].id = strToNum(ansFile[i].name);
                        }
                    }
                    else{       // STD_DIR
                        if(strstr(fileName, ".txt")){
                            stdFile[i].file[j].type = 1;
                        }
                        else if(strstr(fileName, ".c")){  // .c file 
                            stdFile[i].file[j].type = 2;

                        }
                        else{   //others
                            stdFile[i].file[j].type = 3;
                            
                        }
                        // fd_std[j] = open(namelist2[j]->d_name,O_RDONLY);
                        // stdFile[i].file[j].fd = fd_std[j];
                        // printf("%d\n",stdFile[i].file[j].fd);
                        // printf("%s\n",dentry2->d_name );
                        memcpy(stdFile[i].file[j].name, namelist2[j]->d_name, NAME_LEN);
                        
                        // strToNum
                        stdFile[i].file[j].id = strToNum(stdFile[i].file[j].name);
                    }
                }
            }
            if(type == 2){
                
            for(int l=0; l<problemNum; l++){
                for(int k=l; k<problemNum; k++){
                    if(stdFile[i].file[l].id > stdFile[i].file[k].id){

                        AnsFile tmp;
                        tmp = stdFile[i].file[l];
                        stdFile[i].file[l] = stdFile[i].file[k];
                        stdFile[i].file[k] = tmp;
                    }
                }
            }
            
            }
            for(int j=0; j<filecnt; j++){
                free(namelist2[j]);
            }
            free(namelist2);
        }
        chdir("..");
    }
    printf("%d\n",dircnt);
    for(int i=0; i<dircnt; i++){
        free(namelist1[i]);
    }
    free(namelist1);
    
    chdir("..");

    if(type == 1){
        for(int i=0; i<problemNum; i++){
            for(int j=i; j<problemNum; j++){
                if(ansFile[i].id > ansFile[j].id){
                    AnsFile tmp;
                    tmp = ansFile[i];
                    ansFile[i] = ansFile[j];
                    ansFile[j] = tmp;
                }
            
            }
        }
    }
    // ansFile 의 처음 3개는 . .. scroe_table.csv가 들어있음!

    else {
        for(int l=0; l<studentNum; l++){
        for(int k=l; k<studentNum; k++){
            if(strcmp(stdFile[l].stdName, stdFile[k].stdName) > 0){

                char buf[NAME_LEN];
                strcpy(buf,stdFile[l].stdName);
                strcpy(stdFile[l].stdName,stdFile[k].stdName);
                strcpy(stdFile[k].stdName,buf);
            }
        }
    }
    }
}
int strToNum(char *name){
    // 1-1.txt 10-1.c 2-3.txt 5-2.txt를 11, 101, 23, 52 으로 만들고 싶다
    
    int len = strlen(name);
    int idx1, idx2, num=0, res;
    const char *ptr;
    char buf[NAME_LEN];

    if(strstr(name,"-")){
        ptr = strchr(name, '-');
        // 만약 '-'이 없는 경우
        idx1 = ptr - name;
        for(int j=0; j<idx1; j++){
            // printf("%c",name[j]);
            buf[j] = name[j];
        }
        buf[idx1] = 0;
        res = atoi(buf);
        num = res * 10;

        ptr = strchr(name, '.');
        idx2 = ptr - name;   // 
        for(int j=idx1+1; j<idx2; j++){
            // printf("%c",name[j]);
            buf[j-idx1-1] = name[j];
        }
        buf[idx2 - idx1 - 1] = 0;
        res = atoi(buf);
        num += res;
    }
    else {
        ptr = strchr(name, '.');
        idx1 = ptr - name;
        for(int j=0; j<idx1; j++){
            // printf("%c",name[j]);
            buf[j] = name[j];
        }
        buf[idx1] = 0;
        res = atoi(buf);
        num = res * 10;
    }
    // printf("  res1 = %d  ", res);

   
    // printf("  res2 = %d\n", res);
    // printf("num = %d\n",num);
    return num;
}

void runStdProgram(char *pathname){
    sigset_t sigset;
    char cmd[50], buf1[50], buf2[50], problemName[50];
    char fileerror[50];
    int fd,len, fd_err;
    off_t errorSize;

    system("pwd");
    chdir(pathname);

    // setup main thread signal

    signal(SIGALRM, sig_handler);
    // sigemptyset(&sigset);
    // sigaddset(&sigset, SIGALRM);
    // sigprocmask(SIG_BLOCK, &sigset, NULL);

    // pthread_sigmask(SIG_BLOCK, &sigset, NULL);

    // pthread_create(&wtid, NULL, (void *)watchdog, NULL);

    for(int i=0; i<studentNum; i++){
        for(int j=0; j<problemNum; j++){
            if(stdFile[i].file[j].type ==2){
                printf("runStdProgram in %s %s\n", stdFile[i].stdName, stdFile[i].file[j].name);

               
                memset(buf1, 0, 50);
                memset(buf2, 0, 50);
                memset(cmd, 0, 50);
                
                strcpy(cmd, "gcc -o ");
                // printf("%s %s\n", stdFile[i].stdName, stdFile[i].file[j].name);
                // fd of c file in std dir
                fd = stdFile[i].file[j].fd;
                chdir(stdFile[i].stdName);
                
                strcpy(buf1, stdFile[i].file[j].name);

                strcpy(buf2, buf1);
                len = strlen(buf1);
                // printf("%s %s %s %s\n",stdFile[i].file[j].name, buf1, buf2, cmd);
                buf1[len-2] = 0;
                strcpy(problemName, buf1);  // problemName
                strcpy(fileerror, buf1);

                strcat(buf1, ".stdexe ");
                strcat(cmd, buf1);
                strcat(cmd, buf2);
                // printf("cmd = %s\n",cmd);

                strcat(cmd, " -lpthread"); // -lpthread option
                
                
                strcat(fileerror, "_error.txt");
                
                if((fd_err = open(fileerror, O_RDWR|O_CREAT|O_TRUNC, 0644)) < 0){
                    fprintf(stderr,"open error for test.txt\n");
                    printf("%s\n",strerror(errno));
                    exit(1);
                }
                // 에러는 fd_err
                dup2(fd_err, 2);
                
                // 컴파일 에러 처리해야함..
                system(cmd);

                errorSize = lseek(fd_err, 0, SEEK_END);
                
                if(errorSize == 0){
                    char rmcmd[50];
                    strcpy(rmcmd, "rm ");
                    strcat(rmcmd, fileerror);
                    system(rmcmd);
                }

                alarm(TIMEOUT);

                pthread_create(&tid, NULL, (void *)workerThread, (void *)problemName);

                pthread_join(tid, NULL);

                // 만약 에러가 나지 않으면 실행 후 결과를 파일에 출력
                // printSTDProgram(problemName);
                // 에러가 나면 에러파일 생성 후 결과를 파일에 출력

                chdir("..");
            }
        }
    }
    chdir("..");
    // printf("runSTDprogrma ends!\n");

    // pthread_join(wtid, NULL);
}
void runAnsProgram(char *pathname){
    struct dirent *dentry1, *dentry2;
    struct stat statbuf1, statbuf2;
    char filename1[NAME_LEN], filename2[NAME_LEN];
    DIR *dirp1, *dirp2;
    
    char curdir[200], buf[1024];
    char cmd[50], buf1[50], buf2[50], ansName[50];
    int fd,len,i=0;

    if((dirp1 = opendir(pathname)) == NULL || chdir(pathname) == -1){
        fprintf(stderr, "opendir: chdir error for %s\n",pathname);
        printf("%s\n",strerror(errno));
        exit(1);
    }

    while((dentry1 = readdir(dirp1)) != NULL){
        if(dentry1->d_ino == 0)
            continue;

        memcpy(filename1, dentry1->d_name, NAME_LEN);
        strcpy(ansDirname[i], filename1);
        if(stat(filename1, &statbuf1) == -1){
            fprintf(stderr, "stat error for %s\n", filename1);
            printf("%s\n",strerror(errno));
            exit(1);
        }
        // printf("runAnsProgram dir %s\n",filename1);
        if(S_ISDIR(statbuf1.st_mode)){  // if directory
            if(strncmp(".", filename1, 1) == 0 || strncmp("..", filename1, 2) == 0)
                continue;
            if((dirp2 = opendir(filename1)) == NULL){
                fprintf(stderr, "opendir error for %s\n", filename2);
                printf("%s\n",strerror(errno));
                exit(1);
            }
            if(strcmp(filename1, "score_table.csv") == 0) continue;
            chdir(filename1);    // change dir to child dir
            // system("pwd");

            
            while((dentry2 = readdir(dirp2)) != NULL){
                if(dentry1->d_ino == 0)
                    continue;
                memcpy(filename2, dentry2->d_name, NAME_LEN); 

                if(strncmp(".", filename2, 1) == 0 || strncmp("..", filename2, 2) == 0)
                    continue;
                // printf("%s\n",filename2);
                
                if(stat(filename2, &statbuf2) == -1){
                    fprintf(stderr, "stat error for %s\n", filename2);
                    printf("%s\n",strerror(errno));
                    exit(1);
                }
            
                if(S_ISREG(statbuf2.st_mode)){
                    printf("%s\n",filename2);
                    if(strstr(filename2, ".c")){
                        // printf("runAnsProgram file in %s\n", filename2);

                        memset(buf1, 0, 50);
                        memset(buf2, 0, 50);
                        memset(cmd, 0, 50);
                        
                        strcpy(cmd, "gcc -o ");

                        // fd of c file in ans dir
                        fd = ansFile[i].fd;
                        
                        strcpy(buf1, filename2);

                        strcpy(buf2, buf1);
                        len = strlen(buf1);
                        // printf("%s %s %s %s\n",filename2, buf1, buf2, cmd);
                        buf1[len-2] = 0;
                        
                        strcpy(ansName, buf1);
                        strcat(buf1, ".stdexe ");
                        strcat(cmd, buf1);
                        strcat(cmd, buf2);
                        // printf("cmd = %s\n",cmd);
                        
                        strcat(cmd, " -lpthread");   // -lpthread opt
                        system(cmd);
                        // system("pwd");
                        
                        // 실행 후 결과를 파일에 출력
                        printANSProgram(ansName);
                        // 에러가 나면 에러파일 생성 후 결과를 파일에 출력
                        i++;
                    }
                }
            }
            if(closedir(dirp2) == 0){
                // printf("closedir dirp2\n");
            }
            chdir("..");
            if(dentry1->d_ino == 0) continue;
        }
    }
    
    // problemNum = i;
    if(closedir(dirp1) == 0){
        // printf("closedir dirp1\n");
    }
    chdir("..");
   
}

void printANSProgram(char *pathname){
    char buf[50]="./", fileout[50];
    int fd, saved_stdout;
    system("pwd");

    strcpy(fileout, pathname);
    strcat(fileout, ".stdout");

    // printf("printAnsProgram %s\n",fileout);
    if((fd = open(fileout, O_RDWR|O_CREAT|O_TRUNC, 0644)) < 0){
        fprintf(stderr,"open error for test.txt\n");
        printf("%s\n",strerror(errno));
        exit(1);
    }

    strcat(buf, pathname);
    strcat(buf, ".stdexe");
    saved_stdout = dup(1);
    dup2(fd, 1);
    // printf("fd = %d\n",fd);
    // printf("printAnsProgram buf = %s\n",buf);
    system(buf);

    dup2(saved_stdout, 1);
}

void printSTDProgram(char *pathname){
    char cmd[50] = "./", fileout[50];
    int fd_out, saved_stdout;
    // system("pwd");
    
    strcpy(fileout, pathname);
    strcat(fileout, ".stdout");

    if((fd_out = open(fileout, O_RDWR|O_CREAT|O_TRUNC, 0644)) < 0){
        fprintf(stderr,"open error for test.txt\n");
        printf("%s\n",strerror(errno));
        exit(1);
    }

    strcat(cmd, pathname);
    strcat(cmd, ".stdexe");

    saved_stdout = dup(1);
    dup2(fd_out, 1);

    // 에러 생기면 dup2 로 에러파일에 출력
    system(cmd);
    dup2(saved_stdout, 1);
}

int compareResult(char *pathname){
    //fd_ans를 읽어서 pathname(STD)와 비교한다.
    struct dirent **namelist1, **namelist2;
    struct stat statbuf1, statbuf2;
    char ansName[50], fileName[50], buf1[2048], buf2[2048],ch;
    int dircnt=0, filecnt=0, len;
    int fd_std[110];
    double probPoints[110];

    int offsetLine[110]={0,}, lineCnt=0, offset=0;

    chdir(pathname);
    system("pwd");


    // read score_table.csv
    // 배열에 문제번호의 배점을 저장
    // filename과 일치하는 이름의 배점을 가져온다.
    // 맞으면 += score


    
    // while((len = read(csvfd, buf1, 2)) > 0){
    //     if(strcmp(buf1, "\n") == 0){
    //         offsetLine[lineCnt] = offset;
    //         lineCnt++;
    //     }
    //     offset++;
    //     printf("%s",buf1);
    //     // 1바이트씩 읽으면서 "\n"의 offset을 offsetLine[lineCnt]에 저장한다.
    //     // lseek한다.
    // }

    printf("csvfd = %d\n",csvfd);
    

    for(int i=0; i<studentNum; i++){
        // STD[i] open
        // if(strlen(stdFile[i].stdName) == 0 ) continue;
        if( strcmp(stdFile[i].stdName, "") == 0 ) continue;
        strcpy(ansName, stdFile[i].stdName);
        chdir(ansName);
        // system("pwd");
        for(int j=0; j<problemNum; j++){
        // printf("compareResult %s\n",stdFile[i].file[j].name);
            if(strcmp(stdFile[i].file[j].name, "") == 0) continue;
            
            strcpy(fileName, stdFile[i].file[j].name);
            // printf("STD fileName = %s\n", fileName);

            for(int k=0; k<problemNum; k++){
                if(strcmp(fileName, ansFile[k].name) == 0){

                    // 요기에 score_table.csv
                    // read(fd_ans, buf2, 2048);
                    // printf("%s\n",buf2);
                    // printf("ANS = %10s, STD = %10s in  %10s\n",ansFile[k].name, fileName, stdFile[i].stdName);
                    if(strstr(fileName, ".txt")){
                        // matchBlank
                    }
                    else if(strstr(fileName, ".c")){
                        // match .stdout
                        // 요기에 ANS.stdout과 STD.stdout을 보내서 비교한다.
                    }
                    
                }
            }

            if((fd_std[j] = open(fileName, O_RDONLY)) < 0){
                fprintf(stderr, "open error for %s\n",fileName);
                printf("%s\n",strerror(errno));
                exit(1);
            }
            close(fd_std[j]);   // close fd_std[j]. 매우 중요함. Too many open files 를 보고 싶지 않다면 close 할 것.
            
            
            // printf("before read\n");
            
            // while((len = read(fd_std[j], buf1, 2048)) > 0){
            //     printf("%s\n",buf1);
            // }

            // ANS[j] open
            // STD[i][j] open

            // if .txt, matchBlank

            // else .c, match .stdout

            // if correct, find score_table.csv and score ++

        }
        chdir("..");
        // close STD[i]
        // printf("20190000 is finished... score is 46.8\n");
    }
}

void *watchdog(void *arg){
    sigset_t alrm_sigs;
    int nErrno, nSigNum;
    int flag = 0;
    int cnt=0;

    sigemptyset(&alrm_sigs);
    sigaddset(&alrm_sigs, SIGALRM);

    while(1){
        if(flag == 1){
            flag = 0;
        }
        if( cnt == 3) break;
        nErrno = sigwait(&alrm_sigs, &nSigNum);
        if(nErrno > 0){
            perror("sigwait error\n");
            return NULL;
        }
        // signal no. 에 따라서 signal handler 함수 호출 혹은 종료
        switch(nSigNum){
            case SIGALRM:
                // printf("[signal SIGALRM]\n");
                sig_handler(nSigNum);
            default:
                flag = 1;
                break;
        }
        cnt++;
    }
    pthread_exit(0);
    // printf("watchdog ends!\n");
}
void *workerThread(void *arg){
    int saved_stdout;
    char *pathname;
    pathname = (char *)arg;
    
    saved_stdout = dup(1);

    pthread_cleanup_push(cleanup, (void *)saved_stdout);

    // printf("workerThread tid = %u\n",pthread_self());
    
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    printSTDProgram(pathname);
    
    // printf("workerThread ends!\n");

    pthread_cleanup_pop(0);
}

void sig_handler(int nSigNum){
    // printf("Thread tid : %lu\n",pthread_self());

    pthread_cancel(tid);
    // pthread_kill(tid, SIGKILL);
    // syscall(SYS_tkill, tidNum, 9);
    // tkill(tidNum, SIGTERM);
}
void cleanup(void *arg){
    int saved_stdout = (int) arg;
    dup2(saved_stdout, 1);
    // printf("thread ends!\nalarm starts!\n");
    // alarm(3);
}

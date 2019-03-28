// SSU_20142468 Kyungyoung Heo

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define NAME_LEN 200

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

void showHelp(void);
int checkScoreTable(char *pathname);
int selectType(void);
void selectProblemPoint(int scoreType, double* scorePoints);
void fillScoreTable(int csvfd, AnsFile *ansFile, int scoreType, double *scorePoints);
void readANS(char *pathname);
void readSTD(char *pathname);
void readSTDfd(char *stdpath, char *pathname);
int strToNum(char *name);
void runStdProgram(char *pathname);
void printStdProgram(char *pathname);
int fd_ans[110], fd_std[110]; // ANS/files, STD/num/files의 fd를 저장
char stdDirname[110][200];
int problemNum = 0, studentNum = 0; // number of problem and students

AnsFile ansFile[110];
StdFile stdFile[110];

int main(int argc, char** argv){
    int opt;
    int flag = 0, scoreType;
    int csvfd;
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
    
    printf("%s %s",student_dir, answer_dir);

    while((opt = getopt(argc, argv, "epthc")) == -1){
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
    
    // ANS_DIR 읽고 어떤 문제가 있는지 저장 (.txt, .c 구분)
    readANS(answer_dir);
    
    // for(int i=0; i<problemNum; i++){
    //     printf("%s %d\n",ansFile[i].name, ansFile[i].type);
    // }

    readSTD(student_dir);
    
    // readSTDfd(student_dir, );
    runStdProgram(student_dir);

    // for(int i=0; i<studentNum; i++){
    //     printf("%s\n",stdFile[i].stdName);
    //     for(int j=0; j<10; j++){
    //         printf("%s\n",stdFile[i].file[j].name);
    //     }
    // }

    // scoreType = selectType();
    // selectProblemPoint(scoreType,scorePoints);

    // fillScoreTable(csvfd, ansFile, scoreType, scorePoints);


    // printf("%d",scorePoints[1]);
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
    char dtoc[20]="";

    for(int i=0; i<problemNum; i++){
        
            write(csvfd, ansFile[i].name, strlen(ansFile[i].name));
            write(csvfd, ", ", 2);
        
        
            if(scoreType == 1){
                // 빈칸, 프로그램 문제 구분
                if(ansFile[i].type == 1){ // blank
                    snprintf(dtoc, 10, "%3lf", scorePoints[0]);                                   
                    write(csvfd, dtoc, strlen(dtoc));
                    // printf("%s is type %d, score is %lf\n", ansFile[i].name, ansFile[i].type, scorePoints[0]);
                }
                else{   // program
                    snprintf(dtoc, 10, "%3lf", scorePoints[1]);
                    write(csvfd, dtoc, strlen(dtoc));
                    printf("%s is type %d, score is %lf\n", ansFile[i].name, ansFile[i].type, scorePoints[1]);
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

void readANS(char *pathname){
    struct dirent *dentry1, *dentry2;
    struct stat statbuf1, statbuf2;
    char filename1[200], filename2[200];
    char curdir[200], buf[1024];
    int i = 0;
    DIR *dirp1, *dirp2;

    if((dirp1 = opendir(pathname)) == NULL || chdir(pathname) == -1){
        fprintf(stderr, "opendir: chdir error for %s\n",pathname);
        exit(1);
    }

    while((dentry1 = readdir(dirp1)) != NULL){
        if(dentry1->d_ino == 0)
            continue;
    
        memcpy(filename1, dentry1->d_name, NAME_LEN);

        if(stat(filename1, &statbuf1) == -1){
            fprintf(stderr, "stat error for %s\n", filename1);
            exit(1);
        }

        if(S_ISDIR(statbuf1.st_mode)){  // if directory
            if(strncmp(".", filename1, 1) == 0 || strncmp("..", filename1, 2) == 0)
                continue;
            if((dirp2 = opendir(filename1)) == NULL){
                fprintf(stderr, "opendir error for %s\n", filename2);
                exit(1);
            }
            if(strcmp(filename1, "score_table.csv") == 0) continue;
            chdir(filename1);    // change dir to child dir

            while((dentry2 = readdir(dirp2)) != NULL){
                if(dentry1->d_ino == 0)
                    continue;
                memcpy(filename2, dentry2->d_name, NAME_LEN); 

                if(strncmp(".", filename2, 1) == 0 || strncmp("..", filename2, 2) == 0)
                    continue;
                // printf("%s\n",filename2);
                
                if(stat(filename2, &statbuf2) == -1){
                    fprintf(stderr, "stat error for %s\n", filename2);
                    exit(1);
                }

                if(S_ISREG(statbuf2.st_mode)){
                    // printf("%s\n",filename2);
                    
                    fd_ans[i] = open(dentry2->d_name,O_RDONLY);
                    ansFile[i].fd = fd_ans[i];
                                    
                    memcpy(ansFile[i].name, dentry2->d_name, NAME_LEN);
                    
                    // strToNum
                    ansFile[i].id = strToNum(ansFile[i].name);

                    // while(read(fd_ans[i], buf, 1024)){
                    //     // printf("%s\n",buf);
                    // }
                    

                    // .txt file
                    if(strstr(filename2, ".txt")){
                        ansFile[i].type = 1;
                    }
                    else {  // .c file 
                        ansFile[i].type = 2;
                    }
                     i++;
                }
            }
            closedir(dirp2);
            chdir("..");
            if(dentry1->d_ino == 0) continue;
        }
    }
    problemNum = i;
    closedir(dirp1);
    chdir("..");

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

void readSTD(char *pathname){
    struct dirent *dentry1, *dentry2;
    struct stat statbuf1, statbuf2;
    char filename1[200], filename2[200];
    char curdir[200], buf[1024];
    int i = 0, j = 0;
    DIR *dirp1, *dirp2;

    if((dirp1 = opendir(pathname)) == NULL || chdir(pathname) == -1){
        fprintf(stderr, "opendir: chdir error for %s\n",pathname);
        exit(1);
    }

    while((dentry1 = readdir(dirp1)) != NULL){
        if(dentry1->d_ino == 0)
            continue;
        memcpy(filename1, dentry1->d_name, NAME_LEN);
        if(strcmp(filename1, "score_table.csv") == 0) continue;
        memcpy(stdDirname[i], filename1, NAME_LEN);
        memcpy(stdFile[i].stdName, stdDirname[i], NAME_LEN);
        // printf("%s\n",filename1);
        if(stat(filename1, &statbuf1) == -1){
            fprintf(stderr, "stat error for %s\n", filename1);
            perror("stat error: ");
            exit(1);
        }

        if(S_ISDIR(statbuf1.st_mode)){  // if directory
            if(strncmp(".", filename1, 1) == 0 || strncmp("..", filename1, 2) == 0)
                continue;
            
            if((dirp2 = opendir(filename1)) == NULL){
                fprintf(stderr, "opendir error for %s\n", filename1);
                exit(1);
            }
            
            chdir(filename1);
            printf("%15s\n",filename1);
            readSTDfd(pathname, filename1);
            j=0;
            while((dentry2 = readdir(dirp2)) != NULL){
                if(dentry2->d_ino == 0)
                    continue;
                memcpy(filename2, dentry2->d_name, NAME_LEN); 

                if(strncmp(".", filename2, 1) == 0 || strncmp("..", filename2, 2) == 0)
                    continue;
                // printf("%s\n",filename2);
                
                if(stat(filename2, &statbuf2) == -1){
                    fprintf(stderr, "stat error for %s\n", filename2);
                    exit(1);
                }

                if(S_ISREG(statbuf2.st_mode)){
                    // printf("%s\n",filename2);
                    
                    fd_std[j] = open(dentry2->d_name,O_RDONLY);
                    // stdFile[i].file[j].fd = fd_std[j];
                    // printf("%d\n",stdFile[i].file[j].fd);
                    // printf("%s\n",dentry2->d_name );
                    memcpy(stdFile[i].file[j].name, dentry2->d_name, NAME_LEN);
                    
                    // strToNum
                    stdFile[i].file[j].id = strToNum(stdFile[i].file[j].name);
                    // printf("%s %d\n",stdFile[i].file[j].name, stdFile[i].file[j].id);
                    // while(read(fd_std[i][j], buf, 1024)){
                    //     printf("%s\n",buf);
                    // }
                        
                    // .txt file
                    if(strstr(filename2, ".txt")){
                        stdFile[i].file[j].type = 1;
                    }
                    else {  // .c file 
                        stdFile[i].file[j].type = 2;
                    }
                }
                
                j++;
            }
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
            closedir(dirp2);
            chdir("..");
            if(dentry1->d_ino == 0) continue;
            i++;
        }
    }
    
    studentNum = i;
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
    closedir(dirp1);
}

// STD dirpath 와 20190000 dirpath, return fd of dirpathname
void readSTDfd(char *stdpath, char *pathname){
    struct dirent *dentry;
    struct stat statbuf;
    char filename[200];
    char buf[1024];
    DIR *dirp;
    int i = 0;
    chdir("..");
    if((dirp = opendir(pathname)) == NULL){
        fprintf(stderr, "opendir error for %s\n", pathname);
        exit(1);
    }
    chdir(pathname);
    // printf("%15s\n",pathname);


    while((dentry = readdir(dirp)) != NULL){
        if(dentry->d_ino == 0)
            continue;
        memcpy(filename, dentry->d_name, NAME_LEN);

        if(strncmp(".", filename, 1) == 0 || strncmp("..", filename, 2) == 0)
            continue;
        // printf("%s\n",filename);
        
        if(stat(filename, &statbuf) == -1){
            fprintf(stderr, "stat error for %s\n", filename);
            printf("errno = %s\n",strerror(errno));
            exit(1);
        }
        if(S_ISREG(statbuf.st_mode)){
            // printf("%s\n",filename2);
            
            fd_std[i] = open(dentry->d_name,O_RDONLY);
            // printf("%d\n",stdFile[i].file[j].fd);
            // printf("%s\n",dentry->d_name );

            // printf("%s %d\n",stdFile[i].file[j].name, stdFile[i].file[j].id);
            // while(read(fd_std[i], buf, 1024)){
            //     printf("%s\n",buf);
            // }
        }
        i++;
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

//

void runStdProgram(char *pathname){
    char cmd[50], buf1[50], buf2[50];
    int fd,len;

    // system("pwd");

    for(int i=0; i<5; i++){
        for(int j=0; j<problemNum; j++){
            if(stdFile[i].file[j].type ==2){
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
                buf1[len-2] = 0;
                strcat(buf1, ".stdexe ");

                strcat(cmd, buf1);
                strcat(cmd, buf2);
                printf("cmd = %s\n",cmd);
                system(cmd);
                // system("pwd");
                // printStdProgram(buf1);
                chdir("..");
            }
        }
    }
}

void printStdProgram(char *pathname){
    system("pwd");
}
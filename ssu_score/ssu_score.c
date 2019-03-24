// SSU_20142468 Kyungyoung Heo

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void showHelp(void);
int checkScoreTable(char *pathname);
char* readFiles(char *pathname);
int selectType(void);
int* selectProblemPoint(int scoreType);
int main(int argc, char** argv){
    int opt;
    int flag = 0, scoreType;
    int csvFileDes;
    int *scorePoints;
    char *student_dir, *trueset_dir;
    char *fileNames;

    if(argc < 3){
        fprintf(stderr, "Usage : %s <STD_DIR> <ANS_DIR>", argv[0]);
        exit(1);
    }

    student_dir = argv[2];
    trueset_dir = argv[3];
    
    printf("%s %s",student_dir, trueset_dir);

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
    csvFileDes = checkScoreTable(trueset_dir);
    // ANS_DIR 읽고 어떤 문제가 있는지 저장 (.txt, .c 구분)
    filenames = readFiles(trueset_dir);
    scoreType = selectType();
    scorePoints = selectProblemPoint(scoreType);
    printf("%d",scorePoints[1]);
    //  문제 배점 입력
    //  STD, ANS 디렉토리 읽음
    //  .txt면 바로 비교
    //  .c면 컴파일 후 실행, 실행결과를 비교
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
    // printf("scoretable : %s\n",pathname);
    strcat(pathname, "/score_table.csv");

    if((fd = open(pathname, O_RDWR)) < 0){
        printf("score_table.csv file doens't exist in TRUEDIR!\n");
        if((fd = creat(pathname, 0666)) < 0){
            fprintf(stderr, "creat error for %s\n", pathname);
            exit(1);
        }
    }

    return fd;
}

/*
    Read files in pathname and verify type of problems
*/
char* readFiles(char *pathname){

}

int selectType(){
    int type;

    printf("1. input blank question and program question's score. ex) 0.5 1\n");
    printf("2. input all question's score. ex) Input value of 1-1: 0.1\n");
    printf("select type >> ");
    scanf("%d", &type);

    return type;
}

int* selectProblemPoint(int scoreType){
    int blank, program;
    int scorePoints[110];

    // If scoreType is 1, use first two elements of scorePoints
    if(scoreType == 1){
        printf("Input value of blank question : ");
        scanf("%d", &blank);
        printf("Input value of program question : ");
        scanf("%d", &program);

        scorePoints[0] = blank;
        scorePoints[1] = program;

    }
    /*
    else{

    }
    */
    return scorePoints;
}

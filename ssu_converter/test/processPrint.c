#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// 프로세스 생성해서 한줄씩 프린트, 터미널 clear하는 테스트
char javafile[30][100], cfile[30][100];
int main(void){
    pid_t pid;
    int status, ret_val;
    FILE *javafp, *cfp;
    int javasize, csize;

    javafp = fopen("../javafile/q1.java", "r");
    cfp = fopen("./q1.c", "r");

    fseek(javafp, 0, SEEK_END);
    javasize = ftell(javafp);
    rewind(javafp);

    fseek(cfp, 0, SEEK_END);
    csize = ftell(cfp);
    rewind(cfp);
    
    printf("%d %d\n", javasize, csize);
    char ch;
    int i=0, javaline=0, cline=0;
    while((ch = fgetc(javafp)) != EOF){
        javafile[javaline][i] = ch;
        i++;
        if(ch == '\n'){
            javafile[javaline][i] = 0;
            javaline ++;
            i=0;
        }
    }
    javafile[javaline][i] = 0;
    i = 0;
    
    while((ch = fgetc(cfp)) != EOF){
        cfile[cline][i] = ch;
        i++;
        if(ch == '\n'){
            cfile[cline][i] = ch;
            cline ++;
            i=0;
        }
    }
    cfile[cline][i] = 0;
    

    // fread(javafile, 1, javasize, javafp);
    // fread(cfile, 1, csize, cfp);
    for(int j=0; j<javaline; j++){
        system("clear");

        if((pid = fork()) == 0){    // 자식 프로세스
            for(int k=0; k<j; k++){
                printf("%s", javafile[k]);
            }
            sleep(1);
            exit(0);
        }
        else if(pid > 0){
            for(int k=0; k<j; k++){
                printf("%s", cfile[k]);
            }
            ret_val = wait(&status);
        }
    }

        // printf("%s\n%s\n",javafile, cfile);
    return 0;
}
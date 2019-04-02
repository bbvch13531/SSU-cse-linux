#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


char targs[10][50], cargs[10][50];

void handle(char opt,int argc, char **argv, int optind, char* optarg);
int main(int argc, char **argv){
    
    int opt;
    int flag=0;
    char file_name[50], cpyoptarg[50], STD[50], ANS[50];
    while((opt = getopt(argc, argv, "e:pt:hc:")) != -1){
        memset(cpyoptarg, 0, sizeof(cpyoptarg));

        switch(opt){
            case 'e':
                flag |= 1;
                strcpy(cpyoptarg, optarg);
                handle('e', argc, argv, optind, cpyoptarg);
                //optarg : <error>, optind : 처리 안된 인덱스. 
                // printf("optarg = %s optind = %d, argv[optind] = %s\n",optarg, optind,argv[optind]);
                for(int i=optind; i<argc; i++){
                    printf("argv[i] = %s  ",argv[i]);
                }
                // e처리 함수에 optarg와 optind를 pass
                // optind--;             
                break;
            case 'p':
                flag |= 2;
                handle('p', argc, argv, optind, cpyoptarg);
                break;
            case 't':
                flag |= 4;
                
                strcpy(cpyoptarg, optarg);
                handle('t', argc, argv, optind, cpyoptarg);

                printf("optarg = %s optind = %d\n",optarg, optind);
                
                break;
            case 'h':
                flag |= 8;
                strcpy(cpyoptarg, optarg);
                handle('h', argc, argv, optind, cpyoptarg);
                break;

            case 'c':
                flag |= 16;
                strcpy(cpyoptarg, optarg);
                handle('c', argc, argv, optind, cpyoptarg);
                break;
            case '?':
                flag |= 32;
                printf("Unknown flag\n");
                break;
        }
    }
    printf("---------------\n");
    if(flag == 0){      // no option
        if(argc != 3){
            fprintf(stderr, "Usage : %s <STD_DIR> <ANS_DIR>", argv[0]);
            exit(1);
       }
    }
    
    else{
        if(flag & 1){
            // memcpy(file_name, optarg, strlen(optarg));
            // -e 는 인자 1개만.
            // 만약 argv[optind-1] 와 switch 에서 받은 optarg가 다르면 에러.
        
            // printf("only one argv %s\n",argv[optind-1]);
            
            for(int i=optind; i<argc; i++){
                printf("%s\n",argv[i]);
            }
        }
        
        if(flag & 2){
            printf("p\n");
            printf("no argv %s\n",argv[optind]);
            // -p 는 인자 없음

        }
        if(flag & 4){
            printf("t\n");
            // -t 이후 5개 인자까지만 처리
            for(int i=0; i<5; i++){
                printf("targs : %s\n",targs[i]);
            }
        }
        if(flag & 8){
            printf("h\n");
            // -h 는 인자 없음
        }
        if(flag & 16){
            printf("c\n");
            // -c 이후 5개 인자까지만 처리
            for(int i=0; i<5; i++){
                printf("cargs : %s\n",cargs[i]);
            }
        }
        // 인자 여러개 받을 수 있는 옵션 :-t -c 5개로 제한
    }
    exit(0);
}


void handle(char opt,int argc, char** argv, int optind, char* optarg){
    int maxArg = 0;
    printf("optind = %d, optarg = %s\n",optind, optarg);
    if(opt == 'e'){
        // 이전 argv와 현재 optarg가 다르면 (처리되지 않은 인자가 있으면)
        // 인자가 1개가 아니면 error

        // argv[optind] 가 NULL이나 -phct가 아니면 에러!
        if(optind == argc || strchr(argv[optind],'-')){
            printf("VALID -e option\n");
        }
        else{
            printf("INVALID -e option\n");
        }
        // printf("%s %s\n", argv[optind], optarg);
        if(strcmp(argv[optind-1], optarg) != 0){
            printf("-e error\n");
        }
    }
    else if(opt == 'p'){
        printf("argv[optind] = %s optind = %d argc = %d\n",argv[optind], optind, argc);
        if(optind == argc || strstr(argv[optind], "-")){
            printf("VALID -p option\n");
        }
        else{
            printf("INVALID -p option\n");
        }
    }
    else if(opt == 't'){
        // for( ;optind < argc && *argv[optind] != '-'; optind++){
        //     if(maxArg == 4) break;
        //     printf("%s\n",argv[optind]);
        //     maxArg ++;
        // }
        strcpy(targs[0], optarg);
        for(int i=optind; i<argc && *argv[i] != '-'; i++){
            if(maxArg == 4) break;
            // printf("%s\n",argv[i]);
            int j = i - optind;
            strcpy(targs[j+1], argv[i]);
            maxArg ++;
        }
    }
    else if(opt == 'h'){

    }
    else if(opt == 'c'){
        strcpy(cargs[0], optarg);
        for(int i=optind; i<argc && *argv[i] != '-'; i++){
            if(maxArg == 4) break;
            // printf("%s\n",argv[i]);
            int j = i - optind;
            strcpy(cargs[j+1], argv[i]);
            maxArg ++;
        }
    }
}
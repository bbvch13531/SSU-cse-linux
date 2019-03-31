#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
    
    int opt;
    int flag=0;
    char file_name[50];

    while((opt = getopt(argc, argv, "e:pt:hc:")) != -1){

        switch(opt){
            case 'e':
                flag |= 1;

                printf("optarg = %s optind = %d, argv[optind] = %s\n",optarg, optind,argv[optind]);
                // 만약 e
                // e처리 함수에 optarg와 optind를 pass
                // optind--;             
                break;
            case 'p':
                flag |= 2;
                break;
            case 't':
                flag |= 4;
                
                printf("optarg = %s optind = %d\n",optarg, optind);
                int maxArg = 0;
                for( ;optind < argc && *argv[optind] != '-'; optind++){
                    if(maxArg == 4) break;
                    printf("%s\n",argv[optind]);
                    maxArg ++;
                }
                
                break;
            case 'h':
                flag |= 8;
                break;
            case 'c':
                flag |= 16;
                break;
            case '?':
                flag |= 32;
                printf("Unknown flag\n");
                if(opt == 'e'){
                    printf("opt error\n");
                }
                break;
        }
    }
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
        }
        if(flag & 8){
            printf("h\n");
            // -h 는 인자 없음
        }
        if(flag & 16){
            printf("c\n");
            // -c 이후 5개 인자까지만 처리
        }
        // 인자 여러개 받을 수 있는 옵션 :-t -c 5개로 제한
    }
    exit(0);
}


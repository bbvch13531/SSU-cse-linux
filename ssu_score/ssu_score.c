#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv){
    int opt;
    int flag = 0;
    char *student_dir, *trueset_dir;

    student_dir = argv[1];
    trueset_dir = argv[2];
    
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
    // e
    if(flag & 1){
        printf("e\n");
    } 
    if(flag & 2){
        printf("p\n");
    }
    if(flag & 4){
        printf("t\n");
    }

    exit(0);
}
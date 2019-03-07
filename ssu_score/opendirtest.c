#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h> // DIR
#include <errno.h> // errno

#define DIRECTORY_SIZE MAXNAMLEN

int main(int argc, char** argv){
    
    // 가변인자로 들어온 디렉터리1(STD_DIR), 디렉터리2(ANS_DIR)를 가져온다.
    // dir1과 dir2 내부의 디렉터리와 파일을 모두 출력한다.
    // 디렉터리가 있으면 그 내부를 탐색해서 내부의 디렉터리, 파일을 모두 출력.

    struct dirent *dentry;
    struct stat statbuf;
    char filename[DIRECTORY_SIZE+1];
    DIR *dirp1, *dirp2;

    if(argc < 3){
        fprintf(stderr, "Usage : %s <STD_DIR> <ANS_DIR>", argv[0]);
        exit(1);
    }

    if((dirp1 = opendir(argv[1])) == NULL || chdir(argv[1]) == -1){
        fprintf(stderr, "opendir : chdir error");
        exit(1);
    }

    while((dentry = readdir(dirp1)) != NULL){
        if(dentry->d_ino == 0)
            continue;
        memcpy(filename, dentry->d_name, DIRECTORY_SIZE);

        if(stat(filename, &statbuf) == -1){
            fprintf(stderr, "stat error for %s %x\n", filename, statbuf.st_mode);
            perror("stat err");
            break;
        }

        if((statbuf.st_mode & S_IFMT) == S_IFREG){
            printf("%-14s\n",filename);
        }
        else {
            printf("%-14s is directory\n",filename);
        }
    }

    // while((dentry = readdir(dirp2)) != NULL){
    //     if(dentry->d_ino == 0)
    //         continue;
    //     memcpy(filename, dentry->d_name, DIRECTORY_SIZE);

    //     if(stat(filename, &statbuf) == -1){
    //         fprintf(stderr, "stat error for %s %d\n", filename, statbuf.st_mode);
    //         perror("Error : ");
    //         break;
    //     }

    //     if((statbuf.st_mode & S_IFMT) == S_IFREG){
    //         printf("%-14s\n",filename);
    //     }
    //     else {
    //         printf("%-14s\n",filename);
    //     }
    // }
    exit(0);
}
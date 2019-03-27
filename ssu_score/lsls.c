#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DIRECTORY_SIZE MAXNAMLEN

int cnt = 0;
char * files[10000];
void _ls(char* chdpos,int depth);
int main(int argc,char* argv[]){
    if(argc>3){
        perror("Usage: : lsls [Directory] \n");
        exit(EXIT_FAILURE);
    }

    char* position;

    struct dirent *dentry1, *dentry2;
    struct stat statbuf1, statbuf2;
    char filename[DIRECTORY_SIZE+1];
    char curdir[10000], buf[10000];
    DIR *dirp1, *dirp2;

    printf("argc : %d\n",argc);
    if((dirp1 = opendir(argv[1])) == NULL || chdir(argv[1]) == -1){
        fprintf(stderr, "opendir : chdir error");
        exit(1);
    }
    
    while((dentry1 = readdir(dirp1)) != NULL){
        
        if(getcwd(curdir, sizeof(curdir)) != NULL){
            // printf("cur dir = %s\n",curdir);
        }
        if(dentry1->d_ino == 0)
            continue;
        memcpy(filename, dentry1->d_name, DIRECTORY_SIZE);

        if(stat(filename, &statbuf1) == -1){
            fprintf(stderr, "stat error for %s %x\n", filename, statbuf1.st_mode);
            perror("stat err");
            break;
        }

        if((statbuf1.st_mode & S_IFMT) == S_IFREG){
            printf("%-20s is file\n",filename);
        }

        else {
            // printf("%-20s is directory\n",filename);
            if(strncmp(".",dentry1->d_name,1) == 0 ||
                    strncmp("..",dentry1->d_name,2) == 0) //.과 ..은 출력x
                continue;
            // _ls(filename,0);
            if((dirp2 = opendir(filename)) == NULL){
                perror("Can not open directory..\n");
                exit(EXIT_FAILURE);
            }
            chdir(filename);
            while((dentry2 = readdir(dirp2)) != NULL){
                 if(strncmp(".",dentry2->d_name,1) == 0 ||
                    strncmp("..",dentry2->d_name,2) == 0) //.과 ..은 출력x
                    continue;
                if(dentry2->d_ino == 0)
                    continue;
                printf("%s\n",dentry2->d_name);
                if(stat(dentry2->d_name, &statbuf2) == -1){
                    fprintf(stderr, "stat error for %s %x\n", filename, statbuf2.st_mode);
                    perror("stat error: ");
                    break;
                }
                if((statbuf2.st_mode & S_IFMT) == S_IFREG){
                    // printf("%-14s\n",filename);

                    // output .txt files
                    if(strstr(dentry2->d_name, ".txt")){

                        int fd = open(dentry2->d_name,O_RDONLY);
                        while(read(fd, buf, 1024)){
                            printf("%s\n",buf);
                        }
                    }
                    /* .c files
                    else{

                    {
                    */
                }
            }
            chdir("..");
        }
    }

    for(int i=0; i<cnt; i++){
        printf("%d : %s\n", i, files[i]);
    }
    // position = argv[1];   // 메인함수는 디렉토리 목록을 출력할 위치를
            // 인자로 받아 _ls 함수의 매개변수로 전달하는 일만 수행합니다.
    exit(0);
}
void _ls(char* chdpos,int depth){  //depth는 처음 0이고, 디렉토리 출력중 새로운 디렉토리를 만나면
                                           //depth를 증가시켜 재귀적으로 함수를 다시 호출합니다.
    DIR *dp;                 // 실제 파일을 가리키는 포인터
    struct dirent *dir;     // 포인터가 가리키는 정보(i-node, name 등..)를 저장하는 구조체
    struct stat stat;        // device, uid, gid, size, time 등등 더 자세한 내용을 담는 구조체
    printf("ls: %s\n",chdpos);
    
    if( (dp=opendir(chdpos)) == NULL){
        perror("Can not open directory..\n");
        exit(EXIT_FAILURE);
    }
    chdir(chdpos);   //_ls에 넘겨진 위치인자 chdpos로 이동
    while(dir = readdir(dp)){
        memset(&stat,0,sizeof(struct stat));
        lstat(dir->d_name,&stat);  //dirent 구조체를 이용하여 아래 목록들을 출력합니다.
        if(S_ISDIR(stat.st_mode)){  //만약 디렉토리라면
            if(strncmp(".",dir->d_name,1) == 0 ||
                    strncmp("..",dir->d_name,2) == 0) //.과 ..은 출력x
                continue;
            printf("%*s%s/ \n",depth,"",dir->d_name);
            _ls(dir->d_name,depth+4);  //디렉토리라면 그 안으로 또 들어갑니다. 재귀형식입니다.
        }
        else{
            printf("filename is %s \n",dir->d_name);
            files[cnt] = dir->d_name;   
            cnt++;
        }
    }
    
    if(chdir("..") >=0){
        // printf("Change chdir to ..\n");
    }
    closedir(dp);
}
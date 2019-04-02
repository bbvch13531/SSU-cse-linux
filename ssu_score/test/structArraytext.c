#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define NAME_LEN 200

typedef struct {
    char name[NAME_LEN];
    int fd;
    int id;
} AnsFile;

typedef struct {
    char stdName[NAME_LEN];
    AnsFile file[110];
} StdFile;

AnsFile ansFile[110];
StdFile stdFile[110];

int main(){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            stdFile[i].file[j].fd = i*10+j;
        }
    }

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            printf("%d\n",stdFile[i].file[j].fd);
        }
    }
    exit(0);
}
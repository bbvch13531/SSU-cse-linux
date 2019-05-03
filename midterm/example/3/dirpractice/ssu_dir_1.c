// 인자로 주어진 디렉토리 읽는 예제
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define DIR_SIZE MAXNAMLEN

int main(int argc, char *argv[]){
    struct dirent *dentry;
    struct stat statbuf;
    DIR * dirp;

	char fname[DIR_SIZE];

    if(argc <2){
        fprintf(stderr, "usage: \n");
        exit(1);
    }
    if((dirp = opendir(argv[1])) == NULL || chdir(argv[1]) == -1){
		fprintf(stderr, "opendir error\n");
		exit(1);
	}
	
	while((dentry = readdir(dirp)) != NULL){
		if(dentry->d_ino == 0)	continue;
		
		memcpy(fname, dentry->d_name, DIR_SIZE);

		if(stat(fname, &statbuf) == -1){
			fprintf(stderr, "stat error for %s\n",fname);
			exit(1);
		}
		
		if(S_ISREG(statbuf.st_mode)){
			printf("%-14s %ld\n", fname, statbuf.st_size);
		}
		else{
			printf("%-14s\n", fname);
		}

	}
    exit(0);
}

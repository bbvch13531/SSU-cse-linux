#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void search_directory(char *dir);
int main(int argc, char*argv[]){
	
	if(argc < 2){
		fprintf(stderr, "usage:\n");
		exit(1);
	}

	search_directory(argv[1]);
	exit(0);
}

void search_directory(char *dir){
	struct dirent *dentry;
	struct stat statbuf;
	char cwd[1024];
	char pathname[1024];
	DIR *dirp;

	chdir(dir);
	getcwd(cwd, 1024);
	printf("cwd = %s\n",cwd);
	system("pwd");
	if(lstat(cwd, &statbuf) < 0){
		fprintf(stderr, "lstat error\n");
		exit(1);
	}

	if(!S_ISDIR(statbuf.st_mode)){
		printf("file : %s/%s\n", cwd, dentry->d_name);
		return;
	}
	if(S_ISREG(statbuf.st_mode)){
		return ;
	}
	printf("name : %s\n", cwd);
	if((dirp = opendir(dir)) == NULL){
		fprintf(stderr, "opendir error %s \n", dir);
		system("pwd");
		exit(1);
	}
	
	while((dentry = readdir(dirp)) != NULL){
		if(strcmp(dentry->d_name, ".") && strcmp(dentry->d_name, "..")){
			printf("hello\n");
			strcpy(pathname, dir);
			strcat(pathname, "/");
			strcat(pathname, dentry->d_name);
			search_directory(pathname);			
		}
	}
	chdir("..");
}

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void sear_dir(char *dir ){
	struct stat statbuf;
	DIR *dirp;
	char cwd[1024];
	struct dirent *dentry;

	getcwd(cwd, 1024);

	if(lstat(dir, &statbuf) < 0){
		exit(1);
	}

	if(!S_ISDIR(statbuf.st_mode)){
		printf("%s/%s\n", cwd, dentry->d_name);
		return ;
	}

	if((dirp = opendir(dir)) == NULL){
		exit(1);
	}

	chdir(dir);

	while((dentry = readdir(dirp)) != NULL){
		if(dentry->d_ino == 0)
			continue;
		if(strcmp(dentry->d_name, ".") && strcmp(dentry->d_name, "..")){
			sear_dir(dentry->d_name);
		}
	}
	chdir(cwd);
}

int main(int argc, char *argv[]){
	struct dirent *dentry;
	if(argc <2){
		exit(1);
	}
	sear_dir(argv[1]);
}

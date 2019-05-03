// do grep 예제
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define MAX_SIZE 1024

#ifdef LINE_MAX
#define LINE_MAX 2048
#endif

int ssu_do_grep();
void ssu_make_grep(int argc, char *argv[]);

char *pathname;
char cmd[MAX_SIZE], grep_cmd[MAX_SIZE];

int main(int argc, char *argv[]){
	
	if(argc < 2){
		fprintf(stderr, "usage:\n");
		exit(1);
	}
	if(pathmax == 0){
		if((pathmax = pathconf("/", _PC_PATH_MAX)) < 0)
			pathmax = MAX_SIZE;
		else
			pathmax++;
	}
	if((pathname = (char*) malloc(pathmax+1)) == NULL){
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	strcpy(pathname, argv[argc-1]);

	ssu_make_grep(argc, argv);
	ssu_do_grep();

	exit(0);
}

int ssu_do_grep(){
	DIR * dirp;
	struct dirent *dentry;
	struct stat statbuf;
	char *ptr;

	if(lstat(pathname, &statbuf)<0){
		fprintf(stderr, "lstat error\n");
		return 0;
	}

	if(S_ISDIR(statbuf.st_mode) == 0){
		sprintf(cmd, "%s %s", grep_cmd, pathname);
		printf("%s : \n", pathname);
		system(cmd);
		return 0;
	}

	ptr = pathname + strlen(pathname);
	*ptr++ = '/';
	*ptr = '\0';

	if((dirp = opendir(pathname)) == NULL){
		fprintf(stderr, "opendir error\n");
		return 0;
	}

	while((dentry = readdir(dirp)) != NULL){
		if(strcmp(dentry->d_name, ".") && strcmp(dentry->d_name, "..")){
				strcpy(ptr, dentry->d_name);

				if(ssu_do_grep() < 0)
					break;
		}
	}
	ptr[-1] = 0;	// 마지막 '/'를 지운다. 없어도 상관 ㄴ
	closedir(dirp);

	return 0;	
}


void ssu_make_grep(int argc, char *argv[]){
	strcpy(grep_cmd, "grep");

	for(int i=1; i<argc-1; i++){
		strcat(grep_cmd, " ");
		strcat(grep_cmd, argv[i]);
	}
}

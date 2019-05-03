// symlink와 그 링크를 따라간 파일의 종류를 출력하는 예제인듯.
// readlink로 심볼릭 링크와 연결된 파일을 open
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

void print_file_type(struct stat *statbuf);
int main(int argc, char* argv[]){
	char *fname = "symlink";
	char dest[1024];
	DIR *dp;
	struct stat statbuf;
	struct dirent dentry;

	readlink(fname, dest, 1024);

	if(lstat(dest, &statbuf) < 0){
		fprintf(stderr, "lstat error\n");
		exit(1);
	}
	print_file_type(&statbuf);

	if(lstat(fname, &statbuf) < 0){
		fprintf(stderr, "lstat error\n");
		exit(1);
	}
	print_file_type(&statbuf);


	exit(0);
}
void print_file_type(struct stat *sb){
	char *str;
	if(S_ISREG(sb->st_mode))
		str = "regular";
	else if(S_ISDIR(sb->st_mode))
		str = "directory";
	else if(S_ISSOCK(sb->st_mode))
		str = "socket";
	else if(S_ISFIFO(sb->st_mode))
		str = "FIFO";
	else if(S_ISBLK(sb->st_mode))
		str = "block special";
	else if(S_ISCHR(sb->st_mode))
		str = "character special";
	else if(S_ISLNK(sb->st_mode))
		str = "symbolic link";
	else 
		str = "unknown mode";

	printf("%s\n",str);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char*argv[]){
	
	if(argc != 3){
		fprintf(stderr, "usage :\n");
		exit(1);
	}
	link(argv[1], argv[2]);
	unlink(argv[1]);
	exit(0);
}


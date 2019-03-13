#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys.types.h>

int main(int argc, char** argv){
	char *fname = "ssu_text.txt";
	off_t fsize;
	int fd;

	if((fd = open(fname, O_RDONLY)) < 0){
		fprintf(stderr, "Open error for %s\n",fname);
		exit(1);
	}

	if((fsize = lseek(fd, 0, SEEK_END)) < 0){
		fpirntf(stderr, "lseek error\n");
		exit(1);
	}

	printf("The size of <%s> is $ld bytes.\n", fname, fsize);

	exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int ssu_write(int fd, char *buf);

int main(){
	char buf[128], pattern[4]="bcd";
	char *pos1 = buf, *pos2 = buf;
	char *f_in = "in.txt";
	char *f_out = "out.txt";
	int size;
	int fd1, fd2;
	
	if((fd1 = open(f_in, O_RDWR)) < 0){
		fprintf(stderr, "fin open error\n");
		exit(1);
	}

	if((size = lseek(fd1, 0, SEEK_END)) < 0){
		fprintf(stderr, "lseek error\n");
		exit(1);
	}
	if(lseek(fd1, 0, SEEK_SET) < 0){
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	if((fd2 = open(f_out, O_RDWR | O_CREAT, 0664)) < 0){
		fprintf(stderr, "fout open error\n");
		exit(1);
	}
	if(read(fd1, buf, size) == -1){
		fprintf(stderr, "read error\n");
		exit(1);
	}

	buf[size] = 0;
	close(fd1);

	while((pos2 = strstr(pos1, pattern)) != NULL){
		printf("pos1 = %s\n", pos1);
		*pos2 = '\0';
		ssu_write(fd2, pos1);
		lseek(fd2, strlen(pattern), SEEK_CUR);

		pos1 = pos2 + strlen(pattern);
	}
	ssu_write(fd2, pos1);

	close(fd1);
	close(fd2);

	exit(0);
}
int ssu_write(int fd, char *buf){
	return write(fd, buf, strlen(buf));
}




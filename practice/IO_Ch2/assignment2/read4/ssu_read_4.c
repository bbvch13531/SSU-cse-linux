#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000
#define TABLE_SIZE 128
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    struct timeval begin_t, end_t;
    static struct {
        long offset;
        int length;
    } table [TABLE_SIZE];

    char buf[BUFFER_SIZE];
    long offset;
    int entry, i, length, fd;

    gettimeofday(&begin_t, NULL);
    if(argc < 2){
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        exit(1);
    }

    if((fd = open(argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n",argv[1]);
        exit(1);
    }

    entry = 0;
    offset = 0;

    while((length = read(fd, buf, BUFFER_SIZE)) > 0){   // fd에서 사이즈만큼 읽고 buf에 저장
        for(i = 0; i < length; i++){
            table[entry].length++;      // 엔트리의 length 증가
            offset++;

            if(buf[i] == '\n')
                table[++entry].offset = offset;     // \n 만나면 offset 설정 후 엔트리 증가
        }
    }

    #ifdef DEBUG    // 디버그 모드일 때 실행
        for(i = 0; i < entry; i++){
            printf("%d : %ld, %d\n", i+1, table[i].offset, table[i].length);
        }
    #endif
        while(1){
            printf("Enter line number : ");
            scanf("%d", &length);

            if(--length < 0)
                break;
            
            lseek(fd, table[length].offset, 0);
            if(read(fd, buf, table[length].length) <= 0){
                continue;
            }

            buf[table[length].length] = '\0';
            printf("%s",buf);
        }
    close(fd);
    gettimeofday(&end_t, NULL);

	end_t.tv_sec -= begin_t.tv_sec;
	if(end_t.tv_usec < begin_t.tv_usec){
		end_t.tv_sec--;
		end_t.tv_usec += SEC_TO_MICRO;
	}
	end_t.tv_usec -= begin_t.tv_usec;
	printf("Runtime: %ld:%ld\n",end_t.tv_sec, end_t.tv_usec);
    exit(0);
}
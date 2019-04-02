#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
int compareFiles(int fd1, int fd2){
    // 대소문자, 공백 허용
    char ch1, ch2;
    int isSame = 0, res1, res2;
    // ch1 : ANS, ch2 : STD

    while(1){
        
        printf("isSame1 = %d\n",isSame);
        if((res1 = read(fd1, &ch1, 1)) > 0 && (res2 = read(fd2, &ch2, 1)) > 0){
            isSame = 0;
            if(ch1 == ' '){
                while(1){
                    read(fd1, &ch1, 1);
                    if(ch1 != ' ')
                        break;
                }
            }
            if(ch2 == ' '){
                while(1){
                    read(fd2, &ch2, 1);
                    if(ch2 != ' ')
                        break;
                }
            }
            printf("%c %c\n",ch1,ch2);
            if(isalpha(ch1) && isalpha(ch2)){
                if(ch1 == ch2 || ch1 + 32 == ch2 || ch1 - 32 == ch2){
                    isSame = 1;
                }
            }
            else{
                if(ch1 == ch2){
                    isSame = 1;
                }
            }
        }
        printf("isSame2 = %d\n",isSame);
        
        if(res1 == 0 || res2 == 0){
            if(isSame == 1)
                return 1;
            else
                return 0;
        }
        printf("isSame3 = %d\n",isSame);
        if(isSame == 0){
            break;
        }
    }
    if(isSame == 1){
        return 1;
    }
    else{
        printf("wrong\n");
        return 0;
    }
}

int main(void){
    int res;
    int fd1, fd2;
    fd1 = open("1.txt", O_RDONLY);
    fd2 = open("2.txt", O_RDONLY);
    res = compareFiles(fd1, fd2);
    printf("res = %d\n",res);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "student.h"

STUDENT std;

STUDENT data[14]={
    {"20190001", "aaaa", "aa", "a", "aa", "aa", "aa"},
    {"20190002", "bbbb", "bb", "b", "bb", "bb", "bb"},
    {"20190004", "cccc", "cc", "c", "cc", "cc", "cc"},
    {"20190005", "dddd", "dd", "d", "dd", "dd", "dd"},
    {"20190006", "eeee", "ee", "e", "ee", "ee", "ee"},
    {"20190007", "ffff", "ff", "f", "ff", "ff", "ff"},
    {"20190008", "gggg", "gg", "g", "gg", "gg", "gg"},
    {"20190009", "hhhh", "hh", "h", "hh", "hh", "hh"},
    {"20190014", "iiii", "ii", "i", "ii", "ii", "ii"},
    {"20190025", "jjjj", "jj", "j", "jj", "jj", "jj"},
    {"20190046", "kkkk", "kk", "k", "kk", "kk", "kk"},
    {"20190057", "llll", "ll", "l", "ll", "ll", "ll"},
    {"20190068", "mmmm", "mm", "m", "mm", "mm", "mm"},
    {"20190019", "nnnn", "nn", "n", "nn", "nn", "nn"}
};

int main(void){
    FILE *fp;
    STUDENT std1;
    char id[11], name[21], addr[31], year[2], dept[20], phone[16], email[26];
    int len, cnt=0;

    fp = fopen("student.dat", "w+");
    
    /*
    while(1){
        printf("%dth STUDENT id(11)/name(21)/addr(31)/year(2)/dept(20)/phone(16)/email(26) : ", cnt+1);
        scanf("%s", std.id);
        if(strcmp(std.id, "-1") == 0){
            break;
        }
        scanf("%s %s %s %s %s %s", std.name, std.addr, std.year, std.dept, std.phone, std.email);
        fwrite(&std, 120, 1, fp);
        cnt++;
    }
    */
    for(int i=0; i<14; i++){
        fwrite(&data[i], 120, 1, fp);
    }
    printf("Input ends\n");

    fseek(fp, 0, SEEK_SET);
    printf("file pointer:%d\n",ftell(fp));

    for(int i=0; i<14; i++){
        fread(&std1, 120, 1, fp);

        printf("%s %s %s %s %s %s %s\n", std1.id, std1.name, std1.addr, std1.year, std1.dept, std1.phone, std1.email);
    }
    

    return 0;
}
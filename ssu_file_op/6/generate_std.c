#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "student.h"

STUDENT std;
int main(void){
    FILE *fp;
    STUDENT std1;
    char id[11], name[21], addr[31], year[2], dept[20], phone[16], email[26];
    int len, cnt=0;

    fp = fopen("student.dat", "w+");
    
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
    printf("Input ends\n");

    fseek(fp, 0, SEEK_SET);
    printf("file pointer:%d\n",ftell(fp));

    for(int i=0; i<cnt; i++){
        fread(&std1, 120, 1, fp);

        printf("%s %s %s %s %s %s %s\n", std1.id, std1.name, std1.addr, std1.year, std1.dept, std1.phone, std1.email);
    }
    

    return 0;
}
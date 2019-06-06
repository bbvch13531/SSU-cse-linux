#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "student.h"

#define N 17
#define M 23

STUDENT std;

STUDENT data1[N]={
    {"20190001", "aaaa", "aa", "a", "aa", "aa", "aa"},
    {"20190002", "bbbb", "bb", "b", "bb", "bb", "bb"},
    {"20190004", "cccc", "cc", "c", "cc", "cc", "cc"},
    {"20190005", "dddd", "dd", "d", "dd", "dd", "dd"},
    {"20190006", "eeee", "ee", "e", "ee", "ee", "ee"},
    {"20190007", "ffff", "ff", "f", "ff", "ff", "ff"},  // % 23 == 18
    {"20190008", "gggg", "gg", "g", "gg", "gg", "gg"},
    {"20190009", "hhhh", "hh", "h", "hh", "hh", "hh"},  // % 23 == 22
    {"20190014", "iiii", "ii", "i", "ii", "ii", "ii"},  // % 23 == 18
    {"20190025", "jjjj", "jj", "j", "jj", "jj", "jj"},
    {"20190046", "kkkk", "kk", "k", "kk", "kk", "kk"},
    {"20190057", "llll", "ll", "l", "ll", "ll", "ll"},
    {"20190068", "mmmm", "mm", "m", "mm", "mm", "mm"},
    {"20190019", "nnnn", "nn", "n", "nn", "nn", "nn"},
    {"20190037", "oooo", "oo", "o", "oo", "oo", "oo"},  // % 23 == 22
    {"20190041", "pppp", "pp", "p", "pp", "pp", "pp"},  // % 23 == 18
    {"20190066", "qqqq", "qq", "q", "qq", "qq", "qq"}   // % 23 == 18
};

STUDENT data2[M]={
    {"0020190002", "bbbb", "bb", "b", "bb", "bb", "bb"},  // % 31 == 30
    {"0020190001", "aaaa", "aa", "a", "aa", "aa", "aa"},
    {"0020190004", "cccc", "cc", "c", "cc", "cc", "cc"},
    {"0020190098", "eeee", "ee", "e", "ee", "ee", "ee"},  // % 31 == 30
    {"0020190005", "dddd", "dd", "d", "dd", "dd", "dd"},
    {"0020190007", "ffff", "ff", "f", "ff", "ff", "ff"},  
    {"0020190008", "gggg", "gg", "g", "gg", "gg", "gg"},
    {"0020190009", "hhhh", "hh", "h", "hh", "hh", "hh"},  // % 31 == 8
    {"0020190014", "iiii", "ii", "i", "ii", "ii", "ii"},  
    {"0020190020", "jjjj", "jj", "j", "jj", "jj", "jj"},  // % 31 == 30
    {"0020190047", "kkkk", "kk", "k", "kk", "kk", "kk"},  // % 31 == 8
    {"0020190057", "llll", "ll", "l", "ll", "ll", "ll"},
    {"0020190068", "mmmm", "mm", "m", "mm", "mm", "mm"},
    {"0020190089", "nnnn", "nn", "n", "nn", "nn", "nn"},  // % 31 == 30
    {"0020190037", "oooo", "oo", "o", "oo", "oo", "oo"},  
    {"0020190023", "pppp", "pp", "p", "pp", "pp", "pp"},  // % 31 == 8
    {"0020190066", "qqqq", "qq", "q", "qq", "qq", "qq"},  
    {"0020190032", "kkkk", "kk", "k", "kk", "kk", "kk"},  // % 31 == 8
    {"0020190042", "wwww", "ww", "w", "ww", "ww", "ww"},  
    {"0020190074", "xxxx", "xx", "x", "xx", "xx", "xx"},  // % 31 == 8
    {"0020190088", "zzzz", "zz", "z", "zz", "zz", "zz"},  
    {"0020190090", "vvvv", "vv", "v", "vv", "vv", "vv"},  // % 31 == 8
    {"0020190099", "rrrr", "rr", "r", "rr", "rr", "rr"} 
};

int main(void){
    FILE *fp;
    STUDENT std1;
    char id[11], name[21], addr[31], year[2], dept[20], phone[16], email[26];
    int len, cnt=0;

    fp = fopen("student.dat", "w+");
    
    for(int i=0; i<N; i++){
        fwrite(&data1[i], 120, 1, fp);
    }
    printf("Input ends %d\n", ftell(fp));

    fseek(fp, 0, SEEK_SET);
    printf("file pointer:%d\n",ftell(fp));

    while(1){
        fread(&std1, 120, 1, fp);

        if(feof(fp))
            break;
        printf("%s %s %s %s %s %s %s\n", std1.id, std1.name, std1.addr, std1.year, std1.dept, std1.phone, std1.email);
    }
    

    return 0;
}
#include <stdio.h>
#include <string.h>

int main(void){
    int num = 98765, out;
    char buf[20], name[10]="abcdefgh";
    
    //buf에 10바이트는 name, 4바이트는 num을 복사하는 예제

    strncpy(buf, name, 8);
    // sprintf(buf+10, "%d", num);
    memcpy(buf+10, (void *)&num, 4);

    memcpy(&out, buf+10, 4);
    printf("buf=%s\n",buf);
    printf("out = %d\n",out);
    return 0;
}
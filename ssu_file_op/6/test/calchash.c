#include <stdio.h>
#include <string.h>

int main(void){
    int A=48,B=48,N=0, hashnum=31;
    int flag=0;
    
    for(int i=0; i<10; i++){
        flag = 0;
        A = 48 + i;
        for(int j=0; j<10; j++){
            B = 48 + j;
            if((A*B) % hashnum == 8){
                printf("A=%d, B=%d, %d\n",A,B, (A*B) % hashnum);
                // flag = 1;
                // break;
            }
        }
        // if(flag == 1){
            // break;
        // }
    }
    return 0;
}
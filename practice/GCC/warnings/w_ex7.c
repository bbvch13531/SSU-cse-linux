#include <stdio.h>
int main(void) {
    char arr[] = "Hello World\n";
    for(int i = 0 ; i < sizeof(arr) ; i++)
        printf("%c", arr[i]); 
    return 0;
}
/*
$gcc -Wsign-compare w_ex7.c
w_ex7.c:4:23: warning: comparison of integers of different signs: 'int' and 'unsigned long'
      [-Wsign-compare]
    for(int i = 0 ; i < sizeof(arr) ; i++)
                    ~ ^ ~~~~~~~~~~~
1 warning generated.
*/
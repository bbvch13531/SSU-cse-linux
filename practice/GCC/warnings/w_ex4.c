#include <stdio.h>
int main(void) {
    int x = 10; 
    printf("Hello World\n"); 
    return 0;
}
/*
$gcc -Wunused-variable w_ex4.c
w_ex4.c:3:9: warning: unused variable 'x' [-Wunused-variable]
    int x = 10;
        ^
1 warning generated.
*/
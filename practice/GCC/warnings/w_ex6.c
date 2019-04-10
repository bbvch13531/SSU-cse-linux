#include <stdio.h>
int main(void) {
    int x;
    printf("value : %d\n", x); 
    return 0;
}
/*
$gcc -Wuninitialized w_ex6.c
w_ex6.c:4:28: warning: variable 'x' is uninitialized when used here [-Wuninitialized]
    printf("value : %d\n", x);
                           ^
w_ex6.c:3:10: note: initialize the variable 'x' to silence this warning
    int x;
         ^
          = 0
1 warning generated.
*/
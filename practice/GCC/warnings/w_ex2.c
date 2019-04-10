#include <stdio.h>
int main(void) {
    int x = 10;
    float y = 20.0; 
    printf("value x:%f\n", x, y); 
    return 0;
}
/*
$gcc w_ex2.c
w_ex2.c:5:28: warning: format specifies type 'double' but the argument has type 'int' [-Wformat]
    printf("value x:%f\n", x, y);
                    ~~     ^
                    %d
w_ex2.c:5:31: warning: data argument not used by format string [-Wformat-extra-args]
    printf("value x:%f\n", x, y);
           ~~~~~~~~~~~~~~     ^
2 warnings generated.
*/
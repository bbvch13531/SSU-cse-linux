#include <stdio.h> 
#include <stdlib.h>
int main (void) {
    double x = -3.14;
    double y = abs(x); /* fabs(x)*/ 
    printf ("x = %g |x| = %g\n", x, y); 
    return 0;
}
/*
$gcc -Wconversion w_ex9.c
w_ex9.c:5:16: warning: using integer absolute value function 'abs' when argument is of floating point
      type [-Wabsolute-value]
    double y = abs(x); fabs(x)
               ^
w_ex9.c:5:16: note: use function 'fabs' instead
    double y = abs(x);  fabs(x)
               ^~~
               fabs
w_ex9.c:5:16: note: include the header <math.h> or explicitly provide a declaration for 'fabs'
w_ex9.c:5:20: warning: implicit conversion turns floating-point number into integer: 'double' to 'int'
      [-Wfloat-conversion]
    double y = abs(x); fabs(x)
               ~~~ ^
2 warnings generated.
*/
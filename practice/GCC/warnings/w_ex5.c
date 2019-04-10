#include <stdio.h>
int a[2][2] = { 0, 1, 2, 3 };
int b[2][2] = { { 0, 1 }, { 2, 3 } };
int main(void) {
    printf("Hello Wolrd\n");
    return 0; 
}
/*
$gcc -Wmissing-braces w_ex5.c
w_ex5.c:2:17: warning: suggest braces around initialization of subobject [-Wmissing-braces]
int a[2][2] = { 0, 1, 2, 3 };
                ^~~~
                {   }
w_ex5.c:2:23: warning: suggest braces around initialization of subobject [-Wmissing-braces]
int a[2][2] = { 0, 1, 2, 3 };
                      ^~~~
                      {   }
2 warnings generated.
*/
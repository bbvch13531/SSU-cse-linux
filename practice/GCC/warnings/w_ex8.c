#include <stdio.h>
int main(int argc, char *argv[]) {
    printf("Hello World\n");
    return 0;
}
/*
$gcc -Wunused-parameter w_ex8.c
w_ex8.c:2:14: warning: unused parameter 'argc' [-Wunused-parameter]
int main(int argc, char *argv[]) {
             ^
w_ex8.c:2:26: warning: unused parameter 'argv' [-Wunused-parameter]
int main(int argc, char *argv[]) {
                         ^
2 warnings generated.
*/
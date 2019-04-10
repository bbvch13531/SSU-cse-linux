#include <stdio.h> 
int foo();
int main(void) {
    foo();
    return 0; 
}
int foo() {
    printf("foo\n");
}
/*
$gcc w_ex3.c
w_ex3.c:9:1: warning: control reaches end of non-void function [-Wreturn-type]
}
^
1 warning generated.
 ~/Projects/SSU-cse-linux/practice/gcc   master ●  gcc -Wreturn-type w_ex3.c
w_ex3.c:9:1: warning: control reaches end of non-void function [-Wreturn-type]
}
^
1 warning generated.
*/
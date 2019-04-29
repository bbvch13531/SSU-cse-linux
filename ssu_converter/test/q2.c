#include <stdio.h>
#include "Stack.h"

int main(void){
    Stack st;
    push(&st, 5);
    push(&st, 2);
    push(&st, 3);
    push(&st, 4);
    push(&st, 1);

    printStack(&st);

    pop(&st);
    pop(&st);
    push(&st, 15);
    printStack(&st);
    printf("TOP OF STACK : %d\n", peek(&st));
    pop(&st);
    pop(&st);
    pop(&st);
    pop(&st);

    push(&st, 30);

    printStack(&st);
    return 0;
}
#include <stdio.h>

int peek();
void push(int);
void pop();
void printStack();

int main(void){

    push(5);
    push(2);
    push(3);
    push(4);
    push(1);

    printStack();

    pop();
    pop();
    push(15);
    printStack();
    printf("TOP OF STACK : %d\n", peek());
    pop();
    pop();
    pop();
    pop();

    push(30);

    printStack();
    return 0;
}
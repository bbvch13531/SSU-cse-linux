#include <stdio.h>

typedef struct Stack{
    int top = -1;
    static const int STACK_SIZE = 10;
    int stack[STACK_SIZE];

}Stack;

int peek(Stack *stk){
    int top = stk->top;
    return stk->stack[top];
}

void push(Stack *stk, int value){
    int top = stk->top;
    stk->stack[++top] = value;
    printf("%d PUSH !\n", stk->stack[top]);
}

int pop(Stack *stk){
    int top = stk->top;
    printf("%d POP !\n", stk->stack[top]);
    return stk->stack[top--];
}
void printStack(Stack *stk){
    int top = stk->top;
    printf("\n-----STACK LIST-----\n");

    for(int i=top; i>=0; i--){
        printf("%d\n",stk->stack[i]);
    }
    printf("\n-----END OF LIST-----\n");
}
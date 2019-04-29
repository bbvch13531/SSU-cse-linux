#include <stdio.h>
#define STACK_SIZE 10
typedef struct Stack{
    int top;
    int stack[STACK_SIZE];

}Stack;

int peek(Stack *stk){
    int top = stk->top;
    return stk->stack[stk->top];
}

void push(Stack *stk, int value){
    stk->stack[++stk->top] = value;
    printf("%d PUSH !\n", stk->stack[stk->top]);
}

int pop(Stack *stk){
    printf("%d POP !\n", stk->stack[stk->top]);
    return stk->stack[stk->top--];
}
void printStack(Stack *stk){
    printf("\n-----STACK LIST-----\n");

    for(int i=stk->top; i>=0; i--){
        printf("%d\n",stk->stack[i]);
    }
    printf("\n-----END OF LIST-----\n");
}
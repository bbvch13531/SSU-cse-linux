// SSU_20142468 Kyungyoung Heo
#ifndef STACK_H_

#include <stdbool.h>
#define MAX 100000

typedef struct stack {
    char* arr[MAX];
    int size;
} stack;

void init(stack *s){
    s->size = 0;
}

void pop(stack *s){
    s->size--;
    s->arr[s->size] = '\0';        
}

void push(stack *s, char* c){
    s->arr[s->size] = c;
    s->size++;
};

char* top(stack *s){
    return s->arr[s->size-1];
}

bool empty(stack *s){
    if(s->size) return false;
    else return true;
}

#endif // STACK_H_
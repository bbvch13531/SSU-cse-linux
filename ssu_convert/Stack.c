#include <stdio.h>
#define STACK_SIZE 10
	int top;
	int stack[STACK_SIZE];
	void Stack(){
		top = -1;

	}
	int peek(){

	}
	void push(int value){
		stack[++top] = value;
		printf("%d PUSH !\n", stack[top]);

	}
	int pop(){
		printf("%d POP !\n", stack[top]);

	}
	void printStack(){
		printf("\n-----STACK LIST-----\n");
		for(int i=top; i>=0; i--){
			printf("%d\n",stack[i]);
		}
		printf("-----END OF LIST-----\n");

	}


#include <stdlib.h>
#include <stdio.h>
#define STACK_SIZE 10
	int top;
	int stack[STACK_SIZE];
	void Stack(){
		top = -1;

	}
	int peek(){
		return stack[top];

	}
	void push(int value){
		stack[++top] = value;

	}
	int pop(){
		return stack[top--];

	}
	void printStack(){
		printf("\n-----STACK LIST-----\n");
		for(int i=top; i>=0; i--){
			System.out.printf("%d\n",stack[i]);
		}
		printf("-----END OF LIST-----\n");

	}
	int main(void){
		
		st.push(5);
		st.push(2);
		st.push(3);
		st.push(4);
		st.push(1);
		st.printStack();
		st.pop();
		st.pop();
		st.push(15);
		printf("TOP OF STACK : %d\n", st.peek());
		st.printStack();
		st.pop();
		st.pop();
		st.pop();
		st.pop();
		st.push(30);
		st.printStack();

	}

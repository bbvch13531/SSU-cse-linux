
#include <stdlib.h>
#include <stdio.h>
#define STACK_SIZE 10
	int top;
	int stack[STACK_SIZE];
		top = -1;
		return 0;
	}
	int peek(){
		return 0;
	}
	void push(int value){
		return 0;
	}
	int pop(){
		return 0;
	}
	void printStack(){
		printf("\n-----STACK LIST-----\n");
		for(int i=top; i>=0; i--){
			System.out.printf("%d\n",stack[i]);
		}
		printf("-----END OF LIST-----\n");
		return 0;
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
		return 0;
	}

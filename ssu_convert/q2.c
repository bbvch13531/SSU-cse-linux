
#include <stdlib.h>
#include <stdio.h>
	int main(void){
		
		Stack st = new Stack();
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

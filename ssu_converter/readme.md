# ssu_convert

ssu_convert <FILENAME> <OPTION>

import java.util.Scanner;

public class q1{
	public static void main(String[] args){
		Scanner scn = new Scanner(System.in);

		System.out.printf("Enter the number : ");

		int num;
		num = scn.nextInt();
		int even=0, odd=0;

		for(int i=1; i<=num; i++){ // Checking...
			if(i % 2 == 0){
				even+=i;
			}
			else{
				odd+=i;
			}
		}

		System.out.printf("Sum of Even number : %d\n", even);
		System.out.printf("Sum of Odd number : %d\n", odd);

		return ;
	}
}


class Stack{

	int top;
	int[] stack;

	public static final int STACK_SIZE = 10;

	public Stack(){
		top = -1;
		stack = new int[STACK_SIZE];
	}

	public int peek(){
		return stack[top];
	}

	public void push(int value){
		stack[++top] = value;
		System.out.printf(stack[top] + " PUSH !\n");
	}

	public int pop(){
		System.out.printf(stack[top] + " POP !\n");
		return stack[top--];
	}

	public void printStack(){
		System.out.printf("\n-----STACK LIST-----\n");

		for(int i=top; i>=0; i--){
			System.out.printf("%d\n",stack[i]);
		}

		System.out.printf("-----END OF LIST-----\n");
	}
}

public class q2{

	public static void main(String args[]){

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

		System.out.printf("TOP OF STACK : %d\n", st.peek());

		st.printStack();

		st.pop();
		st.pop();
		st.pop();
		st.pop();

		st.push(30);

		st.printStack();
	}
}


import java.io.File;
import java.io.IOException;
import java.io.FileWriter;

public class q3{
	public static void main(String[] args) throws IOException{


		File file = new File("q3java.txt");

		/****** 두번째 매개변수 ******/
		/****** true : 기존 파일의 내용 이후부터 쓰여짐 ******/
		/****** false : 처음부터 쓰여짐 ******/

		FileWriter writer = new FileWriter(file, false);

		writer.write("2019 OSLAB\n");
		writer.write("Linux System Programming\n");

		writer.flush();
		System.out.printf("DONE\n");

		if(writer != null)
			writer.close();

	}
}



import java.util.Scanner;

public class q1{
	public static void main(String[] args){
		Scanner scn = new Scanner(System.in);

		System.out.printf("Enter the number : ");

		int num, even=0, odd=0;
		num = scn.nextInt();

		for(int i=1; i<=num; i++){ // Checking...
			if(i % 2 == 1){
				odd+=i;
			}
			else{
				even+=i;
			}
		}

		System.out.printf("Sum of Even number : %d\nSum of Odd number : %d\n", even, odd);

		return ;
	}
}
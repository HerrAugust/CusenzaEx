package melideo;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		es1();
	}

	/*
	 * Create a keyboard scanner in which the tokens are unsigned
	 * integers, and write the code to determine the sum of the integers.
	 * Note: -5 will be scanned as the unsigned integer 5, and the
	 * minus sign will be skipped over as a delimiter.
	 */
	public static void es3() {
		System.out.println("Scrivi dei numeri unsigned");
		Scanner s = new Scanner(System.in);
		String str = s.nextLine();
		s.close();
		
		int sum = 0;
		s = new Scanner(str).useDelimiter("-| ");
		while(s.hasNext()) {
			if(s.hasNextInt())
				sum += s.nextInt();
			else
				s.next();
		}
		
		s.close();
		System.out.println("somma: " + sum);
	}
	
	/*
	 * Create a small program that substitutes all occurrences of " is " with
	 * " was ".
	 */
	public static void es1() {
		System.out.print("Scrivi una stringa: ");
		Scanner s = new Scanner(System.in);
		String st = s.nextLine();
		
		s = new Scanner(st); //nota: il codice non gestisce "is this me?": manca una if da qualche parte...
		s.useDelimiter(" is |\\r| is\\r"); //\\r è il \n
		st = "";
		while(s.hasNext()) {
			if(st.length() != 0)
				st = st + " was ";
			st += s.next();
		}
		System.out.println(st);
	}
	
	/*
	 * Write and run a small program in which
	 * the end user enters three lines of input. 
	 * The first line contains a string, the second
	 * line contains a substring to be replaced, and
	 * the third line contains the replacement substring.
	 * The output is the string in the first line with
	 * each occurrence of the substring in the second line
	 * replaced with the substring in the third line.
	 * No replacement should be made for an embedded occurrence,
	 * in the first line, of the substring in the second line.
	 * For example, suppose the original string is
	 * “The snow is now on the ground.”, the target string is
	 * “now”, and the replacement string is “melting”.
	 * The output will be “The snow is melting on the ground.”.
	 */
	public static void es2() {
		String s1,s2,s3;
		Scanner s = new Scanner(System.in);
		System.out.println("Inserire una stringa");
		s1 = s.nextLine();
		System.out.println("Inserire una substring to be replaced");
		s2 = s.nextLine();
		System.out.println("Inserire una replacement substring");
		s3 = s.nextLine();
		s.close();
		
		s = new Scanner (s1);
		s.useDelimiter(" " + s2 + " ");
		while(s.hasNext()) {
			String token = s.next();
			System.out.print(token);
			if(!s1.endsWith(token))
				System.out.print(" " + s3 + " ");
		}
		
		s.close();
	}
	
}


public class Main {

	public static void main(String[] args) {
		run();
	}
	
	public static void run() {
		System.out.println("Ordinamento per nome, crescente:");
		System.out.println("\nImplementazione con TreeSet:");
		new Ex1TreeSet().run();
		System.out.println("\nImplementazione con TreeMap:");
		new Ex1TreeMap().run();

		System.out.println("\n\nOrdinamento per divisione:");
		System.out.println("\nImplementazione con TreeSet:");
		new Ex2TreeSet().run();
		System.out.println("\nImplementazione con TreeMap:");
		new Ex2TreeMap().run();

		System.out.println("\n\nQuanti operai ci sono in una divisione:");
		new Ex3().run();
	}

}

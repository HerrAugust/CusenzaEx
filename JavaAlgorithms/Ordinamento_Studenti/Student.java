/*
 * Esercizio sull'ordinamento:
 * Declare a LinkedList (ArrayList) object, whose elements come from the Student class.
 * Each student has a name and grade point average.
 * Print the list where the students are in alphabetical order.
 * Print the list where the students are  in decreasing order of GPAs.
 */

import java.util.List;
import java.lang.Comparable;
import java.util.Comparator;
import java.util.Collections;
import java.util.LinkedList;

public class Student {
	public static void main(String[] s) {
		List<Studente> l = new LinkedList<Studente>();
		l.add(new Studente("A", 10));
		l.add(new Studente("A", 7));
		l.add(new Studente("B", 8));
		l.add(new Studente("D", 6));
		l.add(new Studente("E", 7));
		l.add(new Studente("C", 8));

		List<Studente> copy = new LinkedList<Studente>(l);
		Collections.sort(copy);
		System.out.println("Alphabetically showing students: " + copy);

		System.out.println("--------------------------");
		Collections.sort(l, new StudenteByGPA());
		System.out.println("Showing students by GPA: " + l);
	}


}

class Studente implements Comparable<Studente> {
	private String nome;
	private int gpa;

	public Studente(String n, int gpa) {
		this.nome = n;
		this.gpa = gpa;
	}

	@Override
	public String toString() {
		return this.nome + " gpa: " + gpa;
	}

	public int getGPA() {return gpa;}
	public String getNome() {return nome;}

	/*
	 * Mnemonic:
	 * a.compareTo(b) < 0 // a < b, where < is "precedes"
	 * a.compareTo(b) > 0 // a > b, where > is "follows"
	 * a.compareTo(b) == 0 // a == b
	 */
	public int compareTo(Studente a) {
		if(nome.equals(a.nome)) //this = 10 and a = 2 => 2 10, so this should follow => > 0
			return gpa - a.gpa;
		return nome.compareTo(a.nome);
	}

	@Override
	public boolean equals(Object a) {
		if(a instanceof Studente == false)
			return false;
		Studente as = (Studente) a;
		return nome.equals(as.nome) && gpa == as.gpa;
	}
}

class StudenteByGPA implements Comparator<Studente> {
	public int compare(Studente a, Studente b) {
		return b.getGPA() - a.getGPA(); //if a < b => compareTo < 0
	}
}
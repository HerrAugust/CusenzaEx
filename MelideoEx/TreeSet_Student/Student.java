/*
 * Declare two TreeSet objects, set1 and set2, whose elements come from the same Student class.
 * Each student has a name and grade point average.  In set1, the students are in alphabetical order.
 * In set2, the elements are in decreasing order of GPAs.  Insert a few students into each set and
 * then print out the set.
 */

import java.util.*;

public class Student implements Comparable<Student> {
	public static void main(String[] a) {
		run();
	}

	private int gpa;
	private String name;
	public Student(String n, int gpa1) {name = n; gpa = gpa1;}
	public int getGPA() {return gpa;}
	public String getname() {return name;}
	public String toString() {return name + " " + gpa;}
	public int compareTo(Student a) {
		if(name.equals(a.name))
			return gpa-a.gpa;
		return name.compareTo(a.name);
	}

	public static void run() {
		TreeSet<Student> alfa = new TreeSet<Student>(); //implementare Comparable!!
		TreeSet<Student> bygpa = new TreeSet<Student>(new StudentByGPA()); //implementare Comparator!!

		alfa.add(new Student("Giacomo", 12));
		alfa.add(new Student("Luca", 10));
		alfa.add(new Student("Aldo", 13));

		bygpa.add(new Student("Giacomo", 12));
		bygpa.add(new Student("Luca", 10));
		bygpa.add(new Student("Aldo", 13));		

		System.out.println("Alfabetico:");
		for(Student i : alfa)
			System.out.println(i); //scrivere toString()!!

		System.out.println("By GPA:");
		for(Student i : bygpa)
			System.out.println(i);
	}

}

class StudentByGPA implements Comparator<Student> {
	public int compare(Student a, Student b) {
		return a.getGPA()-b.getGPA();
	}
}
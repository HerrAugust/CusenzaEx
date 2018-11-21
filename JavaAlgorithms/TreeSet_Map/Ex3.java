/*
 * In riferimento all'esercizio sugli impigati dire quanti impiegati ci sono in un certo ufficio usando TreeSet/TreeMap.
 */
import java.util.*;
 public class Ex3 {

 	public static void main(String[] c) {  new Ex3().run(); }

	public void run() { new Ex3().runTreeSet(); new Ex3().runTreeMap(); }

 	public void runTreeMap() {
 		System.out.println("\nImplementazione tramite TreeMap:");
 		TreeMap<Integer, Integer> divisions = new TreeMap<Integer, Integer>();
 		TreeMap<String, Integer> impiegati = new TreeMap<String, Integer>();

		impiegati.put("Misino, John", 8);
		impiegati.put("Nguyen,Viet", 14);
		impiegati.put("Panchenko,Eric", 6);
		impiegati.put("Dunn,Michael", 6);
		impiegati.put("Deusenbery,Amanda", 14);
		impiegati.put("Taoubina,Xenia", 6); 		

		for(Map.Entry<String, Integer> entry : impiegati.entrySet()) //cost: O(logn)
		{
			if(divisions.containsKey(entry.getValue())) { //O(logn)
				int oldvalue = divisions.get(entry.getValue()); //O(logn)
				divisions.put(entry.getValue(), oldvalue+1); //O(logn)
			}
			else
				divisions.put(entry.getValue(), 1);
		}

		for(Map.Entry<Integer, Integer> entry : divisions.entrySet())
			System.out.println("In division " + entry.getKey() + " there are " + entry.getValue());
 	}

 	public void runTreeSet() {
 		System.out.println("\nImplementazione tramite TreeSet:");
 		TreeSet<Impiegato> impiegati = new TreeSet<Impiegato>();

 		impiegati.add(new Impiegato("Misino,John", 8));
		impiegati.add(new Impiegato("Nguyen,Viet", 14));
		impiegati.add(new Impiegato("Panchenko,Eric", 6));
		impiegati.add(new Impiegato("Dunn,Michael", 6));
		impiegati.add(new Impiegato("Deusenbery,Amanda", 14));
		impiegati.add(new Impiegato("Taoubina,Xenia", 6));

		TreeSet<Division> divisions = new TreeSet<Division>();
		for(Impiegato i : impiegati)
			if(divisions.add(new Division(i.getNum(), 1)) == false) //se l'elemento non è già presente
			{
				System.out.println("Warning");
				//divisions....impossibile ottenere vecchio valore di impiegati in una division...
			}
 	}

 }

 class Division implements Comparable<Division> {
 	public int division, numImpiegati;
 	public Division(int div, int nImp) { division = div; numImpiegati = nImp; }
 	public int compareTo(Division a) {
 			return division- a.division;
 	}
 }

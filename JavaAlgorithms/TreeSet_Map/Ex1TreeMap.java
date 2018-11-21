/*
 * Exercise 1 (see file Ex1TreeSet.java) can also be resolved using TreeMap.
 * Implementation with TreeMap.
 */

import java.util.TreeMap;
import java.util.Map;

public class Ex1TreeMap {

		public void run() {
			TreeMap<String, Integer> impiegati = new TreeMap<String, Integer>();

			impiegati.put("Misino, John", 8);
			impiegati.put("Nguyen,Viet", 14);
			impiegati.put("Panchenko,Eric", 6);
			impiegati.put("Dunn,Michael", 6);
			impiegati.put("Deusenbery,Amanda", 14);
			impiegati.put("Taoubina,Xenia", 6);
			impiegati.put("Nguyen,Viet", 50); //non aggiunto perchè Comparable è definito sul campo nome
		
			for(Map.Entry<String, Integer> entry : impiegati.entrySet())
				System.out.println(entry.getKey() + " " + entry.getValue());
		}
}

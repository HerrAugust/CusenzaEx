/*
 * Do the same as Ex2TreeSet.java but now using TreeMap.
 */

import java.util.TreeMap;
import java.util.Map;
import java.util.Comparator;

public class Ex2TreeMap {

	public void runTreeMap() {
		TreeMap<Impiegato, Integer> impiegati = new TreeMap<Impiegato, Integer>(new ImpiegatoByDivision());

		impiegati.put(new Impiegato("Misino,John", 8), 1);
		impiegati.put(new Impiegato("Panchenko,Eric", 6), 1);
		impiegati.put(new Impiegato("Dunn,Michael", 6), 1);
		impiegati.put(new Impiegato("Deusenbery,Amanda", 14), 1);
		impiegati.put(new Impiegato("Taoubina,Xenia", 6), 1);
		impiegati.put(new Impiegato("Nguyen,Viet", 14), 1);

		for(Map.Entry<Impiegato, Integer> entry : impiegati.entrySet())
			System.out.println(entry.getKey());
	}
}

class  ImpiegatoByDivision implements Comparator<Impiegato> {

	public int compare(Impiegato a, Impiegato b) {
		return a.getNum() - b.getNum();
	}

}

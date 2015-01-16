import java.util.TreeSet;

/*
 * Suppose we are given the name and division number for each employee in a company.
 * There are no duplicate names. We would like to store this information alphabetically, by name. 
 * How should this be done: TreeMap or TreeSet? Comparable or Comparator?
 * RISP: Devo memorizzare i nomi in modo alfabetico, quindi devo usare Comparable.
 * Devo inoltre memorizzare impiegati (classe), che ha una stringa e un numero. Inoltre
 * non ci devono essere duplicati, quindi va scelta TreeSet (gli insiemi matematici per definizione
 * non possono avere duplicati).  
 */

public class Ex1 {
	public void run() {
		TreeSet<Impiegato> impiegati = new TreeSet<Impiegato>();
		
		impiegati.add(new Impiegato("Misino,John", 8));
		impiegati.add(new Impiegato("Nguyen,Viet", 14));
		impiegati.add(new Impiegato("Panchenko,Eric", 6));
		impiegati.add(new Impiegato("Dunn,Michael", 6));
		impiegati.add(new Impiegato("Deusenbery,Amanda", 14));
		impiegati.add(new Impiegato("Taoubina,Xenia", 6));
		impiegati.add(new Impiegato("Nguyen,Viet", 50)); //non aggiunto perchè Comparable è definito sul campo nome
		
		for(Impiegato i : impiegati)
			System.out.println(i);
	}
}

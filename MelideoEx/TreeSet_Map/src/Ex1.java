import java.util.TreeSet;

/*
 * Suppose we are given the name and division number for each employee in a company.
 * There are no duplicate names. We would like to store this information alphabetically, by name.
 * How should this be done: TreeMap or TreeSet? Comparable or Comparator? 
 * RISP: Non vengono dati in ingresso doppioni, quindi non c'è problema di cancellare elementi già esistenti.
 * Poichè la differenza tra TreeSet e TreeMap è proprio questa, non c'è differenza tra i due.
 * Se ci fossero stati in ingresso doppioni avremmo dovuto decidere se cancellare (TreeMap) o meno (TreeSet).
 * Inoltre l'output desiderato è ottenibile facilmente sia con TreeMap (tramite codice) sia con TreeSet (tramite toString()).
 * Poichè, inoltre, si vuole l'ordinamento alfabetico dei nomi basta un compareTo() => Comparable.
 * Implementazione con TreeSet.
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

import java.util.Comparator;
import java.util.TreeSet;

/*
 * Re-do Programming Exercise 2, but now the ordering should be by increasing division numbers,
 * and within each division number, by alphabetical order of names.
 * MY NOTE: this exercise can only be solved using TreeSet and not TreeMap because there are
 * duplicated division numbers (so keys would be duplicated in TreeMao).
 */

public class Ex2TreeSet {
	public void run() {
		TreeSet<Impiegato> impiegati = new TreeSet<Impiegato>(new ImpiegatoByDivision());
		
		impiegati.add(new Impiegato("Misino,John", 8));
		impiegati.add(new Impiegato("Nguyen,Viet", 14));
		impiegati.add(new Impiegato("Panchenko,Eric", 6));
		impiegati.add(new Impiegato("Dunn,Michael", 6));
		impiegati.add(new Impiegato("Deusenbery,Amanda", 14));
		impiegati.add(new Impiegato("Taoubina,Xenia", 6));
		impiegati.add(new Impiegato("Nguyen,Viet", 50)); //viene aggiunto perchè compare() restituisce 0 (=> uguali) <=> nome e num sono uguali
		
		for(Impiegato i : impiegati)
			System.out.println(i);
	}
}

class ImpiegatoByDivision implements Comparator<Impiegato> {
	@Override
	public int compare(Impiegato arg0, Impiegato arg1) {
		if(arg0.getNum() == arg1.getNum())
			return arg0.getNome().compareTo(arg1.getNome());
		return arg0.getNum() - arg1.getNum();
	}
}

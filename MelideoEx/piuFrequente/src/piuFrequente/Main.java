package piuFrequente;

import java.util.LinkedList;
import java.util.List;
import java.util.TreeMap;

/*
 * Si scriva un metodo String piuFrequente(List<String>) che, data una lista di stringhe,
 * restituisce quella con il maggior numero di occorrenze. Si consiglia l'uso di un TreeMap.
 */

public class Main {

	public static void main(String[] args) {
		run();
	}
	
	public static void run() {
		TreeMap<Integer, String> lista = new TreeMap<Integer, String>();
		lista.put(1,"Cane");
		lista.put(2,"Gatto");
		
		System.out.println("first: " + lista.firstKey());
	}
	
	/*
	 * ALG: Prendo una per una le entry della lista di stringhe e le inserisco nel TreeMap.
	 * Nel farlo controllo prima se tale stringa c'è già: se c'è allora la inserisco con value = 1;
	 * se non c'è allora la inserisco col suo vecchio value + 1. In ogni caso tengo sempre un 
	 * puntatore alla stringa più frequente, tale che non debba fare la scansione dell'albero
	 * per cercare la stringa più frequente.
	 */
	public static String piuFrequente(List<String> list) {
		TreeMap<String, Integer> tree = new TreeMap<String, Integer>();
		int oldvalue = 0, frequenza = 0;
		String piuFrequente = "";
		
		for(String e : list) {
			if(tree.containsKey(e))
				oldvalue = tree.get(e);
			tree.put(e, oldvalue + 1);
			if(oldvalue + 1 > frequenza) {
				frequenza = oldvalue + 1;
				piuFrequente = e;
			}
			oldvalue = 0;
		}
		
		return piuFrequente;
	}
}

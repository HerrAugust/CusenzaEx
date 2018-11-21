
public class TestMoneta {

	public static void main(String[] args){
		new TestMoneta().run();
	}


	public void run(){
	
		Moneta unoCent = new Moneta();
		Moneta cinquantaCent = new Moneta(50, "cinquanta");
		Moneta ventiCent = new Moneta(20, "venti");
		
		System.out.println("\nValore della moneta uno: ");
		System.out.println(unoCent.getValore());
		System.out.println("\nNome della moneta uno: ");
		System.out.println(unoCent.getNome());
		System.out.println("\nValore della moneta cinquanta: ");
		System.out.println(cinquantaCent.getValore());
		System.out.println("\nNome della moneta cinquanta: ");
		System.out.println(cinquantaCent.getNome());
	
		Moneta dueCent = new Moneta();
		Moneta cinquantaCentBis = new Moneta(50, "cinquanta");
		
		System.out.println("\nControllo se le monete sono uguali:");
		System.out.println("Valore della moneta dueCent: ");
		System.out.println(dueCent.getValore());
		System.out.println("\nNome della moneta unobis: ");
		System.out.println(dueCent.getNome());
		System.out.println("\nValore della moneta cinquantaCentBis: ");
		System.out.println(cinquantaCentBis.getValore());
		System.out.println("\nNome della moneta cinquantaCentBis: ");
		System.out.println(cinquantaCentBis.getNome());
		
		/*
		 * per via del costruttore nullo questo confronto porta a nullPointerExc poiche' sono due valori null;
		 * 
		System.out.println("\nControllo se le monete unoCent e dueCent sono uguali:");
		System.out.println(unoCent.equals(dueCent));
		*/
	
		
		System.out.println("\nControllo se le monete cinquantaCent e cinquantaCentBis sono uguali:");
		System.out.println(cinquantaCent.equals(cinquantaCentBis));
		
		System.out.println("\nControllo compareTo su monete: ");
		System.out.println(unoCent.compareTo(dueCent));
		System.out.println("\nControllo compareTo su monete: ");
		System.out.println(ventiCent.compareTo(cinquantaCent));
		System.out.println("\n");
		System.out.println(cinquantaCent.toString());
		System.out.println("\n");
		System.out.println(cinquantaCentBis.toString());		
	}
}
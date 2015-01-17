public class TestPortamonete {

	public static void main(String[] args){
		new TestPortamonete().run();
	}


	public void run()
	{
		Portamonete gucci = new Portamonete();
		System.out.println("\nStampo il portamoneta creato: ");
		gucci.print();
		System.out.println("\nStampo il portamoneta dopo l'aggiunta di cinque monete: ");
		Moneta cinquantaCent = new Moneta(50, "cinquanta");
		Moneta ventiCent = new Moneta(20,"venti");
		Moneta dieciCent = new Moneta(10, "dieci");
		

		gucci.addMoneta(cinquantaCent);
		gucci.addMoneta(dieciCent);
		gucci.addMoneta(cinquantaCent);
		gucci.addMoneta(ventiCent);
		gucci.addMoneta(cinquantaCent);


		gucci.print(); //20 50 50 50
		System.out.println("\nStampo il portamoneta dopo la rimozione di una moneta: ");


		gucci.print();
		System.out.println("\nStampo il portamoneta dopo la rimozione di una moneta da 50: ");

		gucci.removeMoneta(cinquantaCent);
		gucci.print(); //20 50 50
		
		System.out.println("\nStampo il portamoneta dopo la rimozione del tipo moneta cinquanta: ");
		gucci.removeTypeMoneta(cinquantaCent);

		gucci.print(); //20
		/*
		
		Moneta cinquantadue = new Moneta(52, "cinquantadue");
		gucci.addMoneta(cinquantadue);
		Moneta cinquantatre = new Moneta(53, "cinquantatre");
		gucci.addMoneta(cinquantatre);
		{System.out.println(gucci.wallet);} */

		gucci.print();


	}
}

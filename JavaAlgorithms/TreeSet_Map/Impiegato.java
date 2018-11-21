public class Impiegato implements Comparable<Impiegato> {
		private String nome;
		private int num;
		
		public Impiegato(String n, int nu) {
			nome = n; num = nu;
		}
		
		public String getNome() { return nome; }
		public int getNum() { return num; }
		
		@Override
		public String toString() {
			return nome + ", num: " + num;
		}

		@Override
		public int compareTo(Impiegato arg0) {
			return this.nome.compareTo(arg0.nome);
		}
}

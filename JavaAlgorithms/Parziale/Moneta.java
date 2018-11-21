public class Moneta implements Comparable<Moneta> {
	
	public int valore;
	public String nome;
	
	public Moneta()
	{
	}
	
	public Moneta(int value, String name)
	{
		valore = value;
		nome = name;
	}

	public int getValore()
	{
		return valore;
	}
	
	public String getNome()
	{
		return nome;
	}

	public boolean equals(Moneta m)
	{
		if((this.getValore() == m.getValore()) && (this.nome.equals(m.nome))) return true;
		return false;
	}
		
	public int compareTo(Moneta m)
	{
		return this.valore - m.valore;
	}
	
	public String toString()
	{
		return "Nome: " + nome + " Valore: " + valore;
	}

}
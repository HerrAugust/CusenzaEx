import java.util.*;
import java.util.LinkedList;


public class Portamonete
{
	List<Moneta> wallet = new LinkedList<Moneta>();

	public Portamonete()
	{
	}
	
	public void addMoneta(Moneta m)
	{
	if(wallet.isEmpty())
	{
		wallet.add(m);
		return;
	}
	for(int i=0; i<wallet.size(); i++)
	{
	Moneta corr = wallet.get(i);
	int ret = corr.compareTo(m);
	if(ret == 0)
	{
		wallet.add(i, m);
		break;
	}
	if(ret > 0)
	{
		wallet.add(i-1, m);
		break;
	}
	}
}
	
	/*
	 * rimuove una sola moneta di un dato tipo
	 * */
	public void removeMoneta(Moneta m)
	{
		if(wallet.isEmpty()) return;

		for(int i=0; i<wallet.size(); i++)
		{
			if(wallet.get(i).compareTo(m)==0)
			{
				wallet.remove(i);
				return;
			}
		}
		return;
	}
	
	/*
	 * rimuove tutte le monete di un dato tipo
	 * */
	public void removeTypeMoneta(Moneta m)
	{
		if(wallet.isEmpty()) return;

		for(int i=0; i<wallet.size(); i++)
		{
			if(wallet.get(i).compareTo(m)==0)
			{
				wallet.remove(i);
				i--;
			}
		}
		return;
	}
	
	public void print()
	{
		for (Moneta corr : wallet)
		{
			System.out.println(corr.toString());
		}
	}
	

	
}

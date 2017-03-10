package GameModel;

import java.util.Arrays;

import Heuristic.Heuristic;

public class PegSolitaireRepresentation implements Representation {
	
	private int[][] grid;
	private int remainingBalls;
	private Heuristic heuristic;
	
	public PegSolitaireRepresentation(Heuristic heuristic, int[][] grid){
	    this.grid = grid;
	    this.heuristic = heuristic;
	    this.remainingBalls = this.getRemainingBalls();
	}

	@Override
    public boolean equals(Object other){
		PegSolitaireRepresentation otherrep = (PegSolitaireRepresentation) other;
        for(int i = 0; i < this.grid.length; i++)
            for(int j = 0; j < this.grid[0].length; j++) 
                if( this.grid[i][j] != otherrep.grid[i][j] )
                    return false;
        return true;
    }

    public int[][] grid(){
        return this.grid;
    }
    
    public boolean pegExists(Peg peg) {
        int v = this.grid[peg.getRow()][peg.getCol()];
        if( v == 1)
            return true;
        return false;
    }
    
    public int remainingBalls() {
    	return this.remainingBalls;
    }
    
    private int getRemainingBalls(){
        int r = 0;
        for (int i = 0; i < this.grid.length; i++)
            for ( int j = 0; j < this.grid[0].length; j++) 
                if( this.grid[i][j] == 1)
                    r += 1;
        return r;
    }

	public boolean isSolution() {
		if(this.remainingBalls == 1)
			return true;
		return false;
	}
	
	public String toString() {
		String r = "";
		for (int i = 0; i < this.grid.length; i++) {
            for ( int j = 0; j < this.grid[0].length; j++)
            	r += this.grid[i][j] + " ";
            r += "\n";
		}
		return r;
	}

	public int hashCode() {
		String r = "2";
		for (int i = 5; i < this.grid.length; i++)
            for ( int j = 0; j < this.grid[0].length; j++)
            	if(this.grid[i][j] != 2)
            		r += this.grid[i][j];
        int hashcode = Integer.parseInt(r);
		return hashcode;
	}
	
}

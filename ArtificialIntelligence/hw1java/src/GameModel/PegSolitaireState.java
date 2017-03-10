package GameModel;

import Heuristic.Heuristic;

public class PegSolitaireState implements State {

	private static int lastID = 1; //needed for debug
	private Heuristic H;
	private Representation representation;
	private PegSolitaireState parentState;
	private int identifier;
	private int level;

    public PegSolitaireState(Heuristic heuristic, int[][] grid, PegSolitaireState parentState ) {
        this.H = heuristic;
        this.representation = new PegSolitaireRepresentation(heuristic, grid);
        this.parentState = parentState;
        
        PegSolitaireState.lastID += 1;
        this.identifier = PegSolitaireState.lastID;
    }

    public Representation getRepresentation() {
        return this.representation;
    }

    public Heuristic getHeuristic() {
        return this.H;
    }
    
    public PegSolitaireState parent() {
        return this.parentState;
    }
    
    //needed for debug
    public String getStateName() {
        String stateName = "level= " + this.level + ", id= " + this.identifier;
        return stateName;
    }
        
    public void setLevel(int level) {
        this.level = level;
    }
        
    public int getLevel() {
        return this.level;
    }
    
    //needed for hashset
    @Override
    public boolean equals(Object other) {
    	PegSolitaireState otherstate = (PegSolitaireState) other;
        return (this.representation).equals(otherstate.representation);
    }
    
    @Override
    public int hashCode() {
    	int h =  ((PegSolitaireRepresentation) this.representation).hashCode();
    	return h;
    }

	@Override
	public int f() {
        int g = 1; //could be any number. this is the cost to move a peg
        int h = this.H.H((State) this);
        int valf = g + h;
        return valf;
    }

	public boolean isSolution() {
		return ((PegSolitaireRepresentation) this.getRepresentation()).isSolution();
	}
	
	public String toString() {
		int[][] grid = ((PegSolitaireRepresentation) this.representation).grid();
		String r = "";
		for (int i = 0; i < grid.length; i++) {
            for ( int j = 0; j < grid[0].length; j++)
            	r += grid[i][j] + " ";
            r += "\n";
		}
		return r;
	}

	public void setParent(PegSolitaireState parent) {
		this.parentState = parent;
	}
                
}

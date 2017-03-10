package GameModel;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import Heuristic.Heuristic;

public class PegSolitaireGame implements Game {
	
	private PegSolitaireState state;
	private Heuristic heuristic;
	
	public PegSolitaireGame(PegSolitaireState s, Heuristic heuristic) {
		this.state = s;
		this.heuristic = heuristic;
	}
        
    public char map(int j) {
        char[] directions = {'n', 'e', 's', 'w'};
        return directions[j];
    }
    
    //given the current grid, it returns the possible moves
    public List<State> neighbors(State state){
        this.heuristic = state.getHeuristic();
        List<State> possiblegrids = new ArrayList<State>(12);
        
        int[][] grid = ((PegSolitaireRepresentation) state.getRepresentation()).grid(); 
        
        //visit the whole grid, looking for possible moves
        for (int i = 0; i < grid.length; i++)
            for (int j = 0; j < grid[0].length; j++) {
                Peg peg = new Peg(i,j);
                //if peg exists, i.e. current cell is not a hole or a corner...
                PegSolitaireRepresentation rep = ((PegSolitaireRepresentation) state.getRepresentation());
                if ( !rep.pegExists(peg) )
                    continue;
                //...find a possible move for this peg (note{ each peg could be moved also in all the 4 directions)
                for(int k = 0; k < 4; k++) {
                    if (this.moveIsLegal(peg, this.map(k), grid)) {
                        int[][] copy = new int[grid.length][];
                        
                        //copy grid into copy
                        for(int m = 0; m < grid.length; m++)
                            copy[m] = grid[m].clone();
                        
                        PegSolitaireState newstate = this.makeMove(copy, peg, this.map(k));
                        newstate.setParent((PegSolitaireState) state);
                        int fatherLevel = ((PegSolitaireState) state).getLevel();
                        newstate.setLevel(fatherLevel + 1);
                        possiblegrids.add(newstate);
                    }
                }
            }
        return ((List<State>) possiblegrids);
    }
    
    public boolean moveIsLegal(Peg peg, char direction, int[][] grid) { //(3,4) n
        int r = peg.getRow();
        int c = peg.getCol();
        int gridRows = grid.length;
        int gridCols = grid[0].length;
        if( direction == 'n') {
            if ( r == 0 )  // |o
                return false;
            if (r == 1)  // |oo
                return false;
            if ( r > 1 && grid[r-2][c] == 0 && grid[r-1][c] == 1 )  //xoo 
                return true;
            if ( r > 1 && grid[r-2][c] == 1 && grid[r-1][c] == 1 ) //ooo
                return false;
        }
        else if ( direction == 'e' ) {
            if (c == gridCols-1) // |o
                return false;
            if (c == gridCols-2) // |oo
                return false;
            if ( c < gridCols-2 && grid[r][c+2] == 0 && grid[r][c+1] == 1) // xoo
                return true;
            if (c < gridCols-2 && grid[r][c+2] == 1 && grid[r][c+1] == 1) // ooo
                return false;
        }
        else if (direction == 's') {
            if (r == gridRows-1)
                return false;
            if (r == gridRows-2)
                return false;
            if (r < gridRows-2 && grid[r+2][c] == 0 && grid[r+1][c] == 1)
                return true;
            if (r < gridRows-2 && grid[r+2][c] == 1 && grid[r+1][c] == 1)
                return false;
        }
        else { //west
            if (c == 0)
                return false;
            if (c == 1)
                return false;
            if (c > 1 && grid[r][c-2] == 0 && grid[r][c-1] == 1)
                return true;
            if (c > 1 && grid[r][c-2] == 1 && grid[r][c-1] == 1)
                return false;
            }
        return false;
    }


    //assumes move is legal
    public PegSolitaireState makeMove(int[][] grid, Peg peg, char direction) {
        int r = peg.getRow();
        int c = peg.getCol();
        if (direction == 'n') { //move north, eating peg
            grid[r][c] = 0;
            grid[r-1][c] = 0;
            grid[r-2][c] = 1;
        }
        else if( direction == 'e' ) {
            grid[r][c] = 0;
            grid[r][c+1] = 0;
            grid[r][c+2] = 1;
        }
        else if( direction == 's' ) {
            grid[r][c] = 0;
            grid[r+1][c] = 0;
            grid[r+2][c] = 1;
        }
        else { //direction == 'w'
            grid[r][c] = 0;
            grid[r][c-1] = 0;
            grid[r][c-2] = 1;
        }
        PegSolitaireState newstate = new PegSolitaireState(this.state.getHeuristic(), grid, null);
        return newstate;
    }

	
	public State getState() {
		// TODO Auto-generated method stub
		return null;
	}

	
	public boolean isSolution(State state) {
		// TODO Auto-generated method stub
		return false;
	}
                
}

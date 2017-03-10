package Heuristic;

import GameModel.Peg;
import GameModel.PegSolitaireRepresentation;
import GameModel.PegSolitaireState;
import GameModel.State;

public class ManhattanDistanceHeuristic implements Heuristic {
	//grid is a PegSolitaireRepresentation
    public int H(State state) {
        int e = 0;
        PegSolitaireRepresentation representation = ((PegSolitaireRepresentation) state.getRepresentation());
        int[][] grid = representation.grid();
        for (int i = 0; i < grid.length; i++)
            for (int j = 0; j < grid[0].length; j++)
                if (grid[i][j] == 1)
                    e += new Peg(i,j).manhattandistance();
        return e;
    }
    
}

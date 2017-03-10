package hw1java;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import GameModel.PegSolitaireGame;
import GameModel.PegSolitaireRepresentation;
import GameModel.PegSolitaireState;
import GameModel.State;
import Heuristic.Heuristic;
import Heuristic.ManhattanDistanceHeuristic;

public class Main {
	
	private static int movesNumber;
	private static Set<PegSolitaireState> explored;
	private static PegSolitaireState solution;

	private static int[][] classic = {
	           {2,2,1,1,1,2,2},
	           {2,2,1,1,1,2,2},
	           {1,1,1,1,1,1,1},
	           {1,1,1,0,1,1,1},
	           {1,1,1,1,1,1,1},
	           {2,2,1,1,1,2,2},
	           {2,2,1,1,1,2,2} };
	
	public static void main(String[] args) throws InterruptedException {
	    //Manhattan distance heuristic for classic
	    System.out.println( "Manhattan distance heuristic for classic" );
	   
	    explored 						= new HashSet<PegSolitaireState>();
	    Heuristic heuristic           	= new ManhattanDistanceHeuristic();
		PegSolitaireState state0        = new PegSolitaireState(heuristic, classic.clone(), null);
	    PegSolitaireGame game           = new PegSolitaireGame(state0, heuristic);
		
	    //A* Algorithm
	    long start = System.currentTimeMillis();
	    boolean res = AStar(game, state0);
		if (res) {
			System.out.println("Solution found!");
		}
		else
			System.out.println("No solution found");
		long end = System.currentTimeMillis();
		
		//print solution
		System.out.println("");
		System.out.println("Seconds needed: " + (end-start)/1000);
		System.out.println("Moves needed (#" + movesNumber + "):");
		PegSolitaireState curState = solution;
		List<PegSolitaireState> moveslist = new ArrayList<PegSolitaireState>(32);
		do { //needed for reverse
			moveslist.add(curState);
			curState = curState.parent();
		} while(curState != null);
		for(int i = moveslist.size()-1; i >= 0; i--) {
			System.out.println(((PegSolitaireRepresentation) moveslist.get(i).getRepresentation()).toString());
			System.out.println("____________________");
		}
	}
	
	public static State pick(List<State> states) {
		if(states.size() == 0)
			return null;
		
		State min = states.get(0);
		for (State s : states) {
			if(s.f() < min.f())
				min = s;
		}
		return min;
	}
	
	public static boolean AStar(PegSolitaireGame game, PegSolitaireState state) throws InterruptedException {
		if(state.isSolution()) {
			solution = state;
	        return true;
		}
	    
	    List<State> children = game.neighbors(state);
	    while (true) {
	    	System.out.println( "___________________________");
	    	if(state != null)
	    		System.out.println("We are at node: " + state.getStateName());
	    	System.out.println("This node has these children:");
	    	for(int i = 0; i < children.size();) {
	    		PegSolitaireState child = (PegSolitaireState ) children.get(i);
	    		PegSolitaireRepresentation rep = (PegSolitaireRepresentation) child.getRepresentation();
	    		System.out.println(i++ + ". Node: " + child.getStateName() + ", f= " + child.f() + ", balls= " + rep.remainingBalls());
	    	}
	    	
	    	State best = pick(children);
	        while(true) {
	            best = pick(children); //take best child board
	            if (best != null) // do not check this board anymore
		            children.remove(best);
	            else
	            	return false; //node is leaf (not solution), so go back to father
	            System.out.println("Chosen best= " + ((PegSolitaireState) best).getStateName());
	            if( !explored.contains(best) ) //if board already explored (as child of some other board, skip it)
	            	break;
	            else
	            	System.out.println("Best node already explored");
	        }
	        
	        System.out.println( "\nview name: level "+ state.getStateName());
	        if (state.parent() != null)
	            System.out.println( "view father: "+ state.parent().getStateName());
	        System.out.println( "Move number: " + movesNumber);
	        System.out.println( "Explored grids "+explored.size());
	        int r = ((PegSolitaireRepresentation) state.getRepresentation()).remainingBalls();
	        System.out.println( "Balls: "+ r);
	        System.out.println( "Exploring matrix:");
	        System.out.println(((PegSolitaireRepresentation) best.getRepresentation()).toString());
	        
	        explored.add((PegSolitaireState) best);
	        movesNumber++;
	        boolean r1 = AStar(game, (PegSolitaireState)best);
	        if (r1)
	            return true;
	        //false: go to father node and choose another path to explore
	        movesNumber--;
	    }
	}

}

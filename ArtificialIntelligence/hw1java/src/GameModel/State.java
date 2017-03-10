package GameModel;

import Heuristic.Heuristic;

public interface State {
	public Representation getRepresentation();
	public Heuristic getHeuristic();
	public int f();
}

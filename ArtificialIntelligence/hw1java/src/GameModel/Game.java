package GameModel;

import java.util.List;

public interface Game {

    public List<State> neighbors(State state);

    public State getState();

    public boolean isSolution(State state);
}

import GameModels as G

class Heuristic:

    def __init__(self):
        pass

    def H(self, state):
        raise NotImplementedError("Please implement this function")

class ManhattanDistanceHeuristic(Heuristic):
    #grid is a PegSolitaireRepresentation
    def H(self, state):
        e = 0
        representation = state.getRepresentation()
        grid = representation.grid
        for i in range(0, len(grid)):
            for j in range(0, len(grid[0])):
                if grid[i][j] == 1:
                    e += G.Peg(i,j).manhattandistance()
        return e
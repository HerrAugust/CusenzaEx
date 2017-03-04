class Heuristic:

    def __init__(self):
        pass

    def H(self, state):
        raise NotImplementedError("Please implement this function")

class ExponentialDistanceHeuristic(Heuristic):

    # Exponential Distance:
    # If H,V are the horizontal and vertical distances from the center respectively, then the heuristic's value is 2^max(H,V)
    def H(self, peg, grid):
        h = abs(peg.getCol() - grid.centerX)
        v = abs(peg.getRow() - grid.centerY)
        e = 2**max(h, v)
        return e

class ManhattanDistanceHeuristic(Heuristic):
    def H(self, peg, grid):
        h = abs(peg.getCol() - grid.centerX)
        v = abs(peg.getRow() - grid.centerY)
        e = h + v
        return e
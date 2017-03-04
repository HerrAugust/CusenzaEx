from GameModels import PegSolitaireGame as G

class Heuristic:

    def __init__(self):
        pass

    def H(self, state):
        raise NotImplementedError("Please implement this function")

class ExponentialDistanceHeuristic(Heuristic):

    # Exponential Distance:
    # If H,V are the horizontal and vertical distances from the center respectively, then the heuristic's value is 2^max(H,V)
    def H(self, peg):
        h = peg.getCol() - G.centerX
        v = peg.getRow() - G.centerY
        e = 2**max(h, v)
        return e

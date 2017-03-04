import GameModels as G

class Game:

    def __init__(self, initialState=None, heuristic=None):
        self.state = initialState
        self.heuristic = heuristic

    def neighbors(self, state):
        out = set([])
        return out

    def getState(self):
        return self.state

    def solution(self, state):
        return True

class PegSolitaireGame(Game):
    centerRow = 0 #static var. it is the column of the central space of play grid. needed for Manhattan Distance
    centerCol = 0 #static var. it is the row    of the central space of play grid. needed for Manhattan Distance


    def __init__(self, heuristic, grid):
        self.state = G.PegSolitaireState(None, heuristic, grid)

    def issolution(self, state):
        out = state.getRepresentation().remainingBalls() == 1
        return out

    def heuristic(self):
        return self.state.getHeuristic()
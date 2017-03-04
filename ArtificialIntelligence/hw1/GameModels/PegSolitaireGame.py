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

    def __init__(self, heuristic, grid):
        self.state = G.PegSolitaireState(heuristic, grid)

    @staticmethod
    def issolution(grid):
        out = (grid.remainingBalls == 1)
        return out

    def heuristic(self):
        return self.state.getHeuristic()
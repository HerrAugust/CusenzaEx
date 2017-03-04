#This class is a container of the state of the game. It contains various, general information about it

import GameModels as G

class PegSolitaireState:

    def __init__(self, parent, heuristic, grid):
        self.parent = parent
        self.H = heuristic
        self.representation = G.PegSolitaireRepresentation(grid)

    def getRepresentation(self):
        return self.representation

    def getHeuristic(self):
        return self.heuristic
#This class is a container of the state of the game. It contains various, general information about it

import GameModels as G
class PegSolitaireState:

    def __init__(self, heuristic, grid, parentState = None):
        self.H = heuristic
        self.representation = G.PegSolitaireRepresentation(grid)
        self.parentState = parentState

    def getRepresentation(self):
        return self.representation

    def getHeuristic(self):
        return self.H
    
    def parent(self):
        return self.parentState
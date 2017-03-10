#This class is a container of the state of the game. It contains various, general information about it

import GameModels as G
class PegSolitaireState:
    
    lastID = 1 #needed for debug

    def __init__(self, heuristic, grid, parentState = None):
        self.H = heuristic
        self.representation = G.PegSolitaireRepresentation(grid)
        self.parentState = parentState
        
        PegSolitaireState.lastID += 1
        self.identifier = PegSolitaireState.lastID

    def getRepresentation(self):
        return self.representation

    def getHeuristic(self):
        return self.H
    
    def parent(self):
        return self.parentState
    
    #needed for debug
    def getStateName(self):
        stateName = str(self.level) + ", id= " + str(self.identifier)
        return stateName
        
    def setLevel(self, level):
        self.level = level
        
    def getLevel(self):
        return self.level
    
    def __eq__(self, other):
        return self.representation == other.representation
    
    #needed for set (add and remove) and list (remove)
    def __hash__(self):
        grid = self.representation.grid
        l = ""
        for j in range(0,len(grid)):
            for k in range(0,len(grid[0])):
                if grid[j][k] != 2:
                    l += str(grid[j][k])
        h = int(l)
        
#        h = hash(self.representation)
        return h
       
    def __repr__(self):
        return repr(self.representation)   
        
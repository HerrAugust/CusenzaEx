#This class represents the game grid
#The grid is a list of lists. Pegs are represented as 1, void cells as 0.

class PegSolitaireRepresentation:
    centerX = 3  #static var. it is the column of the central space of play grid. needed for Manhattan Distance
    centerY = 3  #static var. it is the row of the central space of play grid. needed for Manhattan Distance
    
    def __init__(self, grid):
        self.grid = grid
        self.gridRows = len(grid)
        self.gridCols = len(grid[0])
        self.remainingBalls = 0
        for i in range(0,len(self.grid[0])):
            for j in range(0,len(self.grid)):
                if self.grid[i][j] == 1:
                    self.remainingBalls += 1
        self.valf = -1
        
    def __hash__(self):
        i = 1
        hash = 0
        for j in range(0,len(self.grid)):
            for k in range(0,len(self.grid[0])):
                if self.grid[j][k] == 1:
                    hash += i*self.grid[j][k]
                    i += 1
        return hash
    
    def f(self, game):
        g = 1 #could be any number. this is the cost to move a peg
        h = game.heuristic().H(self)
        self.valf = g + h
        return self.valf
    
    def grid(self):
        return self.grid
    
    def pegExists(self, peg):
        val = self.grid[peg.getRow()][peg.getCol()]
        if val == 1:
            return True
        return False
    
    def remainingBalls(self):
        r = 0
        for i in range(0,len(self.grid)):
            for j in range(0, len(self.grid[0])):
                if self.grid[i][j] == 1:
                    r += 1
        return r
    
    
    
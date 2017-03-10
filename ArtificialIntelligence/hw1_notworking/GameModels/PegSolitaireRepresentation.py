#This class represents the game grid
#The grid is a list of lists. Pegs are represented as 1, void cells as 0.

class PegSolitaireRepresentation:
    centerX = 3  #static var. it is the column of the central space of play grid. needed for Manhattan Distance
    centerY = 3  #static var. it is the row of the central space of play grid. needed for Manhattan Distance
    
    def __init__(self, grid):
        self.grid = grid
        self.gridRows = len(grid)
        self.gridCols = len(grid[0])
        self.remainingBalls = self.remainingBalls()
        self.valf = -1
        
    def __hash__(self):
        l = ""
        for j in range(0,len(self.grid)):
            for k in range(0,len(self.grid[0])):
                if self.grid[j][k] != 2:
                    l += str(self.grid[j][k])
        h = int(l)
        return h
    
    def __repr__(self):
        rows = len(self.grid)
        cols = len(self.grid[0])
        t = ""
        for i in range(0,rows):
            toprint = ""
            for j in range(0,cols):
                toprint = toprint + " " + str(self.grid[i][j])
            t += toprint + "\n"
        return t
    
    def __eq__(self, other):
        for i in range(0, len(self.grid)):
            for j in range(0, len(self.grid[0])):
                if self.grid[i][j] != other.grid[i][j]:
                    return False
        return True
    
    def f(self, state):
        heuristic = state.getHeuristic()
        g = 1 #could be any number. this is the cost to move a peg
        h = heuristic.H(state)
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
    
    
    
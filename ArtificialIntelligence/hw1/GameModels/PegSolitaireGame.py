
import GameModels as G
from   copy import deepcopy

class Game:

    def __init__(self, initialState=None, heuristic=None):
        self.state = initialState
        self.heuristic = heuristic

    def neighbors(self, state):
        out = set([])
        return out

    def getState(self):
        return self.state

    def isSolution(self, state):
        return True

class PegSolitaireGame(Game):
    
    def isSolution(self, state):
        gridRepresentation = state.representation
        out = (gridRepresentation.remainingBalls == 1)
        return out
        
    def map(self,j):
        directions = ["n", "e", "s", "w"]
        return directions[j]
    
    #given the current grid, it returns the possible moves
    def neighbors(self, state):
        possiblegrids = set()
        
        grid = state.getRepresentation().grid 
        
        #visit the whole grid, looking for possible moves
        for i in range(0,len(grid)):
            for j in range(0,len(grid[0])):
                peg = G.Peg(i,j)
                #if peg exists, i.e. current cell is not a hole or a corner...
                if not state.getRepresentation().pegExists(peg):
                    continue
                #...find a possible move for this peg (note: each peg could be moved also in all the 4 directions)
                for direction in range(0,4):
                    if self.moveIsLegal(peg, self.map(direction), grid):
                        copy = deepcopy(grid)
                        newgrid = self.makeMove(copy, peg, self.map(direction))
                        possiblegrids.add(newgrid)
        return possiblegrids
    
    def moveIsLegal(self, peg, direction, grid): #(3,4) n
        r = peg.getRow()
        c = peg.getCol()
        gridRows = len(grid)
        gridCols = len(grid[0])
        if direction == 'n':
            if r == 0:
                return False
            if r-1 >= 0 and grid[r-1][c] == 0:
                return True
            if r == 1:
                return False
            if r-2 >= 0 and grid[r-2][c] == 0:
                return True
            if r-2 >= 0 and grid[r-2][c] == 1:
                return False
        elif direction == 'e':
            if r == gridCols-1:
                return False
            if c+1 < gridCols and grid[r][c+1] == 0:
                return True
            if r == gridCols-2:
                return False
            if c+2 < gridCols and grid[r][c+2] == 0:
                return True
            if c+2 < gridCols and grid[r][c+2] == 1:
                return False
        elif direction == 's':
            if r == gridRows-1:
                return False
            if r+1 < gridRows and grid[r+1][c] == 0:
                return True
            if r == gridRows-2:
                return False
            if r+2 < gridRows and grid[r+2][c] == 0:
                return True
            if r+2 < gridRows and grid[r+2][c] == 1:
                return False
        else: #west
            if r == gridCols-1:
                return False
            if c-1 >= 0 and grid[r][c-1] == 0:
                return True
            if r == gridCols-2:
                return False
            if c-2 >= 0 and grid[r][c-2] == 0:
                return True
            if c-2 >= 0 and grid[r][c-2] == 1:
                return False


    #assumes move is legal
    def makeMove(self, grid, peg, direction):
        r = peg.getRow()
        c = peg.getCol()
        gridRows = len(grid)
        gridCols = len(grid[0])
        if direction == 'n':
            if r-1 >= 0 and grid[r-1][c] == 0:
                grid[r-1][c] = 1
                grid[r][c] = 0
            else: #move north, eating peg
                grid[r][c] = 0
                grid[r-1][c] = 0
                #self.remainingBalls -= 1
                grid[r-2][c] = 1
        elif direction == 'e':
            if c+1 < gridCols and grid[r][c+1] == 0:
                grid[r][c+1] = 1
                grid[r][c] = 0
            else:
                grid[r][c] = 0
                grid[r][c+1] = 0
                #self.remainingBalls -= 1
                grid[r][c+2] = 1
        elif direction == 's':
            if r+1 < gridRows and grid[r+1][c] == 0:
                grid[r+1][c] = 1
                grid[r][c] = 0
            else:
                grid[r][c] = 0
                grid[r+1][c] = 0
                #self.remainingBalls -= 1
                grid[r+2][c] = 1
        else: #direction == 'w'
            if c-1 >= 0 and grid[r][c-1] == 0:
                grid[r][c-1] = 1
                grid[r][c] = 0
            else:
                grid[r][c] = 0
                grid[r][c-1] = 0
                #self.remainingBalls -= 1
                grid[r][c-2] = 1
        return G.PegSolitaireState(self.state.getHeuristic(), grid, self.state)
    
    
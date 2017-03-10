
import GameModels as G
from   copy import deepcopy



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
        self.state = state
        self.heuristic = state.getHeuristic()
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
                        newstate = self.makeMove(copy, peg, self.map(direction))
                        fatherLevel = state.getLevel()
                        newstate.setLevel(fatherLevel + 1)
                        possiblegrids.add(newstate)
        return possiblegrids
    
    def moveIsLegal(self, peg, direction, grid): #(3,4) n
        r = peg.getRow()
        c = peg.getCol()
        gridRows = len(grid)
        gridCols = len(grid[0])
        if direction == 'n':
            if r == 0: # |o
                return False
            if r == 1: # |oo
                return False
            if r > 1 and grid[r-2][c] == 0 and grid[r-1][c] == 1: #xoo 
                return True
            if r > 1 and grid[r-2][c] == 1 and grid[r-1][c] == 1: #ooo
                return False
        elif direction == 'e':
            if c == gridCols-1: # |o
                return False
            if c == gridCols-2: # |oo
                return False
            if c < gridCols-2 and grid[r][c+2] == 0 and grid[r][c+1] == 1: # xoo
                return True
            if c < gridCols-2 and grid[r][c+2] == 1 and grid[r][c+1] == 1: # ooo
                return False
        elif direction == 's':
            if r == gridRows-1:
                return False
            if r == gridRows-2:
                return False
            if r < gridRows-2 and grid[r+2][c] == 0 and grid[r+1][c] == 1:
                return True
            if r < gridRows-2 and grid[r+2][c] == 1 and grid[r+1][c] == 1:
                return False
        else: #west
            if c == 0:
                return False
            if c == 1:
                return False
            if c > 1 and grid[r][c-2] == 0 and grid[r][c-1] == 1:
                return True
            if c > 1 and grid[r][c-2] == 1 and grid[r][c-1] == 1:
                return False


    #assumes move is legal
    def makeMove(self, grid, peg, direction):
        r = peg.getRow()
        c = peg.getCol()
        if direction == 'n': #move north, eating peg
            grid[r][c] = 0
            grid[r-1][c] = 0
            grid[r-2][c] = 1
        elif direction == 'e':
            grid[r][c] = 0
            grid[r][c+1] = 0
            grid[r][c+2] = 1
        elif direction == 's':
            grid[r][c] = 0
            grid[r+1][c] = 0
            grid[r+2][c] = 1
        else: #direction == 'w'
            grid[r][c] = 0
            grid[r][c-1] = 0
            grid[r][c-2] = 1
        newstate = G.PegSolitaireState(self.state.getHeuristic(), grid, self.state)
        return newstate
    
    
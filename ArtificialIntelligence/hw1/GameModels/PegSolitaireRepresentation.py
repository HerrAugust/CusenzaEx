#This class represents the game grid
#The grid is a list of lists. Pegs are represented as 1, void cells as 0.

import GameModels as G
from copy import deepcopy

class PegSolitaireRepresentation:
    centerX = 0  #static var. it is the column of the central space of play grid. needed for Manhattan Distance
    centerY = 0  #static var. it is the row of the central space of play grid. needed for Manhattan Distance
    
    def init(self, grid):
        self.grid = grid
        self.gridRows = len(grid)
        self.gridCols = len(grid[0])
        self.remainingBalls = 0
        for i in range(0,len(self.grid[0])):
            for j in range(0,len(self.grid)):
                if self.grid[i][j] == 1:
                    self.remainingBalls += 1
        self.valf = -1
        
    def getBitMap(self):
        bitmap = 0
        for i in range(0,len(self.grid)):
            for j in range(0,len(self.grid[0])):
                bitmap |= int("{0:b}".format(self.grid[i][j]))
                if j != len(self.grid) - 1 or i != len(self.grid[0]) - 1:
                    bitmap <<= 1;
        return bitmap        
    
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
        return self.remainingBalls
    
    def getPossibleMoves(self):
        raise NotImplementedError("Please implement this method")
    
    def bestDirection(self, peg):
        raise NotImplementedError("Please implement this method")
    
    def map(self,j):
        directions = ["n", "e", "s", "w"]
        return directions[j]
    
    def moveIsLegal(self, peg, direction):
        raise NotImplementedError("Please implement this method")
    
    def makeMove(self, peg, direction):
        raise NotImplementedError("Please implement this method")

class PegSolitaireClassicRepresentation(PegSolitaireRepresentation):

    def __init__(self, grid):
        PegSolitaireRepresentation.init(self, grid)
    
    #given the current grid, it returns the possible moves
    def getPossibleMoves(self):
        possiblegrids = []
        #visit the whole grid, looking for possible moves
        for i in range(0,len(self.grid)):
            for j in range(0,len(self.grid[0])):
                peg = G.Peg(i,j)
                #if peg exists, i.e. current cell is not a hole or a corner...
                if not self.pegExists(peg):
                    continue
                #...find a possible move for this peg (note: each peg could be moved also in all the 4 directions)
                excluded = []
                for d in range(0,4):
                    direction = self.bestDirection(peg)
                    if direction is not None and direction not in excluded:
                        copy = deepcopy(self.grid)
                        newgrid = self.makeMove(copy, peg, direction)
                        newgrid.centerX = self.centerX
                        newgrid.centerY = self.centerY
                        possiblegrids.append(newgrid)
                        excluded.append(direction)
        return possiblegrids
    
    def bestDirection(self, peg, excluded = []): #north, south, east, west
        row = peg.getRow()
        col = peg.getCol()
        #north
        if not "n" in excluded and row - 2 >= 0 and self.grid[row-1][col] == 1 and self.grid[row-2][col] == 0:
            return "n" 
        #east
        if not "e" in excluded and col + 2 < self.gridCols and self.grid[row][col+1] == 1 and self.grid[row][col+2] == 0:
            return "e" 
        #south
        if not "s" in excluded and row + 2 < self.gridRows and self.grid[row+1][col] == 1 and self.grid[row+2][col] == 0:
            return "s" 
        #west
        if not "w" in excluded and col - 2 >= 0 and self.grid[row][col-1] == 1 and self.grid[row][col-2] == 0:
            return "w" 
        
        return None

    def moveIsLegal(self, peg, direction): #(3,4) n NOT USED
        r = peg.getRow()
        c = peg.getCol()
        if direction == 'n':
            if r == 0:
                return False
            if r-1 >= 0 and self.grid[r-1][c] == 0:
                return True
            if r == 1:
                return False
            if r-2 >= 0 and self.grid[r-2][c] == 0:
                return True
            if r-2 >= 0 and self.grid[r-2][c] == 1:
                return False
        elif direction == 'e':
            if r == self.gridCols-1:
                return False
            if c+1 < self.gridCols and self.grid[r][c+1] == 0:
                return True
            if r == self.gridCols-2:
                return False
            if c+2 < self.gridCols and self.grid[r][c+2] == 0:
                return True
            if c+2 < self.gridCols and self.grid[r][c+2] == 1:
                return False
        elif direction == 's':
            if r == self.gridRows-1:
                return False
            if r+1 < self.gridRows and self.grid[r+1][c] == 0:
                return True
            if r == self.gridRows-2:
                return False
            if r+2 < self.gridRows and self.grid[r+2][c] == 0:
                return True
            if r+2 < self.gridRows and self.grid[r+2][c] == 1:
                return False
        else: #west
            if r == self.gridCols-1:
                return False
            if c-1 >= 0 and self.grid[r][c-1] == 0:
                return True
            if r == self.gridCols-2:
                return False
            if c-2 >= 0 and self.grid[r][c-2] == 0:
                return True
            if c-2 >= 0 and self.grid[r][c-2] == 1:
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
                self.remainingBalls -= 1
                grid[r-2][c] = 1
        elif direction == 'e':
            if c+1 < gridCols and grid[r][c+1] == 0:
                grid[r][c+1] = 1
                grid[r][c] = 0
            else:
                grid[r][c] = 0
                grid[r][c+1] = 0
                self.remainingBalls -= 1
                grid[r][c+2] = 1
        elif direction == 's':
            if r+1 < gridRows and grid[r+1][c] == 0:
                grid[r+1][c] = 1
                grid[r][c] = 0
            else:
                grid[r][c] = 0
                grid[r+1][c] = 0
                self.remainingBalls -= 1
                grid[r+2][c] = 1
        else: #direction == 'w'
            if c-1 >= 0 and grid[r][c-1] == 0:
                grid[r][c-1] = 1
                grid[r][c] = 0
            else:
                grid[r][c] = 0
                grid[r][c-1] = 0
                self.remainingBalls -= 1
                grid[r][c-2] = 1
        return PegSolitaireClassicRepresentation(grid)
    
class PegSolitaireRevisitedRepresentation(PegSolitaireRepresentation):
    def __init__(self, grid):
        PegSolitaireRepresentation.init(self, grid)

    def bestDirection(self, peg):
        row = peg.getRow()
        col = peg.getCol()
        #north
        if row - 2 >= 0 and self.grid[row-1][col] == 1 and self.grid[row-2][col] == 0:
            return "n" 
        #east
        if col + 2 < self.gridCols and self.grid[row][col+1] == 1 and self.grid[row][col+2] == 0:
            return "e" 
        #south
        if row + 2 < self.gridRows and self.grid[row+1][col] == 1 and self.grid[row+2][col] == 0:
            return "s" 
        #west
        if col - 2 >= 0 and self.grid[row][col-1] == 1 and self.grid[row][col-2] == 0:
            return "w" 
        
        #if no best direction exists for this peg, choose the one that goes to center, if it exists
        #if peg is in the north, it should go to south (center)
        if row < self.centerY - 1 and self.moveIsLegal(peg, "s"): #-1 to take only pegs in first two rows
            return "s"
        if row > self.centerY + 1 and self.moveIsLegal(peg, "n"):
            return "n"
        if col > self.centerX - 1 and self.moveIsLegal(peg, "e"):
            return "e"
        if col > self.centerX + 1 and self.moveIsLegal(peg, "w"):
            return "w"
        
        #if not possible to optimize direction, choose a random, legal move, if it exists
        for j in range(0,4):
            if self.moveIsLegal(peg, self.map(j)) is True:
                return self.map(j)
            
        #if no move is possible for this peg
        return None

    def moveIsLegal(self, peg, direction): #(3,4) n
        r = peg.getRow()
        c = peg.getCol()
        if direction == 'n':
            if r == 0:
                return False
            if r-1 >= 0 and self.grid[r-1][c] == 0:
                return True
            if r == 1:
                return False
            if r-2 >= 0 and self.grid[r-2][c] == 0:
                return True
            if r-2 >= 0 and self.grid[r-2][c] == 1:
                return False
        elif direction == 'e':
            if r == self.gridCols-1:
                return False
            if c+1 < self.gridCols and self.grid[r][c+1] == 0:
                return True
            if r == self.gridCols-2:
                return False
            if c+2 < self.gridCols and self.grid[r][c+2] == 0:
                return True
            if c+2 < self.gridCols and self.grid[r][c+2] == 1:
                return False
        elif direction == 's':
            if r == self.gridRows-1:
                return False
            if r+1 < self.gridRows and self.grid[r+1][c] == 0:
                return True
            if r == self.gridRows-2:
                return False
            if r+2 < self.gridRows and self.grid[r+2][c] == 0:
                return True
            if r+2 < self.gridRows and self.grid[r+2][c] == 1:
                return False
        else: #west
            if r == self.gridCols-1:
                return False
            if c-1 >= 0 and self.grid[r][c-1] == 0:
                return True
            if r == self.gridCols-2:
                return False
            if c-2 >= 0 and self.grid[r][c-2] == 0:
                return True
            if c-2 >= 0 and self.grid[r][c-2] == 1:
                return False

    #assumes move is legal
    def makeMove(self, peg, direction):
        r = peg.getRow()
        c = peg.getCol()
        if direction == 'n':
            if r-1 >= 0 and self.grid[r-1][c] == 0:
                self.grid[r-1][c] = 1
                self.grid[r][c] = 0
            else: #move north, eating peg
                self.grid[r][c] = 0
                self.grid[r-1][c] = 0
                self.remainingBalls -= 1
                self.grid[r-2][c] = 1
        elif direction == 'e':
            if c+1 < self.gridCols and self.grid[r][c+1] == 0:
                self.grid[r][c+1] = 1
                self.grid[r][c] = 0
            else:
                self.grid[r][c] = 0
                self.grid[r][c+1] = 0
                self.remainingBalls -= 1
                self.grid[r][c+2] = 1
        elif direction == 's':
            if r+1 < self.gridRows and self.grid[r+1][c] == 0:
                self.grid[r+1][c] = 1
                self.grid[r][c] = 0
            else:
                self.grid[r][c] = 0
                self.grid[r+1][c] = 0
                self.remainingBalls -= 1
                self.grid[r+2][c] = 1
        else: #direction == 'w'
            if c-1 >= 0 and self.grid[r][c-1] == 0:
                self.grid[r][c-1] = 1
                self.grid[r][c] = 0
            else:
                self.grid[r][c] = 0
                self.grid[r][c-1] = 0
                self.remainingBalls -= 1
                self.grid[r][c-2] = 1
        return PegSolitaireRevisitedRepresentation(self.grid)
    
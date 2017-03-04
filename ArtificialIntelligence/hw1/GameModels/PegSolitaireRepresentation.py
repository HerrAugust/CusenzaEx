#This class represents the game grid
#The grid is a list of lists. Pegs are represented as 1, void cells as 0.

from GameModels import PegSolitaireGame as Game

class PegSolitaireRepresentation:

    centerX = 0  #static var. it is the column of the central space of play grid. needed for Manhattan Distance
    centerY = 0  #static var. it is the row of the central space of play grid. needed for Manhattan Distance

    def __init__(self, grid):
        self.grid = grid
        self.gridRows = len(grid)
        self.gridCols = len(grid[0])
        self.remainingBalls = 0
        for i in range(0,len(self.grid[0])):
            for j in range(0,len(self.grid)):
                if self.grid[i][j] == 1:
                    self.remainingBalls += 1

    def grid(self):
        return self.grid

    def remainingBalls(self):
        return self.remainingBalls

    def pegExists(self, peg):
        if self.grid[peg.getRow()][peg.getCol()] == 0:
            return False
        return True

    def moveIsLegal(self, peg, direction):
        r = peg.getRow()
        c = peg.getCol()
        jn=self.grid[r-1][c]
        if direction == 'n':
            if r == 0:
                return False
            if self.grid[r-1][c] == 0:
                return True
            if r == 1:
                return False
            if self.grid[r-2][c] == 0:
                return True
            if self.grid[r-2][c] == 1:
                return False
        elif direction == 'e':
            if r == self.gridCols-1:
                return False
            if self.grid[r][c+1] == 0:
                return True
            if r == self.gridCols-2:
                return False
            if self.grid[r][c+2] == 0:
                return True
            if self.grid[r][c+2] == 1:
                return False
        elif direction == 's':
            if r == self.gridRows-1:
                return False
            if self.grid[r+1][c] == 0:
                return True
            if r == self.gridRows-2:
                return False
            if self.grid[r+2][c] == 0:
                return True
            if self.grid[r+2][c] == 1:
                return False
        else: #west
            if r == self.gridCols-1:
                return False
            if self.grid[r][c-1] == 0:
                return True
            if r == self.gridCols-2:
                return False
            if self.grid[r][c-2] == 0:
                return True
            if self.grid[r][c-2] == 1:
                return False

    #assumes move is legal
    def makeMove(self, peg, direction):
        r = peg.getRow()
        c = peg.getCol()
        if direction == 'n':
            if self.grid[r-1][c] == 0:
                self.grid[r-1][c] = 1
                self.grid[r][c] = 0
            else: #move north, eating peg
                self.grid[r][c] = 0
                self.grid[r-1][c] = 0
                self.remainingBalls -= 1
                self.grid[r-2][c] = 1
        elif direction == 'e':
            if self.grid[r][c+1] == 0:
                self.grid[r][c+1] = 1
                self.grid[r][c] = 0
            else:
                self.grid[r][c] = 0
                self.grid[r][c+1] = 0
                self.remainingBalls -= 1
                self.grid[r][c+2] = 1
        elif direction == 's':
            if self.grid[r+1][c] == 0:
                self.grid[r+1][c] = 1
                self.grid[r][c] = 0
            else:
                self.grid[r][c] = 0
                self.grid[r+1][c] = 0
                self.remainingBalls -= 1
                self.grid[r+2][c] = 1
        else: #direction == 'w'
            if self.grid[r][c-1] == 0:
                self.grid[r][c-1] = 1
                self.grid[r][c] = 0
            else:
                self.grid[r][c] = 0
                self.grid[r][c-1] = 0
                self.remainingBalls -= 1
                self.grid[r][c-2] = 1
        return self.grid
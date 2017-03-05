#This class represents the game grid
#The grid is a list of lists. Pegs are represented as 1, void cells as 0.

class PegSolitaireRepresentation:
    centerX = 0  #static var. it is the column of the central space of play grid. needed for Manhattan Distance
    centerY = 0  #static var. it is the row of the central space of play grid. needed for Manhattan Distance
    
    def init(self, grid):
        self.grid = grid
        self.remainingBalls = 0
    
    def grid(self):
        return self.grid
    
    def remainingBalls(self):
        return self.remainingBalls
    
    def moveIsLegal(self, peg, direction):
        raise NotImplementedError("Please implement this method")
    
    def makeMove(self, peg, direction):
        raise NotImplementedError("Please implement this method")

class PegSolitaireClassicRepresentation(PegSolitaireRepresentation):

    def __init__(self, grid):
        self.grid = grid
        self.gridRows = len(grid)
        self.gridCols = len(grid[0])
        self.remainingBalls = 0
        for i in range(0,len(self.grid[0])):
            for j in range(0,len(self.grid)):
                if self.grid[i][j] == 1:
                    self.remainingBalls += 1

    def remainingBalls(self):
        return self.remainingBalls

    def pegExists(self, peg):
        val = self.grid[peg.getRow()][peg.getCol()]
        if val == 1:
            return True
        return False

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
        return PegSolitaireClassicRepresentation(self.grid)
    
class PegSolitaireRevisitedRepresentation(PegSolitaireRepresentation):
    def __init__(self, grid):
        self.grid = grid
        self.gridRows = len(grid)
        self.gridCols = len(grid[0])
        self.remainingBalls = 0
        for i in range(0,len(self.grid[0])):
            for j in range(0,len(self.grid)):
                if self.grid[i][j] == 1:
                    self.remainingBalls += 1

    def remainingBalls(self):
        return self.remainingBalls

    def pegExists(self, peg):
        val = self.grid[peg.getRow()][peg.getCol()]
        if val == 1:
            return True
        return False

    def moveIsLegal(self, peg, direction):
        pass

    #assumes move is legal
    def makeMove(self, peg, direction):
        pass
    
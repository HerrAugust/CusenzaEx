import PegSolitaireGame
class Peg:
    #int row
    #int column
    #bool exists if this peg has not been eaten during the game

    f = 0

    def __init__(self, row, column):
        self.row = row
        self.column = column

    def equals(self, other):
        if self.row == other.row and self.column == other.column:
            return True
        return False

    def getRow(self):
        return self.row

    def getCol(self):
        return self.column

    #it checks the peg potition does not exceed the play grid
    def isLegal(self):
        if self.row < 0 or self.column < 0:
            return False
        if self.row > PegSolitaireGame.gridRows or self.column > PegSolitaireGame.gridCols:
            return False
        return True

    def __repr__(self):
        return "(%d,%d); f=%d" % (self.row, self.column, self.f)

    def __eq__(self, other):
        if self.row == other.row and self.column == other.column:
            return True
        return False

    def __hash__(self):
        return 2 * self.row + self.column

    def move(self, grid, direction):
        r = 0
        c = 0
        if direction == 'n':
            if grid[r - 1][c] == 0:
                r = self.row-1
                c = self.column
            else:  # move north, eating peg
                r = self.row-2
                c = self.column
                grid[r - 2][c] = 1
        elif direction == 'e':
            if grid[r][c + 1] == 0:
                r = self.row
                c = self.column+1
            else:
                r = self.row
                c = self.column+2
        elif direction == 's':
            if grid[r + 1][c] == 0:
                r = self.row+1
                c = self.column
            else:
                r = self.row+2
                c = self.column
        else:  # direction == 'w'
            if grid[r][c - 1] == 0:
                c = self.column-1
                r = self.row
            else:
                c = self.column -2
                r = self.row
        return Peg(r,c)
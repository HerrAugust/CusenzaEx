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
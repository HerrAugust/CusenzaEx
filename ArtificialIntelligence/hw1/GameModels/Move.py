class Move:
    def __init__(self, peg, direction):
        self.peg = peg
        self.direction = direction

    def getDirection(self):
        return self.direction

    def getPeg(self):
        return self.peg

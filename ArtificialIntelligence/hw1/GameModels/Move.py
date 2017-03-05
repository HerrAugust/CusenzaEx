class Move:
    def __init__(self, peg, direction):
        self.peg = peg
        self.direction = direction

    def getDirection(self):
        return self.direction

    def getPeg(self):
        return self.peg

    def __str__(self):
        return str(self.peg) + " moved to " + self.direction 
    
    def __repr__(self):
        return str(self.peg) + " to " + self.direction
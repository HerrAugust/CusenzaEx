__author__ = 'giodegas'

class Heuristic:

    def __init__(self):
        pass

    def H(self, state):
        return 1

class CheckerHeuristic(Heuristic):

    def H0(self, state):
        # number of whites - number of blacks
        out = 0
        for r in range(0,8):
            for c in range(0,8):
                piece = state.getRepresentation().getPiece(r,c)
                if 'w' in piece:
                    out += len(piece)
                elif 'k' in piece:
                    out -= len(piece)
        return out

    def Hl(self, state, l, turn):
        if len(state.getRepresentation().getBoard()[6]) < 8:
            pass
        if l == 0:
            return self.H0(state)
        if turn == 'w': # first call goes here. w = machine
            nexTurn = 'k'
            print "H1(), am in level", str(l), "maximizing"
            print "heuristic.H1(). state:",str(state)
            return max([self.Hl(x, l-1, nexTurn) for x in state.neighbors(nexTurn)]) # max of a list. for each neighbors(macchina), apply H()
        else:
            nexTurn = 'w'
            print "H1(), am in level", str(l), "minimizing"
            print "heuristic.H1(). state:",str(state)
            return min([self.Hl(x, l-1, nexTurn) for x in state.neighbors(nexTurn)])
        
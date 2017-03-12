__author_base__ = 'giodegas' # author of base version

class Heuristic:

    def __init__(self):
        pass

    def H(self, state, l, turn, alfabeta):
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
    
    def Hl_WithoutAlfabeta(self, state, l, turn, alfabeta): # alfabeta is the father node's value to carry around to perform Alfa-Beta Pruning on this prediction node
        if len(state.getRepresentation().getBoard()[6]) < 8:
            pass
        if l == 0:
            return self.H0(state)
        if turn == 'w': # first call goes here. w = machine
            nexTurn = 'k'
            print "H1(), am in level", str(l), "maximizing"
            print "heuristic.H1(). state:",str(state)
            return max([self.Hl(x, l-1, nexTurn, alfabeta) for x in state.neighbors(nexTurn)]) # max of a list. for each neighbors(macchina), apply H()
        else:
            nexTurn = 'w'
            print "H1(), am in level", str(l), "minimizing"
            print "heuristic.H1(). state:",str(state)
            return min([self.Hl(x, l-1, nexTurn, alfabeta) for x in state.neighbors(nexTurn)])

    def H(self, state, l, turn, alfabeta): # alfabeta is the father node's value to carry around to perform Alfa-Beta Pruning on this prediction node
        if l == 0:
            return { "f": self.H0(state), "state": state }
        if turn == 'w': # first call goes here. w = machine
            nexTurn = 'k'
            print "H1(), am in level", str(l), "maximizing"
            print "heuristic.H1(). state:",str(state)
            n = state.neighbors(turn)
            h_vals = []
            for x in n:
                v = self.Hl(x, l - 1, nexTurn, alfabeta)
                if v["f"] > alfabeta:  # stop here and do not deep other paths of the tree
                    alfabeta = v["f"]
                h_vals.append(v)
            i = h_vals.index(max(h_vals))
            return h_vals[i]
            #return max([self.Hl(x, l-1, nexTurn, alfabeta) for x in state.neighbors(nexTurn)]) # max of a list. for each neighbors(macchina), apply H()
        else:
            nexTurn = 'w'
            print "H1(), am in level", str(l), "minimizing"
            print "heuristic.H1(). state:",str(state)
            n = state.neighbors(turn)
            h_vals = [] # list of heuristic value of child-nodes (neighbors)
            for x in n:
                v = self.Hl(x, l-1, nexTurn, alfabeta)
                if alfabeta >= v["f"]:  # stop here and do not deep other paths of the tree
                    return v
                h_vals.append(v)
            i = h_vals.index(min(h_vals))
            return min(h_vals[i])
            #return min([self.Hl(x, l-1, nexTurn, alfabeta) for x in state.neighbors(nexTurn)])
        
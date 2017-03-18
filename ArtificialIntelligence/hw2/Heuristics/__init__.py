import GameModels as M

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
                piece = state.getRepresentation().getPiece(r, c)
                if 'w' in piece:
                    out += len(piece)
                elif 'k' in piece:
                    out -= len(piece)
        return out

    # It does not modify the "state" variable!!!
    # returns an integer
    def H(self, state, l, turn, alfabeta):
        if l == 0:
            return self.H0(state)
        if turn == 'w':  # TRIANGLE UP. w = macchina
            nexTurn = 'k'
            n = state.neighbors(turn)
            h_vals = []
            for x in n:
                x.setCurrentPlayer(turn)  # turn = w
                v = self.H(x, l - 1, nexTurn, alfabeta)
                if v > alfabeta:  # stop here and do not deep other paths of the tree
                    alfabeta = v
                h_vals.append(v)
            if len(h_vals) == 0:   
                return self.H0(state)
            m = max (h_vals)
            return m
        else:  # TRIANGLE DOWN. k = human
            nexTurn = 'w'
            n = state.neighbors(turn)
            h_vals = []  # list of heuristic value of child-nodes (neighbors)
            for x in n:
                x.setCurrentPlayer(turn)  # turn = k
                v = self.H(x, l - 1, nexTurn, alfabeta)
                if alfabeta >= v:  # stop here and do not deep other paths of the tree
                    return v
                h_vals.append(v)
            if len(h_vals) == 0:  # case one player wins
                return self.H0(state)
            m = min (h_vals)
            return m
            #return min([self.Hl(game, x, l - 1, nexTurn) for x in game.neighbors(turn)])
            
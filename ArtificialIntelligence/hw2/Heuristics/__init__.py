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
                piece = state.getPiece(r,c)
                if 'w' in piece:
                    out += len(piece)
                elif 'k' in piece:
                    out -= len(piece)
        return out

    def Hl(self, game, state, l, turn):
        if l == 0:
            return self.H0(state)
        if turn == 'w':
            nexTurn = 'k'
            return max([self.Hl(game, x, l-1, nexTurn) for x in game.neighbors(turn)])
        else:
            nexTurn = 'w'
            return min([self.Hl(game, x, l-1, nexTurn) for x in game.neighbors(turn)])

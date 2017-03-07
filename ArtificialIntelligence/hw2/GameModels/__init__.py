__author__ = 'giodegas'

# da debuggare e completare

import copy

def isEven(x):
    return (x % 2) == 0

class CheckerRepresentation:

    def __init__(self):
        self.board = {}
        # whites configuration
        for r in range(0,3):
            for c in range(0,8):
                if isEven(r+c):
                    self.board[r,c] = 'w'
        # blacks
        for r in range(5,8):
            for c in range(0,8):
                if isEven(r+c):
                    self.board[r,c] = 'k'

    def getPiece(self, r, c):
        # what if out of the board?
        try:
            return self.board[r,c]
        except KeyError:
            if (r in range(0,8)) and (c in range(0,8)):
                return ''
            return None

    def setPiece(self, r,c,piece):
        self.board[r,c] = piece

    def isFree(self, r, c):
        return self.getPiece(r,c)==''

    def isOpposite(self, turn, r, c):
        piece = self.getPiece(r,c)
        if piece:
            return len(piece)>0 and not turn in piece
        else:
            return False

    def isAmmissible(self, configuration):
        # faremo mosse solo ammissibili
        return True

class CheckerState:

    def __init__(self, heuristic):
        self.H = heuristic
        self.representation = CheckerRepresentation()

    def getPiece(self, r,c):
        return self.representation.getPiece(r,c)

    def setPiece(self, r,c,what):
        self.representation.setPiece(r,c,what)

    def isFree(self,r,c):
        return self.representation.isFree(r,c)

    def isOpposite(self, turn, r,c):
        return self.representation.isOpposite(turn, r,c)

class Game:

    def __init__(self, initialState=None, heuristic=None):
        self.state = initialState
        self.heuristic = heuristic

    def neighbors(self, state):
        out = set([])
        return out

    def getState(self):
        return self.state

    def solution(self, state):
        return True

class CheckerGame(Game):

    def __init__(self, heuristic):
        self.state = CheckerState(heuristic)

    def makeMove(self, state, r,c, rn, cn):
        out = copy.copy(state)
        piece = state.getPiece(r,c)
        out.setPiece(r,c,'')
        out.setPiece(rn,cn,piece)
        return out

    def makeEat(self, state, r, c, re, ce):
        out = self.makeMove(state, r,c, re,ce)
        out.setPiece((r+re)/2,(c+ce)/2,'')
        return out

    def neighbors(self, turn):
        # turn in ('w','k')
        # w : white
        # k : black
        state = self.state
        out = set([state])
        for r in range(0,8):
            for c in range(0,8):
                if isEven(r+c):
                    piece = state.getPiece(r,c)
                    if piece and turn in piece:
                        moves = [(1,-1),(1,1)] # ipotesi mossa del bianco
                        if len(piece)==2:
                            moves.add([(-1,-1),(-1,1)])
                        for m in moves:
                            rm,cm = r+m[0],c+m[1]
                            if r==2 and m==(1,1):
                                pass
                            if state.isFree(rm,cm):
                                newR = self.makeMove(state, r,c, rm, cm)
                                out.add(newR)
                            else:
                                # try to eat
                                mEats = [(rm+1,cm-1),(rm+1,cm+1)]
                                if len(piece)==2:
                                    mEats.add([(rm-1,cm-1),(rm-1,cm+1)])
                                for mE in mEats:
                                    if state.isOpposite(turn, rm,cm) and state.isFree(mE[0],mE[1]):
                                        newR = self.makeEat(state, r,c,mE[0],mE[1])
                                        out.add(newR)
        return out

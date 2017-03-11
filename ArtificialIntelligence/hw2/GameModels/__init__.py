
__author__ = 'giodegas'

# da debuggare e completare

import copy

class CheckerRepresentation:

    def __init__(self, board):
        self.board = board
        
    def player(self):
        return self.player

    def getPiece(self, r, c):
        # what if out of the board?
        print "repr, getpiece() ", str(r), " ",str(c)
        print str(self)
        piece = self.board[r][c]
        return piece

    def getBoard(self):
        return self.board

    def setPiece(self, r,c,piece):
        self.board[r,c] = piece

    def setCurrentPlayer(self, player):
        self.player = player

    def isFree(self, r, c):
        return self.getPiece(r,c) == ' '

    def getEnemy(self):
        if self.player == 'k':
            return 'w'
        else:
            return 'k'
        
    def printMatrix(self):
        s = "________________\n"
        for r in range(0,len(self.board)):
            row = ""
            for c in range(0,len(self.board[r])):
                row += self.board[r][c] + " "
            s += row + "\n"
        s += "____________________________"
        return s
        
    def __repr__(self):
        return self.printMatrix()
    
    def __str__(self):
        return self.printMatrix()

    def isAdmissible(self, r,c,er,ec):
        # you may move peg for 1, 2, 4, 6 diagonal distances (euclidean distance)
        if r == er and c == ec: #cannot stay in the same cell
            return False

        #if we stay in the board
        if r >= len(self.board) or c >= len(self.board[0]) or er >= len(self.board) or ec >= len(self.board[0]) or er < 0 or ec < 0:
            return False

        #if self.board[r][c] != self.player:
            #return False

        if self.isFree(er, ec) == False:
            return False

        # cannot move in the cell above, only diagonally
        if c == ec:
            return False
        
        return True
        """#human moves
        if self.player == 'k':
            if er == r-1:
                if self.isFree(er,ec):
                    return True
                return False
            if er == r-2: # in r-1 there must be an enemy
                return self.board[r-1][ec] == self.getEnemy()
            if er == r-4:
                return self.board[r - 3][ec] == self.getEnemy()
            if er == r-6:
                return self.board[r-5][ec] == self.getEnemy()
        else: # machine moves
            if er == r+1:
                if self.isFree(er, ec):
                    return True
                return False
            if er == r+2: # in r+1 there must be an enemy
                return self.board[r+1][ec] == self.getEnemy()
            if er == r+4:
                return self.board[r + 3][ec] == self.getEnemy()
            if er == r+6:
                return self.board[r+5][ec] == self.getEnemy()
        return False"""

    """
    Note: assumes that move is admissible (see self.isAdmissible())
    Does NOT affect self.board
    @return board representation with the move
    """
    def makeMove(self,r,c,er,ec):
        print "repr, makemove()"
        #copy board
        if len(self.board[6]) < 8:
            pass
        newboard = copy.deepcopy(self.board)
        if len(newboard[6]) < 3:
            pass
        print "deepcopy (%d,%d)->(%d,%d):" %(r,c,er,ec)
        print str(self)

        # return the one with the move
        peg = self.board[r][c] 
        newboard[r][c] = ' '
        newboard[er][ec] = peg

        if self.player == 'k': # human, towards north
            if er == r - 1:
                pass
            if er == r - 2:  # in r-1 there must be an enemy
                newboard[er-1] = ' '
            if er == r - 4:
                newboard[er-1] = ' '
                newboard[er-3] = ' '
            if er == r - 6:
                newboard[er - 1] = ' '
                newboard[er - 3] = ' '
                newboard[er - 5] = ' '
        else: # machine, towards south
            if er == r + 1:
                pass
            if er == r + 2:  # in r-1 there must be an enemy
                newboard[er+1] = ' '
            if er == r + 4:
                newboard[er+1] = ' '
                newboard[er+3] = ' '
            if er == r + 6:
                newboard[er + 1] = ' '
                newboard[er + 3] = ' '
                newboard[er + 5] = ' '

        return CheckerRepresentation(newboard)

class CheckerState:

    def __init__(self, heuristic, representation):
        self.H = heuristic
        self.representation = representation

    def getRepresentation(self):
        return self.representation

    def neighbors(self, turn):
        # turn in ('w','k')
        # w : white
        # k : black
        print "state, neighbors()"
        
        rep = self.getRepresentation()
        rows = len( rep.getBoard() )
        cols = len( rep.getBoard()[0] )
        out = set()
        for r in range(0, 8):
            for c in range(0, 8):
                print str(self)
                print "state, neighbors(). r=",str(r), " c=", str(c)
                if self.getRepresentation().getPiece(r,c) == ' ':
                    continue

                if turn == 'w': # machine tries to maximize
                    # moving towards south-east
                    p1 = p2 = False  # true if previous if is successful
                    if self.isAdmissible(r, c, r + 1, c + 1):
                        newstate = self.makeMove(r, c, r + 1, c + 1)
                        out.add(newstate)
                    else:
                        if r + 1 < rows and c + 1 < cols and rep.getPiece(r + 1, c + 1) == 'k' and self.isAdmissible(r,
                                                                                                                    c,
                                                                                                                    r + 2,
                                                                                                                    c + 2):
                            newstate = self.makeMove(r, c, r + 2, c + 2)
                            out.add(newstate)
                            p1 = True
                        if p1 and r + 3 < rows and c + 3 < cols and rep.getPiece(r + 3,
                                                                                c + 3) == 'k' and self.isAdmissible(r,
                                                                                                                    c,
                                                                                                                    r + 4,
                                                                                                                    c + 4):
                            newstate = self.makeMove(r, c, r + 4, c + 2)
                            out.add(newstate)
                            p2 = True
                        if p2 and r - 5 < rows and c + 5 < cols and rep.getPiece(r + 5,
                                                                                c + 5) == 'k' and self.isAdmissible(r,
                                                                                                                    c,
                                                                                                                    r + 6,
                                                                                                                    c + 6):
                            newstate = self.makeMove(r, c, r + 6, c + 2)
                            out.add(newstate)
                    # moving toward south-west
                    p1 = p2 = False  # true if previous if is successful
                    if self.isAdmissible(r, c, r + 1, c - 1):
                        newstate = self.makeMove(r, c, r + 1, c - 1)
                        out.add(newstate)
                    else:
                        if r + 1 < rows and c - 1 > 0 and rep.getPiece(r + 1, c - 1) == 'k' and self.isAdmissible(r,
                                                                                                                 c,
                                                                                                                 r + 2,
                                                                                                                 c - 2):
                            newstate = self.makeMove(r, c, r + 2, c - 2)
                            out.add(newstate)
                            p1 = True
                        if p1 and r + 3 < rows and c + 3 > 0 and rep.getPiece(r + 3, c - 3) == 'k' and self.isAdmissible(
                                r, c, r + 4, c - 4):
                            newstate = self.makeMove(r, c, r + 4, c - 4)
                            out.add(newstate)
                            p2 = True
                        if p2 and r + 5 < rows and c + 5 > 0 and rep.getPiece(r + 5, c - 5) == 'k' and self.isAdmissible(
                                r, c, r + 6, c - 6):
                            newstate = self.makeMove(r, c, r + 6, c - 6)
                            out.add(newstate)
                else: # human tries to minimise
                    #moving towards north-east
                    p1 = p2 = False # true if previous if is successful
                    if self.isAdmissible(r,c,r-1,c+1):
                        newstate = self.makeMove(r,c,r-1,c+1)
                        out.add(newstate)
                    else:
                        if r-1 >= 0 and c+1 < cols and rep.getPiece(r-1,c+1) == 'w' and self.isAdmissible(r,c,r-2,c+2):
                            newstate = self.makeMove(r,c,r-2,c+2)
                            out.add(newstate)
                            p1 = True
                        if p1 and r-3 >= 0 and c+3 < cols and rep.getPiece(r-3,c+3) == 'w' and self.isAdmissible(r,c,r-4,c+4):
                            newstate = self.makeMove(r, c, r - 4, c + 2)
                            out.add(newstate)
                            p2 = True
                        if p2 and r-5 >= 0 and c+5 < cols and rep.getPiece(r-5,c+5) == 'w' and self.isAdmissible(r,c,r-6,c+6):
                            newstate = self.makeMove(r, c, r - 6, c + 2)
                            out.add(newstate)
                    #moving toward north-west
                    p1 = p2 = False  # true if previous if is successful
                    if self.isAdmissible(r, c, r - 1, c - 1):
                        newstate = self.makeMove(r, c, r - 1, c - 1)
                        out.add(newstate)
                    else:
                        if r - 1 >= 0 and c - 1 > 0 and rep.getPiece(r - 1, c - 1) == 'w' and self.isAdmissible(r,
                                                                                                                    c,
                                                                                                                    r - 2,
                                                                                                                    c - 2):
                            newstate = self.makeMove(r, c, r - 2, c - 2)
                            out.add(newstate)
                            p1 = True
                        if p1 and r-3 >= 0 and c+3 > 0 and rep.getPiece(r - 3, c - 3) == 'w' and self.isAdmissible(r, c, r - 4, c - 4):
                            newstate = self.makeMove(r, c, r - 4, c - 4)
                            out.add(newstate)
                            p2 = True
                        if p2 and r-5 >= 0 and c+5 > 0 and rep.getPiece(r - 5, c - 5) == 'w' and self.isAdmissible(r, c, r - 6, c - 6):
                            newstate = self.makeMove(r, c, r - 6, c - 6)
                            out.add(newstate)
        return out

    def setCurrentPlayer(self, player):
        self.getRepresentation().setCurrentPlayer(player)

    """
    Returns 'human' if the current board is solution for human player
    Returns 'machine' if current board is solution for machine player
    Returns None if current board is solution for neither machine and human player
    """
    def solution(self):
        rep = self.repesentation
        solmachine = True
        solhuman = True

        # win for machine (w)
        for r in range(0, 8):
            for c in range(0, 8):
                if rep.getPiece(r,c) == 'w':
                    solmachine = False

        if solmachine == True:
            return 'machine'

        # win for human (k)
        for r in range(0, 8):
            for c in range(0, 8):
                if rep.getPiece(r, c) == 'k':
                    solhuman = False

        if solhuman == True:
            return 'human'

        return None

    def isAdmissible(self, r, c, er, ec):
        resp = self.representation.isAdmissible(r,c,er,ec)
        return resp

    #note: this does not touch current state!!!!!!
    #assumes move is legal
    def makeMove(self,r,c,er,ec):
        rep = self.representation.makeMove(r,c,er,ec)
        newstate = CheckerState(self.H, rep)
        newstate.setCurrentPlayer(self.representation.player)
        return newstate
    
    def __str__(self):
        return str(self.representation)
    
    def __repr__(self):
        return repr(self.getRepresentation())
    

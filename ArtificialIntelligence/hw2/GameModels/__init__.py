
__author_base__ = 'giodegas'  # author of the base code


import copy


free = set()  # set of pegs free to move wherever they want


class CheckerRepresentation:

    def __init__(self, board):
        self.board = board
        
    def player(self):
        return self.player

    def getPiece(self, r, c):
        # what if out of the board?
        cols = len(self.board[0])
        rows = len(self.board)
        piece = ' '
        if 0 <= r < rows and 0 <= c < cols:
            piece = self.board[r][c]
        return piece

    def getBoard(self):
        return self.board

    def getDeepCopy(self):
        b = copy.deepcopy(self.board)
        r = CheckerRepresentation(b)
        r.setCurrentPlayer(self.player[:])  # deep copy of self.player (otw. shallow copy)
        return r

    def setPiece(self, r,c,piece):
        self.board[r, c] = piece

    def setCurrentPlayer(self, player):
        self.player = player

    def isFree(self, r, c):
        if 0 <= r < len(self.board) and 0 <= c < len(self.board[0]):
            return self.getPiece(r, c) == ' '
        return False

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
        s += "________________"
        return s
        
    def __repr__(self):
        return self.printMatrix()
    
    def __str__(self):
        return self.printMatrix()

    def isAdmissible(self, r,c,er,ec):
        # cannot move a not-existing peg
        if self.isFree(r,c):
            return False

        # cannot move a peg of enemy
        if self.board[r][c] != self.player:
            return False

        # cannot stay in the same cell of before
        if r == er and c == ec:
            return False

        #if we stay in the board
        if not ( 0 <= r < len(self.board) and 0 <= er < len(self.board) and 0 <= c < len(self.board[0]) and 0 <= ec < len(self.board[0]) ):
            return False

        # final position of peg must not be occupied
        if self.isFree(er, ec) == False:
            return False

        # cannot move in the cell above, only diagonally
        if c == ec:
            return False
        if abs(er-r) != abs(ec-c):
            return False

        # get peg to move
        peg_rc = self.board[r][c]

        """# if you want to jump more than one row, you must eat!
        if abs(er-r) > 1:
            if er-r == 2:
                # check peg in the middle is one of enemy
                if self.isFree(er-1,ec-1) == True or self.board[er-1][ec-1] == self.player:
                    return False
            if er-r == 4:
                # checks above
                if self.isFree(er-1,ec-1) == True or self.board[er-1][ec-1] == self.player:
                    return False
                if self.isFree(er-3,ec-3) == True or self.board[er-3][ec-3] == self.player:
                    return False
            if er-r == 6:
                # checks above
                if self.isFree(er - 1,ec - 1) == True or self.board[er - 1][ec - 1] == self.player:
                    return False
                if self.isFree(er - 3,ec - 3) == True or self.board[er - 3][ec - 3] == self.player:
                    return False
                if self.isFree(er-6,ec-6) == True or self.board[er-6][ec-6] == self.player:
                    return False"""
        return True

    """
    Note: assumes that move is admissible (see self.isAdmissible())
    Does NOT affect self.board
    @return board representation with the move
    """
    def makeMove(self, r, c, er, ec):
        global free
        
        print "repr, makemove()"
        # copy board
        if len(self.board[6]) < 8:
            pass
        newboard = copy.deepcopy(self.board)
        if len(newboard[6]) < 3:
            pass
        print "deepcopy (%d,%d)->(%d,%d):" %(r,c,er,ec)
        print str(self)

        # if peg reaches the last row of enemy's side, add that peg into "free" (to move) pegs list.
        # if it was already there, remove it
        if Peg(r, c) in free:
            free.remove(Peg(r, c))
        # if peg reaches the last row of enemy's side, add that peg into "free" (to move) pegs list.
        if er == 0 or er == 7:
            free.add(Peg(er, ec))

        # return the board with the move
        peg = self.board[r][c] 
        newboard[r][c] = ' '
        newboard[er][ec] = peg

        # if moving towards north-east
        if er < r and ec > c:
            if r-er == 2:
                # check peg in the middle is one of enemy
                newboard[er+1][ec-1] = ' '
                if Peg(er+1, ec-1) in free:
                    free.remove(Peg(er+1, ec-1))
            if r-er == 4:
                newboard[er+1][ec-1] = ' '
                newboard[er+3][ec-3] = ' '
                if Peg(er + 1, ec - 1) in free:
                    free.remove(Peg(er + 1, ec - 1))
                if Peg(er + 3, ec - 3) in free:
                    free.remove(Peg(er + 3, ec - 3))
            if r-er == 6:
                newboard[er+1][ec-1] = ' '
                newboard[er+3][ec-3] = ' '
                newboard[er+6][er-6] = ' '
                if Peg(er + 1, ec - 1) in free: 
                    free.remove(Peg(er + 1, ec - 1))
                if Peg(er + 3, ec - 3) in free:
                    free.remove(Peg(er + 3, ec - 3))
                if Peg(er + 6, ec - 6) in free:
                    free.remove(Peg(er + 6, ec - 6))
        elif er < r and ec < c: # if moving towards north-west
            if r-er == 2:
                # check peg in the middle is one of enemy
                newboard[er+1][ec+1] = ' '
                if Peg(er + 1, ec + 1) in free:
                    free.remove(Peg(er + 1, ec + 1))
            if r-er == 4:
                newboard[er+1][ec+1] = ' '
                newboard[er+3][ec+3] = ' '
                if Peg(er + 3, ec + 3) in free:
                    free.remove(Peg(er + 1, ec + 1))
                if Peg(er+1, ec+1) in free: 
                    free.remove(Peg(er + 3, ec + 3))
            if r-er == 6:
                newboard[er+1][ec+1] = ' '
                newboard[er+3][ec+3] = ' '
                newboard[er+6][er+6] = ' '
                if Peg(er + 1, ec + 1) in free:
                    free.remove(Peg(er + 1, ec + 1))
                if Peg(er + 3, ec + 3) in free:
                    free.remove(Peg(er + 3, ec + 3))
                if Peg(er + 6, ec + 6) in free:
                    free.remove(Peg(er + 6, ec + 6))
        elif er > r and ec > c: # if moving towards south-east
            if er-r == 2:
                # check peg in the middle is one of enemy
                newboard[er-1][ec-1] = ' '
                if Peg(er - 1, ec - 1) in free:
                    free.remove(Peg(er - 1, ec - 1))
            if er-r == 4:
                newboard[er-1][ec-1] = ' '
                newboard[er-3][ec-3] = ' '
                if Peg(er - 1, ec - 1) in free:
                    free.remove(Peg(er - 1, ec - 1))
                if Peg(er - 3, ec - 3) in free:
                    free.remove(Peg(er - 3, ec - 3))
            if er-r == 6:
                newboard[er-1][ec-1] = ' '
                newboard[er-3][ec-3] = ' '
                newboard[er-6][er-6] = ' '
                if Peg(er - 1, ec - 1) in free:
                    free.remove(Peg(er - 1, ec - 1))
                if Peg(er - 3, ec - 3) in free:
                    free.remove(Peg(er - 3, ec - 3))
                if Peg(er - 6, ec - 6) in free:
                    free.remove(Peg(er - 6, ec - 6))
        else: # if moving towards south-west
            if er-r == 2:
                # check peg in the middle is one of enemy
                newboard[er-1][ec+1] = ' '
                print str(er-1), str(ec+1)
                p = Peg(er - 1, ec + 1)
                if p in free:
                    free.remove(p)
            if er-r == 4:
                newboard[er-1][ec+1] = ' '
                newboard[er-3][ec+3] = ' '
                if Peg(er - 1, ec + 1) in free:
                    free.remove(Peg(er - 1, ec + 1))
                if Peg(er - 3, ec + 3) in free:
                    free.remove(Peg(er - 3, ec + 3))
            if er-r == 6:
                newboard[er-1][ec+1] = ' '
                newboard[er-3][ec+3] = ' '
                newboard[er-6][er+6] = ' '
                if Peg(er - 1, ec + 1) in free:
                    free.remove(Peg(er - 1, ec + 1))
                if Peg(er - 1, ec + 1) in free:
                    free.remove(Peg(er - 3, ec + 3))
                if Peg(er - 1, ec + 1) in free:
                    free.remove(Peg(er - 6, ec + 6))

        return CheckerRepresentation(newboard)

class CheckerState:

    def __init__(self, heuristic, representation):
        self.H = heuristic
        self.representation = representation

    def enemy(self, peg):
        r = peg.r
        c = peg.c
        p = self.representation.getPiece(r,c)
        if p == 'k':
            return 'w'
        return 'k'

    def getRepresentation(self):
        return self.representation

    def getHeuristic(self):
        return self.H

    def neighbors(self, turn):
        """
        Returns the possible moves that player turn can perform.
        :param turn: player to consider (w or k)
        :type turn: str
        :return: set of boards resulting from possible moves of player turn
        :rtype: set(CheckerState)
        """
        # turn in ('w','k')
        # w : white
        # k : black
        global free
        print "state, neighbors()"

        rep = self.getRepresentation()
        out = set()
        for r in range(0, 8):
            for c in range(0, 8):
                p = Peg(r, c, self.getRepresentation().getPiece(r, c))
                print str(self)
                print "state, neighbors(). r=", str(r), " c=", str(c)
                if p.getcontent() == ' ' or p.getcontent() != turn:  # if this is no peg or it's not a peg of mine I cannot move it
                    continue

                # case not eating
                if rep.getPiece(r,c) == 'k' or p in free:  # case moving towards north
                    if rep.isFree(r-1, c-1):
                        newstate = self.makeMove(r,c,r-1,c-1)
                        out.add (newstate)
                    if rep.isFree(r-1, c+1):
                        newstate = self.makeMove(r,c,r-1,c+1)
                        out.add(newstate)
                if rep.getPiece(r,c) == 'w' or p in free:  # moving towards south
                    if rep.isFree(r+1,c+1):
                        newstate = self.makeMove(r,c,r+1,c+1)
                        out.add(newstate)
                    if rep.isFree(r+1,c-1):
                        newstate = self.makeMove(r,c,r+1,c-1)
                        out.add(newstate)

                # case eating
                caseBefore = False  # True if it possible to eat n-1 pegs
                if rep.getPiece(r,c) == 'k' or p in free:  # case moving towards north
                    if self.isAdmissible(r,c,r-6,c+6):  # if I can eat 3 pegs, moving towards north-east
                        if rep.getPiece(r-5,c+5) == self.enemy(p) and rep.isFree(r-4,c+4) and rep.getPiece(r-3,c+3) == self.enemy(p) and rep.isFree(r-2,c+2) and rep.getPiece(r-1,c+1) == self.enemy(p):  # moving towards north-east
                            newstate = self.makeMove(r,c,r-6,c+6)
                            out.add(newstate)
                            caseBefore = True
                    if self.isAdmissible(r, c, r - 6, c - 6):  # if I can eat 3 pegs, moving towards north-west
                        if rep.getPiece(r-5,c-5) == self.enemy(p) and rep.isFree(r-4,c-4) and rep.getPiece(r-3,c-3) == self.enemy(p) and rep.isFree(r-2,c-2) and rep.getPiece(r-1,c-1) == self.enemy(p):
                            newstate = self.makeMove(r,c,r-6,c-6)
                            out.add(newstate)
                            caseBefore = True

                    if not caseBefore and self.isAdmissible(r,c,r-4,c-4):  # if I can eat 2 pegs, moving towards north-west
                        if rep.getPiece(r - 3, c + 3) == self.enemy(p) and rep.isFree(r - 2, c + 2) and rep.getPiece(
                                        r - 1, c + 1) == self.enemy(p):
                            newstate = self.makeMove(r, c, r - 6, c + 6)
                            out.add(newstate)
                            caseBefore = True
                    if not caseBefore and self.isAdmissible(r, c, r - 4, c + 4):  # if I can eat 2 pegs, moving towards north-est
                        if rep.getPiece(r - 3, c - 3) == self.enemy(p) and rep.isFree(r - 2, c - 2) and rep.getPiece(
                                        r - 1, c - 1) == self.enemy(p):
                            newstate = self.makeMove(r, c, r - 4, c - 4)
                            out.add(newstate)
                            caseBefore = True

                    if not caseBefore and self.isAdmissible(r,c,r-2,c-2): # if I can eat 1 peg, moving towards north-west
                        if rep.getPiece(r-1,c-1) == self.enemy(p):
                            newstate = self.makeMove(r,c,r-2,c-2)
                            out.add(newstate)
                    if not caseBefore and self.isAdmissible(r, c, r - 2, c + 2):  # if I can eat 1 peg, moving towards north-east
                        if rep.getPiece(r-1,c+1) == self.enemy(p):
                            newstate = self.makeMove(r,c,r-2,c+2)
                            out.add(newstate)
                caseBefore = False            
                if rep.getPiece(r,c) == 'w' or p in free:  # case moving towards south
                    if self.isAdmissible(r,c,r+6,c+6):  # if I can eat 3 pegs, moving towards north-east
                        if rep.getPiece(r+5,c+5) == self.enemy(p) and rep.isFree(r+4,c+4) and rep.getPiece(r+3,c+3) == self.enemy(p) and rep.isFree(r+2,c+2) and rep.getPiece(r+1,c+1) == self.enemy(p):  # moving towards north-east
                            newstate = self.makeMove(r,c,r+6,c+6)
                            out.add(newstate)
                            caseBefore = True
                    if self.isAdmissible(r, c, r - 6, c - 6):  # if I can eat 3 pegs, moving towards north-west
                        if rep.getPiece(r+5,c-5) == self.enemy(p) and rep.isFree(r+4,c-4) and rep.getPiece(r+3,c-3) == self.enemy(p) and rep.isFree(r+2,c-2) and rep.getPiece(r+1,c-1) == self.enemy(p):
                            newstate = self.makeMove(r,c,r+6,c-6)
                            out.add(newstate)
                            caseBefore = True

                    if not caseBefore and self.isAdmissible(r,c,r+4,c-4):  # if I can eat 2 pegs, moving towards north-west
                        if rep.getPiece(r - 3, c + 3) == self.enemy(p) and rep.isFree(r - 2, c + 2) and rep.getPiece(
                                        r - 1, c + 1) == self.enemy(p):
                            newstate = self.makeMove(r, c, r - 6, c + 6)
                            out.add(newstate)
                            caseBefore = True
                    if not caseBefore and self.isAdmissible(r, c, r - 4, c + 4):  # if I can eat 2 pegs, moving towards north-est
                        if rep.getPiece(r - 3, c - 3) == self.enemy(p) and rep.isFree(r - 2, c - 2) and rep.getPiece(
                                        r - 1, c - 1) == self.enemy(p):
                            newstate = self.makeMove(r, c, r - 4, c - 4)
                            out.add(newstate)
                            caseBefore = True

                    if not caseBefore and self.isAdmissible(r,c,r+2,c-2): # if I can eat 1 peg, moving towards north-west
                        if rep.getPiece(r+1,c-1) == self.enemy(p):
                            newstate = self.makeMove(r,c,r+2,c-2)
                            out.add(newstate)
                    if not caseBefore and self.isAdmissible(r, c, r - 2, c + 2):  # if I can eat 1 peg, moving towards north-east
                        if rep.getPiece(r+1,c+1) == self.enemy(p):
                            newstate = self.makeMove(r,c,r+2,c+2)
                            out.add(newstate)
        return out

    def setCurrentPlayer(self, player):
        self.getRepresentation().setCurrentPlayer(player)

    def solution(self):
        """
            Returns 'human' if the current board is solution for human player
            Returns 'machine' if current board is solution for machine player
            Returns None if current board is solution for neither machine and human player
            :rtype: str
            :return: 'machine' or 'human' or None
        """
        rep = self.representation
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
    def makeMove(self, r, c, er, ec):
        global free
        rep = self.representation.makeMove(r, c, er, ec)
        newstate = CheckerState(self.H, rep)
        newstate.setCurrentPlayer(self.representation.player)
        return newstate
    
    def __str__(self):
        return str(self.representation)
    
    def __repr__(self):
        return repr(self.getRepresentation())


class Peg:
    def __init__(self, r, c, content=' '):
        self.r = r
        self.c = c
        self.content = content

    def r(self):
        return self.r

    def c(self):
        return self.c

    def getcontent(self):
        return self.content

    def __hash__(self):
        s = str(self.r) + str(self.c)
        return int(s)

    def __eq__(self, other):
        if self.r == other.r and self.c == other.c:
            return True
        return False

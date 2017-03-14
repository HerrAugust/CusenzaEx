#CHECKERS game Minmax implementation
#for this implementation MACHINE -> WHITE ('w'); HUMAN -> BLACK ('k')

__author_base__ = 'giodegas'  # author of base version

import GameModels as G
import Heuristics as H

import time


def game():
    board = [
        [' ', 'w', ' ', 'w', ' ', 'w', ' ', 'w'],
        ['w', ' ', 'w', ' ', 'w', ' ', 'w', ' '],
        [' ', 'w', ' ', 'w', ' ', 'w', ' ', 'w'],  # machine frontier
        [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
        [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
        ['k', ' ', 'k', ' ', 'k', ' ', 'k', ' '],  # human frontier
        [' ', 'k', ' ', 'k', ' ', 'k', ' ', 'k'],
        ['k', ' ', 'k', ' ', 'k', ' ', 'k', ' ']
    ]
    
    LEVEL = 3
    heuristic = H.CheckerHeuristic()
    rep = G.CheckerRepresentation(board)
    rep.setCurrentPlayer('w')
    curState = G.CheckerState(heuristic, rep)
    f = open("log", "w")
    f.close()

    while True:
        turn = 'w'  # machine
        curState.setCurrentPlayer(turn)
        states = curState.neighbors(turn)  # find possible moves from here (1 level deeper). these are first level TRIANGLES DOWN
        for s in states:
            print str(s)
        mx = -9999
        ix = None  # best state
        for s in states:  # in this loop I want to choose the best move
            start = time.time()
            h = heuristic.H(s, LEVEL, 'k', mx)  # for each move, calculate heuristic value
            end = time.time()
            print "Time needed for heuristic: ", str( (end-start) )
            if h > mx:  # find best heuristic value (MAX one) and remember the corresponding state
                mx = h
                ix = s

        # generate a move in function of ix
        curState = ix
        print "MATRIX AFTER MACHINE MOVE:"
        print str(curState)
        f = open("log", "a")
        f.write(str(curState))
        f.close()

        # if machine has just moved a peg to the last line of human frontier (row 7) => add it to free set
        for i in range(0,8):
            if curState.getRepresentation().getPiece(7,i) == 'w':
                curState.addToFree(7,i)

        # check if final break WHITE wins!
        if curState.solution() == 'machine':
            print "You lose"
            return

        turn = 'k'  # human
        curState.setCurrentPlayer(turn)
        movePossible = False
        while movePossible == False:
            s = input('Position of move start. [row.column]: ')
            s = str(s)
            r = int(s.split('.')[0])
            c = int(s.split('.')[1])
            s = input('Position of move end. [row.column]: ')
            s = str(s)
            re = int(s.split(".")[0])
            ce = int(s.split(".")[1])
            # is it feasible?
            movePossible = curState.isAdmissible(r, c, re, ce)
            if not movePossible:
                print "Move not admissible"

        curState = curState.makeMove(r, c, re, ce)
        print "RESULTING MATRIX:"
        print str(curState)
        f = open("log", "a")
        f.write(str(curState))
        f.close()
        # check if final break BLACK wins!
        if curState.solution() == 'human':
            print "You win"
            return

        time.sleep(3)
# Main
game()

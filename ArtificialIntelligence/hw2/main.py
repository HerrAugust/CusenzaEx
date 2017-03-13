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
        states = curState.neighbors(turn)  # find possible moves from here (1 level deeper)
        for j in states:
            print str(j)
        mx = -9999
        ix = None  # best state
        for s in states:
            start = time.time()
            h = heuristic.H(s, LEVEL, 'k', mx)  # for each move, calculate heuristic value. this is the beginning MAX
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

        # check if final break WHITE wins!
        if curState.solution() == 'machine':
            print "You lose"
            return

        turn = 'k'  # human
        curState.setCurrentPlayer(turn)
        movePossible = False
        while movePossible == False:
            r = input('Position of move start. row: ')
            c = input('Position of move start. column: ')
            re = input('Position of move end. row: ')
            ce = input('Position of move end. column: ')
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
        time.sleep(3)
        # check if final break BLACK wins!
        if curState.solution() == 'human':
            print "You win"
            return

# Main
game()

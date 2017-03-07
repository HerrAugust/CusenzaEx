__author__ = 'giodegas'

import GameModels as G
import Heuristics as H

# Main
LEVEL = 5
heuristic = H.CheckerHeuristic()
game = G.CheckerGame(heuristic)

while True:
    turn = 'w'
    states = game.neighbors(turn)
    mx = -9999
    ix = 0
    for s in states:
        h = heuristic.Hl(game,s,LEVEL, turn)
        if h>mx:
            mx = h
            ix = s
    print ix
    # generate a move in function of ix
    # ....
    # check if final break WHITE wins!
    # ...
    turn = 'k'
    print 'Position of move start'
    r,c = input()
    print 'Position of move end'
    re,ce = input()
    # is it feasible?
    #...
    game.state.makeMove(r,c, re,ce)
    # check if final break BLACK wins!
    # ...

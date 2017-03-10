# -*- coding: iso-8859-15 -*-
# __author__ = 'HerrAugust'
import time
from copy import deepcopy

import Heuristics as H
import GameModels as G
import Debugging as D

movesNumber = 0

dicOfStates = {}

def backpath(state):
    father = state.parent()
    lStates = [state]
    while father!=None:
        lStates.append(father)
        father = father.parent()
    return reversed(lStates)

def updateState(setOfStates):
    for s in setOfStates:
        dicOfStates[s] = heuristic.H(s)
    return dicOfStates

def argMin(setOfStates):
    if len(setOfStates) == 0:
        return None
    
    m = list(setOfStates)[0]
    for e in setOfStates:
        if e.getRepresentation().f(e) < m.getRepresentation().f(e):
            m = e
    return m
    """v = []
    k = []
    dicOfStates = updateState(setOfStates)
    for sk in setOfStates:
        if dicOfStates.has_key(sk):
            v += [dicOfStates[sk]]
            k += [sk]
    if len(v)>0:
        return k[v.index(min(v))]
    else:
        return None"""

def pick(setOfStates):
    return argMin(setOfStates)

"""#original code of AStar by Giovanni de Gasperis, Università degli Studi dell'Aquila, then revisited by HerrAugust (GitHub)
def AStar(state0, game):
    global movesNumber
    global g
    g = game
    
    sHorizon = set([])
    sExplored = set([])
    sHorizon.add(state0)
    while (len(sHorizon) > 0):
        view = pick(sHorizon)
        movesNumber += 1
        if not (view is None):
            print "___________________________"
            print "view name: level ", view.getStateName()
            if view.parent() is not None:
                print "view father: ", view.parent().getStateName()
            print "Move number: " , str(movesNumber)
            print "Explored grids ",str(len(sExplored))
            r = view.getRepresentation().remainingBalls
            print "Balls: ", str(r)
            print "Exploring matrix:"
            print printMatrix(view.getRepresentation().grid)
            if game.isSolution(view):
                print "============================="
                print "============================="
                print "============================="
                print "Solution found!"
                print "Moves:"
                moves = backpath(view) #list of states
                i = 1
                for e in moves:
                    print "Move ",str(i)
                    i += 1
                    if e.parent() is not None: # not father
                        print "father stateName = ",e.parent().getStateName()
                    print "stateName = ",e.getStateName()
                    printMatrix(e.getRepresentation().grid) 
                return True
            #sHorizon = sHorizon | (game.neighbors(view) - sExplored)
            sExplored.add(view)
            sHorizon.remove(view)
            # seek for all possible moves and make them neighboring states
            children = game.neighbors(view)
            # if the neighbor wasn't yet explored add it to the horizon and repeat the loop
            for child in children:
                if child not in sExplored:
                    sHorizon.add(child)
    return None"""
    
excluded = set()
def AStar(state, game):
    global excluded
    
    if game.isSolution(state):
        print "Solution found"
        return True
    
    children = game.neighbors(state)
    while True:
        best = pick(children)
        if best is not None:
            children.remove(best)
        while best in excluded:
            best = pick(children)
        if best is None: #best is leaf
            return False #go back and choose another path
        
        print "___________________________"
        print "view name: level ", state.getStateName()
        if state.parent() is not None:
            print "view father: ", state.parent().getStateName()
        print "Move number: " , str(movesNumber)
        print "Explored grids ",str(len(excluded))
        r = state.getRepresentation().remainingBalls
        print "Balls: ", str(r)
        print "Exploring matrix:"
        print printMatrix(state.getRepresentation().grid)
        print "hash: ", str(hash(state))
        
        if r == 10:
            pass
        
        excluded.add(best)
        r = AStar(best, game)
        if r is True:
            return True
        #false: choose another path to explore
        

def printMatrix(matrix):
    if matrix is None:
        return
    rows = len(matrix)
    cols = len(matrix[0])
    for i in range(0,rows):
        toprint = ""
        for j in range(0,cols):
            toprint = toprint + " " + str(matrix[i][j])
        print toprint

# Main--------------------------------------------------------------------
revisited = [
    [2,2,1,1,1,2,2],
    [2,1,1,1,1,1,2],
    [1,1,1,1,1,1,1],
    [1,1,1,0,1,1,1],
    [1,1,1,1,1,1,1],
    [2,1,1,1,1,1,2],
    [2,2,1,1,1,2,2]]

classic = [
    [2,2,1,1,1,2,2],
    [2,2,1,1,1,2,2],
    [1,1,1,1,1,1,1],
    [1,1,1,0,1,1,1],
    [1,1,1,1,1,1,1],
    [2,2,1,1,1,2,2],
    [2,2,1,1,1,2,2]]

#classic = D.File().textToMatrix()


toBePlayed = [1]

if 1 in toBePlayed:
    #Manhattan distance heuristic for classic
    print "Manhattan distance heuristic for classic"
    printMatrix(classic)
    lastGrid_remainingBalls = 32
    start               = time.time()
    
    heuristic           = H.ManhattanDistanceHeuristic()
    s                   = G.PegSolitaireState(heuristic, deepcopy(classic))
    s.setLevel(0) #needed for debug
    game                = G.PegSolitaireGame(s, heuristic)
    state0              = game.getState()
    #dicOfStates[state0] = heuristic.H(state0=
    solution            = AStar(state0, game)
    
    end                 = time.time()
    print "Time needed: ", end-start


if 2 in toBePlayed:
    time.sleep(5)
    #Manhattan distance heuristic for revisited
    print "Manhattan distance heuristic for revisited"
    printMatrix(classic)
    lastGrid_remainingBalls = 32
    start               = time.time()
    
    heuristic           = H.ManhattanDistanceHeuristic()
    s                   = G.PegSolitaireState(heuristic, deepcopy(revisited))
    game                = G.PegSolitaireGame(s, heuristic)
    state0              = game.getState()
    dicOfStates[state0] = heuristic.H(state0)
    solution            = AStar(state0, game)
    
    end                 = time.time()
    print "Time needed: ", end-start


"""if 3 in toBePlayed:
    #Exponential Distance heuristic for classic
    print
    print
    print
    print "Exponential Distance heuristic for classic"
    printMatrix(classic)
    lastGrid_remainingBalls = 32
    start = time.time()
    
    heuristic   = H.ExponentialDistanceHeuristic()
    game        = G.PegSolitaireGame(heuristic, G.PegSolitaireRepresentation(deepcopy(classic)))
    state0      = game.getState()
    state0.getRepresentation().centerX = 3
    state0.getRepresentation().centerY = 3
    solution    = AStar(state0.getRepresentation(), G.Path(), game)
    
    end = time.time()
    print "Time needed: ", end-start


if 4 in toBePlayed:
    #Exponential Distance heuristic for revisited solitaire
    print
    print
    print
    print "Exponential Distance heuristic for revisited solitaire"
    printMatrix(revisited)
    lastGrid_remainingBalls = 36
    start = time.time()
    
    heuristic   = H.ExponentialDistanceHeuristic()
    game        = G.PegSolitaireGame(heuristic, G.PegSolitaireRepresentation(deepcopy(revisited)))
    state0      = game.getState()
    state0.getRepresentation().centerX = 3
    state0.getRepresentation().centerY = 3
    solution    = AStar(state0.getRepresentation(), G.Path(), game)
    
    end = time.time()
    print "Time needed: ", end-start"""

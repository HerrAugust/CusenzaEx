# -*- coding: iso-8859-15 -*-
# __author__ = 'HerrAugust'
import time
from copy import deepcopy

import Heuristics as H
import GameModels as G
from GameModels.PegSolitaireRepresentation import PegSolitaireClassicRepresentation

gridExplored = 0
movesNumber = 0
AStarCalls = 0
movesPath = G.Path()
excluded = [] #already visited grids

def argMin(listOfStates, game):
    if len(listOfStates) == 0:
        return { 'elem': None, 'index': -1 }
    
    index = 0
    i = index - 1
    cur = listOfStates[index]
        
    for e in listOfStates:
        i += 1
        if e.f(game) < cur.f(game): #with the minimum, pegs tend to concentrate to center
            cur = e
            index = i
            
    return { 'elem':cur, 'index': index }

def pick(setOfStates, game):
    a = argMin(setOfStates, game)
    return a

def mapDirection(direction):
    directions = ("n", "e", "s", "w")
    return directions[direction]

#application of (revisited) algorithm http://courses.csail.mit.edu/6.884/spring10/labs/lab5.pdf plus heuristic (A*), found at TODO
def AStar(grid, game):
    global movesNumber
    global gridExplored
    global excluded
    
    gridExplored += 1
    print "Grid explored " ,gridExplored
    if gridExplored == 45000: #too many moves: stop
        return True
    
    if G.PegSolitaireGame.issolution(grid): #base case: go back to root of tree
        return True
    
    #create horizon (i.e., new level of search tree) as a list
    horizon = grid.getPossibleMoves() #see PegSolitaireRepresentation.py
    
    #try all grids in horizon. One is the solution!
    while True:
        #get best grid ( min f(grid) = g(grid) + h(grid) for each possible future grid )
        res = pick(horizon, game)
        newGrid = res['elem']
        newGrid_index = res['index']
        if newGrid is None: #leaf is not a solution
            return False
        bitmap = newGrid.getBitMap()
        if bitmap in excluded:#do not touch this grid in future
            del horizon[newGrid_index]
            continue
        excluded.append(bitmap)
        if G.PegSolitaireGame.issolution(newGrid): #if grid is solution
            return True
        #movesPath.push(newGrid)
        print "New matrix is:"
        printMatrix(newGrid.grid)
        
        movesNumber += 1
        sol = AStar(newGrid, game) #try that branch
        
        #is this child grid a solution?
        if sol:
            print "Solution found!"
            print "Moves needed: ",movesNumber
            print "Moves: ",str(movesPath)
            return True
        else: #if not, deepened that node
            movesNumber -= 1
            #movesPath.pop()
            print "Rolling back"
            print "len: ",str(len(horizon)), " newgrid_index:", newGrid_index
            if 0 <= newGrid_index < len(horizon):
                del horizon[newGrid_index]
                print "len horizon with less elem: ",str(len(horizon))
        

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

# Main
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

toBePlayed = [1]

if 1 in toBePlayed:
    #Manhattan distance heuristic for classic
    print "Manhattan distance heuristic for classic"
    printMatrix(classic)
    lastGrid_remainingBalls = 32
    start = time.time()
    
    heuristic   = H.ManhattanDistanceHeuristic()
    game        = G.PegSolitaireGame(heuristic, PegSolitaireClassicRepresentation(deepcopy(classic)))
    state0      = game.getState()
    state0.getRepresentation().centerX = 3
    state0.getRepresentation().centerY = 3
    solution    = AStar(state0.getRepresentation(), game)
    
    end = time.time()
    print "Time needed: ", end-start


if 2 in toBePlayed:
    #Manhattan distance heuristic for revisited solitaire
    print
    print
    print
    print "Manhattan distance heuristic for revisited solitaire"
    printMatrix(revisited)
    lastGrid_remainingBalls = 36
    start = time.time()
    
    heuristic   = H.ManhattanDistanceHeuristic()
    game        = G.PegSolitaireGame(heuristic, G.PegSolitaireRevisitedRepresentation(deepcopy(revisited)))
    state0      = game.getState()
    state0.getRepresentation().centerX = 3
    state0.getRepresentation().centerY = 3
    solution    = AStar(state0.getRepresentation(), G.Path(), game)
    
    end = time.time()
    print "Time needed: ", end-start


if 3 in toBePlayed:
    #Exponential Distance heuristic for classic
    print
    print
    print
    print "Exponential Distance heuristic for classic"
    printMatrix(classic)
    lastGrid_remainingBalls = 32
    start = time.time()
    
    heuristic   = H.ExponentialDistanceHeuristic()
    game        = G.PegSolitaireGame(heuristic, PegSolitaireClassicRepresentation(deepcopy(classic)))
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
    game        = G.PegSolitaireGame(heuristic, G.PegSolitaireRevisitedRepresentation(deepcopy(revisited)))
    state0      = game.getState()
    state0.getRepresentation().centerX = 3
    state0.getRepresentation().centerY = 3
    solution    = AStar(state0.getRepresentation(), G.Path(), game)
    
    end = time.time()
    print "Time needed: ", end-start

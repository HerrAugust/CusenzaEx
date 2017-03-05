# -*- coding: iso-8859-15 -*-
# __author__ = 'HerrAugust'
import time
from copy import copy, deepcopy

import Heuristics as H
import GameModels as G
from GameModels.PegSolitaireRepresentation import PegSolitaireClassicRepresentation

untouchablePegs = set() #set of pegs that I have already tried to move but there was to way. so I will simply skip them for the current grid configuration
lastGrid_remainingBalls = 32 #needed in A* function to remove old untouchable pegs if a peg is removed 
movesNumber = 0

def argMax(setOfStates):
    amax = None
    if len(setOfStates) > 0:
        amax = list(setOfStates)[0]
        for e in setOfStates:
            if e. f > amax.f:
                amax = e
    return amax

def pick(setOfStates):
    return argMax(setOfStates)

def mapDirection(direction):
    directions = ("n", "e", "s", "w")
    return directions[direction]

#application of (revisited) algorithm http://courses.csail.mit.edu/6.884/spring10/labs/lab5.pdf plus heuristic (A*), found at TODO
def AStar(grid, path, game):
    global untouchablePegs
    global lastGrid_remainingBalls
    global movesNumber
    horizon = set() #priority queue of possible moves for each peg
    #create horizon (i.e., new level of search tree)
    for r in range(0,7):
        for c in range(0,7):
            p = G.Peg(r,c)
            if p in untouchablePegs:
                continue
            if grid.pegExists(p): #if in that point of the grid there is a peg
                #get Manhattan distance
                p.f = 1 + game.heuristic().H(p,grid) # g = 1 because it is the cost for getting to the new state of the grid. could also be 0 or some other constant value
                horizon.add(p)
    #debug: print horizon
    bestPeg = pick(horizon)
    print "Best peg is: " + repr(bestPeg)
    if bestPeg is None: #no pegs movable
        print "Error: best peg is None"
        return 
    del horizon
    #now decide in which direction to move bestPeg
    bestDirection = grid.bestDirection(bestPeg) #choose the best direction or, if it doesn't exists, a legal one
    if bestDirection is None: #if no move is legal for chosen peg
        untouchablePegs.add(bestPeg)
        return AStar(grid, path, game)
    print "Move: (" + str(bestPeg.getRow()) + "," + str(bestPeg.getCol()) + ") to " + bestDirection
    path.push(G.Move(bestPeg,bestDirection)) #take note of move
    
    #update grid
    movesNumber += 1
    oldGrid = deepcopy(grid.grid) #grid before to move peg
    newGrid = grid.makeMove(bestPeg,bestDirection) #peg after moving peg
    newGrid.centerX = grid.centerX
    newGrid.centerY = grid.centerY
    print "Matrix after moving peg:"
    printMatrix(newGrid.grid)
    
    #if I could remove a peg, in this new grid I can touch all the pegs <=> set becomes void
    if newGrid.remainingBalls < lastGrid_remainingBalls:
        lastGrid_remainingBalls = newGrid.remainingBalls
        del untouchablePegs
        untouchablePegs = set() #in the new grid configuration it could be possible to move untouchable pegs
    else:
        #add bestPeg (whose position has changed) to untouchable pegs set (for next loop)
        untouchablePegs.add(bestPeg.move(oldGrid,bestDirection))
    print "untouchable: ",untouchablePegs
    
    #decide if to repeat loop
    if G.PegSolitaireGame.issolution(newGrid):
        print "Solution found"
        print "Number of moves: " , movesNumber
        print "Moves performed: ", path
        return True
    found = AStar(newGrid, path, game)
    if found: #finish algorithm
        return True   

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
"""
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
solution    = AStar(state0.getRepresentation(), G.Path(), game)

end = time.time()
print "Time needed: ", end-start"""


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

"""
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
print "Time needed: ", end-start"""

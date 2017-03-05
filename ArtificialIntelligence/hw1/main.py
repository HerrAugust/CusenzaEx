# -*- coding: iso-8859-15 -*-
# __author__ = 'HerrAugust'
import time
from copy import copy, deepcopy

import Heuristics as H
import GameModels as G
from GameModels.PegSolitaireRepresentation import PegSolitaireClassicRepresentation

untouchablePegs = set() #set of pegs that I have already tried to move but there was to way. so I will simply skip them for the current grid configuration
lastGrid_remainingBalls = 32 #needed in A* function to remove old untouchable pegs if a peg is removed 

def argMin(setOfStates):
    amin = None
    if len(setOfStates) > 0:
        amin = list(setOfStates)[0]
        for e in setOfStates:
            if e. f < amin.f:
                amin = e
    return amin

def pick(setOfStates):
    return argMin(setOfStates)

def backpath(state): #not used
    padre = state.parent
    lStates = [state]
    while padre!=None:
        lStates.add(padre)
        padre = padre.parent
    return reversed(lStates)

def mapDirection(direction):
    directions = ("n", "e", "s", "w")
    return directions[direction]

#application of (revisited) algorithm http://courses.csail.mit.edu/6.884/spring10/labs/lab5.pdf plus heuristic (A*), found at TODO
def AStar(grid, path, game):
    global untouchablePegs
    global lastGrid_remainingBalls
    horizon = set() #priority queue of possible moves for each peg
    #create horizon (i.e., new level of search tree)
    for r in range(0,6):
        for c in range(0,6):
            p = G.Peg(r,c)
            if p in untouchablePegs:
                continue
            if grid.pegExists(p): #if in that point of the grid there is a peg
                #get Manhattan distance
                p.f = 0 + game.heuristic().H(p,grid) # g = 1 because it is the cost for getting to the new state of the grid. could also be 0 or some other constant value
                horizon.add(p)
    #debug: print horizon
    bestPeg = pick(horizon)
    print "Best peg is: " + str(bestPeg)
    if bestPeg is None: #no pegs movable
        print "Error: best peg is None"
        del untouchablePegs #make all pegs movable
        untouchablePegs = set()
        AStar(grid, path, game) 
    del horizon
    #now decide in which direction to move bestPeg
    for j in range(0,4): #0=north,1=east,2=south,3=west. per scegliere la migliore, potrei fare la distanza manattiana anche per questi, usando sempre la priorityqueue
        if grid.moveIsLegal(bestPeg,mapDirection(j)):
            print "Move: (" + str(bestPeg.getRow()) + "," + str(bestPeg.getCol()) + ") to " + mapDirection(j)
            
            #update grid
            oldGrid = deepcopy(grid.grid)
            newGrid = grid.makeMove(bestPeg,mapDirection(j))
            newGrid.centerX = grid.centerX
            newGrid.centerY = grid.centerY
            print "Resulting matrix is:"
            printMatrix(newGrid.grid)
            path.push(G.Move(bestPeg,mapDirection(j))) #take not of move
            
            #if I could remove a peg, I can touch all the pegs
            if newGrid.remainingBalls < lastGrid_remainingBalls:
                lastGrid_remainingBalls = newGrid.remainingBalls
                del untouchablePegs
                untouchablePegs = set() #in the new grid configuration it could be possible to move untouchable pegs
            else:
                #add bestPeg (whose position has changed) to untouchable pegs set (for next loop)
                untouchablePegs.add(bestPeg.move(oldGrid,mapDirection(j)))
            print "untouchable: ",untouchablePegs
            
            #decide if to repeat loop
            if G.PegSolitaireGame.issolution(newGrid):
                print "Solution found"
                printMatrix(newGrid)
                return True
            found = AStar(newGrid, path, game)
            if found: #finish algorithm
                return True
            else:
                path.pop()
    #if no move is legal for chosen peg
    untouchablePegs.add(bestPeg)
    AStar(grid, path, game)            
    
def printMatrix(matrix):
    rows = len(matrix)
    cols = len(matrix[0])
    for i in range(0,rows):
        toprint = ""
        for j in range(0,cols):
            toprint = toprint + " " + str(matrix[i][j])
        print toprint

# Main
other = [
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
printMatrix(classic)
start = time.time()

heuristic   = H.ManhattanDistanceHeuristic()
game        = G.PegSolitaireGame(heuristic, PegSolitaireClassicRepresentation(classic))
state0      = game.getState()
state0.getRepresentation().centerX = 3
state0.getRepresentation().centerY = 3
solution    = AStar(state0.getRepresentation(), G.Path(), game)

end = time.time()
print "Time needed: ", end-start

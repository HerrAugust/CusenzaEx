# -*- coding: iso-8859-15 -*-
# __author__ = 'HerrAugust'
import time

import Heuristics as H
import GameModels as G
from GameModels.PegSolitaireRepresentation import PegSolitaireClassicRepresentation

untouchablePegs = set() #set of pegs that I have already tried to move but there was to way. so I will simply skip them for the current grid configuration

def argMin(setOfStates):
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
    print horizon
    bestPeg = pick(horizon)
    print "Best peg is: " + str(bestPeg)
    del horizon
    #now decide in which direction to move bestPeg
    for j in range(0,4): #0=north,1=east,2=south,3=west. per scegliere la migliore, potrei fare la distanza manattiana anche per questi, usando sempre la priorityqueue
        if grid.moveIsLegal(bestPeg,mapDirection(j)):
            print "Move: (" + str(bestPeg.getRow()) + "," + str(bestPeg.getCol()) + ") to " + mapDirection(j)
            newGrid = grid.makeMove(bestPeg,mapDirection(j))
            newGrid.centerX = grid.centerX
            newGrid.centerY = grid.centerY
            printMatrix(newGrid.grid)
            path.push(G.Move(bestPeg,mapDirection(j))) #take not of move
            del untouchablePegs
            untouchablePegs = set() #in the new grid configuration it could be possible to move untouchable pegs
            untouchablePegs.add(bestPeg.move(grid.grid,mapDirection(j)))
            if G.PegSolitaireGame.issolution(newGrid):
                print "Solution found"
                printMatrix(newGrid)
                return True
            found = AStar(newGrid, path, game)
            if found: #finish algorithm
                return True
            else:
                path.pop()
    #if no move is legal
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

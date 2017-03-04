# -*- coding: iso-8859-15 -*-
# __author__ = 'HerrAugust'
import time

from GameModels import PegSolitaireGame as Game
import Heuristics as H
from GameModels import Peg
from GameModels import Move
from GameModels import Path

dicOfStates = {}#not used

def argMin(setOfStates):
    min = None
    for e in setOfStates:
        if min is not None and e. f < min.f: #if e.f < min.f
            min = e

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
    horizon = set() #priority queue of possible moves for each peg
    #create horizon (i.e., new level of search tree)
    for r in range(0,6):
        for c in range(0,6):
            p = Peg(r,c)
            if grid.pegExists(p): #if in that point of the grid there is a peg
                #get Manhattan distance
                p.f = 1 + grid.heuristic().H(p) # g = 1 because it is the cost for getting to the new state of the grid. could also be 0 or some other constant value
                horizon = horizon | p
    bestPeg = pick(horizon)
    #now decide in which direction to move bestPeg
    for j in range(0,3): #0=north,1=east,2=south,3=west. per scegliere la migliore, potrei fare la distanza manattiana anche per questi, usando sempre la priorityqueue
        if grid.moveIsLegal(bestPeg,mapDirection(j)):
            newGrid = grid.makeMove(bestPeg,j)
            path.push(Move(bestPeg,mapDirection(j))) #take not of move
            if game.issolution(newGrid):
                print "Solution found"
                print2DimArray(newGrid)
                return True
            found = AStar(newGrid, path, game)
            if found: #finish algorithm
                return True
            else:
                path.pop()
    return False

def print2DimArray(array):
    for l in array:
        print l

# Main
classic = []
classic.append([0,0,1,1,1,0,0])
classic.append([0,0,1,1,1,0,0])
classic.append([1,1,1,1,1,1,1])
classic.append([1,1,1,0,1,1,1])
classic.append([1,1,1,1,1,1,1])
classic.append([0,0,1,1,1,0,0])
classic.append([0,0,1,1,1,0,0])

Game.gridRows = len(classic[0])
Game.gridCols = len(classic)
Game.centerX = 3
Game.centerY = 3

heuristic = H.ExponentialDistanceHeuristic()
game = Game(heuristic, classic)
state0 = game.getState()
solution = AStar(state0.getRepresentation(), Path(), game)
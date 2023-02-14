'''
Team Names: Allen Chan, Jacob Cheney
'''
import sys

#For queues
from collections import deque


outf = sys.argv[4]
#Class for representing a state
class State:
    def __init__(self, wolfLeft, chickenLeft, wolfRight, chickenRight, boat, cost):
        self.chickenLeft = chickenLeft
        self.chickenRight = chickenRight

        self.wolfRight = wolfRight
        self.wolfLeft = wolfLeft

        self.boat = boat
        self.parent = None
        self.cost = cost
        self.heuristicValue = 0

    #check if action is valid
    def isValid(self):
        #No negative values
        if self.chickenLeft >= 0 and self.chickenRight >= 0 and self.wolfLeft >= 0 and self.wolfRight >= 0:
            #Check to make sure that the state is actually valid
            #State needs to make sure that either banks have less chickens than wolves and also make sure that there is a chicken there

            if (self.chickenLeft >= self.wolfLeft or self.chickenLeft == 0) and (self.chickenRight >= self.wolfRight or self.chickenRight == 0):
                return True
            else:
                return False
        else:
            return False


    def __eq__(self, other):
        if self.chickenLeft == other.chickenLeft and self.wolfLeft == other. wolfLeft and self.wolfRight == other.wolfRight and self.boat == other.boat:
            #If everything matches then we know they're equivalent!
            return True
        else:
            return False

    def printNode(self):
        #print("Left bank: ", self.chickenLeft, " chickens ", self.wolfLeft, " wolves ", "Right Bank: ", self.chickenRight, " chickens ", self.wolfRight, " wolves")

        f = open(outf, "a")

        print("Left bank: ", self.chickenLeft, " chickens ", self.wolfLeft, " wolves ", "Right Bank: ", self.chickenRight, " chickens ", self.wolfRight, " wolves")

        f.write("Left bank: " +  str(self.chickenLeft) + " chickens " + str(self.wolfLeft) + " wolves " + "Right Bank: " + str(self.chickenRight) + " chickens " + str(self.wolfRight) + " wolves" + '\n')

#Global variables
frontier = []
exploredNodes = []
expandedNodes = 0
priorityQueue = []

def expand(state):
    global frontier
    
    #Get the sucessors
    successorNodes = getSuccessors(state)

    #Placing all the VALID sucessor nodes into the frontier
    for node in successorNodes:
        frontier.append(node)


def getSuccessors(state):

    #placing the sucessors into the successor array

    #Preform actions on a state, checks if the action is valid or not

    #Fill the sucessors list with valid AND non-valid states

    #Then

    #Iterate over the list of sucessors and determine if each of them is valid or not

    child = []


    #Boat is on the right side of the river
    if state.boat == "0":
        #We make sure to swap the boat bool for every new state

        #print("Boat is on the right side of river")

        #Placing on chicken on the boat
        newState = State(state.wolfLeft, state.chickenLeft + 1, state.wolfRight, state.chickenRight - 1, '1', 1)

        if newState.isValid() == True:
            newState.parent = state
            child.append(newState)

        #Place two chickens on boat
        newState = State(state.wolfLeft, state.chickenLeft + 2, state.wolfRight, state.chickenRight - 2, '1', 2)

        if newState.isValid() == True:
            newState.parent = state
            child.append(newState)

        #Put one wolf on the boat
        newState = State(state.wolfLeft + 1, state.chickenLeft, state.wolfRight - 1, state.chickenRight, '1', 1)

        if newState.isValid() == True:
            newState.parent = state
            child.append(newState)

        #Put one wolf and one chicken in boat
        newState = State(state.wolfLeft + 1, state.chickenLeft + 1, state.wolfRight - 1, state.chickenRight - 1, '1', 2)

        if newState.isValid() == True:
            newState.parent = state
            child.append(newState)

        #Put two wolves in the boat
        newState = State(state.wolfLeft + 2, state.chickenLeft, state.wolfRight - 2, state.chickenRight , '1', 2)

        if newState.isValid() == True:
            newState.parent = state
            child.append(newState)
    

    
    #Boat is on the left bank
    if state.boat == '1':
                #Placing on chicken on the boat
        newState = State(state.wolfLeft, state.chickenLeft - 1, state.wolfRight, state.chickenRight + 1, '0', 1)

        if newState.isValid() == True:
            newState.parent = state
            child.append(newState)

        #Place two chickens on boat
        newState = State(state.wolfLeft, state.chickenLeft - 2, state.wolfRight, state.chickenRight + 2, '0', 2)

        if newState.isValid() == True:
            newState.parent = state
            child.append(newState)

        #Put one wolf on the boat
        newState = State(state.wolfLeft - 1, state.chickenLeft, state.wolfRight + 1, state.chickenRight, '0', 1)

        if newState.isValid() == True:
            newState.parent = state
            child.append(newState)

        #Put one wolf and one chicken in boat
        newState = State(state.wolfLeft - 1, state.chickenLeft - 1, state.wolfRight + 1, state.chickenRight + 1, '0', 2)

        if newState.isValid() == True:
            newState.parent = state
            child.append(newState)

        #Put two wolves in the boat
        newState = State(state.wolfLeft - 2, state.chickenLeft, state.wolfRight + 2, state.chickenRight, '0', 2)

        if newState.isValid() == True:
            newState.parent = state
            child.append(newState)

    return child


def isAGoalState(state, goal):

    if state == goal:
        return True
    else:
        return False
    pass


#Uses FIFO
def bfs(start, goal):
    global frontier
    global expandedNodes
    #Place node onto the frontier

    frontier.append(start)
    foundGoal = False

    print("Starting search")

    #As long as the frontier isn't empty, we need to keep expanding nodes
    #Just trying to get a few iterations of it with i
    while foundGoal == False:

        #Check for empty frontier
        if len(frontier) == 0:
            foundGoal = True #We've failed to find the goal node
            print("Failed to find goal state")

            f = open(outf, 'a')
            print("Failed to find goal state")
            f.close()

            return False

        #Choose node from frontier
        currNode = frontier.pop(len(frontier) - 1) #Gives us the first thing on the queue
        
        #Check if current node we chose is a goal state, return if it is
        if isAGoalState(currNode, goal):
        #Making sure we break out of the loop
            foundGoal = True

            f = open(outf, 'a')
            print("Found a goal state!")
            currNode.printNode()

            return True 



        #Add chosen node to explored set
        
        #Expand current chosen node, add all resultant nodes to frontier
        #ONLY if the node is not in the frontier or explored set already

        #currNode.printNode()

        #Only expand if we haven't visited this node yet
        if currNode not in exploredNodes:

            exploredNodes.append(currNode)

            expandedNodes = expandedNodes + 1

            currNode.printNode()

            expand(currNode)

    f.close()

#Uses LIFO
def dfs(start, goal):
    global frontier
    global expandedNodes
    #Place node onto the frontier

    frontier.append(start)

    foundGoal = False

    print("Starting search")

    #As long as the frontier isn't empty, we need to keep expanding nodes
    #Just trying to get a few iterations of it with i
    while foundGoal == False:

        #Check for empty frontier
        if len(frontier) == 0:
            foundGoal = True #We've failed to find the goal node
            print("Failed to find goal state")

            f = open(outf, 'a')
            print("Failed to find goal state")

            return False

        #Choose node from frontier
        currNode = frontier.pop(0) #Gives us the first thing on the queue
        
        #Check if current node we chose is a goal state, return if it is
        if isAGoalState(currNode, goal):
        #Making sure we break out of the loop
            foundGoal = True
            
            print("Found a goal state!")

            f = open(outf, 'a')
            print("Found a goal state!")
            f.close()

            currNode.printNode()

            return True 

        #Expand current chosen node, add all resultant nodes to frontier
        #ONLY if the node is not in the frontier or explored set already
        if currNode not in exploredNodes:

            exploredNodes.append(currNode)

            expandedNodes = expandedNodes + 1

            currNode.printNode()

            expand(currNode)
    f.close()


#Uses LIFO, w/ iterative tracker
def iddfs(start, goal):
    global frontier
    global expandedNodes
    #iterativeLimit = 0
    #Place node onto the frontier

    frontier.append(start)

    foundGoal = False
    limit = 9999
    currLimit = 0

    print("Starting search")

    #As long as the frontier isn't empty, we need to keep expanding nodes
    #Just trying to get a few iterations of it with i
    while currLimit != limit:

        #Check for empty frontier
        if len(frontier) == 0:
            foundGoal = True #We've failed to find the goal node
            print("Failed to find goal state")

            f = open(outf, 'a')
            print("Failed to find goal state")
            f.close()

            return False

        #Choose node from frontier
        currNode = frontier.pop() #Gives us the first thing on the queue
        
        #Check if current node we chose is a goal state, return if it is
        if isAGoalState(currNode, goal):
        #Making sure we break out of the loop
            foundGoal = True

            currNode.printNode()

            print("It took ", currLimit, " depth level to find the goal!")

            return True

        #Expand current chosen node, add all resultant nodes to frontier
        #ONLY if the node is not in the frontier or explored set already

        if foundGoal == False:

            currLimit = currLimit + 1

        if currNode not in exploredNodes:
    
            exploredNodes.append(currNode)

            expandedNodes = expandedNodes + 1

            currNode.printNode()

            expand(currNode)


def getHueristic(goalNode, currNode):

    #Current Heuristic, check our current state, check our current node n and compare
    #We know that the nodes we have are all valid, so we don't have to worry about that
    #How far are we away from the goal state? Check the difference between each of the current chicken/wolf, boat, etc


    heurValue = (goalNode.chickenLeft - currNode.chickenLeft) + (goalNode.wolfLeft - currNode.wolfLeft)
    

    return heurValue

#Uses Priority Queue
def astar(start, goal):

    global frontier
    global expandedNodes
    #Place node onto the frontier

    frontier.append(start)
    foundGoal = False

    print("Starting search")

    #As long as the frontier isn't empty, we need to keep expanding nodes
    #Just trying to get a few iterations of it with i
    while foundGoal == False:

        #Check for empty frontier
        if len(frontier) == 0:
            foundGoal = True #We've failed to find the goal node
            print("Failed to find goal state")

            f = open(outf, 'a')
            print("Failed to find goal state")
            f.close()

            return False

        #Choose the node from the frontier with the highest heuristic
        #Iterate over all the nodes in the frontier to find it 
        #Mimics what a priority queue would do and select the best option.

        currentHighestNode = frontier[0]

        for node in frontier:

            if node.heuristicValue > currentHighestNode.heuristicValue:
                
                currentHighestNode = node
            
        currNode = currentHighestNode

        #Check if current node we chose is a goal state, return if it is
        if isAGoalState(currNode, goal):
        #Making sure we break out of the loop
            foundGoal = True

            f = open(outf, 'a')
            print("Found a goal state!")
            currNode.printNode()

            return True 

        #Add chosen node to explored set
        
        #Expand current chosen node, add all resultant nodes to frontier
        #ONLY if the node is not in the frontier or explored set already

        #currNode.printNode()

        #Only expand if we haven't visited this node yet



        if currNode not in exploredNodes:

            exploredNodes.append(currNode)

            expandedNodes = expandedNodes + 1

            currNode.printNode()

            #Only expand the node if it meets the heuristic criteria
            
            expand(currNode)



def main():
    #Take command line arguments
    print('Argument list: ', str(sys.argv))

    if len(sys.argv) < 5:
        print("Not enough arguements")
    else:
        start = sys.argv[1]
        goal = sys.argv[2]
        mode = sys.argv[3]
        outputFile = sys.argv[4]

        startFile = open(start, "r")
        goalFile = open(goal, "r")

        fullStartLine = []
        fullGoalLine = []

        #Appending to end of list
        for line in startFile:
            contents = line.strip().split(",")
            fullStartLine += contents

        for line in goalFile:
            contents = line.strip().split(",")
            fullGoalLine += contents

        startFile.close()
        goalFile.close()

        leftBank = {
            "chickens" : 0,
            "wolves" : 0,
            "boat" : 0,
        }

        rightBank = {
            "chickens" : 0,
            "wolves" : 0,
            "boat" : 0,
        }

        #0/3 = chickens
        #1/4 = wolves
        #2/5 = boat state

        #Processing for the left bank
        leftBank["chickens"] = int(fullStartLine[0])
        leftBank["wolves"] = int(fullStartLine[1])
        leftBank["boat"] = int(fullStartLine[2])

        #Processing for the right bank
        rightBank["chickens"] = int(fullStartLine[3])
        rightBank["wolves"] = int(fullStartLine[4])

        initialState = State(leftBank["wolves"], leftBank["chickens"], rightBank["wolves"], rightBank["chickens"], str(leftBank["boat"]), 0)
        initialState.parent = "None"
        
        goalState = State(int(fullGoalLine[1]), int(fullGoalLine[0]), int(fullGoalLine[4]), int(fullGoalLine[3]), str(fullGoalLine[2]), 0)

        initialState.heuristicValue = getHueristic(initialState, goalState)

        if mode == "bfs":
            #print("in bfs")
            #print("Starting BFS")
            bfs(initialState, goalState)

        if mode == "dfs":
            #print("in dfs")
            dfs(initialState, goalState)

        if mode == "iddfs":
            #print("in iddfs")
            iddfs(initialState, goalState)
        if mode == "astar":
            #print("in astar")
            astar(initialState, goalState)
        
        print("Nodes explored a total of: ", expandedNodes)
        
        f = open(outputFile, "a")
        f.write("Nodes explored a total of: %d" % expandedNodes)
        f.write("\n\n")
        f.close()
        
if __name__ == "__main__":
    main()
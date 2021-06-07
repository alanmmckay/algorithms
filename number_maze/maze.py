from vertex import Vertex
from graph import Graph
from helpers import *
import sys
sys.setrecursionlimit(10**6) #this is always a good sign...
  

class MazeCoordinate(object):
    def __init__(self,pair,distance):
        self.pair = pair
        self.distance = distance
        self.x = pair[0]
        self.y = pair[1]
        
    def getX(self):
        return self.x
    
    def getY(self):
        return self.y
    
    def getDistance(self):
        return self.distance
    
    def getPair(self):
        return self.pair
    
    #This method is used to check to see if the coordinate exists in some queue
    def __eq__(self,mazeCoordinate):
        if type(mazeCoordinate) == MazeCoordinate:
            return (mazeCoordinate.getPair(),mazeCoordinate.getDistance()) \
                == (self.pair,self.distance)

  
class Maze(object):
    def __init__(self):
        self.rows = 0
        self.matrix = []
        ''' ---
            a coordinate is a tuple, where the first element is an x,y pair
            and the second coordinate is the distance measure. Need to make
            a class for this.
        '''
        self.coordinates = []
        self.graph = Graph()
        self.startCoordinate = ()
        self.startVertex = Vertex(None)
        self.endCoordinate = ()
        self.graphQueue = []
        self.callcount = 0
        
    def importFrom(self,data):
        
        self.rows = int(data[0].split()[0])
        switch = False
        row = []

        for index in range(1,len(data)):
            split = data[index].split()
            if len(split) > 0:
                num = int(split[0])
                row.append(num)
                if len(row) == self.rows:
                    self.matrix.append(row)
                    row = []
    
    def displayMatrix(self):
        string = '\n'
        for row in self.matrix:
            for num in row:
                string += str(num) + '  '
            string += '\n'
        return string
    
    def getMatrix(self):
        return self.matrix
    
    def getCoordinates(self):
        #which processes are reliant on this
        if not self.coordinates:
            for y in range(0,len(self.matrix)):
                for x in range(0,len(self.matrix[y])):
                    self.coordinates.append(((x+1,y+1),self.matrix[y][x]))
        return self.coordinates
    
    def getCoordinate(self,pair):
        return (pair,self.matrix[pair[1]-1][pair[0]-1])
    
    #need to refactor the logic for valid input
    def traverseFrom(self,coordinate,direction):
        if direction in Directions and coordinate[1] > 0:
            if direction == Directions.LEFT:
                if coordinate[0][0]-coordinate[1] > 0:
                    pair = (coordinate[0][0]-coordinate[1],coordinate[0][1])
                else:
                    return False
            elif direction == Directions.RIGHT:
                if coordinate[0][0]+coordinate[1] <= self.rows:
                    pair = (coordinate[0][0]+coordinate[1],coordinate[0][1])
                else:
                    return False
            elif direction == Directions.UP:
                if coordinate[0][1]-coordinate[1] > 0:
                    pair = (coordinate[0][0],coordinate[0][1]-coordinate[1])
                else:
                    return False
            elif direction == Directions.DOWN:
                if coordinate[0][1]+coordinate[1] <= self.rows:
                    pair = (coordinate[0][0],coordinate[0][1]+coordinate[1])
                else:
                    return False
            return self.getCoordinate(pair)
        else:
            return False

    def traversalsFrom(self,coordinate):
        paths = []
        for direction in Directions:
            path = self.traverseFrom(coordinate,direction)
            if path:
                paths.append(path)
        return paths
    
    def generateGraph(self):
        #probably oughta refactor this for the sake of a name that makes sense:
        self.getCoordinates() #prime the coordinates object
        self.startCoordinate = self.coordinates[0]
        self.endCoordinate = self.coordinates[-1]
        self.graphQueue = [self.startCoordinate]
        self.startVertex = self.graph.createVertex(self.startCoordinate[0],self.startCoordinate[1])
        self.generateGraphDFS(self.startVertex)
        
    def generateGraphDFS(self,vertex):
        self.callcount = self.callcount + 1
        coordinate = (vertex.getID(),vertex.getLabel())
        neighbors = self.traversalsFrom(coordinate)
        for neighbor in neighbors:
            if neighbor not in self.graphQueue:
                newVertex = self.graph.createVertex(neighbor[0],neighbor[1])
                self.graphQueue.append(neighbor)
                self.generateGraphDFS(newVertex)
            self.graph.createEdge(vertex,self.graph.getVertex(neighbor[0]))
            
    def lenShortestRoute(self,sourceCoordinate,destinationCoordinate):
        source = (sourceCoordinate[0],sourceCoordinate[1],0)
        bfsQueue = [source] #(tuple,distance,clock)
        
        #build a dictionary to store status of each node
        status = dict()
        for coordinate in self.coordinates:
            status[coordinate] = Status.NEW
            
        queueIndex = 0
        queueLength = 1
        while queueIndex < queueLength:
            node = bfsQueue[queueIndex]
            coordinate = (node[0],node[1]) #(tuple, distance)
            status[coordinate] = Status.ACTIVE
            neighbors = self.traversalsFrom(coordinate)
            for neighbor in neighbors: #(tuple,distance)
                if status[neighbor] == Status.NEW:
                    status[neighbor] = status[neighbor] + 1
                    bfsQueue.append((neighbor[0],neighbor[1],node[2]+1))
                    queueLength = queueLength + 1
                    if neighbor == destinationCoordinate:
                        return (neighbor[0],neighbor[1],node[2] + 1)
            queueIndex = queueIndex + 1
            
    def getGraph(self):
        return self.graph
    
    def renderGraph(self):
        return self.graph.renderGraph(self.startVertex) 
    

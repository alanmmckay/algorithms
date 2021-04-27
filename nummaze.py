from enum import Enum
import sys
sys.setrecursionlimit(10**6)

class Status(Enum):
    NEW = 1;
    ACTIVE = 2;
    FINISHED = 3;
    
    def __add__(self,val):
        if val == 1:
            if self == Status.NEW:
                return Status.ACTIVE
            else:
                return Status.FINISHED
        else:
            return False
        
        
class Directions(Enum):
    UP = 1;
    DOWN = 2;
    LEFT = 3;
    RIGHT = 4;
    
    def __iter__(self):
        yield self.UP
        yield self.DOWN
        yield self.LEFT
        yield self.RIGHT
        
        
class Maze(object):
    def __init__(self):
        self.rows = 0
        self.matrix = []
        self.coordinates = []
        self.graph = Graph()
        self.startCoordinate = ()
        self.startVertex = Vertex(None)
        self.endCoordinate = ()
        self.graphQueue = []
        
    def importFrom(self,fileName):
        try:
            f = open(fileName,'r')
            data = f.readlines()
            f.close()
        except:
            #probably need to prime data here
            print("Invalid filename!")
        
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
        if not self.coordinates:
            for y in range(0,len(self.matrix)):
                for x in range(0,len(self.matrix[y])):
                    self.coordinates.append(((x+1,y+1),self.matrix[y][x]))
        return self.coordinates
    
    def getCoordinate(self,pair):
        for coordinate in self.coordinates:
            if pair == coordinate[0]:
                return coordinate
        return False
    
    def traverseFrom(self,coordinate,direction):
        if direction in Directions and coordinate[1] > 0:
            if direction == Directions.UP:
                if coordinate[0][1]-coordinate[1] > 0:
                    pair = (coordinate[0][0],coordinate[0][1]-coordinate[1])
                else:
                    return False
            elif direction == Directions.DOWN:
                if coordinate[0][1]+coordinate[1] <= self.rows:
                    pair = (coordinate[0][0],coordinate[0][1]+coordinate[1])
                else:
                    return False
            elif direction == Directions.LEFT:
                if coordinate[0][0]-coordinate[1] > 0:
                    pair = (coordinate[0][0]-coordinate[1],coordinate[0][1])
                else:
                    return False
            elif direction == Directions.RIGHT:
                if coordinate[0][0]+coordinate[1] <= self.rows:
                    pair = (coordinate[0][0]+coordinate[1],coordinate[0][1])
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
        coordinate = (vertex.getID(),vertex.getLabel())
        neighbors = self.traversalsFrom(coordinate)
        for neighbor in neighbors:
            if neighbor not in self.graphQueue:
                newVertex = self.graph.createVertex(neighbor[0],neighbor[1])
                self.graphQueue.append(neighbor)
                self.generateGraphDFS(newVertex)
            self.graph.createEdge(vertex,self.graph.getVertex(neighbor[0]))
            
            
    def findRoute(self,source,destination):
        dfsQueue = [source]
        count = 0
        while dfsQueue:
            vertex = dfsQueue.pop()
            if vertex == destination:
                return count
            else:
                vertex.incrementStatus()
                for neighbor in vertex.getOutNeighbors():
                    if neighbor.getStatus() == Status.NEW:
                        dfsQueue.append(neighbor)
            count = count + 1
        return False
        
            
        
            
    def getGraph(self):
        return self.graph
    
    def renderGraph(self):
        return self.graph.renderGraph(self.startVertex)
        
     
            
class Vertex(object):
    def __init__(self,identifier,label = None):
        self.identifier = identifier
        self.label = label
        self.inNeighbors = []
        self.outNeighbors = []
        self.status = Status.NEW
        
    def getID(self):
        return self.identifier
    
    def getLabel(self):
        return self.label
    
    def setLabel(self,label):
        self.label = label
        return True
    
    def getStatus(self):
        return self.status
    
    def setStatus(self,status):
        self.status = status
        return True
    
    def incrementStatus(self):
        if self.status == Status.FINISHED:
            return False
        else:
            self.status = self.status + 1
            return True
    
    def addInNeighbor(self,vertex):
        if vertex not in self.inNeighbors:
            self.inNeighbors.append(vertex)
            return True
        else:
            return False
    
    def getInNeighbors(self):
        return self.inNeighbors
    
    def addOutneighbor(self,vertex):
        if vertex not in self.outNeighbors:
            self.outNeighbors.append(vertex)
            return True
        else:
            return False
        
    def getOutNeighbors(self):
        return self.outNeighbors
    

class Graph(object):
    def __init__(self):
        self.vertices = []
        self.vertexIds = []
        self.edges = []
        
        self.graphQueue = []
        self.edge_str = ""
        self.node_str = ""
    
    def createVertex(self,identifier,label=None):
        if identifier not in self.vertexIds:
            vertex = Vertex(identifier,label)
            self.vertices.append(vertex)
            self.vertexIds.append(identifier)
            return vertex
        else:
            return False
    
    def createEdge(self,vertexA,vertexB,weight = None):
        if vertexA.getID() in self.vertexIds and vertexB.getID() in self.vertexIds:
            edge = (vertexA,vertexB,weight)
            if edge not in self.edges:
                self.edges.append(edge)
                vertexA.addOutneighbor(vertexB)
                vertexB.addInNeighbor(vertexA)
                return edge
            else:
                return False
        else:
            return False
        
    def getVertex(self,identifier):
        for vertex in self.vertices:
            if vertex.getID() == identifier:
                return vertex
        return False
    
    def getVertices(self):
        return self.vertices
    
    def vertexCheck(self,identifier):
        if identifier in vertexIds:
            return True
        else:
            return False
        
    def renderGraph(self,vertex):
        self.graphQueue = [vertex]
        self.edge_str = ""
        self.node_str = ""
        return self.renderGraphDFS(vertex)
    
    def renderGraphDFS(self,vertex):
        self.node_str += '"'+str(vertex.getID())+'"'
        self.node_str += ' [label="'+str(vertex.getID())
        self.node_str += '",shape=circle,fixedsize=true,fontsize=18,width=1]\n'
        self.graphQueue.append(vertex)
        #vertex.incrementStatus()
        for outNeighbor in vertex.getOutNeighbors():
            if outNeighbor not in self.graphQueue:
                self.renderGraphDFS(outNeighbor)
            self.edge_str += '"'+str(vertex.getID())+'" -> "' + str(outNeighbor.getID())+'"'
            self.edge_str += ' [penwidth=1]\n'
        #vertex.incrementStatus()
        primer_str = 'digraph D {\n'+self.node_str+'\n'+self.edge_str+'}'
        return primer_str + self.node_str + self.edge_str
    
    
        

maze = Maze()
maze.importFrom("SmallB.txt")
#maze.importFrom("mediumX.txt")
print(len(maze.matrix[0]))
#print(maze.displayMatrix())

#maze.generateGraph()

#print(maze.renderGraph())
#dfs logic
'''
coordinates = maze.getCoordinates()
print(coordinates)
print(maze.traversalsFrom(coordinates[0]))

g = Graph()
start = coordinates[0]
end = coordinates[-1]

print(start)
print(end)
created = [start]
startingVertex = g.createVertex(start[0],start[1])
print(start)

def formGraph(vertex):
    coordinate = (vertex.getID(),vertex.getLabel())
    neighbors = maze.traversalsFrom(coordinate)
    for neighbor in neighbors:
        if neighbor not in created:
            newVertex = g.createVertex(neighbor[0],neighbor[1])
            created.append(neighbor)
            formGraph(newVertex)
        g.createEdge(vertex,g.getVertex(neighbor[0]))
        
formGraph(startingVertex)
'''

#graph logic
'''
discovered = []
edge_str = ""
node_str = ""

def generateGraph(vertex):
    global discovered
    global edge_str
    global node_str
    node_str += '"'+str(vertex.getID())+'"'
    node_str += ' [label ="'+str(vertex.getID())
    node_str += '",shape=circle,fixedsize=true,fontsize=18,width=1]\n'
    discovered.append(vertex)
    vertex.incrementStatus()
    for outNeighbor in vertex.getOutNeighbors():
        if outNeighbor not in discovered:
            generateGraph(outNeighbor)
        edge_str += '"'+str(vertex.getID()) + '" -> "' + str(outNeighbor.getID())+'"'
        edge_str += ' [penwidth=1]\n'
    vertex.incrementStatus()

#generateGraph(startingVertex)
    #create queue 
    #vertex = g.createVertex(pair[0],pair[1])

print("digraph D { \n "+node_str+"\n"+edge_str+"}")

print(len(g.vertices))
'''

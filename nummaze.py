from enum import Enum

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
        
    def importFrom(self,fileName):
        try:
            f = open(fileName,'r')
            data = f.readlines()
            f.close()
        except:
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
        if direction in Directions:
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
     
            
class Vertex(object):
    def __init__(self, identifier, label = None):
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
            self.status + 1
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
    
    def createVertex(self, identifier, label=None):
        if identifier not in vertexIds:
            vertex = Vertex(identifier,label)
            self.vertices.append(vertex)
            return vertex
        else:
            return False
    
    def createEdge(self,vertexA,vertexB,weight = None):
        if vertexA.getID() in vertexIds and vertexB.getID() in vertexIds:
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
    
    def vertexCheck(self,identifier):
        if identifier in vertexIds:
            return True
        else:
            return False
        
    
    
    

maze = Maze()
maze.importFrom("SmallB.txt")
print(maze.displayMatrix())
pairs = maze.getCoordinates()
print(pairs)
print(maze.traversalsFrom(pairs[0]))



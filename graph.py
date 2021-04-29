from vertex import Vertex 
from helpers import Status
 
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
        return primer_strMaze

from vertex import Vertex 
from helpers import Status
 
class Graph(object):
    def __init__(self):
        self.vertices = []
        self.vertexIds = []
        self.vertexMap = dict()
        self.edges = []
        self.edgeMap = dict()

        self.graphQueue = []
        self.edge_str = ""
        self.node_str = ""
    
    def createVertex(self,identifier,label=None):
        if not self.vertexCheck(identifier):
            vertex = Vertex(identifier,label)
            self.vertices.append(vertex)
            self.vertexIds.append(identifier)
            self.vertexMap[identifier] = vertex
            return vertex
        else:
            return False
    
    def createEdge(self,vertexA,vertexB,weight = None):
        if self.vertexCheck(vertexA.getID()) and self.vertexCheck(vertexB.getID()):
            edge = (vertexA,vertexB,weight)
            if not self.edgeCheck(edge):
                self.edges.append(edge)
                #self.edgeMap[edge] = None
                vertexA.addOutneighbor(vertexB)
                vertexB.addInNeighbor(vertexA)
                return edge
            else:
                return False
        else:
            return False
        
    def getVertex(self,identifier):
        if self.vertexCheck(identifier):
            return self.vertexMap[identifier]
        else:
            return False
    
    def getVertices(self):
        return self.vertices
    
    def vertexCheck(self,identifier):
        try:
            self.vertexMap[identifier]
            return True
        except:
            return False

    def edgeCheck(self,edge):
        try:
            self.edgeMap[edge]
            return True
        except:
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
        return primer_str

from helpers import Status

class Vertex(object):
    def __init__(self,identifier,label = None):
        self.identifier = identifier
        self.label = label
        self.inNeighbors = []
        self.outNeighbors = []
        self.status = Status.NEW
        self.clock = 0
        self.parent = None
        
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
    
    def setClock(self,time):
        self.clock = time
        return True
    
    def getClock(self):
        return self.clock

    def setParent(self,parent):
        self.parent = parent
        return True

    def getParent(self):
        return self.parent

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
       

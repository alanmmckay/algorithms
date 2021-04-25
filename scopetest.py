
class Numm(object):
    def __init__(self,val):
        self.val = val
        
    def getVal(self):
        return self.val 
    
    def setVal(self,val):
        self.val = val 
        
class Test(object):
    def __init__(self):
        self.objects = []
        
    def produce(self,num):
        new = Numm(num)
        self.objects.append(new)
        return new

test = Test()
ob = test.produce(3)
ob.setVal(6)
print(test.objects[0].getVal())
tup = (ob,)
print(ob)
print(tup)
tup[0].setVal(5)
print(test.objects[0].getVal())

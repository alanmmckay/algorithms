infinity = float('inf')

class Board(object):
    def __init__(self, n):
        self.positions = list()
        for position in range(0,n):
            self.positions.append(Pit())
        self.empty = False
        self.initial = list()
            
    def primePits(self,string):
        count = 0
        for char in string:
            self.positions[count].setValue(int(char))
            count += 1
        self.initial = self.getState()
    
    def setValues(self,quantities):
        count = 0
        for quantity in quantities:
            self.positions[count].setValue(int(quantity))
            count += 1
    
    def setState(self,state_string):
        quantities = list()
        characters = state_string.split()
        for character in characters:
            quantities.append(character)
        self.setValues(quantities)
    
    def getPits(self):
        return self.positions
    
    def getValues(self):
        values = list()
        finished_bool = True
        for position in self.positions:
            value = position.getValue()
            values.append(value)
        return values
     
    def getState(self):
        state = str()
        values = self.getValues()
        for value in values:
            state += str(value)
        return state
    
    def isEmpty(self):
        for position in self.positions:
            if position.getValue() != 0:
                return False
        return True
    
    def makeMove(self, position):
        qty = self.positions[position].grab()
        pit = position + 1
        while qty != 0 and pit < len(self.positions):
            self.positions[pit].incrementValue()
            pit += 1
            qty -= 1
        return self.getState()
            
    def getPossibleMoves(self):
        possible_moves = list()
        count = 0
        for pit in self.positions:
            if pit.getValue() != 0:
                possible_moves.append(count)
            count += 1
        return possible_moves
    
    def minimax(self, state, position, choice):
        self.setValues(state)
        if position != None:
            self.makeMove(position)
        if self.isEmpty():
            if choice:
                return (position, -1)
            elif not choice:
                return (position, 1)
        elif choice:
            highest = -(infinity)
            for possible_move in self.getPossibleMoves():
                tmp = self.minimax(self.getValues(), possible_move, not choice)[1]
                if tmp > highest:
                    highest = tmp
                    move = possible_move
            self.setValues(state)
            return (move, highest)
        else:
            lowest = infinity
            for possible_move in self.getPossibleMoves():
                tmp = self.minimax(self.getValues(), possible_move, not choice)[1]
                if tmp < lowest:
                    lowest = tmp
                    move = possible_move
            self.setValues(state)
            return (move, lowest)
        
    def play(self):
        result = self.minimax(self.getValues(),None,True)
        if result[1] == 1:
            cond = 'win'
        elif result[1] == -1:
            cond = 'lose'
        return (result[0]+1,cond)
    
class Pit(object):
    def __init__(self, qty = 0):
        self.value = qty
    
    def getValue(self):
        return self.value
    
    def setValue(self, qty):
        self.value = qty
        
    def incrementValue(self):
        self.value += 1
        
    def grab(self):
        qty = self.value
        self.value = 0
        return qty


def search(string):
    board = Board(len(string))
    board.primePits(string)
    return board.play()


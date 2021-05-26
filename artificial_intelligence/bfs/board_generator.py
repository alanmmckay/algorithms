'''
A board consists of a set of nodes.
   -These nodes are organized in a square
From each node, one of four moves can be made
   -up, down, left, right
   -The value associated with each node determines the amount of nodes
    that must be traversed. 
       -One cannot move off the board.
       -Only one node has a non-numeric value. That node has a value of
        G. The goal is to find G from the node which represents the top
        left of the board;
'''
'''
The board is represented as a string of unseparated values. A board 
with two rows and two columns has 4 nodes, and thus 4 characters. 
A board with three rows and three columns has 9 nodes, etc.
    -Thus, if the amount of nodes represented on a board is n, then a
     board has sqrt(n) rows and columns. The first sqrt(n) nodes 
     represent the first row. The following sqrt(n) nodes represent
     the second row, and so on.
    -To determine which 
'''
'''
To determine which column a node exists, take it's positional value within
the board string (starting at index 0) and mod sqrt(n). Add one to that
value.
To determine which row a node exists, apply the node position // sqrt(n)
and add one to that value.
   -NOTE the string representation of a board implies it makes no sense
    to have a value greater than 9.
It makes no sense for a node to contain a value, other than G, that cannot
reach at least one other node. There is no need for a value of 9 on a board
which only has a row/column length of 8.
'''

import math
import random

def generate_random_board(length):
    nodeQty = length * length
    if length > 9:
        return False
    
    board = str()
    for nodePosition in range(0,nodeQty):
        leftQty = nodePosition % length
        rightQty = (length - 1) - (nodePosition % length)
        aboveQty = nodePosition // length
        belowQty = (length - 1) - (nodePosition // length)
        maximumMove = max(leftQty, rightQty, aboveQty, belowQty)
        nodeValue = random.randint(1,maximumMove)
        board += str(nodeValue)
    
    g_position = random.randint(0,nodeQty)
    board = board[0:(g_position-1)] + "G" + board[(g_position-1):(nodeQty-1)]
    return board

print(generate_random_board(2))
        

''' ---- ---- ---- '''
#AI: Programming Assignment #1
#Author: Alan McKay
#Breadth First Search function for lillypad puzzle
''' ---- ---- ---- '''

import math

#ad-hoc function to address the fact path direction information
#was not maintained while generating the sequence of nodes for
#the path
def calculate_moves(nodes, board):
    path = str()
    for i in range(0,len(nodes)-1):
        if nodes[i] < nodes[i+1]:
            #moved down or right
            if nodes[i+1] - nodes[i] < math.sqrt(len(board)):
                #stayed in row
                path += "R"
            else:
                #stayed in column
                path += "D"
        elif nodes[i] > nodes[i+1]:
            if nodes[i] - nodes[i+1] < math.sqrt(len(board)):
                #stayed in row
                path += "L"
            else:
                #stayed in column
                path += "U"
            #moved up or left
    return path
            

#main search function; Uses BFS strategy
def search(board_string):
    frontier = list()
    explored = list()
    frontier.append([0])
    node_count = len(board_string)
    board_length = int(math.sqrt(len(board_string)))
    # consider validating the board length; validate single occurance of G
    while len(frontier) != 0:
        #grab the first element in the frontier:
        current_path = frontier[0]
        #remove the first element in the frontier:
        frontier = frontier[1:len(frontier)]
        #The current node being evaluated:
        current_node_position = int(current_path[-1])
        #The jump value of the current node:
        current_node_value = board_string[current_node_position]
        
        if current_node_position not in explored:
            explored.append(current_node_position)
            if current_node_value == "G":
                return calculate_moves(current_path, board_string)
            else:
                current_node_value = int(current_node_value)
            
            if (current_node_position + 1) + (current_node_value * board_length) <= node_count:
                #valid move down
                new_path = list(current_path)
                new_path.append(current_node_position + (current_node_value * board_length))
                frontier.append(new_path)
                    
            if (board_length - 1) - (current_node_position % board_length) >= current_node_value:
                #valid move right; amount of nodes in the row to the right of current node
                new_path = list(current_path)
                new_path.append(current_node_position + current_node_value)
                frontier.append(new_path)
                
            if current_node_position % board_length >= current_node_value:
                #valid move left; amount of nodes in the row to the left of current node
                new_path = list(current_path)
                new_path.append(current_node_position - current_node_value)
                frontier.append(new_path)
                
            if (current_node_position + 1) - (current_node_value * board_length) > 0:
                #valid move up;
                new_path = list(current_path)
                new_path.append(current_node_position - (current_node_value * board_length))
                frontier.append(new_path)
            
    return "No Solution"

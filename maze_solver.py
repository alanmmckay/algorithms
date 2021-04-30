from maze import Maze
from helpers import textImport
import time

inputStr = "Input Number Maze File Name (Include Extension; input q to quit): "
userInput = input(inputStr)
while userInput != 'q':
    data = textImport(userInput)
    if data:
        start = time.time()
        maze = Maze()
        maze.importFrom(data)
        maze.getCoordinates()
        info = maze.lenShortestRoute(maze.coordinates[0],maze.coordinates[-1])
        end = time.time()
        string = "Length of shortest path: "+str(info[2])+"\n"
        string += "Runtime: "+str(end-start)+" seconds\n"
        print(string)
        inputStr = "Input Number Maze File Name (Include Extension; input q to quit): "
    else:
        inputStr = "\n!!! Invalid File\n" + inputStr
    userInput = input(inputStr)
print('\nQuitting\n')

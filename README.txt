McKay - Number Maze Solver

I dove deep into this assignment. You'll find that this assignment consists of 
5 python files. What needs to be run through the interpreter is maze_solver.py.
It contains the logic that kicks off the execution of the algorithms involved 
for this assignment.

The inclusion of this many files implies I took an object oriented approach -
At least I did while initially diving into the assignment. You will see 
graph.py, vertex.py, maze.py, helpers.py, and maze_solver.py
    The important files and methods for the sake of this assignment are:
        -maze_solver.py
        -maze.py
            contains most of the information to solve the problem for this 
            assignment. The method in which this occurs is lenShortestRoute(). 
            This method calls traversalsFrom() which itself calls traverseFrom()
            which itself calls getCoordinate(). Also involved is importFrom()
            which converts the input data to a matrix, and getCoordinates() 
            which creates a set of (x,y) pairs associated with the matrix and 
            puts them in a tuple with the associated distance measure.
        -helpers.py
            Contains some enum objects and helper functions used outside of 
            these object classes
        
As indicated, maze.py contains most of the logic. The maze class is what holds 
most of the relevent information. lenShortestRoute() takes a BFS approach to 
solving the problem. BFSqueue stores tuples which represent a node within the 
graph search. Each of these tuples have the following elements:
    -a tuple describing the x,y coordinates within the matrix
    -the distance measure associated with the matrix
    -a clock to describe the time at which the tuple was formed and discovered
The algorithm starts off by putting the source coordinate into this queue. It 
then creates a dictionary of all coordinates within the matrix and marks them 
as new. The BFS loops starts by looking at the first entry on the queue, finding
all it's outbound neighbors, and creates their coorinates as described above - 
puting the 3-tuple onto the queue. It only does this if the relevant entry 
within the dictionary previously described has the coordinate marked as new. 
Once the coordinate is placed on the queue it is incremented to active.
    -This occurs until the destination node is discovered, in which a coordinate
    for it is created, and the clock value is returned.
The logic that describes whether or not a move is valid is in traversalsFrom() 
and therefore traverseFrom(). These check to see if a move is valid (whether or
not it stays on the board) then taps into the matrix property of the maze class 
to get the relevant distance measure. It returns the cartesian coordinate and 
the distance measure within a tuple.
    -I need to implement a class to handle the maze coordinates - specifically 
    because the implementation of these methods is kind of messy. What is to 
    note here is that coordinate[0] indicates an x,y pair where coordinate[0][0]
    is an x-coordinate and the y-coordinate is coordinate[0][1]. coordinate[1] 
    is the distance measure.
    
Also included in this class is logic for a DFS search which essentially builds 
the entire graph. I'm still working on this part in terms of trying to make it 
more effecient. This is where the graph.py and vertex.py files come into play. 
Feel free to take a look at those!
    I also have plans to extend the lenShortestRoute() method to produce a 
    graph while it executes.

-------------------------------------------------------------------------

smallX.txt: Length: 9; Runtime: 4.47177 Milliseconds
smallY.txt: Length: 7; Runtime: 1.62888 Milliseconds
mediumX.txt: Length: 63; Rumtime: 139.69588 Milliseconds
mediumY.txt: Length: 62; Runtime: 187.59560 Milliseconds
largeX.txt: Length: 54; Runtime: 22,826.137 Milliseconds
largeY.txt: Length: 56; Runtime: 23050.255 Milliseconds

-------------------------------------------------------------------------

How to run:
Run python3 with the file maze_solver.py. Make sure all the other .py files 
included in this archive are in the same folder. Input the text file name of any
valid files within the same directory as prompted. It will return runtime in 
seconds in addition to the length of the shortest path to solve the number maze.




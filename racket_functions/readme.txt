This is a simple repository of racket functions.
    -These functions are a means to help incorporate features which are
    often taken for granted in a traditional programming language.
    -The creation of these functions also provide a good test bed to
    practice working with the conventions and syntax of racket.
    
Function list:
    index-into-list.rkt:
        -A means to parse through a list as if it were an array.
        -index-into-list takes two arguments. The first of which is an
        list and the second of which is the index value, where the first
        element of a list is considered index 0.
    average:
        -A simple function which takes as input a list of integers and
        returns the average of those integers
    append-list:
        -A function which takes two lists of items as input and returns
        a list in which the items of the second are added to the items
        of the first.
        
To-do:
    -Find a means to validate input data. For example, average relies on
    an input of a list of numbers. If this list were to include a string,
    the interpreter will likely throw an error.

This is a simple repository of racket functions.
    -These functions are a means to help incorporate features which are
    often taken for granted in a traditional programming language.
    -The creation of these functions also provide a good test bed to
    practice working with the conventions and syntax of racket.
    
Function list:
    append-list:
        -A function which takes two lists of items as input and returns
        a list in which the items of the second are added to the items
        of the first.
    apply:
        -An implementation of the apply function, where each element
        of a supplied list is applied to eachother by some supplied
        operand/function.
    average:
        -A simple function which takes as input a list of integers and
        returns the average of those integers
    index-into-list.rkt:
        -A means to parse through a list as if it were an array.
        -index-into-list takes two arguments. The first of which is an
        list and the second of which is the index value, where the first
        element of a list is considered index 0.
    map:
        -An implementation of the map function, where a new list is
        constructed by the result of a supplied function which takes, in
        turn, each element of a supplied list as an argument.
    nested-apply:
        -A mutually recursive implementation of the apply function which
        factors nested lists.
    nested-map:
        -A mutually recursive implementation of the map function which
        factors nested lists.

        
To-do:
    -Find a means to validate input data. For example, average relies on
    an input of a list of numbers. If this list were to include a string,
    the interpreter will likely throw an error.

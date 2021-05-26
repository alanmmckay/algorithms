--McKay - Problem 4 
{-- A sorted stack is a stack with the invariant that the elements on the stack
    are always ordered from smallest to largest.
    -- This invariant is achieved with the following operations:
        -- pop returns and removes the top item of the stack
        -- push x begins by removing items from the head of the stack so long
            as they are less than x: it then adds x to the head of the stack
    -- For example, push 4 [1,2,2,4,5,6] should produce the stack [4,4,5,6] --}


type SStack a = [a]    

pop :: Ord a => SStack a -> Maybe (a, SStack a)
pop [] = Nothing
pop (x : xs) = Just (x, xs)

push :: Ord a => a -> SStack a -> SStack a
push x [] = [x]
push x (y : ys)
    | x <= y = x : y : ys
    | otherwise = push x ys    

-- popper allows multiple subsequent pops from the stack specification
popper :: Ord a => SStack a -> SStack a
popper xs = ys
    where Just (y, ys) = pop xs

-- push' is a reimplementation of the stack specification with respect to
-- pop.
push' :: Ord a => a -> SStack a -> SStack a
push' x [] = [x]
push' x ys
    | x <= z = x : z : zs
    | otherwise = push' x zs
    where Just (z, zs) =  pop ys

-- popper' allows multiple subsequent pops from the stack, factoring the
-- nothing case

popper' :: Ord a => Maybe (SStack a) -> SStack a
popper' Nothing = []
popper' (Just xs)
    | pop xs == Nothing = []
    | otherwise = pop xs
    
{-- Show that, starting from an empty stack, in any sequence of push and
pop operations each  operation takes (amortized) constant time --}
        
{--
    I have described push in terms of a series of pop operations and a single
    cons operation within the push' function. 
    
    The worst case runtime for this function is O(n) where n is the length of the list.
    This occurs when an item that is larger than any other is inserted into the stack 
    which requires n pop operations, returning a stack with one item - the new item.
        It probably should be explicitly stated that a pop operation has a runtime
        of O(1). It merely removes an item from the top of the stack.
    
    SO, the actual cost of push' is T(n) = T(n-1) + c where c represents a pop
    operation, which is equivelant to 1. Base case is T(0) = 1 - the cons operation
        T(n) = T(n-1) + 1 = (T(n-2) + 1) + 1 = T(n-2) + 2 = ... = T(n-k) + k
        Let k = n,
        T(n-n) + n = T(0) + n = 1 + n
        Making O(n) operations
        
    Let's consider the aggregate method of amortized analysis. Let A(n) represent
    the application of the aggregate method on a list of size n for T in relation to
    the push' function.
        A(n) = T(n) / n = (n + 1) / n = 1 + 1/n
    This better represents the average runtime, relation to n.
    
    If we wanted to make the claim it's constant time, we could ignore the base-case
    operational cost, making T(0) = 0. This would set A(n) = n/n = 1
    
--}

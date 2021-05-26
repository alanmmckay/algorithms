
-- A function which determines the minimum value of a list
minOfList :: [Int] -> Int
minOfList [] = error "No min of empty list"
minOfList (x : xs) = minOfListH xs x

minOfListH :: [Int] -> Int -> Int
minOfListH [] n = n
minOfListH (x : xs) n = min n (min x (minOfListH xs n))
 
-- A function which determines the maximum value of a list
maxOfList :: [Int] -> Int
maxOfList [] = error "No max of empty list"
maxOfList (x : xs) = maxOfListH xs x

maxOfListH :: [Int] -> Int -> Int
maxOfListH [] n = n
maxOfListH (x : xs) n = max n (max x (maxOfListH xs n))
 
-- A function which determines either the minimum or the maxiumum
-- value of a list. Two polar functions.
polarOfList :: (Int -> Int -> Int) -> [Int] -> Int
polarOfList f [] = error "No polar of empty list"
polarOfList f (x : xs) = polarOfListH f xs x

polarOfListH :: (Int -> Int -> Int) -> [Int] -> Int -> Int
polarOfListH f [] n = n
polarOfListH f (x : xs) n = f n (f x (polarOfListH f xs n))

-- A function wich performs a boolean operation on a list of values
apply :: (a -> a -> a) -> [a] -> a
apply f (x : []) = x
apply f (x : xs) = f x (apply f xs)



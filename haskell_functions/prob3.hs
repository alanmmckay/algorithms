--Problem 3 - Alan McKay

type Delta a = [a] -> [a]

cons :: a -> Delta a -> Delta a
-- cons x d = foldr (:) (d [x])
cons x d = \ xs -> x : d xs

nil :: Delta a
-- nil = foldr (:) []
nil = \ xs -> xs

app :: Delta a -> Delta a -> Delta a 
-- app d1 d2 = \ zs -> foldr (:) (d2 zs) (d1 [])
app d1 d2 = \zs -> d1 (d2 (nil zs))

reverse' xs = rev xs []
    where rev [] = nil
          rev (x : xs) = app (rev xs) (cons x nil)
          

{--
    Cons is a function which returns an anonymous function.
    The anonymous function's primary operation is the cons
    operation, which has a constant runtime.
    
    Nils is a function which returns an anonymous function.
    The anonymous function's primary operation is to take
    some list and return the list as new list with a
    type synonym labeled delta.
    
    The cons operation, described above, also returns a
    delta.
    
    Like the previous two functions, app returns an
    anonymous function. It applies it's first delta to
    the second (supplied to app) which is then applied to 
    the input paramter of the anonymous function.
    
    reverse' combines these functions in an order which
    will reverse the list.
    
    Consider the input [1,2,3]
    
    reverse' [1,2,3] = (rev [1,2,3]) []
                     = (app (rev [2.3]) (cons 1 nil)) []
                     = (app (app (rev [3]) (cons 2 nil)) (cons 1 nil)) []
                     = (app (app (app (rev []) (cons 3 nil)) (cons 2 nil)) (cons 1 nil)) []
                     = (app (app (app (nil) (cons 3 nil)) (cons 2 nil)) (cons 1 nil)) []
                     = (app (app (app nil [3]) [2]) [1]) [] --where these lists are deltas
                     = (app (app (\zs -> nil ([3] (nil zs))) [2]) [1]) []
                     = (app (\ys -> (\zs -> nil ([3] (nil zs))) ([2] (nil ys))) [1]) []
                     = (\xs (\ys -> (\zs -> nil ([3] (nil zs))) ([2] (nil ys))) ([1] (nil xs))) []
                     = (\ys -> (\zs -> nil ([3] (nil zs))) ([2] (nil ys))) ([1] (nil []))
                     = (\ys -> (\zs -> nil ([3] (nil zs))) ([2] (nil ys))) [1] //This is a delta
                     = (\zs -> nil ([3] (nil zs))) ([2] (nil [1]))
                     = (\zs -> nil ([3] (nil zs))) [2,1]
                     = nil ([3] (nil [2,1]))
                     = nil [3,2,1]
                     = [3,2,1]
    Recognizing this pattern was key for me to solve the app problem
    
    Let the key operation here be the application of the app function within rev.
    The most costly operation within app is the (:) operation embedded within cons
    which only occurs as many times as it is called - which is equal to the quantity
    in which app is called. (:) has a constant runtime.
    
    T(0) = 0
    T(n) = 1 + T(n-1)
         = 1 + (1 + T(n-2))
         = 2 + T(n-2)
        for some k:
         = k + T(n-k)
        let k = n
         = n + T(n-n) = n
    Thus, this function has a runtime of O(n), where n is the size of the input list.
    
--}

-- ...I much rather prefer to write this function in this manner :^)
reverse'' :: [a] -> [a]
reverse'' xs = reverse''h xs []
reverse''h :: [a] -> [a] -> [a]
reverse''h [] ys = ys
reverse''h (x : xs) ys = reverse''h xs (x : ys)

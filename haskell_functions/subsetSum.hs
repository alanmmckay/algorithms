subsetSum :: [Int] -> Int -> Bool
subsetSum _ 0  = True
subsetSum [] t = False
subsetSum (x : xs) t
    | t < 0 = False
    | otherwise = max (subsetSum xs (t-x)) (subsetSum xs t)
    

lisBigger :: Int -> [Int] -> Int
lisBigger _ [] = 0
lisBigger prev (x : xs)
    | x <= prev = lisBigger prev xs
    | otherwise = max (lisBigger prev xs) ((lisBigger x xs) + 1)

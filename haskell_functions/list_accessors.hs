
index_into_list :: [a] -> Int -> a
index_into_list [] i  = error ("Error: List does not contain index " ++ (show i))
index_into_list (x:xs) i = if i == 0 then x else index_into_list xs (i-1);

-- bool_list_contains :: list -> a -> Bool
bool_list_contains [] item = False
bool_list_contains (x:xs) item = if item == x then True else bool_list_contains xs item;

-- index_of_item :: [a] -> a -> Int
index_of_item [] item = error ("Error: No items exist within an empty list")
index_of_item (x:xs) item = index_of_item_helper (x:xs) item 0;

-- index_of_item_helper :: [a] -> a -> Int -> a
index_of_item_helper [] item i = error ("Error: Supplied list does not contain the following item: " ++ (show item))
index_of_item_helper (x:xs) item i = if item == x then i else index_of_item_helper xs item (i + 1);

first :: [a] -> a
first list = index_into_list list 0
{-
rest :: [a] -> [a]
rest [] = []
rest -}

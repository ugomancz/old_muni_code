--1) S danou instancí Eq platí Fraction 3 6 == Fraction 1 2
--   Typový kontext Integral i lze v definici instance pro Num nahradit kontextem Num i
--   Je možné vytvořit hodnotu Fraction 3.14 42
--   Výraz 5 * Fraction 42 3 se vyhodnotí na Fraction 210 3

--2) map007 f s = foldr (\e r -> f e : r) [] s
--   map16 f s = foldl (\r e -> r ++ [f e]) [] s

--3)
instance Show Prop where
    show (Var x) = x
    show (Not x) = "~" ++ show x
    show (And x y) = "(" ++ show x ++ " & " ++ show y ++ ")"

--4)
"countVotesFor :: String -> [String] -> Int
countVotesFor c xs = foldr (f c) z xs"

z :: Int
z = 0

f :: (Eq a1, Num a2) => a1 -> a1 -> a2 -> a2
f c = (\x y-> if x == c then 1 + y else 0 + y)

--5)
"lawAdopted :: [Vote] -> Bool
lawAdopted xs = g (foldr f z xs)"

z :: Int
z = 0

f :: Num a => Vote -> a -> a
f (Yes) y = 1 + y
f _ y = -1 + y  

g :: (Ord a, Num a) => a -> Bool
g y = y > 0
-- 1)
--zipWith (:)    :: [[a]] -> [[a]] -> [[a]]
--[]             :: [a -> a]
--(map id [not]) :: [Bool -> Bool]

-- 2)

--3)
raiseWith :: Ord a => (a -> a) -> [a] -> [a]
raiseWith f = map (\x -> if (f (x)) > x then (f (x)) else x)

--4)
inSub :: Ord a => [a] -> a -> [a]
inSub [] _ = []
inSub (x:xs) f = if x > f then x : (inSub xs x) else inSub xs f
increasingSubseq :: Ord a => [a] -> [a]
increasingSubseq [] = []
increasingSubseq (x:xs) = x : (inSub (x:xs) x)

--5)
alcont :: (Foldable t1, Eq t2) => t2 -> [t1 t2] -> [Bool]
alcont _ [] = [True]
alcont z (x:xs) = (elem z x) : (alcont z xs)
allContain :: Eq a => a -> [[a]] -> Bool
allContain _ [] = True
allContain z (x:xs) = notElem False (alcont z (x:xs))
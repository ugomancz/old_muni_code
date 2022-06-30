--1) 007, 42

--2)
encrypt :: Eq a => [a] -> [(a,a)] -> [a]
encrypt [] _ = []
encrypt (x:xy) rs = helper x rs : encrypt xy rs

helper :: Eq t => t -> [(t, t)] -> t
helper x [] = x
helper x (r:rs) = if x == fst(r) then snd(r) else helper x rs

--3)
--4)
--5)
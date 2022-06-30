-- #3
--names = [(445763, "Adam Matousek"), (422279, "Jan Mrazek"), (3496, "Jiri Barnat")]
--grades = [(3496, 'F'), (422279, 'B'), (3496, 'F'), (445763, 'A'), (3496, 'E')]

join :: Eq a => [(a, b)] -> [(a, c)] -> [(a, b, c)]
join xs ys  = [(fst x, snd x , snd y) | x <- xs, y <- ys,  fst x == fst y]

-- #4 fakt nevim


-- #5

"data BinTree a = Empty
               | Node a (BinTree a) (BinTree a)
               deriving (Show, Eq)
data Direction = L | R
               deriving (Show, Eq, Ord)

myTree = Node "koren"
              (Node "levy" Empty Empty)
              (Node "vnitrni"
                    (Node "stredni" Empty Empty)
                    (Node "pravy" Empty Empty))"

findInTree :: BinTree a -> [Direction] -> Maybe a
findInTree Empty _ = Nothing
findInTree (Node s l r) [] = Just s
findInTree (Node s l r) (x:xs) = if x == L then findInTree l xs else findInTree r xs
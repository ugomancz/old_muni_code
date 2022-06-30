pwr :: Integer -> [Integer] --vypíše druhé mocniny čísla k v 1,2,3,... až k
pwr k = [ x^2 | x <- [1..k] ]

divisors :: Integer -> [Integer] --vypíše kladné dělitele čísla k
divisors k = [ x | x <- [1..k-1], mod k x == 0]

-- vlastní datové typy

data Day = Mon | Tue | Wed | Thu | Fri | Sat | Sun
         deriving (Show, Eq, Ord)

data Shape = Circle Double
           | Rectangle Double Double
           | Point
           deriving (Eq, Show)

area :: Shape -> Double
area (Circle r) = r^2*pi
area (Rectangle x y) = x*y
area Point = 0

divlist :: Integral a => [a] -> [a] -> [Maybe a]
divlist x y = zipWith (\x y -> if y == 0 then Nothing else Just (div x y) ) x y

data Expr = Con Float
          | Add Expr Expr | Sub Expr Expr
          | Mul Expr Expr | Div Expr Expr

eval :: Expr -> Float
eval (Con x) = x
eval (Add x y) = eval x + eval y
eval (Sub x y) = eval x - eval y
eval (Mul x y) = eval x * eval y
eval (Div x y) = eval x / eval y

-- nasleduje soubor z ISu:

-- Nase definice binarniho stromu
data BinTree a = Empty
               | Node a (BinTree a) (BinTree a)
               deriving (Show, Eq, Ord)

-- Testovací stromy pro některé úkoly.

tree01 :: BinTree Int
tree01 = Node 4 (Node 2 (Node 1 Empty Empty) (Node 3 Empty Empty))
                (Node 6 (Node 5 Empty Empty) (Node 7 Empty Empty))

tree02 :: BinTree Int
tree02 = Node 9 Empty (Node 10 Empty (Node 11 Empty (Node 12 Empty Empty)))

tree03 :: BinTree Int
tree03 = Node 8 tree01 tree02

tree04 :: BinTree Int
tree04 = Node 4 (Node 2 Empty (Node 3 Empty Empty))
                (Node 6 (Node 5 Empty Empty) Empty)

tree05 :: BinTree Int
tree05 = Node 100 (Node 101 Empty (Node 102 (Node 103 Empty (Node 104 Empty Empty)) Empty))
                  (Node 99 (Node 98 Empty Empty) (Node 98 Empty Empty))

tree06 :: BinTree Int
tree06 = Node 66 Empty Empty

tree07 :: BinTree Int
tree07 = Node 7567 (Node 5555 Empty Empty) Empty

forest :: [BinTree Int]
forest = [Empty, tree01, tree02, tree03, tree04, tree05, tree06, tree07]

-- vlastni funkce zalozene na souboru z ISu

treeSize :: BinTree a -> Integer -- vrati pocet listu
treeSize Empty = 0
treeSize (Node x l r) = 1 + (treeSize l) + (treeSize r)

listTree :: BinTree a -> [a] -- vrati seznam hodnot listu
listTree Empty = []
listTree (Node x l r) = [x] ++ (listTree l) ++ (listTree r)

longestPath :: BinTree a -> [a] -- vrati seznam hodnot, pres ktere prochazi nejdelsi cesta stromem
longestPath Empty = []
longestPath (Node x l r) = x : if (length lpL > length lpR) then lpL else lpR where lpL = longestPath l
                                                                                    lpR = longestPath r

fullTree :: Int -> a -> BinTree a -- po volani fulltree n v vytvori binarni strom vysky n, ve kterem jsou vsechny vetve stejne dlouhe a vsechny uzly maji hodnotu v
fullTree n v = if n > 1 then Node v (fullTree (n-1) v) (fullTree (n-1) v) else Node v Empty Empty

treeZip :: BinTree a -> BinTree b -> BinTree (a,b) -- hodnoty uzlu se spoji do usporadanych dvojic
treeZip Empty _ = Empty
treeZip _ Empty = Empty
treeZip (Node x1 l1 r1) (Node x2 l2 r2) = Node (x1,x2) (treeZip l1 l2) (treeZip r1 r2)

treeRepeat :: a -> BinTree a
treeRepeat v = Node v (treeRepeat v) (treeRepeat v)

nilTree = treeRepeat []

treeIterate :: (a -> a) -> (a -> a) -> a -> BinTree a
treeIterate f1 f2 v = Node v (treeIterate f1 f2 (f1 v)) (treeIterate f1 f2 (f2 v))

data Shape = Circle Double
           | Rectangle Double Double
           | Point
           deriving (Show)

isEqual :: Shape -> Shape -> Bool
isEqual (Circle x) (Circle y) = x == y
isEqual (Rectangle x y) (Rectangle a b) = x == a && y == b
isEqual (Point) (Point) = True
isEqual _ _ = False

data TrafficLight = Red | Orange | Green
                  deriving (Show)

instance Eq TrafficLight where
  Red == Red = True
  Orange == Orange = True
  Green == Green = True
  _ == _ = False

instance Ord TrafficLight where
  _ <= Red = True
  Green <= _ = True
  Orange <= Orange = True
  _ <= _ = False

data PairT a b = PairV a b

instance (Show a, Show b) => Show (PairT a b) where
  show (PairV a b) = "a pair of " ++ show a ++ " and " ++ show b

producto :: [Int] -> Int
producto [] = 1
producto xs = head xs * product (tail xs)

lengtho :: [a] -> Int
lenghto [] = 0
lengtho xs = 1 + lengtho (tail xs)

mapo :: (a -> b) -> [a] -> [b]
mapo _ [] = []
mapo f xs = f (head xs) : mapo f (tail xs)

abstraction b f [] = b
abstraction b f (x:xs) = f x (abstraction b f xs)

producto2 = abstraction 1 (*)
lengtho2 = abstraction 0 (\x y -> 1 + y)
mapo2 f = abstraction [] (\x y -> f x : y)

sumFold :: Num a => [a] -> a
sumFold = foldr (+) 0

productFold :: Num a => [a] -> a
productFold = foldr (*) 1

orFold :: [Bool] -> Bool
orFold = foldr (||) False

andFold :: [Bool] -> Bool
andFold = foldr (&&) True

lengthFold :: [a] -> Int
lengthFold = foldr (\x y -> 1 + y) 0

minimumFold :: Ord a => [a] -> a
minimumFold = foldr1 min

maximumFold :: Ord a => [a] -> a
maximumFold = foldr1 max

maxminFold :: Ord a => [a] -> (a,a)
maxminFold x = (maximumFold x,minimumFold x)

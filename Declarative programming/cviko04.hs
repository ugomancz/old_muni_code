longStringInitials :: [String] -> [Char]
longStringInitials [] = []
longStringInitials x = map head (filter (\x -> (length x) >= 5) x)

myzip :: [a] -> [b] -> [(a,b)]
myzip [] _ = []
myzip _ [] = []
myzip (x:s) (y:t) = (x,y) : zip s t

connectEven :: Integral b => [a] -> [b] -> [(a,b)]
connectEven [] _ = []
connectEven _ [] = []
connectEven xy ts = filter (\(x,t) -> even t) (myzip xy ts)

naturals = natural 1
natural x = [x] ++ natural (x+1)

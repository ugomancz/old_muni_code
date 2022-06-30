circleArea x = pi * 2 * x
isSucc n1 n2 = (n1 + 1) == n2
max3 x y z = max x (max y z)
mid x y z = x + y + z - (max3 x y z) - (min x (min y z))
tell x = if x == 1 then "one" else if x == 2 then "two" else if mod x 2 == 0 then "(even)" else "(odd)"
isSmallVowel a = elem a "aeiouy"
factorial x = if x == 1 then 1 else factorial (x-1) * x
mod3 x = if x == 0 then 0 else if x == 1 then 1 else if x == 2 then 2 else mod3 (x-3)
power z n = if n<0 then 0 else z ** n
two x = if x < 1 then False else if x == 1 then True else two (x/2)

dfct x = if x == 0 then 1 else if mod x 2 == 0 then dfcteven x else dfctodd x
dfcteven x = if x == 0 then 1 else 2 * x * dfcteven (x-1)
dfctodd x = if x == 0 then 1 else (2 * x + 1) * dfctodd (x-1)

linear :: Fractional a => a -> a -> a
linear a b = (-b) / a

cube :: Double -> Double
cube = (**3)

filterlist :: Eq a => a -> [a] -> [a]
filterlist _ [] = []
filterlist a (x:xs) = if x == a then filterlist a xs else x : filterlist a xs
--filterlist a (x:xs) = [x | x <- (x:xs), x /= a]

oddlength [] = False
oddlength [_] = True
oddlength (x:y:xs) = oddlength xs

listsum [] = 0
listsum (x:xs) = x + listsum xs

listsequal a b = notElem False (listsequalh a b)
listsequalh [] [] = []
listsequalh (x:xs) (y:ys) = if x == y then True : listsequalh (xs) (ys) else False : listsequalh (xs) (ys)

getlast [x] = x
getlast (x:xs) = getlast (xs)

striplast [_] = []
striplast (x:xs) = x : striplast xs

elem' :: Eq a => a -> [a] -> Bool
elem' _ [] = False
elem' a (x:xs) = if a == x then True else elem' a (xs)

doubles (x:z:xs) = (x,z) : doubles (xs)
doubles _ = []

sums :: [[Integer]] -> [Integer]
sums (x:xs) = map (foldr (+) 0) (x:xs)

applytolist :: (a -> b) -> [a] -> [b]
applytolist _ [] = []
applytolist f (x:xs) = f (x) : applytolist f xs

evens :: [Integer] -> [Integer]
evens [] = []
evens (x:xs) = if mod x 2 == 0 then x : evens xs else evens xs
--evens xs = [x | x <- xs, mod x 2 == 0]

multiplyeven :: [Integer] -> [Integer]
multiplyeven xs = map (*2) (evens xs)

sqroots :: [Double] -> [Double]
sqroots xs = map (sqrt) (filter (>0) xs)

fromend :: Int -> [Int] -> Int
fromend 1 xs = last(xs)
fromend a xs = if a > length(xs) then error "cant do" else fromend (a-1) (init(xs))

maxima :: [[Int]] -> [Int]
maxima xs = map maximum xs

isvowel x = elem x "aeiouyAEIOUY"
vowelsin [] = []
vowelsin (x:xs) = if isvowel x == True then x : vowelsin xs else vowelsin xs
vowels [] = []
vowels (x:xs) = vowelsin x : vowels xs

myzip2 x y = zipWith (,) x y

data Day = Mon | Tue | Wed | Thu | Fri | Sat | Sun
         deriving (Show, Eq, Ord)

weekend :: Day -> Bool
weekend x = x == Sat || x == Sun

data Jar = EmptyJar | Jam String | Cucumbers | Compote Int

today = 2018

stale :: Jar -> Bool
stale (Compote x) = (today - x) > 10
stale _ = error "already eaten"

data Teleso = Kvadr Float Float Float -- a,b,c
            | Valec Float Float -- r,v
            | Kuzel Float Float -- r,v
            | Koule Float -- r

objem (Kvadr a b c) = a*b*c
objem (Valec r v) = pi*r*r*v
objem (Kuzel r v) = 1/3*pi*r*r*v
objem (Koule r) = 4/3*pi*r*r*r
povrch (Koule r) = 4*pi*r*r
povrch (Kuzel r v) = (pi*r*r) + (pi*r*(sqrt(r*r + v*v)))
povrch (Valec r v) = 2*pi*r*r + 2*pi*r*v
povrch (Kvadr a b c) = 2*a*b + 2*a*c + 2*b*c

data Point = P Int Int
           deriving(Show)
data LPicture = Line Point Point | Comp LPicture LPicture
              deriving(Show)

addtox :: Int -> LPicture -> LPicture
addtox a (Line (P x y) (P w z)) = (Line (P (x+a) y) (P (w+a) z))
addtox a (Comp l r) = (Comp (addtox a l) (addtox a r))

mydrop :: Int -> [a] -> [a]
mydrop 0 xz = xz
mydrop _ [] = []
mydrop x xs = mydrop (x-1) (tail(xs))

-- zkouška 17.1.2018

myzip :: [a] -> [b] -> [(a,b)]
myzip _ [] = []
myzip [] _ = []
myzip (x:xy) (y:yz) = (x,y) : myzip xy yz

flipxy :: LPicture -> LPicture
flipxy (Line (P x y) (P w z)) = Line (P y x) (P z w)
flipxy (Comp l r) = (Comp (flipxy l) (flipxy r))

myfilter _ [] = []
myfilter g (x:xs) = if g(x) == True then x : myfilter g xs else myfilter g xs

myconcat :: [[a]] -> [a]
myconcat [] = []
myconcat (x:xs) = x ++ myconcat xs

foo :: [[Integer]] -> [[Integer]]
foo xs = map tail xs

myall :: (a ->  Bool) -> [a] -> Bool
myall f xs = notElem False (myhelp f xs)
myhelp :: (a -> Bool) -> [a] -> [Bool]
myhelp _ [] = []
myhelp f (x:xs) = if f(x) then True : myhelp f xs else False : myhelp f xs
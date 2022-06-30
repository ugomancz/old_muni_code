import Data.Char

help (x,y) = x
done (x,y) = y


--takeEvenelements (x:xs) = if mod (help x) 2 == 0 then [done x] ++ takeEvenElements xs else takeEvenElements xs

-- vyberte ze seznamu sudá čísla s využitím lambda abstrakce

evens :: [Integer] -> [Integer]
evens x = filter (\x -> mod x 2 ==0) x


-- převeďte string s malými písmeny na velké s využitím lambda abstrakce

toUpperStr :: String -> String
toUpperStr xs = map (\x -> toUpper x) xs


mymin6 x = if x<6 then x else 6

-- sude prvky ze seznamu zvetsi o jedna
addOneOrNothing :: Integral a => [a] -> [a]
addOneOrNothing xs = map (\x -> if (mod x 2) == 0 then x+1 else x) xs

-- ponecha v seznamu pouze prvky delitelne 3
justDivisibleBy3 :: Integral a => [a] -> [a]
justDivisibleBy3 xs = filter (\x -> mod x 3 == 0) xs

--vrati soucty vsech seznamu, ktere obsahuje jen prvky vetsi nez 5
--sumOfLists :: (Num a, Ord a) => [[a]] -> [a]
--sumOfLists xs = +

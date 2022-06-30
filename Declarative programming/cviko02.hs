--Napište program, který vypíše seznam čísel 1 až 1024 pomocí rekurze

numlist x = if x==1 then [1] else (numlist (x-1)) ++ [x]


--Napište rekurzivní funkci divBy3, která celočíselně
--vydělí zadaný argument číslem 3 bez použití funkce div

divBy3 0 = 0
divBy3 1 = 0
divBy3 2 = 0
divBy3 n = 1 + (divBy3 (n-3))


-- definujte funkci myhead :: [a] -> a, která vrátí první prvek seznamu

myhead :: [a] -> a
myhead [] = error "prazdny seznam"
myhead (x:xs) = x

mytail :: [a] -> [a]
mytail [] = error "prazdny seznam"
mytail (x:xs) = xs


oddLength :: [a] -> Bool
oddLength [] = False
oddLength [_] = True
oddLength (x:y:xs) = oddLength xs


-- funkce pro výpočet počtu kořenů kvadratické rovnice; let->in

numRoots :: Int -> Int -> Int -> Int
numRoots a b c = let disk = b ^ 2 - 4 * a * c in
		 if disk < 0
		 then 0
		 else if disk == 0
		 then 1 else 2


--definujte funkci, která ze seznamu vybere sudá čísla pomocí filter

evens :: [Integer] -> [Integer]
evens (x:xs) = filter even (x:xs)


--definujte funkci, která převede řetězec malých písmen na řetězec velkých písmen

--toUpperStr :: String -> String
--toUpperStr xs = map toUpper xs


-- funkce ktera vybere suda cisla ze seznamu a vynasobi je 2x
multiplyEven :: [Integer] -> [Integer]
multiplyEven xs = map (2*) (filter even xs)

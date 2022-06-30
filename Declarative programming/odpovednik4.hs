type Bitvec = String

toBitvec :: String -> Bitvec
toBitvec x = x

fromBitvec :: Bitvec -> String
fromBitvec x = x

bvnot :: Bitvec -> Bitvec
bvnot x = map (\x -> if x == '0' then '1' else '0') x

bvand :: Bitvec -> Bitvec -> Bitvec -- s využitím funkce resize první upravíme oba řetězce na shodnou délku a zavoláme funkci znovu s upravenými řetězci, poté už jen jednoduchou funkcí rekurzivně porovnáváme prvky řetězců
bvand (x:xy) (r:rs) = let lr = length (r:rs)
                          lx = length (x:xy)
                      in if lx > lr then (bvand (x:xy) (resize lx (r:rs))) else if lx < lr then (bvand (resize lr (x:xy)) (r:rs)) else if x == '1' && r == '1' then "1" ++ bvand xy rs else "0" ++ bvand xy rs
bvand "" "" = ""
bvand [] rs = bvand (resize (length rs) "") rs
bvand xy [] = bvand xy (resize (length xy) "")


bvor :: Bitvec -> Bitvec -> Bitvec -- s využitím funkce resize první upravíme oba řetězce na shodnou délku a zavoláme funkci znovu s upravenými řetězci, poté už jen jednoduchou funkcí rekurzivně porovnáváme prvky řetězců
bvor (x:xy) (r:rs) = let lr = length (r:rs)
                         lx = length (x:xy)
                     in if lx > lr then (bvor (x:xy) (resize lx (r:rs))) else if lx < lr then (bvor (resize lr (x:xy)) (r:rs)) else if x == '1' || r == '1' then "1" ++ bvor xy rs else "0" ++ bvor xy rs
bvor "" "" = ""
bvor [] rs = bvor (resize (length rs) "") rs
bvor xy [] = bvor xy (resize (length xy) "")

bvxor :: Bitvec -> Bitvec -> Bitvec -- s využitím funkce resize první upravíme oba řetězce na shodnou délku a zavoláme funkci znovu s upravenými řetězci, poté už jen jednoduchou funkcí rekurzivně porovnáváme prvky řetězců
bvxor (x:xy) (r:rs) = let lr = length (r:rs)
                          lx = length (x:xy)
                      in if lx > lr then (bvxor (x:xy) (resize lx (r:rs))) else if lx < lr then (bvxor (resize lr (x:xy)) (r:rs)) else if x /= r then "1" ++ bvxor xy rs else "0" ++ bvxor xy rs
bvxor "" "" = ""
bvxor [] rs = bvxor (resize (length rs) "") rs
bvxor xy [] = bvxor xy (resize (length xy) "")

resize :: Int -> Bitvec -> Bitvec -- porovná zadanou a požadovanou délku řetězce a upraví ho buď přidáním 0 na začátek, za pomoci funkce zero, nebo ubíráním bitů nejvyššího řádu
resize x "" = zero x
resize x (s:sd) = let l = length (s:sd) in if l < x then (zero (x-l)) ++ (s:sd) else if l > x then resize x sd else (s:sd)

zero :: Int -> Bitvec -- rekurzivně vygeneruje řetězec o zadaném počtu nul
zero x = if x /= 0 then "0" ++ (zero (x-1)) else ""

rotRight :: Int -> Bitvec -> Bitvec -- rekurzivně přesouvá poslední prvek řetězce na začátek
rotRight _ "" = ""
rotRight r xs = if r == 0 then xs else rotRight (r-1) ([(last xs)] ++ (init xs))

rotLeft :: Int -> Bitvec -> Bitvec -- rekurzivně přesouvá první prvek řetězce na konec
rotLeft _ "" = ""
rotLeft r xs = if r == 0 then xs else rotLeft (r-1) ((tail xs) ++ [(head xs)])

shiftRight :: Int -> Bitvec -> Bitvec -- rozhodne o správném směru posunu, funguje tedy i pro záporné r, v tom případě zavolá funkci shiftLeft; pokud je r větší než délka řetězce r, pak pouze vygeneruje řetězec nul o stejné délce, jako měl původní řetězec, za využití funkce zero. Pokud je řetězec delší než žádaný bitový posun, pak rekurzivně přidává na začátek řetězce nulu a zároveň maže poslední prvek řetězce
shiftRight r xs = let l = length xs in if r < 0 then shiftLeft (negate r) xs else if l < r then zero l else if r == 0 then xs else "0" ++ shiftRight (r-1) (init xs)

shiftLeft :: Int -> Bitvec -> Bitvec -- rozhodne o správném směru posunu, funguje tedy i pro záporné r, v tom případě zavolá funkci shiftRight; pokud je r větší než délka řetězce r, pak pouze vygeneruje řetězec nul o stejné délce, jako měl původní řetězec, za využití funkce zero. Pokud je řetězec delší než žádaný bitový posun, pak rekurzivně maže první prvek řetězce a zároveň přidává na konec řetězce nulu
shiftLeft r xs = let l = length xs in if r < 0 then shiftRight (negate r) xs else if l < r then zero l else if r == 0 then xs else shiftLeft (r-1) (tail xs) ++ "0"

add :: Bitvec -> Bitvec -> Bitvec -- upravi delku retezce a zavola pomocnou funkci addhelp
add "" y = y
add x "" = x
add x y = let lx = length x
              ly = length y
              in if ly > lx then (add (resize ly x) y) else if ly < lx then (add x (resize lx y)) else addhelp x y 0

addhelp :: Bitvec -> Bitvec -> Int -> Bitvec -- přidaná proměnná f značí hodnotu přenosu po sečtení bitů; funkce porovná bity na daném indexu a rozhodne, jaký je jejich součet a bitový přenos
addhelp "" _ _ = ""
addhelp _ "" _ = ""
addhelp x y 0 = let tx = last x
                    ty = last y
                    ix = init x
                    iy = init y
                in if tx == '0' && ty == '0' then (addhelp ix iy 0) ++ "0" else if (tx /= ty) then (addhelp ix iy 0) ++ "1" else (addhelp ix iy 1) ++ "0"
addhelp x y 1 = let tx = last x
                    ty = last y
                    ix = init x
                    iy = init y
                in if tx == '0' && ty == '0' then (addhelp ix iy 0) ++ "1" else if (tx /= ty) then (addhelp ix iy 1) ++ "0" else (addhelp ix iy 1) ++ "1"
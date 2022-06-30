#	nacteme knihovnu "prob"
library (prob)

# Priklad 1 
# s ciselnymi hodnotami 
n <- 4

mince <- tosscoin (n)
# vytvoril se tzv. data.frame = datova tabulka (matice) s pojmenovanymi sloupci
mince
# rozmery 
dim (mince)
nrow (mince)
ncol (mince)
# nazvy sloupcu (promennych)
names (mince)
# nazvy lze menit, napr. 
names (mince) <- c ("prvni", "druha", "treti","ctvrta")
mince
# krome klasickeho indexovani pomoci hranatych zavorek se lze na sloupce odkazovat i nazvem: promenna$nazev
mince$prvni
mince$treti
# struktura promenne
str (mince)
# vidime, ze vysledky jsou H = head a T = tail
# jedna se o tzv. faktory
# interne je ulozena ciselna hodnota, cislo je ale pouze kodem, nema vyznam ciselne hopdnoty
as.numeric (mince$treti)

# vytvorime pravdepodobnostni prostor
S <- probspace (mince)

# podivame se na vysledek
S
str (S)
names (S)
#names (S) <- c ("prvni","druha","treti","ctvrta","sance")
# jde opet o datovou tabulku, na kazdem radku je jeden elementarni jev, pribyl sloupec s pravdepodobnosti


# velikost zakladniho prostoru Omega
nrow (S)


# jev A = padnou same lice = heads = H
A <- subset (S, isin (S, rep ("H", n)))
A

nrow (A)
nrow (A) / nrow (S)

Prob (A)



# jev Bk = padne prave k licu, tzn. k krat H a (n-k) krat T
B0 <- subset (S, isin (S, rep ("T", 4)))
B1 <- subset (S, isin (S, c ("H", "T", "T", "T")))
B2 <- subset (S, isin (S, c ("H", "H", "T", "T")))
B3 <- subset (S, isin (S, c ("H", "H", "H", "T")))
B4 <- A

B0
B1
B2
B3
B4

Prob (B0)
Prob (B1)
Prob (B2)
Prob (B3)
Prob (B4)

psti <- c (Prob (B0), Prob (B1), Prob (B2), Prob (B3), Prob (B4))

# zkontrolujeme soucet
sum (psti)

  # vykreslime sloupcovy graf
names (psti) <- seq (0, 4, by = 1)
barplot (psti, xlab = "pocet licu", ylab = "pravdepodobnost")



# Dalsi ukoly k samostatnemu vyreseni (na cvicenich anebo domaci ukol): 

# Opakujte ulohu pro vetsi pocet hodu n 

# Urcete mnoziny elementarnich jevu priznivych nasledujicim jevum a jejich pravdepodobnosti: 
# jev Ck = padne alespon k licu
# jev Dk = padne nejvyse k licu
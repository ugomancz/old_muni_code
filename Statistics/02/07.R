# library (prob)

# Priklad 7

kostky <- rolldie (3)

S <- probspace (kostky)

# budou se nam hodit soucty i souciny hozenych cisel, pridame je 
S1 <- S
S1$soucet <- apply (kostky, 1, sum)
S1$soucin <- apply (kostky, 1, prod)

# (a), (b)

tab.soucet <- table (S1$soucet)
psti.soucet <- tab.soucet / nrow (S1)
psti.soucet
barplot (psti.soucet)

# mj. vidime, ze hodit soucet 11 je vice pravdepodobne, ne zhodit soucet 12

# (c)

C <- subset (S, isin (S, rep (6, 3)))
C
Prob (C)
nrow (C) / nrow (S)

# (d)

D <- subset (S, isin (S, rep (6, 2)))
D
Prob (D)
nrow (D) / nrow (S)

# (e)

E1 <- subset (S, isin (S, 1))
E3 <- subset (S, isin (S, 3))
E5 <- subset (S, isin (S, 5))
E135 <- union (union (E1, E3), E5)
E <- setdiff (S, E135)
E
Prob (E)

# (f)

F <- subset (S, isin (S, c (1, 2, 3)))
F
Prob (F)
nrow (F)
factorial (3)

# (g) 

# vybirame ty elementarni jevy, pro nez dava soucin po deleni 3 zbytek 0
G <- subset (S1, S1$soucin %% 3 == 0)
Prob (G)

# muzeme se podivat i na sloupcovy graf pro souciny delitelne 3 
G.tab.soucin <- table (G$soucin)
G.psti.soucin <- G.tab.soucin / nrow (S1)
G.psti.soucin
barplot (G.psti.soucin)
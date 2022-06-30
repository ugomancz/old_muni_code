library (prob)

#	Priklad 1

kostky <- rolldie (2)
S <- probspace (kostky)

# A = 2 petky
# B = soucet delitelny peti

A <- subset (S, X1 == 5 & X2 == 5)
B <- subset (S, (X1 + X2) %% 5 == 0)
AB <- intersect (A, B)
Prob (AB) / Prob (B)

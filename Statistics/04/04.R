# Priklad 4

lambda <- 4
#	mozne hodnoty x jsou vsechna prirozena cisla, 
#	horni mez sekvence hodnot x v R je tak nutno patricne upravit 
x <- seq (0, 10)
titulek <- "Poissonovo rozdeleni"

# pravdepodobnostni funkce
pravdepodobnostni <- dpois (x, lambda = lambda)

#	sloupcovy graf
barplot (pravdepodobnostni, col = rainbow (length (x)), names.arg = x, ylab = "pravdepodobnostni funkce", main = titulek)

#	klasicky bodovy (korektne matematicky) graf
plot (x, pravdepodobnostni, type = "h", col = "red", ylab = "pravdepodobnostni funkce", main = titulek)
points (x, pravdepodobnostni, pch = 16, cex = 0.5, col = "red")

# distribucni funkce
distribucni <- ppois (x, lambda = lambda)
# jedna se o skokovou funkci
dist.fce <- stepfun (x, c (0, distribucni))

# distribucni funkce je vzdy zprava spojita, 
# tzn. leve krajni body vzdy patri k useckam
plot (dist.fce, verticals = FALSE, col = "red", pch = 16, cex = 0.5, ylab = "distribucni funkce", main = titulek)

# (A)
dpois(0,lambda)

# (B)
ppois(4,lambda)

# (C)
1 - dpois(0,lambda)

# (D)
ppois(6, lambda) - ppois(1,lambda)

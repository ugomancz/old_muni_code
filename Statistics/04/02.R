# Priklad 2

n <- 20
theta <- 1/6

x <- seq (0, n)
titulek <- paste ("binomicke rozdeleni,", "n =", n)

# pravdepodobnostni funkce
pravdepodobnostni <- dbinom (x, size = n, prob = theta)

#	sloupcovy graf
barplot (pravdepodobnostni, col = rainbow (length (x)), names.arg = x, ylab = "pravdepodobnostni funkce", main = titulek)

#	klasicky bodovy (korektne matematicky) graf
plot (x, pravdepodobnostni, type = "h", col = "red", ylab = "pravdepodobnostni funkce", main = titulek)
points (x, pravdepodobnostni, pch = 16, cex = 0.5, col = "red")

# distribucni funkce
distribucni <- pbinom (x, size = n, prob = theta)
# jedna se o skokovou funkci
dist.fce <- stepfun (x, c (0, distribucni))

# distribucni funkce je vzdy zprava spojita, 
# tzn. leve krajni body vzdy patri k useckam
plot (dist.fce, verticals = FALSE, col = "red", pch = 16, cex = 0.5, ylab = "distribucni funkce", main = titulek)

# (A)
dbinom(5,n,theta)

# (B) 
pbinom(4,n,theta)

# (C)
1 - pbinom(5,n,theta)

#	(D)
# ...

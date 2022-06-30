# Priklad 8 

# Porovnani grafu pro nekolik hodnot parametru a

mu <- 2
titulek <- "porovnani Gamma (Erlangova) rozdeleni"

hustota1 <- dgamma (x, shape = 1, scale = mu)
hustota2 <- dgamma (x, shape = 2, scale = mu)
hustota3 <- dgamma (x, shape = 3, scale = mu)
hustota4 <- dgamma (x, shape = 6, scale = mu)

plot (x, hustota1, type = "l", col = "#FF0000", lwd = 3, ylab = "hustoty pravdepodobnosti", main = titulek)
lines (x, hustota2, col = "#009900", lwd = 3)
lines (x, hustota3, col = "#0000FF", lwd = 3)
lines (x, hustota4, col = "#FFCC00", lwd = 3)

distribucni1 <- pgamma (x, shape = 1, scale = mu)
distribucni2 <- pgamma (x, shape = 2, scale = mu)
distribucni3 <- pgamma (x, shape = 3, scale = mu)
distribucni4 <- pgamma (x, shape = 6, scale = mu)

plot (x, distribucni1, type = "l", col = "#FF0000", lwd = 3, ylab = "distribucni funkce", main = titulek)
lines (x, distribucni2, col = "#009900", lwd = 3)
lines (x, distribucni3, col = "#0000FF", lwd = 3)
lines (x, distribucni4, col = "#FFCC00", lwd = 3)

#	=======================================================================

# Porovnani grafu pro nekolik hodnot parametru mu

a <- 2
titulek <- "porovnani Gamma (Erlangova) rozdeleni"

hustota1 <- dgamma (x, shape = a, scale = 0.5)
hustota2 <- dgamma (x, shape = a, scale = 1)
hustota3 <- dgamma (x, shape = a, scale = 2)
hustota4 <- dgamma (x, shape = a, scale = 3)

plot (x, hustota1, type = "l", col = "#FF0000", lwd = 3, ylab = "hustoty pravdepodobnosti", main = titulek)
lines (x, hustota2, col = "#009900", lwd = 3)
lines (x, hustota3, col = "#0000FF", lwd = 3)
lines (x, hustota4, col = "#FFCC00", lwd = 3)

distribucni1 <- pgamma (x, shape = a, scale = 0.5)
distribucni2 <- pgamma (x, shape = a, scale = 1)
distribucni3 <- pgamma (x, shape = a, scale = 2)
distribucni4 <- pgamma (x, shape = a, scale = 3)

plot (x, distribucni1, type = "l", col = "#FF0000", lwd = 3, ylab = "distribucni funkce", main = titulek)
lines (x, distribucni2, col = "#009900", lwd = 3)
lines (x, distribucni3, col = "#0000FF", lwd = 3)
lines (x, distribucni4, col = "#FFCC00", lwd = 3)

# ==================================================================== 

# Analogicky zkoumejte totez pro normalni rozdeleni a parametry "mean" a "sd"


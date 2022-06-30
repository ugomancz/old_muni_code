# Priklad 7

mu <- 40
sigma <- 4

# konce intervalu hodnot x nutno vhodne upravovat
x <- seq (25, 55, by = 0.01)
titulek <- paste ("Normalni (Gaussovo) rozdeleni, ", "mu =", mu, ", sigma = ", sigma)

# hustota pravdepodobnosti 
# POZOR! Matematicky znacime N (mu, sigma^2) 
# ale v R se zadava (mu, sigma)
hustota <- dnorm (x, mean = mu, sd = sigma)

#	hustotu graficky zobrazujeme jako krivku
plot (x, hustota, type = "l", col = "blue", lwd = 3, ylab = "hustota pravdepodobnosti", main = titulek)

polygon (c(min (x), x, max(x)), c(0, hustota, 0), col = "#CCFFCC")

# distribucni funkce je spojita, 
#	graficky ji zobrazujeme jako krivku
distribucni <- pnorm (x, mean = mu, sd = sigma)
plot (x, distribucni, type = "l", col = "blue", lwd = 3, ylab = "distribucni funkce", main = titulek)

#	=======================================================================

# Porovnani grafu pro nekolik hodnot parametru mu a sigma

titulek <- "porovnani normalnich rozdeleni"
x <- seq (-5, 55, by = 0.01)

hustota1 <- dnorm (x, mean = 40, sd = 4)
hustota2 <- dnorm (x, mean = 40, sd = 5)
hustota3 <- dnorm (x, mean = 40, sd = 1)
hustota4 <- dnorm (x, mean = 0, sd = 1)
# hustota4 odpovida standardizovanemu normalnimu rozdeleni pravdepodobnosti

plot (x, hustota1, type = "l", col = "blue", lwd = 3, ylab = "hustoty pravdepodobnosti", main = titulek, xlim = c (-5, 55), ylim = c (0, 0.45))
lines (x, hustota2, col = "green", lwd = 3)
lines (x, hustota3, col = "red", lwd = 3)
lines (x, hustota4, col = "black", lwd = 3)

distribucni1 <- pnorm (x, mean = 40, sd = 4)
distribucni2 <- pnorm (x, mean = 40, sd = 5)
distribucni3 <- pnorm (x, mean = 40, sd = 1)
distribucni4 <- pnorm (x, mean = 0, sd = 1)

plot (x, distribucni1, type = "l", col = "blue", lwd = 3, ylab = "distribucni funkce", main = titulek, xlim = c (-5, 55))
lines (x, distribucni2, col = "green", lwd = 3)
lines (x, distribucni3, col = "red", lwd = 3)
lines (x, distribucni4, col = "black", lwd = 3)



# =====================================================================
mu <- 40
sigma <- 4
x <- seq (25, 55, by = 0.01)
hustota <- dnorm (x, mean = mu, sd = sigma)
distribucni <- pnorm (x, mean = mu, sd = sigma)

# (A) 
plot (x, hustota, type = "l", col = "blue", lwd = 3, ylab = "hustota pravdepodobnosti")
indexy <- which (x <= 50)
polygon (x[c(min(indexy), indexy, max(indexy))], c(0, hustota[indexy], 0), col = "#FFCC00")

pnorm (50, mean = mu, sd = sigma)
# standardizace U = (X - mu) / sigma
U <- (50 - mu) / sigma
pnorm (U)

# (B) 
plot (x, hustota, type = "l", col = "blue", lwd = 3, ylab = "hustota pravdepodobnosti")
indexy <- which (x > 35)
polygon (x[c(min(indexy), indexy, max(indexy))], c(0, hustota[indexy], 0), col = "#FFCC00")

1 - pnorm (35, mean = mu, sd = sigma)
# standardizace U = (X - mu) / sigma
U <- (35 - mu) / sigma
1 - pnorm (U)

# (C) 
plot (x, hustota, type = "l", col = "blue", lwd = 3, ylab = "hustota pravdepodobnosti")
indexy <- which ((x > 35) & (x < 45))
polygon (x[c(min(indexy), indexy, max(indexy))], c(0, hustota[indexy], 0), col = "#FFCC00")

pnorm (45, mean = mu, sd = sigma) - pnorm (35, mean = mu, sd = sigma)
# standardizace U = (X - mu) / sigma
pnorm ((45 - mu) / sigma) - pnorm ((35 - mu) / sigma)

# (D) 
plot (x, hustota, type = "l", col = "blue", lwd = 3, ylab = "hustota pravdepodobnosti")
indexy <- which ((x > mu - 1.96 * sigma) & (x < mu + 1.96 * sigma))
polygon (x[c(min(indexy), indexy, max(indexy))], c(0, hustota[indexy], 0), col = "#FFCC00")

pnorm (mu + 1.96 * sigma, mean = mu, sd = sigma) - pnorm (mu - 1.96 * sigma, mean = mu, sd = sigma)
# standardizace U = (X - mu) / sigma
pnorm (1.96) - pnorm (-1.96)


# Priklad 5

a <- 0
b <- 10

x <- seq (a-10, b+10, by = 0.01)
titulek <- "rovnomerne spojite rozdeleni"

# hustota pravdepodobnosti
hustota <- dunif (x, a, b)

#	hustotu graficky zobrazujeme jako krivku
plot (x, hustota, type = "l", col = "blue", lwd = 2, ylab = "hustota pravdepodobnosti", main = titulek)

# pravdepodobnost je dana plochou pod grafem hustoty pravdepodobnosti
# v R se ploch kresli jako vybarveny mnohouhelnik
polygon (c(min (x), x, max(x)), c(0, hustota, 0), col = "#CCFFCC")

# dokazeme zvyraznit i plochu pod krivkou v zadanem intervalu, 
# napr. v rozmezi od 3 do 8, vyuzijeme pritom funkci "which"
indexy <- which ((x >= 3) & (x <= 8))
polygon (x[c(min(indexy), indexy, max(indexy))], c(0, hustota[indexy], 0), col = "#FFCC00")

# distribucni funkce je spojita, 
#	graficky ji zobrazujeme jako krivku
distribucni <- punif (x, a, b)
plot (x, distribucni, type = "l", col = "blue", lwd = 2, ylab = "distribucni funkce", main = titulek)

# A
dunif(2,a,b)

# B
punif(5,a,b)

# C
1 - punif(1,a,b)

# D

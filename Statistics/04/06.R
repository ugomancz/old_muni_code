# Priklad 6

lambda <- 4

# pravy konec intervalu hodnot x nutno vhodne upravovat
x <- seq (0, 1.5, by = 0.01)
titulek <- "exponencialni rozdeleni"

# hustota pravdepodobnosti
hustota <- dexp (x, rate = lambda)

#	hustotu graficky zobrazujeme jako krivku
plot (x, hustota, type = "l", col = "blue", lwd = 3, ylab = "hustota pravdepodobnosti", main = titulek)

# pravdepodobnost je dana plochou pod grafem hustoty pravdepodobnosti
# v R se ploch kresli jako vybarveny mnohouhelnik
polygon (c(min (x), x, max(x)), c(0, hustota, 0), col = "#CCFFCC")

# distribucni funkce je spojita, 
#	graficky ji zobrazujeme jako krivku
distribucni <- pexp (x, rate = lambda)
plot (x, distribucni, type = "l", col = "blue", lwd = 3, ylab = "distribucni funkce", main = titulek)


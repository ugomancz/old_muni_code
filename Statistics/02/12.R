# Priklad 12

a <- 10
r <- 2
n <- 10

par (mfrow = c(1,1), mar = c (2,2,4,1))
plot (c(-r, a+r), c(-r, a+r), type = "n", asp = 1)
abline (h = 0, col = "sienna", lty = 2)
abline (h = a, col = "sienna", lty = 2)
abline (v = 0, col = "sienna", lty = 2)
abline (v = a, col = "sienna", lty = 2)

# Generovani souradnic stredu micku 
Sx <- runif (n, min = 0, max = a) 
Sy <- runif (n, min = 0, max = a) 

V <- data.frame (cbind (Sx, Sy))
V$ok <- (V$Sx > r) & (V$Sx < a - r) & (V$Sy > r) & (V$Sy < a - r)
V$color <- ifelse (V$ok, "#00cc00", "#ff0000")
V$symbol <- ifelse (V$ok, 3, 4)

points (V$Sx, V$Sy, col = V$color, pch = V$symbol, lwd = 2)
nA <- sum (V$ok)
fA <- nA / n
title (main = paste (nA, "/", n, "=", fA))

# zakomentujte nasl. radek, pokud nechcete kreslit obrys micku (vhodne obzvlast pro velka n)
symbols (V$Sx, V$Sy, circles = rep (r, nrow (V)), fg = V$color, lty = 2, inches = FALSE, add = TRUE)

# Ukol: modifikujte reseni sit s oky tvaru obdelniku o stranach delek a, b
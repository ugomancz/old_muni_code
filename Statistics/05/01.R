#	Vypocetni pomucka k Prikladu 1

X <- seq (0, 4, by = 1)
p <- c (1/2, 1/4, 1/8, 1/16, 1/16)
F <- cumsum (p)
data.frame (X, p, F)

# ===============================================================================
#	Graficka pomucka k Prikladu 2

#	Definujeme vlastni hustotu pravdepodobnosti
f <- function (x) {
	f <- ifelse (x >= 0 & x <= 10, 1/5 - x/50, 0)
	return (f)
}

#	Definujeme vlastni distribucni funkci
F <- function (x) {
	F <- x/5 - x^2/100
	F[x < 0] <- 0
	F[x > 10] <- 1
	return (F)
}

x <- seq (-2, 12, by = 0.01)

plot (x, f(x), type = "l", col = "blue", lwd = 2)

plot (x, F(x), type = "l", col = "red", lwd = 2)
abline (v = 5, lty = 2)
abline (h = 0.75, lty = 2)

plot (x, f(x), type = "l", col = "blue", lwd = 2)
indexy <- which (x >= 0 & x <= 5)
polygon (x[c(min(indexy), indexy, max(indexy))], c(0, f(x[indexy]), 0), col = "#FFCC00")

# ===============================================================================
#	Vypocetni pomucka k Prikladu 3

v <- c(1/3, 0, 1/3, 0, 1/3, 0)
p <- matrix (v, 3, 2, dimnames = list (seq (-1, 1), seq (0, 1)))
p

pX <- rowSums (p)
pY <- colSums (p)

FX <- cumsum (pX)
FY <- cumsum (pY)

data.frame (pX, FX)
data.frame (pY, FY)

# ===============================================================================
#	Vypocetni pomucka k Prikladu 4

v <- c(1, 6, 3, 0, 10, 15, 0, 0, 10) / 45
p <- matrix (v, 3, 3, dimnames = list (seq (0, 2), seq (0, 2)))
p

pX <- rowSums (p)
pY <- colSums (p)

FX <- cumsum (pX)
FY <- cumsum (pY)

data.frame (pX, FX)
data.frame (pY, FY)

# F(1,1)
sum (p[1:2, 1:2])

# F(2,1)
sum (p[, 1:2])

# P(x >= 1)
sum (pX[2:3])

# ===============================================================================
#	Graficka pomucka k Prikladu 5

# Grafy marginalnich hustot pravdepodobnosti

fX <- function (w) {
	f <- ifelse (w >= 0 & w <= 10, (10 - w) / 50, 0)
	return (f)
}

fY <- function (w) {
	f <- ifelse (w >= 0 & w <= 10, w / 50, 0)
	return (f)
}

w <- seq (-2, 12, by = 0.01)

plot (w, fX(w), type = "l", col = "blue", lwd = 2, ylab = "marg. hustoty pravdepodobnosti")
lines (w, fY(w), col = "blue", lwd = 2, lty = 2)

# Grafy marginalnich distribucnich funkci

FX <- function (w) {
	F <- (10*w - w^2/2) / 50
	F[w < 0] <- 0
	F[w > 10] <- 1
	return (F)
}

FY <- function (w) {
	F <- w^2/100
	F[w < 0] <- 0
	F[w > 10] <- 1
	return (F)
}

plot (w, FX(w), type = "l", col = "blue", lwd = 2, ylab = "marg. distribucni funkce")
lines (w, FY(w), col = "blue", lwd = 2, lty = 2)

# P (X >= 4) = 1 - FX (4)
1 - FX (4)

# ===============================================================================
#	Vypocetni pomucka k Prikladu 6

lambdaX <- 1 
lambdaY <- 1/2 
w <- 2

# (b) 
1 - pexp (w, rate = lambdaX)

# (c) 
(1 - pexp (w, rate = lambdaX)) * (1 - pexp (w, rate = lambdaY))

# (d) 
pexp (w, rate = lambdaX) * (1 - pexp (w, rate = lambdaY)) + 
	(1 - pexp (w, rate = lambdaX)) * pexp (w, rate = lambdaY)

# (e) 
1 - pexp (w, rate = lambdaX) * pexp (w, rate = lambdaY)

#	Graficka pomucka k Prikladu 1

x <- seq (0, 10, by = 0.01)
fX <- dexp (x, rate = 0.5)
plot (x, fX, type = "l", col = "red", lwd = 2, ylab = "hustota X")

y <- seq (0, 660, by = 0.01)
fY <- ifelse (y < 60, 0, exp (-y/120 + 1/2) / 120)
dev.new () 
plot (y, fY, type = "l", col = "blue", lwd = 2, ylab = "hustota Y")



# ===============================================================================
#	Graficka pomucka k Prikladu 2

graphics.off ()

x <- seq (80, 120, by = 0.01)
fX <- dunif (x, 90, 110)
plot (x, fX, type = "l", col = "red", lwd = 2, ylab = "hustota X")

y <- seq (7000, 13000, by = 0.1)
fY <- ifelse (y < 8100 | y > 12100, 0, 1 / 40 / sqrt(y))
dev.new () 
plot (y, fY, type = "l", col = "blue", lwd = 2, ylab = "hustota Y")

graphics.off ()


# ===============================================================================
#	Vypocetni pomucka k Prikladu 6 

#	pnorm s defaultnimi parametry pocita distribucni funkci standardizovaneho normnalniho rozeleni N (0; 1)
pnorm (1/3)
1 - pnorm (1/3)



# ===============================================================================
#	Vypocetni pomucka k Prikladu 7 

u <- (240 - 40 * 5) / sqrt (8.3 * 40)
pnorm (u)



# ===============================================================================
#	Vypocetni pomucka k Prikladu 8 

u2 <- (1850 - 1800) / sqrt (180)
u1 <- (1750 - 1800) / sqrt (180)
pnorm (u2) - pnorm (u1)


# ===============================================================================
#	Vypocetni pomucka k Prikladu 9 

u2 <- (20.5 - 100/6) / sqrt (100 * 1/6 * 5/6)
u1 <- (-0.5 - 100/6) / sqrt (100 * 1/6 * 5/6)
pnorm (u2) - pnorm (u1)


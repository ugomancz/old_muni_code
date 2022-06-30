# =============================================================================================================================
# Priklad 6

tabulka <- read.csv (file = "teplota.csv", header = TRUE, sep = ",", dec = ".")
summary (tabulka)

# grafika

plot (c (1850, 2000), c (14, 15.5), type = "n", xlab = "rok", ylab = "teplota")

points (tabulka$Year, tabulka$Temperature, col = "blue", pch = 24, lwd = 1.5, cex = 1.0)

# primka

model1 <- lm (Temperature ~ Year, data = tabulka) 
model1
prehled1 <- summary (model1)
prehled1

# kubicka parabola
model2 <- lm (Temperature ~ Year + I(Year^2) + I(Year^3), data = tabulka) 
model2
prehled2 <- summary (model2)
prehled2



# prichystame si sit na x-ove ose
x <- seq (1850, 2000, by = 0.1)
# pomoci funkce "predict" nechame dopocitat odpovidajici Y-ove hodnoty na regresni funkci
Y1 <- predict (model1, data.frame (Year = x))
Y2 <- predict (model2, data.frame (Year = x))

lines (x, Y1, col = "red", lwd = 2)
lines (x, Y2, col = "#00cc00", lwd = 2)

# 95% intervaly spolehlivosti pro koeficienty modelu
confint (model1, level = 0.95)
# porovnejte je s testy vyznamnosti jednotlivych parametru
prehled1

confint (model2, level = 0.95)
prehled2

# muzeme prikreslit 95% pasy spolehlivosti pro stredni hodnotu, tj. kolem regresni funkce
CI1 <- predict (model1, data.frame (Year = x), interval = "confidence", level = 0.95)
CI2 <- predict (model2, data.frame (Year = x), interval = "confidence", level = 0.95)
lines (x, CI1[,2], col = "red", lty = 2)
lines (x, CI1[,3], col = "red", lty = 2)
lines (x, CI2[,2], col = "#00cc00", lty = 2)
lines (x, CI2[,3], col = "#00cc00", lty = 2)

# boxploty rezidui

boxplot (model1$residuals, model2$residuals, ylab = "rezidua", names = c(1,2), border = c ("red", "#00cc00"))

# porovnani modelu

sum (model1$residuals^2) / model1$df.residual
prehled1$r.squared
prehled1$adj.r.squared

sum (model2$residuals^2) / model2$df.residual
prehled2$r.squared
prehled2$adj.r.squared

anova (model1, model2) 

# oba modely jsou srovnatelne, volime model s regresni primkou, nebot je jednodussi pri stejne schopnosti modelovat data
# ANOVA zde hypotezu o rovnosti strednich hodnot obou modelu nezamita



#-----------------------------------------------------
#centrovane
tabulka$rok=tabulka$Year-1931

plot (c (-70, 70), c (14, 15.5), type = "n", xlab = "rok", ylab = "teplota")

points (tabulka$rok, tabulka$Temperature, col = "blue", pch = 24, lwd = 1.5, cex = 1.0)

# primka

model <- lm (Temperature ~ rok, data = tabulka) 
model
prehled <- summary (model)
prehled

model3 <- lm (Temperature ~ rok + I(rok^2) + I(rok^3), data = tabulka) 
model3
prehled3 <- summary (model3)
prehled3

# prichystame si sit na x-ove ose
x <- seq (-70, 70, by = 0.1)
# pomoci funkce "predict" nechame dopocitat odpovidajici Y-ove hodnoty na regresni funkci
Y <- predict (model, data.frame (rok = x))
Y3 <- predict (model3, data.frame (rok = x))

lines (x, Y, col = "red", lwd = 2)
lines (x, Y3, col = "#00cc00", lwd = 2)
# muzeme prikreslit 95% pasy spolehlivosti pro stredni hodnotu, tj. kolem regresni funkce
CI <- predict (model, data.frame (rok = x), interval = "confidence", level = 0.95)
CI3 <- predict (model3, data.frame (rok = x), interval = "confidence", level = 0.95)
lines (x, CI[,2], col = "red", lty = 2)
lines (x, CI[,3], col = "red", lty = 2)
lines (x, CI3[,2], col = "#00cc00", lty = 2)
lines (x, CI3[,3], col = "#00cc00", lty = 2)

# boxploty rezidui

boxplot (model$residuals, model3$residuals, ylab = "rezidua", names = c(1,2), border = c ("red", "#00cc00"))

# porovnani modelu

sum (model$residuals^2) / model$df.residual
prehled$r.squared
prehled$adj.r.squared

sum (model3$residuals^2) / model3$df.residual
prehled3$r.squared
prehled3$adj.r.squared

anova (model, model3) 

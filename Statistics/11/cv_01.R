# =============================================================================================================================
# Priklad 1 

tabulka <- read.csv (file = "KysMlecna.csv", header = TRUE, sep = ",", dec = ".")
names (tabulka)
str (tabulka)
summary (tabulka)

# primka 

model1 <- lm (novorozenec ~ matka, data = tabulka) 
model1
prehled1 <- summary (model1)
prehled1

model1$coefficients
coef (model1)
model1$residuals
residuals (model1)
model1$fitted.values
fitted.values (model1)
model.matrix (model1)

prehled1$sigma
prehled1$df
prehled1$r.squared
prehled1$adj.r.squared
prehled1$fstatistic

# parabola

model2 <- lm (novorozenec ~ matka + I(matka^2), data = tabulka) 
model2
prehled2 <- summary (model2)
prehled2

model2$coefficients
coef (model2)
model2$residual2
residuals (model2)
model2$fitted.values
fitted.values (model2)
model.matrix (model2)

prehled2$sigma
prehled2$df
prehled2$r.squared
prehled2$adj.r.squared
prehled2$fstatistic

# grafika

summary (tabulka)
plot (c (0, 70), c (-5, 60), type = "n", xlab = "matka", ylab = "novorozenec")

points (tabulka$matka, tabulka$novorozenec, col = "blue", pch = 24, lwd = 1.5, cex = 1.0)

# pruchystame si sit na x-ove ose
x <- seq (0, 70, by = 0.1)
# pomoci funkce "predict" nechame dopocitat odpovidajici Y-ove hodnoty na regresni funkci
Y1 <- predict (model1, data.frame (matka = x))
Y2 <- predict (model2, data.frame (matka = x))

lines (x, Y1, col = "red", lwd = 2)
lines (x, Y2, col = "#00cc00", lwd = 2)

# 95% intervaly spolehlivosti pro koeficienty modelu
confint (model1, level = 0.95)
# porovnejte je s testy vyznamnosti jednotlivych parametru
prehled1

confint (model2, level = 0.95)
prehled2

# muzeme prikreslit 95% pasy spolehlivosti pro stredni hodnotu, tj. kolem regresni funkce
CI1 <- predict (model1, data.frame (matka = x), interval = "confidence", level = 0.95)
CI2 <- predict (model2, data.frame (matka = x), interval = "confidence", level = 0.95)
lines (x, CI1[,2], col = "red", lty = 2)
lines (x, CI1[,3], col = "red", lty = 2)
lines (x, CI2[,2], col = "#00cc00", lty = 2)
lines (x, CI2[,3], col = "#00cc00", lty = 2)
dev.copy2pdf (file = "obrazek.pdf", width = 5, height = 4)

# boxploty rezidui

boxplot (model1$residuals, model2$residuals, ylab = "rezidua", names = c(1,2), border = c ("red", "#00cc00"))
dev.copy2pdf (file = "obrazek.pdf", width = 3.5, height = 4)

# porovnani modelu

sum (model1$residuals^2) / model1$df.residual
prehled1$r.squared
prehled1$adj.r.squared

sum (model2$residuals^2) / model2$df.residual
prehled2$r.squared
prehled2$adj.r.squared

anova (model1, model2) 

# primka je vhodnejsim modelem, rozhodneme se zde napr. podle rezidualniho souctu ctvercu ci korigovaneho indexu determinace
# ANOVA zde hypotezu o rovnosti strednich hodnot nezamita

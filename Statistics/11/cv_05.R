tabulka <- read.csv (file = "EmiseUhliku.csv", header = TRUE, sep = ",")
names (tabulka)
str (tabulka)
attach(tabulka)

model1 <- lm(CarbonEmissions~Year, data = tabulka)
(prehled1 <- summary(model1))


model2 <- lm(CarbonEmissions~Year + I(Year^2), data = tabulka)
(prehled2 <- summary(model2))

# vykresleni
summary(tabulka)
plot(c(1950,1995), c(1620,6080), type = "n", xlab = "rok", ylab = "emise")

points(Year, CarbonEmissions, col = "blue")

x <- seq(1950,1995)
# plot(rychlost, spotreba, type="p")
Y1 <- predict (model1, data.frame(Year = x))
Y2 <- predict (model2, data.frame(Year = x))

lines (x, Y1, col = "red", lwd = 2)
lines (x, Y2, col = "#00cc00", lwd = 2)

detach(tabulka)
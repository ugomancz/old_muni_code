tabulka <- read.csv (file = "CO2.csv", header = TRUE, sep = ",")
names (tabulka)
str (tabulka)
attach(tabulka)

model1 <- lm(CO2~poly(Year, degree=2, raw=T))
# summary(model1)

model2 <- lm(CO2~poly(Year, degree=3, raw=T))
summary(model2)

model3 <- lm(CO2~poly(Year, degree=4, raw=T))
# summary(model3)

model4 <- lm(CO2~poly(Year, degree=5, raw=T))
# summary(model4)


# vykresleni
summary(tabulka)
plot(c(1764,1995), c(276,361), type = "n", xlab = "rok", ylab = "emise")

points(Year, CO2, col = "blue")

x <- seq(1764,1995)
# plot(rychlost, spotreba, type="p")
Y1 <- predict (model1, data.frame(Year = x))
Y2 <- predict (model2, data.frame(Year = x))
Y3 <- predict (model3, data.frame(Year = x))
Y4 <- predict (model4, data.frame(Year = x))

lines (x, Y1, col = "red", lwd = 2)
lines (x, Y2, col = "blue", lwd = 2)
lines (x, Y3, col = "black", lwd = 2)
# model3 a model4 dávají stejný výsledek
lines (x, Y4, col = "yellow", lwd = 2)


detach(tabulka)
tabulka <- read.csv (file = "spotreba2.csv", header = TRUE, sep = ";", dec = ",")
names (tabulka)
str (tabulka)
attach(tabulka)

model1 <- lm(spotreba~rychlost, data = tabulka)
(prehled1 <- summary(model1))


model2 <- lm(spotreba~rychlost + I(rychlost^2), data = tabulka)
(prehled2 <- summary(model2))

# vykresleni
plot(c(30,110), c(5,11), type = "n", xlab = "rychlost", ylab = "spotreba")

points(rychlost, spotreba, col = "blue")

x <- seq (30,110, by = 0.1)
# plot(rychlost, spotreba, type="p")
Y1 <- predict (model1, data.frame (rychlost = x))
Y2 <- predict (model2, data.frame (rychlost = x))

lines (x, Y1, col = "red", lwd = 2)
lines (x, Y2, col = "#00cc00", lwd = 2)

confint (model1, level = 0.95)
confint (model2, level = 0.95)

detach(tabulka)
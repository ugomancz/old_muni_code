tabulka <- read.csv (file = "data002.csv", header = TRUE, sep = ",", dec = ".")
attach(tabulka)
lin_model <- lm(zasoba.TP~spotreba.TP, data = tabulka)
q_model <- lm(zasoba.TP~poly(spotreba.TP, degree=2, raw=TRUE), data = tabulka)

anova(lin_model, q_model)

# predikce_spotreby
koef <- lin_model$coefficients
koef[1] + koef[2]*2


# graf
summary (tabulka)
plot (c (0,6), c (0,9), type = "n", xlab = "spotreba", ylab = "zasoba", main="Graf závislosti zásoby TP na spotřebě")

points (spotreba.TP, zasoba.TP, col = "blue", pch = 24, lwd = 1.5, cex = 1.0)

x <- seq (0,6, by = 0.1)

Y1 <- predict (lin_model, data.frame (spotreba.TP = x))
Y2 <- predict (q_model, data.frame (spotreba.TP = x))

lines (x, Y1, col = "red", lwd = 2)
lines (x, Y2, col = "#00cc00", lwd = 2)

legend("bottomright",legend=c("lineární model","kvadratický model"),col=c("red","green"),lty=c(1,1))

# intervaly spolehlivosti

CI1 <- predict (lin_model, data.frame (spotreba.TP = x), interval = "confidence", level = 0.95)
CI2 <- predict (q_model, data.frame (spotreba.TP = x), interval = "confidence", level = 0.95)
lines (x, CI1[,2], col = "red", lty = 2)
lines (x, CI1[,3], col = "red", lty = 2)
lines (x, CI2[,2], col = "#00cc00", lty = 2)
lines (x, CI2[,3], col = "#00cc00", lty = 2)

# index determinace
summary(lin_model)$r.squared

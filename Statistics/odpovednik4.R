data <- read.csv (file = "odpovednik4.csv", header = TRUE, sep = ",", dec = ".")

# prumer vahy vsech subjektu

prumer_vahy <- mean(data$weight)

# smerodatna odchylka vysky vsech subjektu

rozptyl <- mean(data$height^2) - mean(data$height)^2
s <- sqrt(rozptyl)

# boxplot pro hmotnost
boxplot(data$weight, horizontal=T, main="boxplot pro hmotnost")
stripchart (data$weight, vertical = FALSE, method = "jitter", pch = 21, col = "red", bg = "yellow", cex = 0.8, add = TRUE)


# 0.75 kvantil vysky vsech subjektu
quantile(data$height, 0.75)


# rozdeleni do intervalu
min(data$weight)
max(data$weight)

#	dle zadani vytvarime intervaly delky 10

dolni <- seq (from = 39, to = 119, by = 10)
horni <- seq (from = 39 + 10, to = 119 + 10, by = 10)
stredy <- (dolni + horni) / 2

tabulka <- data.frame(dolni, horni, stredy)

n.j <- apply (tabulka, 1, function (w) {
  sum (data$weight > w[1] & data$weight <= w[2])
})
# n.j
# sum(n.j)

# mozna odecist toho jednoho cloveka, ktery nemuze byt ani v jednom intervalu?? (zena s 39kg)
# pak by to bylo takto: p.j <- n.j/(length(data$weight) - 1)
p.j <- n.j/length(data$weight)

tabulka <- cbind(tabulka, data.frame(n.j, p.j))
tabulka


# polygon cetnosti

plot(tabulka$stredy, tabulka$p.j, type="b", xlab="vaha", ylab="cetnost", main="polygon cetnosti")

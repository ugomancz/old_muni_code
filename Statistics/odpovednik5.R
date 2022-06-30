data <- read.csv (file = "data_odpovednik5.csv", header = TRUE, sep = ";", dec = ".")
data1 <- read.csv (file = "data_odpovednik51.csv", header = TRUE, sep = ";", dec = ".")
zeny <- subset(data1, pohlavi=="zena")
muzi <- subset(data1, pohlavi=="muz")

sigma.test(data1$skore.matematika,sigmasq=225)


var.test(zeny$skore.telocvik, muzi$skore.telocvik)

t.test(zeny$skore.cestina,muzi$skore.cestina,var.equal=T)

t.test(zeny$skore.cestina~muzi$skore.cestina,var.equal=T)

prumer1 <- mean(zeny$skore.cestina)
prumer2 <- mean(muzi$skore.cestina)
temp <- qt(1-(0.05/2), length(zeny$skore.cestina) + length(muzi$skore.cestina) - 2)
(prumer1 - prumer2) >= temp


cestina <- data1$skore.cestina
alpha <- 0.01
D <- mean(cestina) - qt(1-alpha/2, length(cestina) - 1)*sd(cestina)/sqrt(length(cestina))
H <- mean(cestina) + qt(1-alpha/2, length(cestina) - 1)*sd(cestina)/sqrt(length(cestina))
c(D,H)


zeny_tv <- muzi$skore.telocvik
muzi_tv <- zeny$skore.telocvik
alpha <- 0.05
var.test(zeny_tv, muzi_tv)

n1 <- length(zeny_tv)
n2 <- length(muzi_tv)
rozdil <- zeny_tv - muzi_tv

s1 <- sd(zeny_tv)
s2 <- sd(muzi_tv)

s12 <- sqrt(((n1-1)*s1^2+(n2-1)*s2^2)/(n1+n2-2))
D <- mean(zeny_tv) - mean(muzi_tv) - qt(1-alpha/2, n1+n2-2) * s12*sqrt(((n1+n2)/(n1*n2)))
H <- mean(zeny_tv) - mean(muzi_tv) + qt(1-alpha/2, n1+n2-2) * s12*sqrt(((n1+n2)/(n1*n2)))
c (D,H)

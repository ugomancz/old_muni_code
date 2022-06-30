#	Priklad 1

X <- c (0.31, 0.30, 0.29, 0.32)
n <- length (X)
prumer <- mean (X)
odchylka <- sd (X)
alpha <- 0.05
kvantil <- qchisq (1 - alpha, n - 1)
D <- sqrt (n - 1) * odchylka / sqrt (kvantil)
D



# Priklad 2 

data <- read.csv (file = "intervaly.csv", header = TRUE, sep = ",", dec = ".")
stredy <- (data$dolni + data$horni) / 2
X <- rep (stredy, data$cetnost)
n <- sum (data$cetnost)
prumer <- mean (X)
odchylka <- sd (X)
rozptyl <- var (X)

alpha <- 0.05
kvantil <- qt (1 - alpha/2, n - 1)
D <- prumer - kvantil * odchylka / sqrt(n)
H <- prumer + kvantil * odchylka / sqrt(n)
c (D, H)

alpha <- 0.05
kvantil1 <- qchisq (1 - alpha/2, n - 1)
kvantil2 <- qchisq (alpha/2, n - 1)
D <- (n - 1) * rozptyl / kvantil1
H <- (n - 1) * rozptyl / kvantil2
c (D, H)


# Priklad 3
zamestnanci <- 8000
alpha <- 0.05
n <- 160
vlakem <- 48
prumer <- vlakem/n
rozptyl <- sqrt(prumer*(1-prumer))
kvantil <- qnorm(1 - alpha/2)
D <- prumer - kvantil * rozptyl/sqrt(n)
H <- prumer + kvantil * rozptyl/sqrt(n)

prumer # bodovy odhad
c(D,H) # interval spolehlivosti pro podil
prumer * zamestnanci # bodovy odhad pro pocet
c(D*zamestnanci, H*zamestnanci) # interval spolehlivosti pro pocet


# Priklad 4
A <- c (0.140,0.138,0.143,0.142,0.144,0.137)
B <- c (0.135,0.140,0.142,0.136,0.138)
nA <- length(A)
nB <- length(B)
rozptylA <- 4*10^-6
rozptylB <- 9*10^-6
prumerA <- mean(A)
prumerB <- mean(B)
alpha <- 0.05
kvantil <- qnorm(1 - alpha)
D <- prumerA - prumerB - kvantil*sqrt(rozptylA/nA + rozptylB/nB)

D # dolni odhad

# Priklad 5 - spatne
data <- read.csv(file="selata.csv", header=TRUE, sep=",", dec=".")
X <- data$prir1
Y <- data$prir2
n1 <- length(X)
n2 <- length(Y)
s1 <- sd(X)
s2 <- sd(Y)
prumer1 <- mean(X)
prumer2 <- mean(Y)
s12 <- sqrt(((n1-1)*s1^2+(n2-1)*s2^2)/(n1+n2-2))
kvantil <- qt(1 - (alpha/2), n1+n2-2)
D <- prumer1 - prumer2 - kvantil * s12 * sqrt((n1+n2)/n1*n2)
H <- prumer1 - prumer2 + kvantil * s12 * sqrt((n1+n2)/n1*n2)

c(D,H) # interval spolehlivosti pro EX - EY


# Priklad 6



# Priklad 12 

data <- read.csv (file = "kola.csv", header = TRUE, sep = ",", dec = ".")

# cyklus pomoci funkce "sapply", kde se promenna M (= cislo mesice) postupne meni od 1 do 12
# v kazdem cyklu vratime 4 cisla: cislo mesice, dolni odhad stredni hodnoty, prumer, a horni odhad stredni hodnoty 
matice <- sapply (seq (1, 12), function (M) {
	X <- subset (data, mnth == M)$cnt
	n <- length (X)
	prumer <- mean (X)
	odchylka <- sd (X)
	alpha <- 0.05
	kvantil <- qt (1 - alpha / 2, n - 1)
	D <- prumer - kvantil * odchylka / sqrt (n) 
	H <- prumer + kvantil * odchylka / sqrt (n) 
	# jako posledni prikaz tela funkce v cyklu se uvede vektor cisel, ktera se maji ulozit do matice vysledku
	return (c (mesic = M, D = D, prumer = prumer, H = H))
})

matice 
# prehodime jeste sloupce a radky funkci "t" (= transpozice matice) a vytvorime tabulku 

tabulka <- data.frame (t (matice))
tabulka

plot (tabulka$mesic, tabulka$prumer, type = "b", lwd = 2, col = "red", ylim = c (1500, 6500), xlab = "mesic", ylab = "prumerny pocet zapujcek za den s 95% IS")
lines (tabulka$mesic, tabulka$D, type = "b", lty = 2, col = "green")
lines (tabulka$mesic, tabulka$H, type = "b", lty = 2, col = "blue")

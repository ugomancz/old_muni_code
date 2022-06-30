# Priklad 1 

n <- 40
N <- 22
alpha <- 0.05
prumer <- N / n 
odchylka <- sqrt (prumer * (1 - prumer))
rozptyl <- odchylka^2 

# i
(z <- abs (prumer - 0.5) * sqrt(n) / odchylka)
(kvantil <- qnorm (1 - alpha / 2))
z > kvantil

# ii
p <- 2 * (1 - pnorm (z))
p < alpha
# Pozor! binom.test v R dava jinou p-hodnotu, protoze pocita presnou p-hodnotu, nikoliv aproximovanou standardizovanym normalnim rozdelenim z CLV
binom.test (N, n, p = 0.5)

# iii
D <- prumer - kvantil*odchylka/sqrt(n)
H <- prumer + kvantil*odchylka/sqrt(n)
c (D, H)
(D <= 0.5) & (0.5 <= H)



# Priklad 2 

n1 <- 50
n2 <- 40
prumer1 <- 275
prumer2 <- 280
rozptyl1 <- 48
rozptyl2 <- 41
alpha <- 0.05

# i
(z <- abs (prumer1 - prumer2) / sqrt (rozptyl1 / n1 + rozptyl2 / n2))
(kvantil <- qnorm (1 - alpha))
z > kvantil

# ii
(p <- 1 - pnorm (z))
p < alpha

# iii
# Pocitame horni odhad v IS a divame se, jestli je cislo 0 (tj. neni rozdil v produkci za nulove hypotezy) mensi nez H
H <- (prumer1 - prumer2) + kvantil * sqrt (rozptyl1 / n1 + rozptyl2 / n2)
0 <= H



#	Priklad 3

data <- read.csv (file = "spotreba.csv", header = TRUE, sep = ";", dec = ",")
str (data)
X <- data$spotreba 
n <- length (X)
prumer <- mean (X)
rozptyl <- var (X)
odchylka <- sd (X)
alpha <- 0.05

# stredni hodnota
# prvni zpusob 
(t <- abs ((prumer - 9) / odchylka * sqrt(n)))
(kvantil <- qt (1-alpha/2, n-1))
t > kvantil

# druhy zpusob
(p <- 2 * min (1 - pt (abs (prumer - 9) / odchylka * sqrt(n), n-1), pt (abs (prumer - 9) / odchylka * sqrt(n), n-1)))
p < alpha
t.test (X, mu = 9)

# treti zpusob
D <- prumer - kvantil * odchylka / sqrt(n)
H <- prumer + kvantil * odchylka / sqrt(n)
c (D, H)
(D <= 9) & (9 <= H)

# odchylka, resp. rozptyl
# prvni zpusob
(k <- rozptyl / 0.5^2 * (n-1))
(kvantil1 <- qchisq (alpha/2, n-1))
(kvantil2 <- qchisq (1-alpha/2, n-1))
(k < kvantil1) | (kvantil2 < k)

# druhy zpusob
(p <- 2 * min (1 - pchisq (rozptyl * (n-1) / 0.5^2, n-1), pchisq (rozptyl * (n-1) / 0.5^2, n-1)))
p < alpha

# treti zpusob
kvantil1 <- qchisq (1 - alpha/2, n - 1)
kvantil2 <- qchisq (alpha/2, n - 1)
D <- (n - 1) * rozptyl / kvantil1
H <- (n - 1) * rozptyl / kvantil2
c (D, H)
(D <= 0.5^2) & (0.5^2 <= H)



#	Priklad 4

n <- 25
prumer <- 3118
odchylka <- 357
rozptyl <- odchylka^2 
alpha <- 0.05

# i
(k <- rozptyl / 300^2 * (n-1))
(kvantil1 <- qchisq (alpha/2, n-1))
(kvantil2 <- qchisq (1-alpha/2, n-1))
(k < kvantil1) | (kvantil2 < k)

# ii
(p <- 2 * min (1 - pchisq (rozptyl * (n-1) / 300^2, n-1), pchisq (rozptyl * (n-1) / 300^2, n-1)))
p < alpha

# iii
kvantil1 <- qchisq (1 - alpha/2, n - 1)
kvantil2 <- qchisq (alpha/2, n - 1)
D <- sqrt (n - 1) * odchylka / sqrt (kvantil1)
H <- sqrt (n - 1) * odchylka / sqrt (kvantil2)
c (D, H)
(D <= 300) & (300 <= H)



#	Priklad 5 

data <- read.csv (file = "pevnost.csv", header = TRUE, sep = ";", dec = ",")
str (data)
X <- data$pevnost
n <- length (X)
rozptyl <- var (X)
odchylka <- sd (X)
alpha <- 0.05

# i 
(k <- rozptyl / 0.36 * (n-1))
(kvantil2 <- qchisq (1-alpha, n-1))
k > kvantil2

# ii
(p <- pchisq (rozptyl * (n - 1)/0.36, n - 1, lower.tail = rozptyl < 0.36))
p < alpha

# iii
kvantil <- qchisq (1 - alpha, n - 1)
D <- (n - 1) * rozptyl / kvantil
D
D <= 0.36



#	Priklad 6 

data <- read.csv (file = "SiO2.csv", header = TRUE, sep = ";", dec = ",")
str (data)
# sloupec metoda je tzv. faktor, podle nehoz merene obsahy SiO_2 rozdelime do dvou statistickych souboru
X <- subset (data, metoda == "A")$obsah
Y <- subset (data, metoda == "B")$obsah
n_X <- length (X)
n_Y <- length (Y)
prumer_X <- mean (X)
prumer_Y <- mean (Y)
odchylka_X <- sd (X)
odchylka_Y <- sd (Y)
rozptyl_X <- var (X)
rozptyl_Y <- var (Y)
S12 <- sqrt (((n_X - 1) * rozptyl_X + (n_Y - 1) * rozptyl_Y) / (n_X + n_Y - 2))
alpha <- 0.05

# podil rozptylu 
# i
(f <- rozptyl_X / rozptyl_Y)
(kvantil1 <- qf (alpha / 2, n_X - 1, n_Y - 1))
(kvantil2 <- 1 / qf (alpha / 2, n_Y - 1, n_X - 1))
(f < kvantil1) | (kvantil2 < f)

# ii
(p <- 2 * min (1 - pf (rozptyl_X / rozptyl_Y, n_X - 1, n_Y - 1), pf (rozptyl_X / rozptyl_Y, n_X - 1, n_Y - 1)))
p < alpha
var.test (X, Y)

# iii
kvantil1 <- qf (1 - alpha / 2, n_X - 1, n_Y - 1)
kvantil2 <- qf (1 - alpha / 2, n_Y - 1, n_X - 1)
D <- rozptyl_X / rozptyl_Y / kvantil1
H <- rozptyl_X / rozptyl_Y * kvantil2
c (D, H)
(D <= 1) & (1 <= H)

# rozdil strednich hodnot
# i
(t <- abs ((prumer_X - prumer_Y) / S12 * sqrt((n_X * n_Y) / (n_X + n_Y))))
(kvantil <- qt (1-alpha/2, n_X + n_Y - 2))
t > kvantil

# ii
(p <- 2 * (1 - pt (t, n_X + n_Y - 2)))
p < alpha
t.test (X, Y, var.equal = TRUE)

# iii
kvantil <- qt (1 - alpha / 2, n_X + n_Y - 2)
D <- prumer_Y - prumer_X - kvantil * S12 * sqrt ((n_X+ n_Y) / (n_X * n_Y))
H <- prumer_Y - prumer_X + kvantil * S12 * sqrt ((n_X+ n_Y) / (n_X * n_Y))
c (D, H) 
(D <= 0) & (0 <= H)



# Priklad 7 

data <- read.csv (file = "zakaznici.csv", header = TRUE, sep = ",", dec = ".")
str (data)
X <- data$zakaznici
n <- length (X)
prumer <- mean (X)
odchylka <- sqrt (prumer)
rozptyl <- odchylka^2
alpha <- 0.05
# Pozn.: 20 sekund cekani odpovida 3 zakaznikum za minutu, tj. H_O: lambda=3

# i
(z <- abs (prumer - 3) / odchylka * sqrt (n))
(kvantil <- qnorm (1 - alpha/2))
z > kvantil

# ii
(p <- 2 * (1 - pnorm (z)))
p < alpha

# iii
kvantil <- qnorm (1 - alpha / 2)
D <- prumer - kvantil * odchylka / sqrt (n) 
H <- prumer + kvantil * odchylka / sqrt (n) 
c (D, H) 
(D <= 3) & (3 <= H)

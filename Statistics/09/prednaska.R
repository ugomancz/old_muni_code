#------------------
# Testovani hypotez
#------------------

# Prvni priklad - letadlo
# Nacteni dat
load("cviceni9.RData")
x <- data9$pr1$x

n <- length(x)
alpha <- 0.05

# prvni zpusob
(ux <- abs((mean(x)-872)/2.1*sqrt(n)))
(kvantil <- qnorm(1-alpha/2))

# druhy zpusob
2*pnorm(mean(x),mean=872,sd=2.1/sqrt(n))

# treti zpusob
D <- mean(x) - kvantil*2.1/sqrt(n)
H <- mean(x) + kvantil*2.1/sqrt(n)
c(D,H)

# ctvrty zpusob
#install.packages("TeachingDemos")
library("TeachingDemos")
z.test(x,mu=872,sd=2.1)

# Druhy priklad - chlapci
# Nacteni dat
load("cviceni9.RData")
x <- data9$pr2$x

n <- length(x)
alpha <- 0.05

# prvni zpusob
(ux <- (mean(x)-136.1)/6.4*sqrt(n))
(kvantil <- qnorm(1-alpha))

# druhy zpusob
1 - pnorm(mean(x),mean=136.1,sd=6.4/sqrt(n))

# treti zpusob
(D <- mean(x) - kvantil*6.4/sqrt(n))

# ctvrty zpusob
z.test(x,mu=136.1,alternative="greater",sd=6.4)


# Treti priklad - auto
# Nacteni dat
load("cviceni9.RData")
x <- data9$pr3$x

n <- length(x)
alpha <- 0.05
m <- mean(x)
s <- sd(x)

# a)
# prvni zpusob
(t <- abs((m-8.8)/s*sqrt(n)))
(kvantil <- qt(1-alpha/2,n-1))

# druhy zpusob
2*(1-pt((m-8.8)/s*sqrt(n),n-1))

# treti zpusob
D <- m - kvantil*s/sqrt(n)
H <- m + kvantil*s/sqrt(n)
c(D,H)

# ctvrty zpusob
t.test(x,mu=8.8)

# b)
# prvni zpusob
(k <- s^2/0.1*(n-1))
(kvantil1 <- qchisq(alpha/2,n-1))
(kvantil2 <- qchisq(1-alpha/2,n-1))

# druhy zpusob
pchisq( s^2*(n-1)/0.1, n-1) * 2
#pchisq( s^2*(n-1)/0.1, n-1, lower.tail= s^2 < 0.1 ) * 2

# treti zpusob
D <- s^2/kvantil2*(n-1)
H <- s^2/kvantil1*(n-1)
c(D,H)

# ctvrty zpusob
sigma.test(x, sigmasq = 0.1)


# Ctvrty priklad - hnojiva
# Nacteni dat
load("cviceni9.RData")
x <- data9$pr4$x
y <- data9$pr4$y

alpha <- 0.05
n1 <- length(x)
n2 <- length(y)
s1 <- sd(x)
s2 <- sd(y)
# a)
(f <- (s1/s2)^2)
(kvantil1 <- qf(1-alpha/2,n1-1,n2-1))
(kvantil2 <- 1/qf(1-alpha/2,n2-1,n1-1))
# b)
2*min(1-pf(var(x)/var(y),n1-1,n2-1),pf(var(x)/var(y),n1-1,n2-1))
# c)
D <- (s1/s2)^2/kvantil1
H <- (s1/s2)^2/kvantil2
c(D,H)

# d)
var.test(x,y)

# I
prumer_x <- mean(x)
prumer_y <- mean(y)
s12 <- sqrt(((n1-1)*s1^2+(n2-1)*s2^2)/(n1+n2-2))
(kvantil <- qt(1-alpha/2,n1+n2-2))
(t <- (prumer_x - prumer_y)/s12*sqrt((n1*n2)/(n1+n2)))

# II
(p <- 2*(1-pt(t,n1+n2-2)))

# III
D <- prumer_x - prumer_y - kvantil*s12*sqrt((n1+n2)/(n1*n2))
H <- prumer_x - prumer_y + kvantil*s12*sqrt((n1+n2)/(n1*n2))
c(D,H)

# IV
t.test(x,y,var.equal=T)

# Paty priklad - listy
# Nacteni dat
load("cviceni9.RData")
x <- data9$pr5$x
y <- data9$pr5$y

z <- x - y
alpha <- 0.05
n <- length(z)
prumer <- mean(z)
odchylka <- sd(z)

# I
(t <- prumer/odchylka*sqrt(n))
(kvantil <- qt(1-alpha/2,n-1))

# II
(p <- 2*(1-pt(t,n-1)))

# III
D <- prumer - kvantil*odchylka/sqrt(n)
H <- prumer + kvantil*odchylka/sqrt(n)
c(D,H)

# IV
t.test(x,y,paired=T)

# Sesty priklad - starosta
# Nacteni dat
n <- 100
pro <- 48
proti <- n - pro
alpha <- 0.05
# vypocet
prumer <- pro/n 
odh_odchylka <- sqrt(prumer*(1-prumer))
odchylka <- sqrt(0.6*(1-0.6))
kvantil <- qnorm(1-alpha/2)

# I
(u <- abs(prumer - 0.6)*sqrt(n)/odchylka)

# II
(p <- 2*(1-pnorm(u)))

# III
D <- prumer - kvantil*odh_odchylka/sqrt(n)
H <- prumer + kvantil*odh_odchylka/sqrt(n)
c(D,H)

# IV
binom.test(pro,n,p=0.6)
#prop.test(pro,n,p=0.6,correct=F)
#-----------------------------------------------------------------------------------
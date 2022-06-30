# Prvni priklad
# nacteni dat
load("cviceni7.RData")
clen <- data7$pr1$clen
dom <- data7$pr1$dom

# relativni cetnosti
rel_cetnosti <- dom/30

# kumulativni cetnosti
kum_cetnosti <- cumsum(dom)

# kumulativni relativni cetnosti
kum_rel_cetnosti <- cumsum(rel_cetnosti)

# zapis do tabulky
tabulka <- data.frame(nj=dom,pj=rel_cetnosti,Nj=kum_cetnosti,Fj=kum_rel_cetnosti)
tabulka

# graf cetnostni funkce
x11(w=12,h=9)
plot(clen,dom,type="p",pch=20,xlab="pocet clenu domacnosti",ylab="hodnoty cetnostni funkce",main="Graf cetnostni funkce")

# graf empiricke distribucni funkce
plot(c(clen,7),c(kum_rel_cetnosti,1),type="s",xlab="pocet clenu domacnosti",ylab="hodnoty empir. distr. fce",main="Graf empiricke distribucni funkce")

# sloupkovy diagram
barplot(dom,names.arg=as.character(1:6),xlab="pocet clenu domacnosti",ylab="pocet pozorovani",main="Sloupkovy diagram")

# polygon cetnosti
plot(clen,dom,type="b",pch=20,xlab="pocet clenu domacnosti",ylab="pocet pozorovani",main="Polygon cetnosti")

#---------------------------------------------------------------------------------------------------------------------------------------------------------
# Druhy priklad
# nacteni dat
load("cviceni7.RData")
stredy <- data7$pr2$stredy
dom <- data7$pr2$dom

# relativni cetnosti
rel_cetnosti <- dom/sum(dom)

# kumulativni cetnosti
kum_cetnosti <- cumsum(dom)

# kumulativni relativni cetnosti
kum_rel_cetnosti <- cumsum(rel_cetnosti)

# zapis do tabulky
tabulka <- data.frame(nj=dom,pj=rel_cetnosti,Nj=kum_cetnosti,Fj=kum_rel_cetnosti)
tabulka

# histogram
# nejprve je potreba vytvorit data
x <- rep(stredy,times=dom)
x
hist(x,breaks=c(35,stredy+15),xlab="vydaje",ylab="hodnoty cetnostni hustoty",main="Histogram")

# graf empiricke distribucni funkce
plot(seq(from=5,to=245,by=30),c(0,0,kum_rel_cetnosti,1),type='b',pch=20,xlab="vydaje",ylab="hodnoty empir. distr. fce",main="Empiricka distribucni funkce")

#----------------------------------------------------------------------------------------------------------------------------------------------------------
# Treti priklad
# nacteni dat
load("cviceni7.RData")
body <- data7$pr3$body
stud <- data7$pr3$stud

# vytvoreni dat
data <- rep(body,times=stud)

# vypocet kvantilu
quantile(data,probs=c(.5,.1,.9,.25,.75))

#----------------------------------------------------------------------------------------------------------------------------------------------------------
# Ctvrty priklad
# nacteni dat
load("cviceni7.RData")
clen <- data7$pr1$clen
dom <- data7$pr1$dom

# vytvoreni dat
data <- rep(clen,times=dom)

# prumer
prumer <- mean(data)

# rozptyl, pozor R implicitne pocita s 1/(n-1)
rozptyl <- var(data)
# korekce
n <- sum(dom)
rozptyl <- (n-1)/n*rozptyl

#----------------------------------------------------------------------------------------------------------------------------------------------------------
# Paty priklad
# boxplot
boxplot(data,horizontal=T,main="Boxplot")

#----------------------------------------------------------------------------------------------------------------------------------------------------------
# Sesty priklad
# nacteni dat
data <- data7$pr6$data

# vytvoreni vektoru poradi
j <- rank(data)   # seradime data

# vzorecek pro alfa
n <- length(data)
alpha_j <- (j-.375)/(n+.25)

# prislusne kvantily normalniho rozdeleni
u_j <- qnorm(alpha_j)

# vykreslime body
plot(u_j,j,pch=20,xlab="teoreticky kvantil",ylab="pozorovany kvantil",main="Q-Q plot")

# body prolozime primkou
lines(u_j, lm(j ~ u_j)$fitted.values)

# jinak
x11()
qqnorm(data)
qqline(data)
# naprogramujte n-p plot
#-----------------------------------------------------------------------------------------

# Sedmy priklad
# nacteni dat
load("minuta.RData")

# histogram
h <- hist(x,probability=TRUE, breaks="Scott",col="linen",
          xlab="odhad munity",
          main="Histogram, Normal Curve",ylim=c(0,0.08))
xx <- seq(from=min(h$breaks),to=max(h$breaks), length.out=50)
mx <- mean(x)
sx <- sd(x)
lines(xx,dnorm(xx,mean=mx,sd=sx),col=2)

# qqplot
qqnorm(x)
qqline(x,col=2)

# vyberova distribucni funkce
n <- length(x)
z <- sort((x-mx)/sx)
emp_F <- (1:n)/n
teor_F <- pnorm(z)
plot(z,emp_F,type='l',ylab="distribucni fce")
lines(z,teor_F,type="l",col="red")
legend("topleft",legend=c("Empiricka","Teoreticka"),col=c("black","red"),lty=c(1,1))

# P-P plot
plot(teor_F, emp_F, type = "p", pch = 20, main = "P-P plot")

model <- lm(emp_F ~ teor_F)
lines(teor_F, model$fitted.values, col = "red")
#-----------------------------------------------------------------------------------------


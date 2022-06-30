# Prvni priklad - LRM
# nacteni dat
load("cviceni10.RData")
X <- data10$pr1$X
Y <- data10$pr1$Y
(d <- dim(X))

# vypocet
XX<- solve(t(X)%*%X)
XY<- t(X)%*%Y
(beta <- XX%*%XY)
(Yhat <- X%*%beta)
(Se <- t(Y-Yhat)%*%(Y-Yhat))
(s <- Se/(d[1]-d[2]))

# nebo
mod <- lm(Y~0+X)
(ss <- summary(mod))
(beta <- mod$coefficients)
(Yhat <- mod$fitted.values)
(Se <- sum(mod$residuals^2))
(s <- Se/(d[1]-d[2]))

# Druhy priklad
# nacteni dat
load("cviceni10.RData")
x <- data10$pr2$X
Y <- data10$pr2$y
d <- length(x)

# vypocet
# model 1: beta_0 + beta_1 x
model1 <- lm(Y~1+x)
(prehled <- summary(model1))
beta <- model1$coefficients
Yhat <- model1$fitted.values
s <- prehled$sigma^2
ID <- prehled$r.squared
F <- prehled$fstatistic["value"]
M <- prehled$coefficients
M[,4] # p-hodnoty testu pro jednotlive koeficienty
# vykresleni
x11()
plot(x,Y,type="p")
curve(predict(model1,data.frame(x=x)),add=T)

# model 2: beta_1 x
model2 <- lm(Y~0+x)
(prehled <- summary(model2))
beta <- model2$coefficients
Yhat <- model2$fitted.values
s <- prehled$sigma^2
ID <- prehled$r.squared
F <- prehled$fstatistic["value"]
M <- prehled$coefficients
M[,4] # p-hodnoty testu pro jednotlive koeficienty
# vykresleni
plot(x,Y,type="p")
curve(predict(model2,data.frame(x=x)),add=T,col=2)

# model 3: beta_0 + beta_1 x + beta_2 x^2
model3 <- lm(Y~1+x+I(x^2))
(prehled <- summary(model3))
beta <- model3$coefficients
Yhat <- model3$fitted.values
s <- prehled$sigma^2
ID <- prehled$r.squared
F <- prehled$fstatistic["value"]
M <- prehled$coefficients
M[,4] # p-hodnoty testu pro jednotlive koeficienty
# vykresleni
plot(x,Y,type="p")
curve(predict(model3,data.frame(x=x)),add=T,col=3)

# model 4: beta_1 x + beta_2 x^2
model4 <- lm(Y~0+x+I(x^2))
(prehled <- summary(model4))
beta <- model4$coefficients
Yhat <- model4$fitted.values
s <- prehled$sigma^2
ID <- prehled$r.squared
F <- prehled$fstatistic["value"]
M <- prehled$coefficients
M[,4] # p-hodnoty testu pro jednotlive koeficienty
# vykresleni
plot(x,Y,type="p")
curve(predict(model4,data.frame(x=x)),add=T,col=4)

# model5: beta_0 + beta_1 x + beta_2 exp(x)
model5 <- lm(Y~1+x+I(exp(x)))
(prehled <- summary(model5))
beta <- model5$coefficients
Yhat <- model5$fitted.values
s <- prehled$sigma^2
ID <- prehled$r.squared
F <- prehled$fstatistic["value"]
M <- prehled$coefficients
M[,4] # p-hodnoty testu pro jednotlive koeficienty
# vykresleni
plot(x,Y,type="p")
curve(predict(model5,data.frame(x=x)),add=T,col=5)

# Vykresleni vsech
x11(w=12,h=9)
plot(x,Y,type="p")
curve(predict(model1,data.frame(x=x)),add=T,col=1)
curve(predict(model2,data.frame(x=x)),add=T,col=2)
curve(predict(model3,data.frame(x=x)),add=T,col=3)
curve(predict(model4,data.frame(x=x)),add=T,col=4)
curve(predict(model5,data.frame(x=x)),add=T,col=5)
legend("bottomright",legend=c("model 1","model 2", "model 3", "model 4", "model 5"),col=1:5,lty=rep(1,5))

# Interpolacni polynom
model <- lm(Y~1+x+I(x^2)+I(x^3)+I(x^4))
(prehled <- summary(model))
plot(x,Y,type="p")
curve(predict(model,data.frame(x=x)),add=T,col=6)

# Pridani hodnoty
model1 <- lm(Y~1+x)
x[6]<- 3
Y[6]<- -2
plot(x,Y,type="p")
curve(predict(model1,data.frame(x=x)),add=T)
model_post <- lm(Y~1+x)
curve(predict(model_post,data.frame(x=x)),add=T,col=2)
legend("topright",legend=c("puvodni model","aktualizovany model"),col=1:2,lty=rep(1,2))


# Treti priklad
# nacteni dat
load("cviceni10.RData")
x <- data10$pr3$X
Y <- data10$pr3$Y

# vypocet
# model: beta_0 + beta_1 x
model <- lm(Y~1+x)
(prehled <- summary(model))
# vykresleni
plot(x,Y,type="p")
curve(predict(model,data.frame(x=x)),add=T)

# model: beta_1 x
model <- lm(Y~0+x)
(prehled <- summary(model))
# vykresleni
curve(predict(model,data.frame(x=x)),col="red",add=T)

# Ctvrty priklad
# nacteni dat
rm(list=ls())
load("cukrovka.RData")
attach(cukrovka)
w <- cetnosti/sum(cetnosti) # vektor vah
x <- (x.od+x.do)/2  # stredy intervalu
plot(x,Y, cex = 50 * w, xlab = "mnozstvi hnojiva", ylab = "vynos", main = "Vynosy cukrovky")

# model I
# 1) vypocet vazeneho
mod1 <- lm(Y ~ x, weight = w)
(prehled1 <- summary(mod1))
# 2) vypocet nevazeneho
mod1b <- lm(Y ~ x)
(prehled1b <- summary(mod1b))
# vykresleni
curve(predict(mod1,data.frame(x=x)),add=T,col="red")
curve(predict(mod1b,data.frame(x=x)),add=T,col="green")
legend("bottomright",legend=c("Vazeny","Nevazeny"),col=c("red","green"),lty=c(1,1))

# model II
# 1) vypocet vazeneho
mod2 <- lm(Y ~ 1+x+I(x^2), weight = w)
(prehled2 <- summary(mod2))
# 2) vypocet nevazeneho
mod2b <- lm(Y ~ 1+x+I(x^2))
(prehled2b <- summary(mod2b))
# vykresleni
plot(x,Y, cex = 50 * w, xlab = "mnozstvi hnojiva", ylab = "vynos", main = "Vynosy cukrovky")
curve(predict(mod2,data.frame(x=x)),add=T,col="red")
curve(predict(mod2b,data.frame(x=x)),add=T,col="green")
legend("bottomright",legend=c("Vazeny","Nevazeny"),col=c("red","green"),lty=c(1,1))

# model III
# 1) vypocet vazeneho
mod3 <- lm(Y ~ 1+I(sqrt(x)), weight = w)
(prehled3 <- summary(mod3))
# 2) vypocet nevazeneho
mod3b <- lm(Y ~ 1+I(sqrt(x)))
(prehled3b <- summary(mod3b))
# vykresleni
plot(x,Y, cex = 50 * w, xlab = "mnozstvi hnojiva", ylab = "vynos", main = "Vynosy cukrovky")
curve(predict(mod3,data.frame(x=x)),add=T,col="red")
curve(predict(mod3b,data.frame(x=x)),add=T,col="green")
legend("bottomright",legend=c("Vazeny","Nevazeny"),col=c("red","green"),lty=c(1,1))

# Residua
res1 <- prehled1$residuals
res2 <- prehled2$residuals
res3 <- prehled3$residuals
boxplot(data.frame(M1=res1,M2=res2,M3=res3),horizontal=T,xlab="residua")
# Q-Q ploty pro residua
qqnorm(res1)
qqline(res1)
# totez
plot(mod1,2)
plot(mod2,2)
plot(mod3,2)

#Shapiro Wilk test
shapiro.test(res1)
shapiro.test(res2)
shapiro.test(res3)

# analyza residui
par(mfrow = c(2,2))
plot(mod1)
x11()
par(mfrow = c(2,2))
plot(mod2)
detach(cukrovka)
# -----------------------------------------------------------------

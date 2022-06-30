# Priklad 10

n <- 100

# nastaveni grafickych parametru, vice viz "?par"
par (mfrow = c(1,1), mar = c (4,4,4,1))
# prikazem "plot" s parametrem type="n" prichystame prazdny souradnicovy system 
plot (c(18,19), c(18,19), type = "n", xlab = "Eva", ylab = "Honza")

# funkce "runif" generuje vektor (delky n) nahodnych cisel nezavisle generovanych v zadanem intervalu 
E <- runif (n, 18, 19)
H <- runif (n, 18, 19)

# funkce "cbind" vytvari matici z vektoru (matic) tak, ze je umisti jako sloupce vedle sebe
# funkce "data.frame" vytvari datovou tabulku
# v datove tabulce sloupce odpovidaji jednotlivym promennych, radky odpovidaji jednotlivym merenim (opakovanim pokusu)
V <- data.frame (cbind (E, H))
# logicka formule
V$ok <- (V$E - 1/6 <= V$H) & (V$H <= V$E + 1/3)
V$color <- ifelse (V$ok, "#00cc00", "#ff0000")
V$symbol <- ifelse (V$ok, 4, 4)

# prikaz "points" vykresluje body, jejich souradnice jsou zadany vektory jako prvni dva argumenty
# parametr col nastavuje barvu, parametr pch kreslici symbol, lwd tloustku car
points (V$E, V$H, col = V$color, pch = V$symbol, lwd = 2)
# spocitame a do obrazku vypiseme relativni cetnost
nA <- sum (V$ok)
fA <- nA / n
title (main = paste (nA, "/", n, "=", fA))
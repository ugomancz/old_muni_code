#	library (prob)

#	Priklad 3

#	Kunhuta
# "DK" = divka Kunhuta, "Do" = divka jineho jmena, "H" = hoch

u <- c ("DK", "Do", "H")
# Ceska republika: 1 osoba z 3566848 ma jmeno Kunhuta
p1 <- 1 / 3566848
p <- c (p1, 0.5 - p1, 0.5)
S <- iidspace (u, 2, probs = p)
S
#	V jedne rodine nemuze mit vice deti stejne jmeno
S[2,]$probs <- S[2,]$probs + S[1,]$probs / 2
S[4,]$probs <- S[4,]$probs + S[1,]$probs / 2
S[1,]$probs <- 0
S

dev.new ()
barplot (as.matrix (S$probs), col = rainbow (nrow (S)), horiz = TRUE, xlim = c (0, 1.4), main = "Kunhuta") 
legend ("right", legend = paste (S$X1, S$X2, round (S$probs, 2), sep = " - ") , fill = rainbow (nrow (S)))

B <- subset (S, isin (S, "DK"))
A <- subset (S, ! isin (S, "H"))
AB <- intersect (A, B)
Prob (AB) / Prob (B)



# ================================================================================
#	Marie

u <- c ("DM", "Do", "H")
# Ceska republika: 1 osoba z 40 ma jmeno Marie
p1 <- 1 / 40
p <- c (p1, 0.5 - p1, 0.5)
S <- iidspace (u, 2, probs = p)
S
#	V jedne rodine nemuze mit vice deti stejne jmeno
S[2,]$probs <- S[2,]$probs + S[1,]$probs / 2
S[4,]$probs <- S[4,]$probs + S[1,]$probs / 2
S[1,]$probs <- 0
S

dev.new ()
barplot (as.matrix (S$probs), col = rainbow (nrow (S)), horiz = TRUE, xlim = c (0, 1.4), main = "Marie") 
legend ("right", legend = paste (S$X1, S$X2, round (S$probs, 2), sep = " - ") , fill = rainbow (nrow (S)))

B <- subset (S, isin (S, "DM"))
A <- subset (S, ! isin (S, "H"))
AB <- intersect (A, B)
Prob (AB) / Prob (B)



# ================================================================================
#	Fikce: kdyby petinu populace v CR tvorily zeny se stejnym jmenem

u <- c ("DJ", "Do", "H")
# Fikce: 1 osoba z 5 ma jedno stejne zenske jmeno
p1 <- 1 / 5
p <- c (p1, 0.5 - p1, 0.5)
S <- iidspace (u, 2, probs = p)
S
#	V jedne rodine nemuze mit vice deti stejne jmeno
S[2,]$probs <- S[2,]$probs + S[1,]$probs / 2
S[4,]$probs <- S[4,]$probs + S[1,]$probs / 2
S[1,]$probs <- 0
S

dev.new ()
barplot (as.matrix (S$probs), col = rainbow (nrow (S)), horiz = TRUE, xlim = c (0, 1.4), main = "velmi zastoupene jmeno") 
legend ("right", legend = paste (S$X1, S$X2, round (S$probs, 2), sep = " - ") , fill = rainbow (nrow (S)))

B <- subset (S, isin (S, "DJ"))
A <- subset (S, ! isin (S, "H"))
AB <- intersect (A, B)
Prob (AB) / Prob (B)

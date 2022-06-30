#	library (prob)

#	Priklad 2

# "D" = divka, "H" = hoch

u <- c ("D", "H")
p <- c (0.5, 0.5)
iidspace (u, 1, probs = p)
S <- iidspace (u, 2, probs = p)
S

barplot (as.matrix (S$probs), col = rainbow (nrow (S)), horiz = TRUE, xlim = c (0, 1.4)) 
legend ("right", legend = paste (S$X1, S$X2, round (S$probs, 2), sep = " - ") , fill = rainbow (nrow (S)))

# A = obe deti jsou dcery
# B = jedno dite je dcera
# P (A | B) = ?
B <- subset (S, isin (S, "D"))
A <- subset (S, isin (S, c ("D", "D")))
AB <- intersect (A, B)
Prob (AB) / Prob (B)

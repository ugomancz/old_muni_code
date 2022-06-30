#	Priklad 4

# Pravdepodobnostn prostor vytvorime primym zapisem
kategorie <- rep (c ("A", "B", "C"), each = 2)
nehoda <- rep (c ("ano", "ne"), 3)
# Zkombinujeme do datove tabulky
el.jevy <- data.frame (kategorie, nehoda)
# Zadame pravdepodobnosti 
p <- c (0.7 * 0.03, 0.7 * (1-0.03), 0.2 * 0.06, 0.2 * (1-0.06), 0.1 * 0.1, 0.1 * (1-0.1))
S <- probspace (el.jevy, probs = p)

S
sum (S$probs)

barplot (as.matrix (S$probs), col = rainbow (nrow (S)), horiz = TRUE, xlim = c (0, 1.4), main = "kategorie - nehoda") 
legend ("right", legend = paste (S$kategorie, S$nehoda, round (S$probs, 2), sep = " - ") , fill = rainbow (nrow (S)))

N <- subset (S, nehoda == "ano")
Prob (N)

A <- subset (S, kategorie == "A")
AN <- intersect (A, N)
Prob (AN) / Prob (N)
Prob (AN)

# Analogicky zkontrolujte ostatni podminene pravdepodobnosti a pravdepodobnosti pruniku

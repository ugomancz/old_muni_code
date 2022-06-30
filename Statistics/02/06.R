#	nacteme knihovnu "prob", pokud jsme ji dosud nenacetli
# library (prob)

# Priklad 6

kostky <- rolldie (2)

S <- probspace (kostky)

S
str (S)
names (S)
dim (S)



# chceme dopocitat soucet padlych cisel pro kazdy elementarni jev
# misto psani for-cyklu vyuzijeme funkci apply 

# prozkoumejte chovani funkce apply
apply (kostky, 1, sum)
apply (kostky, 2, sum)

# vytvorime si kopii datove tabulky
# a doplnime sloupec nazvany "soucty" do datove tabulky pravdepodobnostniho prostoru
S1 <- S
S1$soucet <- apply (kostky, 1, sum)

S1
str (S1)
names (S1)



# jednoduchou frekvencni tabulku (tabulku cetnosti) vytvoriem funkci "table"
tab <- table (S1$soucet)
tab

# misto cetnosti chceme pravdepodobnosti 
psti <- tab / nrow (S1)
psti

sum (psti)

barplot (psti)
male(tywin).
male(tommen).
male(joffrey).
male(jaime).

female(myrcella).
female(cersei).
female(joanna).

parent(cersei, tommen).
parent(cersei, myrcella).
parent(cersei, joffrey).
parent(jaime, myrcella).
parent(jaime, joffrey).
parent(jaime, tommen).
parent(joanna, cersei).
parent(joanna, tyrion).
parent(joanna, jaime).
parent(tywin, jaime).
parent(tywin, cersei).
parent(tywin, tyrion).

maleGrandchild(X, Z) :- parent(X, Y), parent(Y, Z), male(Z).

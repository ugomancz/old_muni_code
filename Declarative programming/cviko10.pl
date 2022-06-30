woman(pavla).
woman(vlasta).
woman(jarmila).
woman(zuzana).
woman(tereza).

man(radek).
man(jirka).
man(michal).
man(filip).
man(martin).
man(petr).
man(adam).
man(vaclav).

parent(radek, michal).
parent(radek, filip).
parent(pavla, michal).
parent(pavla, filip).
parent(pavla, martin).
parent(jirka, martin).
parent(jarmila, petr).
parent(michal, petr).
parent(filip, adam).
parent(vlasta, adam).
parent(adam, tereza).
parent(adam, vaclav).
parent(zuzana, tereza).
parent(zuzana, vaclav).

father(Father, Child) :- parent(Father, Child), man(Father).

parentOfTwo(Parent) :- parent(Parent, First), parent(Parent, Second), First \= Second.

% == je test na identitu termů, bez unifikace; =:= je test na aritmetickou shodu, vyhodnotí obě strany

% firstnums(Number, Sum).
firstnums(0, 0).
firstnums(N, S) :- N1 is N - 1, firstnums(N1, S1), S is N + S1.

powertwo(1).
powertwo(X) :- X1 is X/2, powertwo(X1).



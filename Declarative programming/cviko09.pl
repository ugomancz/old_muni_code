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
parent(honza,pavla).
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
mother(Mother, Child) :- parent(Mother, Child), woman(Mother).
child(Child, Parent) :- parent(Parent, Child).
grandmother(Granny, Kid)  :- woman(Granny), parent(Granny, X), parent(X, Kid).
brother(Bro1, Bro2) :- man(Bro1), man(Bro2), parent(X, Bro1), parent(X, Bro2).
descendant(Child,Parent) :- parent(Parent,Child).
descendant(New,Old) :- parent(X, New), descendant(X, Old).


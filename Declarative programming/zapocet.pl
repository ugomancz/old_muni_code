only([X], Y) :- X=Y.
only([X|SF], Y) :- X=Y, only(SF, Y).

consecutive([X,Y]) :- X is Y-1.
consecutive([X,Y|Z]) :- X is Y-1; consecutive([Y|Z]).


lengtho([_|Z],Y) :- lengtho(Z,Y1), Y is Y1+1.
lengtho([],0).

z(a).
z(c).
zz(a).
u(X,Y) :- zz(X), Y = b.
u(X,Y) :- z(X), z(Y).

powertwo(1).
powertwo(X) :- X1 is X/2, 1 =< X1, powertwo(X1).

mydrop(_,0,Z).
mydrop([_|Y],Z,_) :- Z1 is Z-1, L1 = Y, mydrop(Y,Z1,L1).

f(a).
f(c).
g(X) :- h(Y,X), f(X).
h(X,Y) :- f(X), f(Y).

fo([],_,[]).
fo(_,[],[]).
fo([X],[Y],[Z]) :- Z is X+Y.
fo([X|S1],[Y|S2],[Z|S3]) :- Z is X+Y, fo(S1,S2,S3).

test([_|S],Z) :- Z = S.

intail([],[]).
intail([[_|XS]|G],[XS|V]) :- intail(G,V).

inhead([],[]).
inhead([[X|_]|SF],[X|XS]) :- inhead(SF,XS).

myfilter([],[]).
myfilter([X|XS],[X|YS]) :- X > 3, myfilter(XS,YS).
myfilter([X|XS],YS) :- X =< 3, myfilter(XS,YS).
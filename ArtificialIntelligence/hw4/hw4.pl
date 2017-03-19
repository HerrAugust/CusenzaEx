% This is the first step (which is parsing a sentence - if it belongs to the grammar) for building a Natural Language Processing System that,
% taken an input by the user (e.g., "Put block b from c onto the table") performs that action.

s(s(V,O,FP,TP)) 						--> verb(V),obj(O),fromplace(FP),toplace(TP).
verb(verb(put)) 						--> [put].
obj(obj(W,BN))							--> word(W),blockname(BN).
word(word(block))						--> [block].
blockname(blockname(a))					--> [a].
blockname(blockname(b))					--> [b].
blockname(blockname(c))					--> [c].
fromplace(fromplace(P,BN))				--> preposition(P),blockname(BN).
toplace(toplace(P,FIX))					--> preposition(P),fixplace(FIX).
fixplace(fixplace(B2,B3))				--> b(B2),b(B3).
b(b(the))								--> [the].
b(b(table))								--> [table].
toplace(toplace(P,W,BN))				--> preposition(P),word(W),blockname(BN).
preposition(preposition(from))			--> [from].
preposition(preposition(onto))			--> [onto].

% launch and make 	the query "s(T,[put,block,a,from,b,onto,the,table],[])."
% or also 			the query "s(T,[put,block,a,from,b,onto,block,c],[])."
% or an admissible sentence.
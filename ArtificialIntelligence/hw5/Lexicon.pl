% takes as input a list of tokens (e.g., [is, block, a, on, block, b, ?]) and returns its 

% Note: this code is almost a copy-past of the code by N.C.Petersen. In fact, I adapted it for my specific Blocks World,
% in which blocks are not colored.

/* */
/* Natural Language in Blocks Worlds */
/* by Niklas Christoffer Petersen , Spring 2010 */
/* */
/* LEXICON FILE */
/* */

/* Articles */
lex(the , np(X)/n(X) , []) .
lex(a , np(X)/ n(X) , []) .

/* NOUNS */
/* Pronouns */
lex( it , np(X) , [ last(X) ]) .

/* Common Nouns */
lex( color , n(X ,Y) , [ color(X ,Y) ]) .
lex( object , n(X) , [ object(X ,_) ]) .
lex( table , n(X) , [ object(X , table ) ]) .
lex( block , n(X) , [ object(X , block ) ]) .

/* VERBS */
/* Imperative */
lex( grasp , s( cmd ) / np(X) , [ grasp(X) ]) .
/* Imperative with preposition */
lex( put , (s( cmd )/ pp(X , Y))/ np(X) , [ put(X ,Y) ]) .
lex( grasp , (s( cmd )/ pp(X ,_)) / np( X) , [ grasp(X ) ]) .
/* Transitive */
lex( is , (s( dcl )\ np(X)) / np(X ) , []) .
lex( supports , (s( dcl )\ np(Y) )/ np(X) , [ on(X ,Y ) ]) .

/* ADJECTIVES. Not present in my Blocks World */
% lex( yellow , n(X)/ n(X) , [ color(X , yellow ) ]) .
% lex( blue , n(X)/n(X) , [ color(X , blue ) ]) .

/* PREPOSITION */
lex( from , pp(X ,Y) / np(Y) , [ in(X ,Y) ]) .
lex( from , pp(X ,Y) / np(Y) , [ on(X ,Y) ]) .
lex( in , pp(X , Y)/ np(Y) , [ in(X ,Y ) ]) .
lex( into , pp(X ,Y) / np(Y) , [ in(X ,Y) ]) .
lex( on , pp(X , Y)/ np(Y) , [ on(X ,Y ) ]) .
lex( onto , pp(X ,Y) / np(Y ) , [ on(X ,Y) ]) .

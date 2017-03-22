:- use_module(library(porter_stem)).

tokenize(Sentence, Tokens) :- string_lower(Sentence,PrivSentence),tokenize_atom(PrivSentence,Tokens).
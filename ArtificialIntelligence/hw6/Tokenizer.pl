%%%%%%%%%%%%%%%%%%%%%%%
% Author: 	HerrAugust
% Source: 	https://github.com/HerrAugust/EserciziUni/tree/master/ArtificialIntelligence/hw6
% License: 	Opensource. This code is provided AS IS, WITHOUT ANY WORRANTY
%%%%%%%%%%%%%%%%%%%%%%%

:- use_module(library(porter_stem)).

tokenize(Sentence, Tokens) :- string_lower(Sentence,PrivSentence),tokenize_atom(PrivSentence,Tokens).
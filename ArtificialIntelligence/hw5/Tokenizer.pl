remove_Quotes([],Res).
remove_Quotes([H|TokenList],Res) :- atom_codes(Atom , H), remove_Quotes(TokenList, [Atom]).
% see http://stackoverflow.com/questions/19736439/delete-character-from-string-in-prolog

tokenize(Sentence, Tokens) :- string_lower(Sentence,PrivSentence),split_string(PrivSentence, " ", "", PrivTokens),remove_Quotes(PrivTokens,Tokens).
:- 	consult('Tokenizer.pl').

:- 	consult('Parser.pl').

write_list([]).
write_list([H|List]) :- write(H),write(", "),write_list(List).

% calls a predicate in Parser.pl
parse(Sentence, Tree) :- s(Tree, Sentence, []).

run :- 	write("Ask me to check something (e.g., 'Is block a on the table?'): "),
		read(Assertion),
		tokenize(Assertion, Tokens),
		parse(Tokens, Tree),
		write('Got tree:'),write(Tree).


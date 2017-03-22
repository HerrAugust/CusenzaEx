:- 	consult('Tokenizer.pl').

:- 	consult('Parser.pl').

:- 	consult('Interpreter.pl').

% writes a list 
write_list([]).
write_list([H|List]) :- write(H),write(", "),write_list(List).

% calls a predicate in Parser.pl that returns the parse tree
parse(Sentence, Tree) :- s(Tree, Sentence, []).

run :- 	write("Ask me to check something (e.g., 'Is block a on the table?'): "),
		read(Assertion),
		tokenize(Assertion, Tokens),
		parse(Tokens, Tree),
		write('Got tree:'),write(Tree),
		int_assertion(Tree).

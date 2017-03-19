:- 	consult('Tokenizer.pl').

:- 	consult('Parser.pl').

% calls a predicate in Parser.pl
parse(Sentence, Tree) :- s(Tree, Sentence, []).

run :- 	repeat,
		flush,
		write("Ask me to check something (e.g., if a block is on the table): "),
		read(Assertion),
		write(Assertion),
		tokenize(Assertion, Tokens),
		parse(Tokens, Tree),
		write(Tree).
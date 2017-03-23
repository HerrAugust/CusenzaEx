%%%%%%%%%%%%%%%%%%%%%%%
% What the grammar allows
%%%%%%%%%%%%%%%%%%%%%%%
% Accepting assertions:
% 	1. is b on the table?
% 	2. is b on c?
% Accepting commands:
% 	1. Grasp block b
%	2. Put it onto the table
%	3. Put it onto c
% Accepting queries:
% 	1. Which blocks are on the table?
%	2. What color is b?

%%%%%%%%%%%%%%%%%%%%%%%
% Imports
%%%%%%%%%%%%%%%%%%%%%%%
:- 	consult('Tokenizer.pl').

:- 	consult('Parser.pl').

:- 	consult('Interpreter.pl').


%%%%%%%%%%%%%%%%%%%%%%%
% Utility functions
%%%%%%%%%%%%%%%%%%%%%%%
% writes a list 
write_list([]).
write_list([H|List]) :- write(H),write(", "),write_list(List).

% calls a predicate in Parser.pl that returns the parse tree of sentence (e.g., "toplace(put,b).")
parse(Sentence, Tree) :- s(Tree, Sentence, []).

%%%%%%%%%%%%%%%%%%%%%%%
% Main program
%%%%%%%%%%%%%%%%%%%%%%%
run :- 	write("Ask me something (e.g., 'Is block a on the table?'): "),
		read(Request),
		tokenize(Request, Tokens),
		parse(Tokens, Tree),
		write('Got tree:'),write(Tree),
		term_string(Tree,String),
		interpret(String).

%%%%%%%%%%%%%%%%%%%%%%%
% Author: 	HerrAugust
% Source: 	https://github.com/HerrAugust/EserciziUni/tree/master/ArtificialIntelligence/hw6
% License: 	Opensource. This code is provided AS IS, WITHOUT ANY WORRANTY
%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%
% What the grammar allows
%%%%%%%%%%%%%%%%%%%%%%%
% Accepting assertions:
% 	1. is b on the table?
% 	2. is b on c?
% Accepting commands:
% 	1. Grasp block b
%	2. Put it onto the table (intended to be in combination with grasping command 1.)
%	3. Put it onto c (intended to be in combination with grasping command 1.)
%	4. Print state
%	5. Put a onto b (this is the command that needs Planner.pl)
% Accepting queries:
% 	1. Which blocks are on the table?
%	2. What color is b?
%%%%%%%%%%%%%%%%%%%%%%%

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
		term_string(Tree,String),
		interpret(String).

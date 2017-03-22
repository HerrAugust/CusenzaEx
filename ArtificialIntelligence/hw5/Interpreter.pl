:- 	consult('Knowledge.pl').

%%%%%%%%%%%%%%%%%%%%
% utility functions
%%%%%%%%%%%%%%%%%%%%

% extracts the arguments from a predicate.
% e.g., extract("on(b,a)","on(",Args). ---> Args=[b,,,a]. (",,," because
% "," are considered "anything else" by tokenize_atom() (see online doc for SWI Prolog), which expects spaces )
extract(From,PredName,Args) :- 	writeln(PredName),string_length(PredName,PredLen),sub_string(From, PredLen, _, 1, TempArgs), 
								writeln(TempArgs),tokenize_atom(TempArgs,Args), writeln(Args).

% instanciates a list of Atoms to some variables. Because this function is made to work with extract() (above),
% it checks if the token is a ',' (see tokenize_atom() documentation for more info).
% e.g., instanciate([b,,,c],[Obj,RelObj]). ---> Obj = b; RelObj = c.
instanciate([],L).
instanciate([H|ListToken], [J|ListVars]) :- H\==',',J=H,instanciate(ListToken,ListVars).
instanciate([H|ListToken], [J|ListVars]) :- H==',',instanciate(ListToken,[J|ListVars]).

%%%%%%%%%%%%%%%%%%%%
% Interpreter
%%%%%%%%%%%%%%%%%%%%

int_assertion(Tree) :-	term_string(Tree,String),
						writeln(String),
						extract(String,"on(",Args),
						writeln(''),write('Got question: '), write('on '), write(Args), write('?'),
						writeln(''), write('Answer: '),
						instanciate(Args,[Object,RelativeObject]),
						!, on(Object,RelativeObject). % the ! is needed if on(X,Y) is false, in order not to backtrack
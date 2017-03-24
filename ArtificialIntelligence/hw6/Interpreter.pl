:- 	consult('Knowledge.pl').

%%%%%%%%%%%%%%%%%%%%
% utility functions
%%%%%%%%%%%%%%%%%%%%

% extracts the arguments from a predicate.
% e.g., extract("on(b,a)","on(",Args). ---> Args=[b,,,a]. (",,," because
% "," are considered "anything else" by tokenize_atom() (see online doc for SWI Prolog), which expects spaces )
extract(From,PredName,Args) :- 	substring(PredName,From),writeln(PredName),string_length(PredName,PredLen),sub_string(From, PredLen, _, 1, TempArgs), 
								writeln(TempArgs),tokenize_atom(TempArgs,Args), writeln(Args).

% instanciates a list of Atoms to some variables. Because this function is made to work with extract() (above),
% it checks if the token is a ',' (see tokenize_atom() documentation for more info).
% e.g., instanciate([b,,,c],[Obj,RelObj]). ---> Obj = b; RelObj = c.
instanciate([],L).
instanciate([H|ListToken], [J|ListVars]) :- H\==',',J=H,instanciate(ListToken,ListVars).
instanciate([H|ListToken], [J|ListVars]) :- H==',',instanciate(ListToken,[J|ListVars]).

% retracts all the on(X,Object).
% e.g., cancelOn([a,b,c],b) = retract(on(a,b)),retract(on(b,b)),retract(on(c,b))
cancelOn([],Object).
cancelOn([H|List],Object) :- retract(on(Object,H)),assert(clear(H)),cancelOn(List,Object).

% true if X is substring of S.
substring(X,Y) :- forall(sub_atom(X,_,1,_,C), sub_atom(Y,_,1,_,C)).

%%%%%%%%%%%%%%%%%%%%
% Interpreter
%%%%%%%%%%%%%%%%%%%%

% Assertion: Is b on c?
interpret(Stringtree)   :- 	extract(Stringtree,"on(",Args),
							instanciate(Args,[Object,RelativeObject]),
							!, % the ! is needed if on(X,Y) is false, in order not to backtrack
							( on(Object,RelativeObject) -> ( writeln( 'Yes.') , fail ) ; writeln('No.') ).

% Query: Which blocks are on the table?
interpret(Stringtree)   :- 	extract(Stringtree,"blockson(",Args),
							instanciate(Args,[Object]),
							!,
							write("Blocks on it are: "),
							findall(X,on(X,Object),L),
							write_list(L).

% Query: What color is b?
interpret(Stringtree)   :- 	extract(Stringtree,"color(",Args),
							instanciate(Args,[Object]),
							!,
							write("The color is: "),
							color(Object,Color),
							write(Color).

% Command: Grasp b
interpret(Stringtree)   :- 	extract(Stringtree,"grasp(",Args),
							instanciate(Args,[Object]),
							!,
							( \+clear(Object) -> write('Cannot grasp it because the block is not on top'), fail ; write('') ),
							( \+holding(nothing) -> write('Cannot grasp it. Already grasping block '), holding(X), write(X), fail ; write('') ),
							retract(holding(nothing)),
							assert(holding(Object)),
							assert(lastgrasped(Object)),
							retract(clear(Object)),
							findall(X,on(Object,X),L), 		% block Object is no more on any block 
							cancelOn(L,Object),				% b is no more on any other block
							write('0K, holding '), holding(X), write(X).

% Command: Put it onto c/onto the table. This is in combination with grasp
interpret(Stringtree)   :- 	extract(Stringtree,"toplace(",Args),
							instanciate(Args,[RelativeObject]),
							!,
							( \+clear(RelativeObject) -> write('Sorry, '),write(RelativeObject), write(' is not on top'),fail; write('')),
							( holding(nothing) -> write('Sorry, grasping nothing'), fail ; write('') ),
							holding(Object),				% the block currently grasped
							retract(holding(Object)),		% grasping nothing
							assert(holding(nothing)),
							retract(lastgrasped(_)),
							assert(lastgrasped(nothing)),
							retract(clear(RelativeObject)),	% block Object is on top of c
							assert(clear(table)),			% table is always clear (needed for put it onto the table)
							assert(clear(Object)),
							assert(on(Object,RelativeObject)),
							write('0K, put '), write(Object), write(' on '), write(RelativeObject).

% Command: Print state
interpret(Stringtree)	:-	extract(Stringtree,"printstate(",DiscartedArgs),
							findall(X,block(X),LBlocks),
							write('blocks: '),write(LBlocks),
							findall([B,C],color(B,C),L),
							nl,write('colors: '),write_list(L),
							findall(X,clear(X),L1),
							nl,write('clear: '),write_list(L1),
							findall([X,Y],on(X,Y),L2),
							nl,write('on relations: '),write_list(L2),
							holding(X),
							nl,write('holding: '),write(X).


% If none of the previous attempts to interpret fail, show error message
interpret(_)			:- 	nl,writeln("Sorry, I do not understand what you say...").
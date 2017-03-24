:- 	consult('Knowledge.pl').

:- 	consult('Planner.pl').

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

% get current state of Blocks World
% e.g., if the state is the initial one, it returns [clear(b),clear(c),clear(table),block(b),block(c),block(a),on(b,a),on(b,table),on(c,table)]
getstate(State)							:-	findall(clear(X),clear(X),L1),findall(block(X),block(X),L2),append(L1,L2,ResL1),findall(on(X,Y),on(X,Y),L3),
											append(ResL1,L3,State).

% get state resulting from on(Object,RelativeObject).
% e.g., if the state is the initial one and Object=a,RelativeObject=b, then it returns this list (repetitions are possible):
% [clear(table),clear(b),clear(a),on(a,table),on(c,table),on(b,c),block(a),block(b),block(c)]
% and what the method does is:
% on(b,c) duable if clear(b),clear(c)
% on(b,c) implies clear(c),on(b,X) for each X are no more true; on(b,c),clear(b),clear(X) for each X,clear(table) become true
getstate(Object, RelativeObject, Final)	:- 	getstate(State),											% first, check if movement makes sense (admissible?)
											member(clear(Object),State),
											member(clear(RelativeObject),State),
											findall(on(Object,X),on(Object,X),Delete),					% compute new state
											findall(clear(X),on(Object,X),NewClear),
											append(Delete,[clear(RelativeObject)],NewDelete),
											subtract(State,NewDelete,Res),
											append(Res,NewClear,Res1),
											append(Res1,[on(Object,RelativeObject),clear(Object),clear(table)],Final).

% true if X is substring of S.
substring(X,Y) :- forall(sub_atom(X,_,1,_,C), sub_atom(Y,_,1,_,C)).

% turns result of Planner.pl into StepsEnglish
translateEnglish([],S).
translateEnglish([H|Steps],Eng)			:-	term_string(H,Str),
											extract(Stringtree,"move(",Args),
											instanciate(Args,[Block,FromOn,ToOn]),
											format(Output,'Move block ~w from ~w onto ~w.',Args),
											append(Eng,Output,Eng),
											translateEnglish(Steps,Eng).

translateEnglish([H|Steps],Eng)			:-	term_string(H,Str),
											extract(Stringtree,"moveToTable(",Args),
											instanciate(Args,[Block,FromOn]),
											format(Output,'Move block ~w from ~w onto the table.',Args),
											append(Eng,Output,Eng),
											translateEnglish(Steps,Eng).

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
interpret(Stringtree)	:-	extract(Stringtree,"printstate(",DiscartedArgs),	% check command
							!,
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

% Command: Put a onto b (this is the command that needs Planner.pl. Here is the culmination of AI for this homework).
% Notice that it does not modify the state of the Blocks world, it just returns the steps to reach that state!
interpret(Stringtree)	:-	extract(Stringtree,"putonto(",Args),
							instanciate(Args,[Object,RelativeObject]),
							!,
							getstate(Init),
							% write('Init: '),write_list(Init),
							getstate(Object,RelativeObject, Final),
							% write('Final:'),write_list(Final),
							solve(Init,Final,Steps),						% see Planner.pl
							translateEnglish(Steps,StepsEnglish),
							writeln('Steps:'),write_list(StepsEnglish).

% If none of the previous attempts to interpret fail, show error message
interpret(_)			:- 	nl,writeln("Sorry, I do not understand what you say...").
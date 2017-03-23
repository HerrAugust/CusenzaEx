%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Present in SWI-Prolog, it allows to use functions like append, and member for lists
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
use_module(library(lists)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Utility functions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

alldif([]).
alldif([E|Es]) 						:- maplist(dif(E), Es),alldif(Es).

apply([], State).
apply([H|Preconditions],State) 		:- member(H, State), apply(Preconditions,State).

find_missing([], To, Res).														% base case
find_missing([H|From],To,Res) 		:- member(H,To),find_missing(From,To,Res). 	% skip element
find_missing([H|From], To, [H|Res]) :- find_missing(From, To, Res). 			% add item H to Res

																				% naiverev() from "Learn Prolog Now!, http://www.learnprolognow.org/"
naiverev([],[]).
naiverev([H|T],R)					:- naiverev(T,RevT),  append(RevT,[H],R). 

write_list([]).
write_list([H|T]) 					:- writeln(H),write_list(T).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% algorithm for solution
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Possible actions for STRIPS problem. From book "Artificial Intelligence: A Modern Approach, 3rd Edition"
action(	move(B,X,Y),									% Name of action
		[block(B),block(Y),on(B,X),clear(B),clear(Y)], 	% Preconditions
		[on(B,Y),clear(X)],								% Effects
		[on(B,X),clear(Y)],								% Effects: things no more valid in State
		[B,X,Y] ).										% Variables used. Needed for alldif()

action( moveToTable(B,X),								% Name of action
		[on(B,X),clear(B),block(B),block(X)],					% Preconditions
		[on(B,table),clear(X)],							% Effects
		[on(B,X)],										% Effects: things no more valid in State
		[B,X] ).										% Variables used. Needed for alldif()



% impossibility cases
solve([], Goal, Steps). % no need to go to goal. It is impossible to achieve it
solve(Init, [], Steps). % no need to go to goal. It is impossible to achieve it

solve(State, Goal, Steps) :- 	apply(State,Goal),									% base case of recursion
								naiverev(Steps,StepsReverse),
								write_list(StepsReverse).
																					% given a (the current) state, a goal state and the list of steps that you are looking for:
solve(State, Goal, Steps) :-	action(Name, Preconditions, Effects, Old, Vars),	% take a possible action
								alldif(Vars),										% (if some variables are equal in action => assignment not correct)
								apply(Preconditions, State),						% if that preconditions apply to current state
								subtract(State, Effects, NewState),					% apply its effects (i.e., remove effects from state and add the new information)...
								subtract(NewState, Old, NewState2),
								find_missing(Effects, NewState2,Missing),
								append(NewState2, Missing,NewState3),
								subtract(NewState3, [clear(table)], NewState4),	 	% (otherwise "table" could be added with action 1, wrong)
								solve(NewState4,Goal,[Name|Steps]).					% ...and add the move into solution, which is Steps





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Main
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Steps expected: "move(c,table,a)"
ex1 :- solve(		[block(a),block(c),clear(c),on(c,table),clear(a),on(a,table)],
					[block(a),block(c),clear(a),on(a,c),on(c,table)],
					Steps),
					write_list(Steps).

% Steps expected: "moveToTable(b,a), move(a,table,b)"
ex2 :- solve(		[block(a),block(b),clear(b),on(a,table),on(b,a)],
					[block(a),block(b),clear(a),on(b,table),on(a,b)],
					Steps),
					write_list(Steps).

% Note: to make it run, write into console "ex1." or "ex2."

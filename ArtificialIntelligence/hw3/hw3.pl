%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Present in SWI-Prolog, it allows to use functions like append, and member for lists
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
use_module(library(lists)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Utility functions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
write_list([]).
write_list([H|T]) :- writeln(H),write_list(T).

find_missing([], To, Res).													% base case
find_missing([H|From],To,Res) :- member(H,To),find_missing(From,To,Res). 	% skip element
find_missing([H|From], To, [H|Res]) :- find_missing(From, To, Res). 		% add item H to Res

apply([], State).
apply([H|Preconditions],State) :- member(H, State), apply(Preconditions,State).

alldif([]).
alldif([E|Es]) :- maplist(dif(E), Es),alldif(Es).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% algorithm for solution
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% name of action, preconditions, effects, things no more valid
action(move(B,X,Y), [on(B,X),clear(B),clear(Y),block(B),block(Y)], [on(B,Y),clear(X)], [on(B,X),clear(Y)], [B,X,Y]).
%action(moveToTable(B,X), [on(B,X),clear(B),block(B)], [on(B,table),clear(X)], [on(B,X)]).

% impossibility cases
solve([], Goal, Steps). % no need to go to goal. It is impossible to achieve it
solve(Init, [], Steps). % no need to go to goal. It is impossible to achieve it

solve(Init, Goal, Steps) :- apply(Init,Goal),write_list(Steps).							% base case
																					% given a (the current) state, a goal state and the list of steps that you are looking for:
solve(State, Goal, Steps) :-	action(Name, Preconditions, Effects, Old, Vars),	% take a possible action
								alldif(Vars),										% (if some variables are equal in action => assignment not correct)
								apply(Preconditions, State),						% if that preconditions apply to current state
								subtract(State, Effects, NewState),					% apply its effects (i.e., remove effects from state and add the new information)...
								subtract(NewState, Old, NewState2),
								find_missing(Effects, NewState2,Missing),
								append(NewState2, Missing,NewState3),
								subtract(NewState3, [clear(table)], NewState4),	 	% (otherwise terra could be added with action 1, wrong)
								write_list(NewState4),nl,
								solve(NewState4,Goal,[Name|Steps]).					% ...and add the move into solution, which is Steps





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Main
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
main :- solve(	[block(a),block(c),clear(c),on(c,table),clear(a),on(a,table)],
				[block(a),block(c),clear(c),on(c,a),on(a,table)],
				Steps),
				write_list(Steps).

% Note: to make it run, write into console "main."
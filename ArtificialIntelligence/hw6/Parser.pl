%%%%%%%%%%%%%%%%%%%%%%%
% Accepting assertions:
% 	1. is b on the table?
% 	2. is b on c?
% Accepting commands:
% 	1. Grasp block b
%	2. Put it on the table
%	3. Put it on c
% Accepting queries:
% 	1. Which blocks are on the table?
%	2. What color is b?
%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%
% Assertions
%%%%%%%%%%%%%%%%%%%
s(A)											--> assertion(A).
assertion(on(S,P)) 		 						--> verb(_),subj(S),place(P),questionmark(_).
subj(B) 				 						--> block(B).
article(article(the))							--> [the].
blockname(a)									--> [a].
blockname(b)									--> [b].
blockname(c)									--> [c].
preposition(prep(on)) 							--> [on].
questionmark(questionmark(q))					--> [?].
verb(be)		 								--> [is].
word(table)		  								--> [table].
word(block)		 								--> [block].
block(B)		 								--> article(_),word(_),blockname(B). 	% the block a
block(B)		 								--> word(_),blockname(B). 				% block a
block(B) 										--> blockname(B).						% a
place(B)										--> preposition(_),block(B).
place(B)										--> preposition(_),fixplace(B). 		% there is only one fixplace: the table, so discart assignment
fixplace(table)									--> article(_),[table].

%%%%%%%%%%%%%%%%%%%
% Queries
%%%%%%%%%%%%%%%%%%%
s(Q)											--> query(Q).
% 1. Which blocks are on the table?
query(blockson(W))								--> which(WHICH),verb(_),place(W),questionmark(_).
which(which(W))									--> [which],([block];[blocks]). 		% notice AND and OR to force a certain sequence of words

% 2. What color is b?
query(color(B))									--> what(_),subj(B),questionmark(_).
what(what(W))									--> [what],[color],[is].

%%%%%%%%%%%%%%%%%%%
% Commands
%%%%%%%%%%%%%%%%%%%
s(C)											--> command(C).
% 1. Grasp block b
command(grasp(O))								--> [grasp],obj(O).
obj(O)											--> block(O).

% 2. Put it onto the table
command(toplace(C,TP))							--> [put],[it],toplace(TP).
toplace(FP)										--> [onto],fixplace(FP).

% 3. Put it onto c
toplace(B)										--> [onto],block(B).


% launch and make 	the query "s(T,[is,block,a,on,the,table,?],[])."
% or also 			the query "s(T,[is,block,a,on,the,block,c,?],[])."
% or an admissible sentence.

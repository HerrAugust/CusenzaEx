
s(Q)											--> assertion(Q).
assertion(on(S,P)) 		 						--> verb(_),subj(S),place(P),questionmark(_).
subj(B) 				 						--> block(B).
article(article(the))							--> [the].
blockname(a)									--> [a].
blockname(b)									--> [b].
blockname(c)									--> [c].
preposition(prep(on)) 							--> [on].
questionmark(questionmark(q))					--> [?].
verb(verb(be))	 								--> [is].
word(table)		  								--> [table].
word(block)		 								--> [block].
block(B)		 								--> article(_),word(_),blockname(B). 	% the block a
block(B)		 								--> word(_),blockname(B). 				% block a
block(B) 										--> blockname(B).						% a
place(B)										--> preposition(_),block(B).
place(B)										--> preposition(_),fixplace(B). 		% there is only one fixplace: the table, so discart assignment
fixplace(W)										--> article(_),word(W).
fixplace(W)										--> word(W).

% launch and make 	the query "s(T,[is,block,a,on,the,table,?],[])."
% or also 			the query "s(T,[is,block,a,on,the,block,c,?],[])."
% or an admissible sentence.

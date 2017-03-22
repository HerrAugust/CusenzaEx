% static knowledge: this knowledge will not change
block(a).
block(b).
block(c).

% dynamic knowledge (not used for this project): 
:- assert(on(b,a)).
:- assert(on(a,table)).
:- assert(clear(b)).
:- assert(on(c,table)).
:- assert(clear(c)).

% machine arm is holding nothing at the beginning (not used for this project)
:- assert(holding(nothing)).
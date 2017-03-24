% static knowledge: this knowledge will not change
block(a).
block(b).
block(c).
color(b, red).
color(a,green).
color(c, yellow).
clear(table).

% dynamic knowledge (not used for this project): 
:- assert(on(b,a)).
:- assert(on(a,table)).
:- assert(clear(b)).
:- assert(on(c,table)).
:- assert(clear(c)).
:- assert(lastgrasped(nothing)).

% machine arm is holding nothing at the beginning (not used for this project)
:- assert(holding(nothing)).
on(b,t).


% if you five
assert(on(b,t)).

% you are saying that you want to manipulate dynamically on(b,t)
% if you give
listing.
% prolog will return twice on(b,t)

% now give
retract(on(b,t)).
% listing will show an empty DB
listing.

%this means that if you want to use retract (i.e. remove from DB of facts), you must fist use assert
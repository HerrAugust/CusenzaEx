/*
Match strings in {0,1,+1,2,+2,...} between "(" and ")" and print the first digit.
Example: (+243) => 2
(41) => 4
(+78231321) => 7
(0) => 0 
*/


%{
#include <stdio.h>	
#include <ctype.h>
%}

%%
\([0-9]+\) {printf("%c", yytext[1]);}
\(\+[1-9]+\) { printf("%c", yytext[2]); }
%%

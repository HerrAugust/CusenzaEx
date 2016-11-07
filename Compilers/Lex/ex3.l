/*
Match strings in {0,+1,+2,...} between "(" and ")" and print the first digit.
Example:
(0) => 0
(+9875) => 9
(*2123) => 2
*/


%{
#include <stdio.h>	
#include <ctype.h>
%}

%%
\(0\) {printf("0");}
\(\+[1-9]+\) { printf("%c", yytext[2]); }
%%

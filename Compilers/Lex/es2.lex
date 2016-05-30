/*
Recognize sequences (also void) of digits fllowed by a sequence (not void) of letters with the condition that these sequences are separated by '?'.
Write the first letter found.
*/

%{
#include <stdio.h>	
%}

%%
[0-9]*"?"[a-zA-Z]+ { int i; for(i = 0; i < yyleng; i++) if(!isdigit(yytext[i]) && yytext[i] != '?') { printf("%c", yytext[i]); break; } }
%%

/*
Match the not-void sequence of vowels that can begin or not by digit. Write the first vowel.
*/


%{
#include <stdio.h>	
%}

%%
[0-9]?[aeiou]+ { if(isdigit(yytext[0])) printf("%c", yytext[1]); else printf("%c", yytext[0]); }
%%

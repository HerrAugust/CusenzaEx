/*
For grammar
S->(X)
X->X PIPPO
X->PIPPO
where S,X are non-terminal symbols (S is the initial one) and pippo and () are terminal (with pippo token for {a,b}),

write a YACC program that prints the amount of 'a' in input.

Example: for input (abaa) output: 3
*/

%{
#include <stdio.h>
#include <ctype.h>
int counter;
%}
%union {char tipo;}
%token <tipo> PIPPO
%start s
%%
s : '(' X ')' {printf("%d", counter); return 0;};
X : X PIPPO {if($2 =='a') counter++;};
X : PIPPO {if($1 == 'a') counter++;};
%%
yylex() {
	char c=getchar();
	if(c=='a' || c == 'b') {
		yylval.tipo = c;
		return (PIPPO);
	}
	else return c;
}

yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

main() {
	counter = 0;
	yyparse();
}

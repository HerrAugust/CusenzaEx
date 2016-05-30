/*
Scrivere del codice Lex per riconoscere una sequenza di cifre ottali
circondata da una coppia di parentesi quadrate da entrambi i lati.
*/

%{
	#include <stdio.h>
%}

%%
\[\[[0-7]*\]\] printf("%d", yyleng-4); /* Attenzione al -4 */
%%

/* Nota: Si ottiene un "premature EOF" da Lex se si inseriscono più spazi nella prima sezione. Mettere %} come sopra!
   Nota: Il %% finale è necessario! 
   */

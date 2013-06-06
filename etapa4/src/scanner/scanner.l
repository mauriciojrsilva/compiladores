%{
#include "../symbol.h"
#include "../tree/node.h"
#include "../parser/parser.hpp"

int numeroLinha = 1;
%}

%x COMM

letra [A-Za-z_]
digito [0-9]

%%
inteiro { return TK_PR_INTEIRO; }
flutuante { return TK_PR_FLUTUANTE; }
booleano { return TK_PR_BOOLEANO; }
caractere { return TK_PR_CARACTERE; }
cadeia { return TK_PR_CADEIA;	}
se { return TK_PR_SE; }
entao { return TK_PR_ENTAO;	}
senao { return TK_PR_SENAO;	}
enquanto { return TK_PR_ENQUANTO;	}
realiza { return TK_PR_REALIZA;	}
entrada { return TK_PR_ENTRADA;	}
saida { return TK_PR_SAIDA;	}
retorna { return TK_PR_RETORNA;	}

"verdadeiro" { yylval.symbol = new Symbol(yytext, LIT_BOOL); return TK_LIT_VERDADEIRO; }
"falso" { yylval.symbol = new Symbol(yytext, LIT_BOOL); return TK_LIT_FALSO; }

"<=" { return TK_OC_LE; }
">=" { return TK_OC_GE; }
"==" { return TK_OC_EQ; }
"!=" { return TK_OC_NE; }
"&&" { return TK_OC_AND; }
"||" { return TK_OC_OR; }

","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"*"|"/"|"<"|">"|"="|"!"|"&"|"$" { return yytext[0];	}

{letra}({letra}|{digito})* { yylval.symbol = new Symbol(yytext, IDENTIFIER); return TK_IDENTIFICADOR; }
{digito}+ { yylval.symbol = new Symbol(yytext, LIT_INTEGER); return TK_LIT_INTEIRO; }
{digito}+"."{digito}+ { yylval.symbol = new Symbol(yytext, LIT_FLOAT); return TK_LIT_FLUTUANTE; }
\'.\' { yylval.symbol = new Symbol(yytext, LIT_CHAR); return TK_LIT_CARACTERE; }
\"[^"]*\" { yylval.symbol = new Symbol(yytext, LIT_STRING); return TK_LIT_CADEIA; }

"//".* {}

"/*" { BEGIN(COMM); }
<COMM>"*/" { BEGIN(INITIAL); }
<COMM>"\n" { numeroLinha++; }
<COMM>.

\n { numeroLinha++; }
[ \t] { }
. { return TOKEN_ERRO; }

%%
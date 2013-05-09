%{
#include "hash.h"
#include "ast.h"
#include "parser.h"

int numeroLinha = 1;

#define K_SIMBOLO_INDEFINIDO 0
#define K_SIMBOLO_LITERAL_INTEIRO 1
#define K_SIMBOLO_LITERAL_FLUTUANTE 2
#define K_SIMBOLO_LITERAL_CARACTERE 3
#define K_SIMBOLO_LITERAL_CADEIA 4
#define K_SIMBOLO_LITERAL_IDENTIFICADOR 5

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

"verdadeiro" { return TK_LIT_VERDADEIRO; }
"falso" { return TK_LIT_FALSO; }

"<=" { return TK_OC_LE; }
">=" { return TK_OC_GE; }
"==" { return TK_OC_EQ; }
"!=" { return TK_OC_NE; }
"&&" { return TK_OC_AND; }
"||" { return TK_OC_OR; }

","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"*"|"/"|"<"|">"|"="|"!"|"&"|"$" { return yytext[0];	}

{letra}({letra}|{digito})* { hash_insert(K_SIMBOLO_LITERAL_IDENTIFICADOR, yytext); return TK_IDENTIFICADOR; }
{digito}+ { hash_insert(K_SIMBOLO_LITERAL_INTEIRO, yytext); /*printf("int: %s\n", yytext);*/ return TK_LIT_INTEIRO; }
{digito}+"."{digito}+ { hash_insert(K_SIMBOLO_LITERAL_FLUTUANTE, yytext); /*printf("float: %s\n", yytext);*/ return TK_LIT_FLUTUANTE; }
\'.\' { hash_insert(K_SIMBOLO_LITERAL_CARACTERE, yytext); return TK_LIT_CARACTERE; }
\"[^"]*\" { hash_insert(K_SIMBOLO_LITERAL_CADEIA, yytext); return TK_LIT_CADEIA; }

"//".* {}

"/*" { BEGIN(COMM); }
<COMM>"*/" { BEGIN(INITIAL); }
<COMM>"\n" { numeroLinha++; }
<COMM>.

\n { numeroLinha++; }
[ \t] { }
. { return TOKEN_ERRO; }

%%
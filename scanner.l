%{
#include "tokens.h"
#include "hash.c"

int numeroLinha = 1;

%}

%x COMM

letra                                                                           [A-Za-z_]
digito                                                                          [0-9]


%%
inteiro       																	{ return TK_PR_INTEIRO;   	}
flutuante     																	{ return TK_PR_FLUTUANTE; 	}
booleano      																	{ return TK_PR_BOOLEANO;  	}
caractere     																	{ return TK_PR_CARACTERE; 	}
cadeia        																	{ return TK_PR_CADEIA;    	}
se            																	{ return TK_PR_SE;        	}
entao         																	{ return TK_PR_ENTAO; 	  	}
senao         																	{ return TK_PR_SENAO; 	  	}
enquanto      																	{ return TK_PR_ENQUANTO;  	}
realiza       																	{ return TK_PR_REALIZA; 	}
entrada       																	{ return TK_PR_ENTRADA; 	}
saida         																	{ return TK_PR_SAIDA; 		}
retorna       																	{ return TK_PR_RETORNA; 	}

"verdadeiro"				                                                    { hash_insert(TK_LIT_VERDADEIRO, yytext);return TK_LIT_VERDADEIRO;}
"falso"				                                                            { hash_insert(TK_LIT_FALSO, yytext);return TK_LIT_FALSO;}

"<="          																	{ return TK_OC_LE;  		}
">="          																	{ return TK_OC_GE;  		}
"=="          																	{ return TK_OC_EQ;  		}
"!="          																	{ return TK_OC_NE;  		}
"&&"          																	{ return TK_OC_AND; 		}
"||"          																	{ return TK_OC_OR;  		}

","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"*"|"/"|"<"|">"|"="|"!"|"&"|"$"		{ return yytext[0];			}

{letra}({letra}|{digito})*														{ hash_insert(TK_IDENTIFICADOR, yytext); return TK_IDENTIFICADOR;  }
-?{digito}+																		{ hash_insert(TK_LIT_INTEIRO, yytext); return TK_LIT_INTEIRO;}
-?{digito}+"."{digito}+															{ hash_insert(TK_LIT_FLUTUANTE, yytext); return TK_LIT_FLUTUANTE;}
\'.\'																			{ hash_insert(TK_LIT_CARACTERE, yytext); return TK_LIT_CARACTERE;}
\"[^"]*\"																		{ hash_insert(TK_LIT_CADEIA, yytext); return TK_LIT_CADEIA;}

"//".*							                                                {}

"/*"							                                                { BEGIN(COMM);}
<COMM>"*/"						                                                { BEGIN(INITIAL);}
<COMM>"\n"						                                                { numeroLinha++;}
<COMM>.

\n								                                                { numeroLinha++;}
[ \t]							                                                {}
.								                                                { printf("Erro na linha %d: %s\n", numeroLinha, yytext); return TOKEN_ERRO;}

%%

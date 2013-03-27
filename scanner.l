%{
#include "tokens.h"
%}
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

"<="          																	{ return TK_OC_LE;  		}
">="          																	{ return TK_OC_GE;  		}
"=="          																	{ return TK_OC_EQ;  		}
"!="          																	{ return TK_OC_NE;  		}
"&&"          																	{ return TK_OC_AND; 		}
"||"          																	{ return TK_OC_OR;  		}

","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"*"|"/"|"<"|">"|"="|"!"|"&"|"$"		{ return yytext[0];			} 

[a-zA-Z][a-zA-Z0-9_]*															{ return TK_IDENTIFICADOR;  }         

" "           																	{ }
.             																	{ return TOKEN_ERRO;      	}
%%

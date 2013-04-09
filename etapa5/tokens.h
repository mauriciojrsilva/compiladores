/*
  tokens.h

  Lista dos tokens, com valores constantes associados.  Este arquivo
  será posterioremente substituído automaticamente. Portanto, não
  acrescente nada a ele, caso contrário seu analisador léxico não
  funcionará. Os valores das constantes são arbitrários, mas não podem
  ser alterados. Cada valor deve ser distinto e fora da escala ASCII.
  Assim, eles não entram em conflito entre si e com os tokens
  representados pelo próprio valor ASCII de caracteres isolados.
*/

/* Palavras Reservadas (PR) */
#define TK_PR_INTEIRO     256   /* inteiro   */
#define TK_PR_FLUTUANTE   257   /* flutuante */
#define TK_PR_BOOLEANO    258   /* booleano  */
#define TK_PR_CARACTERE   259   /* caractere */
#define TK_PR_CADEIA      260   /* cadeia    */
#define TK_PR_SE          261   /* se        */
#define TK_PR_ENTAO       262   /* entao     */
#define TK_PR_SENAO       263   /* senao     */
#define TK_PR_ENQUANTO    264   /* enquanto  */
#define TK_PR_REALIZA     265   /* realiza   */
#define TK_PR_ENTRADA     266   /* entrada   */
#define TK_PR_SAIDA       267   /* saida     */
#define TK_PR_RETORNA     268   /* retorna   */

/* Operadores Compostos (OC) */
#define TK_OC_LE    270   /* <=        */
#define TK_OC_GE    271   /* >=        */
#define TK_OC_EQ    272   /* ==        */
#define TK_OC_NE    273   /* !=        */
#define TK_OC_AND   274   /* &&        */
#define TK_OC_OR    275   /* ||        */

/* Literais (LIT) */
#define TK_LIT_INTEIRO    281
#define TK_LIT_FLUTUANTE  282
#define TK_LIT_FALSO      283
#define TK_LIT_VERDADEIRO 284
#define TK_LIT_CARACTERE  285
#define TK_LIT_CADEIA     286

/* Indentificador */
#define TK_IDENTIFICADOR  290

/* Erro */
#define TOKEN_ERRO        291

/* Fim de tokens.h */

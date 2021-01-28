#ifndef SPVM_YACC_UTIL_H
#define SPVM_YACC_UTIL_H

#include "spvm_typedef.h"

union SPVM_yystype
{
  SPVM_OP* opval;
};

#define YYSTYPE SPVM_YYSTYPE
#define YYPRINT(file, type, value) SPVM_yyprint(file, type, value)

extern int SPVM_yydebug;

int SPVM_yyparse(SPVM_COMPILER* compiler);
void SPVM_yyerror(SPVM_COMPILER* compiler, const char* s);
void SPVM_yyprint (FILE *file, int type, YYSTYPE yylval);

#endif

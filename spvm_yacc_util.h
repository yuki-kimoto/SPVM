#ifndef SPVM_YACC_H
#define SPVM_YACC_H

#include <stdio.h>
#include "spvm_base.h"

union SPVM_yystype
{
  SPVM_OP* opval;
};

#define YYSTYPE SPVM_YYSTYPE
#define YYPRINT(file, type, value) SPVM_yyprint(file, type, value)

extern int SPVM_yydebug;

int SPVM_yyparse(SPVM_COMPILER* compiler);
void SPVM_yyerror(SPVM_COMPILER* compiler, const char* s);
void SPVM_yyerror_format(SPVM_COMPILER* compiler, const char* message, ...);
void SPVM_yyprint (FILE *file, int type, YYSTYPE yylval);

#endif

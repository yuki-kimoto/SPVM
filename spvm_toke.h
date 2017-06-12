#ifndef SPVM_TOKE_H
#define SPVM_TOKE_H

#include "spvm_.h"

int SPVM_yylex(SPVM_YYSTYPE* yylvalp, SPVM_* spvm);
SPVM_OP* SPVM_TOKE_newOP(SPVM_* spvm, int32_t type);

#endif

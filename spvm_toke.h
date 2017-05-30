#ifndef SPVM_TOKE_H
#define SPVM_TOKE_H

#include "spvm.h"

int SPVM_yylex(SPVM_YYSTYPE* yylvalp, SPVM* spvm);
SPVM_OP* SPVM_TOKE_newOP(SPVM* spvm, int32_t type);

#endif

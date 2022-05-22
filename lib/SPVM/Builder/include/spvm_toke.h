#ifndef SPVM_TOKE_H
#define SPVM_TOKE_H

#include "spvm_typedecl.h"

enum {
  SPVM_TOKE_C_VAR_EXPANSION_STATE_DEFAULT,
  SPVM_TOKE_C_VAR_EXPANSION_STATE_FIRST_CONCAT,
  SPVM_TOKE_C_VAR_EXPANSION_STATE_VAR,
  SPVM_TOKE_C_VAR_EXPANSION_STATE_SECOND_CONCAT,
  SPVM_TOKE_C_VAR_EXPANSION_STATE_BEGIN_NEXT_STRING_LITERAL,
};

int SPVM_yylex(SPVM_YYSTYPE* yylvalp, SPVM_COMPILER* compiler);
SPVM_OP* SPVM_TOKE_newOP(SPVM_COMPILER* compiler, int32_t type);

#endif

#ifndef SPVM_TOKE_H
#define SPVM_TOKE_H



int SPVM_yylex(SPVM_YYSTYPE* yylvalp, SPVM_COMPILER* compiler);
SPVM_OP* SPVM_TOKE_newOP(SPVM_COMPILER* compiler, int32_t type);

#endif

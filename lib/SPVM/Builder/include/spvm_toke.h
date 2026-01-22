// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_TOKE_H
#define SPVM_TOKE_H

#include "spvm_typedecl.h"

enum {
  SPVM_TOKE_C_VAR_EXPANSION_STATE_NOT_STARTED,
  SPVM_TOKE_C_VAR_EXPANSION_STATE_FIRST_STRING_CONCAT,
  SPVM_TOKE_C_VAR_EXPANSION_STATE_VAR,
  SPVM_TOKE_C_VAR_EXPANSION_STATE_SECOND_STRING_CONCAT,
  SPVM_TOKE_C_VAR_EXPANSION_STATE_BEGIN_NEXT_STRING_LITERAL,
};

int SPVM_yylex(SPVM_YYSTYPE* yylvalp, SPVM_COMPILER* compiler);

void SPVM_TOKE_init_compiler_current_info(SPVM_COMPILER* compiler);

int32_t SPVM_TOKE_load_class_file(SPVM_COMPILER* compiler);

SPVM_OP* SPVM_TOKE_new_op(SPVM_COMPILER* compiler, int32_t type);

SPVM_OP* SPVM_TOKE_new_op_with_column(SPVM_COMPILER* compiler, int32_t type, int32_t column);

int32_t SPVM_TOKE_is_white_space(SPVM_COMPILER* compiler, char ch);

int32_t SPVM_TOKE_is_octal_number(SPVM_COMPILER* compiler, char ch);

int32_t SPVM_TOKE_is_hex_number(SPVM_COMPILER* compiler, char ch);

char SPVM_TOKE_parse_hex_escape(SPVM_COMPILER* compiler, char** char_ptr_ptr);

char SPVM_TOKE_parse_octal_escape(SPVM_COMPILER* compiler, char** char_ptr_ptr);

int32_t SPVM_TOKE_is_valid_utf8_code_point(int32_t code_point);

int32_t SPVM_TOKE_is_unicode_scalar_value(int32_t code_point);

int32_t SPVM_TOKE_convert_unicode_codepoint_to_utf8_character(int32_t uc, uint8_t* dst);

int32_t SPVM_TOKE_parse_line_terminator(SPVM_COMPILER* compiler, char** ch_ptr_ptr);

int32_t SPVM_TOKE_is_line_terminator(SPVM_COMPILER* compiler, char* ch);

void SPVM_TOKE_increment_current_line(SPVM_COMPILER* compiler);

int32_t SPVM_TOKE_isalpha_ascii(SPVM_COMPILER* compiler, int32_t ch);

int32_t SPVM_TOKE_isalnum_ascii(SPVM_COMPILER* compiler, int32_t ch);

int32_t SPVM_TOKE_isdigit_ascii(SPVM_COMPILER* compiler, int32_t ch);

int32_t SPVM_TOKE_islower_ascii(SPVM_COMPILER* compiler, int32_t ch);

int32_t SPVM_TOKE_isspace_ascii(SPVM_COMPILER* compiler, int32_t ch);

int32_t SPVM_TOKE_isprint_ascii(SPVM_COMPILER* compiler, int32_t ch);

#endif

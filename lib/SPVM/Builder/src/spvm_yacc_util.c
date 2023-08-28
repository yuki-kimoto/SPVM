// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>


#include "spvm_compiler.h"
#include "spvm_yacc_util.h"
#include "spvm_allocator.h"
#include "spvm_yacc.h"
#include "spvm_constant.h"
#include "spvm_var.h"
#include "spvm_op.h"
#include "spvm_type.h"
#include "spvm_basic_type.h"
#include "spvm_list.h"

// Print error
void SPVM_yyerror(SPVM_COMPILER* compiler, const char* message_not_used) {
  (void)compiler;
  
  // Current token
  int32_t length = 0;
  int32_t empty_count = 0;
  const char* ptr = compiler->token_begin_ch_ptr;
  while (ptr != compiler->ch_ptr) {
    if (*ptr == ' ' || *ptr == '\t' || *ptr == '\n') {
      empty_count++;
    }
    else {
      length++;
    }
    ptr++;
  }
  
  char* token = (char*) SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->current_each_compile_allocator, length + 1);
  memcpy(token, compiler->token_begin_ch_ptr + empty_count, length);
  token[length] = '\0';
  
  int32_t char_pos = (int32_t)(compiler->token_begin_ch_ptr + empty_count + 1 - compiler->line_begin_ch_ptr);
  
  SPVM_COMPILER_error(compiler, "Unexpected token \"%s\"\n  at %s line %d:%d", token, compiler->current_file, compiler->current_line, char_pos);

  SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, token);
}

// Print the token value in yacc/bison debug mode
void SPVM_yyprint (FILE *file, int type, YYSTYPE yylval) {
  
  switch(type) {
    case SYMBOL_NAME:
    case VAR_NAME:
    {
      const char* name = yylval.opval->uv.name;
      fprintf(file, "%s", name);
      break;
    }
  }
}

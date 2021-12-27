#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>


#include "spvm_compiler.h"
#include "spvm_yacc_util.h"
#include "spvm_compiler_allocator.h"
#include "spvm_yacc.h"
#include "spvm_constant.h"
#include "spvm_var.h"
#include "spvm_op.h"
#include "spvm_type.h"
#include "spvm_basic_type.h"

// Print error
void SPVM_yyerror(SPVM_COMPILER* compiler, const char* message) {
  (void)compiler;
  
  compiler->error_count++;
  
  // Current token
  int32_t length = 0;
  int32_t empty_count = 0;
  const char* ptr = compiler->befbufptr;
  while (ptr != compiler->bufptr) {
    if (*ptr == ' ' || *ptr == '\t' || *ptr == '\n') {
      empty_count++;
    }
    else {
      length++;
    }
    ptr++;
  }
  
  char* token = (char*) SPVM_COMPILER_ALLOCATOR_safe_malloc_zero_tmp(compiler, length + 1);
  memcpy(token, compiler->befbufptr + empty_count, length);
  token[length] = '\0';
  
  int32_t char_pos = (int32_t)(compiler->befbufptr + empty_count + 1 - compiler->line_start_ptr);
  
  fprintf(stderr, "[CompileError]Unexpected token \"%s\" at %s line %d:%d\n", token, compiler->cur_file, compiler->cur_line, char_pos);
  SPVM_COMPILER_ALLOCATOR_free_tmp(compiler, token);
}

// Print token value for debug
void SPVM_yyprint (FILE *file, int type, YYSTYPE yylval) {
  
  switch(type) {
    case NAME: {
      fprintf(file, "%s", yylval.opval->uv.name);
      break;
    }
    case VAR_NAME: {
      const char* var_name = yylval.opval->uv.name;
      fprintf(file, "%s", var_name);
      break;
    }
  }
}

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
  
  char* token = (char*) SPVM_ALLOCATOR_new_block_compile_tmp(compiler, length + 1);
  memcpy(token, compiler->befbufptr + empty_count, length);
  token[length] = '\0';
  
  int32_t char_pos = (int32_t)(compiler->befbufptr + empty_count + 1 - compiler->line_start_ptr);
  
  const char* error_format = "[CompileError]Unexpected token \"%s\" at %s line %d:%d\n";
  
  int32_t error_message_max_size = strlen(error_format) + strlen(token) + strlen(compiler->cur_file) + 30 + 30 + 1;
  
  fprintf(stderr, error_format, token, compiler->cur_file, compiler->cur_line, char_pos);
  
  char* message = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, error_message_max_size);
  sprintf(message, error_format, token, compiler->cur_file, compiler->cur_line, char_pos);
  
  SPVM_LIST_push(compiler->error_messages, message);

  SPVM_ALLOCATOR_free_block_compile_tmp(compiler, token);
}

// Print the token value in yacc/bison debug mode
void SPVM_yyprint (FILE *file, int type, YYSTYPE yylval) {
  
  switch(type) {
    case NAME:
    case VAR_NAME:
    {
      const char* name = yylval.opval->uv.name;
      fprintf(file, "%s", name);
      break;
    }
  }
}

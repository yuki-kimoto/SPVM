#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>


#include "spvm_compiler.h"
#include "spvm_yacc_util.h"
#include "spvm_compiler_allocator.h"
#include "spvm_util_allocator.h"
#include "spvm_yacc.h"
#include "spvm_constant.h"
#include "spvm_var.h"
#include "spvm_op.h"
#include "spvm_type.h"
#include "spvm_basic_type.h"

// Print error
void SPVM_yyerror(SPVM_COMPILER* compiler, const char* message)
{
  compiler->error_count++;
  
  // Current token
  const char* ptr = compiler->bufptr;
  char* line_start_ptr = compiler->bufptr_line_start;
  int32_t length = ptr - line_start_ptr + 1;
  
  char* near = (char*) SPVM_UTIL_ALLOCATOR_safe_malloc_zero(length + 1);
  memcpy(near, line_start_ptr, length);
  near[length] = '\0';
  
  fprintf(stderr, "Syntax error near\n%s at %s line %d\n", near, compiler->cur_file, compiler->cur_line);
  free(near);
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

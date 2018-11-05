#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
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

void SPVM_yyerror_format(SPVM_COMPILER* compiler, const char* message_template, ...) {
  
  int32_t message_length = 0;
  
  // Prefix
  const char* prefix = "Error:";
  int32_t prefix_length = (int32_t)strlen(prefix);
   
  // Message template
  int32_t message_template_length = (int32_t)strlen(message_template);
  
  // Messsage template with prefix
  int32_t message_template_with_prefix_length = prefix_length + message_template_length;
  char* message_template_with_prefix = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, message_template_with_prefix_length + 1);
  strncpy(message_template_with_prefix, prefix, prefix_length);
  strncpy(message_template_with_prefix + prefix_length, message_template, message_template_length);
  message_template_with_prefix[message_template_with_prefix_length] = '\0';
  message_length += message_template_with_prefix_length;
  
  va_list args;
  va_start(args, message_template);
  
  // Argument count
  char* found_ptr = message_template_with_prefix;
  while (1) {
    found_ptr = strchr(found_ptr, '%');
    if (found_ptr) {
      if (*(found_ptr + 1) == 's') {
        char* arg = va_arg(args, char*);
        message_length += strlen(arg);
      }
      else if (*(found_ptr + 1) == 'd') {
        (void) va_arg(args, int);
        message_length += 30;
      }
      else {
        fprintf(stderr, "Invalid arguments(SPVM_yyerror_format)\n");
        exit(EXIT_FAILURE);
      }
      found_ptr++;
    }
    else {
      break;
    }
  }
  va_end(args);
  
  char* message = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, message_length + 1);
  
  va_start(args, message_template);
  vsprintf(message, message_template_with_prefix, args);
  va_end(args);
  
  SPVM_yyerror(compiler, message);
}

// Print error
void SPVM_yyerror(SPVM_COMPILER* compiler, const char* message)
{
  compiler->error_count++;
  
  if (memcmp(message, "Error:", 6) == 0) {
    fprintf(stderr, "%s", message);
  }
  // Syntax structure error
  else {
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
    
    char* token = (char*) SPVM_UTIL_ALLOCATOR_safe_malloc_zero(length + 1);
    memcpy(token, compiler->befbufptr + empty_count, length);
    token[length] = '\0';
    
    fprintf(stderr, "Error: unexpected token \"%s\" at %s line %d\n", token, compiler->cur_file, compiler->cur_line);
    free(token);
  }
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

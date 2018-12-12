#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <inttypes.h>


#include "spvm_compiler.h"
#include "spvm_toke.h"
#include "spvm_yacc_util.h"
#include "spvm_yacc.h"
#include "spvm_op.h"
#include "spvm_compiler_allocator.h"
#include "spvm_util_allocator.h"
#include "spvm_constant.h"
#include "spvm_var.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_descriptor.h"
#include "spvm_type.h"
#include "spvm_use.h"
#include "spvm_basic_type.h"
#include "spvm_my.h"
#include "spvm_string_buffer.h"
#include "spvm_sub.h"
#include "spvm_package.h"

SPVM_OP* SPVM_TOKE_newOP(SPVM_COMPILER* compiler, int32_t type) {
  
  SPVM_OP* op = SPVM_OP_new_op(compiler, type, compiler->cur_file, compiler->cur_line);
  
  return op;
}

// Get token
int SPVM_yylex(SPVM_YYSTYPE* yylvalp, SPVM_COMPILER* compiler) {

  // Save buf pointer
  compiler->befbufptr = compiler->bufptr;

  // Constant minus sign
  int32_t minus = 0;
  
  // Expect sub name
  int32_t expect_sub_name = compiler->expect_sub_name;
  compiler->expect_sub_name = 0;
  
  // Before token is arrow
  int32_t before_token_is_arrow = compiler->before_token_is_arrow;
  compiler->before_token_is_arrow = 0;

  // Expect field name
  int32_t expect_field_name = compiler->expect_field_name;
  compiler->expect_field_name = 0;
  
  // Expect variable expansion state
  int32_t state_var_expansion = compiler->state_var_expansion;
  compiler->state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_DEFAULT;
  
  while(1) {
    // Get current character
    char ch = *compiler->bufptr;
    
    // Variable expansion state
    if (state_var_expansion == SPVM_TOKE_C_STATE_VAR_EXPANSION_FIRST_CONCAT) {
      ch = '.';
    }
    else if (state_var_expansion == SPVM_TOKE_C_STATE_VAR_EXPANSION_SECOND_CONCAT) {
      ch = '.';
    }
    else if (state_var_expansion == SPVM_TOKE_C_STATE_VAR_EXPANSION_DOUBLE_QUOTE) {
      ch = '"';
    }
    
    // line end
    switch (ch) {
      case '\0': {
        compiler->cur_file = NULL;
        compiler->cur_src = NULL;
        compiler->bufptr = NULL;
        compiler->befbufptr = NULL;
        
        // If there are more module, load it
        SPVM_LIST* op_use_stack = compiler->op_use_stack;
        
        while (1) {
          if (op_use_stack->length == 0) {
            return 0;
          }
          else if (op_use_stack->length > 0) {
            SPVM_OP* op_use = SPVM_LIST_shift(op_use_stack);
            
            const char* package_name = op_use->uv.use->op_type->uv.type->basic_type->name;
            
            SPVM_PACKAGE* found_package = SPVM_HASH_fetch(compiler->package_symtable, package_name, strlen(package_name));
            
            if (found_package) {
              continue;
            }
            else {
              // change :: to / and add ".spvm"
              int32_t module_path_base_length = (int32_t)(strlen(package_name) + 6);
              char* module_path_base = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, module_path_base_length + 1);
              const char* bufptr_orig = package_name;
              char* bufptr_to = module_path_base;
              while (*bufptr_orig) {
                if (*bufptr_orig == ':' && *(bufptr_orig + 1) == ':') {
                  *bufptr_to = '/';
                  bufptr_orig += 2;
                  bufptr_to++;
                }
                else {
                  *bufptr_to = *bufptr_orig;
                  bufptr_orig++;
                  bufptr_to++;
                }
              }
              strncpy(bufptr_to, ".spvm", 5);
              bufptr_to += 5;
              *bufptr_to = '\0';
              
              // Search module file
              char* cur_file = NULL;
              FILE* fh = NULL;
              int32_t module_include_pathes_length = compiler->module_include_pathes->length;
              {
                int32_t i;
                for (i = 0; i < module_include_pathes_length; i++) {
                  const char* include_path = (const char*) SPVM_LIST_fetch(compiler->module_include_pathes, i);
                  
                  // File name
                  int32_t file_name_length = (int32_t)(strlen(include_path) + 1 + strlen(module_path_base));
                  cur_file = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, file_name_length + 1);
                  sprintf(cur_file, "%s/%s", include_path, module_path_base);
                  cur_file[file_name_length] = '\0';
                  
                  // Open source file
                  fh = fopen(cur_file, "rb");
                  if (fh) {
                    compiler->cur_file = cur_file;
                    break;
                  }
                  errno = 0;
                }
              }
              if (!fh) {
                if (op_use->uv.use->is_require) {
                  op_use->uv.use->load_fail = 1;
                  SPVM_OP* op_package = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PACKAGE, op_use->file, op_use->line);
                  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
                  type->basic_type = op_use->uv.use->op_type->uv.type->basic_type;
                  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, op_use->file, op_use->line);
                  type->basic_type->fail_load = 1;
                  
                  SPVM_OP_build_package(compiler, op_package, op_type, NULL, NULL);
                  
                  continue;
                }
                else {
                  fprintf(stderr, "Can't locate %s in @INC (@INC contains:", module_path_base);
                  {
                    int32_t i;
                    for (i = 0; i < module_include_pathes_length; i++) {
                      const char* include_path = (const char*) SPVM_LIST_fetch(compiler->module_include_pathes, i);
                      fprintf(stderr, " %s", include_path);
                    }
                  }
                  fprintf(stderr, ") at %s line %d\n", op_use->file, op_use->line);
                  compiler->error_count++;
                  return 0;
                }
              }
              
              compiler->cur_file = cur_file;
              
              // Read file content
              fseek(fh, 0, SEEK_END);
              int32_t file_size = (int32_t)ftell(fh);
              if (file_size < 0) {
                SPVM_COMPILER_error(compiler, "Can't read file %s at %s line %d\n", cur_file, op_use->file, op_use->line);
                return 0;
              }
              fseek(fh, 0, SEEK_SET);
              char* cur_src = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, file_size + 1);
              if ((int32_t)fread(cur_src, 1, file_size, fh) < file_size) {
                SPVM_COMPILER_error(compiler, "Can't read file %s at %s line %d\n", cur_file, op_use->file, op_use->line);
                return 0;
              }
              fclose(fh);
              cur_src[file_size] = '\0';
              
              compiler->cur_src = cur_src;
              compiler->bufptr = cur_src;
              compiler->befbufptr = cur_src;
              compiler->cur_line = 1;
              break;
            }
          }
          else {
            assert(0);
          }
        }
        if (compiler->cur_src) {
          continue;
        }
        else {
          return 0;
        }
      }
      // Skip space character
      case ' ':
      case '\t':
      case '\r':
        compiler->bufptr++;
        continue;
      case '\n':
        compiler->bufptr++;
        compiler->cur_line++;
        continue;
      // Cancat
      case '.': {
        if (state_var_expansion == SPVM_TOKE_C_STATE_VAR_EXPANSION_FIRST_CONCAT) {
          compiler->state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_VAR;
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_CONCAT);
          return '.';
        }
        else if (state_var_expansion == SPVM_TOKE_C_STATE_VAR_EXPANSION_SECOND_CONCAT) {
          compiler->state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_DOUBLE_QUOTE;
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_CONCAT);
          return '.';
        }
        else {
          compiler->bufptr++;
          if (*compiler->bufptr == '=') {
            compiler->bufptr++;
            SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
            op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_CONCAT;
            
            yylvalp->opval = op_special_assign;
            
            return SPECIAL_ASSIGN;
          }
          else if (*compiler->bufptr == '.' && *(compiler->bufptr + 1) == '.') {
            compiler->bufptr += 2;
            yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_DOT3);
            return DOT3;
          }
          else {
            yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_CONCAT);
            return '.';
          }
        }
      }
      // Addition
      case '+':
        compiler->bufptr++;
        
        if (*compiler->bufptr == '+') {
          compiler->bufptr++;
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NULL);
          return INC;
        }
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_ADD;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NULL);
          return '+';
        }
      
      // Subtract
      case '-':
        compiler->bufptr++;
        
        // Decimal Literal or Floating point Literal allow minus
        if (
          isdigit(*compiler->bufptr)
          &&
          (
            (*compiler->bufptr != '0')
            || ((*compiler->bufptr == '0') && (*(compiler->bufptr + 1) == '.')))
          )
        {
          minus = 1;
          continue;
        }
        else if (*compiler->bufptr == '>') {
          compiler->bufptr++;
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NULL);
          compiler->expect_sub_name = 1;
          compiler->before_token_is_arrow = 1;
          
          return ARROW;
        }
        else if (*compiler->bufptr == '-') {
          compiler->bufptr++;
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NULL);
          return DEC;
        }
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_SUBTRACT;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NULL);;
          return '-';
        }
      // Multiply
      case '*': {
        compiler->bufptr++;
        
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MULTIPLY;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_MULTIPLY);
          yylvalp->opval = op;
          return MULTIPLY;
        }
      }
      // Divide
      case '/': {
        compiler->bufptr++;
        
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_DIVIDE;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_DIVIDE);
          yylvalp->opval = op;
          return DIVIDE;
        }
      }
      case '%': {
        compiler->bufptr++;
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_REMAINDER;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_REMAINDER);
          yylvalp->opval = op;
          return REMAINDER;
        }
      }
      case '^': {
        compiler->bufptr++;
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_XOR;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_BIT_XOR);
          yylvalp->opval = op;
          return BIT_XOR;
        }
      }
      case '|':
        compiler->bufptr++;
        // Or
        if (*compiler->bufptr == '|') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_OR);
          yylvalp->opval = op;
          return OR;
        }
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_OR;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_BIT_OR);
          yylvalp->opval = op;
          return BIT_OR;
        }

      case '&':
        compiler->bufptr++;
        // Or
        if (*compiler->bufptr == '&') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_AND);
          yylvalp->opval = op;
          return AND;
        }
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        // AMPERSAND - Bit and or type reference
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_BIT_AND);
          yylvalp->opval = op;
          return AMPERSAND;
        }
      
      // Comment
      case '#':
        compiler->bufptr++;
        while(1) {
          if (*compiler->bufptr == '\r' || *compiler->bufptr == '\n' || *compiler->bufptr == '\0') {
            break;
          }
          compiler->bufptr++;
        }
        
        continue;
      
      case '=':
        // Pod
        if (compiler->bufptr == compiler->cur_src || *(compiler->bufptr - 1) == '\n' || *(compiler->bufptr - 1) == '\r') {
          while (1) {
            compiler->bufptr++;
            if (*compiler->bufptr == '\n') {
              compiler->cur_line++;
            }
            
            if (*compiler->bufptr == '\0') {
              break;
            }
            
            if (
              *compiler->bufptr == '='
              && strncmp(compiler->bufptr + 1, "cut", 3) == 0
              && (*(compiler->bufptr + 4) == '\0' || isspace((int)*(compiler->bufptr + 4)))
            )
            {
              compiler->bufptr += 4;
              
              while (1) {
                if (*compiler->bufptr == '\r' || *compiler->bufptr == '\n' || *compiler->bufptr == '\0') {
                  break;
                }
                compiler->bufptr++;
              }
              break;
            }
          }
          continue;
        }
        else {
          compiler->bufptr++;
          
          // ==
          if (*compiler->bufptr == '=') {
            compiler->bufptr++;
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_EQ);
            yylvalp->opval = op;
            return REL;
          }
          // =>
          if (*compiler->bufptr == '>') {
            compiler->bufptr++;
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NULL);
            yylvalp->opval = op;
            return ',';
          }
          // =
          else {
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_ASSIGN);
            yylvalp->opval = op;
            return ASSIGN;
          }
        }
        
      case '<':
        compiler->bufptr++;
        
        if (*compiler->bufptr == '<') {
          compiler->bufptr++;
          // <<=
          if (*compiler->bufptr == '=') {
            compiler->bufptr++;
            SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
            op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_LEFT_SHIFT;
            
            yylvalp->opval = op_special_assign;
            
            return SPECIAL_ASSIGN;
          }
          // <<
          else {
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_LEFT_SHIFT);
            yylvalp->opval = op;
            return SHIFT;
          }
        }
        // <=
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_LE);
          yylvalp->opval = op;
          return REL;
        }
        // <
        else {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_LT);
          yylvalp->opval = op;
          return REL;
        }
      
      case '>':
        compiler->bufptr++;
        
        if (*compiler->bufptr == '>') {
          compiler->bufptr++;
          if (*compiler->bufptr == '>') {
            compiler->bufptr++;
            // >>>=
            if (*compiler->bufptr == '=') {
              compiler->bufptr++;
              SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
              op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT_UNSIGNED;
              
              yylvalp->opval = op_special_assign;
              
              return SPECIAL_ASSIGN;
            }
            // >>=
            else {
              SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_RIGHT_SHIFT_UNSIGNED);
              yylvalp->opval = op;
              return SHIFT;
            }
          }
          else {
            // >>=
            if (*compiler->bufptr == '=') {
              compiler->bufptr++;
              SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
              op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT;
              
              yylvalp->opval = op_special_assign;
              
              return SPECIAL_ASSIGN;
            }
            // >>
            else {
              SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_RIGHT_SHIFT);
              yylvalp->opval = op;
              return SHIFT;
            }
          }
        }
        // >=
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_GE);
          yylvalp->opval = op;
          return REL;
        }
        // >
        else {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_GT);
          yylvalp->opval = op;
          return REL;
        }
      case '!':
        compiler->bufptr++;
        
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NE);
          yylvalp->opval = op;
          return REL;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NOT);
          yylvalp->opval = op;
          return NOT;
        }
        
      case '~': {
        compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_COMPLEMENT);
          yylvalp->opval = op;
        return '~';
      }
      case '\'': {
        compiler->bufptr++;
        
        char ch;
        // Null string
        if (*compiler->bufptr == '\'') {
          ch = '\0';
          compiler->bufptr++;
        }
        // Escape sequence
        else {
          if (*compiler->bufptr == '\\') {
            compiler->bufptr++;
            if (*compiler->bufptr == 'r') {
              ch = 0x0D;
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 'n') {
              ch = 0x0A;
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 't') {
              ch = '\t';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 'b') {
              ch = '\b';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 'f') {
              ch = '\f';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == '0') {
              ch = '\0';
              compiler->bufptr++;
            }
            else {
              ch = *compiler->bufptr;
              compiler->bufptr++;
            }
          }
          else {
            ch = *compiler->bufptr;
            compiler->bufptr++;
          }
          
          if (*compiler->bufptr == '\'') {
            compiler->bufptr++;
          }
          else {
            SPVM_COMPILER_error(compiler, "Can't find constant char terminator \"'\" at %s line %d\n", compiler->cur_file, compiler->cur_line);
          }
        }
        
        // Constant 
        SPVM_OP* op_constant = SPVM_OP_new_op_constant_byte(compiler, ch, compiler->cur_file, compiler->cur_line);
        
        yylvalp->opval = op_constant;
        
        return CONSTANT;
      }
      case '"': {
        if (state_var_expansion == SPVM_TOKE_C_STATE_VAR_EXPANSION_DOUBLE_QUOTE) {
          // $var-> is invalid
          if (*compiler->bufptr == '-' && *(compiler->bufptr + 1) == '>') {
            SPVM_COMPILER_error(compiler, "Don't support variable expansion of array access or field access at %s line %d\n", compiler->cur_file, compiler->cur_line);
          }
        }
        else {
          compiler->bufptr++;
        }

        compiler->state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_DEFAULT;
        
        // Save current position
        const char* cur_token_ptr = compiler->bufptr;
        
        int8_t next_state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_DEFAULT;
        
        char* str;
        int32_t str_length = 0;
        if (*(compiler->bufptr) == '"') {
          str = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, 1);
          str[0] = '\0';
          compiler->bufptr++;
        }
        else {
          int32_t finish = 0;
          while(1) {
            // End of string literal
            if (*compiler->bufptr == '"' && *(compiler->bufptr - 1) != '\\') {
              finish = 1;
            }
            // Variable expansion
            else if (*compiler->bufptr == '$' && *(compiler->bufptr - 1) != '\\') {
              finish = 1;
              next_state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_FIRST_CONCAT;
            }
            // End of source file
            else if (*compiler->bufptr == '\0') {
              finish = 1;
            }
            if (finish) {
              break;
            }
            else {
              compiler->bufptr++;
            }
          }
          if (*compiler->bufptr == '\0') {
            SPVM_COMPILER_error(compiler, "Can't find string terminator '\"' anywhere before EOF at %s line %d\n", compiler->cur_file, compiler->cur_line);
            continue;
          }
          
          int32_t str_tmp_len = (int32_t)(compiler->bufptr - cur_token_ptr);

          compiler->bufptr++;
          
          str = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, str_tmp_len + 1);
          {
            char* char_ptr = (char*)cur_token_ptr;
            while (char_ptr != compiler->bufptr - 1) {
              if (*char_ptr == '\\') {
                char_ptr++;
                if (*char_ptr == 'r') {
                  str[str_length] = 0x0D;
                }
                else if (*char_ptr == 'n') {
                  str[str_length] = 0x0A;
                }
                else if (*char_ptr == 't') {
                  str[str_length] = '\t';
                }
                else if (*char_ptr == 'b') {
                  str[str_length] = '\b';
                }
                else if (*char_ptr == 'f') {
                  str[str_length] = '\f';
                }
                else if (*char_ptr == '0') {
                  str[str_length] = '\0';
                }
                else {
                  str[str_length] = *char_ptr;
                }
                str_length++;
              }
              else {
                str[str_length] = *char_ptr;
                str_length++;
              }
              char_ptr++;
            }
          }
          str[str_length] = '\0';
        }
        
        SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, str, str_length, compiler->cur_file, compiler->cur_line);
        
        yylvalp->opval = op_constant;
        
        // Next is start from $
        if (next_state_var_expansion == SPVM_TOKE_C_STATE_VAR_EXPANSION_FIRST_CONCAT) {
          compiler->state_var_expansion = next_state_var_expansion;
          compiler->bufptr--;
        }
        
        return CONSTANT;
      }
      case '\\':
        compiler->bufptr++;
        return REF;
      default:
        // Variable
        if (ch == '$') {
          // Derefernece
          if (*(compiler->bufptr + 1) == '$') {
            compiler->bufptr++;
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_DEREF);
            yylvalp->opval = op;
            return DEREF;
          }
          // Exception variable
          else if (*(compiler->bufptr + 1) == '@') {
            compiler->bufptr += 2;
            SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_EXCEPTION_VAR, compiler->cur_file, compiler->cur_line);
            yylvalp->opval = op_exception_var;
            return EXCEPTION_VAR;
          }
          // Lexical variable or Package variable
          else {
            compiler->bufptr++;

            int8_t have_brace = 0;
            
            if (*compiler->bufptr == '{') {
              have_brace = 1;
              compiler->bufptr++;
            }
            
            // Save current position
            const char* cur_token_ptr = compiler->bufptr;
            
            // Var name
            while (
              isalnum(*compiler->bufptr)
              || (*compiler->bufptr) == '_'
              || (*compiler->bufptr == ':' && *(compiler->bufptr + 1) == ':')
              || (*compiler->bufptr) == '@'
            )
            {
              if ((*compiler->bufptr == ':' && *(compiler->bufptr + 1) == ':')) {
                compiler->bufptr += 2;
              }
              else {
                compiler->bufptr++;
              }
            }
          

            int32_t var_name_length_without_sigil = compiler->bufptr - cur_token_ptr;
            char* var_name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, 1 + var_name_length_without_sigil + 1);
            var_name[0] = '$';
            memcpy(&var_name[1], cur_token_ptr, var_name_length_without_sigil);
            var_name[1 + var_name_length_without_sigil] = '\0';
            
            if (have_brace) {
              if (*compiler->bufptr == '}') {
                compiler->bufptr++;
              }
              else {
                SPVM_COMPILER_error(compiler, "Need close brace at end of variable at %s line %d\n", compiler->cur_file, compiler->cur_line);
              }
            }

            // Name OP
            SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, var_name, compiler->cur_file, compiler->cur_line);

            yylvalp->opval = op_name;
            
            // Variable expansion next state is double quote
            if (state_var_expansion == SPVM_TOKE_C_STATE_VAR_EXPANSION_VAR) {
              compiler->state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_SECOND_CONCAT;
            }
            
            // Package variable
            if (isupper(var_name[1]) || strstr(var_name, "::")) {
              return PACKAGE_VAR_NAME;
            }
            // Lexical variable
            else {
              return VAR_NAME;
            }
          }
        }
        // Number Literal
        else if (isdigit(ch)) {
          const char* cur_token_ptr;
          
          // Before character is minus
          if (minus) {
            cur_token_ptr = compiler->bufptr - 1;
            minus = 0;
          }
          else {
            cur_token_ptr = compiler->bufptr;
          }
          
          int32_t digit = 0;
          if (*(compiler->bufptr) == '0') {
            // Hex Literal
            if (*(compiler->bufptr + 1) == 'x' || *(compiler->bufptr + 1) == 'X') {
              cur_token_ptr = compiler->bufptr + 2;
              digit = 16;
            }
            // Binary Literal
            else if (*(compiler->bufptr + 1) == 'b' || *(compiler->bufptr + 1) == 'B') {
              cur_token_ptr = compiler->bufptr + 2;
              digit = 2;
            }
            // Octal Literal
            else if (isdigit(*(compiler->bufptr + 1))) {
              cur_token_ptr = compiler->bufptr + 1;
              digit = 8;
            }
          }
          // Decimal Literal
          else {
            digit = 10;
          }
          
          int32_t is_floating_number = 0;
          
          compiler->bufptr++;
          // Scan Hex number
          if (digit == 16) {
            compiler->bufptr += 2;
            while(
              isdigit(*compiler->bufptr)
              || *compiler->bufptr == 'a' || *compiler->bufptr == 'b' || *compiler->bufptr == 'c' || *compiler->bufptr == 'd' || *compiler->bufptr == 'e' || *compiler->bufptr == 'f'
              || *compiler->bufptr == 'A' || *compiler->bufptr == 'B' || *compiler->bufptr == 'C' || *compiler->bufptr == 'D' || *compiler->bufptr == 'E' || *compiler->bufptr == 'F'
              || *compiler->bufptr == '_'
            )
            {
              compiler->bufptr++;
            }
          }
          // Scan octal or binary number
          else if (digit == 8 || digit == 2) {
            compiler->bufptr += 1;
            while(
              isdigit(*compiler->bufptr)
              || *compiler->bufptr == '_'
            )
            {
              compiler->bufptr++;
            }
          }
          // Scan Floaing point number
          else {
            while(
              isdigit(*compiler->bufptr)
              || *compiler->bufptr == '.' || *compiler->bufptr == '-' || *compiler->bufptr == '+' || *compiler->bufptr == 'e' || *compiler->bufptr == 'E'
              || *compiler->bufptr == '_'
            )
            {
              if (*compiler->bufptr == '.' || *compiler->bufptr == 'e' || *compiler->bufptr == 'E') {
                is_floating_number = 1;
              }
              compiler->bufptr++;
            }
          }
          
          // First is space for + or -
          int32_t str_len = (compiler->bufptr - cur_token_ptr);
          
          char* num_str = (char*)SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, str_len + 2);
          {
            int32_t i;
            int32_t pos = 0;
            for (i = 0; i < str_len; i++) {
              if (*(cur_token_ptr + i) != '_') {
                *(num_str + pos) = *(cur_token_ptr + i);
                pos++;
              }
            }
            num_str[pos] = '\0';
          }
          
          // Constant
          SPVM_TYPE* constant_type;
          
          // long suffix
          if (*compiler->bufptr == 'l' || *compiler->bufptr == 'L')  {
            SPVM_OP* op_constant_type = SPVM_OP_new_op_long_type(compiler, compiler->cur_file, compiler->cur_line);
            constant_type = op_constant_type->uv.type;
            compiler->bufptr++;
          }
          // float suffix
          else if (*compiler->bufptr == 'f' || *compiler->bufptr == 'F')  {
            SPVM_OP* op_constant_type = SPVM_OP_new_op_float_type(compiler, compiler->cur_file, compiler->cur_line);
            constant_type = op_constant_type->uv.type;
            compiler->bufptr++;
          }
          // double suffix
          else if (*compiler->bufptr == 'd' || *compiler->bufptr == 'D')  {
            SPVM_OP* op_constant_type = SPVM_OP_new_op_double_type(compiler, compiler->cur_file, compiler->cur_line);
            constant_type = op_constant_type->uv.type;
            compiler->bufptr++;
          }
          // no suffix
          else {
            // floating point
            if (is_floating_number) {
              SPVM_OP* op_constant_type = SPVM_OP_new_op_double_type(compiler, compiler->cur_file, compiler->cur_line);
              constant_type = op_constant_type->uv.type;
            }
            // integer
            else {
              SPVM_OP* op_constant_type = SPVM_OP_new_op_int_type(compiler, compiler->cur_file, compiler->cur_line);
              constant_type = op_constant_type->uv.type;
            }
          }
          
          char *end;
          // Constant op
          SPVM_OP* op_constant;
          
          // float
          if (constant_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
            double num = strtof(num_str, &end);
            
            if (*end != '\0') {
              SPVM_COMPILER_error(compiler, "Invalid float literal at %s line %d\n", compiler->cur_file, compiler->cur_line);
            }
            op_constant = SPVM_OP_new_op_constant_float(compiler, (float)num, compiler->cur_file, compiler->cur_line);
          }
          // double
          else if (constant_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
            double num = strtod(num_str, &end);
            
            if (*end != '\0') {
              SPVM_COMPILER_error(compiler, "Invalid double literal at %s line %d\n", compiler->cur_file, compiler->cur_line);
            }
            op_constant = SPVM_OP_new_op_constant_double(compiler, num, compiler->cur_file, compiler->cur_line);
          }
          // int
          else if (constant_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
            int64_t num;
            errno = 0;
            int32_t out_of_range = 0;
            int32_t invalid = 0;
            
            if (digit == 16 || digit == 8 || digit == 2) {
              uint64_t unum = (uint64_t)strtoull(num_str, &end, digit);
              if (*end != '\0') {
                invalid = 1;
              }
              else if (unum > UINT32_MAX || errno == ERANGE) {
                out_of_range = 1;
              }
              num = (int64_t)unum;
            }
            else {
              num = (int64_t)strtoll(num_str, &end, 10);
              if (*end != '\0') {
                invalid = 1;
              }
              else if (num < INT32_MIN || num > INT32_MAX || errno == ERANGE) {
                out_of_range = 1;
              }
            }
            
            if (invalid) {
              SPVM_COMPILER_error(compiler, "Invalid int literal at %s line %d\n", compiler->cur_file, compiler->cur_line);
            }
            else if (out_of_range) {
              SPVM_COMPILER_error(compiler, "int literal out of range at %s line %d\n", compiler->cur_file, compiler->cur_line);
            }
            op_constant = SPVM_OP_new_op_constant_int(compiler, num, compiler->cur_file, compiler->cur_line);
          }
          // long
          else if (constant_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
            int64_t num;
            errno = 0;
            int32_t out_of_range = 0;
            int32_t invalid = 0;
            
            if (digit == 16 || digit == 8 || digit == 2) {
              uint64_t unum = (uint64_t)strtoull(num_str, &end, digit);
              if (*end != '\0') {
                invalid = 1;
              }
              else if (unum > UINT64_MAX || errno == ERANGE) {
                out_of_range = 1;
              }
              num = (int64_t)unum;
            }
            else {
              num = (int64_t)strtoll(num_str, &end, 10);
              if (*end != '\0') {
                invalid = 1;
              }
              else if (num < INT64_MIN || num > INT64_MAX || errno == ERANGE) {
                out_of_range = 1;
              }
            }
            
            if (invalid) {
              SPVM_COMPILER_error(compiler, "Invalid long literal at %s line %d\n", compiler->cur_file, compiler->cur_line);
            }
            else if (out_of_range) {
              SPVM_COMPILER_error(compiler, "long literal out of range at %s line %d\n", compiler->cur_file, compiler->cur_line);
            }
            op_constant = SPVM_OP_new_op_constant_long(compiler, num, compiler->cur_file, compiler->cur_line);
          }
          else {
            assert(0);
          }
          
          yylvalp->opval = op_constant;
          
          return CONSTANT;
        }
        // Keyword or name
        else if (isalpha(ch) || ch == '_') {
          // Save current position
          const char* cur_token_ptr = compiler->bufptr;
          
          compiler->bufptr++;
          
          // Go to end of name
          while(isalnum(*compiler->bufptr)
            || *compiler->bufptr == '_'
            || (*compiler->bufptr == ':' && *(compiler->bufptr + 1) == ':'))
          {
            if (*compiler->bufptr == ':' && *(compiler->bufptr + 1) == ':') {
              compiler->bufptr += 2;
            }
            else {
              compiler->bufptr++;
            }
          }
          
          
          char* keyword;
          int32_t str_len = (compiler->bufptr - cur_token_ptr);
          char* found_name = SPVM_HASH_fetch(compiler->name_symtable, cur_token_ptr, str_len);
          if (found_name) {
            keyword = found_name;
          }
          else {
            keyword = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, str_len + 1);
            memcpy(keyword, cur_token_ptr, str_len);
            keyword[str_len] = '\0';
            SPVM_HASH_insert(compiler->name_symtable, keyword, str_len, keyword);
          }
          
          if (expect_sub_name) {
            SPVM_LIST_push(compiler->current_sub_names, keyword);
          }
          else if (expect_field_name) {
            // None
          }
          else {
            switch (keyword[0]) {
              // Keyword
              case 'b' :
                if (strcmp(keyword, "byte") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_BYTE);
                  return BYTE;
                }
                break;
              case 'B' :
                if (strcmp(keyword, "BEGIN") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_BEGIN);
                  return BEGIN;
                }
                break;
              case 'c' :
                if (strcmp(keyword, "case") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_CASE);
                  return CASE;
                }
                else if (strcmp(keyword, "croak") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_CROAK);
                  return CROAK;
                }
                break;
              case 'd' :
                if (strcmp(keyword, "default") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_DEFAULT);
                  return DEFAULT;
                }
                else if (strcmp(keyword, "double") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_DOUBLE);
                  return DOUBLE;
                }
                break;
              case 'e' :
                if (strcmp(keyword, "elsif") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_ELSIF);
                  return ELSIF;
                }
                else if (strcmp(keyword, "else") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_ELSE);
                  return ELSE;
                }
                else if (strcmp(keyword, "enum") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_ENUM);
                  return ENUM;
                }
                else if (strcmp(keyword, "eq") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_EQ);
                  return REL;
                }
                else if (strcmp(keyword, "eval") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_EVAL);
                  return EVAL;
                }
                break;
              case 'f' :
                if (strcmp(keyword, "for") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_FOR);
                  return FOR;
                }
                else if (strcmp(keyword, "float") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_FLOAT);
                  return FLOAT;
                }
                break;
              case 'g' :
                if (strcmp(keyword, "gt") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_GT);
                  return REL;
                }
                else if (strcmp(keyword, "ge") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_GE);
                  return REL;
                }
                break;
              case 'h' :
                if (strcmp(keyword, "has") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_FIELD);
                  compiler->expect_field_name = 1;
                  return HAS;
                }
                break;
              case 'i' :
                if (strcmp(keyword, "if") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_IF);
                  return IF;
                }
                else if (strcmp(keyword, "interface") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_INTERFACE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  return DESCRIPTOR;
                }
                else if (strcmp(keyword, "isa") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_ISA);
                  return ISA;
                }
                else if (strcmp(keyword, "int") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_INT);
                  return INT;
                }
                break;
              case 'l' :
                if (strcmp(keyword, "last") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_LAST);
                  return LAST;
                }
                else if (strcmp(keyword, "length") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_LENGTH);
                  return LENGTH;
                }
                else if (strcmp(keyword, "lt") == 0) {
                  SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_LT);
                  yylvalp->opval = op;
                  
                  return REL;
                }
                else if (strcmp(keyword, "le") == 0) {
                  SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_LE);
                  yylvalp->opval = op;
                  
                  return REL;
                }
                else if (strcmp(keyword, "long") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_LONG);
                  return LONG;
                }
                break;
              case 'm' :
                if (strcmp(keyword, "my") == 0) {
                  SPVM_MY* my = SPVM_MY_new(compiler);
                  yylvalp->opval = SPVM_OP_new_op_my(compiler, my, compiler->cur_file, compiler->cur_line);
                  return MY;
                }
                break;
              case 'n' :
                if (strcmp(keyword, "native") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_NATIVE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  return DESCRIPTOR;
                }
                else if (strcmp(keyword, "ne") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_NE);
                  return REL;
                }
                else if (strcmp(keyword, "next") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NEXT);
                  return NEXT;
                }
                else if (strcmp(keyword, "new") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NEW);
                  return NEW;
                }
                break;
              case 'o' :
                if (strcmp(keyword, "our") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_PACKAGE_VAR);
                  return OUR;
                }
                else if (strcmp(keyword, "object") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_OBJECT);
                  return OBJECT;
                }
                break;
              case 'p' :
                if (strcmp(keyword, "package") == 0) {
                  
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_PACKAGE);
                  
                  return PACKAGE;
                }
                else if (strcmp(keyword, "private") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_PRIVATE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  return DESCRIPTOR;
                }
                else if (strcmp(keyword, "public") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_PUBLIC, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  return DESCRIPTOR;
                }
                else if (strcmp(keyword, "precompile") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_PRECOMPILE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  return DESCRIPTOR;
                }
                else if (strcmp(keyword, "pointer_t") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_POINTER_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  return DESCRIPTOR;
                }
                break;
              case 'r' :
                if (strcmp(keyword, "return") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_RETURN);
                  return RETURN;
                }
                else if (strcmp(keyword, "require") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_REQUIRE);
                  return REQUIRE;
                }
                else if (strcmp(keyword, "rw") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_RW, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  return DESCRIPTOR;
                }
                else if (strcmp(keyword, "ro") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_RO, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  return DESCRIPTOR;
                }
                break;
              case 's' :
                if (strcmp(keyword, "self") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SELF);
                  return SELF;
                }
                else if (strcmp(keyword, "switch") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SWITCH);
                  return SWITCH;
                }
                else if (strcmp(keyword, "sub") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SUB);
                  compiler->expect_sub_name = 1;
                  
                  return SUB;
                }
                else if (strcmp(keyword, "string") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING);
                  return STRING;
                }
                else if (strcmp(keyword, "short") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SHORT);
                  return SHORT;
                }
                else if (strcmp(keyword, "scalar") == 0) {
                  compiler->bufptr++;
                  SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SCALAR);
                  yylvalp->opval = op;
                  
                  return SCALAR;
                }
                break;
              case 'u' :
                if (strcmp(keyword, "undef") == 0) {
                  yylvalp->opval = SPVM_OP_new_op_undef(compiler, compiler->cur_file, compiler->cur_line);
                  return UNDEF;
                }
                else if (strcmp(keyword, "unless") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_UNLESS);
                  return UNLESS;
                }
                else if (strcmp(keyword, "use") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_USE);
                  return USE;
                }
                break;
              case 'v' :
                if (strcmp(keyword, "void") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_VOID);
                  return VOID;
                }
                else if (strcmp(keyword, "value_t") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_VALUE_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  return DESCRIPTOR;
                }
                break;
              case 'w' :
                if (strcmp(keyword, "while") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_WHILE);
                  return WHILE;
                }
                else if (strcmp(keyword, "weaken") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_WEAKEN);
                  return WEAKEN;
                }
                else if (strcmp(keyword, "wo") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_WO, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  return DESCRIPTOR;
                }
                break;
              case '_':
                if (strcmp(keyword, "__END__") == 0) {
                  *compiler->bufptr = '\0';
                  continue;
                }
                break;
            }
          }
          
          // Symbol name can't conatain __
          if (strstr(keyword, "__")) {
            SPVM_COMPILER_error(compiler, "Symbol name can't contain __ at %s line %d\n", compiler->cur_file, compiler->cur_line);
          }
          
          SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, keyword, compiler->cur_file, compiler->cur_line);
          yylvalp->opval = op_name;
          
          return NAME;
        }
        
        // Return character
        compiler->bufptr++;
        yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NULL);
        
        // Expect field name
        if (before_token_is_arrow && ch == '{') {
          compiler->expect_field_name = 1;
        }
        
        return (int) (uint8_t) ch;
    }
  }
}


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
#include "spvm_dynamic_array.h"
#include "spvm_hash.h"
#include "spvm_descriptor.h"
#include "spvm_type.h"
#include "spvm_use.h"
#include "spvm_constant_pool.h"

SPVM_OP* SPVM_TOKE_newOP(SPVM_COMPILER* compiler, int32_t type) {
  
  SPVM_OP* op = SPVM_OP_new_op(compiler, type, compiler->cur_file, compiler->cur_line);
  
  return op;
}

// Get token
int SPVM_yylex(SPVM_YYSTYPE* yylvalp, SPVM_COMPILER* compiler) {

  // Save buf pointer
  compiler->befbufptr = compiler->bufptr;
  _Bool before_is_comma = compiler->before_is_comma;
  compiler->before_is_comma = 0;

  _Bool before_is_package = compiler->before_is_package;
  compiler->before_is_package = 0;
  
  // Constant minus sign
  int32_t minus = 0;
  
  while(1) {
    // Get current character
    char c = *compiler->bufptr;
    
    // line end
    switch(c) {
      case '\0':
        compiler->cur_file = NULL;
        free(compiler->cur_src);
        compiler->cur_src = NULL;
        compiler->bufptr = NULL;
        compiler->befbufptr = NULL;
        
        // If there are more module, load it
        SPVM_DYNAMIC_ARRAY* op_use_stack = compiler->op_use_stack;
        
        while (1) {
          SPVM_OP* op_use = NULL;
          if (op_use_stack->length > 0) {
            op_use = SPVM_DYNAMIC_ARRAY_pop(op_use_stack);
          }
          
          if (op_use) {
            const char* package_name = op_use->uv.use->package_name;
            
            SPVM_OP* found_op_package = SPVM_HASH_search(compiler->op_package_symtable, package_name, strlen(package_name));
            
            if (found_op_package) {
              continue;
            }
            else {
              
              // Append "SPVM/", change :: to / and add ".spvm"
              int32_t module_path_base_length = (int32_t)(5 + strlen(package_name) + 6);
              char* module_path_base = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, module_path_base_length);
              const char* bufptr_orig = package_name;
              char* bufptr_to = module_path_base;
              strncpy(bufptr_to, "SPVM/", 5);
              bufptr_to += 5;
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
              int32_t include_pathes_length = compiler->include_pathes->length;
              {
                int32_t i;
                for (i = 0; i < include_pathes_length; i++) {
                  const char* include_path = (const char*) SPVM_DYNAMIC_ARRAY_fetch(compiler->include_pathes, i);
                  
                  // File name
                  int32_t file_name_length = (int32_t)(strlen(include_path) + 1 + strlen(module_path_base));
                  cur_file = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, file_name_length);
                  sprintf(cur_file, "%s/%s", include_path, module_path_base);
                  cur_file[file_name_length] = '\0';
                  
                  // Open source file
                  fh = fopen(cur_file, "r");
                  if (fh) {
                    compiler->cur_file = cur_file;
                    break;
                  }
                  errno = 0;
                }
              }
              if (!fh) {
                if (op_use) {
                  fprintf(stderr, "Can't locate %s in @INC (@INC contains:", module_path_base);
                  {
                    int32_t i;
                    for (i = 0; i < include_pathes_length; i++) {
                      const char* include_path = (const char*) SPVM_DYNAMIC_ARRAY_fetch(compiler->include_pathes, i);
                      fprintf(stderr, " %s", include_path);
                    }
                  }
                  fprintf(stderr, ") at %s line %" PRId32 "\n", op_use->file, op_use->line);
                }
                else {
                  fprintf(stderr, "Can't find file %s\n", cur_file);
                }
                exit(EXIT_FAILURE);
              }
              
              compiler->cur_file = cur_file;
              compiler->cur_package_name_with_template_args = op_use->uv.use->package_name_with_template_args;
              compiler->cur_op_use = op_use;
              
              
              // Read file content
              fseek(fh, 0, SEEK_END);
              int32_t file_size = (int32_t)ftell(fh);
              if (file_size < 0) {
                fprintf(stderr, "Can't read file %s at %s line %" PRId32 "\n", cur_file, op_use->file, op_use->line);
                exit(EXIT_FAILURE);
              }
              fseek(fh, 0, SEEK_SET);
              char* cur_src = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(file_size + 1);
              if ((int32_t)fread(cur_src, 1, file_size, fh) < file_size) {
                if (op_use) {
                  fprintf(stderr, "Can't read file %s at %s line %" PRId32 "\n", cur_file, op_use->file, op_use->line);
                }
                else {
                  fprintf(stderr, "Can't read file %s\n", cur_file);
                }
                exit(EXIT_FAILURE);
              }
              fclose(fh);
              cur_src[file_size] = '\0';
              
              // Add package loading information
              SPVM_CONSTANT_POOL_push_string(compiler, compiler->constant_pool, package_name);
              SPVM_CONSTANT_POOL_push_string(compiler, compiler->constant_pool, op_use->uv.use->package_name_with_template_args);
              const char* package_path = cur_file;
              SPVM_CONSTANT_POOL_push_string(compiler, compiler->constant_pool, package_path);
              SPVM_DYNAMIC_ARRAY_push(compiler->use_package_names, (void*)package_name);
              SPVM_HASH_insert(compiler->use_package_path_symtable, package_name, strlen(package_name), (void*)package_path);
              
              compiler->cur_src = cur_src;
              compiler->bufptr = cur_src;
              compiler->befbufptr = cur_src;
              compiler->current_package_count = 0;
              compiler->cur_line = 1;
              compiler->cur_template_args = op_use->uv.use->template_args;
              break;
            }
          }
          else {
            return 0;
          }
        }
        if (compiler->cur_src) {
          continue;
        }
        else {
          return 0;
        }
      
      /* Skip space character */
      case ' ':
      case '\t':
        compiler->bufptr++;
        continue;

      case '\n':
        compiler->bufptr++;
        compiler->cur_line++;
        continue;
      
      /* Cancat */
      case '.':
        compiler->bufptr++;
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_CONCAT_STRING;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_CONCAT_STRING);
          return '.';
        }
      
      /* Addition */
      case '+':
        compiler->bufptr++;
        
        if (*compiler->bufptr == '+') {
          compiler->bufptr++;
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NULL);
          return INC;
        }
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_ADD;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NULL);
          return '+';
        }
      
      /* Subtract */
      case '-':
        compiler->bufptr++;
        
        // 10 digit literal or floating point literal allow minus
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
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NULL);
          return ARROW;
        }
        else if (*compiler->bufptr == '-') {
          compiler->bufptr++;
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NULL);
          return DEC;
        }
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_SUBTRACT;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NULL);;
          return '-';
        }
      /* Multiply */
      case '*': {
        compiler->bufptr++;
        
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MULTIPLY;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_MULTIPLY);
          yylvalp->opval = op;
          return MULTIPLY;
        }
      }
      /* Divide */
      case '/': {
        compiler->bufptr++;
        
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_DIVIDE;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_DIVIDE);
          yylvalp->opval = op;
          return DIVIDE;
        }
      }
      case '%': {
        compiler->bufptr++;
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_REMAINDER;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_REMAINDER);
          yylvalp->opval = op;
          return REMAINDER;
        }
      }
      case '^': {
        compiler->bufptr++;
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_XOR;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_BIT_XOR);
          yylvalp->opval = op;
          return BIT_XOR;
        }
      }
      case '|':
        compiler->bufptr++;
        /* Or */
        if (*compiler->bufptr == '|') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_OR);
          yylvalp->opval = op;
          return OR;
        }
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_OR;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_BIT_OR);
          yylvalp->opval = op;
          return BIT_OR;
        }

      case '&':
        compiler->bufptr++;
        /* Or */
        if (*compiler->bufptr == '&') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_AND);
          yylvalp->opval = op;
          return AND;
        }
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        /* Bit and */
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_BIT_AND);
          yylvalp->opval = op;
          return BIT_AND;
        }
      
      /* Comment */
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
          
          /* == */
          if (*compiler->bufptr == '=') {
            compiler->bufptr++;
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_EQ);
            yylvalp->opval = op;
            return REL;
          }
          /* = */
          else {
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_ASSIGN);
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
            SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
            op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_LEFT_SHIFT;
            
            yylvalp->opval = op_special_assign;
            
            return SPECIAL_ASSIGN;
          }
          // <<
          else {
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_LEFT_SHIFT);
            yylvalp->opval = op;
            return SHIFT;
          }
        }
        // <=
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_LE);
          yylvalp->opval = op;
          return REL;
        }
        /* < */
        else {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_LT);
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
              SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
              op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT_UNSIGNED;
              
              yylvalp->opval = op_special_assign;
              
              return SPECIAL_ASSIGN;
            }
            // >>=
            else {
              SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_RIGHT_SHIFT_UNSIGNED);
              yylvalp->opval = op;
              return SHIFT;
            }
          }
          else {
            // >>=
            if (*compiler->bufptr == '=') {
              compiler->bufptr++;
              SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SPECIAL_ASSIGN);
              op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT;
              
              yylvalp->opval = op_special_assign;
              
              return SPECIAL_ASSIGN;
            }
            // >>
            else {
              SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_RIGHT_SHIFT);
              yylvalp->opval = op;
              return SHIFT;
            }
          }
        }
        /* >= */
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_GE);
          yylvalp->opval = op;
          return REL;
        }
        /* > */
        else {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_GT);
          yylvalp->opval = op;
          return REL;
        }
      case '!':
        compiler->bufptr++;
        
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NE);
          yylvalp->opval = op;
          return REL;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NOT);
          yylvalp->opval = op;
          return NOT;
        }
        
      case '~': {
        compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_COMPLEMENT);
          yylvalp->opval = op;
        return '~';
      }
      case '@': {
        compiler->bufptr++;
        SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_ARRAY_LENGTH);
        yylvalp->opval = op;
        
        return ARRAY_LENGTH;
      }
      case '\'': {
        compiler->bufptr++;
        
        int8_t ch;
        // Null string
        if (*compiler->bufptr == '\'') {
          ch = '\0';
          compiler->bufptr++;
        }
        // Escape sequence
        else {
          if (*compiler->bufptr == '\\') {
            compiler->bufptr++;
            if (*compiler->bufptr == '"') {
              ch = '"';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == '\'') {
              ch = '\'';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == '\\') {
              ch = '\\';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 'r') {
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
            else {
              fprintf(stderr, "Invalid escape character \"%c%c\" at %s line %" PRId32 "\n", *(compiler->bufptr -1),*compiler->bufptr, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
            }
          }
          else {
            ch = *compiler->bufptr;
            compiler->bufptr++;
          }
          
          if (*compiler->bufptr != '\'') {
            fprintf(stderr, "syntax error: character literal don't finish with '\n");
            exit(EXIT_FAILURE);
          }
          compiler->bufptr++;
        }
        
        // Constant 
        SPVM_OP* op_constant = SPVM_OP_new_op_constant_byte(compiler, ch, compiler->cur_file, compiler->cur_line);
        
        yylvalp->opval = op_constant;
        
        return CONSTANT;
      }
      case '"': {
        compiler->bufptr++;
        
        /* Save current position */
        const char* cur_token_ptr = compiler->bufptr;
        
        char* str;
        if (*(compiler->bufptr) == '"') {
          str = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, 0);
          str[0] = '\0';
          compiler->bufptr++;
        }
        else {
          _Bool finish = 0;
          while(1) {
            if (*compiler->bufptr == '"' && *(compiler->bufptr - 1) != '\\') {
              finish = 1;
            }
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
            fprintf(stderr, "syntax error: string don't finish with '\"'\n");
            exit(EXIT_FAILURE);
          }
          
          int32_t str_tmp_len = (int32_t)(compiler->bufptr - cur_token_ptr);
          
          char* str_tmp = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, str_tmp_len);
          memcpy(str_tmp, cur_token_ptr, str_tmp_len);
          str_tmp[str_tmp_len] = '\0';

          compiler->bufptr++;
          
          str = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, str_tmp_len);
          int32_t str_index = 0;
          {
            int32_t i;
            for (i = 0; i < str_tmp_len; i++) {
              if (str_tmp[i] == '\\') {
                i++;
                if (str_tmp[i] == '"') {
                  str[str_index] = '"';
                  str_index++;
                }
                else if (str_tmp[i] == '\'') {
                  str[str_index] = '\'';
                  str_index++;
                }
                else if (str_tmp[i] == '\\') {
                  str[str_index] = '\\';
                  str_index++;
                }
                else if (str_tmp[i] == 'r') {
                  str[str_index] = 0x0D;
                  str_index++;
                }
                else if (str_tmp[i] == 'n') {
                  str[str_index] = 0x0A;
                  str_index++;
                }
                else if (str_tmp[i] == 't') {
                  str[str_index] = '\t';
                  str_index++;
                }
                else if (str_tmp[i] == 'b') {
                  str[str_index] = '\b';
                  str_index++;
                }
                else if (str_tmp[i] == 'f') {
                  str[str_index] = '\f';
                  str_index++;
                }
                else {
                  fprintf(stderr, "Invalid escape character \"%c%c\" at %s line %" PRId32 "\n", *(compiler->bufptr -1),*compiler->bufptr, compiler->cur_file, compiler->cur_line);
                  exit(EXIT_FAILURE);
                }
              }
              else {
                str[str_index] = str_tmp[i];
                str_index++;
              }
            }
          }
          str[str_index] = '\0';
        }
        
        SPVM_OP* op_constant = SPVM_OP_new_op_constant_byte_array_string(compiler, str, compiler->cur_file, compiler->cur_line);
        
        yylvalp->opval = op_constant;
        
        return CONSTANT;
      }
      default:
        /* Variable */
        if (c == '$') {
          /* Save current position */
          const char* cur_token_ptr = compiler->bufptr;
          
          compiler->bufptr++;
          
          // Exception
          if (*compiler->bufptr == '@') {
            compiler->bufptr++;
            
            // Exception variable
            SPVM_OP* op_exception_var = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_EXCEPTION_VAR);
            yylvalp->opval = op_exception_var;
            
            return EXCEPTION_VAR;
          }
          // Lexical variable
          else {
            /* Next is graph */
            while(isalnum(*compiler->bufptr) || (*compiler->bufptr) == '_') {
              compiler->bufptr++;
            }
            
            int32_t str_len = (compiler->bufptr - cur_token_ptr);
            char* var_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, str_len);
            memcpy(var_name, cur_token_ptr, str_len);
            var_name[str_len] = '\0';

            // 
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_VAR);
            SPVM_VAR* var = SPVM_VAR_new(compiler);
            
            // Name OP
            SPVM_OP* op_name = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NAME);
            op_name->uv.name = var_name;
            
            var->op_name = op_name;
            
            op->uv.var = var;
            yylvalp->opval = op;
            
            return VAR;
          }
        }
        /* Number literal */
        else if (isdigit(c)) {
          const char* cur_token_ptr;
          
          // Before character is minus
          if (minus) {
            cur_token_ptr = compiler->bufptr - 1;
            minus = 0;
          }
          else {
            cur_token_ptr = compiler->bufptr;
          }
          
          // Digit
          int32_t digit = 0;
          if (*(compiler->bufptr) == '0') {
            if (*(compiler->bufptr + 1) == 'x') {
              cur_token_ptr = compiler->bufptr + 2;
              digit = 16;
            }
            else if (*(compiler->bufptr + 1) == 'b') {
              cur_token_ptr = compiler->bufptr + 2;
              digit = 2;
            }
            else if (isdigit(*(compiler->bufptr + 1))) {
              cur_token_ptr = compiler->bufptr + 1;
              digit = 8;
            }
          }
          else {
            digit = 10;
          }
          
          _Bool is_floating_number = 0;
          
          compiler->bufptr++;
          // Scan number
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
          
          // Number literal(first is space for sign)
          int32_t str_len = (compiler->bufptr - cur_token_ptr);
          char* num_str = (char*) SPVM_UTIL_ALLOCATOR_safe_malloc_zero(str_len + 2);
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
          
          if (*compiler->bufptr == 'y')  {
            constant_type = SPVM_TYPE_get_byte_type(compiler);
            compiler->bufptr++;
          }
          else if (*compiler->bufptr == 's')  {
            constant_type = SPVM_TYPE_get_short_type(compiler);
            compiler->bufptr++;
          }
          else if (*compiler->bufptr == 'L')  {
            constant_type = SPVM_TYPE_get_long_type(compiler);
            compiler->bufptr++;
          }
          else if (*compiler->bufptr == 'f')  {
            constant_type = SPVM_TYPE_get_float_type(compiler);
            compiler->bufptr++;
          }
          else if (*compiler->bufptr == 'd')  {
            constant_type = SPVM_TYPE_get_double_type(compiler);
            compiler->bufptr++;
          }
          else {
            if (is_floating_number) {
              constant_type = SPVM_TYPE_get_double_type(compiler);
            }
            else {
              constant_type = SPVM_TYPE_get_int_type(compiler);
            }
          }
          
          // float
          char *end;
          // Constant op
          SPVM_OP* op_constant;
          
          if (constant_type->code == SPVM_TYPE_C_CODE_FLOAT) {
            double num = strtod(num_str, &end);
            
            if (*end != '\0') {
              fprintf(stderr, "Invalid float literal %s at %s line %" PRId32 "\n", num_str, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
            }
            op_constant = SPVM_OP_new_op_constant_float(compiler, (float)num, compiler->cur_file, compiler->cur_line);
          }
          // double
          else if (constant_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
            double num = strtod(num_str, &end);
            
            if (*end != '\0') {
              fprintf(stderr, "Invalid double literal %s at %s line %" PRId32 "\n", num_str, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
            }
            op_constant = SPVM_OP_new_op_constant_double(compiler, num, compiler->cur_file, compiler->cur_line);
          }
          // byte
          else if (constant_type->code == SPVM_TYPE_C_CODE_BYTE) {
            int64_t num;
            errno = 0;
            _Bool out_of_range = 0;
            _Bool invalid = 0;
            
            if (digit == 16 || digit == 8 || digit == 2) {
              uint64_t unum = (uint64_t)strtoull(num_str, &end, digit);
              if (*end != '\0') {
                invalid = 1;
              }
              else if (unum > UINT8_MAX || errno == ERANGE) {
                out_of_range = 1;
              }
              num = (int64_t)unum;
            }
            else {
              num = (int64_t)strtoll(num_str, &end, 10);
              if (*end != '\0') {
                invalid = 1;
              }
              else if (num < INT8_MIN || num > INT8_MAX || errno == ERANGE) {
                out_of_range = 1;
              }
            }
            
            if (invalid) {
              fprintf(stderr, "Invalid byte literal %s at %s line %" PRId32 "\n", num_str, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
            }
            else if (out_of_range) {
              fprintf(stderr, "byte literal out of range %s at %s line %" PRId32 "\n", num_str, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
            }
            op_constant = SPVM_OP_new_op_constant_byte(compiler, num, compiler->cur_file, compiler->cur_line);
          }
          // short
          else if (constant_type->code == SPVM_TYPE_C_CODE_SHORT) {
            int64_t num;
            errno = 0;
            _Bool out_of_range = 0;
            _Bool invalid = 0;
            
            if (digit == 16 || digit == 8 || digit == 2) {
              uint64_t unum = (uint64_t)strtoull(num_str, &end, digit);
              if (*end != '\0') {
                invalid = 1;
              }
              else if (unum > UINT16_MAX || errno == ERANGE) {
                out_of_range = 1;
              }
              num = (int64_t)unum;
            }
            else {
              num = (int64_t)strtoll(num_str, &end, 10);
              if (*end != '\0') {
                invalid = 1;
              }
              else if (num < INT16_MIN || num > INT16_MAX || errno == ERANGE) {
                out_of_range = 1;
              }
            }
            
            if (invalid) {
              fprintf(stderr, "Invalid short literal %s at %s line %" PRId32 "\n", num_str, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
            }
            else if (out_of_range) {
              fprintf(stderr, "short literal out of range %s at %s line %" PRId32 "\n", num_str, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
            }
            op_constant = SPVM_OP_new_op_constant_short(compiler, num, compiler->cur_file, compiler->cur_line);
          }
          // int
          else if (constant_type->code == SPVM_TYPE_C_CODE_INT) {
            int64_t num;
            errno = 0;
            _Bool out_of_range = 0;
            _Bool invalid = 0;
            
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
              fprintf(stderr, "Invalid int literal %s at %s line %" PRId32 "\n", num_str, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
            }
            else if (out_of_range) {
              fprintf(stderr, "int literal out of range %s at %s line %" PRId32 "\n", num_str, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
            }
            op_constant = SPVM_OP_new_op_constant_int(compiler, num, compiler->cur_file, compiler->cur_line);
          }
          // long
          else if (constant_type->code == SPVM_TYPE_C_CODE_LONG) {
            int64_t num;
            errno = 0;
            _Bool out_of_range = 0;
            _Bool invalid = 0;
            
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
              fprintf(stderr, "Invalid long literal %s at %s line %" PRId32 "\n", num_str, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
            }
            else if (out_of_range) {
              fprintf(stderr, "long literal out of range %s at %s line %" PRId32 "\n", num_str, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
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
        else if (isalpha(c) || c == '_') {
          // Save current position
          const char* cur_token_ptr = compiler->bufptr;
          
          compiler->bufptr++;
          
          _Bool has_double_underline = 0;
          while(isalnum(*compiler->bufptr)
            || *compiler->bufptr == '_'
            || (*compiler->bufptr == ':' && *(compiler->bufptr + 1) == ':'))
          {
            if (*compiler->bufptr == ':' && *(compiler->bufptr + 1) == ':') {
              compiler->bufptr += 2;
            }
            else if (*compiler->bufptr == '_' && *(compiler->bufptr + 1) == '_') {
              has_double_underline = 1;
              compiler->bufptr += 2;
            }
            else {
              compiler->bufptr++;
            }
          }
          
          
          int32_t str_len = (compiler->bufptr - cur_token_ptr);
          char* keyword = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, str_len);
          
          memcpy(keyword, cur_token_ptr, str_len);
          keyword[str_len] = '\0';
          
          char* original_keyword = keyword;
          
          // Replace template variable
          const char* found_template_var = strstr(keyword, "type");
          if (found_template_var) {
            if (isdigit(found_template_var[4])) {
              SPVM_DYNAMIC_ARRAY* part_names = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
              
              char* base_ptr = keyword;
              char* cur_ptr = keyword;
              
              while (1) {
                if (*cur_ptr == '_' || *cur_ptr == '\0') {
                  int32_t length = (int32_t)(cur_ptr - base_ptr);
                  char* part_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, length);
                  memcpy(part_name, base_ptr, length);
                  part_name[length] = '\0';
                  SPVM_DYNAMIC_ARRAY_push(part_names, part_name);
                  if (*cur_ptr == '\0') {
                    break;
                  }
                  cur_ptr++;
                  base_ptr = cur_ptr;
                }
                else {
                  cur_ptr++;
                }
              }
              
              SPVM_DYNAMIC_ARRAY* replaced_part_names = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
              int32_t replaced_part_names_length = 0;
              {
                int32_t i;
                for (i = 0; i < part_names->length; i++) {
                  char* part_name = SPVM_DYNAMIC_ARRAY_fetch(part_names, i);
                  if (strncmp(part_name, "type", 4) == 0 && isdigit(part_name[4])) {
                    int32_t template_args_index;
                    errno = 0;
                    char *end;
                    template_args_index = strtol(&part_name[4], &end, 10);
                    if (*end != '\0') {
                      fprintf(stderr, "Invalid template variable %s at %s line %" PRId32 "\n", &part_name[4], compiler->cur_file, compiler->cur_line);
                      exit(EXIT_FAILURE);
                    }
                    else if (template_args_index == 0 || template_args_index > compiler->cur_template_args->length) {
                      fprintf(stderr, "Invalid template variable, Index out of range %s at %s line %" PRId32 "\n", part_name, compiler->cur_file, compiler->cur_line);
                      exit(EXIT_FAILURE);
                    }
                    
                    char* replaced_part_name = SPVM_DYNAMIC_ARRAY_fetch(compiler->cur_template_args, template_args_index - 1);
                    SPVM_DYNAMIC_ARRAY_push(replaced_part_names, replaced_part_name);
                    replaced_part_names_length += strlen(replaced_part_name);
                  }
                  else {
                    SPVM_DYNAMIC_ARRAY_push(replaced_part_names, part_name);
                    replaced_part_names_length += strlen(part_name);
                  }
                  // _
                  if (i != part_names->length - 1) {
                    replaced_part_names_length += 1;
                  }
                }
              }
              
              char* replaced_keyword = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, replaced_part_names_length);
              {
                int32_t i;
                char* base_ptr = replaced_keyword;
                for (i = 0; i < replaced_part_names->length; i++) {
                  const char* replaced_part_name = SPVM_DYNAMIC_ARRAY_fetch(replaced_part_names, i);
                  memcpy(base_ptr, replaced_part_name, strlen(replaced_part_name));
                  base_ptr += strlen(replaced_part_name);
                  if (i != replaced_part_names->length - 1) {
                    *base_ptr = '_';
                    base_ptr++;
                  }
                }
                replaced_keyword[replaced_part_names_length] = '\0';
              }
              keyword = replaced_keyword;
            }
          }
          
          switch (keyword[0]) {
            // Keyword
            case 'b' :
              if (strcmp(keyword, "byte") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_BYTE);
                return BYTE;
              }
              break;
            case 'c' :
              if (strcmp(keyword, "case") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_CASE);
                return CASE;
              }
              else if (strcmp(keyword, "const") == 0) {
                SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_DESCRIPTOR);
                op->code = SPVM_DESCRIPTOR_C_CODE_CONST;
                yylvalp->opval = op;
                
                return DESCRIPTOR;
              }
              break;
            case 'd' :
              if (strcmp(keyword, "default") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_DEFAULT);
                return DEFAULT;
              }
              else if (strcmp(keyword, "die") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_DIE);
                return DIE;
              }
              else if (strcmp(keyword, "double") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_DOUBLE);
                return DOUBLE;
              }
              break;
            case 'e' :
              if (strcmp(keyword, "elsif") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_ELSIF);
                return ELSIF;
              }
              else if (strcmp(keyword, "else") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_ELSE);
                return ELSE;
              }
              else if (strcmp(keyword, "enum") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_ENUM);
                return ENUM;
              }
              else if (strcmp(keyword, "eval") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_EVAL);
                return EVAL;
              }
              break;
            case 'f' :
              if (strcmp(keyword, "for") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_FOR);
                return FOR;
              }
              else if (strcmp(keyword, "float") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_FLOAT);
                return FLOAT;
              }
              break;
            case 'h' :
              if (strcmp(keyword, "has") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_FIELD);
                return HAS;
              }
              break;
            case 'i' :
              if (strcmp(keyword, "if") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_IF);
                return IF;
              }
              else if (strcmp(keyword, "int") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_INT);
                return INT;
              }
              break;
            case 'l' :
              if (strcmp(keyword, "last") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_LAST);
                return LAST;
              }
              else if (strcmp(keyword, "len") == 0) {
                compiler->bufptr++;
                SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_ARRAY_LENGTH);
                yylvalp->opval = op;
                
                return ARRAY_LENGTH;
              }
              else if (strcmp(keyword, "long") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_LONG);
                return LONG;
              }
              break;
              break;
            case 'm' :
              if (strcmp(keyword, "my") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_MY);
                return MY;
              }
              break;
            case 'n' :
              if (strcmp(keyword, "native") == 0) {
                SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_DESCRIPTOR);
                op->code = SPVM_DESCRIPTOR_C_CODE_NATIVE;
                yylvalp->opval = op;
                
                return DESCRIPTOR;
              }
              else if (strcmp(keyword, "next") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NEXT);
                return NEXT;
              }
              else if (strcmp(keyword, "new") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NEW);
                return NEW;
              }
              break;
            case 'p' :
              if (strcmp(keyword, "package") == 0) {
                // File can contains only one package
                if (compiler->current_package_count) {
                  fprintf(stderr, "Can't write second package declaration in file at %s line %" PRId32 "\n", compiler->cur_file, compiler->cur_line);
                  exit(EXIT_FAILURE);
                }
                compiler->current_package_count++;
                
                compiler->before_is_package = 1;
                
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_PACKAGE);
                return PACKAGE;
              }
              break;
            case 'r' :
              if (strcmp(keyword, "return") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_RETURN);
                return RETURN;
              }
              break;
            case 's' :
              if (strcmp(keyword, "switch") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SWITCH);
                return SWITCH;
              }
              else if (strcmp(keyword, "sub") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SUB);
                return SUB;
              }
              else if (strcmp(keyword, "short") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_SHORT);
                return SHORT;
              }
              else if (strcmp(keyword, "string") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_STRING);
                return STRING;
              }
              break;
            case 'u' :
              if (strcmp(keyword, "undef") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_UNDEF);
                return UNDEF;
              }
              else if (strcmp(keyword, "use") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_USE);
                return USE;
              }
              break;
            case 'v' :
              if (strcmp(keyword, "void") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_VOID);
                return VOID;
              }
              break;
            case 'w' :
              if (strcmp(keyword, "while") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_WHILE);
                return WHILE;
              }
              else if (strcmp(keyword, "weaken") == 0) {
                yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_WEAKEN);
                return WEAKEN;
              }
              break;
            case '_':
              if (strcmp(keyword, "__END__") == 0) {
                *compiler->bufptr = '\0';
                continue;
              }
              break;
          }
          
          if (has_double_underline) {
            fprintf(stderr, "Can't contain __ in package, subroutine or field name at %s line %" PRId32 "\n", compiler->cur_file, compiler->cur_line);
            exit(EXIT_FAILURE);
          }
          
          // Package name must be same as use package name
          if (before_is_package) {
            
            SPVM_OP* op_use = compiler->cur_op_use;
            SPVM_USE* use = op_use->uv.use;
            
            if (strcmp(keyword, use->package_name_with_template_args) != 0) {
              fprintf(stderr, "Package name \"%s\" must be match corresponding file path at %s line %" PRId32 "\n", original_keyword, compiler->cur_file, compiler->cur_line);
              exit(EXIT_FAILURE);
            }
          }
          
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NAME);
          op->uv.name = keyword;
          yylvalp->opval = op;
          
          return NAME;
        }
        
        if (*compiler->bufptr == ',') {
          if (before_is_comma && *compiler->bufptr == ',') {
            fprintf(stderr, "Double camma is forbidden at %s line %" PRId32 "\n", compiler->cur_file, compiler->cur_line);
            exit(EXIT_FAILURE);
          }
          compiler->before_is_comma = 1;
        }
        
        /* Return character */
        compiler->bufptr++;
        yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_NULL);
        
        return (int) (uint8_t) c;
    }
  }
}


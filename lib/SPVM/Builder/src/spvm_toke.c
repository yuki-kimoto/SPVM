#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <inttypes.h>


#include "spvm_compiler.h"
#include "spvm_yacc_util.h"
#include "spvm_yacc.h"
#include "spvm_op.h"
#include "spvm_allocator.h"
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
#include "spvm_method.h"
#include "spvm_class.h"

SPVM_OP* SPVM_TOKE_newOP(SPVM_COMPILER* compiler, int32_t type) {
  
  SPVM_OP* op = SPVM_OP_new_op(compiler, type, compiler->cur_file, compiler->cur_line);
  
  return op;
}

SPVM_OP* SPVM_TOKE_newOP_with_keyword_start_pos(SPVM_COMPILER* compiler, int32_t type, int32_t keyword_start_pos) {
  
  SPVM_OP* op = SPVM_OP_new_op(compiler, type, compiler->cur_file, compiler->cur_line);
  
  // keyword_start_pos is only used to decide anon sub uniquness
  op->keyword_start_pos = keyword_start_pos;
  
  return op;
}

int32_t SPVM_TOKE_is_white_space(SPVM_COMPILER* compiler, char ch) {
  (void)compiler;
  // SP, CR, LF, HT, FF
  if (ch == 0x20 || ch == 0x0D || ch == 0x0A || ch == 0x09 || ch == 0x0C) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TOKE_is_valid_unicode_codepoint(int32_t uc) {
  return (((uint32_t)uc)-0xd800 > 0x07ff) && ((uint32_t)uc < 0x110000);
}

int32_t SPVM_TOKE_convert_unicode_codepoint_to_utf8(int32_t uc, uint8_t* dst) {
  if (uc < 0x00) {
    return 0;
  } else if (uc < 0x80) {
    dst[0] = (uint8_t)uc;
    return 1;
  } else if (uc < 0x800) {
    dst[0] = (uint8_t)(0xC0 + (uc >> 6));
    dst[1] = (uint8_t)(0x80 + (uc & 0x3F));
    return 2;
  // Note: we allow encoding 0xd800-0xdfff here, so as not to change
  // the API, however, these are actually invalid in UTF-8
  } else if (uc < 0x10000) {
    dst[0] = (uint8_t)(0xE0 + (uc >> 12));
    dst[1] = (uint8_t)(0x80 + ((uc >> 6) & 0x3F));
    dst[2] = (uint8_t)(0x80 + (uc & 0x3F));
    return 3;
  } else if (uc < 0x110000) {
    dst[0] = (uint8_t)(0xF0 + (uc >> 18));
    dst[1] = (uint8_t)(0x80 + ((uc >> 12) & 0x3F));
    dst[2] = (uint8_t)(0x80 + ((uc >> 6) & 0x3F));
    dst[3] = (uint8_t)(0x80 + (uc & 0x3F));
    return 4;
  }
  else {
    return 0;
  }
}

// Get token
int SPVM_yylex(SPVM_YYSTYPE* yylvalp, SPVM_COMPILER* compiler) {
  
  // Save buf pointer
  compiler->befbufptr = compiler->bufptr;

  // Constant minus sign
  int32_t minus = 0;
  
  // Expect sub name
  int32_t expect_method_name = compiler->expect_method_name;
  compiler->expect_method_name = 0;
  
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

    if (compiler->bufptr == NULL) {
      compiler->bufptr = "";
    }
    
    // Get current character
    char ch = *compiler->bufptr;
    
    // "aaa $foo bar" is interupted "aaa $foo " . "bar"
    if (compiler->bufptr == compiler->next_double_quote_start_bufptr) {
      compiler->next_double_quote_start_bufptr = NULL;
      state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_SECOND_CONCAT;
    }
    
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

    // '\0' means end of file, so try to read next module source
    if (ch == '\0') {
      compiler->cur_file = NULL;
      compiler->cur_src = NULL;
      compiler->bufptr = NULL;
      compiler->befbufptr = NULL;
      compiler->line_start_ptr = NULL;
      
      // If there are more module, load it
      SPVM_LIST* op_use_stack = compiler->op_use_stack;
      
      while (1) {
        if (op_use_stack->length == 0) {
          return 0;
        }
        else if (op_use_stack->length > 0) {
          SPVM_OP* op_use = SPVM_LIST_shift(op_use_stack);
          
          const char* class_name = op_use->uv.use->op_type->uv.type->basic_type->name;

          const char* used_class_name = (const char*)SPVM_HASH_fetch(compiler->used_class_symtable, class_name, strlen(class_name));

          if (used_class_name) {
            continue;
          }
          else {
            SPVM_HASH_insert(compiler->used_class_symtable, class_name, strlen(class_name), (void*)class_name);
            
            // Create moudle relative file name from class name by changing :: to / and add ".spvm"
            int32_t cur_rel_file_length = (int32_t)(strlen(class_name) + 6);
            char* cur_rel_file = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, cur_rel_file_length + 1);
            const char* bufptr_orig = class_name;
            char* bufptr_to = cur_rel_file;
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

            char* cur_file = NULL;
            
            // Do directry module search
            int32_t do_directry_module_search;

            // Byte, Short, Int, Long, Float, Double, Bool is already existsregistered in module source symtable
            const char* found_module_source = SPVM_HASH_fetch(compiler->embedded_module_source_symtable, class_name, strlen(class_name));
            if (found_module_source) {

            }
            else {
              // Search module file
              FILE* fh = NULL;
              int32_t module_dirs_length = compiler->module_dirs->length;
              for (int32_t i = 0; i < module_dirs_length; i++) {
                const char* include_dir = (const char*) SPVM_LIST_fetch(compiler->module_dirs, i);
                
                // File name
                int32_t file_name_length = (int32_t)(strlen(include_dir) + 1 + strlen(cur_rel_file));
                cur_file = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, file_name_length + 1);
                sprintf(cur_file, "%s/%s", include_dir, cur_rel_file);
                cur_file[file_name_length] = '\0';
                
                // \ is replaced to /
                for (int32_t i = 0; i < file_name_length; i++) {
                  if (cur_file[i] == '\\') {
                    cur_file[i] = '/';
                  }
                }

                // Add module file symtable
                SPVM_HASH_insert(compiler->loaded_module_file_symtable, class_name, strlen(class_name), (void*)cur_file);
                
                // Open source file
                fh = fopen(cur_file, "rb");
                if (fh) {
                  break;
                }
                errno = 0;
              }
              
              // Module not found
              if (!fh) {
                if (!op_use->uv.use->is_require) {
                  fprintf(stderr, "[CompileError]Can't locate %s to load %s class in @INC (@INC contains:", cur_rel_file, class_name);
                  for (int32_t i = 0; i < module_dirs_length; i++) {
                    const char* include_dir = (const char*) SPVM_LIST_fetch(compiler->module_dirs, i);
                    fprintf(stderr, " %s", include_dir);
                  }
                  fprintf(stderr, ") at %s line %d\n", op_use->file, op_use->line);
                  compiler->error_count++;
                  return 0;
                }
              }
              // Module found
              else {
                // Read file content
                fseek(fh, 0, SEEK_END);
                int32_t file_size = (int32_t)ftell(fh);
                if (file_size < 0) {
                  SPVM_COMPILER_error(compiler, "Can't read file %s at %s line %d\n", cur_file, op_use->file, op_use->line);
                  return 0;
                }
                fseek(fh, 0, SEEK_SET);
                char* src = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, file_size + 1);
                if ((int32_t)fread(src, 1, file_size, fh) < file_size) {
                  SPVM_COMPILER_error(compiler, "Can't read file %s at %s line %d\n", cur_file, op_use->file, op_use->line);
                  SPVM_ALLOCATOR_free_block_compile_tmp(compiler, src);
                  return 0;
                }
                fclose(fh);
                src[file_size] = '\0';
                
                found_module_source = src;
                SPVM_HASH_insert(compiler->embedded_module_source_symtable, class_name, strlen(class_name), src);
              }
            }
            
            const char* src = NULL;
            int32_t file_size = 0;
            int32_t module_not_found = 0;
            if (found_module_source) {
              src = found_module_source;
              file_size = strlen(src);
            }
            else {
              module_not_found = 1;
            }
            
            // If module not found and that is if (requre Foo) syntax, syntax is ok.
            if (module_not_found && op_use->uv.use->is_require) {
              op_use->uv.use->load_fail = 1;
              SPVM_OP* op_class = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS, op_use->file, op_use->line);
              SPVM_TYPE* type = SPVM_TYPE_new(compiler);
              type->basic_type = op_use->uv.use->op_type->uv.type->basic_type;
              SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, op_use->file, op_use->line);
              type->basic_type->fail_load = 1;
              
              SPVM_OP_build_class(compiler, op_class, op_type, NULL, NULL);
              
              continue;
            }
            else {
              
              // Copy original source to current source because original source is used at other places(for example, SPVM::Builder::Exe)
              compiler->cur_src = (char*)src;
              compiler->cur_rel_file = cur_rel_file;
              compiler->cur_rel_file_class_name = class_name;
              
              // If we get current module file path, set it, otherwise set module relative file path
              if (cur_file) {
                compiler->cur_file = cur_file;
              }
              else {
                compiler->cur_file = cur_rel_file;
              }
              
              // Set initial information for tokenization
              compiler->bufptr = compiler->cur_src;
              compiler->befbufptr = compiler->cur_src;
              compiler->line_start_ptr = compiler->cur_src;
              compiler->cur_line = 1;
            }
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
    
    switch (ch) {
      // Skip space character
      case ' ':
      case '\t':
      case '\f':
      {
        compiler->bufptr++;
        continue;
      }
      case '\r':
      case '\n':
      {
        if (*compiler->bufptr == '\r' && *(compiler->bufptr + 1) == '\n') {
          compiler->bufptr++;
        }

        compiler->bufptr++;
        compiler->cur_line++;
        compiler->line_start_ptr = compiler->bufptr;
        continue;
      }
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
          compiler->expect_method_name = 1;
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
        // * is used in MULTIPLY operator or type reference
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NULL);
          yylvalp->opval = op;
          return '*';
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
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_LOGICAL_OR);
          yylvalp->opval = op;
          return LOGICAL_OR;
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
        // &&
        if (*compiler->bufptr == '&') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_LOGICAL_AND);
          yylvalp->opval = op;
          return LOGICAL_AND;
        }
        // &=
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        // &foo - Current class
        else if (isalpha(*compiler->bufptr) || *compiler->bufptr == '_') {
          yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_CURRENT_CLASS);
          compiler->expect_method_name = 1;
          return CURRENT_CLASS;
        }
        // &
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_BIT_AND);
          yylvalp->opval = op;
          return BIT_AND;
        }
      
      // Comment
      case '#':
        compiler->bufptr++;
        while(1) {
          if (*compiler->bufptr == '\r' && *(compiler->bufptr + 1) == '\n') {
            compiler->bufptr++;
          }
          if (*compiler->bufptr == '\n' || *compiler->bufptr == '\r' || *compiler->bufptr == '\0') {
            break;
          }
          else {
            compiler->bufptr++;
          }
        }
        
        continue;
      
      case '=':
        // POD
        if (compiler->bufptr == compiler->cur_src || *(compiler->bufptr - 1) == '\n') {
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
              && (*(compiler->bufptr + 4) == '\0' || SPVM_TOKE_is_white_space(compiler, *(compiler->bufptr + 4)))
            )
            {
              compiler->bufptr += 4;
              
              while (1) {
                if (*compiler->bufptr == '\n' || *compiler->bufptr == '\0') {
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
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NUMERIC_EQ);
            yylvalp->opval = op;
            return NUMEQ;
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

          // <=>
          if (*compiler->bufptr == '>') {
            compiler->bufptr++;
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NUMERIC_CMP);
            yylvalp->opval = op;
            return NUMERIC_CMP;
          }
          // <=
          else {
            SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NUMERIC_LE);
            yylvalp->opval = op;
            return NUMLE;
          }
        }
        // <
        else {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NUMERIC_LT);
          yylvalp->opval = op;
          return NUMLT;
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
              op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_LOGICAL_SHIFT;
              
              yylvalp->opval = op_special_assign;
              
              return SPECIAL_ASSIGN;
            }
            // >>>
            else {
              SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT);
              yylvalp->opval = op;
              return SHIFT;
            }
          }
          else {
            // >>=
            if (*compiler->bufptr == '=') {
              compiler->bufptr++;
              SPVM_OP* op_special_assign = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
              op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_ARITHMETIC_SHIFT;
              
              yylvalp->opval = op_special_assign;
              
              return SPECIAL_ASSIGN;
            }
            // >>
            else {
              SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT);
              yylvalp->opval = op;
              return SHIFT;
            }
          }
        }
        // >=
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NUMERIC_GE);
          yylvalp->opval = op;
          return NUMGE;
        }
        // >
        else {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NUMERIC_GT);
          yylvalp->opval = op;
          return NUMGT;
        }
      case '!':
        compiler->bufptr++;
        
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_NUMERIC_NE);
          yylvalp->opval = op;
          return NUMNE;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_LOGICAL_NOT);
          yylvalp->opval = op;
          return LOGICAL_NOT;
        }
      case '~': {
        compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_BIT_NOT);
          yylvalp->opval = op;
        return BIT_NOT;
      }
      // Character Literal
      case '\'': {
        compiler->bufptr++;
        char ch = 0;
        
        if (*compiler->bufptr == '\'') {
          SPVM_COMPILER_error(compiler, "Character Literal must have one character at %s line %d\n", compiler->cur_file, compiler->cur_line);
        }
        else {
          if (*compiler->bufptr == '\\') {
            compiler->bufptr++;
            if (*compiler->bufptr == '0') {
              ch = '\0';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 'a') {
              ch = '\a';
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
            else if (*compiler->bufptr == 't') {
              ch = '\t';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 'r') {
              ch = '\r';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 'n') {
              ch = '\n';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == '\'') {
              ch = '\'';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == '"') {
              ch = '\"';
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == '\\') {
              ch = '\\';
              compiler->bufptr++;
            }
            // Hex ascii code
            else if (*compiler->bufptr == 'x') {
              compiler->bufptr++;
              if (*compiler->bufptr == '0' || *compiler->bufptr == '1' || *compiler->bufptr == '2' || *compiler->bufptr == '3' || *compiler->bufptr == '4' || *compiler->bufptr == '5' || *compiler->bufptr == '6' || *compiler->bufptr == '7') {
                int32_t memory_blocks_count_compile_tmp = compiler->allocator->memory_blocks_count_compile_tmp;
                
                char* num_str = SPVM_ALLOCATOR_new_block_compile_tmp(compiler, 3);
                num_str[0] = *compiler->bufptr;
                compiler->bufptr++;
                if (
                  isdigit(*compiler->bufptr)
                  || *compiler->bufptr == 'a'  || *compiler->bufptr == 'b'  || *compiler->bufptr == 'c'  || *compiler->bufptr == 'd'  || *compiler->bufptr == 'e'  || *compiler->bufptr == 'f'
                  || *compiler->bufptr == 'A'  || *compiler->bufptr == 'B'  || *compiler->bufptr == 'C'  || *compiler->bufptr == 'D'  || *compiler->bufptr == 'E'  || *compiler->bufptr == 'F'
                )
                {
                  num_str[1] = *compiler->bufptr;
                  compiler->bufptr++;
                  char *end;
                  ch = (char)strtol(num_str, &end, 16);
                }
                else {
                  SPVM_COMPILER_error(compiler, "Invalid ascii code in escape character of charater literal at %s line %d\n", compiler->cur_file, compiler->cur_line);
                }
                SPVM_ALLOCATOR_free_block_compile_tmp(compiler, num_str);
                assert(compiler->allocator->memory_blocks_count_compile_tmp == memory_blocks_count_compile_tmp);
              }
              else {
                SPVM_COMPILER_error(compiler, "Invalid ascii code in escape character of charater literal at %s line %d\n", compiler->cur_file, compiler->cur_line);
              }
            }
            else {
              SPVM_COMPILER_error(compiler, "Invalid escape character in charater literal at %s line %d\n", compiler->cur_file, compiler->cur_line);
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
            SPVM_COMPILER_error(compiler, "Can't find character literal terminiator at %s line %d\n", compiler->cur_file, compiler->cur_line);
          }
        }
        
        // Constant 
        SPVM_OP* op_constant = SPVM_OP_new_op_constant_byte(compiler, ch, compiler->cur_file, compiler->cur_line);
        
        yylvalp->opval = op_constant;
        
        return CONSTANT;
      }
      // String Literal
      case '"': {
        if (state_var_expansion == SPVM_TOKE_C_STATE_VAR_EXPANSION_DOUBLE_QUOTE) {
          // Nothing
        }
        else {
          compiler->bufptr++;
        }

        compiler->state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_DEFAULT;
        
        // Save current position
        const char* cur_token_ptr = compiler->bufptr;
        
        int8_t next_state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_DEFAULT;
        
        char* str_tmp;
        int32_t memory_blocks_count_compile_tmp = compiler->allocator->memory_blocks_count_compile_tmp;
        int32_t str_length = 0;
        if (*(compiler->bufptr) == '"') {
          str_tmp = SPVM_ALLOCATOR_new_block_compile_tmp(compiler, 1);
          str_tmp[0] = '\0';
          compiler->bufptr++;
        }
        else {
          int32_t finish = 0;
          
          while(1) {
            // End of string literal
            if (*compiler->bufptr == '"') {
              finish = 1;
            }
            // Variable expansion
            else if (*compiler->bufptr == '$') {
              if (*(compiler->bufptr + 1) == '"') {
                // Last $ is allow
              }
              else {
                finish = 1;
                next_state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_FIRST_CONCAT;
                
                // Pending next string literal start
                char* next_double_quote_start_bufptr = compiler->bufptr + 1;

                // Dereference
                int32_t var_is_ref = 0;
                if (*next_double_quote_start_bufptr == '$') {
                  next_double_quote_start_bufptr++;
                  var_is_ref = 1;
                }
                
                int32_t var_have_brace = 0;
                if (*next_double_quote_start_bufptr == '{') {
                  next_double_quote_start_bufptr++;
                  var_have_brace = 1;
                }
                
                if (*next_double_quote_start_bufptr == '@') {
                  next_double_quote_start_bufptr++;
                  if (var_have_brace) {
                    if (*next_double_quote_start_bufptr == '}') {
                      next_double_quote_start_bufptr++;
                    }
                  }
                }
                else {
                
                  // Pend variable
                  while (1) {
                    if (isalnum(*next_double_quote_start_bufptr) || *next_double_quote_start_bufptr == '_') {
                      next_double_quote_start_bufptr++;
                    }
                    else if (*next_double_quote_start_bufptr == ':' && *(next_double_quote_start_bufptr + 1) == ':') {
                      next_double_quote_start_bufptr += 2;
                    }
                    else if (*next_double_quote_start_bufptr == '}') {
                      if (var_have_brace) {
                        next_double_quote_start_bufptr++;
                        break;
                      }
                    }
                    else {
                      break;
                    }
                  }
                  
                  // Pend Field access or array access(only support field access or constant array accsess)
                  if (!var_have_brace && !var_is_ref) {
                    int32_t is_access = 0;
                    if (*next_double_quote_start_bufptr == '-' && *(next_double_quote_start_bufptr + 1) == '>') {
                      is_access = 1;
                      next_double_quote_start_bufptr += 2;
                    }
                    if (is_access) {
                      while (1) {
                        if (isalnum(*next_double_quote_start_bufptr) || *next_double_quote_start_bufptr == '_' || *next_double_quote_start_bufptr == '{' || *next_double_quote_start_bufptr == '[') {
                          next_double_quote_start_bufptr++;
                        }
                        else if (*next_double_quote_start_bufptr == '}' || *next_double_quote_start_bufptr == ']') {
                          if ((*(next_double_quote_start_bufptr + 1) == '-' && *(next_double_quote_start_bufptr + 2) == '>')) {
                            next_double_quote_start_bufptr += 2;
                          }
                          else if (*(next_double_quote_start_bufptr + 1) == '{' || *(next_double_quote_start_bufptr + 1) == '[') {
                            next_double_quote_start_bufptr++;
                          }
                          else {
                            next_double_quote_start_bufptr++;
                            break;
                          }
                        }
                        else {
                          break;
                        }
                      }
                    }
                  }
                }
                compiler->next_double_quote_start_bufptr = next_double_quote_start_bufptr;
              }
            }
            // End of source file
            else if (*compiler->bufptr == '\0') {
              finish = 1;
            }
            if (finish) {
              break;
            }
            else {
              // Escape is always 2 characters
              if (*compiler->bufptr == '\\') {
                compiler->bufptr += 2;
              }
              else {
                compiler->bufptr++;
              }
            }
          }
          if (*compiler->bufptr == '\0') {
            SPVM_COMPILER_error(compiler, "Can't find string terminator '\"' anywhere before EOF at %s line %d\n", compiler->cur_file, compiler->cur_line);
            SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, "", 0, compiler->cur_file, compiler->cur_line);
            yylvalp->opval = op_constant;
            return CONSTANT;
          }
          
          int32_t str_tmp_len = (int32_t)(compiler->bufptr - cur_token_ptr) * 4;

          compiler->bufptr++;
          
          str_tmp = SPVM_ALLOCATOR_new_block_compile_tmp(compiler, str_tmp_len + 1);
          {
            char* char_ptr = (char*)cur_token_ptr;
            while (char_ptr != compiler->bufptr - 1) {
              if (*char_ptr == '\\') {
                char_ptr++;
                if (*char_ptr == '0') {
                  str_tmp[str_length] = '\0';
                  str_length++;
                  char_ptr++;
                }
                else if (*char_ptr == 'a') {
                  str_tmp[str_length] = '\a';
                  str_length++;
                  char_ptr++;
                }
                else if (*char_ptr == 'f') {
                  str_tmp[str_length] = '\f';
                  str_length++;
                  char_ptr++;
                }
                else if (*char_ptr == 't') {
                  str_tmp[str_length] = '\t';
                  str_length++;
                  char_ptr++;
                }
                else if (*char_ptr == 'r') {
                  str_tmp[str_length] = '\r';
                  str_length++;
                  char_ptr++;
                }
                else if (*char_ptr == 'n') {
                  str_tmp[str_length] = '\n';
                  str_length++;
                  char_ptr++;
                }
                else if (*char_ptr == '\'') {
                  str_tmp[str_length] = '\'';
                  str_length++;
                  char_ptr++;
                }
                else if (*char_ptr == '"') {
                  str_tmp[str_length] = '\"';
                  str_length++;
                  char_ptr++;
                }
                else if (*char_ptr == '\\') {
                  str_tmp[str_length] = '\\';
                  str_length++;
                  char_ptr++;
                }
                else if (*char_ptr == '$') {
                  str_tmp[str_length] = '$';
                  str_length++;
                  char_ptr++;
                }
                else if (*char_ptr == 'x') {
                  char_ptr++;
                  if (*char_ptr == '0' || *char_ptr == '1' || *char_ptr == '2' || *char_ptr == '3' || *char_ptr == '4' || *char_ptr == '5' || *char_ptr == '6' || *char_ptr == '7') {
                    int32_t memory_blocks_count_compile_tmp = compiler->allocator->memory_blocks_count_compile_tmp;
                    char* num_str = SPVM_ALLOCATOR_new_block_compile_tmp(compiler, 3);
                    num_str[0] = *char_ptr;
                    char_ptr++;
                    if (
                      isdigit(*char_ptr)
                      || *char_ptr == 'a'  || *char_ptr == 'b'  || *char_ptr == 'c'  || *char_ptr == 'd'  || *char_ptr == 'e'  || *char_ptr == 'f'
                      || *char_ptr == 'A'  || *char_ptr == 'B'  || *char_ptr == 'C'  || *char_ptr == 'D'  || *char_ptr == 'E'  || *char_ptr == 'F'
                    )
                    {
                      num_str[1] = *char_ptr;
                      char_ptr++;
                      char *end;
                      ch = (char)strtol(num_str, &end, 16);
                      str_tmp[str_length] = ch;
                      str_length++;
                    }
                    else {
                      SPVM_COMPILER_error(compiler, "Invalid ascii code in escape character of string literal at %s line %d\n", compiler->cur_file, compiler->cur_line);
                    }
                    SPVM_ALLOCATOR_free_block_compile_tmp(compiler, num_str);
                    assert(compiler->allocator->memory_blocks_count_compile_tmp == memory_blocks_count_compile_tmp);
                  }
                  else {
                    SPVM_COMPILER_error(compiler, "Invalid ascii code in escape character of string literal at %s line %d\n", compiler->cur_file, compiler->cur_line);
                  }
                }
                // Unicode code point. This is converted to UTF-8
                else if (*char_ptr == 'N' && *(char_ptr + 1) == '{') {
                  char_ptr++;
                  if (*char_ptr == '{' && *(char_ptr + 1) == 'U' && *(char_ptr + 2) == '+') {
                    char_ptr += 3;
                    char* char_start_ptr = char_ptr;
                    int32_t unicode_chars_length = 0;
                    
                    while (
                      isdigit(*char_ptr)
                      || *char_ptr == 'a'  || *char_ptr == 'b'  || *char_ptr == 'c'  || *char_ptr == 'd'  || *char_ptr == 'e'  || *char_ptr == 'f'
                      || *char_ptr == 'A'  || *char_ptr == 'B'  || *char_ptr == 'C'  || *char_ptr == 'D'  || *char_ptr == 'E'  || *char_ptr == 'F'
                    )
                    {
                      char_ptr++;
                      unicode_chars_length++;
                    }
                    if (*char_ptr == '}') {
                      char_ptr++;
                      if (unicode_chars_length < 1) {
                        SPVM_COMPILER_error(compiler, "Unicode code point is empty at %s line %d\n", compiler->cur_file, compiler->cur_line);
                      }
                      else if (unicode_chars_length > 8) {
                        SPVM_COMPILER_error(compiler, "Too big unicode code point at %s line %d\n", compiler->cur_file, compiler->cur_line);
                      }
                      else {
                        int32_t memory_blocks_count_compile_tmp = compiler->allocator->memory_blocks_count_compile_tmp;
                        char* unicode_chars = SPVM_ALLOCATOR_new_block_compile_tmp(compiler, unicode_chars_length + 1);
                        memcpy(unicode_chars, char_start_ptr, unicode_chars_length);
                        char *end;
                        int32_t unicode = (int32_t)strtoll(unicode_chars, &end, 16);
                        
                        int32_t valid = SPVM_TOKE_is_valid_unicode_codepoint(unicode);
                        if (valid) {
                          char utf8_chars[4];
                          int32_t byte_length = SPVM_TOKE_convert_unicode_codepoint_to_utf8(unicode, (uint8_t*)utf8_chars);
                          for (int32_t byte_index = 0; byte_index < byte_length; byte_index++) {
                            str_tmp[str_length] = utf8_chars[byte_index];
                            str_length++;
                          }
                        }
                        else {
                          SPVM_COMPILER_error(compiler, "Invalid unicode code point at %s line %d\n", compiler->cur_file, compiler->cur_line);
                        }
                        SPVM_ALLOCATOR_free_block_compile_tmp(compiler, unicode_chars);
                        assert(compiler->allocator->memory_blocks_count_compile_tmp == memory_blocks_count_compile_tmp);
                      }
                    }
                    else {
                      SPVM_COMPILER_error(compiler, "Unicode escape need close bracket at %s line %d\n", compiler->cur_file, compiler->cur_line);
                    }
                  }
                  else {
                    SPVM_COMPILER_error(compiler, "Invalid unicode escape of string literal at %s line %d\n", compiler->cur_file, compiler->cur_line);
                  }
                }
                else {
                  switch(*char_ptr) {
                    case 'w':
                    case 'W':
                    case 's':
                    case 'S':
                    case 'd':
                    case 'D':
                    case 'p':
                    case 'P':
                    case 'X':
                    case 'g':
                    case 'k':
                    case 'K':
                    case 'v':
                    case 'V':
                    case 'h':
                    case 'H':
                    case 'R':
                    case 'b':
                    case 'B':
                    case 'A':
                    case 'Z':
                    case 'z':
                    case 'G':
                    case 'N':
                    case '!':
                    case '#':
                    case '@':
                    case '%':
                    case '&':
                    case '(':
                    case ')':
                    case '*':
                    case '+':
                    case ',':
                    case '-':
                    case '.':
                    case '/':
                    case ':':
                    case ';':
                    case '<':
                    case '=':
                    case '>':
                    case '?':
                    case '[':
                    case ']':
                    case '^':
                    case '_':
                    case '`':
                    case '{':
                    case '|':
                    case '}':
                    case '~':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    {
                      str_tmp[str_length] = '\\';
                      str_length++;
                      str_tmp[str_length] = *char_ptr;
                      str_length++;
                      char_ptr++;
                      break;
                    }
                    default: {
                      SPVM_COMPILER_error(compiler, "Invalid escape character in string literal \"\\%c\" at %s line %d\n", *char_ptr, compiler->cur_file, compiler->cur_line);
                    }
                  }
                }
              }
              else {
                if (*char_ptr == '\r' && *(char_ptr + 1) == '\n') {
                  char_ptr++;
                }
                if (*char_ptr == '\n' || *char_ptr == '\r') {
                  compiler->cur_line++;
                  compiler->line_start_ptr = compiler->bufptr;
                }
                
                str_tmp[str_length] = *char_ptr;
                str_length++;
                char_ptr++;
              }
            }
          }
          str_tmp[str_length] = '\0';
        }

        char* str;
        // String Literal
        char* found_str = SPVM_HASH_fetch(compiler->const_string_symtable, str_tmp, str_length);
        if (found_str) {
          str = found_str;
        }
        else {
          str = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, str_length + 1);
          memcpy(str, str_tmp, str_length);
          SPVM_HASH_insert(compiler->const_string_symtable, str, str_length, str);
        }
        
        SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, str, str_length, compiler->cur_file, compiler->cur_line);
        
        SPVM_ALLOCATOR_free_block_compile_tmp(compiler, str_tmp);
        assert(compiler->allocator->memory_blocks_count_compile_tmp == memory_blocks_count_compile_tmp);
        
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
        SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_CREATE_REF);
        yylvalp->opval = op;
        return CREATE_REF;
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
          // Exception variable with {}
          else if (*(compiler->bufptr + 1) == '{' && *(compiler->bufptr + 2) == '@' && *(compiler->bufptr + 3) == '}') {
            compiler->bufptr += 4;
            SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_EXCEPTION_VAR, compiler->cur_file, compiler->cur_line);
            yylvalp->opval = op_exception_var;
            return EXCEPTION_VAR;
          }
          // Lexical variable or Class variable
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
            )
            {
              if (*compiler->bufptr == ':') {
                if (*(compiler->bufptr + 1) == ':') {
                  compiler->bufptr += 2;
                }
                else {
                  SPVM_COMPILER_error(compiler, "Single colon \":\" in variable name is invalid at %s line %d\n", compiler->cur_file, compiler->cur_line);
                  compiler->bufptr += 1;
                }
              }
              else {
                compiler->bufptr++;
              }
            }
          

            int32_t var_name_length_without_sigil = compiler->bufptr - cur_token_ptr;
            int32_t var_name_length = var_name_length_without_sigil + 1;

            char* var_name;
            char* found_var_name = SPVM_HASH_fetch(compiler->const_string_symtable, cur_token_ptr - 1, var_name_length);
            if (found_var_name) {
              var_name = found_var_name;
            }
            else {
              var_name = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, 1 + var_name_length_without_sigil + 1);
              var_name[0] = '$';
              memcpy(&var_name[1], cur_token_ptr, var_name_length_without_sigil);
              var_name[1 + var_name_length_without_sigil] = '\0';
              SPVM_HASH_insert(compiler->const_string_symtable, var_name, var_name_length_without_sigil + 1, var_name);
            }

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

            // Variable name can't conatain __
            if (strstr(var_name, "__")) {
              SPVM_COMPILER_error(compiler, "Variable name \"%s\" can't contain \"__\" at %s line %d\n", var_name, compiler->cur_file, compiler->cur_line);
            }

            if (strstr(var_name, ":::")) {
              SPVM_COMPILER_error(compiler, "Variable name \"%s\" can't contain \":::\" at %s line %d\n", var_name, compiler->cur_file, compiler->cur_line);
            }

            // Variable name can't start with number
            if (isdigit(var_name[1])) {
              SPVM_COMPILER_error(compiler, "Variable name \"%s\" must not start with number at %s line %d\n", var_name, compiler->cur_file, compiler->cur_line);
            }

            if (strlen(var_name) > 1 && var_name[var_name_length_without_sigil] == ':' && var_name[var_name_length_without_sigil - 1] == ':') {
              SPVM_COMPILER_error(compiler, "Variable name \"%s\" must not end with \"::\" at %s line %d\n", var_name, compiler->cur_file, compiler->cur_line);
            }
            
            
            // Class variable
            return VAR_NAME;
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
              digit = 16;
            }
            // Binary Literal
            else if (*(compiler->bufptr + 1) == 'b' || *(compiler->bufptr + 1) == 'B') {
              digit = 2;
            }
            // Octal Literal
            else if (isdigit(*(compiler->bufptr + 1))) {
              digit = 8;
            }
          }
          // Decimal Literal
          else {
            digit = 10;
          }
          
          int32_t is_floating_number = 0;
          int32_t is_hex_floating_number = 0;
          
          compiler->bufptr++;
          // Scan Hex number
          if (digit == 16) {
            compiler->bufptr += 2;
            while(
              isdigit(*compiler->bufptr)
              || *compiler->bufptr == 'a' || *compiler->bufptr == 'b' || *compiler->bufptr == 'c' || *compiler->bufptr == 'd' || *compiler->bufptr == 'e' || *compiler->bufptr == 'f'
              || *compiler->bufptr == 'A' || *compiler->bufptr == 'B' || *compiler->bufptr == 'C' || *compiler->bufptr == 'D' || *compiler->bufptr == 'E' || *compiler->bufptr == 'F'
              || *compiler->bufptr == '_' || *compiler->bufptr == '.' || *compiler->bufptr == 'p' || *compiler->bufptr == 'P' || *compiler->bufptr == '-' || *compiler->bufptr == '+'
            )
            {
              // Floating point literal
              if (*compiler->bufptr == '.' || *compiler->bufptr == 'p' || *compiler->bufptr == 'P') {
                is_floating_number = 1;
              }
              if (*compiler->bufptr == 'p' || *compiler->bufptr == 'P') {
                is_hex_floating_number = 1;
              }
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
          // Scan Decimal number
          else {
            while(
              isdigit(*compiler->bufptr)
              || *compiler->bufptr == '.' || *compiler->bufptr == '-' || *compiler->bufptr == '+' || *compiler->bufptr == 'e' || *compiler->bufptr == 'E'
              || *compiler->bufptr == '_'
            )
            {
              // Floating point literal
              if (*compiler->bufptr == '.' || *compiler->bufptr == 'e' || *compiler->bufptr == 'E') {
                is_floating_number = 1;
              }
              compiler->bufptr++;
            }
          }
          
          // First is space for + or -
          int32_t str_len = (compiler->bufptr - cur_token_ptr);
          
          // Ignore under line
          int32_t num_str_tmp_memoyr_blocks_count = compiler->allocator->memory_blocks_count_compile_tmp;
          char* num_str_tmp = (char*)SPVM_ALLOCATOR_new_block_compile_tmp(compiler, str_len + 2);
          int32_t pos = 0;
          {
            int32_t i;
            for (i = 0; i < str_len; i++) {
              if (*(cur_token_ptr + i) != '_') {
                *(num_str_tmp + pos) = *(cur_token_ptr + i);
                pos++;
              }
            }
            num_str_tmp[pos] = '\0';
          }
          // Back suffix such as "f" or "F" when hex floating number
          if (is_hex_floating_number && !isdigit(*(compiler->bufptr - 1))) {
            compiler->bufptr--;
            num_str_tmp[pos - 1] = '\0';
          }
          
          int32_t num_str_length = strlen(num_str_tmp);

          // Keyword string
          char* num_str;
          char* found_num_str = SPVM_HASH_fetch(compiler->const_string_symtable, num_str_tmp, num_str_length);
          if (found_num_str) {
            num_str = found_num_str;
          }
          else {
            num_str = (char*)SPVM_ALLOCATOR_new_block_compile_eternal(compiler, num_str_length + 1);
            memcpy(num_str, num_str_tmp, num_str_length);
            SPVM_HASH_insert(compiler->const_string_symtable, num_str, num_str_length, num_str);
          }
          
          SPVM_ALLOCATOR_free_block_compile_tmp(compiler, num_str_tmp);
          assert(compiler->allocator->memory_blocks_count_compile_tmp == num_str_tmp_memoyr_blocks_count);

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
              char* num_str_only_num;
              if (digit == 16) {
                num_str_only_num = num_str + 2;
              }
              else if (digit == 8) {
                num_str_only_num = num_str + 1;
              }
              else if (digit == 2) {
                num_str_only_num = num_str + 2;
              }
              else {
                assert(0);
              }
              uint64_t unum = (uint64_t)strtoull(num_str_only_num, &end, digit);
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
              char* num_str_only_num;
              if (digit == 16) {
                num_str_only_num = num_str + 2;
              }
              else if (digit == 8) {
                num_str_only_num = num_str + 1;
              }
              else if (digit == 2) {
                num_str_only_num = num_str + 2;
              }
              else {
                assert(0);
              }
              uint64_t unum = (uint64_t)strtoull(num_str_only_num, &end, digit);
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
          
          op_constant->uv.constant->num_str = num_str;
          
          yylvalp->opval = op_constant;
          
          return CONSTANT;
        }
        // Keyword or name
        else if (isalpha(ch) || ch == '_') {
          // Keyword start position
          int32_t keyword_start_pos = compiler->bufptr - compiler->line_start_ptr;
          
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
          
          // Keyword string
          char* keyword;
          int32_t keyword_length = (compiler->bufptr - cur_token_ptr);
          char* found_name = SPVM_HASH_fetch(compiler->const_string_symtable, cur_token_ptr, keyword_length);
          if (found_name) {
            keyword = found_name;
          }
          else {
            keyword = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, keyword_length + 1);
            memcpy(keyword, cur_token_ptr, keyword_length);
            keyword[keyword_length] = '\0';
            SPVM_HASH_insert(compiler->const_string_symtable, keyword, keyword_length, keyword);
          }

          // If following token is fat comma, keyword is manipulated as string literal
          int32_t next_is_fat_camma = 0;
          char* fat_camma_check_ptr = compiler->bufptr;
          while (SPVM_TOKE_is_white_space(compiler, *fat_camma_check_ptr)) {
            fat_camma_check_ptr++;
          }
          if (*fat_camma_check_ptr == '=' && *(fat_camma_check_ptr + 1) == '>') {
            next_is_fat_camma = 1;
          }
          else {
            next_is_fat_camma = 0;
          }
          if (next_is_fat_camma) {
            SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, keyword, keyword_length, compiler->cur_file, compiler->cur_line);
            
            yylvalp->opval = op_constant;
            
            return CONSTANT;
          }
          
          // Keyword
          if (expect_method_name) {
            // None
          }
          else if (expect_field_name) {
            // None
          }
          else {
            switch (keyword[0]) {
              // Keyword
              case 'a' : {
                if (strcmp(keyword, "allow") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_ALLOW);
                  return ALLOW;
                }
                else if (strcmp(keyword, "as") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_AS);
                  return AS;
                }
                break;
              }
              case 'b' : {
                if (strcmp(keyword, "break") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_BREAK);
                  return BREAK;
                }
                else if (strcmp(keyword, "byte") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_BYTE);
                  return BYTE;
                }
                break;
              }
              case 'c' : {
                if (strcmp(keyword, "callback_t") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_CALLBACK_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  return DESCRIPTOR;
                }
                else if (strcmp(keyword, "case") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_CASE);
                  return CASE;
                }
                else if (strcmp(keyword, "cmp") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_CMP);
                  return STRING_CMP;
                }
                else if (strcmp(keyword, "class") == 0) {
                  
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_CLASS);
                  
                  return CLASS;
                }
                break;
              }
              case 'd' : {
                if (strcmp(keyword, "default") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_DEFAULT);
                  return DEFAULT;
                }
                else if (strcmp(keyword, "die") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_DIE);
                  return DIE;
                }
                else if (strcmp(keyword, "double") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_DOUBLE);
                  return DOUBLE;
                }
                else if (strcmp(keyword, "dump") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_DUMP);
                  return DUMP;
                }
                break;
              }
              case 'e' : {
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
                  return STREQ;
                }
                else if (strcmp(keyword, "eval") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_EVAL);
                  return EVAL;
                }
                break;
              }
              case 'f' : {
                if (strcmp(keyword, "for") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_FOR);
                  return FOR;
                }
                else if (strcmp(keyword, "float") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_FLOAT);
                  return FLOAT;
                }
                else if (strcmp(keyword, "false") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_FALSE);
                  return FALSE;
                }
                break;
              }
              case 'g' : {
                if (strcmp(keyword, "gt") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_GT);
                  return STRGT;
                }
                else if (strcmp(keyword, "ge") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_GE);
                  return STRGE;
                }
                break;
              }
              case 'h' : {
                if (strcmp(keyword, "has") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_FIELD);
                  compiler->expect_field_name = 1;
                  return HAS;
                }
                break;
              }
              case 'i' : {
                if (strcmp(keyword, "if") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_IF);
                  return IF;
                }
                else if (strcmp(keyword, "isa") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_ISA);
                  return ISA;
                }
                else if (strcmp(keyword, "isweak") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_ISWEAK);
                  return ISWEAK;
                }
                else if (strcmp(keyword, "int") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_INT);
                  return INT;
                }
                break;
              }
              case 'I' : {
                if (strcmp(keyword, "INIT") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_INIT);
                  return INIT;
                }
                break;
              }
              case 'l' : {
                if (strcmp(keyword, "last") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_LAST);
                  return LAST;
                }
                else if (strcmp(keyword, "length") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_LENGTH);
                  return STRING_LENGTH;
                }
                else if (strcmp(keyword, "lt") == 0) {
                  SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_LT);
                  yylvalp->opval = op;
                  
                  return STRLT;
                }
                else if (strcmp(keyword, "le") == 0) {
                  SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_LE);
                  yylvalp->opval = op;
                  
                  return STRLE;
                }
                else if (strcmp(keyword, "long") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_LONG);
                  return LONG;
                }
                break;
              }
              case 'm' : {
                if (strcmp(keyword, "my") == 0) {
                  SPVM_MY* my = SPVM_MY_new(compiler);
                  yylvalp->opval = SPVM_OP_new_op_my(compiler, my, compiler->cur_file, compiler->cur_line);
                  return MY;
                }
                else if (strcmp(keyword, "mulnum_t") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_MULNUM_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  return DESCRIPTOR;
                }
                else if (strcmp(keyword, "method") == 0) {
                  SPVM_OP* op_method = SPVM_TOKE_newOP_with_keyword_start_pos(compiler, SPVM_OP_C_ID_METHOD, keyword_start_pos);
                  yylvalp->opval = op_method;

                  compiler->expect_method_name = 1;

                  return METHOD;
                }
                break;
              }
              case 'n' : {
                if (strcmp(keyword, "native") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_NATIVE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  return DESCRIPTOR;
                }
                else if (strcmp(keyword, "ne") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_STRING_NE);
                  return STRNE;
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
              }
              case 'o' : {
                if (strcmp(keyword, "our") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_CLASS_VAR);
                  return OUR;
                }
                else if (strcmp(keyword, "object") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_OBJECT);
                  return OBJECT;
                }
                break;
              }
              case 'p' : {
                if (strcmp(keyword, "print") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_PRINT);
                  return PRINT;
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
              }
              case 'r' : {
                if (strcmp(keyword, "ref") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_REFOP);
                  return REFOP;
                }
                else if (strcmp(keyword, "refcnt") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_REFCNT);
                  return REFCNT;
                }
                else if (strcmp(keyword, "return") == 0) {
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
              }
              case 's' : {
                if (strcmp(keyword, "static") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_STATIC, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  return DESCRIPTOR;
                }
                else if (strcmp(keyword, "switch") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_SWITCH);
                  return SWITCH;
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
              }
              case 't' : {
                if (strcmp(keyword, "true") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_TRUE);
                  return TRUE;
                }
                break;
              }
              case 'u' : {
                if (strcmp(keyword, "undef") == 0) {
                  yylvalp->opval = SPVM_OP_new_op_undef(compiler, compiler->cur_file, compiler->cur_line);
                  return UNDEF;
                }
                else if (strcmp(keyword, "unless") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_UNLESS);
                  return UNLESS;
                }
                else if (strcmp(keyword, "unweaken") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_UNLESS);
                  return UNWEAKEN;
                }
                else if (strcmp(keyword, "use") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_USE);
                  return USE;
                }
                break;
              }
              case 'v' : {
                if (strcmp(keyword, "void") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_VOID);
                  return VOID;
                }
                break;
              }
              case 'w' : {
                if (strcmp(keyword, "warn") == 0) {
                  yylvalp->opval = SPVM_TOKE_newOP(compiler, SPVM_OP_C_ID_WARN);
                  return WARN;
                }
                else if (strcmp(keyword, "while") == 0) {
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
              }
              case '_': {
                if (strcmp(keyword, "__END__") == 0) {
                  *compiler->bufptr = '\0';
                  continue;
                }
                else if (strcmp(keyword, "__CLASS__") == 0) {
                  yylvalp->opval = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CURRENT_CLASS_NAME, compiler->cur_file, compiler->cur_line);
                  return CURRENT_CLASS_NAME;
                }
                else if (strcmp(keyword, "__FILE__") == 0) {
                  SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, compiler->cur_rel_file, strlen(compiler->cur_rel_file), compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_constant;
                  return CONSTANT;
                }
                else if (strcmp(keyword, "__LINE__") == 0) {
                  SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, compiler->cur_line, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_constant;
                  return CONSTANT;
                }
                break;
              }
            }
          }
          
          // Symbol name can't conatain __
          if (strstr(keyword, "__")) {
            SPVM_COMPILER_error(compiler, "Symbol name \"%s\" must not contains __ at %s line %d\n", keyword, compiler->cur_file, compiler->cur_line);
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


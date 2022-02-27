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

SPVM_OP* SPVM_TOKE_new_op(SPVM_COMPILER* compiler, int32_t type) {
  
  SPVM_OP* op = SPVM_OP_new_op(compiler, type, compiler->cur_file, compiler->cur_line);
  
  return op;
}

SPVM_OP* SPVM_TOKE_new_op_with_column(SPVM_COMPILER* compiler, int32_t type, int32_t column) {
  
  SPVM_OP* op = SPVM_OP_new_op(compiler, type, compiler->cur_file, compiler->cur_line);
  
  // column is only used to decide anon sub uniquness
  op->column = column;
  
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

  int32_t parse_start = compiler->parse_start;
  compiler->parse_start = 0;

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
      
      if (!parse_start) {
        compiler->parse_start = 1;
        SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_END_OF_FILE);
        yylvalp->opval = op;
        return END_OF_FILE;
      }
      
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
            const char* found_module_source = SPVM_HASH_fetch(compiler->module_source_symtable, class_name, strlen(class_name));
            if (found_module_source) {

            }
            else {
              // Search module file
              FILE* fh = NULL;
              int32_t module_dirs_length = compiler->module_dirs->length;
              for (int32_t i = 0; i < module_dirs_length; i++) {
                const char* module_dir = (const char*) SPVM_LIST_fetch(compiler->module_dirs, i);
                
                // File name
                int32_t file_name_length = (int32_t)(strlen(module_dir) + 1 + strlen(cur_rel_file));
                cur_file = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, file_name_length + 1);
                sprintf(cur_file, "%s/%s", module_dir, cur_rel_file);
                cur_file[file_name_length] = '\0';
                
                // \ is replaced to /
                for (int32_t i = 0; i < file_name_length; i++) {
                  if (cur_file[i] == '\\') {
                    cur_file[i] = '/';
                  }
                }

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
                  int32_t moduler_dirs_str_length = 0;
                  for (int32_t i = 0; i < module_dirs_length; i++) {
                    const char* module_dir = (const char*) SPVM_LIST_fetch(compiler->module_dirs, i);
                    moduler_dirs_str_length += 1 + strlen(module_dir);
                  }
                  char* moduler_dirs_str = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, moduler_dirs_str_length + 1);
                  int32_t moduler_dirs_str_offset = 0;
                  for (int32_t i = 0; i < module_dirs_length; i++) {
                    const char* module_dir = (const char*) SPVM_LIST_fetch(compiler->module_dirs, i);
                    sprintf(moduler_dirs_str + moduler_dirs_str_offset, " %s", module_dir);
                    moduler_dirs_str_offset += 1 + strlen(module_dir);
                  }
                  
                  SPVM_COMPILER_error(compiler, "Can't find the file \"%s\" to load the \"%s\" class in @INC (@INC contains:%s) at %s line %d", cur_rel_file, class_name, moduler_dirs_str, op_use->file, op_use->line);
                  
                  return 0;
                }
              }
              // Module found
              else {
                // Read file content
                fseek(fh, 0, SEEK_END);
                int32_t file_size = (int32_t)ftell(fh);
                if (file_size < 0) {
                  SPVM_COMPILER_error(compiler, "Can't read file %s at %s line %d", cur_file, op_use->file, op_use->line);
                  return 0;
                }
                fseek(fh, 0, SEEK_SET);
                char* src = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, file_size + 1);
                if ((int32_t)fread(src, 1, file_size, fh) < file_size) {
                  SPVM_COMPILER_error(compiler, "Can't read file %s at %s line %d", cur_file, op_use->file, op_use->line);
                  SPVM_ALLOCATOR_free_block_compile_tmp(compiler, src);
                  return 0;
                }
                fclose(fh);
                src[file_size] = '\0';
                
                found_module_source = src;
                SPVM_HASH_insert(compiler->module_source_symtable, class_name, strlen(class_name), src);
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
                char* embedded_file_name = (char*)SPVM_ALLOCATOR_new_block_compile_eternal(compiler, 11 + strlen(cur_rel_file) + 1);
                sprintf(embedded_file_name, "embedded://%s", cur_rel_file);
                compiler->cur_file = embedded_file_name;
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
        compiler->befbufptr = compiler->bufptr;
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
        compiler->befbufptr = compiler->bufptr;
        continue;
      }
      // Cancat
      case '.': {
        if (state_var_expansion == SPVM_TOKE_C_STATE_VAR_EXPANSION_FIRST_CONCAT) {
          compiler->state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_VAR;
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CONCAT);
          return '.';
        }
        else if (state_var_expansion == SPVM_TOKE_C_STATE_VAR_EXPANSION_SECOND_CONCAT) {
          compiler->state_var_expansion = SPVM_TOKE_C_STATE_VAR_EXPANSION_DOUBLE_QUOTE;
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CONCAT);
          return '.';
        }
        else {
          compiler->bufptr++;
          if (*compiler->bufptr == '=') {
            compiler->bufptr++;
            SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
            op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_CONCAT;
            
            yylvalp->opval = op_special_assign;
            
            return SPECIAL_ASSIGN;
          }
          else if (*compiler->bufptr == '.' && *(compiler->bufptr + 1) == '.') {
            compiler->bufptr += 2;
            yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DOT3);
            return DOT3;
          }
          else {
            yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CONCAT);
            return '.';
          }
        }
      }
      // Addition
      case '+':
        compiler->bufptr++;
        
        if (*compiler->bufptr == '+') {
          compiler->bufptr++;
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NULL);
          return INC;
        }
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_ADD;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NULL);
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
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NULL);
          compiler->expect_method_name = 1;
          compiler->before_token_is_arrow = 1;
          
          return ARROW;
        }
        else if (*compiler->bufptr == '-') {
          compiler->bufptr++;
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NULL);
          return DEC;
        }
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_SUBTRACT;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NULL);;
          return '-';
        }
      // Multiply
      case '*': {
        compiler->bufptr++;
        
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MULTIPLY;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        // * is used in MULTIPLY operator or type reference
        else {
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NULL);
          yylvalp->opval = op;
          return '*';
        }
      }
      // Divide
      case '/': {
        compiler->bufptr++;
        
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_DIVIDE;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DIVIDE);
          yylvalp->opval = op;
          return DIVIDE;
        }
      }
      case '%': {
        compiler->bufptr++;
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_REMAINDER;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_REMAINDER);
          yylvalp->opval = op;
          return REMAINDER;
        }
      }
      case '^': {
        compiler->bufptr++;
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_XOR;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_BIT_XOR);
          yylvalp->opval = op;
          return BIT_XOR;
        }
      }
      case '|':
        compiler->bufptr++;
        // Or
        if (*compiler->bufptr == '|') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_LOGICAL_OR);
          yylvalp->opval = op;
          return LOGICAL_OR;
        }
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_OR;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_BIT_OR);
          yylvalp->opval = op;
          return BIT_OR;
        }

      case '&':
        compiler->bufptr++;
        // &&
        if (*compiler->bufptr == '&') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_LOGICAL_AND);
          yylvalp->opval = op;
          return LOGICAL_AND;
        }
        // &=
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        // &foo - Current class
        else if (isalpha(*compiler->bufptr) || *compiler->bufptr == '_') {
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CURRENT_CLASS);
          compiler->expect_method_name = 1;
          return CURRENT_CLASS;
        }
        // &
        else {
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_BIT_AND);
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
            SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NUMERIC_EQ);
            yylvalp->opval = op;
            return NUMEQ;
          }
          // =>
          if (*compiler->bufptr == '>') {
            compiler->bufptr++;
            SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NULL);
            yylvalp->opval = op;
            return ',';
          }
          // =
          else {
            SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ASSIGN);
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
            SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
            op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_LEFT_SHIFT;
            
            yylvalp->opval = op_special_assign;
            
            return SPECIAL_ASSIGN;
          }
          // <<
          else {
            SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_LEFT_SHIFT);
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
            SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NUMERIC_CMP);
            yylvalp->opval = op;
            return NUMERIC_CMP;
          }
          // <=
          else {
            SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NUMERIC_LE);
            yylvalp->opval = op;
            return NUMLE;
          }
        }
        // <
        else {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NUMERIC_LT);
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
              SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
              op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_LOGICAL_SHIFT;
              
              yylvalp->opval = op_special_assign;
              
              return SPECIAL_ASSIGN;
            }
            // >>>
            else {
              SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT);
              yylvalp->opval = op;
              return SHIFT;
            }
          }
          else {
            // >>=
            if (*compiler->bufptr == '=') {
              compiler->bufptr++;
              SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
              op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_ARITHMETIC_SHIFT;
              
              yylvalp->opval = op_special_assign;
              
              return SPECIAL_ASSIGN;
            }
            // >>
            else {
              SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT);
              yylvalp->opval = op;
              return SHIFT;
            }
          }
        }
        // >=
        else if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NUMERIC_GE);
          yylvalp->opval = op;
          return NUMGE;
        }
        // >
        else {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NUMERIC_GT);
          yylvalp->opval = op;
          return NUMGT;
        }
      case '!':
        compiler->bufptr++;
        
        if (*compiler->bufptr == '=') {
          compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NUMERIC_NE);
          yylvalp->opval = op;
          return NUMNE;
        }
        else {
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_LOGICAL_NOT);
          yylvalp->opval = op;
          return LOGICAL_NOT;
        }
      case '~': {
        compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_BIT_NOT);
          yylvalp->opval = op;
        return BIT_NOT;
      }
      // Character literals
      case '\'': {
        compiler->bufptr++;
        char ch = 0;
        
        if (*compiler->bufptr == '\'') {
          SPVM_COMPILER_error(compiler, "Character literals must have at least one character at %s line %d", compiler->cur_file, compiler->cur_line);
          compiler->bufptr++;
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
              if (isdigit(*compiler->bufptr)
                  || (*compiler->bufptr >= 'a' && *compiler->bufptr <= 'f')
                  || (*compiler->bufptr >= 'A' && *compiler->bufptr <= 'F'))
              {
                int32_t memory_blocks_count_compile_tmp = compiler->allocator->memory_blocks_count_compile_tmp;
                
                char* num_str = SPVM_ALLOCATOR_new_block_compile_tmp(compiler, 3);
                num_str[0] = *compiler->bufptr;
                compiler->bufptr++;
                if (
                  isdigit(*compiler->bufptr)
                  || (*compiler->bufptr >= 'a' && *compiler->bufptr <= 'f')
                  || (*compiler->bufptr >= 'A' && *compiler->bufptr <= 'F'))
                {
                  num_str[1] = *compiler->bufptr;
                  compiler->bufptr++;
                  char *end;
                  ch = (char)strtol(num_str, &end, 16);
                }
                else {
                  SPVM_COMPILER_error(compiler, "A invalid hexadecimal ascii code \"\\x%c%c\" in the second hexadecimal character of the charater literal at %s line %d", *(compiler->bufptr - 1), *compiler->bufptr, compiler->cur_file, compiler->cur_line);
                  compiler->bufptr++;
                }
                SPVM_ALLOCATOR_free_block_compile_tmp(compiler, num_str);
                assert(compiler->allocator->memory_blocks_count_compile_tmp == memory_blocks_count_compile_tmp);
              }
              else {
                SPVM_COMPILER_error(compiler, "A invalid hexadecimal ascii code \"\\x%c%c\" in the first hexadecimal character of the charater literal at %s line %d", *compiler->bufptr, *(compiler->bufptr + 1), compiler->cur_file, compiler->cur_line);
                compiler->bufptr += 2;
              }
            }
            else {
              SPVM_COMPILER_error(compiler, "A invalid escape character \"\\%c\" in the charater literal at %s line %d", *compiler->bufptr, compiler->cur_file, compiler->cur_line);
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
            SPVM_COMPILER_error(compiler, "Can't find the keyword_terminiator \"'\" of the character literal at %s line %d", compiler->cur_file, compiler->cur_line);
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
            SPVM_COMPILER_error(compiler, "Can't find string keyword_terminator '\"' anywhere before EOF at %s line %d", compiler->cur_file, compiler->cur_line);
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
                      SPVM_COMPILER_error(compiler, "Invalid ascii code in escape character of string literal at %s line %d", compiler->cur_file, compiler->cur_line);
                    }
                    SPVM_ALLOCATOR_free_block_compile_tmp(compiler, num_str);
                    assert(compiler->allocator->memory_blocks_count_compile_tmp == memory_blocks_count_compile_tmp);
                  }
                  else {
                    SPVM_COMPILER_error(compiler, "Invalid ascii code in escape character of string literal at %s line %d", compiler->cur_file, compiler->cur_line);
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
                        SPVM_COMPILER_error(compiler, "Unicode code point is empty at %s line %d", compiler->cur_file, compiler->cur_line);
                      }
                      else if (unicode_chars_length > 8) {
                        SPVM_COMPILER_error(compiler, "Too big unicode code point at %s line %d", compiler->cur_file, compiler->cur_line);
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
                          SPVM_COMPILER_error(compiler, "Invalid unicode code point at %s line %d", compiler->cur_file, compiler->cur_line);
                        }
                        SPVM_ALLOCATOR_free_block_compile_tmp(compiler, unicode_chars);
                        assert(compiler->allocator->memory_blocks_count_compile_tmp == memory_blocks_count_compile_tmp);
                      }
                    }
                    else {
                      SPVM_COMPILER_error(compiler, "Unicode escape need close bracket at %s line %d", compiler->cur_file, compiler->cur_line);
                    }
                  }
                  else {
                    SPVM_COMPILER_error(compiler, "Invalid unicode escape of string literal at %s line %d", compiler->cur_file, compiler->cur_line);
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
                      SPVM_COMPILER_error(compiler, "Invalid escape character in string literal \"\\%c\" at %s line %d", *char_ptr, compiler->cur_file, compiler->cur_line);
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
        char* found_str = SPVM_HASH_fetch(compiler->string_symtable, str_tmp, str_length);
        if (found_str) {
          str = found_str;
        }
        else {
          str = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, str_length + 1);
          memcpy(str, str_tmp, str_length);
          SPVM_LIST_push(compiler->strings, str);
          SPVM_HASH_insert(compiler->string_symtable, str, str_length, str);
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
        SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CREATE_REF);
        yylvalp->opval = op;
        return CREATE_REF;
      default:
        // Variable
        if (ch == '$') {
          // Derefernece
          if (*(compiler->bufptr + 1) == '$') {
            compiler->bufptr++;
            SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DEREF);
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
            
            // Variable name
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
                  SPVM_COMPILER_error(compiler, "Single colon \":\" in variable name is invalid at %s line %d", compiler->cur_file, compiler->cur_line);
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
            char* found_var_name = SPVM_HASH_fetch(compiler->string_symtable, cur_token_ptr - 1, var_name_length);
            if (found_var_name) {
              var_name = found_var_name;
            }
            else {
              var_name = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, 1 + var_name_length_without_sigil + 1);
              var_name[0] = '$';
              memcpy(&var_name[1], cur_token_ptr, var_name_length_without_sigil);
              var_name[1 + var_name_length_without_sigil] = '\0';
              SPVM_LIST_push(compiler->strings, var_name);
              SPVM_HASH_insert(compiler->string_symtable, var_name, var_name_length_without_sigil + 1, var_name);
            }

            if (have_brace) {
              if (*compiler->bufptr == '}') {
                compiler->bufptr++;
              }
              else {
                SPVM_COMPILER_error(compiler, "Need close brace at end of variable at %s line %d", compiler->cur_file, compiler->cur_line);
              }
            }

            // Name OP
            SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, var_name, compiler->cur_file, compiler->cur_line);

            yylvalp->opval = op_name;

            // Variable name can't conatain __
            if (strstr(var_name, "__")) {
              SPVM_COMPILER_error(compiler, "Variable name \"%s\" can't contain \"__\" at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
            }

            if (strstr(var_name, ":::")) {
              SPVM_COMPILER_error(compiler, "Variable name \"%s\" can't contain \":::\" at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
            }

            // Variable name can't start with number
            if (isdigit(var_name[1])) {
              SPVM_COMPILER_error(compiler, "Variable name \"%s\" must not start with number at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
            }

            if (strlen(var_name) > 1 && var_name[var_name_length_without_sigil] == ':' && var_name[var_name_length_without_sigil - 1] == ':') {
              SPVM_COMPILER_error(compiler, "Variable name \"%s\" must not end with \"::\" at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
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
          int32_t num_str_memoyr_blocks_count = compiler->allocator->memory_blocks_count_compile_tmp;
          char* num_str = (char*)SPVM_ALLOCATOR_new_block_compile_tmp(compiler, str_len + 2);
          int32_t pos = 0;
          {
            int32_t i;
            for (i = 0; i < str_len; i++) {
              if (*(cur_token_ptr + i) != '_') {
                *(num_str + pos) = *(cur_token_ptr + i);
                pos++;
              }
            }
            num_str[pos] = '\0';
          }
          // Back suffix such as "f" or "F" when hex floating number
          if (is_hex_floating_number && !isdigit(*(compiler->bufptr - 1))) {
            compiler->bufptr--;
            num_str[pos - 1] = '\0';
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
              SPVM_COMPILER_error(compiler, "Invalid float literal at %s line %d", compiler->cur_file, compiler->cur_line);
            }
            op_constant = SPVM_OP_new_op_constant_float(compiler, (float)num, compiler->cur_file, compiler->cur_line);
          }
          // double
          else if (constant_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
            
            double num = strtod(num_str, &end);
            if (*end != '\0') {
              SPVM_COMPILER_error(compiler, "Invalid double literal at %s line %d", compiler->cur_file, compiler->cur_line);
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
              SPVM_COMPILER_error(compiler, "Invalid int literal at %s line %d", compiler->cur_file, compiler->cur_line);
            }
            else if (out_of_range) {
              SPVM_COMPILER_error(compiler, "int literal out of range at %s line %d", compiler->cur_file, compiler->cur_line);
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
              SPVM_COMPILER_error(compiler, "Invalid long literal at %s line %d", compiler->cur_file, compiler->cur_line);
            }
            else if (out_of_range) {
              SPVM_COMPILER_error(compiler, "long literal out of range at %s line %d", compiler->cur_file, compiler->cur_line);
            }
            op_constant = SPVM_OP_new_op_constant_long(compiler, num, compiler->cur_file, compiler->cur_line);
          }
          else {
            assert(0);
          }

          SPVM_ALLOCATOR_free_block_compile_tmp(compiler, num_str);
          assert(compiler->allocator->memory_blocks_count_compile_tmp == num_str_memoyr_blocks_count);

          
          yylvalp->opval = op_constant;
          
          return CONSTANT;
        }
        // Keyword or name
        else if (isalpha(ch) || ch == '_') {
          // Keyword start position
          int32_t column = compiler->bufptr - compiler->line_start_ptr;
          
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
          
          // Keyword name
          char* symbol_name;
          int32_t symbol_name_length = (compiler->bufptr - cur_token_ptr);
          char* found_name = SPVM_HASH_fetch(compiler->string_symtable, cur_token_ptr, symbol_name_length);
          if (found_name) {
            symbol_name = found_name;
          }
          else {
            symbol_name = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, symbol_name_length + 1);
            memcpy(symbol_name, cur_token_ptr, symbol_name_length);
            symbol_name[symbol_name_length] = '\0';
            SPVM_LIST_push(compiler->strings, symbol_name);
            SPVM_HASH_insert(compiler->string_symtable, symbol_name, symbol_name_length, symbol_name);
          }

          // If following token is fat comma, symbol_name is manipulated as string literal
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
            SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, symbol_name, symbol_name_length, compiler->cur_file, compiler->cur_line);
            
            yylvalp->opval = op_constant;
            
            return CONSTANT;
          }
          
          // Check if the symbol is symbol_name
          int32_t is_keyword = 0;
          int32_t keyword_term = 0;
          if (expect_method_name) {
            // None
          }
          else if (expect_field_name) {
            // None
          }
          else {
            // Keywords
            switch (symbol_name[0]) {
              // Keyword
              case 'a' : {
                if (strcmp(symbol_name, "allow") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ALLOW);
                  is_keyword = 1;
                  keyword_term = ALLOW;
                }
                else if (strcmp(symbol_name, "as") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_AS);
                  is_keyword = 1;
                  keyword_term = AS;
                }
                break;
              }
              case 'b' : {
                if (strcmp(symbol_name, "break") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_BREAK);
                  is_keyword = 1;
                  keyword_term = BREAK;
                }
                else if (strcmp(symbol_name, "byte") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_BYTE);
                  is_keyword = 1;
                  keyword_term = BYTE;
                }
                break;
              }
              case 'c' : {
                if (strcmp(symbol_name, "callback_t") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_CALLBACK_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "case") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CASE);
                  is_keyword = 1;
                  keyword_term = CASE;
                }
                else if (strcmp(symbol_name, "cmp") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_CMP);
                  is_keyword = 1;
                  keyword_term = STRING_CMP;
                }
                else if (strcmp(symbol_name, "class") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CLASS);
                  is_keyword = 1;
                  keyword_term = CLASS;
                }
                else if (strcmp(symbol_name, "copy") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_COPY);
                  is_keyword = 1;
                  keyword_term = COPY;
                }
                break;
              }
              case 'd' : {
                if (strcmp(symbol_name, "default") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DEFAULT);
                  is_keyword = 1;
                  keyword_term = DEFAULT;
                }
                else if (strcmp(symbol_name, "die") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DIE);
                  is_keyword = 1;
                  keyword_term = DIE;
                }
                else if (strcmp(symbol_name, "divui") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT);
                  is_keyword = 1;
                  keyword_term = DIVIDE_UNSIGNED_INT;
                }
                else if (strcmp(symbol_name, "divul") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG);
                  is_keyword = 1;
                  keyword_term = DIVIDE_UNSIGNED_LONG;
                }
                else if (strcmp(symbol_name, "double") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DOUBLE);
                  is_keyword = 1;
                  keyword_term = DOUBLE;
                }
                else if (strcmp(symbol_name, "dump") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DUMP);
                  is_keyword = 1;
                  keyword_term = DUMP;
                }
                break;
              }
              case 'e' : {
                if (strcmp(symbol_name, "elsif") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ELSIF);
                  is_keyword = 1;
                  keyword_term = ELSIF;
                }
                else if (strcmp(symbol_name, "else") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ELSE);
                  is_keyword = 1;
                  keyword_term = ELSE;
                }
                else if (strcmp(symbol_name, "enum") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ENUM);
                  is_keyword = 1;
                  keyword_term = ENUM;
                }
                else if (strcmp(symbol_name, "eq") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_EQ);
                  is_keyword = 1;
                  keyword_term = STREQ;
                }
                else if (strcmp(symbol_name, "eval") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_EVAL);
                  is_keyword = 1;
                  keyword_term = EVAL;
                }
                break;
              }
              case 'f' : {
                if (strcmp(symbol_name, "for") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_FOR);
                  is_keyword = 1;
                  keyword_term = FOR;
                }
                else if (strcmp(symbol_name, "float") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_FLOAT);
                  is_keyword = 1;
                  keyword_term = FLOAT;
                }
                else if (strcmp(symbol_name, "false") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_FALSE);
                  is_keyword = 1;
                  keyword_term = FALSE;
                }
                break;
              }
              case 'g' : {
                if (strcmp(symbol_name, "gt") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_GT);
                  is_keyword = 1;
                  keyword_term = STRGT;
                }
                else if (strcmp(symbol_name, "ge") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_GE);
                  is_keyword = 1;
                  keyword_term = STRGE;
                }
                break;
              }
              case 'h' : {
                if (strcmp(symbol_name, "has") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_FIELD);
                  compiler->expect_field_name = 1;
                  is_keyword = 1;
                  keyword_term = HAS;
                }
                else if (strcmp(symbol_name, "has_implement") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_HAS_IMPLEMENT);
                  is_keyword = 1;
                  keyword_term = HAS_IMPLEMENT;
                }
                break;
              }
              case 'i' : {
                if (strcmp(symbol_name, "if") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_IF);
                  is_keyword = 1;
                  keyword_term = IF;
                }
                else if (strcmp(symbol_name, "isa") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ISA);
                  is_keyword = 1;
                  keyword_term = ISA;
                }
                else if (strcmp(symbol_name, "isweak") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ISWEAK);
                  is_keyword = 1;
                  keyword_term = ISWEAK;
                }
                else if (strcmp(symbol_name, "is_read_only") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_IS_READ_ONLY);
                  is_keyword = 1;
                  keyword_term = IS_READ_ONLY;
                }
                else if (strcmp(symbol_name, "implement") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_IMPLEMENT);
                  is_keyword = 1;
                  keyword_term = IMPLEMENT;
                }
                else if (strcmp(symbol_name, "int") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_INT);
                  is_keyword = 1;
                  keyword_term = INT;
                }
                else if (strcmp(symbol_name, "interface_t") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_INTERFACE_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                break;
              }
              case 'l' : {
                if (strcmp(symbol_name, "last") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_LAST);
                  is_keyword = 1;
                  keyword_term = LAST;
                }
                else if (strcmp(symbol_name, "length") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_LENGTH);
                  is_keyword = 1;
                  keyword_term = STRING_LENGTH;
                }
                else if (strcmp(symbol_name, "lt") == 0) {
                  SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_LT);
                  yylvalp->opval = op;
                  
                  is_keyword = 1;
                  keyword_term = STRLT;
                }
                else if (strcmp(symbol_name, "le") == 0) {
                  SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_LE);
                  yylvalp->opval = op;
                  
                  is_keyword = 1;
                  keyword_term = STRLE;
                }
                else if (strcmp(symbol_name, "long") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_LONG);
                  is_keyword = 1;
                  keyword_term = LONG;
                }
                break;
              }
              case 'm' : {
                if (strcmp(symbol_name, "make_read_only") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_MAKE_READ_ONLY);
                  is_keyword = 1;
                  keyword_term = MAKE_READ_ONLY;
                }
                else if (strcmp(symbol_name, "my") == 0) {
                  SPVM_MY* my = SPVM_MY_new(compiler);
                  yylvalp->opval = SPVM_OP_new_op_my(compiler, my, compiler->cur_file, compiler->cur_line);
                  is_keyword = 1;
                  keyword_term = MY;
                }
                else if (strcmp(symbol_name, "mulnum_t") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_MULNUM_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "method") == 0) {
                  SPVM_OP* op_method = SPVM_TOKE_new_op_with_column(compiler, SPVM_OP_C_ID_METHOD, column);
                  yylvalp->opval = op_method;

                  compiler->expect_method_name = 1;

                  is_keyword = 1;
                  keyword_term = METHOD;
                }
                else if (strcmp(symbol_name, "mutable") == 0) {
                  SPVM_OP* op_mutable = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_MUTABLE);
                  is_keyword = 1;
                  keyword_term = MUTABLE;
                }
                break;
              }
              case 'n' : {
                if (strcmp(symbol_name, "native") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_NATIVE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "ne") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_NE);
                  is_keyword = 1;
                  keyword_term = STRNE;
                }
                else if (strcmp(symbol_name, "next") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NEXT);
                  is_keyword = 1;
                  keyword_term = NEXT;
                }
                else if (strcmp(symbol_name, "new") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NEW);
                  is_keyword = 1;
                  keyword_term = NEW;
                }
                else if (strcmp(symbol_name, "new_string_len") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NEW_STRING_LEN);
                  is_keyword = 1;
                  keyword_term = NEW_STRING_LEN;
                }
                break;
              }
              case 'o' : {
                if (strcmp(symbol_name, "our") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CLASS_VAR);
                  is_keyword = 1;
                  keyword_term = OUR;
                }
                else if (strcmp(symbol_name, "object") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_OBJECT);
                  is_keyword = 1;
                  keyword_term = OBJECT;
                }
                break;
              }
              case 'p' : {
                if (strcmp(symbol_name, "print") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_PRINT);
                  is_keyword = 1;
                  keyword_term = PRINT;
                }
                else if (strcmp(symbol_name, "private") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_PRIVATE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "public") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_PUBLIC, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "precompile") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_PRECOMPILE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "pointer_t") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_POINTER_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                break;
              }
              case 'r' : {
                if (strcmp(symbol_name, "ref") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_REFOP);
                  is_keyword = 1;
                  keyword_term = REFOP;
                }
                else if (strcmp(symbol_name, "refcnt") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_REFCNT);
                  is_keyword = 1;
                  keyword_term = REFCNT;
                }
                else if (strcmp(symbol_name, "remui") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_REMAINDER_UNSIGNED_INT);
                  is_keyword = 1;
                  keyword_term = REMAINDER_UNSIGNED_INT;
                }
                else if (strcmp(symbol_name, "remul") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_REMAINDER_UNSIGNED_LONG);
                  is_keyword = 1;
                  keyword_term = REMAINDER_UNSIGNED_LONG;
                }
                else if (strcmp(symbol_name, "return") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_RETURN);
                  is_keyword = 1;
                  keyword_term = RETURN;
                }
                else if (strcmp(symbol_name, "require") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_REQUIRE);
                  is_keyword = 1;
                  keyword_term = REQUIRE;
                }
                else if (strcmp(symbol_name, "rw") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_RW, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "ro") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_RO, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                break;
              }
              case 's' : {
                if (strcmp(symbol_name, "static") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_STATIC, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "switch") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SWITCH);
                  is_keyword = 1;
                  keyword_term = SWITCH;
                }
                else if (strcmp(symbol_name, "string") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING);
                  is_keyword = 1;
                  keyword_term = STRING;
                }
                else if (strcmp(symbol_name, "short") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SHORT);
                  is_keyword = 1;
                  keyword_term = SHORT;
                }
                else if (strcmp(symbol_name, "scalar") == 0) {
                  compiler->bufptr++;
                  SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SCALAR);
                  yylvalp->opval = op;
                  
                  is_keyword = 1;
                  keyword_term = SCALAR;
                }
                break;
              }
              case 't' : {
                if (strcmp(symbol_name, "true") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_TRUE);
                  is_keyword = 1;
                  keyword_term = TRUE;
                }
                break;
              }
              case 'u' : {
                if (strcmp(symbol_name, "undef") == 0) {
                  yylvalp->opval = SPVM_OP_new_op_undef(compiler, compiler->cur_file, compiler->cur_line);
                  is_keyword = 1;
                  keyword_term = UNDEF;
                }
                else if (strcmp(symbol_name, "unless") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_UNLESS);
                  is_keyword = 1;
                  keyword_term = UNLESS;
                }
                else if (strcmp(symbol_name, "unweaken") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_UNLESS);
                  is_keyword = 1;
                  keyword_term = UNWEAKEN;
                }
                else if (strcmp(symbol_name, "use") == 0) {
                  yylvalp->opval = SPVM_OP_new_op_use(compiler, compiler->cur_file, compiler->cur_line);
                  is_keyword = 1;
                  keyword_term = USE;
                }
                break;
              }
              case 'v' : {
                if (strcmp(symbol_name, "void") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_VOID);
                  is_keyword = 1;
                  keyword_term = VOID;
                }
                break;
              }
              case 'w' : {
                if (strcmp(symbol_name, "warn") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_WARN);
                  is_keyword = 1;
                  keyword_term = WARN;
                }
                else if (strcmp(symbol_name, "while") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_WHILE);
                  is_keyword = 1;
                  keyword_term = WHILE;
                }
                else if (strcmp(symbol_name, "weaken") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_WEAKEN);
                  is_keyword = 1;
                  keyword_term = WEAKEN;
                }
                else if (strcmp(symbol_name, "wo") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_WO, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  is_keyword = 1;
                  keyword_term = DESCRIPTOR;
                }
                break;
              }
              case 'I' : {
                if (strcmp(symbol_name, "INIT") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_INIT);
                  is_keyword = 1;
                  keyword_term = INIT;
                }
                break;
              }
              case '_': {
                if (strcmp(symbol_name, "__END__") == 0) {
                  *compiler->bufptr = '\0';
                  continue;
                }
                else if (strcmp(symbol_name, "__CLASS__") == 0) {
                  yylvalp->opval = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CURRENT_CLASS_NAME, compiler->cur_file, compiler->cur_line);
                  is_keyword = 1;
                  keyword_term = CURRENT_CLASS_NAME;
                }
                else if (strcmp(symbol_name, "__FILE__") == 0) {
                  SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, compiler->cur_rel_file, strlen(compiler->cur_rel_file), compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_constant;
                  is_keyword = 1;
                  keyword_term = CONSTANT;
                }
                else if (strcmp(symbol_name, "__LINE__") == 0) {
                  SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, compiler->cur_line, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_constant;
                  is_keyword = 1;
                  keyword_term = CONSTANT;
                }
                break;
              }
            }
          }
          
          // Keyword
          int32_t term;
          if (is_keyword) {
            assert(keyword_term > 0);
            term = keyword_term;
          }
          // Symbol name
          else {
            // Symbol name can't conatain __
            if (strstr(symbol_name, "__")) {
              SPVM_COMPILER_error(compiler, "Symbol name \"%s\" must not contains __ at %s line %d", symbol_name, compiler->cur_file, compiler->cur_line);
            }

            SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, symbol_name, compiler->cur_file, compiler->cur_line);
            yylvalp->opval = op_name;
            
            term = NAME;
          }
          
          return term;
        }
        
        // Return character
        compiler->bufptr++;
        yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NULL);
        
        // Expect field name
        if (before_token_is_arrow && ch == '{') {
          compiler->expect_field_name = 1;
        }
        
        return (int) (uint8_t) ch;
    }
  }
}


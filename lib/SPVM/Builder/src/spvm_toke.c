#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <inttypes.h>

#include "spvm_toke.h"
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
#include "spvm_var_decl.h"
#include "spvm_string_buffer.h"
#include "spvm_method.h"
#include "spvm_class.h"
#include "spvm_constant_string.h"

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

int32_t SPVM_TOKE_is_hex_number(SPVM_COMPILER* compiler, char ch) {
  (void)compiler;
  // SP, CR, LF, HT, FF
  if (isdigit(ch) || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F')) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TOKE_is_unicode_scalar_value(int32_t code_point) {
  int32_t is_unicode_scalar_value = 0;
  if (code_point >= 0 && code_point <= 0x10FFFF) {
    if (!(code_point >= 0xD800 && code_point <= 0xDFFF)) {
      is_unicode_scalar_value = 1;
    }
  }
  
  return is_unicode_scalar_value;
}

int32_t SPVM_TOKE_convert_unicode_codepoint_to_utf8_character(int32_t uc, uint8_t* dst) {
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
  int32_t before_char_is_minus = 0;
  
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
  int32_t var_expansion_state = compiler->var_expansion_state;
  compiler->var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_DEFAULT;

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
      var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_SECOND_CONCAT;
    }
    
    // Variable expansion state
    if (var_expansion_state == SPVM_TOKE_C_VAR_EXPANSION_STATE_FIRST_CONCAT) {
      ch = '.';
    }
    else if (var_expansion_state == SPVM_TOKE_C_VAR_EXPANSION_STATE_SECOND_CONCAT) {
      ch = '.';
    }
    else if (var_expansion_state == SPVM_TOKE_C_VAR_EXPANSION_STATE_BEGIN_NEXT_STRING_LITERAL) {
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
          
          const char* class_name = op_use->uv.use->class_name;
          int32_t class_name_length = strlen(class_name);

          // Check the class name
          {
            // A class name must begin with a upper case character
            if (islower(class_name[0])) {
              SPVM_COMPILER_error(compiler, "The class name \"%s\" must begin with a upper case character at %s line %d", class_name, op_use->file, op_use->line);
              return 0;
            }

            // Part names of the class name begin with lower case
            int32_t class_part_name_is_invalid = 0;
            int32_t class_name_length = strlen(class_name);
            for (int32_t i = 0; i < class_name_length; i++) {
              if (i > 1) {
                if (class_name[i - 2] == ':' && class_name[i - 1] == ':') {
                  if (islower(class_name[i])) {
                    SPVM_COMPILER_error(compiler, "The part names of the class \"%s\" must begin with a upper case character at %s line %d", class_name, op_use->file, op_use->line);
                    return 0;
                  }
                }
              }
            }

            // A class name can't conatain "__"
            if (strstr(class_name, "__")) {
              SPVM_COMPILER_error(compiler, "The class name \"%s\" can't constain \"__\" at %s line %d", class_name, op_use->file, op_use->line);
              return 0;
            }
            
            // A class name can't end with "::"
            if (class_name_length >= 2 && class_name[class_name_length - 2] == ':' && class_name[class_name_length - 1] == ':' ) {
              SPVM_COMPILER_error(compiler, "The class name \"%s\" can't end with \"::\" at %s line %d", class_name, op_use->file, op_use->line);
              return 0;
            }

            // A class name can't contains "::::".
            if (strstr(class_name, "::::")) {
              SPVM_COMPILER_error(compiler, "The class name \"%s\" can't contains \"::::\" at %s line %d", class_name, op_use->file, op_use->line);
              return 0;
            }

            // A class name can't begin with \"$::\"
            if (class_name_length >= 2 && class_name[0] == ':' && class_name[1] == ':') {
              SPVM_COMPILER_error(compiler, "The class name \"%s\" can't begin with \"::\" at %s line %d", class_name, op_use->file, op_use->line);
              return 0;
            }

            // A class name can't begin with a number
            if (class_name_length >= 1 && isdigit(class_name[0])) {
              SPVM_COMPILER_error(compiler, "The class name \"%s\" can't begin with a number at %s line %d", class_name, op_use->file, op_use->line);
              return 0;
            }
          }

          const char* used_class_name = (const char*)SPVM_HASH_get(compiler->used_class_symtable, class_name, strlen(class_name));

          if (used_class_name) {
            continue;
          }
          else {
            SPVM_HASH_set(compiler->used_class_symtable, class_name, strlen(class_name), (void*)class_name);
            
            // Create moudle relative file name from class name by changing :: to / and add ".spvm"
            int32_t cur_rel_file_length = (int32_t)(strlen(class_name) + 6);
            char* cur_rel_file = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, cur_rel_file_length + 1);
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
            const char* found_module_source = SPVM_HASH_get(compiler->module_source_symtable, class_name, strlen(class_name));
            const char* module_dir = NULL;
            if (!found_module_source) {
              // Search module file
              FILE* fh = NULL;
              int32_t module_dirs_length = compiler->module_dirs->length;
              for (int32_t i = 0; i < module_dirs_length; i++) {
                module_dir = (const char*) SPVM_LIST_get(compiler->module_dirs, i);
                
                // File name
                int32_t file_name_length = (int32_t)(strlen(module_dir) + 1 + strlen(cur_rel_file));
                cur_file = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, file_name_length + 1);
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
                    const char* module_dir = (const char*) SPVM_LIST_get(compiler->module_dirs, i);
                    moduler_dirs_str_length += 1 + strlen(module_dir);
                  }
                  char* moduler_dirs_str = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, moduler_dirs_str_length + 1);
                  int32_t moduler_dirs_str_offset = 0;
                  for (int32_t i = 0; i < module_dirs_length; i++) {
                    const char* module_dir = (const char*) SPVM_LIST_get(compiler->module_dirs, i);
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
                char* src = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, file_size + 1);
                if ((int32_t)fread(src, 1, file_size, fh) < file_size) {
                  SPVM_COMPILER_error(compiler, "Can't read file %s at %s line %d", cur_file, op_use->file, op_use->line);
                  SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, src);
                  return 0;
                }
                fclose(fh);
                src[file_size] = '\0';
                
                found_module_source = src;
                SPVM_HASH_set(compiler->module_source_symtable, class_name, strlen(class_name), src);
              }
            }
            
            const char* src = NULL;
            int32_t file_size = 0;
            if (found_module_source) {
              src = found_module_source;
              file_size = strlen(src);

              // Copy original source to current source because original source is used at other places(for example, SPVM::Builder::Exe)
              compiler->cur_src = (char*)src;
              compiler->cur_dir = module_dir;
              compiler->cur_rel_file = cur_rel_file;
              compiler->cur_rel_file_class_name = class_name;
              
              // If we get current module file path, set it, otherwise set module relative file path
              if (cur_file) {
                compiler->cur_file = cur_file;
              }
              else {
                char* embedded_file_name = (char*)SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, 11 + strlen(cur_rel_file) + 1);
                sprintf(embedded_file_name, "embedded://%s", cur_rel_file);
                compiler->cur_file = embedded_file_name;
              }
              
              SPVM_CONSTANT_STRING* cur_file_string = SPVM_CONSTANT_STRING_new(compiler, compiler->cur_file, strlen(compiler->cur_file));
              compiler->cur_file = cur_file_string->value;
              
              // Set initial information for tokenization
              compiler->bufptr = compiler->cur_src;
              compiler->befbufptr = compiler->cur_src;
              compiler->line_start_ptr = compiler->cur_src;
              compiler->cur_line = 1;
            }
            else {
              // If module not found and the module is used in require syntax, compilation errors don't occur.
              if (op_use->uv.use->is_require) {
                SPVM_HASH_set(compiler->not_found_class_class_symtable, class_name, strlen(class_name), (void*)class_name);
                continue;
              }
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
        break;
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
        break;
      }
      // Cancat
      case '.': {
        if (var_expansion_state == SPVM_TOKE_C_VAR_EXPANSION_STATE_FIRST_CONCAT) {
          compiler->var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_VAR;
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CONCAT);
          return '.';
        }
        else if (var_expansion_state == SPVM_TOKE_C_VAR_EXPANSION_STATE_SECOND_CONCAT) {
          compiler->var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_BEGIN_NEXT_STRING_LITERAL;
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
        break;
      }
      // Addition
      case '+': {
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
        break;
      }
      // Subtract
      case '-': {
        compiler->bufptr++;
        
        // "-" is the sign of a numeric literal
        if (isdigit(*compiler->bufptr)) {
          before_char_is_minus = 1;
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
        break;
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
      case '|': {
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
        break;
      }
      case '&': {
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
        break;
      }
      // Comment
      case '#': {
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
        break;
      }
      case '=': {
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
        break;
      }
      case '<': {
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
        break;
      }
      case '>': {
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
        break;
      }
      case '!': {
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
        break;
      }
      case '~': {
        compiler->bufptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_BIT_NOT);
          yylvalp->opval = op;
        return BIT_NOT;
        break;
      }
      // Character literals
      case '\'': {
        compiler->bufptr++;
        char ch = 0;
        
        if (*compiler->bufptr == '\'') {
          SPVM_COMPILER_error(compiler, "A character literal can't be empty at %s line %d", compiler->cur_file, compiler->cur_line);
          compiler->bufptr++;
        }
        else {
          if (*compiler->bufptr == '\\') {
            compiler->bufptr++;
            if (*compiler->bufptr == '0') {
              ch = 0x00; // NUL
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 'a') {
              ch = 0x07; // BEL
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 't') {
              ch = 0x09; // HT
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 'n') {
              ch = 0x0a; // 
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 'f') {
              ch = 0x0c; // FF
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == 'r') {
              ch = 0x0d; // LF
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == '\'') {
              ch = 0x27; // '
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == '"') {
              ch = 0x22; // "
              compiler->bufptr++;
            }
            else if (*compiler->bufptr == '\\') {
              ch = 0x5c; /* \ */
              compiler->bufptr++;
            }
            // Hex ascii code
            else if (*compiler->bufptr == 'x') {
              compiler->bufptr++;

              // {
              int32_t has_brace = 0;
              if (*compiler->bufptr == '{') {
                has_brace = 1;
                compiler->bufptr++;
              }
              
              char hex_escape_char[3] = {0};
              int32_t hex_escape_char_index = 0;
              while (SPVM_TOKE_is_hex_number(compiler, *compiler->bufptr)) {
                if (hex_escape_char_index >= 2) {
                  break;
                }
                hex_escape_char[hex_escape_char_index] = *compiler->bufptr;
                compiler->bufptr++;
                hex_escape_char_index++;
              }
              
              if (strlen(hex_escape_char) > 0) {
                char* end;
                ch = (char)strtol(hex_escape_char, &end, 16);
              }
              else {
                SPVM_COMPILER_error(compiler, "After \"\\x\" of the hexadecimal escape character, one or tow hexadecimal numbers must follow at %s line %d", compiler->cur_file, compiler->cur_line);
              }
              
              if (has_brace) {
                if (*compiler->bufptr == '}') {
                  compiler->bufptr++;
                }
                else {
                  SPVM_COMPILER_error(compiler, "The hexadecimal escape character that has the opening \"{\" must have the closing \"}\" at %s line %d", compiler->cur_file, compiler->cur_line);
                }
              }
            }
            else {
              SPVM_COMPILER_error(compiler, "Invalid charater literal escape character \"\\%c\" at %s line %d", *compiler->bufptr, compiler->cur_file, compiler->cur_line);
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
            SPVM_COMPILER_error(compiler, "A character literal must ends with \"'\" at %s line %d", compiler->cur_file, compiler->cur_line);
          }
        }
        
        // Constant 
        SPVM_OP* op_constant = SPVM_OP_new_op_constant_byte(compiler, ch, compiler->cur_file, compiler->cur_line);
        
        yylvalp->opval = op_constant;
        
        return CONSTANT;
      }
      // String literal
      case '"': {
        if (var_expansion_state == SPVM_TOKE_C_VAR_EXPANSION_STATE_BEGIN_NEXT_STRING_LITERAL) {
          compiler->var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_DEFAULT;
        }
        else {
          compiler->bufptr++;
        }
        
        // Save current position
        const char* cur_token_ptr = compiler->bufptr;
        
        int8_t next_var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_DEFAULT;
        
        char* string_literal_tmp;
        int32_t memory_blocks_count_tmp = compiler->allocator->memory_blocks_count_tmp;
        int32_t string_literal_length = 0;
        if (*(compiler->bufptr) == '"') {
          string_literal_tmp = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, 1);
          string_literal_tmp[0] = '\0';
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
                // Last $ is allowed
              }
              else {
                finish = 1;
                next_var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_FIRST_CONCAT;
                
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
            SPVM_COMPILER_error(compiler, "A string literal must be end with '\"' at %s line %d", compiler->cur_file, compiler->cur_line);
            return 0;
          }
          
          int32_t string_literal_tmp_len = (int32_t)(compiler->bufptr - cur_token_ptr) * 4;

          compiler->bufptr++;
          
          string_literal_tmp = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, string_literal_tmp_len + 1);
          {
            char* char_ptr = (char*)cur_token_ptr;
            while (char_ptr != compiler->bufptr - 1) {
              if (*char_ptr == '\\') {
                char_ptr++;
                if (*char_ptr == '0') {
                  string_literal_tmp[string_literal_length] = 0x00;
                  string_literal_length++;
                  char_ptr++;
                }
                else if (*char_ptr == 'a') {
                  string_literal_tmp[string_literal_length] = 0x07;
                  string_literal_length++;
                  char_ptr++;
                }
                else if (*char_ptr == 't') {
                  string_literal_tmp[string_literal_length] = 0x09;
                  string_literal_length++;
                  char_ptr++;
                }
                else if (*char_ptr == 'n') {
                  string_literal_tmp[string_literal_length] = 0x0a;
                  string_literal_length++;
                  char_ptr++;
                }
                else if (*char_ptr == 'f') {
                  string_literal_tmp[string_literal_length] = 0x0c;
                  string_literal_length++;
                  char_ptr++;
                }
                else if (*char_ptr == 'r') {
                  string_literal_tmp[string_literal_length] = 0x0d;
                  string_literal_length++;
                  char_ptr++;
                }
                else if (*char_ptr == '"') {
                  string_literal_tmp[string_literal_length] = 0x22;
                  string_literal_length++;
                  char_ptr++;
                }
                else if (*char_ptr == '\'') {
                  string_literal_tmp[string_literal_length] = 0x27;
                  string_literal_length++;
                  char_ptr++;
                }
                else if (*char_ptr == '\\') {
                  string_literal_tmp[string_literal_length] = 0x5c;
                  string_literal_length++;
                  char_ptr++;
                }
                else if (*char_ptr == '$') {
                  string_literal_tmp[string_literal_length] = 0x44;
                  string_literal_length++;
                  char_ptr++;
                }
                // A hexadecimal escape character
                else if (*char_ptr == 'x') {
                  char_ptr++;

                  // {
                  int32_t has_brace = 0;
                  if (*char_ptr == '{') {
                    has_brace = 1;
                    char_ptr++;
                  }
                  
                  char hex_escape_char[3] = {0};
                  int32_t hex_escape_char_index = 0;
                  while (SPVM_TOKE_is_hex_number(compiler, *char_ptr)) {
                    if (hex_escape_char_index >= 2) {
                      break;
                    }
                    hex_escape_char[hex_escape_char_index] = *char_ptr;
                    char_ptr++;
                    hex_escape_char_index++;
                  }
                  
                  if (strlen(hex_escape_char) > 0) {
                    char* end;
                    ch = (char)strtol(hex_escape_char, &end, 16);
                    string_literal_tmp[string_literal_length] = ch;
                    string_literal_length++;
                  }
                  else {
                    SPVM_COMPILER_error(compiler, "After \"\\x\" of the hexadecimal escape character, one or tow hexadecimal numbers must follow at %s line %d", compiler->cur_file, compiler->cur_line);
                  }
                  
                  if (has_brace) {
                    if (*char_ptr == '}') {
                      char_ptr++;
                    }
                    else {
                      SPVM_COMPILER_error(compiler, "The hexadecimal escape character that has the opening \"{\" must have the closing \"}\" at %s line %d", compiler->cur_file, compiler->cur_line);
                    }
                  }
                }
                // Unicode escape character
                // Note: "\N" is raw escape character, "\N{" is Unicode escape character
                else if (*char_ptr == 'N' && *(char_ptr + 1) == '{') {
                  char_ptr++;
                  
                  if (*char_ptr == '{' && *(char_ptr + 1) == 'U' && *(char_ptr + 2) == '+') {
                    char_ptr += 3;
                    char* char_start_ptr = char_ptr;
                    int32_t unicode_chars_length = 0;
                    
                    while (SPVM_TOKE_is_hex_number(compiler, *char_ptr)) {
                      char_ptr++;
                      unicode_chars_length++;
                    }
                    if (*char_ptr == '}') {
                      char_ptr++;
                      if (unicode_chars_length < 1) {
                        SPVM_COMPILER_error(compiler, "After \"\\N{U+\" of the Unicode escape character, one or more than one hexadecimal numbers must follow at %s line %d", compiler->cur_file, compiler->cur_line);
                      }
                      else if (unicode_chars_length > 8) {
                        SPVM_COMPILER_error(compiler, "Too big Unicode escape character at %s line %d", compiler->cur_file, compiler->cur_line);
                      }
                      else {
                        int32_t memory_blocks_count_tmp = compiler->allocator->memory_blocks_count_tmp;
                        char* unicode_chars = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, unicode_chars_length + 1);
                        memcpy(unicode_chars, char_start_ptr, unicode_chars_length);
                        char *end;
                        int64_t unicode = (int64_t)strtoll(unicode_chars, &end, 16);
                        
                        int32_t is_unicode_scalar_value = SPVM_TOKE_is_unicode_scalar_value(unicode);
                        if (is_unicode_scalar_value) {
                          char utf8_chars[4];
                          int32_t byte_length = SPVM_TOKE_convert_unicode_codepoint_to_utf8_character(unicode, (uint8_t*)utf8_chars);
                          for (int32_t byte_index = 0; byte_index < byte_length; byte_index++) {
                            string_literal_tmp[string_literal_length] = utf8_chars[byte_index];
                            string_literal_length++;
                          }
                        }
                        else {
                          SPVM_COMPILER_error(compiler, "The code point of Unicode escape character must be a Unicode scalar value at %s line %d", compiler->cur_file, compiler->cur_line);
                        }
                        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, unicode_chars);
                        assert(compiler->allocator->memory_blocks_count_tmp == memory_blocks_count_tmp);
                      }
                    }
                    else {
                      SPVM_COMPILER_error(compiler, "A Unicode escape character must be closed by \"}\" at %s line %d", compiler->cur_file, compiler->cur_line);
                    }
                  }
                  else {
                    SPVM_COMPILER_error(compiler, "Invalid Unicode escape character at %s line %d", compiler->cur_file, compiler->cur_line);
                  }
                }
                else {
                  switch(*char_ptr) {
                    case '!':
                    case '#':
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
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case ':':
                    case ';':
                    case '<':
                    case '=':
                    case '>':
                    case '?':
                    case '@':
                    case 'A':
                    case 'B':
                    case 'D':
                    case 'G':
                    case 'H':
                    case 'K':
                    case 'N':
                    case 'P':
                    case 'R':
                    case 'S':
                    case 'V':
                    case 'W':
                    case 'X':
                    case 'Z':
                    case '[':
                    case ']':
                    case '^':
                    case '_':
                    case '`':
                    case 'b':
                    case 'd':
                    case 'g':
                    case 'h':
                    case 'k':
                    case 'p':
                    case 's':
                    case 'v':
                    case 'w':
                    case 'z':
                    case '{':
                    case '|':
                    case '}':
                    case '~':
                    {
                      string_literal_tmp[string_literal_length] = '\\';
                      string_literal_length++;
                      string_literal_tmp[string_literal_length] = *char_ptr;
                      string_literal_length++;
                      char_ptr++;
                      break;
                    }
                    default: {
                      SPVM_COMPILER_error(compiler, "Invalid string literal escape character \"\\%c\" at %s line %d", *char_ptr, compiler->cur_file, compiler->cur_line);
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
                
                string_literal_tmp[string_literal_length] = *char_ptr;
                string_literal_length++;
                char_ptr++;
              }
            }
          }
          string_literal_tmp[string_literal_length] = '\0';
        }

        SPVM_CONSTANT_STRING* string_literal_string = SPVM_CONSTANT_STRING_new(compiler, string_literal_tmp, string_literal_length);
        const char* string_literal = string_literal_string->value;

        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, string_literal_tmp);
        assert(compiler->allocator->memory_blocks_count_tmp == memory_blocks_count_tmp);
        
        SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, string_literal, string_literal_length, compiler->cur_file, compiler->cur_line);
        
        yylvalp->opval = op_constant;
        
        // Next is start from $
        if (next_var_expansion_state == SPVM_TOKE_C_VAR_EXPANSION_STATE_FIRST_CONCAT) {
          compiler->var_expansion_state = next_var_expansion_state;
          compiler->bufptr--;
        }
        
        return CONSTANT;
      }
      case '\\': {
        compiler->bufptr++;
        SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CREATE_REF);
        yylvalp->opval = op;
        return CREATE_REF;
      }
      default: {
        if (ch == '$') {
          // A derefernece operator
          if (*(compiler->bufptr + 1) == '$') {
            compiler->bufptr++;
            SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DEREF);
            yylvalp->opval = op;
            return DEREF;
          }
          // A exception variable
          else if (*(compiler->bufptr + 1) == '@') {
            compiler->bufptr += 2;
            SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_EXCEPTION_VAR, compiler->cur_file, compiler->cur_line);
            yylvalp->opval = op_exception_var;
            return EXCEPTION_VAR;
          }
          // A exception variable with {}
          else if (*(compiler->bufptr + 1) == '{' && *(compiler->bufptr + 2) == '@' && *(compiler->bufptr + 3) == '}') {
            compiler->bufptr += 4;
            SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_EXCEPTION_VAR, compiler->cur_file, compiler->cur_line);
            yylvalp->opval = op_exception_var;
            return EXCEPTION_VAR;
          }
          // A local variable name or a class variable name
          else {
            compiler->bufptr++;
            
            // ${var} is allowed
            int8_t have_brace = 0;
            if (*compiler->bufptr == '{') {
              have_brace = 1;
              compiler->bufptr++;
            }
            
            // Save the starting position of the symbol name part of the variable name
            const char* var_name_symbol_name_part_start_ptr = compiler->bufptr;
            
            // Go forward to the end of the variable name
            while (
              isalnum(*compiler->bufptr)
              || (*compiler->bufptr) == '_'
              || (*compiler->bufptr == ':' && *(compiler->bufptr + 1) == ':')
            )
            {
              if (*compiler->bufptr == ':' && *(compiler->bufptr + 1) == ':') {
                compiler->bufptr += 2;
              }
              else {
                compiler->bufptr++;
              }
            }
            
            // Create a variable name that doesn't contain "{" and "}"
            int32_t var_name_symbol_name_part_length = compiler->bufptr - var_name_symbol_name_part_start_ptr;
            int32_t var_name_length = var_name_symbol_name_part_length + 1;
            const char* var_name = NULL;
            {

              int32_t memory_blocks_count_tmp_var_name_tmp = compiler->allocator->memory_blocks_count_tmp;
              char* var_name_tmp = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, var_name_length + 1);
              var_name_tmp[0] = '$';
              memcpy(&var_name_tmp[1], var_name_symbol_name_part_start_ptr, var_name_symbol_name_part_length);
              var_name_tmp[1 + var_name_symbol_name_part_length] = '\0';
              
              SPVM_CONSTANT_STRING* var_name_string = SPVM_CONSTANT_STRING_new(compiler, var_name_tmp, 1 + var_name_symbol_name_part_length);
              var_name = var_name_string->value;
              
              SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, var_name_tmp);
              assert(compiler->allocator->memory_blocks_count_tmp == memory_blocks_count_tmp_var_name_tmp);
            }
            
            // Check the closing brace
            if (have_brace) {
              if (*compiler->bufptr == '}') {
                compiler->bufptr++;
              }
              else {
                SPVM_COMPILER_error(compiler, "Need a closing brace \"}\" at the end of the variable name at %s line %d", compiler->cur_file, compiler->cur_line);
              }
            }
            
            // Check the variable name
            {
              // A variable name can't conatain "__"
              if (strstr(var_name, "__")) {
                SPVM_COMPILER_error(compiler, "The variable name \"%s\" can't contain \"__\" at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
              }

              // A variable name can't begin with \"$::\"
              if (var_name_symbol_name_part_length >= 2 && var_name[1] == ':' && var_name[2] == ':') {
                SPVM_COMPILER_error(compiler, "The variable name \"%s\" can't begin with \"$::\" at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
              }

              // A variable name can't end with \"::\"
              if (var_name_symbol_name_part_length >= 2 && var_name[var_name_length - 1] == ':' && var_name[var_name_length - 2] == ':') {
                SPVM_COMPILER_error(compiler, "The variable name \"%s\" can't end with \"::\" at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
              }
              
              // A variable name \"%s\" can't contain \"::::\"
              if (strstr(var_name, "::::")) {
                SPVM_COMPILER_error(compiler, "The variable name \"%s\" can't contain \"::::\" at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
              }

              // A variable name can't begin with a number
              if (var_name_symbol_name_part_length >= 1 && isdigit(var_name[1])) {
                SPVM_COMPILER_error(compiler, "The symbol name part of the variable name \"%s\" can't begin with a number at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
              }
            }
            
            // Name op
            SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, var_name, compiler->cur_file, compiler->cur_line);
            yylvalp->opval = op_name;

            return VAR_NAME;
          }
        }
        // Numeric literal
        else if (isdigit(ch)) {
          const char* number_literal_begin_ptr = compiler->bufptr;
          
          // The before character is "-"
          int32_t minus = 0;
          if (before_char_is_minus) {
            before_char_is_minus = 0;
            minus = 1;
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
            else if (isdigit(*(compiler->bufptr + 1)) || *(compiler->bufptr + 1) == '_') {
              digit = 8;
            }
            // 0...
            else {
              digit = 10;
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
              SPVM_TOKE_is_hex_number(compiler, *compiler->bufptr) || *compiler->bufptr == '_'
              || *compiler->bufptr == '.' || *compiler->bufptr == 'p' || *compiler->bufptr == 'P' || *compiler->bufptr == '-' || *compiler->bufptr == '+'
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
          int32_t str_len = (compiler->bufptr - number_literal_begin_ptr);
          
          // Ignore under line
          int32_t numeric_literal_memoyr_blocks_count = compiler->allocator->memory_blocks_count_tmp;
          char* numeric_literal = (char*)SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, str_len + 1);
          int32_t pos = 0;
          {
            int32_t i;
            for (i = 0; i < str_len; i++) {
              if (*(number_literal_begin_ptr + i) != '_') {
                *(numeric_literal + pos) = *(number_literal_begin_ptr + i);
                pos++;
              }
            }
            numeric_literal[pos] = '\0';
          }
          // Back suffix such as "f" or "F" when hex floating number
          if (is_hex_floating_number && !isdigit(*(compiler->bufptr - 1))) {
            compiler->bufptr--;
            numeric_literal[pos - 1] = '\0';
          }
          
          // Constant
          SPVM_TYPE* constant_type;
          
          // suffix
          char suffix[2];
          suffix[1] = '\0';
          
          // long suffix
          if (*compiler->bufptr == 'l' || *compiler->bufptr == 'L')  {
            suffix[0] = *compiler->bufptr;
            constant_type = SPVM_TYPE_new_long_type(compiler);
            compiler->bufptr++;
          }
          // float suffix
          else if (*compiler->bufptr == 'f' || *compiler->bufptr == 'F')  {
            suffix[0] = *compiler->bufptr;
            constant_type = SPVM_TYPE_new_float_type(compiler);
            compiler->bufptr++;
          }
          // double suffix
          else if (*compiler->bufptr == 'd' || *compiler->bufptr == 'D')  {
            suffix[0] = *compiler->bufptr;
            constant_type = SPVM_TYPE_new_double_type(compiler);
            compiler->bufptr++;
          }
          // no suffix
          else {
            suffix[0] = '\0';
            
            // floating point
            if (is_floating_number) {
              constant_type = SPVM_TYPE_new_double_type(compiler);
            }
            // integer
            else {
              constant_type = SPVM_TYPE_new_int_type(compiler);
            }
          }
          
          SPVM_VALUE num;
          
          // Parse Interger literal - int
          if (constant_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
            
            errno = 0;
            int32_t out_of_range = 0;
            
            int32_t parse_start_offset;
            if (digit == 16) {
              parse_start_offset = 2;
            }
            else if (digit == 8) {
              parse_start_offset = 1;
            }
            else if (digit == 2) {
              parse_start_offset = 2;
            }
            else if (digit == 10) {
              parse_start_offset = 0;
            }
            else {
              assert(0);
            }
            
            char *end;
            uint64_t num_uint64_nosign = strtoull(numeric_literal + parse_start_offset, &end, digit);
            if (*end != '\0') {
              out_of_range = 1;
            }
            else if (errno == ERANGE) {
              out_of_range = 1;
            }
            else {
              if (digit == 16 || digit == 8 || digit == 2) {
                if (num_uint64_nosign > UINT32_MAX) {
                  out_of_range = 1;
                }
              }
              else {
                if (minus) {
                  if (num_uint64_nosign > ((uint32_t)INT32_MAX + 1)) {
                    out_of_range = 1;
                  }
                }
                else {
                  if (num_uint64_nosign > INT32_MAX) {
                    out_of_range = 1;
                  }
                }
              }
            }
            
            if (out_of_range) {
              SPVM_COMPILER_error(compiler, "The numeric literal \"%s%s\" is out of range of maximum and minimum values of int type at %s line %d", minus ? "-" : "", numeric_literal, compiler->cur_file, compiler->cur_line);
            }
            
            if (digit == 16 || digit == 8 || digit == 2) {
              num.ival = (int32_t)(uint32_t)num_uint64_nosign;
              if (minus) {
                num.ival = -num.ival;
              }
            }
            else {
              num.ival = minus ? (int32_t)-num_uint64_nosign : (int32_t)num_uint64_nosign;
            }
          }
          // Parse Interger literal - long
          else if (constant_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
            errno = 0;
            int32_t invalid = 0;
            
            int32_t parse_start_offset;
            if (digit == 16) {
              parse_start_offset = 2;
            }
            else if (digit == 8) {
              parse_start_offset = 1;
            }
            else if (digit == 2) {
              parse_start_offset = 2;
            }
            else if (digit == 10) {
              parse_start_offset = 0;
            }
            else {
              assert(0);
            }
            
            char *end;
            uint64_t num_uint64_nosign = strtoull(numeric_literal + parse_start_offset, &end, digit);
            if (*end != '\0') {
              invalid = 1;
            }
            else if (errno == ERANGE) {
              invalid = 1;
            }
            else {
              if (digit == 16 || digit == 8 || digit == 2) {
                if (num_uint64_nosign > UINT64_MAX) {
                  invalid = 1;
                }
              }
              else {
                if (minus) {
                  if (num_uint64_nosign > ((uint64_t)INT64_MAX + 1)) {
                    invalid = 1;
                  }
                }
                else {
                  if (num_uint64_nosign > INT64_MAX) {
                    invalid = 1;
                  }
                }
              }
            }
            
            if (invalid) {
              SPVM_COMPILER_error(compiler, "The numeric literal \"%s%s%s\" is out of range of maximum and minimum values of long type at %s line %d", minus ? "-" : "", numeric_literal, suffix, compiler->cur_file, compiler->cur_line);
            }
            
            if (digit == 16 || digit == 8 || digit == 2) {
              num.lval = (int64_t)(uint64_t)num_uint64_nosign;
              if (minus) {
                num.lval = -num.lval;
              }
            }
            else {
              num.lval = minus ? (int64_t)-num_uint64_nosign : (int64_t)num_uint64_nosign;
            }
          }
          // Parse floating point literal - float
          else if (constant_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
            char *end;
            num.fval = strtof(numeric_literal, &end);
            if (*end != '\0') {
              SPVM_COMPILER_error(compiler, "Invalid float literal at %s line %d", compiler->cur_file, compiler->cur_line);
            }
            
            if (minus) {
              num.fval = -num.fval;
            }
          }
          // Parse floating point literal - double
          else if (constant_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
            char *end;
            num.dval = strtod(numeric_literal, &end);
            if (*end != '\0') {
              SPVM_COMPILER_error(compiler, "Invalid double literal at %s line %d", compiler->cur_file, compiler->cur_line);
            }
            if (minus) {
              num.dval = -num.dval;
            }
          }
          else {
            assert(0);
          }
          SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, numeric_literal);
          assert(compiler->allocator->memory_blocks_count_tmp == numeric_literal_memoyr_blocks_count);

          // Constant op
          SPVM_OP* op_constant;
          switch (constant_type->basic_type->id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
              op_constant = SPVM_OP_new_op_constant_int(compiler, num.ival, compiler->cur_file, compiler->cur_line);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
              op_constant = SPVM_OP_new_op_constant_long(compiler, num.lval, compiler->cur_file, compiler->cur_line);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
              op_constant = SPVM_OP_new_op_constant_float(compiler, num.fval, compiler->cur_file, compiler->cur_line);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
              op_constant = SPVM_OP_new_op_constant_double(compiler, num.dval, compiler->cur_file, compiler->cur_line);
              break;
            }
            default: {
              assert(0);
            }
          }

          yylvalp->opval = op_constant;
          
          return CONSTANT;
        }
        // A symbol name
        else if (isalpha(ch) || ch == '_') {
          // Column
          int32_t column = compiler->bufptr - compiler->line_start_ptr;
          
          // The staring position of the symbol name
          const char* symbol_name_start_ptr = compiler->bufptr;
          
          // Go foward by one character
          compiler->bufptr++;
          
          // Go forward to the end of the symbol name
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
          
          // Symbol name
          int32_t symbol_name_length = (compiler->bufptr - symbol_name_start_ptr);
          char* symbol_name = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, symbol_name_length + 1);
          memcpy(symbol_name, symbol_name_start_ptr, symbol_name_length);
          symbol_name[symbol_name_length] = '\0';
          
          // If following token is fat comma, the symbol name is manipulated as a string literal
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
          
          // Check if the symbol is symbol_name
          int32_t keyword_token = 0;
          if (next_is_fat_camma) {
            // None
          }
          else if (expect_method_name) {
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
                if (strcmp(symbol_name, "alias") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ALIAS);
                  keyword_token = ALIAS;
                }
                else if (strcmp(symbol_name, "allow") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ALLOW);
                  keyword_token = ALLOW;
                }
                else if (strcmp(symbol_name, "as") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_AS);
                  keyword_token = AS;
                }
                break;
              }
              case 'b' : {
                if (strcmp(symbol_name, "break") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_BREAK);
                  keyword_token = BREAK;
                }
                else if (strcmp(symbol_name, "byte") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_BYTE);
                  keyword_token = BYTE;
                }
                break;
              }
              case 'c' : {
                if (strcmp(symbol_name, "case") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CASE);
                  keyword_token = CASE;
                }
                else if (strcmp(symbol_name, "cmp") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_CMP);
                  keyword_token = STRING_CMP;
                }
                else if (strcmp(symbol_name, "class") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CLASS);
                  keyword_token = CLASS;
                }
                else if (strcmp(symbol_name, "copy") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_COPY);
                  keyword_token = COPY;
                }
                break;
              }
              case 'd' : {
                if (strcmp(symbol_name, "default") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DEFAULT);
                  keyword_token = DEFAULT;
                }
                else if (strcmp(symbol_name, "die") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DIE);
                  keyword_token = DIE;
                }
                else if (strcmp(symbol_name, "divui") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT);
                  keyword_token = DIVIDE_UNSIGNED_INT;
                }
                else if (strcmp(symbol_name, "divul") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG);
                  keyword_token = DIVIDE_UNSIGNED_LONG;
                }
                else if (strcmp(symbol_name, "double") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DOUBLE);
                  keyword_token = DOUBLE;
                }
                else if (strcmp(symbol_name, "dump") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DUMP);
                  keyword_token = DUMP;
                }
                break;
              }
              case 'e' : {
                if (strcmp(symbol_name, "elsif") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ELSIF);
                  keyword_token = ELSIF;
                }
                else if (strcmp(symbol_name, "else") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ELSE);
                  keyword_token = ELSE;
                }
                else if (strcmp(symbol_name, "enum") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ENUM);
                  keyword_token = ENUM;
                }
                else if (strcmp(symbol_name, "eq") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_EQ);
                  keyword_token = STREQ;
                }
                else if (strcmp(symbol_name, "eval") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_EVAL);
                  keyword_token = EVAL;
                }
                break;
              }
              case 'f' : {
                if (strcmp(symbol_name, "for") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_FOR);
                  keyword_token = FOR;
                }
                else if (strcmp(symbol_name, "float") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_FLOAT);
                  keyword_token = FLOAT;
                }
                else if (strcmp(symbol_name, "false") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_FALSE);
                  keyword_token = FALSE;
                }
                break;
              }
              case 'g' : {
                if (strcmp(symbol_name, "gt") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_GT);
                  keyword_token = STRGT;
                }
                else if (strcmp(symbol_name, "ge") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_GE);
                  keyword_token = STRGE;
                }
                break;
              }
              case 'h' : {
                if (strcmp(symbol_name, "has") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_FIELD);
                  compiler->expect_field_name = 1;
                  keyword_token = HAS;
                }
                else if (strcmp(symbol_name, "has_impl") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_HAS_IMPL);
                  keyword_token = HAS_IMPL;
                }
                break;
              }
              case 'i' : {
                if (strcmp(symbol_name, "if") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_IF);
                  keyword_token = IF;
                }
                else if (strcmp(symbol_name, "isa") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ISA);
                  keyword_token = ISA;
                }
                else if (strcmp(symbol_name, "isweak") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ISWEAK);
                  keyword_token = ISWEAK;
                }
                else if (strcmp(symbol_name, "is_read_only") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_IS_READ_ONLY);
                  keyword_token = IS_READ_ONLY;
                }
                else if (strcmp(symbol_name, "interface") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_INTERFACE);
                  keyword_token = INTERFACE;
                }
                else if (strcmp(symbol_name, "int") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_INT);
                  keyword_token = INT;
                }
                else if (strcmp(symbol_name, "interface_t") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_INTERFACE_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  keyword_token = DESCRIPTOR;
                }
                break;
              }
              case 'l' : {
                if (strcmp(symbol_name, "last") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_LAST);
                  keyword_token = LAST;
                }
                else if (strcmp(symbol_name, "length") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_LENGTH);
                  keyword_token = STRING_LENGTH;
                }
                else if (strcmp(symbol_name, "lt") == 0) {
                  SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_LT);
                  yylvalp->opval = op;
                  
                  keyword_token = STRLT;
                }
                else if (strcmp(symbol_name, "le") == 0) {
                  SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_LE);
                  yylvalp->opval = op;
                  
                  keyword_token = STRLE;
                }
                else if (strcmp(symbol_name, "long") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_LONG);
                  keyword_token = LONG;
                }
                break;
              }
              case 'm' : {
                if (strcmp(symbol_name, "make_read_only") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_MAKE_READ_ONLY);
                  keyword_token = MAKE_READ_ONLY;
                }
                else if (strcmp(symbol_name, "my") == 0) {
                  SPVM_OP* op_var_decl = SPVM_OP_new_op_var_decl(compiler, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_var_decl;
                  keyword_token = MY;
                }
                else if (strcmp(symbol_name, "mulnum_t") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_MULNUM_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  keyword_token = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "method") == 0) {
                  SPVM_OP* op_method = SPVM_TOKE_new_op_with_column(compiler, SPVM_OP_C_ID_METHOD, column);
                  yylvalp->opval = op_method;

                  compiler->expect_method_name = 1;

                  keyword_token = METHOD;
                }
                else if (strcmp(symbol_name, "mutable") == 0) {
                  SPVM_OP* op_mutable = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_MUTABLE);
                  keyword_token = MUTABLE;
                }
                break;
              }
              case 'n' : {
                if (strcmp(symbol_name, "native") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_NATIVE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  keyword_token = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "ne") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING_NE);
                  keyword_token = STRNE;
                }
                else if (strcmp(symbol_name, "next") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NEXT);
                  keyword_token = NEXT;
                }
                else if (strcmp(symbol_name, "new") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NEW);
                  keyword_token = NEW;
                }
                else if (strcmp(symbol_name, "new_string_len") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NEW_STRING_LEN);
                  keyword_token = NEW_STRING_LEN;
                }
                break;
              }
              case 'o' : {
                if (strcmp(symbol_name, "of") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_OF);
                  keyword_token = OF;
                }
                else if (strcmp(symbol_name, "our") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CLASS_VAR);
                  keyword_token = OUR;
                }
                else if (strcmp(symbol_name, "object") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_OBJECT);
                  keyword_token = OBJECT;
                }
                break;
              }
              case 'p' : {
                if (strcmp(symbol_name, "print") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_PRINT);
                  keyword_token = PRINT;
                }
                else if (strcmp(symbol_name, "private") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_PRIVATE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  keyword_token = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "public") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_PUBLIC, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  keyword_token = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "precompile") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_PRECOMPILE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  keyword_token = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "pointer_t") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_POINTER_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  
                  keyword_token = DESCRIPTOR;
                }
                break;
              }
              case 'r' : {
                if (strcmp(symbol_name, "ref") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_REFOP);
                  keyword_token = REFOP;
                }
                else if (strcmp(symbol_name, "refcnt") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_REFCNT);
                  keyword_token = REFCNT;
                }
                else if (strcmp(symbol_name, "remui") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_REMAINDER_UNSIGNED_INT);
                  keyword_token = REMAINDER_UNSIGNED_INT;
                }
                else if (strcmp(symbol_name, "remul") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_REMAINDER_UNSIGNED_LONG);
                  keyword_token = REMAINDER_UNSIGNED_LONG;
                }
                else if (strcmp(symbol_name, "return") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_RETURN);
                  keyword_token = RETURN;
                }
                else if (strcmp(symbol_name, "require") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_REQUIRE);
                  keyword_token = REQUIRE;
                }
                else if (strcmp(symbol_name, "required") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_REQUIRED, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  keyword_token = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "rw") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_RW, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  keyword_token = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "ro") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_RO, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  keyword_token = DESCRIPTOR;
                }
                break;
              }
              case 's' : {
                if (strcmp(symbol_name, "static") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_STATIC, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  keyword_token = DESCRIPTOR;
                }
                else if (strcmp(symbol_name, "switch") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SWITCH);
                  keyword_token = SWITCH;
                }
                else if (strcmp(symbol_name, "string") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_STRING);
                  keyword_token = STRING;
                }
                else if (strcmp(symbol_name, "short") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SHORT);
                  keyword_token = SHORT;
                }
                else if (strcmp(symbol_name, "scalar") == 0) {
                  compiler->bufptr++;
                  SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SCALAR);
                  yylvalp->opval = op;
                  
                  keyword_token = SCALAR;
                }
                break;
              }
              case 't' : {
                if (strcmp(symbol_name, "true") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_TRUE);
                  keyword_token = TRUE;
                }
                break;
              }
              case 'u' : {
                if (strcmp(symbol_name, "undef") == 0) {
                  yylvalp->opval = SPVM_OP_new_op_undef(compiler, compiler->cur_file, compiler->cur_line);
                  keyword_token = UNDEF;
                }
                else if (strcmp(symbol_name, "unless") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_UNLESS);
                  keyword_token = UNLESS;
                }
                else if (strcmp(symbol_name, "unweaken") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_UNLESS);
                  keyword_token = UNWEAKEN;
                }
                else if (strcmp(symbol_name, "use") == 0) {
                  yylvalp->opval = SPVM_OP_new_op_use(compiler, compiler->cur_file, compiler->cur_line);
                  keyword_token = USE;
                }
                break;
              }
              case 'v' : {
                if (strcmp(symbol_name, "void") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_VOID);
                  keyword_token = VOID;
                }
                break;
              }
              case 'w' : {
                if (strcmp(symbol_name, "warn") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_WARN);
                  keyword_token = WARN;
                }
                else if (strcmp(symbol_name, "while") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_WHILE);
                  keyword_token = WHILE;
                }
                else if (strcmp(symbol_name, "weaken") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_WEAKEN);
                  keyword_token = WEAKEN;
                }
                else if (strcmp(symbol_name, "wo") == 0) {
                  SPVM_OP* op_descriptor = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_WO, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_descriptor;
                  keyword_token = DESCRIPTOR;
                }
                break;
              }
              case 'I' : {
                if (strcmp(symbol_name, "INIT") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_INIT);
                  keyword_token = INIT;
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
                  keyword_token = CURRENT_CLASS_NAME;
                }
                else if (strcmp(symbol_name, "__FILE__") == 0) {
                  SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, compiler->cur_rel_file, strlen(compiler->cur_rel_file), compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_constant;
                  keyword_token = CONSTANT;
                }
                else if (strcmp(symbol_name, "__LINE__") == 0) {
                  SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, compiler->cur_line, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_constant;
                  keyword_token = CONSTANT;
                }
                break;
              }
            }
          }
          
          // The symbol name is a keyword
          int32_t token;
          if (keyword_token > 0) {
            token = keyword_token;
          }
          // The symbol name is not a keyword
          else {
            // Check the symbol name
            {
              // A symbol name can't conatain "__"
              if (strstr(symbol_name, "__")) {
                SPVM_COMPILER_error(compiler, "The symbol name \"%s\" can't constain \"__\" at %s line %d", symbol_name, compiler->cur_file, compiler->cur_line);
              }
              
              // A symbol name can't end with "::"
              if (symbol_name_length >= 2 && symbol_name[symbol_name_length - 2] == ':' && symbol_name[symbol_name_length - 1] == ':' ) {
                SPVM_COMPILER_error(compiler, "The symbol name \"%s\" can't end with \"::\" at %s line %d", symbol_name, compiler->cur_file, compiler->cur_line);
              }

              // A symbol name can't contains "::::".
              if (strstr(symbol_name, "::::")) {
                SPVM_COMPILER_error(compiler, "The symbol name \"%s\" can't contains \"::::\" at %s line %d", symbol_name, compiler->cur_file, compiler->cur_line);
              }

              // A symbol name can't begin with "::"
              assert(!(symbol_name[0] == ':' && symbol_name[1] == ':'));

              // A symbol name can't begin with a number "0-9".
              assert(!isdigit(symbol_name[0]));
            }

            // A string literal of the left operand of the fat camma
            if (next_is_fat_camma) {
              // The string literal of the left operand of the fat camma can't contains "::".
              if (symbol_name_length >= 2 && strstr(symbol_name, "::")) {
                SPVM_COMPILER_error(compiler, "The string literal \"%s\" of the left operand of the fat camma can't contains \"::\" at %s line %d", symbol_name, compiler->cur_file, compiler->cur_line);
              }

              SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, symbol_name, symbol_name_length, compiler->cur_file, compiler->cur_line);
              yylvalp->opval = op_constant;
              token = CONSTANT;
            }
            // A symbol name
            else {
              SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, symbol_name, compiler->cur_file, compiler->cur_line);
              yylvalp->opval = op_name;
              token = SYMBOL_NAME;
            }
          }

          // Free symbol name
          SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, symbol_name);
          
          return token;
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
}


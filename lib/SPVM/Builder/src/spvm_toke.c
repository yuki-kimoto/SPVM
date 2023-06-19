// Copyright (c) 2023 Yuki Kimoto
// MIT License

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
#include "spvm_attribute.h"
#include "spvm_type.h"
#include "spvm_use.h"
#include "spvm_basic_type.h"
#include "spvm_var_decl.h"
#include "spvm_string_buffer.h"
#include "spvm_method.h"
#include "spvm_constant_string.h"

// Get token
int SPVM_yylex(SPVM_YYSTYPE* yylvalp, SPVM_COMPILER* compiler) {
  
  // Default source is a empty string
  if (compiler->ch_ptr == NULL) {
    compiler->ch_ptr = "";
  }
  
  // Save buf pointer
  compiler->before_ch_ptr = compiler->ch_ptr;
  
  // Before character is "-". This is used by the numeric literal that has "-".
  int32_t before_char_is_minus = 0;
  
  // Before token is arrow
  int32_t before_token_is_arrow = compiler->before_token_is_arrow;
  compiler->before_token_is_arrow = 0;
  
  // Expect method name
  int32_t expect_method_name = compiler->expect_method_name;
  compiler->expect_method_name = 0;
  
  // Expect field name
  int32_t expect_field_name = compiler->expect_field_name;
  compiler->expect_field_name = 0;
  
  // Variable expansion state
  int32_t var_expansion_state = compiler->var_expansion_state;
  compiler->var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_NOT_STARTED;
  
  int32_t parse_not_started = compiler->parse_not_started;
  compiler->parse_not_started = 0;
  
  while(1) {
    
    // Load class file
    int32_t source_index = compiler->ch_ptr - compiler->cur_source;
    if (!compiler->cur_source || source_index >= compiler->cur_source_length) {
      
      // End of file
      if (!parse_not_started) {
        compiler->parse_not_started = 1;
        SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_END_OF_FILE);
        yylvalp->opval = op;
        return END_OF_FILE;
      }
      
      // Load class file
      int32_t success = SPVM_TOKE_load_module_file(compiler);
      
      if (!success) {
        return success;
      }
      
      if (compiler->cur_source) {
        continue;
      }
      else {
        return 0;
      }
    }
    
    // "aaa $foo bar" is interupted "aaa $foo" . " bar"
    if (compiler->ch_ptr == compiler->next_string_literal_ch_ptr) {
      compiler->next_string_literal_ch_ptr = NULL;
      var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_SECOND_CONCAT;
    }
    
    // Current character
    char ch = -1;
    
    // Variable expansion state
    if (var_expansion_state > 0) {
      switch (var_expansion_state) {
        case SPVM_TOKE_C_VAR_EXPANSION_STATE_NOT_STARTED: {
          ch = *compiler->ch_ptr;
          break;
        }
        case  SPVM_TOKE_C_VAR_EXPANSION_STATE_FIRST_CONCAT: {
          ch = '.';
          break;
        }
        case  SPVM_TOKE_C_VAR_EXPANSION_STATE_VAR: {
          ch = *compiler->ch_ptr;
          break;
        }
        case  SPVM_TOKE_C_VAR_EXPANSION_STATE_SECOND_CONCAT: {
          ch = '.';
          break;
        }
        case  SPVM_TOKE_C_VAR_EXPANSION_STATE_BEGIN_NEXT_STRING_LITERAL: {
          ch = '"';
          break;
        }
        default: {
          assert(0);
        }
      }
    }
    else {
      ch = *compiler->ch_ptr;
    }
    
    switch (ch) {
      // Skip space character
      case ' ':
      case '\t':
      case '\f':
      {
        compiler->ch_ptr++;
        compiler->before_ch_ptr = compiler->ch_ptr;
        continue;
        break;
      }
      case '\r':
      case '\n':
      {
        if (*compiler->ch_ptr == '\r' && *(compiler->ch_ptr + 1) == '\n') {
          compiler->ch_ptr++;
        }
        
        compiler->ch_ptr++;
        compiler->cur_line++;
        compiler->line_begin_ptr = compiler->ch_ptr;
        compiler->before_ch_ptr = compiler->ch_ptr;
        continue;
        break;
      }
      // Cancat
      case '.': {
        // Variable expansion "." before the variable
        if (var_expansion_state == SPVM_TOKE_C_VAR_EXPANSION_STATE_FIRST_CONCAT) {
          compiler->var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_VAR;
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CONCAT);
          return '.';
        }
        // Variable expansion second "." after the variable
        else if (var_expansion_state == SPVM_TOKE_C_VAR_EXPANSION_STATE_SECOND_CONCAT) {
          compiler->var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_BEGIN_NEXT_STRING_LITERAL;
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CONCAT);
          return '.';
        }
        else {
          compiler->ch_ptr++;
          if (*compiler->ch_ptr == '=') {
            compiler->ch_ptr++;
            SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
            op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_CONCAT;
            
            yylvalp->opval = op_special_assign;
            
            return SPECIAL_ASSIGN;
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
        compiler->ch_ptr++;
        
        if (*compiler->ch_ptr == '+') {
          compiler->ch_ptr++;
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING);
          return INC;
        }
        else if (*compiler->ch_ptr == '=') {
          compiler->ch_ptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_ADD;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING);
          return '+';
        }
        break;
      }
      // Subtract
      case '-': {
        compiler->ch_ptr++;
        
        // "-" is the sign of a numeric literal
        if (isdigit(*compiler->ch_ptr)) {
          before_char_is_minus = 1;
          continue;
        }
        else if (*compiler->ch_ptr == '>') {
          compiler->ch_ptr++;
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING);
          compiler->expect_method_name = 1;
          compiler->before_token_is_arrow = 1;
          
          return ARROW;
        }
        else if (*compiler->ch_ptr == '-') {
          compiler->ch_ptr++;
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING);
          return DEC;
        }
        else if (*compiler->ch_ptr == '=') {
          compiler->ch_ptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_SUBTRACT;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        else {
          yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING);;
          return '-';
        }
        break;
      }
      // Multiply
      case '*': {
        compiler->ch_ptr++;
        
        if (*compiler->ch_ptr == '=') {
          compiler->ch_ptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MULTIPLY;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        // * is used in MULTIPLY operator or type reference
        else {
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING);
          yylvalp->opval = op;
          return '*';
        }
      }
      // Divide
      case '/': {
        compiler->ch_ptr++;
        
        if (*compiler->ch_ptr == '=') {
          compiler->ch_ptr++;
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
        compiler->ch_ptr++;
        if (*compiler->ch_ptr == '=') {
          compiler->ch_ptr++;
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
        compiler->ch_ptr++;
        if (*compiler->ch_ptr == '=') {
          compiler->ch_ptr++;
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
        compiler->ch_ptr++;
        // Or
        if (*compiler->ch_ptr == '|') {
          compiler->ch_ptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_LOGICAL_OR);
          yylvalp->opval = op;
          return LOGICAL_OR;
        }
        else if (*compiler->ch_ptr == '=') {
          compiler->ch_ptr++;
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
        compiler->ch_ptr++;
        // &&
        if (*compiler->ch_ptr == '&') {
          compiler->ch_ptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_LOGICAL_AND);
          yylvalp->opval = op;
          return LOGICAL_AND;
        }
        // &=
        else if (*compiler->ch_ptr == '=') {
          compiler->ch_ptr++;
          SPVM_OP* op_special_assign = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SPECIAL_ASSIGN);
          op_special_assign->flag = SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND;
          
          yylvalp->opval = op_special_assign;
          
          return SPECIAL_ASSIGN;
        }
        // &foo - Current class
        else if (isalpha(*compiler->ch_ptr) || *compiler->ch_ptr == '_') {
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
        compiler->ch_ptr++;
        while(1) {
          if (*compiler->ch_ptr == '\r' && *(compiler->ch_ptr + 1) == '\n') {
            compiler->ch_ptr++;
          }
          if (*compiler->ch_ptr == '\n' || *compiler->ch_ptr == '\r' || *compiler->ch_ptr == '\0') {
            break;
          }
          else {
            compiler->ch_ptr++;
          }
        }
        
        continue;
        break;
      }
      case '=': {
        // POD
        if (compiler->ch_ptr == compiler->cur_source || *(compiler->ch_ptr - 1) == '\n') {
          while (1) {
            compiler->ch_ptr++;
            if (*compiler->ch_ptr == '\n') {
              compiler->cur_line++;
            }
            
            if (*compiler->ch_ptr == '\0') {
              break;
            }
            
            if (
              *compiler->ch_ptr == '='
              && strncmp(compiler->ch_ptr + 1, "cut", 3) == 0
              && (*(compiler->ch_ptr + 4) == '\0' || SPVM_TOKE_is_white_space(compiler, *(compiler->ch_ptr + 4)))
            )
            {
              compiler->ch_ptr += 4;
              
              while (1) {
                if (*compiler->ch_ptr == '\n' || *compiler->ch_ptr == '\0') {
                  break;
                }
                compiler->ch_ptr++;
              }
              break;
            }
          }
          continue;
        }
        else {
          compiler->ch_ptr++;
          
          // ==
          if (*compiler->ch_ptr == '=') {
            compiler->ch_ptr++;
            SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NUMERIC_EQ);
            yylvalp->opval = op;
            return NUMEQ;
          }
          // =>
          if (*compiler->ch_ptr == '>') {
            compiler->ch_ptr++;
            SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING);
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
        compiler->ch_ptr++;
        
        if (*compiler->ch_ptr == '<') {
          compiler->ch_ptr++;
          // <<=
          if (*compiler->ch_ptr == '=') {
            compiler->ch_ptr++;
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
        else if (*compiler->ch_ptr == '=') {
          compiler->ch_ptr++;
          
          // <=>
          if (*compiler->ch_ptr == '>') {
            compiler->ch_ptr++;
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
          compiler->ch_ptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NUMERIC_LT);
          yylvalp->opval = op;
          return NUMLT;
        }
        break;
      }
      case '>': {
        compiler->ch_ptr++;
        
        if (*compiler->ch_ptr == '>') {
          compiler->ch_ptr++;
          if (*compiler->ch_ptr == '>') {
            compiler->ch_ptr++;
            // >>>=
            if (*compiler->ch_ptr == '=') {
              compiler->ch_ptr++;
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
            if (*compiler->ch_ptr == '=') {
              compiler->ch_ptr++;
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
        else if (*compiler->ch_ptr == '=') {
          compiler->ch_ptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NUMERIC_GE);
          yylvalp->opval = op;
          return NUMGE;
        }
        // >
        else {
          compiler->ch_ptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_NUMERIC_GT);
          yylvalp->opval = op;
          return NUMGT;
        }
        break;
      }
      case '!': {
        compiler->ch_ptr++;
        
        if (*compiler->ch_ptr == '=') {
          compiler->ch_ptr++;
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
        compiler->ch_ptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_BIT_NOT);
          yylvalp->opval = op;
        return BIT_NOT;
        break;
      }
      // Character literals
      case '\'': {
        compiler->ch_ptr++;
        char ch = 0;
        
        if (*compiler->ch_ptr == '\'') {
          SPVM_COMPILER_error(compiler, "The character literal cannnot be empty.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
          compiler->ch_ptr++;
        }
        else {
          if (*compiler->ch_ptr == '\\') {
            compiler->ch_ptr++;
            if (*compiler->ch_ptr == 'a') {
              ch = 0x07; // BEL
              compiler->ch_ptr++;
            }
            else if (*compiler->ch_ptr == 't') {
              ch = 0x09; // HT
              compiler->ch_ptr++;
            }
            else if (*compiler->ch_ptr == 'n') {
              ch = 0x0a; // 
              compiler->ch_ptr++;
            }
            else if (*compiler->ch_ptr == 'f') {
              ch = 0x0c; // FF
              compiler->ch_ptr++;
            }
            else if (*compiler->ch_ptr == 'r') {
              ch = 0x0d; // LF
              compiler->ch_ptr++;
            }
            else if (*compiler->ch_ptr == '\'') {
              ch = 0x27; // '
              compiler->ch_ptr++;
            }
            else if (*compiler->ch_ptr == '"') {
              ch = 0x22; // "
              compiler->ch_ptr++;
            }
            else if (*compiler->ch_ptr == '\\') {
              ch = 0x5c; /* \ */
              compiler->ch_ptr++;
            }
            // Octal escape character
            else if (SPVM_TOKE_is_octal_number(compiler, *compiler->ch_ptr) || *compiler->ch_ptr == 'o') {
              char* char_ptr = compiler->ch_ptr;
              
              ch = SPVM_TOKE_parse_octal_escape(compiler, &char_ptr);
              
              compiler->ch_ptr = char_ptr;
            }
            // Hex escape character
            else if (*compiler->ch_ptr == 'x') {
              char* char_ptr = compiler->ch_ptr;
              
              ch = SPVM_TOKE_parse_hex_escape(compiler, &char_ptr);
              
              compiler->ch_ptr = char_ptr;
            }
            else {
              SPVM_COMPILER_error(compiler, "\"\\%c\" is the invalid charater literal escape character.\n  at %s line %d", *compiler->ch_ptr, compiler->cur_file, compiler->cur_line);
              compiler->ch_ptr++;
            }
          }
          else {
            ch = *compiler->ch_ptr;
            compiler->ch_ptr++;
          }
            
          if (*compiler->ch_ptr == '\'') {
            compiler->ch_ptr++;
          }
          else {
            SPVM_COMPILER_error(compiler, "The character literal must ends with \"'\".\n  at %s line %d", compiler->cur_file, compiler->cur_line);
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
          compiler->var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_NOT_STARTED;
        }
        else {
          compiler->ch_ptr++;
        }
        
        // Save current position
        const char* cur_token_ptr = compiler->ch_ptr;
        
        int8_t next_var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_NOT_STARTED;
        
        char* string_literal_tmp;
        int32_t memory_blocks_count_tmp = compiler->allocator->memory_blocks_count_tmp;
        int32_t string_literal_length = 0;
        if (*(compiler->ch_ptr) == '"') {
          string_literal_tmp = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, 1);
          string_literal_tmp[0] = '\0';
          compiler->ch_ptr++;
        }
        else {
          int32_t string_literal_finished = 0;
          
          while(1) {
            // End of string literal
            if (*compiler->ch_ptr == '"') {
              string_literal_finished = 1;
            }
            // Variable expansion
            else if (*compiler->ch_ptr == '$') {
              if (*(compiler->ch_ptr + 1) == '"') {
                // Last $ is allowed
              }
              else {
                string_literal_finished = 1;
                next_var_expansion_state = SPVM_TOKE_C_VAR_EXPANSION_STATE_FIRST_CONCAT;
                
                // Proceed through a variable expansion and find the position of the next string literal
                char* next_string_literal_ch_ptr = compiler->ch_ptr + 1;
                
                // Dereference
                int32_t var_is_ref = 0;
                if (*next_string_literal_ch_ptr == '$') {
                  next_string_literal_ch_ptr++;
                  var_is_ref = 1;
                }
                
                // Open brace
                int32_t var_have_brace = 0;
                if (*next_string_literal_ch_ptr == '{') {
                  next_string_literal_ch_ptr++;
                  var_have_brace = 1;
                }
                
                // Exception variable
                if (*next_string_literal_ch_ptr == '@') {
                  next_string_literal_ch_ptr++;
                  if (var_have_brace) {
                    // Close brace
                    if (*next_string_literal_ch_ptr == '}') {
                      next_string_literal_ch_ptr++;
                    }
                  }
                }
                else {
                
                  // Proceed through a variable
                  while (1) {
                    if (isalnum(*next_string_literal_ch_ptr) || *next_string_literal_ch_ptr == '_') {
                      next_string_literal_ch_ptr++;
                    }
                    else if (*next_string_literal_ch_ptr == ':' && *(next_string_literal_ch_ptr + 1) == ':') {
                      next_string_literal_ch_ptr += 2;
                    }
                    else if (*next_string_literal_ch_ptr == '}') {
                      if (var_have_brace) {
                        next_string_literal_ch_ptr++;
                        break;
                      }
                    }
                    else {
                      break;
                    }
                  }
                  
                  // Proceed through getting field or getting array element
                  // Array index must be a constant value.
                  // Can't contain space character between "{" and "}" and between "[" and "]"
                  if (!var_have_brace && !var_is_ref) {
                    int32_t has_arrow = 0;
                    int32_t open_getting_field_brace = 0;
                    int32_t open_bracket = 0;
                    int32_t is_first_allow = 1;
                    while (1) {
                      if (!has_arrow) {
                        if (*next_string_literal_ch_ptr == '-' && *(next_string_literal_ch_ptr + 1) == '>') {
                          has_arrow = 1;
                          next_string_literal_ch_ptr += 2;
                        }
                        else {
                          break;
                        }
                      }
                      
                      if (has_arrow) {
                        has_arrow = 0;
                        if (*next_string_literal_ch_ptr == '{') {
                          open_getting_field_brace = 1;
                          next_string_literal_ch_ptr++;
                        }
                        else if (*next_string_literal_ch_ptr == '[') {
                          open_bracket = 1;
                          next_string_literal_ch_ptr++;
                        }
                        else {
                          SPVM_COMPILER_error(compiler, "The character after \"->\" in a string literal must be \"[\" or \"{\".\n  at %s line %d", compiler->cur_file, compiler->cur_line);
                          return 0;
                        }
                      }
                      
                      while (isalnum(*next_string_literal_ch_ptr) || *next_string_literal_ch_ptr == '_') {
                        next_string_literal_ch_ptr++;
                      }
                      
                      if (open_getting_field_brace) {
                        if (*next_string_literal_ch_ptr == '}') {
                          next_string_literal_ch_ptr++;
                          open_getting_field_brace = 0;
                        }
                        else {
                          SPVM_COMPILER_error(compiler, "The getting field in a string literal must be closed with \"}\".\n  at %s line %d", compiler->cur_file, compiler->cur_line);
                          return 0;
                        }
                      }
                      else if (open_bracket) {
                        if (*next_string_literal_ch_ptr == ']') {
                          next_string_literal_ch_ptr++;
                          open_bracket = 0;
                        }
                        else {
                          SPVM_COMPILER_error(compiler, "The getting array element in a string literal must be closed with \"]\".\n  at %s line %d", compiler->cur_file, compiler->cur_line);
                          return 0;
                        }
                      }
                      else {
                        assert(0);
                      }
                      
                      if (*next_string_literal_ch_ptr == '-' && *(next_string_literal_ch_ptr + 1) == '>') {
                        next_string_literal_ch_ptr += 2;
                      }
                      
                      if (!(*next_string_literal_ch_ptr == '{' || *next_string_literal_ch_ptr == '[')) {
                        break;
                      }
                      
                      has_arrow = 1;
                    }
                  }
                }
                compiler->next_string_literal_ch_ptr = next_string_literal_ch_ptr;
              }
            }
            // End of source file
            else if (*compiler->ch_ptr == '\0') {
              string_literal_finished = 1;
            }
            if (string_literal_finished) {
              break;
            }
            else {
              // Escape is always 2 characters
              if (*compiler->ch_ptr == '\\') {
                compiler->ch_ptr += 2;
              }
              else {
                compiler->ch_ptr++;
              }
            }
          }
          if (*compiler->ch_ptr == '\0') {
            SPVM_COMPILER_error(compiler, "The string literal must be end with '\"'.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
            return 0;
          }
          
          int32_t string_literal_tmp_len = (int32_t)(compiler->ch_ptr - cur_token_ptr) * 4;
          
          compiler->ch_ptr++;
          
          string_literal_tmp = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, string_literal_tmp_len + 1);
          {
            char* char_ptr = (char*)cur_token_ptr;
            while (char_ptr != compiler->ch_ptr - 1) {
              if (*char_ptr == '\\') {
                char_ptr++;
                if (*char_ptr == 'a') {
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
                else if (*char_ptr == '$') {
                  string_literal_tmp[string_literal_length] = 0x24;
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
                // Octal escape character
                else if (SPVM_TOKE_is_octal_number(compiler, *char_ptr) || *char_ptr == 'o') {
                  ch = SPVM_TOKE_parse_octal_escape(compiler, &char_ptr);
                  
                  string_literal_tmp[string_literal_length] = ch;
                  string_literal_length++;
                }
                // A hexadecimal escape character
                else if (*char_ptr == 'x') {
                  ch = SPVM_TOKE_parse_hex_escape(compiler, &char_ptr);
                  
                  string_literal_tmp[string_literal_length] = ch;
                  string_literal_length++;
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
                        SPVM_COMPILER_error(compiler, "One or more than one hexadecimal numbers must be followed by \"\\N{U+\" of the Unicode escape character.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
                      }
                      else if (unicode_chars_length > 8) {
                        SPVM_COMPILER_error(compiler, "Too big Unicode escape character.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
                      }
                      else {
                        int32_t memory_blocks_count_tmp = compiler->allocator->memory_blocks_count_tmp;
                        char* unicode_chars = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, unicode_chars_length + 1);
                        memcpy(unicode_chars, char_start_ptr, unicode_chars_length);
                        char *end;
                        int64_t unicode = (int64_t)strtoll(unicode_chars, &end, 16);
                        
                        int32_t is_valid_utf8_code_point = SPVM_TOKE_is_valid_utf8_code_point(unicode);
                        if (is_valid_utf8_code_point) {
                          char utf8_chars[4];
                          int32_t byte_length = SPVM_TOKE_convert_unicode_codepoint_to_utf8_character(unicode, (uint8_t*)utf8_chars);
                          for (int32_t byte_index = 0; byte_index < byte_length; byte_index++) {
                            string_literal_tmp[string_literal_length] = utf8_chars[byte_index];
                            string_literal_length++;
                          }
                        }
                        else {
                          SPVM_COMPILER_error(compiler, "The code point of Unicode escape character must be a Unicode scalar value.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
                        }
                        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, unicode_chars);
                        assert(compiler->allocator->memory_blocks_count_tmp == memory_blocks_count_tmp);
                      }
                    }
                    else {
                      SPVM_COMPILER_error(compiler, "A Unicode escape character must be closed by \"}\".\n  at %s line %d", compiler->cur_file, compiler->cur_line);
                    }
                  }
                  else {
                    SPVM_COMPILER_error(compiler, "Invalid Unicode escape character.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
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
                      SPVM_COMPILER_error(compiler, "Invalid string literal escape character \"\\%c\".\n  at %s line %d", *char_ptr, compiler->cur_file, compiler->cur_line);
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
                  compiler->line_begin_ptr = compiler->ch_ptr;
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
          compiler->ch_ptr--;
        }
        
        return CONSTANT;
      }
      case '\\': {
        compiler->ch_ptr++;
        SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CREATE_REF);
        yylvalp->opval = op;
        return CREATE_REF;
      }
      case '$': {
        // A derefernece operator
        if (*(compiler->ch_ptr + 1) == '$') {
          compiler->ch_ptr++;
          SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DEREF);
          yylvalp->opval = op;
          return DEREF;
        }
        // A exception variable
        else if (*(compiler->ch_ptr + 1) == '@') {
          compiler->ch_ptr += 2;
          SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_EXCEPTION_VAR, compiler->cur_file, compiler->cur_line);
          yylvalp->opval = op_exception_var;
          return EXCEPTION_VAR;
        }
        // A exception variable with {}
        else if (*(compiler->ch_ptr + 1) == '{' && *(compiler->ch_ptr + 2) == '@' && *(compiler->ch_ptr + 3) == '}') {
          compiler->ch_ptr += 4;
          SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_EXCEPTION_VAR, compiler->cur_file, compiler->cur_line);
          yylvalp->opval = op_exception_var;
          return EXCEPTION_VAR;
        }
        // A local variable name or a class variable name
        else {
          compiler->ch_ptr++;
          
          // ${var} is allowed
          int8_t have_brace = 0;
          if (*compiler->ch_ptr == '{') {
            have_brace = 1;
            compiler->ch_ptr++;
          }
          
          // Save the starting position of the symbol name part of the variable name
          const char* var_name_symbol_name_part_start_ptr = compiler->ch_ptr;
          
          // Go forward to the end of the variable name
          while (
            isalnum(*compiler->ch_ptr)
            || (*compiler->ch_ptr) == '_'
            || (*compiler->ch_ptr == ':' && *(compiler->ch_ptr + 1) == ':')
          )
          {
            if (*compiler->ch_ptr == ':' && *(compiler->ch_ptr + 1) == ':') {
              compiler->ch_ptr += 2;
            }
            else {
              compiler->ch_ptr++;
            }
          }
          
          // Create a variable name that doesn't contain "{" and "}"
          int32_t var_name_symbol_name_part_length = compiler->ch_ptr - var_name_symbol_name_part_start_ptr;
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
            if (*compiler->ch_ptr == '}') {
              compiler->ch_ptr++;
            }
            else {
              SPVM_COMPILER_error(compiler, "The variable name is not closed by \"}\".\n  at %s line %d", compiler->cur_file, compiler->cur_line);
            }
          }
          
          // Check the variable name
          {
            // A variable name cannnot conatain "__"
            if (strstr(var_name, "__")) {
              SPVM_COMPILER_error(compiler, "The variable name \"%s\" cannnot contain \"__\".\n  at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
            }
            
            // A variable name cannnot begin with \"$::\"
            if (var_name_symbol_name_part_length >= 2 && var_name[1] == ':' && var_name[2] == ':') {
              SPVM_COMPILER_error(compiler, "The variable name \"%s\" cannnot begin with \"$::\".\n  at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
            }
            
            // A variable name cannnot end with \"::\"
            if (var_name_symbol_name_part_length >= 2 && var_name[var_name_length - 1] == ':' && var_name[var_name_length - 2] == ':') {
              SPVM_COMPILER_error(compiler, "The variable name \"%s\" cannnot end with \"::\".\n  at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
            }
            
            // A variable name \"%s\" cannnot contain \"::::\"
            if (strstr(var_name, "::::")) {
              SPVM_COMPILER_error(compiler, "The variable name \"%s\" cannnot contain \"::::\".\n  at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
            }
            
            // A variable name cannnot begin with a number
            if (var_name_symbol_name_part_length >= 1 && isdigit(var_name[1])) {
              SPVM_COMPILER_error(compiler, "The symbol name part of the variable name \"%s\" cannnot begin with a number.\n  at %s line %d", var_name, compiler->cur_file, compiler->cur_line);
            }
          }
          
          // Name op
          SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, var_name, compiler->cur_file, compiler->cur_line);
          yylvalp->opval = op_name;
          
          return VAR_NAME;
        }
      }
      case '(' :
      case ')' :
      case '[' :
      case ']' :
      case '{' :
      case '}' :
      case ',' :
      case ':' :
      case ';' :
      case '@' :
      {
        // Return character
        compiler->ch_ptr++;
        yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING);
        
        // Expect field name
        if (before_token_is_arrow && ch == '{') {
          compiler->expect_field_name = 1;
        }
        
        return (int) (uint8_t) ch;
      }
      default: {
        // Numeric literal
        if (isdigit(ch)) {
          const char* number_literal_begin_ptr = compiler->ch_ptr;
          
          // The before character is "-"
          int32_t minus = 0;
          if (before_char_is_minus) {
            before_char_is_minus = 0;
            minus = 1;
          }
          
          int32_t digit = 0;
          if (*(compiler->ch_ptr) == '0') {
            // Hex Literal
            if (*(compiler->ch_ptr + 1) == 'x' || *(compiler->ch_ptr + 1) == 'X') {
              digit = 16;
            }
            // Binary Literal
            else if (*(compiler->ch_ptr + 1) == 'b' || *(compiler->ch_ptr + 1) == 'B') {
              digit = 2;
            }
            // Octal Literal
            else if (isdigit(*(compiler->ch_ptr + 1)) || *(compiler->ch_ptr + 1) == '_') {
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
          
          compiler->ch_ptr++;
          // Scan Hex number
          if (digit == 16) {
            compiler->ch_ptr += 2;
            while(
              SPVM_TOKE_is_hex_number(compiler, *compiler->ch_ptr) || *compiler->ch_ptr == '_'
              || *compiler->ch_ptr == '.' || *compiler->ch_ptr == 'p' || *compiler->ch_ptr == 'P' || *compiler->ch_ptr == '-' || *compiler->ch_ptr == '+'
            )
            {
              // Floating point literal
              if (*compiler->ch_ptr == '.' || *compiler->ch_ptr == 'p' || *compiler->ch_ptr == 'P') {
                is_floating_number = 1;
              }
              if (*compiler->ch_ptr == 'p' || *compiler->ch_ptr == 'P') {
                is_hex_floating_number = 1;
              }
              compiler->ch_ptr++;
            }
          }
          // Scan octal or binary number
          else if (digit == 8 || digit == 2) {
            compiler->ch_ptr += 1;
            while(
              isdigit(*compiler->ch_ptr)
              || *compiler->ch_ptr == '_'
            )
            {
              compiler->ch_ptr++;
            }
          }
          // Scan Decimal number
          else {
            while(
              isdigit(*compiler->ch_ptr)
              || *compiler->ch_ptr == '.' || *compiler->ch_ptr == '-' || *compiler->ch_ptr == '+' || *compiler->ch_ptr == 'e' || *compiler->ch_ptr == 'E'
              || *compiler->ch_ptr == '_'
            )
            {
              // Floating point literal
              if (*compiler->ch_ptr == '.' || *compiler->ch_ptr == 'e' || *compiler->ch_ptr == 'E') {
                is_floating_number = 1;
              }
              compiler->ch_ptr++;
            }
          }
          
          // First is space for + or -
          int32_t str_len = (compiler->ch_ptr - number_literal_begin_ptr);
          
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
          if (is_hex_floating_number && !isdigit(*(compiler->ch_ptr - 1))) {
            compiler->ch_ptr--;
            numeric_literal[pos - 1] = '\0';
          }
          
          // Constant
          SPVM_TYPE* constant_type;
          
          // suffix
          char suffix[2];
          suffix[1] = '\0';
          
          // long suffix
          if (*compiler->ch_ptr == 'l' || *compiler->ch_ptr == 'L')  {
            suffix[0] = *compiler->ch_ptr;
            constant_type = SPVM_TYPE_new_long_type(compiler);
            compiler->ch_ptr++;
          }
          // float suffix
          else if (*compiler->ch_ptr == 'f' || *compiler->ch_ptr == 'F')  {
            suffix[0] = *compiler->ch_ptr;
            constant_type = SPVM_TYPE_new_float_type(compiler);
            compiler->ch_ptr++;
          }
          // double suffix
          else if (*compiler->ch_ptr == 'd' || *compiler->ch_ptr == 'D')  {
            suffix[0] = *compiler->ch_ptr;
            constant_type = SPVM_TYPE_new_double_type(compiler);
            compiler->ch_ptr++;
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
              SPVM_COMPILER_error(compiler, "The numeric literal \"%s%s\" is out of range of maximum and minimum values of int type.\n  at %s line %d", minus ? "-" : "", numeric_literal, compiler->cur_file, compiler->cur_line);
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
              SPVM_COMPILER_error(compiler, "The numeric literal \"%s%s%s\" is out of range of maximum and minimum values of long type.\n  at %s line %d", minus ? "-" : "", numeric_literal, suffix, compiler->cur_file, compiler->cur_line);
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
              SPVM_COMPILER_error(compiler, "Invalid float literal.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
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
              SPVM_COMPILER_error(compiler, "Invalid double literal.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
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
          int32_t column = compiler->ch_ptr - compiler->line_begin_ptr;
          
          // The staring position of the symbol name
          const char* symbol_name_start_ptr = compiler->ch_ptr;
          
          // Go foward by one character
          compiler->ch_ptr++;
          
          // Go forward to the end of the symbol name
          while(isalnum(*compiler->ch_ptr)
            || *compiler->ch_ptr == '_'
            || (*compiler->ch_ptr == ':' && *(compiler->ch_ptr + 1) == ':'))
          {
            if (*compiler->ch_ptr == ':' && *(compiler->ch_ptr + 1) == ':') {
              compiler->ch_ptr += 2;
            }
            else {
              compiler->ch_ptr++;
            }
          }
          
          // Symbol name
          int32_t symbol_name_length = (compiler->ch_ptr - symbol_name_start_ptr);
          char* symbol_name = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, symbol_name_length + 1);
          memcpy(symbol_name, symbol_name_start_ptr, symbol_name_length);
          symbol_name[symbol_name_length] = '\0';
          
          // If following token is fat comma, the symbol name is manipulated as a string literal
          int32_t next_is_fat_camma = 0;
          char* fat_camma_check_ptr = compiler->ch_ptr;
          while (SPVM_TOKE_is_white_space(compiler, *fat_camma_check_ptr)) {
            fat_camma_check_ptr++;
          }
          if (*fat_camma_check_ptr == '=' && *(fat_camma_check_ptr + 1) == '>') {
            next_is_fat_camma = 1;
          }
          else {
            next_is_fat_camma = 0;
          }
          
          int32_t end_of_file = 0;
          
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
                if (strcmp(symbol_name, "basic_type_id") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_BASIC_TYPE_ID);
                  keyword_token = BASIC_TYPE_ID;
                }
                else if (strcmp(symbol_name, "break") == 0) {
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
                if (strcmp(symbol_name, "can") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_CAN);
                  keyword_token = CAN;
                }
                else if (strcmp(symbol_name, "case") == 0) {
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
                else if (strcmp(symbol_name, "compile_type_name") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_COMPILE_TYPE_NAME);
                  keyword_token = COMPILE_TYPE_NAME;
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
                else if (strcmp(symbol_name, "eval_error_id") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_EVAL_ERROR_ID);
                  keyword_token = EVAL_ERROR_ID;
                }
                else if (strcmp(symbol_name, "extends") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_EXTENDS);
                  keyword_token = EXTENDS;
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
                break;
              }
              case 'i' : {
                if (strcmp(symbol_name, "if") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_IF);
                  keyword_token = IF;
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
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_INTERFACE_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  keyword_token = ATTRIBUTE;
                }
                else if (strcmp(symbol_name, "isa") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ISA);
                  keyword_token = ISA;
                }
                else if (strcmp(symbol_name, "isa_error") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ISA_ERROR);
                  keyword_token = ISA_ERROR;
                }
                else if (strcmp(symbol_name, "isweak") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ISWEAK);
                  keyword_token = ISWEAK;
                }
                else if (strcmp(symbol_name, "is_compile_type") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_IS_COMPILE_TYPE);
                  keyword_token = IS_COMPILE_TYPE;
                }
                else if (strcmp(symbol_name, "is_type") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_IS_TYPE);
                  keyword_token = IS_TYPE;
                }
                else if (strcmp(symbol_name, "is_error") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_IS_ERROR);
                  keyword_token = IS_ERROR;
                }
                else if (strcmp(symbol_name, "is_read_only") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_IS_READ_ONLY);
                  keyword_token = IS_READ_ONLY;
                }
                else if (strcmp(symbol_name, "items") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_ITEMS);
                  keyword_token = ITEMS;
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
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_MULNUM_T, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  keyword_token = ATTRIBUTE;
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
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_NATIVE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  
                  keyword_token = ATTRIBUTE;
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
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_PRIVATE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  
                  keyword_token = ATTRIBUTE;
                }
                else if (strcmp(symbol_name, "protected") == 0) {
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_PROTECTED, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  
                  keyword_token = ATTRIBUTE;
                }
                else if (strcmp(symbol_name, "public") == 0) {
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_PUBLIC, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  
                  keyword_token = ATTRIBUTE;
                }
                else if (strcmp(symbol_name, "precompile") == 0) {
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_PRECOMPILE, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  
                  keyword_token = ATTRIBUTE;
                }
                else if (strcmp(symbol_name, "pointer") == 0) {
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_POINTER, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  
                  keyword_token = ATTRIBUTE;
                }
                break;
              }
              case 'r' : {
                if (strcmp(symbol_name, "remui") == 0) {
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
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_REQUIRED, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  keyword_token = ATTRIBUTE;
                }
                else if (strcmp(symbol_name, "rw") == 0) {
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_RW, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  keyword_token = ATTRIBUTE;
                }
                else if (strcmp(symbol_name, "ro") == 0) {
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_RO, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  keyword_token = ATTRIBUTE;
                }
                break;
              }
              case 's' : {
                if (strcmp(symbol_name, "say") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_SAY);
                  keyword_token = SAY;
                }
                else if (strcmp(symbol_name, "static") == 0) {
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_STATIC, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  keyword_token = ATTRIBUTE;
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
                  compiler->ch_ptr++;
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
                else if (strcmp(symbol_name, "type_name") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_TYPE_NAME);
                  keyword_token = TYPE_NAME;
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
                if (strcmp(symbol_name, "version") == 0) {
                  yylvalp->opval = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_VERSION_DECL);
                  keyword_token = VERSION_DECL;
                }
                else if (strcmp(symbol_name, "void") == 0) {
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
                  SPVM_OP* op_attribute = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_WO, compiler->cur_file, compiler->cur_line);
                  yylvalp->opval = op_attribute;
                  keyword_token = ATTRIBUTE;
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
                  compiler->ch_ptr = compiler->cur_source + compiler->cur_source_length;
                  compiler->before_ch_ptr = compiler->ch_ptr;
                  compiler->parse_not_started = 1;
                  SPVM_OP* op = SPVM_TOKE_new_op(compiler, SPVM_OP_C_ID_END_OF_FILE);
                  yylvalp->opval = op;
                  keyword_token = END_OF_FILE;
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
              // A symbol name cannnot conatain "__"
              if (strstr(symbol_name, "__")) {
                SPVM_COMPILER_error(compiler, "The symbol name \"%s\" cannnot constain \"__\".\n  at %s line %d", symbol_name, compiler->cur_file, compiler->cur_line);
              }
              
              // A symbol name cannnot end with "::"
              if (symbol_name_length >= 2 && symbol_name[symbol_name_length - 2] == ':' && symbol_name[symbol_name_length - 1] == ':' ) {
                SPVM_COMPILER_error(compiler, "The symbol name \"%s\" cannnot end with \"::\".\n  at %s line %d", symbol_name, compiler->cur_file, compiler->cur_line);
              }
              
              // A symbol name cannnot contains "::::".
              if (strstr(symbol_name, "::::")) {
                SPVM_COMPILER_error(compiler, "The symbol name \"%s\" cannnot contains \"::::\".\n  at %s line %d", symbol_name, compiler->cur_file, compiler->cur_line);
              }
              
              // A symbol name cannnot begin with "::"
              assert(!(symbol_name[0] == ':' && symbol_name[1] == ':'));
              
              // A symbol name cannnot begin with a number "0-9".
              assert(!isdigit(symbol_name[0]));
            }
            
            // A string literal of the left operand of the fat camma
            if (next_is_fat_camma) {
              // The string literal of the left operand of the fat camma cannnot contains "::".
              if (symbol_name_length >= 2 && strstr(symbol_name, "::")) {
                SPVM_COMPILER_error(compiler, "The string literal \"%s\" of the left operand of the fat camma cannnot contains \"::\".\n  at %s line %d", symbol_name, compiler->cur_file, compiler->cur_line);
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
        else {
          SPVM_COMPILER_error(compiler, "The character %d in a 8bit signed integer is not expected.\n  at %s line %d", ch, compiler->cur_file, compiler->cur_line);
          return (int) (uint8_t) ch;
        }
      }
    }
  }
}

int32_t SPVM_TOKE_load_module_file(SPVM_COMPILER* compiler) {

  // Start parsing a source code
  compiler->cur_file = NULL;
  compiler->cur_source = NULL;
  compiler->cur_tmp_vars_length = 0;
  compiler->ch_ptr = NULL;
  compiler->before_ch_ptr = NULL;
  compiler->line_begin_ptr = NULL;
  
  // If there are more class, load it
  SPVM_LIST* op_use_stack = compiler->op_use_stack;
  
  while (1) {
    if (op_use_stack->length == 0) {
      return 0;
    }
    else if (op_use_stack->length > 0) {
      SPVM_OP* op_use = SPVM_LIST_shift(op_use_stack);
      
      const char* basic_type_name = op_use->uv.use->op_type->uv.type->unresolved_basic_type_name;
      int32_t basic_type_name_length = strlen(basic_type_name);
      
      // Check the basic type name
      {
        // A basic type name must begin with an upper case character
        if (islower(basic_type_name[0])) {
          SPVM_COMPILER_error(compiler, "The basic type name \"%s\" must begin with an upper case character.\n  at %s line %d", basic_type_name, op_use->file, op_use->line);
          return 0;
        }
        
        // Part names of the basic type name begin with lower case
        int32_t basic_type_part_name_is_invalid = 0;
        int32_t basic_type_name_length = strlen(basic_type_name);
        for (int32_t i = 0; i < basic_type_name_length; i++) {
          if (i > 1) {
            if (basic_type_name[i - 2] == ':' && basic_type_name[i - 1] == ':') {
              if (islower(basic_type_name[i])) {
                SPVM_COMPILER_error(compiler, "The part names of the \"%s\" class must begin with an upper case character.\n  at %s line %d", basic_type_name, op_use->file, op_use->line);
                return 0;
              }
            }
          }
        }
        
        // A basic type name cannnot conatain "__"
        if (strstr(basic_type_name, "__")) {
          SPVM_COMPILER_error(compiler, "The basic type name \"%s\" cannnot constain \"__\".\n  at %s line %d", basic_type_name, op_use->file, op_use->line);
          return 0;
        }
        
        // A basic type name cannnot end with "::"
        if (basic_type_name_length >= 2 && basic_type_name[basic_type_name_length - 2] == ':' && basic_type_name[basic_type_name_length - 1] == ':' ) {
          SPVM_COMPILER_error(compiler, "The basic type name \"%s\" cannnot end with \"::\".\n  at %s line %d", basic_type_name, op_use->file, op_use->line);
          return 0;
        }
        
        // A basic type name cannnot contains "::::".
        if (strstr(basic_type_name, "::::")) {
          SPVM_COMPILER_error(compiler, "The basic type name \"%s\" cannnot contains \"::::\".\n  at %s line %d", basic_type_name, op_use->file, op_use->line);
          return 0;
        }
        
        // A basic type name cannnot begin with \"$::\"
        if (basic_type_name_length >= 2 && basic_type_name[0] == ':' && basic_type_name[1] == ':') {
          SPVM_COMPILER_error(compiler, "The basic type name \"%s\" cannnot begin with \"::\".\n  at %s line %d", basic_type_name, op_use->file, op_use->line);
          return 0;
        }
        
        // A basic type name cannnot begin with a number
        if (basic_type_name_length >= 1 && isdigit(basic_type_name[0])) {
          SPVM_COMPILER_error(compiler, "The basic type name \"%s\" cannnot begin with a number.\n  at %s line %d", basic_type_name, op_use->file, op_use->line);
          return 0;
        }
      }
      
      SPVM_BASIC_TYPE* found_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, basic_type_name, strlen(basic_type_name));
      
      if (found_basic_type) {
        continue;
      }
      else {
        // Create moudle relative file name from basic type name by changing :: to / and add ".spvm"
        int32_t cur_rel_file_length = (int32_t)(strlen(basic_type_name) + 6);
        char* cur_rel_file = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, cur_rel_file_length + 1);
        const char* ch_ptr_orig = basic_type_name;
        char* ch_ptr_to = cur_rel_file;
        while (*ch_ptr_orig) {
          if (*ch_ptr_orig == ':' && *(ch_ptr_orig + 1) == ':') {
            *ch_ptr_to = '/';
            ch_ptr_orig += 2;
            ch_ptr_to++;
          }
          else {
            *ch_ptr_to = *ch_ptr_orig;
            ch_ptr_orig++;
            ch_ptr_to++;
          }
        }
        strncpy(ch_ptr_to, ".spvm", 5);
        ch_ptr_to += 5;
        *ch_ptr_to = '\0';
        
        char* cur_file = NULL;
        
        SPVM_STRING_BUFFER* found_source_buffer = SPVM_HASH_get(compiler->source_symtable, basic_type_name, strlen(basic_type_name));
        
        const char* include_dir = NULL;
        if (!found_source_buffer) {
          
          // Search class file
          FILE* fh = NULL;
          int32_t include_dirs_length = SPVM_COMPILER_get_include_dirs_length(compiler);
          for (int32_t i = 0; i < include_dirs_length; i++) {
            include_dir = SPVM_COMPILER_get_include_dir(compiler, i);
            
            // File name
            int32_t file_name_length = (int32_t)(strlen(include_dir) + 1 + strlen(cur_rel_file));
            cur_file = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, file_name_length + 1);
            sprintf(cur_file, "%s/%s", include_dir, cur_rel_file);
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
          
          // Class not found
          if (!fh) {
            if (!op_use->uv.use->is_require) {
              int32_t classr_dirs_str_length = 0;
              for (int32_t i = 0; i < include_dirs_length; i++) {
                const char* include_dir = SPVM_COMPILER_get_include_dir(compiler, i);
                classr_dirs_str_length += 1 + strlen(include_dir);
              }
              char* classr_dirs_str = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, classr_dirs_str_length + 1);
              int32_t classr_dirs_str_offset = 0;
              for (int32_t i = 0; i < include_dirs_length; i++) {
                const char* include_dir = SPVM_COMPILER_get_include_dir(compiler, i);
                sprintf(classr_dirs_str + classr_dirs_str_offset, "%s", include_dir);
                classr_dirs_str_offset += strlen(include_dir);
                if (i != include_dirs_length - 1) {
                  classr_dirs_str[classr_dirs_str_offset] = ' ';
                  classr_dirs_str_offset++;
                }
              }
              
              SPVM_COMPILER_error(compiler, "Failed to load the \"%s\" class. The class file \"%s\" is not found in (%s).\n  at %s line %d", basic_type_name, cur_rel_file, classr_dirs_str, op_use->file, op_use->line);
              
              return 0;
            }
          }
          // Class found
          else {
            // Read file content
            fseek(fh, 0, SEEK_END);
            int32_t source_length = (int32_t)ftell(fh);
            if (source_length < 0) {
              SPVM_COMPILER_error(compiler, "[System Error]Failed to tell the class file \"%s\".\n  at %s line %d", cur_file, op_use->file, op_use->line);
              return 0;
            }
            fseek(fh, 0, SEEK_SET);
            char* source = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, source_length + 1);
            int32_t read_error = 0;
            if ((int32_t)fread(source, 1, source_length, fh) < source_length) {
              SPVM_COMPILER_error(compiler, "[System Error]Failed to read the class file \"%s\".\n  at %s line %d", cur_file, op_use->file, op_use->line);
              SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, source);
              read_error = 1;
            }
            
            if (!read_error) {
              fclose(fh);
              source[source_length] = '\0';
              SPVM_COMPILER_add_source(compiler, basic_type_name, source, source_length);
            }
            
            SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, source);
          }
        }
        
        found_source_buffer = SPVM_HASH_get(compiler->source_symtable, basic_type_name, strlen(basic_type_name));
        
        if (found_source_buffer) {
          
          // Copy original source to current source because original source is used at other places(for example, SPVM::Builder::Exe)
          compiler->cur_source = (char*)found_source_buffer->value;
          compiler->cur_source_length = found_source_buffer->length;
          compiler->cur_include_dir = include_dir;
          compiler->cur_rel_file = cur_rel_file;
          compiler->cur_rel_file_basic_type_name = basic_type_name;
          
          // If we get current class file path, set it, otherwise set class relative file path
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
          compiler->ch_ptr = compiler->cur_source;
          compiler->before_ch_ptr = compiler->cur_source;
          compiler->line_begin_ptr = compiler->cur_source;
          compiler->cur_line = 1;
        }
        else {
          // If class not found and the class is used in require syntax, compilation errors don't occur.
          if (op_use->uv.use->is_require) {
            SPVM_HASH_set(compiler->if_require_not_found_basic_type_name_symtable, basic_type_name, strlen(basic_type_name), (void*)basic_type_name);
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
  
  return 1;
}

SPVM_OP* SPVM_TOKE_new_op(SPVM_COMPILER* compiler, int32_t type) {
  
  SPVM_OP* op = SPVM_OP_new_op(compiler, type, compiler->cur_file, compiler->cur_line);
  
  return op;
}

SPVM_OP* SPVM_TOKE_new_op_with_column(SPVM_COMPILER* compiler, int32_t type, int32_t column) {
  
  SPVM_OP* op = SPVM_OP_new_op(compiler, type, compiler->cur_file, compiler->cur_line);
  
  // column is only used to decide anon method uniquness
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

int32_t SPVM_TOKE_is_octal_number(SPVM_COMPILER* compiler, char ch) {
  (void)compiler;
  // SP, CR, LF, HT, FF
  if (ch >= '0' && ch <= '7') {
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

char SPVM_TOKE_parse_octal_escape(SPVM_COMPILER* compiler, char** char_ptr_ptr) {
  char ch = -1;
  char* char_ptr = *char_ptr_ptr;
  
  int32_t is_o_escape_character = 0;
  int32_t has_brace = 0;
  if (*char_ptr == 'o') {
    is_o_escape_character = 1;
    char_ptr++;
    if (*char_ptr == '{') {
      has_brace = 1;
      char_ptr++;
      if (!SPVM_TOKE_is_octal_number(compiler, *char_ptr)) {
        SPVM_COMPILER_error(compiler, "At least one octal number must be followed by \"\\o{\" of the octal escape character.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
        return ch;
      }
    }
    else {
      SPVM_COMPILER_error(compiler, "\"\\o\" of the octal escape character must have its brace.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
      return ch;
    }
  }
  
  char octal_escape_char[4] = {0};
  int32_t octal_escape_char_index = 0;
  while (SPVM_TOKE_is_octal_number(compiler, *char_ptr)) {
    if (octal_escape_char_index >= 3) {
      break;
    }
    octal_escape_char[octal_escape_char_index] = *char_ptr;
    char_ptr++;
    octal_escape_char_index++;
  }
  
  if (strlen(octal_escape_char) > 0) {
    char* end;
    int32_t number = strtol(octal_escape_char, &end, 8);
    if (number > 255) {
      SPVM_COMPILER_error(compiler, "The maxmum number of the octal escape charcater is 377.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
      return ch;
    }
    ch = (char)number;
  }
  
  if (has_brace) {
    if (*char_ptr == '}') {
      char_ptr++;
    }
    else {
      SPVM_COMPILER_error(compiler, "The octal escape character is not closed by \"}\".\n  at %s line %d", compiler->cur_file, compiler->cur_line);
    }
  }
  
  *char_ptr_ptr = char_ptr;
  
  return ch;
}

char SPVM_TOKE_parse_hex_escape(SPVM_COMPILER* compiler, char** char_ptr_ptr) {
  char ch;
  char* char_ptr = *char_ptr_ptr;

  char_ptr++;
  
  // {
  int32_t has_brace = 0;
  if (*char_ptr == '{') {
    has_brace = 1;
    char_ptr++;
  }
  
  char hex_escape_char[9] = {0};
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
  }
  else {
    SPVM_COMPILER_error(compiler, "One or tow hexadecimal numbers must be followed by \"\\x\" of the hexadecimal escape character.\n  at %s line %d", compiler->cur_file, compiler->cur_line);
  }
  
  if (has_brace) {
    if (*char_ptr == '}') {
      char_ptr++;
    }
    else {
      SPVM_COMPILER_error(compiler, "The hexadecimal escape character is not closed by \"}\".\n  at %s line %d", compiler->cur_file, compiler->cur_line);
    }
  }
  
  *char_ptr_ptr = char_ptr;
  
  return ch;
}

int32_t SPVM_TOKE_is_valid_utf8_code_point(int32_t code_point) {
  return SPVM_TOKE_is_unicode_scalar_value(code_point);
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

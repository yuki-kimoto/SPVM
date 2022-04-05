#ifndef SPVM_CHECK_AST_INFO_H
#define SPVM_CHECK_AST_INFO_H

#include "spvm_typedecl.h"

struct spvm_check_ast_info {
  // Class
  SPVM_CLASS* class;
  
  // Method
  SPVM_METHOD* method;
  
  // My stack
  SPVM_LIST* my_stack;
  
  // Block var_decl base stack
  SPVM_LIST* block_var_decl_base_stack;
  
  // Switch stack
  SPVM_LIST* op_switch_stack;

  // Eval block stack length
  int32_t eval_block_stack_length;
  
  // Loop block stack length
  int32_t loop_block_stack_length;
};

SPVM_CHECK_AST_INFO* SPVM_CHECK_AST_INFO_new(SPVM_COMPILER* compiler);

#endif

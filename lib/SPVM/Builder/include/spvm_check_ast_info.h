#ifndef SPVM_CHECK_AST_INFO_H
#define SPVM_CHECK_AST_INFO_H

#include "spvm_typedef.h"

struct SPVM_check_ast_info {
  // Package
  SPVM_PACKAGE* package;
  
  // Subroutine
  SPVM_SUB* sub;
  
  // My stack
  SPVM_LIST* my_stack;
  
  // Block my base stack
  SPVM_LIST* block_my_base_stack;
  
  // Switch stack
  SPVM_LIST* op_switch_stack;

  // Eval block stack length
  int32_t eval_block_stack_length;
  
  // Loop block stack length
  int32_t loop_block_stack_length;
};

SPVM_CHECK_AST_INFO* SPVM_CHECK_AST_INFO_new(SPVM_COMPILER* compiler);

#endif

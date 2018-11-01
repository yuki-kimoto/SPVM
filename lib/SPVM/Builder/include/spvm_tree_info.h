#ifndef SPVM_TREE_INFO_H
#define SPVM_TREE_INFO_H

#include "spvm_base.h"

struct SPVM_tree_info {
  // Eval block stack length
  int32_t eval_block_stack_length;
  
  // Loop block stack length
  int32_t loop_block_stack_length;
  
  // My stack
  SPVM_LIST* my_stack;
  
  // Block my base stack
  SPVM_LIST* block_my_base_stack;
  
  // Switch stack
  SPVM_LIST* op_switch_stack;
};

SPVM_TREE_INFO* SPVM_TREE_INFO_new(SPVM_COMPILER* compiler);

#endif

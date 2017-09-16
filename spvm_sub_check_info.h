#ifndef SPVM_SUB_CHECK_INFO_H
#define SPVM_SUB_CHECK_INFO_H

#include "spvm_base.h"

// Field information
struct SPVM_sub_check_info {
  // my var informations
  SPVM_DYNAMIC_ARRAY* op_my_vars;

  // my variable stack
  SPVM_DYNAMIC_ARRAY* op_my_var_stack;

  // block my variable base position stack
  SPVM_DYNAMIC_ARRAY* block_my_var_base_stack;
  
  int32_t block_my_var_base;

  // try block my variable base position stack
  SPVM_DYNAMIC_ARRAY* try_block_my_var_base_stack;

  // loop block my variable base position stack
  SPVM_DYNAMIC_ARRAY* loop_block_my_var_base_stack;

  // Switch information stack
  SPVM_DYNAMIC_ARRAY* op_switch_stack;

  // op count
  int32_t op_count;

  int32_t my_var_length;

  int32_t my_var_tmp_index;
};

SPVM_SUB_CHECK_INFO* SPVM_SUB_CHECK_INFO_new(SPVM_COMPILER* compiler);

#endif

#ifndef SPVM_SUB_CHECK_INFO_H
#define SPVM_SUB_CHECK_INFO_H

#include "spvm_base.h"

// Field information
struct SPVM_sub_check_info {
  // my var informations
  SPVM_DYNAMIC_ARRAY* op_mys;

  // my variable stack
  SPVM_DYNAMIC_ARRAY* op_my_stack;
  
  // block my variable base position stack
  SPVM_DYNAMIC_ARRAY* block_my_base_stack;
};

SPVM_SUB_CHECK_INFO* SPVM_SUB_CHECK_INFO_new(SPVM_COMPILER* compiler);

#endif

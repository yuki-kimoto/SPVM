#include <stdlib.h>

#include "spvm_sub.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"
#include "spvm_my.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_type.h"

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler) {
  SPVM_SUB* sub = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_SUB));
  
  sub->op_args = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->op_mys = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->object_arg_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);

  sub->op_package_var_accesses = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->op_field_accesses = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->op_types = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->op_call_subs = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->op_constants = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->op_switch_infos = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  
  return sub;
}

int32_t SPVM_SUB_get_var_alloc_length(SPVM_COMPILER* compiler, SPVM_SUB* sub) {
  // Calcurate variable alloc length
  int32_t var_alloc_length = 0;
  {
    int32_t my_index;
    for (my_index = 0; my_index < sub->op_mys->length; my_index++) {
      SPVM_OP* op_my = SPVM_LIST_fetch(sub->op_mys, my_index);
      SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_my);
      int32_t width = SPVM_TYPE_get_width(compiler, type);
      var_alloc_length += width;
    }
  }
  return var_alloc_length;
}


int32_t SPVM_SUB_get_arg_alloc_length(SPVM_COMPILER* compiler, SPVM_SUB* sub) {
  // Calcurate variable alloc length
  int32_t arg_alloc_length = 0;
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < sub->op_args->length; arg_index++) {
      SPVM_OP* op_arg = SPVM_LIST_fetch(sub->op_args, arg_index);
      SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_arg);
      int32_t width = SPVM_TYPE_get_width(compiler, type);
      arg_alloc_length += width;
    }
  }
  return arg_alloc_length;
}

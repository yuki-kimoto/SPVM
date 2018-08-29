#include <stdlib.h>

#include "spvm_sub.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"
#include "spvm_my.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_type.h"
#include "spvm_basic_type.h"

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler) {
  SPVM_SUB* sub = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_SUB));
  
  sub->args = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->mys = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->object_arg_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);

  sub->info_package_var_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->info_sub_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->info_field_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);

  sub->info_types = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->info_constants = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->info_switch_infos = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);

  sub->info_long_pool_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->info_string_pool_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  
  return sub;
}

int32_t SPVM_SUB_get_var_alloc_length(SPVM_COMPILER* compiler, SPVM_SUB* sub) {
  // Calcurate variable alloc length
  int32_t var_alloc_length = 0;
  {
    int32_t my_index;
    for (my_index = 0; my_index < sub->mys->length; my_index++) {
      SPVM_MY* my = SPVM_LIST_fetch(sub->mys, my_index);
      SPVM_TYPE* type = SPVM_OP_get_type(compiler, my->op_my);
      int32_t width = SPVM_TYPE_get_width(compiler, type->basic_type->id, type->dimension, type->flag);
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
    for (arg_index = 0; arg_index < sub->args->length; arg_index++) {
      SPVM_MY* arg_my = SPVM_LIST_fetch(sub->args, arg_index);
      SPVM_TYPE* type = SPVM_OP_get_type(compiler, arg_my->op_my);
      int32_t width = SPVM_TYPE_get_width(compiler, type->basic_type->id, type->dimension, type->flag);
      arg_alloc_length += width;
    }
  }
  return arg_alloc_length;
}

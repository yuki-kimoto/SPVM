#include <stdlib.h>

#include "spvm_method.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_my.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_type.h"
#include "spvm_basic_type.h"

SPVM_METHOD* SPVM_METHOD_new(SPVM_COMPILER* compiler) {
  SPVM_METHOD* method = SPVM_ALLOCATOR_new_block_compile_eternal(compiler->allocator, sizeof(SPVM_METHOD));
  
  method->args = SPVM_ALLOCATOR_new_list_compile_eternal(compiler->allocator, 0);
  method->mys = SPVM_ALLOCATOR_new_list_compile_eternal(compiler->allocator, 0);
  method->arg_types = SPVM_ALLOCATOR_new_list_compile_eternal(compiler->allocator, 0);
  method->object_arg_ids = SPVM_ALLOCATOR_new_list_compile_eternal(compiler->allocator, 0);
  method->captures = SPVM_ALLOCATOR_new_list_compile_eternal(compiler->allocator, 0);
  
  return method;
}

int32_t SPVM_METHOD_get_var_alloc_length(SPVM_COMPILER* compiler, SPVM_METHOD* method) {
  // Calcurate variable alloc length
  int32_t var_alloc_length = 0;
  {
    int32_t my_index;
    for (my_index = 0; my_index < method->mys->length; my_index++) {
      SPVM_MY* my = SPVM_LIST_fetch(method->mys, my_index);
      SPVM_TYPE* type = SPVM_OP_get_type(compiler, my->op_my);
      int32_t width = SPVM_TYPE_get_width(compiler, type->basic_type->id, type->dimension, type->flag);
      var_alloc_length += width;
    }
  }
  return var_alloc_length;
}


int32_t SPVM_METHOD_get_arg_alloc_length(SPVM_COMPILER* compiler, SPVM_METHOD* method) {
  // Calcurate variable alloc length
  int32_t arg_alloc_length = 0;
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < method->args->length; arg_index++) {
      SPVM_MY* arg_my = SPVM_LIST_fetch(method->args, arg_index);
      SPVM_TYPE* type = arg_my->type;
      int32_t width = SPVM_TYPE_get_width(compiler, type->basic_type->id, type->dimension, type->flag);
      arg_alloc_length += width;
    }
  }
  return arg_alloc_length;
}

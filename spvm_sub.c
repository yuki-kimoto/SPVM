#include <stdlib.h>

#include "spvm_sub.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler) {
  SPVM_SUB* sub = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_SUB));
  
  sub->op_args = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->op_mys = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  sub->object_arg_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  
  return sub;
}

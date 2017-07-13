#include <stdlib.h>

#include "spvm_sub.h"
#include "spvm_dynamic_array.h"
#include "spvm_hash.h"

#include "spvm_compiler_allocator.h"
#include "spvm_bytecode_array.h"
#include "spvm_compiler.h"

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler) {
  SPVM_SUB* sub = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_SUB));
  
  sub->op_args = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  sub->op_my_vars = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  sub->constant_pool_index = -1;

  sub->op_name = NULL;
  sub->op_return_type = NULL;
  sub->op_block = NULL;
  sub->native_address = NULL;
  sub->abs_name = NULL;
  sub->file_name = NULL;
  sub->bytecode_base = -1;
  sub->bytecode_length = 0;
  sub->operand_stack_max = 0;
  sub->is_native = 0;
  sub->is_constant = 0;
  
  return sub;
}

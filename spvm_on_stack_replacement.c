#include "spvm_on_stack_replacement.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_ON_STACK_REPLACEMENT* SPVM_ON_STACK_REPLACEMENT_new(SPVM_COMPILER* compiler) {
  SPVM_ON_STACK_REPLACEMENT* on_stack_replacement = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_ON_STACK_REPLACEMENT));

  on_stack_replacement->op_type = NULL;
  on_stack_replacement->op_name = NULL;
  on_stack_replacement->index = -1;
  
  return on_stack_replacement;
}

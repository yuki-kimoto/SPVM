#include "spvm_my_var.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_MY_VAR* SPVM_MY_VAR_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_MY_VAR));
}

#include "spvm_arg.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_ARG* SPVM_ARG_new(SPVM_COMPILER* compiler) {
  SPVM_ARG* arg = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_ARG));

  return arg;
}

#include "spvm_array_init.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_ARRAY_INIT* SPVM_ARRAY_INIT_new(SPVM_COMPILER* compiler) {
  SPVM_ARRAY_INIT* array_init = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_ARRAY_INIT));
  
  return array_init;
}

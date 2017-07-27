#include "spvm_use.h"
#include "spvm_dynamic_array.h"
#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_USE* SPVM_USE_new(SPVM_COMPILER* compiler) {
  SPVM_USE* use = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_USE));
  
  use->package_name = NULL;
  use->template_args = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  return use;
}

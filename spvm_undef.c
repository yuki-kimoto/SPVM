#include <assert.h>
#include <string.h>

#include "spvm_undef.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_UNDEF* SPVM_UNDEF_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_UNDEF));
}

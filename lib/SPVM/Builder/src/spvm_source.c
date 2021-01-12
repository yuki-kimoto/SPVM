#include "spvm_source.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_SOURCE* SPVM_SOURCE_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_SOURCE));
}

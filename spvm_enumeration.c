#include "spvm_enumeration.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_ENUMERATION* SPVM_ENUMERATION_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_ENUMERATION));
}

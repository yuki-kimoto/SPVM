#include "spvm_allow.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_ALLOW* SPVM_ALLOW_new(SPVM_COMPILER* compiler) {
  SPVM_ALLOW* allow = SPVM_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_ALLOW));
  
  return allow;
}

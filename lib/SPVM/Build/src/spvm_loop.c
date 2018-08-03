#include "spvm_loop.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_LOOP* SPVM_LOOP_new(SPVM_COMPILER* compiler) {
  SPVM_LOOP* loop = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_LOOP));
  
  return loop;
}

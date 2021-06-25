#include "spvm_call_method.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_CALL_METHOD* SPVM_CALL_METHOD_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_CALL_METHOD));
}

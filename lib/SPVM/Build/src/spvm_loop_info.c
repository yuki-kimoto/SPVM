#include "spvm_loop_info.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_LOOP_INFO* SPVM_LOOP_INFO_new(SPVM_COMPILER* compiler) {
  SPVM_LOOP_INFO* loop_info = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_LOOP_INFO));
  
  return loop_info;
}

#include "spvm_switch_info.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_SWITCH_INFO* SPVM_SWITCH_INFO_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_SWITCH_INFO));
}

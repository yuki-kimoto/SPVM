#include <assert.h>
#include <string.h>

#include "spvm_sub_check_info.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_SUB_CHECK_INFO* SPVM_SUB_CHECK_INFO_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_SUB_CHECK_INFO));
}

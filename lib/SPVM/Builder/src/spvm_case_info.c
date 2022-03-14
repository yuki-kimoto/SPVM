#include "spvm_case_info.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_CASE_INFO* SPVM_CASE_INFO_new(SPVM_COMPILER* compiler) {
  SPVM_CASE_INFO* case_info = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_CASE_INFO));
  
  return case_info;
}

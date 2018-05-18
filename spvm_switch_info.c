#include "spvm_switch_info.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"
#include "spvm_list.h"

SPVM_SWITCH_INFO* SPVM_SWITCH_INFO_new(SPVM_COMPILER* compiler) {
  SPVM_SWITCH_INFO* switch_info = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, sizeof(SPVM_SWITCH_INFO));
  
  switch_info->op_cases = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, 0);
  switch_info->case_opcode_indexes = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, 0);
  
  return switch_info;
}

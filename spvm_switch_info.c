#include "spvm_switch_info.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"
#include "spvm_dynamic_array.h"

SPVM_SWITCH_INFO* SPVM_SWITCH_INFO_new(SPVM_COMPILER* compiler) {
  SPVM_SWITCH_INFO* switch_info = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_SWITCH_INFO));
  
  switch_info->op_cases = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  switch_info->op_default = NULL;
  
  switch_info->max = 0;
  switch_info->min = 0;
  switch_info->code = 0;
  
  return switch_info;
}

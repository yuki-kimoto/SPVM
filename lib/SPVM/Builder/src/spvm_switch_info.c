#include "spvm_switch_info.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_list.h"

SPVM_SWITCH_INFO* SPVM_SWITCH_INFO_new(SPVM_COMPILER* compiler) {
  SPVM_SWITCH_INFO* switch_info = SPVM_ALLOCATOR_new_block_permanent(compiler->allocator, sizeof(SPVM_SWITCH_INFO));
  
  switch_info->case_infos = SPVM_ALLOCATOR_new_list_permanent(compiler->allocator, 0);
  
  return switch_info;
}

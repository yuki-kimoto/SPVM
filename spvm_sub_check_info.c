#include <assert.h>
#include <string.h>

#include "spvm_sub_check_info.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_SUB_CHECK_INFO* SPVM_SUB_CHECK_INFO_new(SPVM_COMPILER* compiler) {
  (void)compiler;

  SPVM_SUB_CHECK_INFO* sub_check_info = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_SUB_CHECK_INFO));

  // my var informations
  sub_check_info->op_mys = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  // my variable stack
  sub_check_info->op_my_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  // block my variable base position stack
  sub_check_info->block_my_base_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);

  // try block my variable base position stack
  sub_check_info->try_block_my_base_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  // loop block my variable base position stack
  sub_check_info->loop_block_my_base_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  // Switch information stack
  sub_check_info->op_switch_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  return sub_check_info;
}

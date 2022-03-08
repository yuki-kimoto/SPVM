#include "spvm_my.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_MY* SPVM_MY_new(SPVM_COMPILER* compiler) {
  SPVM_MY* my = SPVM_ALLOCATOR_new_block_compile_tmp(compiler->allocator, sizeof(SPVM_MY));

  my->id = -1;
  my->mem_id = -1;
  
  return my;
}

SPVM_MY* SPVM_MY_new_eternal(SPVM_COMPILER* compiler) {
  SPVM_MY* my = SPVM_ALLOCATOR_new_block_compile_eternal(compiler->allocator, sizeof(SPVM_MY));

  my->id = -1;
  my->mem_id = -1;
  my->is_eternal = 1;
  
  return my;
}

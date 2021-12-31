#include "spvm_block.h"
#include "spvm_list.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_BLOCK* SPVM_BLOCK_new(SPVM_COMPILER* compiler) {
  SPVM_BLOCK* block = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, sizeof(SPVM_BLOCK));
  
  return block;
}

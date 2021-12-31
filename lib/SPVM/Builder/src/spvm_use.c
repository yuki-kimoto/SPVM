#include "spvm_use.h"
#include "spvm_list.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_USE* SPVM_USE_new(SPVM_COMPILER* compiler) {
  SPVM_USE* use = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, sizeof(SPVM_USE));
  
  return use;
}

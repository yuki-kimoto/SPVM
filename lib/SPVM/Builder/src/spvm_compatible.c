#include "spvm_compatible.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_IMPLEMENT* SPVM_IMPLEMENT_new(SPVM_COMPILER* compiler) {
  SPVM_IMPLEMENT* compatible = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, sizeof(SPVM_IMPLEMENT));
  
  return compatible;
}

#include "spvm_compatible.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_COMPATIBLE* SPVM_COMPATIBLE_new(SPVM_COMPILER* compiler) {
  SPVM_COMPATIBLE* compatible = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, sizeof(SPVM_COMPATIBLE));
  
  return compatible;
}

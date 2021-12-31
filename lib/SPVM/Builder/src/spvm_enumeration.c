#include "spvm_enumeration.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_ENUMERATION* SPVM_ENUMERATION_new(SPVM_COMPILER* compiler) {
  return SPVM_ALLOCATOR_new_block_compile_eternal(compiler, sizeof(SPVM_ENUMERATION));
}

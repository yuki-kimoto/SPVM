#include "spvm_enumeration_value.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_ENUMERATION_VALUE* SPVM_ENUMERATION_VALUE_new(SPVM_COMPILER* compiler) {
  return SPVM_ALLOCATOR_new_block_compile_eternal(compiler, sizeof(SPVM_ENUMERATION_VALUE));
}

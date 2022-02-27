#include "spvm_string.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_STRING* SPVM_STRING_new(SPVM_COMPILER* compiler) {
  SPVM_STRING* string = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, sizeof(SPVM_STRING));
  
  return string;
}

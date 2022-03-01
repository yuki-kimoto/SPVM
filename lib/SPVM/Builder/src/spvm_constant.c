#include <string.h>


#include "spvm_compiler.h"
#include "spvm_constant.h"
#include "spvm_allocator.h"
#include "spvm_hash.h"
#include "spvm_type.h"

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM_COMPILER* compiler) {
  SPVM_CONSTANT* constant = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, sizeof(SPVM_CONSTANT));
  
  return constant;
}

#include "spvm_opcode.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_OPCODE* SPVM_OPCODE_new(SPVM_COMPILER* compiler) {
  SPVM_OPCODE* opcode = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_OPCODE));
  
  return opcode;
}

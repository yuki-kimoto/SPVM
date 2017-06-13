#include "spvm_descriptor.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

const char* const SPVM_DESCRIPTOR_C_CODE_NAMES[] = {
  "native",
  "const",
};

SPVM_DESCRIPTOR* SPVM_DESCRIPTOR_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_DESCRIPTOR));
}

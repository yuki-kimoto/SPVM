#include "spvm_descriptor.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

const char* const SPVM_DESCRIPTOR_C_ID_NAMES[] = {
  "native",
  "compile",
  "const",
  "jit",
  "interface",
  "public",
  "private",
};

SPVM_DESCRIPTOR* SPVM_DESCRIPTOR_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, sizeof(SPVM_DESCRIPTOR));
}

#include "spvm_descriptor.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

const char* const SPVM_DESCRIPTOR_C_ID_NAMES[] = {
  "interface_t",
  "value_t",
  "pointer_t",
  "native",
  "precompile",
  "public",
  "private",
  "rw",
  "ro",
  "wo",
};

SPVM_DESCRIPTOR* SPVM_DESCRIPTOR_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_DESCRIPTOR));
}

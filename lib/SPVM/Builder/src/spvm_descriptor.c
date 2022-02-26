#include "spvm_descriptor.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

const char* const* SPVM_DESCRIPTOR_C_ID_NAMES(void) {

  static const char* const id_names[] = {
    "callback_t",
    "mulnum_t",
    "pointer_t",
    "native",
    "precompile",
    "public",
    "private",
    "rw",
    "ro",
    "wo",
    "static",
    "interface_t",
  };
  
  return id_names;
}

SPVM_DESCRIPTOR* SPVM_DESCRIPTOR_new(SPVM_COMPILER* compiler) {
  return SPVM_ALLOCATOR_new_block_compile_tmp(compiler, sizeof(SPVM_DESCRIPTOR));
}

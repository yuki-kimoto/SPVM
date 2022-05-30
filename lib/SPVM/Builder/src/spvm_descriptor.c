#include "spvm_descriptor.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"


const char* const* SPVM_DESCRIPTOR_C_ID_NAMES(void) {

  static const char* const id_names[] = {
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
    "required",
  };
  
  return id_names;
}

const char* SPVM_DESCRIPTOR_get_name(SPVM_COMPILER* compiler, int32_t id) {
  return (SPVM_DESCRIPTOR_C_ID_NAMES())[id];
}

SPVM_DESCRIPTOR* SPVM_DESCRIPTOR_new(SPVM_COMPILER* compiler) {
  return SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, sizeof(SPVM_DESCRIPTOR));
}

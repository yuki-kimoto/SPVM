#include "spvm_attribute.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"


const char* const* SPVM_ATTRIBUTE_C_ID_NAMES(void) {

  static const char* const id_names[] = {
    "mulnum_t",
    "pointer_t",
    "native",
    "precompile",
    "public",
    "protected",
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

const char* SPVM_ATTRIBUTE_get_name(SPVM_COMPILER* compiler, int32_t id) {
  return (SPVM_ATTRIBUTE_C_ID_NAMES())[id];
}

SPVM_ATTRIBUTE* SPVM_ATTRIBUTE_new(SPVM_COMPILER* compiler) {
  return SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, sizeof(SPVM_ATTRIBUTE));
}

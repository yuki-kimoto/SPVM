#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_basic_type.h"
#include "spvm_allocator.h"

const char* const* SPVM_BASIC_TYPE_C_ID_NAMES(void) {

  static const char* const id_names[] = {
    "unknown",
    "undef",
    "void",
    "byte",
    "short",
    "int",
    "long",
    "float",
    "double",
    "string",
    "object",
    "Byte",
    "Short",
    "Int",
    "Long",
    "Float",
    "Double",
    "Bool",
  };
  
  return id_names;
}

const char* const* SPVM_BASIC_TYPE_C_CATEGORY_NAMES(void) {

  static const char* const id_names[] = {
    "unknown"
    "fail_load",
    "undef"
    "void"
    "numeric"
    "mulnum"
    "string",
    "class",
    "interface",
    "callback",
    "any_obejct",
  };
  
  return id_names;
}

SPVM_BASIC_TYPE* SPVM_BASIC_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_BASIC_TYPE* basic_type = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_BASIC_TYPE));
  
  return basic_type;
}

const char* SPVM_BASIC_TYPE_get_basic_type_name(int32_t basic_type_id) {
  return (SPVM_BASIC_TYPE_C_ID_NAMES())[basic_type_id];
}

const char* SPVM_BASIC_TYPE_get_basic_type_category_name(int32_t basic_type_id) {
  return (SPVM_BASIC_TYPE_C_CATEGORY_NAMES())[basic_type_id];
}

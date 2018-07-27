#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_basic_type.h"
#include "spvm_compiler_allocator.h"

const char* const SPVM_BASIC_TYPE_C_ID_NAMES[] = {
  "unknown",
  "void",
  "undef",
  "byte_ref",
  "short_ref",
  "int_ref",
  "long_ref",
  "float_ref",
  "double_ref",
  "byte",
  "short",
  "int",
  "long",
  "float",
  "double",
  "object",
};

const char* const SPVM_BASIC_TYPE_C_CATEGORY_NAMES[] = {
  "unknown",
  "void",
  "undef",
  "byte_ref",
  "short_ref",
  "int_ref",
  "long_ref",
  "float_ref",
  "double_ref",
  "numeric",
  "any_object",
  "class",
  "interface",
  "pointer",
  "value_t",
};

SPVM_BASIC_TYPE* SPVM_BASIC_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_BASIC_TYPE* basic_type = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_BASIC_TYPE));
  
  return basic_type;
}

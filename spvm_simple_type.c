#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_simple_type.h"
#include "spvm_compiler_allocator.h"

const char* const SPVM_SIMPLE_TYPE_C_CATEGORY_NAMES[] = {
  "unknown",
  "void",
  "undef",
  "numeric",
  "any_object",
  "package",
};

const char* const SPVM_SIMPLE_TYPE_C_ID_NAMES[] = {
  "unknown",
  "void",
  "undef",
  "byte",
  "short",
  "int",
  "long",
  "float",
  "double",
  "Object",
  "String",
};

SPVM_SIMPLE_TYPE* SPVM_SIMPLE_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_SIMPLE_TYPE* simple_type = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_SIMPLE_TYPE));
  
  return simple_type;
}

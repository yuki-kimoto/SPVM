#include <string.h>


#include "spvm_compiler.h"
#include "spvm_constant.h"
#include "spvm_compiler_allocator.h"
#include "spvm_hash.h"

const char* const SPVM_CONSTANT_C_CODE_NAMES[] = {
  "BYTE",
  "SHORT",
  "INT",
  "LONG",
  "FLOAT",
  "DOUBLE",
  "STRING",
};

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_CONSTANT));
}

SPVM_CONSTANT* SPVM_CONSTANT_create_int_1(SPVM_COMPILER* compiler) {
  
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->code = SPVM_CONSTANT_C_CODE_INT;
  constant->uv.long_value = 1;
  constant->resolved_type = SPVM_HASH_search(compiler->resolved_type_symtable, "int", strlen("int"));
  
  return constant;
}

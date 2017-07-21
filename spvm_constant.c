#include <string.h>


#include "spvm_compiler.h"
#include "spvm_constant.h"
#include "spvm_compiler_allocator.h"
#include "spvm_hash.h"

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM_COMPILER* compiler) {
  SPVM_CONSTANT* constant = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_CONSTANT));
  
  constant->sign = 0;
  constant->resolved = 0;
  constant->type = NULL;
  
  return constant;
}

SPVM_CONSTANT* SPVM_CONSTANT_create_int_1(SPVM_COMPILER* compiler) {
  
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  constant->uv.long_value = 1;
  constant->type = SPVM_HASH_search(compiler->type_symtable, "int", strlen("int"));
  constant->resolved = 1;
  
  return constant;
}

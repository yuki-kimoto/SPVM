#include <string.h>

#include "spvm.h"
#include "spvm_parser.h"
#include "spvm_constant.h"
#include "spvm_parser_allocator.h"
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

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM* spvm) {
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_CONSTANT));
}

SPVM_CONSTANT* SPVM_CONSTANT_create_int_1(SPVM* spvm) {
  
  SPVM_PARSER* parser = spvm->parser;
  
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(spvm);
  
  constant->code = SPVM_CONSTANT_C_CODE_INT;
  constant->uv.long_value = 1;
  constant->resolved_type = SPVM_HASH_search(spvm, parser->resolved_type_symtable, "int", strlen("int"));
  
  return constant;
}

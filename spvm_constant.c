#include <string.h>


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

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM_PARSER* parser) {
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(parser, parser->allocator, sizeof(SPVM_CONSTANT));
}

SPVM_CONSTANT* SPVM_CONSTANT_create_int_1(SPVM_PARSER* parser) {
  
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(parser);
  
  constant->code = SPVM_CONSTANT_C_CODE_INT;
  constant->uv.long_value = 1;
  constant->resolved_type = SPVM_HASH_search(parser->resolved_type_symtable, "int", strlen("int"));
  
  return constant;
}

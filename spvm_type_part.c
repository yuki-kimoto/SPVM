#include "spvm_type_part.h"
#include "spvm.h"
#include "spvm_allocator_parser.h"
#include "spvm_parser.h"

const char* const SPVM_TYPE_PART_C_CODE_NAMES[] = {
  "sub",
  "name",
  "char"
};

SPVM_TYPE_PART* SPVM_TYPE_PART_new(SPVM* spvm) {
  return SPVM_ALLOCATOR_PARSER_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_TYPE_PART));
}

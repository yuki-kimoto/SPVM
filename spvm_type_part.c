#include "spvm_type_part.h"
#include "spvm_.h"
#include "spvm_parser_allocator.h"
#include "spvm_parser.h"

const char* const SPVM_TYPE_PART_C_CODE_NAMES[] = {
  "sub",
  "name",
  "char"
};

SPVM_TYPE_PART* SPVM_TYPE_PART_new(SPVM_* spvm) {
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_TYPE_PART));
}

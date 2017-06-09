#include "spvm_enumeration_value.h"
#include "spvm.h"
#include "spvm_parser_allocator.h"
#include "spvm_parser.h"

SPVM_ENUMERATION_VALUE* SPVM_ENUMERATION_VALUE_new(SPVM* spvm) {
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_ENUMERATION_VALUE));
}

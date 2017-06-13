#include "spvm_enumeration_value.h"

#include "spvm_parser_allocator.h"
#include "spvm_parser.h"

SPVM_ENUMERATION_VALUE* SPVM_ENUMERATION_VALUE_new(SPVM_PARSER* parser) {
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(parser, parser->allocator, sizeof(SPVM_ENUMERATION_VALUE));
}

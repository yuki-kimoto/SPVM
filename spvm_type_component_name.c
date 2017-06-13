#include "spvm_type_component_name.h"

#include "spvm_parser_allocator.h"
#include "spvm_parser.h"

SPVM_TYPE_COMPONENT_NAME* SPVM_TYPE_COMPONENT_NAME_new(SPVM_PARSER* parser) {
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(parser, parser->allocator, sizeof(SPVM_TYPE_COMPONENT_NAME));
}

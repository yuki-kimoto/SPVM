#include "spvm_name_info.h"

#include "spvm_parser_allocator.h"
#include "spvm_parser.h"

SPVM_NAME_INFO* SPVM_NAME_INFO_new(SPVM_PARSER* parser) {
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(parser, parser->allocator, sizeof(SPVM_NAME_INFO));
}

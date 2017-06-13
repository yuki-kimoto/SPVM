#include "spvm_var.h"

#include "spvm_parser_allocator.h"
#include "spvm_parser.h"

SPVM_VAR* SPVM_VAR_new(SPVM_PARSER* parser) {
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(parser, parser->allocator, sizeof(SPVM_VAR));
}

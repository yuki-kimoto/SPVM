#include <stdlib.h>

#include "spvm_sub.h"
#include "spvm_array.h"
#include "spvm_hash.h"

#include "spvm_parser_allocator.h"
#include "spvm_bytecode_array.h"
#include "spvm_parser.h"

SPVM_SUB* SPVM_SUB_new(SPVM_PARSER* parser) {
  SPVM_SUB* sub = SPVM_PARSER_ALLOCATOR_alloc_memory_pool(parser, parser->allocator, sizeof(SPVM_SUB));
  
  sub->op_args = SPVM_PARSER_ALLOCATOR_alloc_array(parser, parser->allocator, 0);
  sub->op_my_vars = SPVM_PARSER_ALLOCATOR_alloc_array(parser, parser->allocator, 0);
  
  return sub;
}

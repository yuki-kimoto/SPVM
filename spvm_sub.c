#include <stdlib.h>

#include "spvm_sub.h"
#include "spvm_array.h"
#include "spvm_hash.h"
#include "spvm.h"
#include "spvm_allocator_parser.h"
#include "spvm_bytecode_array.h"
#include "spvm_parser.h"

SPVM_SUB* SPVM_SUB_new(SPVM* spvm) {
  SPVM_SUB* sub = SPVM_ALLOCATOR_PARSER_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_SUB));
  
  sub->op_args = SPVM_ALLOCATOR_PARSER_alloc_array(spvm, spvm->parser->allocator, 0);
  sub->op_my_vars = SPVM_ALLOCATOR_PARSER_alloc_array(spvm, spvm->parser->allocator, 0);
  
  return sub;
}

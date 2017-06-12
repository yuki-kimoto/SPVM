#include "spvm_my_var.h"
#include "spvm_.h"
#include "spvm_parser_allocator.h"
#include "spvm_parser.h"

SPVM_MY_VAR* SPVM_MY_VAR_new(SPVM_* spvm) {
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_MY_VAR));
}

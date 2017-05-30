#include "spvm_my_var.h"
#include "spvm.h"
#include "spvm_allocator_parser.h"
#include "spvm_parser.h"

SPVM_MY_VAR* SPVM_MY_VAR_new(SPVM* spvm) {
  return SPVM_ALLOCATOR_PARSER_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_MY_VAR));
}

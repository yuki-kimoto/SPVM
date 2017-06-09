#include "spvm_name_info.h"
#include "spvm.h"
#include "spvm_parser_allocator.h"
#include "spvm_parser.h"

SPVM_NAME_INFO* SPVM_NAME_INFO_new(SPVM* spvm) {
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_NAME_INFO));
}

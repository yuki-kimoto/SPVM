#include "spvm_package.h"
#include "spvm.h"
#include "spvm_parser_allocator.h"
#include "spvm_constant_pool.h"
#include "spvm_parser.h"

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM* spvm) {
  SPVM_PACKAGE* package = SPVM_PARSER_ALLOCATOR_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_PACKAGE));
  
  package->op_subs = SPVM_PARSER_ALLOCATOR_alloc_array(spvm, spvm->parser->allocator, 0);
  package->op_fields = SPVM_PARSER_ALLOCATOR_alloc_array(spvm, spvm->parser->allocator, 0);
  
  return package;
}

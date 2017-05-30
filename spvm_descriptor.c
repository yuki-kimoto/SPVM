#include "spvm_descriptor.h"
#include "spvm.h"
#include "spvm_allocator_parser.h"
#include "spvm_parser.h"

const char* const SPVM_DESCRIPTOR_C_CODE_NAMES[] = {
  "native",
  "const",
};

SPVM_DESCRIPTOR* SPVM_DESCRIPTOR_new(SPVM* spvm) {
  return SPVM_ALLOCATOR_PARSER_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_DESCRIPTOR));
}

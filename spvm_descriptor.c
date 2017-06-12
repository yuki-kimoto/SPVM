#include "spvm_descriptor.h"
#include "spvm_.h"
#include "spvm_parser_allocator.h"
#include "spvm_parser.h"

const char* const SPVM_DESCRIPTOR_C_CODE_NAMES[] = {
  "native",
  "const",
};

SPVM_DESCRIPTOR* SPVM_DESCRIPTOR_new(SPVM_* spvm) {
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_DESCRIPTOR));
}

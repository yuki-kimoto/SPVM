#include "spvm_type_component_name.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_TYPE_COMPONENT_NAME* SPVM_TYPE_COMPONENT_NAME_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_TYPE_COMPONENT_NAME));
}

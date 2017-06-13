#include "spvm_package.h"

#include "spvm_compiler_allocator.h"
#include "spvm_constant_pool.h"
#include "spvm_compiler.h"

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM_COMPILER* compiler) {
  SPVM_PACKAGE* package = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_PACKAGE));
  
  package->op_subs = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  package->op_fields = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  return package;
}

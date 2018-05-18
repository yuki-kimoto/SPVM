#include <assert.h>
#include <string.h>

#include "spvm_our.h"

#include "spvm_compiler_allocator.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_compiler.h"

SPVM_OUR* SPVM_OUR_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, sizeof(SPVM_OUR));
}


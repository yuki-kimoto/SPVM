#include <assert.h>
#include <string.h>

#include "spvm_symbol.h"
#include "spvm_compiler.h"
#include "spvm_compiler_allocator.h"

SPVM_SYMBOL* SPVM_SYMBOL_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  return SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_SYMBOL));
}


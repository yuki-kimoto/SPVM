#include "spvm_my.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_MY* SPVM_MY_new(SPVM_COMPILER* compiler) {
  SPVM_MY* my = SPVM_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_MY));

  my->id = -1;
  my->mem_id = -1;
  
  return my;
}

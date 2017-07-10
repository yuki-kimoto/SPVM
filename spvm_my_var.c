#include "spvm_my_var.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_MY_VAR* SPVM_MY_VAR_new(SPVM_COMPILER* compiler) {
  SPVM_MY_VAR* my_var = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_MY_VAR));

  my_var->op_type = NULL;
  my_var->op_name = NULL;
  my_var->index = -1;
  
  return my_var;
}

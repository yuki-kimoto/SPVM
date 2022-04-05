#include <stdlib.h>

#include "spvm_method.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_var_decl.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_type.h"
#include "spvm_basic_type.h"

SPVM_METHOD* SPVM_METHOD_new(SPVM_COMPILER* compiler) {
  SPVM_METHOD* method = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_METHOD));
  
  method->var_decls = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  method->captures = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  
  return method;
}

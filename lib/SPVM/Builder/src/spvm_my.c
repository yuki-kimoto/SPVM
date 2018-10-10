#include "spvm_my.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_MY* SPVM_MY_new(SPVM_COMPILER* compiler) {
  SPVM_MY* my = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_MY));

  my->var_id = -1;
  
  my->byte_var_id = -1;
  my->short_var_id = -1;
  my->int_var_id = -1;
  my->long_var_id = -1;
  my->float_var_id = -1;
  my->double_var_id = -1;
  my->object_var_id = -1;
  my->ref_var_id = -1;
  my->ref_var_id = -1;
  my->value_field_basic_type_id = -1;
  
  return my;
}

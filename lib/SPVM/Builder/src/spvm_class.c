#include "spvm_class.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_field.h"
#include "spvm_op.h"
#include "spvm_list.h"
#include "spvm_type.h"
#include "spvm_limit.h"
#include "spvm_hash.h"

const char* const* SPVM_CLASS_C_CATEGORY_NAMES(void) {
  
  static const char* const category_names[] = {
    "class",
    "callback_t",
    "mulnum_t",
    "interface_t"
  };
  
  return category_names;
}

SPVM_CLASS* SPVM_CLASS_new(SPVM_COMPILER* compiler) {
  SPVM_CLASS* class = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, sizeof(SPVM_CLASS));
  
  // Fields
  class->fields = SPVM_ALLOCATOR_new_list_compile_eternal(compiler, 0);
  class->field_symtable = SPVM_ALLOCATOR_new_hash_compile_eternal(compiler, 0);
  
  // Class variables
  class->class_vars = SPVM_ALLOCATOR_new_list_compile_eternal(compiler, 0);
  class->class_var_symtable = SPVM_ALLOCATOR_new_hash_compile_eternal(compiler, 0);

  class->methods = SPVM_ALLOCATOR_new_list_compile_eternal(compiler, 0);
  class->method_symtable = SPVM_ALLOCATOR_new_hash_compile_eternal(compiler, 0);
  class->class_vars = SPVM_ALLOCATOR_new_list_compile_eternal(compiler, 0);
  class->class_var_symtable = SPVM_ALLOCATOR_new_hash_compile_eternal(compiler, 0);
  class->interface_class_symtable = SPVM_ALLOCATOR_new_hash_compile_eternal(compiler, 0);
  
  class->info_switch_infos = SPVM_ALLOCATOR_new_list_compile_eternal(compiler, 0);
  class->op_uses = SPVM_ALLOCATOR_new_list_compile_eternal(compiler, 0);
  class->op_allows = SPVM_ALLOCATOR_new_list_compile_eternal(compiler, 0);
  class->op_implements = SPVM_ALLOCATOR_new_list_compile_eternal(compiler, 0);
  class->info_constants = SPVM_ALLOCATOR_new_list_compile_eternal(compiler, 0);
  class->anon_methods = SPVM_ALLOCATOR_new_list_compile_eternal(compiler, 0);
  class->class_alias_symtable = SPVM_ALLOCATOR_new_hash_compile_eternal(compiler, 0);

  return class;
}

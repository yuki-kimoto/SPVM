#include "spvm_class.h"

#include "spvm_compiler_allocator.h"
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
    "value",
  };
  
  return category_names;
}

SPVM_CLASS* SPVM_CLASS_new(SPVM_COMPILER* compiler) {
  SPVM_CLASS* class = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_CLASS));
  
  // Fields
  class->fields = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->field_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  
  // Class variables
  class->class_vars = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->class_var_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);

  class->methods = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->method_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  class->class_vars = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->class_var_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  
  class->info_class_var_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->info_class_var_id_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  class->info_method_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->info_method_id_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  class->info_field_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->info_field_id_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  class->info_basic_type_ids = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->info_basic_type_id_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  class->info_switch_infos = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->op_uses = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->op_allows = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->info_constants = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->anon_methods = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  class->class_alias_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);

  return class;
}

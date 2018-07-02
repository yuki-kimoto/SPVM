#include "spvm_package.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"
#include "spvm_field.h"
#include "spvm_op.h"
#include "spvm_list.h"
#include "spvm_type.h"
#include "spvm_limit.h"
#include "spvm_hash.h"

const char* const SPVM_PACKAGE_C_CATEGORY_NAMES[] = {
  "class",
  "interface",
  "struct",
};

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM_COMPILER* compiler) {
  SPVM_PACKAGE* package = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_PACKAGE));
  
  // Fields
  package->op_fields = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  package->op_field_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  
  // Package variables
  package->op_package_vars = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  package->op_package_var_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);

  package->sub_signatures = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  package->sub_signature_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  package->field_signatures = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  package->field_signature_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  package->package_var_signatures = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  package->package_var_signature_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);

  package->has_interface_cache_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  package->op_subs = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  package->op_sub_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  package->op_package_vars = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  package->op_package_var_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  package->object_field_indexes = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);

  package->op_types = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  
  return package;
}

int32_t SPVM_PACKAGE_get_object_fields_length(SPVM_COMPILER* compiler, SPVM_PACKAGE* package) {
  
  SPVM_LIST* op_fields = package->op_fields;
  
  int32_t object_fields_length = 0;
  
  int32_t field_pos;
  for (field_pos = 0; field_pos < op_fields->length; field_pos++) {
    SPVM_OP* op_field = SPVM_LIST_fetch(op_fields, field_pos);
    SPVM_FIELD* field = op_field->uv.field;
    SPVM_TYPE* field_type = field->op_type->uv.type;
    
    if (SPVM_TYPE_is_object(compiler, field_type)) {
      object_fields_length++;
    }
  }
  
  return object_fields_length;
}

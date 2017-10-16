#include "spvm_package.h"

#include "spvm_compiler_allocator.h"
#include "spvm_constant_pool.h"
#include "spvm_compiler.h"
#include "spvm_field_info.h"
#include "spvm_op.h"
#include "spvm_dynamic_array.h"
#include "spvm_type.h"

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM_COMPILER* compiler) {
  SPVM_PACKAGE* package = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_PACKAGE));
  
  package->op_fields = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  package->native_subs = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  return package;
}

int32_t SPVM_PACKAGE_get_object_fields_length(SPVM_COMPILER* compiler, SPVM_PACKAGE* package) {
  
  SPVM_DYNAMIC_ARRAY* op_fields = package->op_fields;
  
  int32_t ref_fields_length = 0;
  
  int32_t field_pos;
  for (field_pos = 0; field_pos < op_fields->length; field_pos++) {
    SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(op_fields, field_pos);
    SPVM_FIELD_INFO* field = op_field->uv.field_info;
    SPVM_TYPE* field_type = field->op_type->uv.type;
    
    if (!SPVM_TYPE_is_numeric(compiler, field_type)) {
      ref_fields_length++;
    }
  }
  
  return ref_fields_length;
}

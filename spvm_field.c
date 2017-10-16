#include <assert.h>
#include <string.h>

#include "spvm_field.h"

#include "spvm_compiler_allocator.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_compiler.h"

SPVM_FIELD* SPVM_FIELD_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_FIELD));
}

int32_t SPVM_FIELD_get_byte_size(SPVM_COMPILER* compiler, SPVM_FIELD* field) {
  (void)compiler;
  
  SPVM_TYPE* field_type = field->op_type->uv.type;
  
  int32_t byte_size;
  if (field_type->code == SPVM_TYPE_C_CODE_BYTE) {
    byte_size = sizeof(int8_t);
  }
  else if (field_type->code == SPVM_TYPE_C_CODE_SHORT) {
    byte_size = sizeof(int16_t);
  }
  else if (field_type->code == SPVM_TYPE_C_CODE_INT || field_type->code == SPVM_TYPE_C_CODE_FLOAT) {
    byte_size = sizeof(int32_t);
  }
  else if (field_type->code == SPVM_TYPE_C_CODE_LONG || field_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
    byte_size = sizeof(int64_t);
  }
  else {
    byte_size = sizeof(void*);
  }
  
  return byte_size;
}

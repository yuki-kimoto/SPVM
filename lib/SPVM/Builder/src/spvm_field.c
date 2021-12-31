#include <assert.h>
#include <string.h>

#include "spvm_field.h"

#include "spvm_allocator.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_compiler.h"
#include "spvm_basic_type.h"

SPVM_FIELD* SPVM_FIELD_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  return SPVM_ALLOCATOR_new_block_compile_eternal(compiler, sizeof(SPVM_FIELD));
}

int32_t SPVM_FIELD_get_byte_size(SPVM_COMPILER* compiler, SPVM_FIELD* field) {
  (void)compiler;
  
  SPVM_TYPE* field_type = field->type;
  
  int32_t byte_size;
  if (field_type->dimension == 0 && field_type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && field_type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) {
    if (field_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
      byte_size = sizeof(int8_t);
    }
    else if (field_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
      byte_size = sizeof(int16_t);
    }
    else if (field_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT || field_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
      byte_size = sizeof(int32_t);
    }
    else if (field_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG || field_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
      byte_size = sizeof(int64_t);
    }
    else {
      assert(0);
    }
  }
  else {
    byte_size = sizeof(void*);
  }
  
  return byte_size;
}

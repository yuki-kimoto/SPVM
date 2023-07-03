// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>
#include <string.h>

#include "spvm_field.h"

#include "spvm_allocator.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_compiler.h"
#include "spvm_basic_type.h"

SPVM_FIELD* SPVM_FIELD_new(SPVM_COMPILER* compiler) {
  
  return SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_FIELD));
}

int32_t SPVM_FIELD_get_size(SPVM_COMPILER* compiler, SPVM_FIELD* field) {
  
  SPVM_TYPE* field_type = field->type;
  
  int32_t size;
  if (field_type->dimension == 0 && field_type->basic_type->id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && field_type->basic_type->id <= SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {    
    if (field_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
      size = sizeof(int8_t);
    }
    else if (field_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
      size = sizeof(int16_t);
    }
    else if (field_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT || field_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
      size = sizeof(int32_t);
    }
    else if (field_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG || field_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
      size = sizeof(int64_t);
    }
    else {
      assert(0);
    }
  }
  else {
    size = sizeof(void*);
  }
  
  return size;
}

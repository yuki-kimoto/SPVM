#include <assert.h>

#include "spvm_field.h"
#include "spvm.h"
#include "spvm_parser_allocator.h"
#include "spvm_resolved_type.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_parser.h"

SPVM_FIELD* SPVM_FIELD_new(SPVM* spvm) {
  (void)spvm;
  
  return SPVM_PARSER_ALLOCATOR_alloc_memory_pool(spvm, spvm->parser->allocator, sizeof(SPVM_FIELD));
}

int32_t SPVM_FIELD_get_byte_size(SPVM* spvm, SPVM_FIELD* field) {
  (void)spvm;
  
  SPVM_RESOLVED_TYPE* field_resolved_type = field->op_type->uv.type->resolved_type;
  
  int32_t byte_size;
  if (field_resolved_type->id == SPVM_RESOLVED_TYPE_C_ID_BYTE) {
    byte_size = sizeof(int8_t);
  }
  else if (field_resolved_type->id == SPVM_RESOLVED_TYPE_C_ID_SHORT) {
    byte_size = sizeof(int16_t);
  }
  else if (field_resolved_type->id == SPVM_RESOLVED_TYPE_C_ID_INT || field_resolved_type->id == SPVM_RESOLVED_TYPE_C_ID_FLOAT) {
    byte_size = sizeof(int32_t);
  }
  else if (field_resolved_type->id == SPVM_RESOLVED_TYPE_C_ID_LONG || field_resolved_type->id == SPVM_RESOLVED_TYPE_C_ID_DOUBLE) {
    byte_size = sizeof(int64_t);
  }
  else {
    byte_size = sizeof(void*);
  }
  
  return byte_size;
}

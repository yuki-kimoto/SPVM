#include <assert.h>

#include "spvm.h"
#include "spvm_ref.h"
#include "spvm_ref_array.h"
#include "spvm_ref_string.h"
#include "spvm_ref_object.h"
#include "spvm_constant_pool.h"
#include "spvm_constant_pool_package.h"

int64_t SPVM_REF_calcurate_byte_size(SPVM* spvm, SPVM_REF* ref) {
  
  int64_t byte_size;
  
  // Reference is string
  if (ref->type == SPVM_REF_C_TYPE_STRING) {
    byte_size = sizeof(SPVM_REF_STRING);
  }
  // Reference is array
  else if (ref->type == SPVM_REF_C_TYPE_ARRAY) {
    SPVM_REF_ARRAY* ref_array = (SPVM_REF_ARRAY*)ref;
    byte_size = sizeof(SPVM_REF_ARRAY) + ref_array->length * SPVM_REF_ARRAY_C_VALUE_SIZES[ref_array->value_type];
  }
  // Reference is object
  else if (ref->type == SPVM_REF_C_TYPE_OBJECT) {
    SPVM_REF_OBJECT* ref_object = (SPVM_REF_OBJECT*)ref;
    SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&spvm->constant_pool->values[ref_object->package_constant_pool_address];
    byte_size = sizeof(SPVM_REF_OBJECT) + constant_pool_package->byte_size;
  }
  else {
    assert(0);
  }
  
  return byte_size;
}

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "spvm_value.h"
#include "spvm_runtime_api.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_field_info.h"
#include "spvm_constant_pool_package.h"
#include "spvm_constant_pool_type.h"
#include "spvm_object.h"
#include "spvm_value.h"
#include "spvm_runtime.h"
#include "spvm_runtime_allocator.h"
#include "spvm_api.h"
#include "spvm_global.h"
#include "spvm_type.h"
#include "spvm_hash.h"

SPVM_RUNTIME* SPVM_RUNTIME_API_get_runtime(SPVM_API* api) {
  (void)api;
  
  return SPVM_GLOBAL_RUNTIME;
}

void SPVM_RUNTIME_API_set_runtime(SPVM_API* api, SPVM_RUNTIME* runtime) {
  (void)api;
  
  SPVM_GLOBAL_RUNTIME = runtime;
}

int32_t SPVM_RUNTIME_API_get_objects_count(SPVM_API* api) {
  (void)api;
  return SPVM_RUNTIME_API_get_runtime(api)->objects_count;
}

void SPVM_RUNTIME_API_free_weaken_back_refs(SPVM_API* api, SPVM_OBJECT* weaken_back_refs, int32_t weaken_back_refs_length) {
  
  SPVM_OBJECT*** weaken_back_refs_elements = (SPVM_OBJECT***)((intptr_t)weaken_back_refs + sizeof(SPVM_OBJECT));
  
  {
    int32_t i;
    for (i = 0; i < weaken_back_refs_length; i++) {
      *weaken_back_refs_elements[i] = NULL;
    }
  }
  memset(weaken_back_refs_elements, 0, sizeof(SPVM_OBJECT**) * weaken_back_refs->length);
  
  SPVM_RUNTIME_API_dec_ref_count(api, (SPVM_OBJECT*)weaken_back_refs);
}

void SPVM_RUNTIME_API_weaken(SPVM_API* api, SPVM_OBJECT** object_address) {
  (void)api;
  
  if (*object_address == NULL) {
    return;
  }
  
  if (SPVM_RUNTIME_API_isweak(api, *object_address)) {
    return;
  }
  
  SPVM_OBJECT* object = *object_address;
  
  // Decrelement reference count
  if (object->ref_count == 1) {
    // If reference count is 1, the object is freeed without weaken
    SPVM_RUNTIME_API_dec_ref_count(api, *object_address);
    *object_address = NULL;
    return;
  }
  else {
    object->ref_count--;
  }
  
  // Weaken is implemented tag pointer. If pointer first bit is 1, object is weaken.
  *object_address = (SPVM_OBJECT*)((intptr_t)*object_address | 1);
  
  // Create array of weaken_back_refs if need
  if (object->weaken_back_refs == NULL) {
    object->weaken_back_refs = SPVM_RUNTIME_API_new_object_array(api, SPVM_TYPE_C_CODE_VOID, 1);
    object->weaken_back_refs->ref_count++;
  }
  
  int32_t capacity = object->weaken_back_refs->length;
  int32_t length = object->weaken_back_refs_length;
  
  // Extend capacity
  assert(capacity >= length);
  if (length == capacity) {
    
    int32_t new_capacity = capacity * 2;
    SPVM_OBJECT* new_weaken_back_refs = SPVM_RUNTIME_API_new_object_array(api, SPVM_TYPE_C_CODE_VOID, new_capacity);
    new_weaken_back_refs->ref_count++;
    
    SPVM_OBJECT*** weaken_back_refs_elements = (SPVM_OBJECT***)((intptr_t)object->weaken_back_refs + sizeof(SPVM_OBJECT));
    SPVM_OBJECT*** new_weaken_back_refs_elements = (SPVM_OBJECT***)((intptr_t)new_weaken_back_refs + sizeof(SPVM_OBJECT));
    memcpy(new_weaken_back_refs_elements, weaken_back_refs_elements, length * sizeof(SPVM_OBJECT**));
    
    // Old object become NULL
    memset(weaken_back_refs_elements, 0, length * sizeof(SPVM_OBJECT**));
    
    // Free old weaken back references
    SPVM_RUNTIME_API_dec_ref_count(api, object->weaken_back_refs);
    
    object->weaken_back_refs = new_weaken_back_refs;
  }
  
  SPVM_OBJECT*** weaken_back_refs_elements = (SPVM_OBJECT***)((intptr_t)object->weaken_back_refs + sizeof(SPVM_OBJECT));
  weaken_back_refs_elements[length] = object_address;
  object->weaken_back_refs_length++;
}

_Bool SPVM_RUNTIME_API_isweak(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  _Bool isweak = (intptr_t)object & 1;
  
  return isweak;
}

void SPVM_RUNTIME_API_unweaken(SPVM_API* api, SPVM_OBJECT** object_address) {
  (void)api;
  
  if (*object_address == NULL) {
    return;
  }
  
  if (!SPVM_RUNTIME_API_isweak(api, *object_address)) {
    return;
  }
  
  // Unweaken
  *object_address = (SPVM_OBJECT*)((intptr_t)*object_address & ~(intptr_t)1);
  
  SPVM_OBJECT* object = *object_address;
  
  // Increment reference count
  object->ref_count++;

  int32_t length = object->weaken_back_refs_length;
  
  SPVM_OBJECT*** weaken_back_refs_elements = (SPVM_OBJECT***)((intptr_t)object->weaken_back_refs + sizeof(SPVM_OBJECT));
  
  {
    int32_t i;
    int32_t found_index = -1;
    for (i = 0; i < length; i++) {
      if (weaken_back_refs_elements[i] == object_address) {
        found_index = i;
        break;
      }
    }
    
    if (found_index == -1) {
      fprintf(stderr, "Not weakened address is specified(SPVM_RUNTIME_API_unweaken())");
      abort();
    }
    if (found_index < length - 1) {
      int32_t move_length = length - found_index - 1;
      memmove(&weaken_back_refs_elements[found_index], &weaken_back_refs_elements[found_index + 1], move_length * sizeof(SPVM_OBJECT**));
    }
  }
  object->weaken_back_refs_length--;
}

void SPVM_RUNTIME_API_set_exception(SPVM_API* api, SPVM_OBJECT* exception) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  if (runtime->exception != NULL) {
    SPVM_RUNTIME_API_dec_ref_count(api, (SPVM_OBJECT*)runtime->exception);
  }
  
  runtime->exception = exception;
  
  if (runtime->exception != NULL) {
    runtime->exception->ref_count++;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_get_exception(SPVM_API* api) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  return runtime->exception;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_byte_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int8_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  // Memory allocation error
  if (__builtin_expect(object == NULL, 0)) {
    // Error message
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Failed to allocate memory(new_byte_array())");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return NULL;
  }
  else {
    ((int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
    
    // Array
    object->dimension = 1;
    
    // Set type id
    int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
    object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_BYTE_ARRAY];
    
    // Set value type
    object->value_type = SPVM_OBJECT_C_VALUE_TYPE_BYTE;
    
    // Set array length
    object->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
    
    return object;
  }
}


SPVM_OBJECT* SPVM_RUNTIME_API_new_short_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int16_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  // Memory allocation error
  if (__builtin_expect(object == NULL, 0)) {
    // Error message
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Failed to allocate memory(new_short_array())");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return NULL;
  }
  else {
    
    ((int16_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
    
    // Array
    object->dimension = 1;
    
    // Set type id
    int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
    object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_SHORT_ARRAY];
    
    // Set value type
    object->value_type = SPVM_OBJECT_C_VALUE_TYPE_SHORT;

    // Set array length
    object->length = length;

    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));

    return object;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_int_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int32_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  // Memory allocation error
  if (__builtin_expect(object == NULL, 0)) {
    // Error message
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Failed to allocate memory(new_int_array())");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return NULL;
  }
  else {
    
    ((int32_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
    
    // Array
    object->dimension = 1;
    
    // Set type id
    int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
    object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_INT_ARRAY];
    
    // Set value type
    object->value_type = SPVM_OBJECT_C_VALUE_TYPE_INT;
    
    // Set array length
    object->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
    
    return object;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_long_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int64_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  // Memory allocation error
  if (__builtin_expect(object == NULL, 0)) {
    // Error message
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Failed to allocate memory(new_long_array())");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return NULL;
  }
  else {
  
    ((int64_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
    
    // Array
    object->dimension = 1;
    
    // Set type id
    int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
    object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_LONG_ARRAY];
    
    // Set value type
    object->value_type = SPVM_OBJECT_C_VALUE_TYPE_LONG;
    
    // Set array length
    object->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
    
    return object;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_float_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(float);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  // Memory allocation error
  if (__builtin_expect(object == NULL, 0)) {
    // Error message
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Failed to allocate memory(new_float_array())");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return NULL;
  }
  else {
    ((float*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
    
    // Array
    object->dimension = 1;
    
    // Set type id
    int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
    object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_FLOAT_ARRAY];
    
    // Set value type
    object->value_type = SPVM_OBJECT_C_VALUE_TYPE_FLOAT;
    
    // Set array length
    object->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
    
    return object;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_double_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(double);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  // Memory allocation error
  if (__builtin_expect(object == NULL, 0)) {
    // Error message
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Failed to allocate memory(new_double_array())");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return NULL;
  }
  else {
    ((double*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
    
    // Array
    object->dimension = 1;
    
    // Set type id
    int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
    object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_DOUBLE_ARRAY];
    
    // Set value type
    object->value_type = SPVM_OBJECT_C_VALUE_TYPE_DOUBLE;
    
    // Set array length
    object->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
    
    return object;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_array(SPVM_API* api, int32_t element_type_id, int32_t length) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(SPVM_OBJECT*);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  // Memory allocation error
  if (__builtin_expect(object == NULL, 0)) {
    // Error message
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Failed to allocate memory(new_double_array())");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return NULL;
  }
  else {
    ((SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
    
    // Initialize by null
    memset(object, 0, array_byte_size);
    
    // Type id
    SPVM_CONSTANT_POOL_TYPE* element_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[element_type_id];
    int32_t type_id = element_type->parent_type_id;
    object->type_id = type_id;
    
    // Set type
    object->dimension = 1;
    
    // Set value type
    object->value_type = SPVM_OBJECT_C_VALUE_TYPE_OBJECT;
    
    // Set array length
    object->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
    
    return object;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object(SPVM_API* api, int32_t type_id) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  int32_t* constant_pool = runtime->constant_pool;
  
  SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[type_id];
  int32_t package_id = constant_pool_type->package_id;
  SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&constant_pool[package_id];
  
  // Allocate memory
  int32_t length = constant_pool_package->fields_length;
  int64_t object_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)sizeof(SPVM_VALUE) * (int64_t)length;
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, object_byte_size);
  
  // Set type id
  object->type_id = type_id;
  
  assert(object_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
  
  return object;
}

int32_t SPVM_RUNTIME_API_get_array_length(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return object->length;
}

int8_t* SPVM_RUNTIME_API_get_byte_array_elements(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;

  return (int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT));
}

int16_t* SPVM_RUNTIME_API_get_short_array_elements(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return (int16_t*)((intptr_t)object + sizeof(SPVM_OBJECT));
}

int32_t* SPVM_RUNTIME_API_get_int_array_elements(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return (int32_t*)((intptr_t)object + sizeof(SPVM_OBJECT));
}

int64_t* SPVM_RUNTIME_API_get_long_array_elements(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return (int64_t*)((intptr_t)object + sizeof(SPVM_OBJECT));
}

float* SPVM_RUNTIME_API_get_float_array_elements(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return (float*)((intptr_t)object + sizeof(SPVM_OBJECT));
}

double* SPVM_RUNTIME_API_get_double_array_elements(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return (double*)((intptr_t)object + sizeof(SPVM_OBJECT));
}

SPVM_OBJECT* SPVM_RUNTIME_API_get_object_array_element(SPVM_API* api, SPVM_OBJECT* object, int32_t index) {
  (void)api;
  
  SPVM_OBJECT** objects = (SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT));

  assert(object);
  assert(index >= 0);
  assert(index <= object->length);
  
  SPVM_OBJECT* value = objects[index];
  
  return value;
}

void SPVM_RUNTIME_API_set_object_array_element(SPVM_API* api, SPVM_OBJECT* object, int32_t index, SPVM_OBJECT* value) {
  (void)api;
  
  SPVM_OBJECT** objects = (SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT));
  
  assert(object);
  assert(index >= 0);
  assert(index <= object->length);
  
  if(objects[index] != NULL) {
    api->dec_ref_count(api, objects[index]);
  }
  
  objects[index] = value;
  
  if(objects[index] != NULL) {
    api->inc_ref_count(api, objects[index]);
  }
}

void SPVM_RUNTIME_API_inc_dec_ref_count(SPVM_API* api, SPVM_OBJECT* object) {
  SPVM_RUNTIME_API_inc_ref_count(api, object);
  SPVM_RUNTIME_API_dec_ref_count(api, object);
}

void SPVM_RUNTIME_API_dec_ref_count(SPVM_API* api, SPVM_OBJECT* object) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  assert(object != NULL);
  assert(object->ref_count > 0);
  
  if (object->ref_count < 1) {
    fprintf(stderr, "Found invalid reference count object(SPVM_RUNTIME_API_dec_ref_count)");
    abort();
  }
  
  // Decrement reference count
  object->ref_count--;
  
  // If reference count is zero, free address.
  if (object->ref_count == 0) {
    // Array
    if (object->dimension > 0) {
      if (object->value_type == SPVM_OBJECT_C_VALUE_TYPE_OBJECT) {
        
        // Array length
        int32_t length = object->length;
        
        {
          int32_t i;
          for (i = 0; i < length; i++) {
            SPVM_OBJECT* object_element = *(SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(void*) * i);
            if (object_element != NULL) {
              SPVM_RUNTIME_API_dec_ref_count(api, object_element);
            }
          }
        }
      }
      SPVM_RUNTIME_ALLOCATOR_free_object(api, runtime->allocator, object);
    }
    // Object
    else {
      int32_t* constant_pool = runtime->constant_pool;
      SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[object->type_id];
      SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&constant_pool[constant_pool_type->package_id];
      
      int32_t object_fields_length = constant_pool_package->object_fields_length;
      
      {
        int32_t i;
        for (i = 0; i < object_fields_length; i++) {
          SPVM_OBJECT** object_field_address
            = (SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * i);
          if (*object_field_address != NULL) {
            // If object is weak, unweaken
            if (SPVM_RUNTIME_API_isweak(api, *object_field_address)) {
              SPVM_RUNTIME_API_unweaken(api, object_field_address);
            }
            else {
              SPVM_RUNTIME_API_dec_ref_count(api, *object_field_address);
            }
          }
        }
      }
      if (object->weaken_back_refs != NULL) {
        SPVM_RUNTIME_API_free_weaken_back_refs(api, object->weaken_back_refs, object->weaken_back_refs_length);
      }
      
      SPVM_RUNTIME_ALLOCATOR_free_object(api, runtime->allocator, object);
    }
  }
}

void SPVM_RUNTIME_API_inc_ref_count(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  if (object != NULL) {
    assert(object->ref_count >= 0);
    // Increment reference count
    object->ref_count++;
  }
}

int32_t SPVM_RUNTIME_API_get_ref_count(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return object->ref_count;
}

void SPVM_RUNTIME_API_call_void_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
  
  int32_t args_length = constant_pool_sub->args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_id);
}

int8_t SPVM_RUNTIME_API_call_byte_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
  
  int32_t args_length = constant_pool_sub->args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_id);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    int8_t value = runtime->call_stack[runtime->operand_stack_top].byte_value;
    runtime->operand_stack_top--;
    return value;
  }
}

int16_t SPVM_RUNTIME_API_call_short_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
  
  int32_t args_length = constant_pool_sub->args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_id);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    int16_t value = runtime->call_stack[runtime->operand_stack_top].short_value;
    runtime->operand_stack_top--;
    return value;
  }
}

int32_t SPVM_RUNTIME_API_call_int_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
  
  int32_t args_length = constant_pool_sub->args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_id);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    int32_t value = runtime->call_stack[runtime->operand_stack_top].int_value;
    runtime->operand_stack_top--;
    return value;
  }
}

int64_t SPVM_RUNTIME_API_call_long_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
  
  int32_t args_length = constant_pool_sub->args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_id);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    int64_t value = runtime->call_stack[runtime->operand_stack_top].long_value;
    runtime->operand_stack_top--;
    return value;
  }
}

float SPVM_RUNTIME_API_call_float_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
  
  int32_t args_length = constant_pool_sub->args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_id);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    float value = runtime->call_stack[runtime->operand_stack_top].float_value;
    runtime->operand_stack_top--;
    return value;
  }
}

double SPVM_RUNTIME_API_call_double_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
  
  int32_t args_length = constant_pool_sub->args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_id);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    double value = runtime->call_stack[runtime->operand_stack_top].double_value;
    runtime->operand_stack_top--;
    return value;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_call_object_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
  
  int32_t args_length = constant_pool_sub->args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_id);
  
  if (runtime->exception) {
    return NULL;
  }
  else {
    SPVM_OBJECT* value = runtime->call_stack[runtime->operand_stack_top].object_value;
    runtime->operand_stack_top--;
    return value;
  }
}

int32_t SPVM_RUNTIME_API_get_field_id(SPVM_API* api, SPVM_OBJECT* object, const char* name) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  int32_t* constant_pool = runtime->constant_pool;
  SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[object->type_id];
  SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&constant_pool[constant_pool_type->package_id];
  
  int32_t length = constant_pool_package->fields_length;
  
  int32_t fields_base = constant_pool_package->fields_base;
  
  int32_t field_index = 0;
  _Bool found = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      
      int32_t field_id = constant_pool[fields_base + i];
      SPVM_CONSTANT_POOL_FIELD_INFO* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD_INFO*)&constant_pool[field_id];
      
      int32_t field_name_id = constant_pool_field->name_id;
      
      char* match_name = (char*)&constant_pool[field_name_id + 1];
      
      if (strcmp(name, match_name) == 0) {
        found = 1;
        field_index = i + 1;
        break;
      }
    }
  }
  
  return field_index;
}

int32_t SPVM_RUNTIME_API_get_sub_id(SPVM_API* api, const char* name) {
  (void)api;
  
  if (name == NULL) {
    return 0;
  }
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_HASH* constant_pool_sub_symtable = runtime->constant_pool_sub_symtable;
  int32_t constant_pool_sub_id = (int32_t)SPVM_HASH_search(constant_pool_sub_symtable, name, strlen(name));
  
  return constant_pool_sub_id;
}

int32_t SPVM_RUNTIME_API_get_type_id(SPVM_API* api, const char* name) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_HASH* constant_pool_type_symtable = runtime->constant_pool_type_symtable;
  int32_t constant_pool_type_id = (int32_t)SPVM_HASH_search(constant_pool_type_symtable, name, strlen(name));

  return constant_pool_type_id;
}

int8_t SPVM_RUNTIME_API_get_byte_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  int8_t byte_value = fields[field_id - 1].byte_value;
  
  return byte_value;
}

int16_t SPVM_RUNTIME_API_get_short_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  int16_t short_value = fields[field_id - 1].short_value;
  
  return short_value;
}

int32_t SPVM_RUNTIME_API_get_int_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  int32_t int_value = fields[field_id - 1].int_value;
  
  return int_value;
}

int64_t SPVM_RUNTIME_API_get_long_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  int64_t long_value = fields[field_id - 1].long_value;
  
  return long_value;
}

float SPVM_RUNTIME_API_get_float_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  float float_value = fields[field_id - 1].float_value;
  
  return float_value;
}

double SPVM_RUNTIME_API_get_double_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  double double_value = fields[field_id - 1].double_value;
  
  return double_value;
}

SPVM_OBJECT* SPVM_RUNTIME_API_get_object_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  SPVM_OBJECT* object_value = fields[field_id - 1].object_value;
  
  return object_value;
}

void SPVM_RUNTIME_API_set_byte_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, int8_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_id - 1].byte_value = value;
}

void SPVM_RUNTIME_API_set_short_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, int16_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_id - 1].short_value = value;
}

void SPVM_RUNTIME_API_set_int_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, int32_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_id - 1].int_value = value;
}

void SPVM_RUNTIME_API_set_long_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, int64_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_id - 1].long_value = value;
}

void SPVM_RUNTIME_API_set_float_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, float value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_id - 1].float_value = value;
}

void SPVM_RUNTIME_API_set_double_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, double value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_id - 1].double_value = value;
}

void SPVM_RUNTIME_API_set_object_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, SPVM_OBJECT* value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  
  if(fields[field_id - 1].object_value != NULL) {
    // If object is weak, unweaken
    if (SPVM_RUNTIME_API_isweak(api, fields[field_id - 1].object_value)) {
      SPVM_RUNTIME_API_unweaken(api, (SPVM_OBJECT**)&fields[field_id - 1]);
    }
    api->dec_ref_count(api, fields[field_id - 1].object_value);
  }
  
  fields[field_id - 1].object_value = value;
  
  if(fields[field_id - 1].object_value != NULL) {
    api->inc_ref_count(api, fields[field_id - 1].object_value);
  }
}

int32_t SPVM_RUNTIME_API_get_array_value_size(SPVM_API* api, int32_t type) {
  (void)api;
  
  static const int32_t array_value_sizes[] = {
    sizeof(int8_t),
    sizeof(int16_t),
    sizeof(int32_t),
    sizeof(int64_t),
    sizeof(float),
    sizeof(double),
    sizeof(void*),
  };
  
  return array_value_sizes[type];
}

int64_t SPVM_RUNTIME_API_calcurate_object_byte_size(SPVM_API* api, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  int64_t byte_size;
  
  // Reference is string
  if (object->dimension > 0) {
    byte_size = sizeof(SPVM_OBJECT) + (object->length + 1) * SPVM_RUNTIME_API_get_array_value_size(api, object->value_type);
  }
  // Reference is object
  else {
    SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[object->type_id];
    
    SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&runtime->constant_pool[constant_pool_type->package_id];
    byte_size = sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * constant_pool_package->fields_length;
  }
  
  return byte_size;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_string(SPVM_API* api, const char* string) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  int32_t length = strlen(string);
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_byte_array(api, length);
  
  // Set type id
  int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
  object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_STRING];
  
  // Copy string
  memcpy((void*)((intptr_t)object + sizeof(SPVM_OBJECT)), string, length + 1);
  
  return object;
}

SPVM_VALUE* SPVM_RUNTIME_API_get_fields(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return (SPVM_VALUE*)((intptr_t)object + sizeof(SPVM_OBJECT));
}

int32_t SPVM_RUNTIME_API_get_fields_length(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[object->type_id];

  int32_t* constant_pool = runtime->constant_pool;
  SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&constant_pool[constant_pool_type->package_id];
  int32_t length = constant_pool_package->fields_length;
  
  return length;
}


int32_t SPVM_RUNTIME_API_dump_field_names(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[object->type_id];
  
  int32_t* constant_pool = runtime->constant_pool;
  SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&constant_pool[constant_pool_type->package_id];
  int32_t field_names_base = constant_pool_package->field_names_base;
  int32_t length = constant_pool_package->fields_length;
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      int32_t name_index = constant_pool[field_names_base + i];
      char* name = (char*)&constant_pool[name_index + 1];
      fprintf(stderr, "%s\n", name);
    }
  }
  
  return length;
}

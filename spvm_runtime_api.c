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
  
  SPVM_VALUE* weaken_back_refs_elements = (SPVM_VALUE*)((intptr_t)weaken_back_refs + sizeof(SPVM_OBJECT));
  
  {
    int32_t i;
    for (i = 0; i < weaken_back_refs_length; i++) {
      *(weaken_back_refs_elements[i].object_address_value) = NULL;
    }
  }
  
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
  if (object->uv.weaken_back_refs == NULL) {
    object->uv.weaken_back_refs = SPVM_RUNTIME_API_new_value_array(api, 1);
    object->uv.weaken_back_refs->ref_count++;
  }
  
  int32_t capacity = object->uv.weaken_back_refs->length;
  int32_t length = object->weaken_back_refs_length;
  
  // Extend capacity
  assert(capacity >= length);
  if (length == capacity) {
    
    int32_t new_capacity = capacity * 2;
    SPVM_OBJECT* new_weaken_back_refs = SPVM_RUNTIME_API_new_value_array(api, new_capacity);
    new_weaken_back_refs->ref_count++;
    
    SPVM_VALUE* weaken_back_refs_elements = (SPVM_VALUE*)((intptr_t)object->uv.weaken_back_refs + sizeof(SPVM_OBJECT));
    SPVM_VALUE* new_weaken_back_refs_elements = (SPVM_VALUE*)((intptr_t)new_weaken_back_refs + sizeof(SPVM_OBJECT));
    memcpy(new_weaken_back_refs_elements, weaken_back_refs_elements, length * sizeof(SPVM_VALUE));
    
    // Old object become NULL
    memset(weaken_back_refs_elements, 0, length * sizeof(SPVM_VALUE));
    
    // Free old weaken back references
    SPVM_RUNTIME_API_dec_ref_count(api, object->uv.weaken_back_refs);
    
    object->uv.weaken_back_refs = new_weaken_back_refs;
  }
  
  SPVM_VALUE* weaken_back_refs_elements = (SPVM_VALUE*)((intptr_t)object->uv.weaken_back_refs + sizeof(SPVM_OBJECT));
  weaken_back_refs_elements[length].object_address_value = object_address;
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
  
  SPVM_VALUE* weaken_back_refs_elements = (SPVM_VALUE*)((intptr_t)object->uv.weaken_back_refs + sizeof(SPVM_OBJECT));
  
  {
    int32_t i;
    int32_t found_index = -1;
    for (i = 0; i < length; i++) {
      if (weaken_back_refs_elements[i].object_address_value == object_address) {
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
      memmove(&weaken_back_refs_elements[found_index], &weaken_back_refs_elements[found_index + 1], move_length * sizeof(SPVM_VALUE));
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

// Use only internal
SPVM_OBJECT* SPVM_RUNTIME_API_new_value_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(SPVM_VALUE);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  // Set array length
  object->length = length;
  
  object->element_byte_size = sizeof(SPVM_VALUE);
  
  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_byte_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int8_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type id
  int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
  object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_BYTE_ARRAY];
  
  // Set array length
  object->length = length;
  
  object->element_byte_size = sizeof(int8_t);
  
  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
  
  return object;
}


SPVM_OBJECT* SPVM_RUNTIME_API_new_short_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int16_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((int16_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type id
  int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
  object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_SHORT_ARRAY];
  
  // Set array length
  object->length = length;

  object->element_byte_size = sizeof(int16_t);

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_int_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int32_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((int32_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type id
  int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
  object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_INT_ARRAY];
  
  // Set array length
  object->length = length;

  object->element_byte_size = sizeof(int32_t);
  
  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_long_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int64_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((int64_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type id
  int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
  object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_LONG_ARRAY];
  
  // Set array length
  object->length = length;

  object->element_byte_size = sizeof(int64_t);
  
  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_float_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(float);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((float*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type id
  int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
  object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_FLOAT_ARRAY];
  
  // Set array length
  object->length = length;

  object->element_byte_size = sizeof(float);
  
  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_double_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(double);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((double*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type id
  int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
  object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_DOUBLE_ARRAY];
  
  // Set array length
  object->length = length;

  object->element_byte_size = sizeof(double);
  
  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_array(SPVM_API* api, int32_t element_type_id, int32_t length) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(SPVM_VALUE);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Initialize by null
  memset(object, 0, array_byte_size);
  
  // Type id
  SPVM_CONSTANT_POOL_TYPE* element_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[element_type_id];
  int32_t type_id = element_type->parent_type_id;
  object->type_id = type_id;
  
  // Set array length
  object->length = length;
  
  // Objects length
  object->objects_length = length;

  object->element_byte_size = sizeof(SPVM_VALUE);
  
  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
  
  return object;
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
  int64_t object_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(SPVM_VALUE);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, object_byte_size);
  
  // Set type id
  object->type_id = type_id;
  
  object->length = length;
  
  // Objects length
  object->objects_length = constant_pool_package->object_fields_length;
  
  object->element_byte_size = sizeof(SPVM_VALUE);
  
  if (constant_pool_package->destructor_sub_id > 0) {
    object->has_destructor = 1;
  }
  
  assert(object_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
  
  return object;
}

int32_t SPVM_RUNTIME_API_get_array_length(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return object->length;
}

int32_t SPVM_RUNTIME_API_get_string_length(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return object->length;
}

// Use only internal
SPVM_VALUE* SPVM_RUNTIME_API_get_value_array_elements(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;

  return (SPVM_VALUE*)((intptr_t)object + sizeof(SPVM_OBJECT));
}

int8_t* SPVM_RUNTIME_API_get_byte_array_elements(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;

  return (int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT));
}

int8_t* SPVM_RUNTIME_API_get_string_bytes(SPVM_API* api, SPVM_OBJECT* object) {
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
  
  SPVM_VALUE* values = (SPVM_VALUE*)((intptr_t)object + sizeof(SPVM_OBJECT));

  assert(object);
  assert(index >= 0);
  assert(index <= object->length);
  
  SPVM_OBJECT* object_value = values[index].object_value;
  
  return object_value;
}

void SPVM_RUNTIME_API_set_object_array_element(SPVM_API* api, SPVM_OBJECT* object, int32_t index, SPVM_OBJECT* object_value) {
  (void)api;
  
  SPVM_VALUE* values = (SPVM_VALUE*)((intptr_t)object + sizeof(SPVM_OBJECT));
  
  assert(object);
  assert(index >= 0);
  assert(index <= object->length);
  
  if(values[index].object_value != NULL) {
    api->dec_ref_count(api, values[index].object_value);
  }
  
  values[index].object_value = object_value;
  
  if(values[index].object_value != NULL) {
    api->inc_ref_count(api, values[index].object_value);
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
  
  if (__builtin_expect(object->ref_count < 1, 0)) {
    fprintf(stderr, "Found invalid reference count object(SPVM_RUNTIME_API_dec_ref_count())");
    abort();
  }
  
  // Decrement reference count
  object->ref_count--;
  
  // If reference count is zero, free address.
  if (object->ref_count == 0) {

    if (__builtin_expect(object->has_destructor, 0)) {
      if (object->in_destroy) {
        return;
      }
      else {
        SPVM_RUNTIME* runtime = api->get_runtime(api);
        SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[object->type_id];
        SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&runtime->constant_pool[constant_pool_type->package_id];
        
        // Call destructor
        SPVM_VALUE args[1];
        args[0].object_value = object;
        object->in_destroy = 1;
        SPVM_RUNTIME_API_call_void_sub(api, constant_pool_package->destructor_sub_id, args);
        object->in_destroy = 0;
        
        if (object->ref_count < 0) {
          printf("object reference count become minus in DESTROY()\n");
          abort();
        }
      }
    }
    
    int32_t objects_length = object->objects_length;
    
    {
      int32_t i;
      for (i = 0; i < objects_length; i++) {
        SPVM_OBJECT** object_field_address = (SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * i);
        if (*object_field_address != NULL) {
          // If object is weak, unweaken
          if (__builtin_expect(SPVM_RUNTIME_API_isweak(api, *object_field_address), 0)) {
            SPVM_RUNTIME_API_unweaken(api, object_field_address);
          }
          else {
            SPVM_RUNTIME_API_dec_ref_count(api, *object_field_address);
          }
        }
      }
    }
    if (__builtin_expect(object->uv.weaken_back_refs != NULL, 0)) {
      SPVM_RUNTIME_API_free_weaken_back_refs(api, object->uv.weaken_back_refs, object->weaken_back_refs_length);
    }
    
    SPVM_RUNTIME_ALLOCATOR_free_object(api, runtime->allocator, object);
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
  (void)api;
  
  (void)SPVM_RUNTIME_call_sub(api, sub_id, args);
}

int8_t SPVM_RUNTIME_API_call_byte_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  (void)api;
  
  SPVM_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.byte_value;
}

int16_t SPVM_RUNTIME_API_call_short_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  (void)api;
  
  SPVM_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.short_value;
}

int32_t SPVM_RUNTIME_API_call_int_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  (void)api;
  
  SPVM_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.int_value;
}

int64_t SPVM_RUNTIME_API_call_long_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  (void)api;
  
  SPVM_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.long_value;
}

float SPVM_RUNTIME_API_call_float_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  (void)api;
  
  SPVM_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.float_value;
}

double SPVM_RUNTIME_API_call_double_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  (void)api;
  
  SPVM_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.double_value;
}

SPVM_OBJECT* SPVM_RUNTIME_API_call_object_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  (void)api;
  
  SPVM_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.object_value;
}

int32_t SPVM_RUNTIME_API_get_field_id(SPVM_API* api, SPVM_OBJECT* object, const char* name) {
  (void)api;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  // Constant pool
  int32_t* constant_pool = runtime->constant_pool;
  
  // Type
  SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[object->type_id];
  
  // Type name
  int32_t constant_pool_type_name_id = constant_pool_type->name_id;
  const char* type_name = (char*)&constant_pool[constant_pool_type_name_id + 1];
  
  // Constant pool field symbol table
  SPVM_HASH* field_id_symtable = runtime->field_id_symtable;
  SPVM_HASH* field_info_symtable = SPVM_HASH_search(field_id_symtable, type_name, strlen(type_name));
  
  int32_t field_id = (int32_t)(intptr_t)SPVM_HASH_search(field_info_symtable, name, strlen(name));
  
  return field_id;
}

int32_t SPVM_RUNTIME_API_get_sub_id(SPVM_API* api, const char* name) {
  (void)api;
  
  if (name == NULL) {
    return 0;
  }
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_HASH* sub_id_symtable = runtime->sub_id_symtable;
  int32_t constant_pool_sub_id = (int32_t)(intptr_t)SPVM_HASH_search(sub_id_symtable, name, strlen(name));
  
  return constant_pool_sub_id;
}

int32_t SPVM_RUNTIME_API_get_type_id(SPVM_API* api, const char* name) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_HASH* type_id_symtable = runtime->type_id_symtable;
  int32_t constant_pool_type_id = (int32_t)(intptr_t)SPVM_HASH_search(type_id_symtable, name, strlen(name));

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

int64_t SPVM_RUNTIME_API_calcurate_object_byte_size(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  int64_t byte_size = sizeof(SPVM_OBJECT) + (object->length + 1) * object->element_byte_size;
  
  return byte_size;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_string(SPVM_API* api, const char* string) {
  (void)api;
  
  int32_t length = strlen(string);
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_string_len(api, length);
  
  // Copy string
  memcpy((void*)((intptr_t)object + sizeof(SPVM_OBJECT)), string, length);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_string_len(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int8_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type id
  int32_t* type_code_to_id = (int32_t*)&runtime->constant_pool[runtime->type_code_to_id_base];
  object->type_id = type_code_to_id[SPVM_TYPE_C_CODE_STRING];
  
  // Set array length
  object->length = length;
  
  object->element_byte_size = sizeof(int8_t);
  
  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));
  
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

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "spvm_value.h"
#include "spvm_runtime_api.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_field.h"
#include "spvm_constant_pool_package.h"
#include "spvm_base_object.h"
#include "spvm_array.h"
#include "spvm_object.h"
#include "spvm_value.h"
#include "spvm_runtime.h"
#include "spvm_runtime_allocator.h"
#include "spvm_api.h"

void SPVM_RUNTIME_API_free_weaken_back_refs(SPVM_API* api, SPVM_ARRAY* weaken_back_refs, int32_t weaken_back_refs_length) {
  
  SPVM_BASE_OBJECT*** weaken_back_refs_elements = (SPVM_BASE_OBJECT***)((intptr_t)weaken_back_refs + sizeof(SPVM_ARRAY));
  
  {
    int32_t i;
    for (i = 0; i < weaken_back_refs_length; i++) {
      *weaken_back_refs_elements[i] = NULL;
    }
  }
  memset(weaken_back_refs_elements, 0, sizeof(SPVM_BASE_OBJECT**) * weaken_back_refs->length);
  
  SPVM_RUNTIME_API_dec_ref_count(api, (SPVM_BASE_OBJECT*)weaken_back_refs);
}

void SPVM_RUNTIME_API_weaken(SPVM_API* api, SPVM_BASE_OBJECT** base_object_address) {
  (void)api;
  
  if (SPVM_RUNTIME_API_isweak(api, *base_object_address)) {
    return;
  }
  
  SPVM_BASE_OBJECT* base_object = *base_object_address;
  
  // Decrelement reference count
  if (base_object->ref_count == 1) {
    // If reference count is 1, the object is freeed without weaken
    SPVM_RUNTIME_API_dec_ref_count(api, *base_object_address);
    *base_object_address = NULL;
  }
  else {
    base_object->ref_count--;
  }
  
  // Weaken is implemented tag pointer. If pointer first bit is 1, object is weaken.
  *base_object_address = (SPVM_BASE_OBJECT*)((intptr_t)*base_object_address | 1);
  
  // Create array of weaken_back_refs if need
  if (base_object->weaken_back_refs == NULL) {
    base_object->weaken_back_refs = SPVM_RUNTIME_API_new_object_array(api, 32);
    base_object->weaken_back_refs->ref_count++;
  }
  
  int32_t capacity = base_object->weaken_back_refs->length;
  int32_t length = base_object->weaken_back_refs_length;
  
  // Extend capacity
  assert(capacity >= length);
  if (length == capacity) {
    int32_t new_capacity = capacity * 2;
    SPVM_ARRAY* new_weaken_back_refs = SPVM_RUNTIME_API_new_object_array(api, new_capacity);
    new_weaken_back_refs->ref_count++;
    warn("BBBBBBBB %d", new_weaken_back_refs->ref_count);
    
    SPVM_BASE_OBJECT*** weaken_back_refs_elements = (SPVM_BASE_OBJECT***)((intptr_t)base_object->weaken_back_refs + sizeof(SPVM_ARRAY));
    SPVM_BASE_OBJECT*** new_weaken_back_refs_elements = (SPVM_BASE_OBJECT***)((intptr_t)new_weaken_back_refs + sizeof(SPVM_ARRAY));
    memcpy(new_weaken_back_refs_elements, weaken_back_refs_elements, length * sizeof(SPVM_BASE_OBJECT**));
    
    // Old object become NULL
    memset(weaken_back_refs_elements, 0, length * sizeof(SPVM_BASE_OBJECT**));
    
    // Free old weaken back references
    SPVM_RUNTIME_API_dec_ref_count(api, (SPVM_BASE_OBJECT*)base_object->weaken_back_refs);
    
    base_object->weaken_back_refs = new_weaken_back_refs;
  }
  
  SPVM_BASE_OBJECT*** weaken_back_refs_elements = (SPVM_BASE_OBJECT***)((intptr_t)base_object->weaken_back_refs + sizeof(SPVM_ARRAY));
  weaken_back_refs_elements[length] = base_object_address;
  base_object->weaken_back_refs_length++;
}

_Bool SPVM_RUNTIME_API_isweak(SPVM_API* api, SPVM_BASE_OBJECT* base_object) {
  (void)api;
  
  _Bool isweak = (intptr_t)base_object & 1;
  
  return isweak;
}

void SPVM_RUNTIME_API_unweaken(SPVM_API* api, SPVM_BASE_OBJECT** base_object_address) {
  (void)api;
  
  if (!SPVM_RUNTIME_API_isweak(api, *base_object_address)) {
    return;
  }
  
  // Unweaken
  *base_object_address = (SPVM_BASE_OBJECT*)((intptr_t)*base_object_address & ~(intptr_t)1);
  
  SPVM_BASE_OBJECT* base_object = *base_object_address;

  // Increment reference count
  base_object->ref_count++;

  int32_t length = base_object->weaken_back_refs_length;
  
  SPVM_BASE_OBJECT*** weaken_back_refs_elements = (SPVM_BASE_OBJECT***)((intptr_t)base_object->weaken_back_refs + sizeof(SPVM_ARRAY));
  
  {
    int32_t i;
    int32_t found_index = -1;
    for (i = 0; i < length; i++) {
      if (weaken_back_refs_elements[i] == base_object_address) {
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
      memmove(&weaken_back_refs_elements[found_index], &weaken_back_refs_elements[found_index + 1], move_length);
    }
  }
  base_object->weaken_back_refs_length--;
}

void SPVM_RUNTIME_API_set_exception(SPVM_API* api, SPVM_ARRAY* exception) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  if (runtime->exception != NULL) {
    SPVM_RUNTIME_API_dec_ref_count(api, (SPVM_BASE_OBJECT*)runtime->exception);
  }
  
  runtime->exception = exception;
  
  if (runtime->exception != NULL) {
    runtime->exception->ref_count++;
  }
}

SPVM_ARRAY* SPVM_RUNTIME_API_get_exception(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  return runtime->exception;
}

SPVM_ARRAY* SPVM_RUNTIME_API_new_byte_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_ARRAY) + (int64_t)(length + 1) * (int64_t)sizeof(int8_t);
  SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((int8_t*)((intptr_t)array + sizeof(SPVM_ARRAY)))[length] = 0;
  
  // Set type
  array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  array->value_type = SPVM_ARRAY_C_VALUE_TYPE_BYTE;
  
  // Set reference count
  array->ref_count = 0;
  
  // Set array length
  array->length = length;

  // Weaken back references
  array->weaken_back_refs = NULL;
  
  // Weaken back references count
  array->weaken_back_refs_length = 0;
  
  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));
  
  return array;
}


SPVM_ARRAY* SPVM_RUNTIME_API_new_short_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_ARRAY) + (int64_t)(length + 1) * (int64_t)sizeof(int16_t);
  SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((int16_t*)((intptr_t)array + sizeof(SPVM_ARRAY)))[length] = 0;
  
  // Set type
  array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  array->value_type = SPVM_ARRAY_C_VALUE_TYPE_SHORT;
  
  // Set reference count
  array->ref_count = 0;
  
  // Set array length
  array->length = length;

  // Weaken back references
  array->weaken_back_refs = NULL;

  // Weaken back references count
  array->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));

  return array;
}

SPVM_ARRAY* SPVM_RUNTIME_API_new_int_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_ARRAY) + (int64_t)(length + 1) * (int64_t)sizeof(int32_t);
  SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((int32_t*)((intptr_t)array + sizeof(SPVM_ARRAY)))[length] = 0;
  
  // Set type
  array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  array->value_type = SPVM_ARRAY_C_VALUE_TYPE_INT;
  
  // Set reference count
  array->ref_count = 0;
  
  // Set array length
  array->length = length;

  // Weaken back references
  array->weaken_back_refs = NULL;

  // Weaken back references count
  array->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));

  return array;
}

SPVM_ARRAY* SPVM_RUNTIME_API_new_long_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_ARRAY) + (int64_t)(length + 1) * (int64_t)sizeof(int64_t);
  SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((int64_t*)((intptr_t)array + sizeof(SPVM_ARRAY)))[length] = 0;
  
  // Set type
  array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  array->value_type = SPVM_ARRAY_C_VALUE_TYPE_LONG;
  
  // Set reference count
  array->ref_count = 0;
  
  // Set array length
  array->length = length;

  // Weaken back references
  array->weaken_back_refs = NULL;

  // Weaken back references count
  array->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));

  return array;
}

SPVM_ARRAY* SPVM_RUNTIME_API_new_float_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_ARRAY) + (int64_t)(length + 1) * (int64_t)sizeof(float);
  SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((float*)((intptr_t)array + sizeof(SPVM_ARRAY)))[length] = 0;
  
  // Set type
  array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  array->value_type = SPVM_ARRAY_C_VALUE_TYPE_FLOAT;
  
  // Set reference count
  array->ref_count = 0;
  
  // Set array length
  array->length = length;

  // Weaken back references
  array->weaken_back_refs = NULL;

  // Weaken back references count
  array->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));

  return array;
}

SPVM_ARRAY* SPVM_RUNTIME_API_new_double_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_ARRAY) + (int64_t)(length + 1) * (int64_t)sizeof(double);
  SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((double*)((intptr_t)array + sizeof(SPVM_ARRAY)))[length] = 0;
  
  // Set type
  array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  array->value_type = SPVM_ARRAY_C_VALUE_TYPE_DOUBLE;
  
  // Set reference count
  array->ref_count = 0;
  
  // Set array length
  array->length = length;
  
  // Weaken back references
  array->weaken_back_refs = NULL;

  // Weaken back references count
  array->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));

  return array;
}

SPVM_ARRAY* SPVM_RUNTIME_API_new_object_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_ARRAY) + (int64_t)(length + 1) * (int64_t)sizeof(SPVM_BASE_OBJECT*);
  SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((SPVM_BASE_OBJECT**)((intptr_t)array + sizeof(SPVM_ARRAY)))[length] = 0;
  
  // Initialize by null
  memset(array, 0, array_byte_size);
  
  // Set type
  array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  array->value_type = SPVM_ARRAY_C_VALUE_TYPE_OBJECT;
  
  // Set reference count
  array->ref_count = 0;
  
  // Set array length
  array->length = length;

  // Weaken back references
  array->weaken_back_refs = NULL;

  // Weaken back references count
  array->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));

  return array;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object(SPVM_API* api, int32_t package_constant_pool_index) {
  
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  int32_t* constant_pool = runtime->constant_pool;
  
  SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
  memcpy(&constant_pool_package, &constant_pool[package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
  
  // Allocate memory
  int32_t length = constant_pool_package.fields_length;
  int64_t object_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)sizeof(SPVM_VALUE) * (int64_t)length;
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, object_byte_size);
  
  // Initialize fields by 0
  memset(object, 0, object_byte_size);
  
  // Set type
  object->type = SPVM_BASE_OBJECT_C_TYPE_OBJECT;
  
  // Set reference count
  object->ref_count = 0;
  
  // Package constant pool index
  object->package_constant_pool_index = package_constant_pool_index;

  // Weaken back references
  object->weaken_back_refs = NULL;

  // Weaken back references count
  object->weaken_back_refs_length = 0;

  assert(object_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)object));

  return object;
}

int32_t SPVM_RUNTIME_API_get_array_length(SPVM_API* api, SPVM_ARRAY* array) {
  (void)api;
  
  return array->length;
}

int8_t* SPVM_RUNTIME_API_get_byte_array_elements(SPVM_API* api, SPVM_ARRAY* array) {
  (void)api;

  return (int8_t*)((intptr_t)array + sizeof(SPVM_ARRAY));
}

int16_t* SPVM_RUNTIME_API_get_short_array_elements(SPVM_API* api, SPVM_ARRAY* array) {
  (void)api;
  
  return (int16_t*)((intptr_t)array + sizeof(SPVM_ARRAY));
}

int32_t* SPVM_RUNTIME_API_get_int_array_elements(SPVM_API* api, SPVM_ARRAY* array) {
  (void)api;
  
  return (int32_t*)((intptr_t)array + sizeof(SPVM_ARRAY));
}

int64_t* SPVM_RUNTIME_API_get_long_array_elements(SPVM_API* api, SPVM_ARRAY* array) {
  (void)api;
  
  return (int64_t*)((intptr_t)array + sizeof(SPVM_ARRAY));
}

float* SPVM_RUNTIME_API_get_float_array_elements(SPVM_API* api, SPVM_ARRAY* array) {
  (void)api;
  
  return (float*)((intptr_t)array + sizeof(SPVM_ARRAY));
}

double* SPVM_RUNTIME_API_get_double_array_elements(SPVM_API* api, SPVM_ARRAY* array) {
  (void)api;
  
  return (double*)((intptr_t)array + sizeof(SPVM_ARRAY));
}

SPVM_BASE_OBJECT* SPVM_RUNTIME_API_get_object_array_element(SPVM_API* api, SPVM_ARRAY* array, int32_t index) {
  (void)api;
  
  SPVM_BASE_OBJECT** objects = (SPVM_BASE_OBJECT**)((intptr_t)array + sizeof(SPVM_ARRAY));

  assert(array);
  assert(index >= 0);
  assert(index <= array->length);
  
  SPVM_BASE_OBJECT* value = objects[index];
  
  return value;
}

void SPVM_RUNTIME_API_set_object_array_element(SPVM_API* api, SPVM_ARRAY* array, int32_t index, SPVM_BASE_OBJECT* value) {
  (void)api;
  
  SPVM_BASE_OBJECT** objects = (SPVM_BASE_OBJECT**)((intptr_t)array + sizeof(SPVM_ARRAY));
  
  assert(array);
  assert(index >= 0);
  assert(index <= array->length);
  
  if(objects[index] != NULL) {
    api->dec_ref_count(api, objects[index]);
  }
  
  objects[index] = value;
  
  if(objects[index] != NULL) {
    api->inc_ref_count(api, objects[index]);
  }
}

void SPVM_RUNTIME_API_inc_dec_ref_count(SPVM_API* api, SPVM_BASE_OBJECT* base_object) {
  SPVM_RUNTIME_API_inc_ref_count(api, base_object);
  SPVM_RUNTIME_API_dec_ref_count(api, base_object);
}

void SPVM_RUNTIME_API_dec_ref_count(SPVM_API* api, SPVM_BASE_OBJECT* base_object) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  assert(base_object != NULL);
  assert(base_object->ref_count > 0);
  
  if (base_object->ref_count < 1) {
    fprintf(stderr, "Found invalid reference count object(SPVM_RUNTIME_API_dec_ref_count)");
    abort();
  }
  
  // Decrement reference count
  base_object->ref_count--;
  
  // If reference count is zero, free address.
  if (base_object->ref_count == 0) {
    
    if (base_object->type == SPVM_BASE_OBJECT_C_TYPE_ARRAY) {
      SPVM_ARRAY* array = (SPVM_ARRAY*)base_object;
      if (array->value_type == SPVM_ARRAY_C_VALUE_TYPE_OBJECT) {
        
        // Array length
        int32_t length = array->length;
        
        {
          int32_t i;
          for (i = 0; i < length; i++) {
            SPVM_BASE_OBJECT* base_object_element = *(SPVM_BASE_OBJECT**)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(void*) * i);
            if (base_object_element != NULL) {
              SPVM_RUNTIME_API_dec_ref_count(api, base_object_element);
            }
          }
        }
      }
      SPVM_RUNTIME_ALLOCATOR_free_base_object(api, runtime->allocator, base_object);
    }
    // Reference is object
    else if (base_object->type == SPVM_BASE_OBJECT_C_TYPE_OBJECT) {
      int32_t* constant_pool = runtime->constant_pool;
      
      SPVM_OBJECT* object = (SPVM_OBJECT*)base_object;
      
      int32_t package_constant_pool_index = object->package_constant_pool_index;
      SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
      
      memcpy(&constant_pool_package, &constant_pool[package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
      
      int32_t object_fields_length = constant_pool_package.object_fields_length;
      
      {
        int32_t i;
        for (i = 0; i < object_fields_length; i++) {
          SPVM_BASE_OBJECT** base_object_field_address
            = (SPVM_BASE_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_BASE_OBJECT*) * i);
          if (*base_object_field_address != NULL) {
            // If object is weak, unweaken
            if (SPVM_RUNTIME_API_isweak(api, *base_object_field_address)) {
              SPVM_RUNTIME_API_unweaken(api, base_object_field_address);
              (*base_object_field_address)->ref_count--;
            }
            else {
              SPVM_RUNTIME_API_dec_ref_count(api, *base_object_field_address);
            }
          }
        }
      }
      if (object->weaken_back_refs != NULL) {
        SPVM_RUNTIME_API_free_weaken_back_refs(api, object->weaken_back_refs, object->weaken_back_refs_length);
      }
      
      SPVM_RUNTIME_ALLOCATOR_free_base_object(api, runtime->allocator, (SPVM_BASE_OBJECT*)object);
    }
  }
}

void SPVM_RUNTIME_API_inc_ref_count(SPVM_API* api, SPVM_BASE_OBJECT* base_object) {
  (void)api;
  
  if (base_object != NULL) {
    assert(base_object->ref_count >= 0);
    // Increment reference count
    base_object->ref_count++;
  }
}

int32_t SPVM_RUNTIME_API_get_ref_count(SPVM_API* api, SPVM_BASE_OBJECT* base_object) {
  (void)api;
  
  return base_object->ref_count;
}

void SPVM_RUNTIME_API_call_void_sub(SPVM_API* api, int32_t sub_constant_pool_index, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  SPVM_CONSTANT_POOL_SUB constant_pool_sub;
  memcpy(&constant_pool_sub, &runtime->constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
  
  int32_t args_length = constant_pool_sub.args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_constant_pool_index);
}

int8_t SPVM_RUNTIME_API_call_byte_sub(SPVM_API* api, int32_t sub_constant_pool_index, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  SPVM_CONSTANT_POOL_SUB constant_pool_sub;
  memcpy(&constant_pool_sub, &runtime->constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
  
  int32_t args_length = constant_pool_sub.args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_constant_pool_index);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    int8_t value = runtime->call_stack[runtime->operand_stack_top].byte_value;
    runtime->operand_stack_top--;
    return value;
  }
}

int16_t SPVM_RUNTIME_API_call_short_sub(SPVM_API* api, int32_t sub_constant_pool_index, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  SPVM_CONSTANT_POOL_SUB constant_pool_sub;
  memcpy(&constant_pool_sub, &runtime->constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
  
  int32_t args_length = constant_pool_sub.args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_constant_pool_index);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    int16_t value = runtime->call_stack[runtime->operand_stack_top].short_value;
    runtime->operand_stack_top--;
    return value;
  }
}

int32_t SPVM_RUNTIME_API_call_int_sub(SPVM_API* api, int32_t sub_constant_pool_index, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  SPVM_CONSTANT_POOL_SUB constant_pool_sub;
  memcpy(&constant_pool_sub, &runtime->constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
  
  int32_t args_length = constant_pool_sub.args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_constant_pool_index);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    int32_t value = runtime->call_stack[runtime->operand_stack_top].int_value;
    runtime->operand_stack_top--;
    return value;
  }
}

int64_t SPVM_RUNTIME_API_call_long_sub(SPVM_API* api, int32_t sub_constant_pool_index, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  SPVM_CONSTANT_POOL_SUB constant_pool_sub;
  memcpy(&constant_pool_sub, &runtime->constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
  
  int32_t args_length = constant_pool_sub.args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_constant_pool_index);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    int64_t value = runtime->call_stack[runtime->operand_stack_top].long_value;
    runtime->operand_stack_top--;
    return value;
  }
}

float SPVM_RUNTIME_API_call_float_sub(SPVM_API* api, int32_t sub_constant_pool_index, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  SPVM_CONSTANT_POOL_SUB constant_pool_sub;
  memcpy(&constant_pool_sub, &runtime->constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
  
  int32_t args_length = constant_pool_sub.args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_constant_pool_index);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    float value = runtime->call_stack[runtime->operand_stack_top].float_value;
    runtime->operand_stack_top--;
    return value;
  }
}

double SPVM_RUNTIME_API_call_double_sub(SPVM_API* api, int32_t sub_constant_pool_index, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  SPVM_CONSTANT_POOL_SUB constant_pool_sub;
  memcpy(&constant_pool_sub, &runtime->constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
  
  int32_t args_length = constant_pool_sub.args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_constant_pool_index);
  
  if (runtime->exception) {
    return 0;
  }
  else {
    double value = runtime->call_stack[runtime->operand_stack_top].double_value;
    runtime->operand_stack_top--;
    return value;
  }
}

SPVM_BASE_OBJECT* SPVM_RUNTIME_API_call_object_sub(SPVM_API* api, int32_t sub_constant_pool_index, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  SPVM_CONSTANT_POOL_SUB constant_pool_sub;
  memcpy(&constant_pool_sub, &runtime->constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
  
  int32_t args_length = constant_pool_sub.args_length;
  
  {
    int32_t i;
    for (i = 0; i < args_length; i++) {
      runtime->operand_stack_top++;
      runtime->call_stack[runtime->operand_stack_top] = args[i];
    }
  }
  
  SPVM_RUNTIME_call_sub(api, sub_constant_pool_index);
  
  if (runtime->exception) {
    return NULL;
  }
  else {
    SPVM_BASE_OBJECT* value = runtime->call_stack[runtime->operand_stack_top].object_value;
    runtime->operand_stack_top--;
    return value;
  }
}

int32_t SPVM_RUNTIME_API_get_field_id(SPVM_API* api, SPVM_OBJECT* object, const char* name) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t* constant_pool = runtime->constant_pool;
  SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
  memcpy(&constant_pool_package, &constant_pool[object->package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
  
  int32_t length = constant_pool_package.fields_length;
  
  
  int32_t field_indexes_constant_pool_index = constant_pool_package.field_indexes_constant_pool_index;
  
  int32_t field_index = SPVM_API_ERROR_NO_ID;
  _Bool found = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      
      int32_t field_constant_pool_index = constant_pool[field_indexes_constant_pool_index + i];
      SPVM_CONSTANT_POOL_FIELD constant_pool_field;
      memcpy(&constant_pool_field, &constant_pool[field_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_FIELD));
      
      int32_t field_name_constant_pool_index = constant_pool_field.name_constant_pool_index;
      
      char* match_name = (char*)&constant_pool[field_name_constant_pool_index + 1];
      
      if (strcmp(name, match_name) == 0) {
        found = 1;
        field_index = i;
        break;
      }
    }
  }
  
  return field_index;
}

int32_t SPVM_RUNTIME_API_get_sub_id(SPVM_API* api, const char* name) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t* constant_pool = runtime->constant_pool;
  int32_t length = runtime->subs_length;
  int32_t sub_indexes_constant_pool_index = runtime-> sub_indexes_constant_pool_index;
  
  int32_t found_sub_constant_pool_index = SPVM_API_ERROR_NO_ID;
  _Bool found = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      int32_t sub_constant_pool_index = constant_pool[sub_indexes_constant_pool_index + i];
      SPVM_CONSTANT_POOL_SUB constant_pool_sub;
      memcpy(&constant_pool_sub, &constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
      
      int32_t sub_name_constant_pool_index = constant_pool_sub.abs_name_constant_pool_index;
      
      char* match_name = (char*)&constant_pool[sub_name_constant_pool_index + 1];
      if (strcmp(name, match_name) == 0) {
        found = 1;
        found_sub_constant_pool_index = sub_constant_pool_index;
        break;
      }
    }
  }
  
  if (!found) {
    fprintf(stderr, "Can't find subroutine name \"%s\"\n", name);
    abort();
  }
  
  return found_sub_constant_pool_index;
}

int32_t SPVM_RUNTIME_API_get_package_id(SPVM_API* api, const char* name) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t* constant_pool = runtime->constant_pool;
  int32_t length = runtime->packages_length;
  int32_t package_indexes_constant_pool_index = runtime-> package_indexes_constant_pool_index;
  
  int32_t found_package_constant_pool_index = SPVM_API_ERROR_NO_ID;
  _Bool found = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      int32_t package_constant_pool_index = constant_pool[package_indexes_constant_pool_index + i];
      SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
      memcpy(&constant_pool_package, &constant_pool[package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
      
      int32_t package_name_constant_pool_index = constant_pool_package.name_constant_pool_index;
      
      char* match_name = (char*)&constant_pool[package_name_constant_pool_index + 1];
      if (strcmp(name, match_name) == 0) {
        found = 1;
        found_package_constant_pool_index = package_constant_pool_index;
        break;
      }
    }
  }
  
  if (!found) {
    fprintf(stderr, "Can't find packageroutine name \"%s\"\n", name);
    abort();
  }
  
  return found_package_constant_pool_index;
}


int8_t SPVM_RUNTIME_API_get_byte_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  int8_t byte_value = fields[field_index].byte_value;
  
  return byte_value;
}

int16_t SPVM_RUNTIME_API_get_short_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  int16_t short_value = fields[field_index].short_value;
  
  return short_value;
}

int32_t SPVM_RUNTIME_API_get_int_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  int32_t int_value = fields[field_index].int_value;
  
  return int_value;
}

int64_t SPVM_RUNTIME_API_get_long_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  int64_t long_value = fields[field_index].long_value;
  
  return long_value;
}

float SPVM_RUNTIME_API_get_float_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  float float_value = fields[field_index].float_value;
  
  return float_value;
}

double SPVM_RUNTIME_API_get_double_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  double double_value = fields[field_index].double_value;
  
  return double_value;
}

SPVM_BASE_OBJECT* SPVM_RUNTIME_API_get_object_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  SPVM_BASE_OBJECT* object_value = fields[field_index].object_value;
  
  return object_value;
}

void SPVM_RUNTIME_API_set_byte_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, int8_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_index].byte_value = value;
}

void SPVM_RUNTIME_API_set_short_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, int16_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_index].short_value = value;
}

void SPVM_RUNTIME_API_set_int_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, int32_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_index].int_value = value;
}

void SPVM_RUNTIME_API_set_long_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, int64_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_index].long_value = value;
}

void SPVM_RUNTIME_API_set_float_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, float value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_index].float_value = value;
}

void SPVM_RUNTIME_API_set_double_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, double value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  fields[field_index].double_value = value;
}

void SPVM_RUNTIME_API_set_object_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, SPVM_BASE_OBJECT* value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  
  if(fields[field_index].object_value != NULL) {
    api->dec_ref_count(api, fields[field_index].object_value);
  }
  
  fields[field_index].object_value = value;
  
  if(fields[field_index].object_value != NULL) {
    api->inc_ref_count(api, fields[field_index].object_value);
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

int64_t SPVM_RUNTIME_API_calcurate_base_object_byte_size(SPVM_API* api, SPVM_BASE_OBJECT* base_object) {
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int64_t byte_size;
  
  // Reference is string
  if (base_object->type == SPVM_BASE_OBJECT_C_TYPE_ARRAY) {
    SPVM_ARRAY* array = (SPVM_ARRAY*)base_object;
    byte_size = sizeof(SPVM_ARRAY) + (array->length + 1) * SPVM_RUNTIME_API_get_array_value_size(api, array->value_type);
  }
  // Reference is object
  else if (base_object->type == SPVM_BASE_OBJECT_C_TYPE_OBJECT) {
    SPVM_OBJECT* object = (SPVM_OBJECT*)base_object;
    SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
    memcpy(&constant_pool_package, &runtime->constant_pool[object->package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
    byte_size = sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * constant_pool_package.fields_length;
  }
  else {
    assert(0);
  }
  
  return byte_size;
}

SPVM_ARRAY* SPVM_RUNTIME_API_new_byte_array_from_pv(SPVM_API* api, const char* pv) {
  (void)api;
  
  int32_t length = strlen(pv);
  SPVM_ARRAY* array = SPVM_RUNTIME_API_new_byte_array(api, length);
  
  // Copy string
  memcpy((void*)((intptr_t)array + sizeof(SPVM_ARRAY)), pv, length + 1);
  
  return array;
}

SPVM_VALUE* SPVM_RUNTIME_API_get_fields(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return (SPVM_VALUE*)((intptr_t)object + sizeof(SPVM_OBJECT));
}

int32_t SPVM_RUNTIME_API_get_fields_length(SPVM_API* api, SPVM_OBJECT* object) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t* constant_pool = runtime->constant_pool;
  SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
  memcpy(&constant_pool_package, &constant_pool[object->package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
  int32_t length = constant_pool_package.fields_length;
  
  return length;
}


int32_t SPVM_RUNTIME_API_dump_field_names(SPVM_API* api, SPVM_OBJECT* object) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t* constant_pool = runtime->constant_pool;
  SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
  memcpy(&constant_pool_package, &constant_pool[object->package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
  int32_t field_name_indexes_constant_pool_index = constant_pool_package.field_name_indexes_constant_pool_index;
  int32_t length = constant_pool_package.fields_length;
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      int32_t name_index = constant_pool[field_name_indexes_constant_pool_index + i];
      char* name = (char*)&constant_pool[name_index + 1];
      fprintf(stderr, "%s\n", name);
    }
  }
  
  return length;
}

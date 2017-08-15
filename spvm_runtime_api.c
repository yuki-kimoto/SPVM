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
#include "spvm_object.h"
#include "spvm_value.h"
#include "spvm_runtime.h"
#include "spvm_runtime_allocator.h"
#include "spvm_api.h"
#include "spvm_global.h"

int32_t SPVM_RUNTIME_API_get_objects_count(SPVM_API* api) {
  (void)api;
  return SPVM_GLOBAL_RUNTIME->objects_count;
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
    object->weaken_back_refs = SPVM_RUNTIME_API_new_object_array(api, 1);
    object->weaken_back_refs->ref_count++;
  }
  
  int32_t capacity = object->weaken_back_refs->length;
  int32_t length = object->weaken_back_refs_length;
  
  // Extend capacity
  assert(capacity >= length);
  if (length == capacity) {
    
    int32_t new_capacity = capacity * 2;
    SPVM_OBJECT* new_weaken_back_refs = SPVM_RUNTIME_API_new_object_array(api, new_capacity);
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
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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
  
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
  return runtime->exception;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_byte_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int8_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type
  object->type = SPVM_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  object->value_type = SPVM_OBJECT_C_VALUE_TYPE_BYTE;
  
  // Set reference count
  object->ref_count = 0;
  
  // Set array length
  object->length = length;

  // Weaken back references
  object->weaken_back_refs = NULL;
  
  // Weaken back references count
  object->weaken_back_refs_length = 0;
  
  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, (SPVM_OBJECT*)object));
  
  return object;
}


SPVM_OBJECT* SPVM_RUNTIME_API_new_short_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int16_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((int16_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type
  object->type = SPVM_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  object->value_type = SPVM_OBJECT_C_VALUE_TYPE_SHORT;
  
  // Set reference count
  object->ref_count = 0;
  
  // Set array length
  object->length = length;

  // Weaken back references
  object->weaken_back_refs = NULL;

  // Weaken back references count
  object->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_int_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int32_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((int32_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type
  object->type = SPVM_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  object->value_type = SPVM_OBJECT_C_VALUE_TYPE_INT;
  
  // Set reference count
  object->ref_count = 0;
  
  // Set array length
  object->length = length;

  // Weaken back references
  object->weaken_back_refs = NULL;

  // Weaken back references count
  object->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_long_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(int64_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((int64_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type
  object->type = SPVM_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  object->value_type = SPVM_OBJECT_C_VALUE_TYPE_LONG;
  
  // Set reference count
  object->ref_count = 0;
  
  // Set array length
  object->length = length;

  // Weaken back references
  object->weaken_back_refs = NULL;

  // Weaken back references count
  object->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_float_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(float);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((float*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type
  object->type = SPVM_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  object->value_type = SPVM_OBJECT_C_VALUE_TYPE_FLOAT;
  
  // Set reference count
  object->ref_count = 0;
  
  // Set array length
  object->length = length;

  // Weaken back references
  object->weaken_back_refs = NULL;

  // Weaken back references count
  object->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_double_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(double);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((double*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Set type
  object->type = SPVM_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  object->value_type = SPVM_OBJECT_C_VALUE_TYPE_DOUBLE;
  
  // Set reference count
  object->ref_count = 0;
  
  // Set array length
  object->length = length;
  
  // Weaken back references
  object->weaken_back_refs = NULL;

  // Weaken back references count
  object->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  // alloc length + 1. Last value is 0
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(length + 1) * (int64_t)sizeof(SPVM_OBJECT*);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  ((SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  // Initialize by null
  memset(object, 0, array_byte_size);
  
  // Set type
  object->type = SPVM_OBJECT_C_TYPE_ARRAY;
  
  // Set value type
  object->value_type = SPVM_OBJECT_C_VALUE_TYPE_OBJECT;
  
  // Set reference count
  object->ref_count = 0;
  
  // Set array length
  object->length = length;

  // Weaken back references
  object->weaken_back_refs = NULL;

  // Weaken back references count
  object->weaken_back_refs_length = 0;

  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_object_byte_size(api, object));

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object(SPVM_API* api, int32_t package_constant_pool_index) {
  
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
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
  object->type = SPVM_OBJECT_C_TYPE_OBJECT;
  
  // Set reference count
  object->ref_count = 0;
  
  // Package constant pool index
  object->package_constant_pool_index = package_constant_pool_index;

  // Weaken back references
  object->weaken_back_refs = NULL;

  // Weaken back references count
  object->weaken_back_refs_length = 0;
  
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
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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
    
    if (object->type == SPVM_OBJECT_C_TYPE_ARRAY) {
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
    // Reference is object
    else if (object->type == SPVM_OBJECT_C_TYPE_OBJECT) {
      int32_t* constant_pool = runtime->constant_pool;
      int32_t package_constant_pool_index = object->package_constant_pool_index;
      SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
      
      memcpy(&constant_pool_package, &constant_pool[package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
      
      int32_t object_fields_length = constant_pool_package.object_fields_length;
      
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
      
      SPVM_RUNTIME_ALLOCATOR_free_object(api, runtime->allocator, (SPVM_OBJECT*)object);
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

void SPVM_RUNTIME_API_call_void_sub(SPVM_API* api, int32_t sub_constant_pool_index, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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

SPVM_OBJECT* SPVM_RUNTIME_API_call_object_sub(SPVM_API* api, int32_t sub_constant_pool_index, SPVM_VALUE* args) {
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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
    SPVM_OBJECT* value = runtime->call_stack[runtime->operand_stack_top].object_value;
    runtime->operand_stack_top--;
    return value;
  }
}

int32_t SPVM_RUNTIME_API_get_field_id(SPVM_API* api, SPVM_OBJECT* object, const char* name) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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

SPVM_OBJECT* SPVM_RUNTIME_API_get_object_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, object);
  SPVM_OBJECT* object_value = fields[field_index].object_value;
  
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

void SPVM_RUNTIME_API_set_object_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, SPVM_OBJECT* value) {
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

int64_t SPVM_RUNTIME_API_calcurate_object_byte_size(SPVM_API* api, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
  int64_t byte_size;
  
  // Reference is string
  if (object->type == SPVM_OBJECT_C_TYPE_ARRAY) {
    byte_size = sizeof(SPVM_OBJECT) + (object->length + 1) * SPVM_RUNTIME_API_get_array_value_size(api, object->value_type);
  }
  // Reference is object
  else if (object->type == SPVM_OBJECT_C_TYPE_OBJECT) {
    SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
    memcpy(&constant_pool_package, &runtime->constant_pool[object->package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
    byte_size = sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * constant_pool_package.fields_length;
  }
  else {
    assert(0);
  }
  
  return byte_size;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_byte_array_from_pv(SPVM_API* api, const char* pv) {
  (void)api;
  
  int32_t length = strlen(pv);
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_byte_array(api, length);
  
  // Copy string
  memcpy((void*)((intptr_t)object + sizeof(SPVM_OBJECT)), pv, length + 1);
  
  return object;
}

SPVM_VALUE* SPVM_RUNTIME_API_get_fields(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return (SPVM_VALUE*)((intptr_t)object + sizeof(SPVM_OBJECT));
}

int32_t SPVM_RUNTIME_API_get_fields_length(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
  int32_t* constant_pool = runtime->constant_pool;
  SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
  memcpy(&constant_pool_package, &constant_pool[object->package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
  int32_t length = constant_pool_package.fields_length;
  
  return length;
}


int32_t SPVM_RUNTIME_API_dump_field_names(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_GLOBAL_RUNTIME;
  
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

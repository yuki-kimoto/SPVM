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

void SPVM_RUNTIME_API_set_exception(SPVM_API* api, SPVM_SPVM_ARRAY* exception) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  if (runtime->exception != NULL) {
    SPVM_RUNTIME_API_dec_ref_count(api, (SPVM_BASE_OBJECT*)runtime->exception);
  }
  
  runtime->exception = exception;
  
  if (runtime->exception != NULL) {
    runtime->exception->ref_count++;
  }
}

SPVM_SPVM_ARRAY* SPVM_RUNTIME_API_malloc_byte_array_noinc(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  int32_t size = SPVM_RUNTIME_API_get_array_value_size(api, SPVM_SPVM_ARRAY_C_VALUE_TYPE_BYTE);
  
  // Allocate array
  int32_t array_byte_size = sizeof(SPVM_SPVM_ARRAY) + size * length;
  SPVM_SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  
  if (array) {
    // Set type
    array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
    
    // Set value type
    array->value_type = SPVM_SPVM_ARRAY_C_VALUE_TYPE_BYTE;
    
    // Set reference count
    array->ref_count = 0;
    
    // Set array length
    array->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));
  }
  
  return array;
}


SPVM_SPVM_ARRAY* SPVM_RUNTIME_API_malloc_short_array_noinc(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  int32_t size = SPVM_RUNTIME_API_get_array_value_size(api, SPVM_SPVM_ARRAY_C_VALUE_TYPE_SHORT);
  
  // Allocate array
  int32_t array_byte_size = sizeof(SPVM_SPVM_ARRAY) + size * length;
  SPVM_SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  
  if (array) {
    // Set type
    array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
    
    // Set value type
    array->value_type = SPVM_SPVM_ARRAY_C_VALUE_TYPE_SHORT;
    
    // Set reference count
    array->ref_count = 0;
    
    // Set array length
    array->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));
  }
  
  return array;
}

SPVM_SPVM_ARRAY* SPVM_RUNTIME_API_malloc_int_array_noinc(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  int32_t size = SPVM_RUNTIME_API_get_array_value_size(api, SPVM_SPVM_ARRAY_C_VALUE_TYPE_INT);
  
  // Allocate array
  int32_t array_byte_size = sizeof(SPVM_SPVM_ARRAY) + size * length;
  SPVM_SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  
  if (array) {
    // Set type
    array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
    
    // Set value type
    array->value_type = SPVM_SPVM_ARRAY_C_VALUE_TYPE_INT;
    
    // Set reference count
    array->ref_count = 0;
    
    // Set array length
    array->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));
  }
  
  return array;
}

SPVM_SPVM_ARRAY* SPVM_RUNTIME_API_malloc_long_array_noinc(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  int32_t size = SPVM_RUNTIME_API_get_array_value_size(api, SPVM_SPVM_ARRAY_C_VALUE_TYPE_LONG);
  
  // Allocate array
  int32_t array_byte_size = sizeof(SPVM_SPVM_ARRAY) + size * length;
  SPVM_SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  
  if (array) {
    // Set type
    array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
    
    // Set value type
    array->value_type = SPVM_SPVM_ARRAY_C_VALUE_TYPE_LONG;
    
    // Set reference count
    array->ref_count = 0;
    
    // Set array length
    array->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));
  }
  
  return array;
}

SPVM_SPVM_ARRAY* SPVM_RUNTIME_API_malloc_float_array_noinc(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  int32_t size = SPVM_RUNTIME_API_get_array_value_size(api, SPVM_SPVM_ARRAY_C_VALUE_TYPE_FLOAT);
  
  // Allocate array
  int32_t array_byte_size = sizeof(SPVM_SPVM_ARRAY) + size * length;
  SPVM_SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  
  if (array) {
    // Set type
    array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
    
    // Set value type
    array->value_type = SPVM_SPVM_ARRAY_C_VALUE_TYPE_FLOAT;
    
    // Set reference count
    array->ref_count = 0;
    
    // Set array length
    array->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));
  }
  
  return array;
}

SPVM_SPVM_ARRAY* SPVM_RUNTIME_API_malloc_double_array_noinc(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  int32_t size = SPVM_RUNTIME_API_get_array_value_size(api, SPVM_SPVM_ARRAY_C_VALUE_TYPE_DOUBLE);
  
  // Allocate array
  int32_t array_byte_size = sizeof(SPVM_SPVM_ARRAY) + size * length;
  SPVM_SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  
  if (array) {
    // Set type
    array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
    
    // Set value type
    array->value_type = SPVM_SPVM_ARRAY_C_VALUE_TYPE_DOUBLE;
    
    // Set reference count
    array->ref_count = 0;
    
    // Set array length
    array->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));
  }
  
  return array;
}

SPVM_SPVM_ARRAY* SPVM_RUNTIME_API_malloc_object_array_noinc(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  int32_t size = SPVM_RUNTIME_API_get_array_value_size(api, SPVM_SPVM_ARRAY_C_VALUE_TYPE_OBJECT);
  
  // Allocate array
  int32_t array_byte_size = sizeof(SPVM_SPVM_ARRAY) + size * length;
  SPVM_SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  
  if (array) {
    // Initialize by null
    memset((void*)((intptr_t)array + sizeof(SPVM_SPVM_ARRAY)), 0, size * length);
    
    // Set type
    array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
    
    // Set value type
    array->value_type = SPVM_SPVM_ARRAY_C_VALUE_TYPE_OBJECT;
    
    // Set reference count
    array->ref_count = 0;
    
    // Set array length
    array->length = length;
    
    assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));
  }
  
  return array;
}

SPVM_OBJECT* SPVM_RUNTIME_API_malloc_object_noinc(SPVM_API* api, int32_t package_constant_pool_index) {
  
  
  SPVM_RUNTIME* runtime = api->runtime;
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  int32_t* constant_pool = runtime->constant_pool;
  
  SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
  memcpy(&constant_pool_package, &constant_pool[package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
  
  // Allocate memory
  int32_t length = constant_pool_package.fields_length;
  int32_t byte_size = sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * length;
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, byte_size);
  
  if (__builtin_expect(object != NULL, 1)) {
    // Set type
    object->type = SPVM_BASE_OBJECT_C_TYPE_OBJECT;
    
    // Set reference count
    object->ref_count = 0;
    
    // Initialize reference fields by 0
    memset((void*)((intptr_t)object + sizeof(SPVM_OBJECT)), 0, sizeof(SPVM_VALUE) * constant_pool_package.object_fields_length);
    
    // Package constant pool index
    object->package_constant_pool_index = package_constant_pool_index;
    
    assert(byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)object));
  }
  
  return object;
}

int32_t SPVM_RUNTIME_API_get_array_length(SPVM_API* api, SPVM_SPVM_ARRAY* array) {
  (void)api;
  
  return array->length;
}

int8_t* SPVM_RUNTIME_API_get_byte_array_elements(SPVM_API* api, SPVM_SPVM_ARRAY* array) {
  (void)api;

  return (int8_t*)((intptr_t)array + sizeof(SPVM_SPVM_ARRAY));
}

int16_t* SPVM_RUNTIME_API_get_short_array_elements(SPVM_API* api, SPVM_SPVM_ARRAY* array) {
  (void)api;
  
  return (int16_t*)((intptr_t)array + sizeof(SPVM_SPVM_ARRAY));
}

int32_t* SPVM_RUNTIME_API_get_int_array_elements(SPVM_API* api, SPVM_SPVM_ARRAY* array) {
  (void)api;
  
  return (int32_t*)((intptr_t)array + sizeof(SPVM_SPVM_ARRAY));
}

int64_t* SPVM_RUNTIME_API_get_long_array_elements(SPVM_API* api, SPVM_SPVM_ARRAY* array) {
  (void)api;
  
  return (int64_t*)((intptr_t)array + sizeof(SPVM_SPVM_ARRAY));
}

float* SPVM_RUNTIME_API_get_float_array_elements(SPVM_API* api, SPVM_SPVM_ARRAY* array) {
  (void)api;
  
  return (float*)((intptr_t)array + sizeof(SPVM_SPVM_ARRAY));
}

double* SPVM_RUNTIME_API_get_double_array_elements(SPVM_API* api, SPVM_SPVM_ARRAY* array) {
  (void)api;
  
  return (double*)((intptr_t)array + sizeof(SPVM_SPVM_ARRAY));
}

SPVM_BASE_OBJECT** SPVM_RUNTIME_API_get_object_array_elements(SPVM_API* api, SPVM_SPVM_ARRAY* array) {
  (void)api;
  
  return (SPVM_BASE_OBJECT**)((intptr_t)array + sizeof(SPVM_SPVM_ARRAY));
}

void SPVM_RUNTIME_API_dec_ref_count(SPVM_API* api, SPVM_BASE_OBJECT* base_object) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  assert(base_object != NULL);
  assert(base_object->ref_count > 0);
  
  // Decrement reference count
  base_object->ref_count--;
  
  // If reference count is zero, free address.
  if (base_object->ref_count == 0) {
    
    if (base_object->type == SPVM_BASE_OBJECT_C_TYPE_ARRAY) {
      SPVM_SPVM_ARRAY* array = (SPVM_SPVM_ARRAY*)base_object;
      if (array->value_type == SPVM_SPVM_ARRAY_C_VALUE_TYPE_OBJECT) {
        
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
          SPVM_BASE_OBJECT* base_object_field = *(SPVM_BASE_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(void*) * i);
          if (base_object_field != NULL) {
            SPVM_RUNTIME_API_dec_ref_count(api, base_object_field);
          }
        }
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

void SPVM_RUNTIME_API_push_var_byte(SPVM_API* api, int8_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].byte_value = value;
}

void SPVM_RUNTIME_API_push_var_short(SPVM_API* api, int16_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].short_value = value;
}

void SPVM_RUNTIME_API_push_var_int(SPVM_API* api, int32_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].int_value = value;
}

void SPVM_RUNTIME_API_push_var_long(SPVM_API* api, int64_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].long_value = value;
}

void SPVM_RUNTIME_API_push_var_float(SPVM_API* api, float value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].float_value = value;
}

void SPVM_RUNTIME_API_push_var_double(SPVM_API* api, double value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].double_value = value;
}

void SPVM_RUNTIME_API_push_var_object(SPVM_API* api, SPVM_BASE_OBJECT* value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].object_value = value;
}

void SPVM_RUNTIME_API_push_retval_byte(SPVM_API* api, int8_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].byte_value = value;
}

void SPVM_RUNTIME_API_push_retval_short(SPVM_API* api, int16_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].short_value = value;
}

void SPVM_RUNTIME_API_push_retval_int(SPVM_API* api, int32_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].int_value = value;
}

void SPVM_RUNTIME_API_push_retval_long(SPVM_API* api, int64_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].long_value = value;
}

void SPVM_RUNTIME_API_push_retval_float(SPVM_API* api, float value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].float_value = value;
}

void SPVM_RUNTIME_API_push_retval_double(SPVM_API* api, double value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].double_value = value;
}

void SPVM_RUNTIME_API_push_retval_object(SPVM_API* api, SPVM_BASE_OBJECT* value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].object_value = value;
}

int8_t SPVM_RUNTIME_API_pop_retval_byte(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int8_t value = runtime->call_stack[runtime->operand_stack_top].byte_value;
  runtime->operand_stack_top--;

  return value;
}

int16_t SPVM_RUNTIME_API_pop_retval_short(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int16_t value = runtime->call_stack[runtime->operand_stack_top].short_value;
  runtime->operand_stack_top--;

  return value;
}

int32_t SPVM_RUNTIME_API_pop_retval_int(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t value = runtime->call_stack[runtime->operand_stack_top].int_value;
  runtime->operand_stack_top--;
  return value;
}

int64_t SPVM_RUNTIME_API_pop_retval_long(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int64_t value = runtime->call_stack[runtime->operand_stack_top].long_value;
  runtime->operand_stack_top--;
  
  return value;
}

float SPVM_RUNTIME_API_pop_retval_float(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  float value = runtime->call_stack[runtime->operand_stack_top].float_value;
  
  runtime->operand_stack_top--;
  
  return value;
}

double SPVM_RUNTIME_API_pop_retval_double(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  double value = runtime->call_stack[runtime->operand_stack_top].double_value;
  runtime->operand_stack_top--;
  
  return value;
}

void* SPVM_RUNTIME_API_pop_retval_object(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  SPVM_BASE_OBJECT* value = runtime->call_stack[runtime->operand_stack_top].object_value;
  
  runtime->operand_stack_top--;
  
  return value;
}

int8_t SPVM_RUNTIME_API_get_var_byte(SPVM_API* api, int32_t index) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].byte_value;
}

int16_t SPVM_RUNTIME_API_get_var_short(SPVM_API* api, int32_t index) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].short_value;
}

int32_t SPVM_RUNTIME_API_get_var_int(SPVM_API* api, int32_t index) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].int_value;
}

int64_t SPVM_RUNTIME_API_get_var_long(SPVM_API* api, int32_t index) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].long_value;
}

float SPVM_RUNTIME_API_get_var_float(SPVM_API* api, int32_t index) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].float_value;
}

double SPVM_RUNTIME_API_get_var_double(SPVM_API* api, int32_t index) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].double_value;
}

void* SPVM_RUNTIME_API_get_var_object(SPVM_API* api, int32_t index) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].object_value;
}

int32_t SPVM_RUNTIME_API_get_field_index(SPVM_API* api, SPVM_OBJECT* object, const char* name) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t* constant_pool = runtime->constant_pool;
  SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
  memcpy(&constant_pool_package, &constant_pool[object->package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
  
  int32_t length = constant_pool_package.fields_length;
  int32_t field_indexes_constant_pool_index = constant_pool_package.field_indexes_constant_pool_index;
  
  int32_t field_index = -1;
  _Bool found = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      
      int32_t field_constant_pool_index = constant_pool[field_indexes_constant_pool_index + i];
      SPVM_CONSTANT_POOL_FIELD constant_pool_field;
      memcpy(&constant_pool_field, &constant_pool[field_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_FIELD));
      
      int32_t field_name_constant_pool_index = constant_pool_field.name_constant_pool_index;
      
      char* match_name = (char*)&constant_pool[field_name_constant_pool_index];
      if (strcmp(name, match_name) == 0) {
        found = 1;
        field_index = i;
        break;
      }
    }
  }
  
  if (!found) {
    fprintf(stderr, "Can't find field name \"%s\"\n", name);
    abort();
  }
  
  return field_index;
}

int32_t SPVM_RUNTIME_API_get_sub_index(SPVM_API* api, const char* name) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t* constant_pool = runtime->constant_pool;
  int32_t length = runtime->subs_length;
  int32_t sub_indexes_constant_pool_index = runtime-> sub_indexes_constant_pool_index;
  
  int32_t found_sub_constant_pool_index = -1;
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

int32_t SPVM_RUNTIME_API_get_package_index(SPVM_API* api, const char* name) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t* constant_pool = runtime->constant_pool;
  int32_t length = runtime->packages_length;
  int32_t package_indexes_constant_pool_index = runtime-> package_indexes_constant_pool_index;
  
  int32_t found_package_constant_pool_index = -1;
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
  fields[field_index].object_value = value;
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
    SPVM_SPVM_ARRAY* array = (SPVM_SPVM_ARRAY*)base_object;
    byte_size = sizeof(SPVM_SPVM_ARRAY) + array->length * SPVM_RUNTIME_API_get_array_value_size(api, array->value_type);
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

SPVM_SPVM_ARRAY* SPVM_RUNTIME_API_create_array_byte(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  int32_t array_byte_size = sizeof(SPVM_SPVM_ARRAY) + sizeof(int8_t) * length;
  SPVM_SPVM_ARRAY* array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, array_byte_size);
  
  // Fatal memory allocation error
  if (!array) {
    fprintf(stderr, "Failed to allocate memory(create_array_from_pv)");
    abort();
  }
  
  // Set type
  array->type = SPVM_BASE_OBJECT_C_TYPE_ARRAY;
  
  // Set sub type
  array->value_type = SPVM_SPVM_ARRAY_C_VALUE_TYPE_BYTE;
  
  // Set reference count
  array->ref_count = 0;
  
  // Set array length
  array->length = length;
  
  assert(array_byte_size == SPVM_RUNTIME_API_calcurate_base_object_byte_size(api, (SPVM_BASE_OBJECT*)array));
  
  return array;
}

SPVM_SPVM_ARRAY* SPVM_RUNTIME_API_create_array_byte_from_pv(SPVM_API* api, const char* pv) {
  (void)api;
  
  int32_t length = strlen(pv);
  SPVM_SPVM_ARRAY* array = SPVM_RUNTIME_API_create_array_byte(api, length);
  
  // Copy string
  memcpy((void*)((intptr_t)array + sizeof(SPVM_SPVM_ARRAY)), pv, length);
  
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

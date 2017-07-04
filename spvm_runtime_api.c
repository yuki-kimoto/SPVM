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
#include "spvm_data.h"
#include "spvm_data_array.h"
#include "spvm_data_object.h"
#include "spvm_value.h"
#include "spvm_runtime.h"
#include "spvm_runtime_allocator.h"
#include "spvm_api.h"

int64_t SPVM_RUNTIME_API_calcurate_data_byte_size(SPVM_API* api, SPVM_DATA* data) {
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int64_t byte_size;
  
  // Reference is string
  if (data->type == SPVM_DATA_C_TYPE_ARRAY) {
    SPVM_DATA_ARRAY* data_array = (SPVM_DATA_ARRAY*)data;
    byte_size = sizeof(SPVM_DATA_ARRAY) + data_array->length * SPVM_RUNTIME_API_get_array_value_size(api, data_array->value_type);
  }
  // Reference is object
  else if (data->type == SPVM_DATA_C_TYPE_OBJECT) {
    SPVM_DATA_OBJECT* data_object = (SPVM_DATA_OBJECT*)data;
    SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
    memcpy(&constant_pool_package, &runtime->constant_pool[data_object->package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
    byte_size = sizeof(SPVM_DATA_OBJECT) + sizeof(SPVM_VALUE) * constant_pool_package.fields_length;
  }
  else {
    assert(0);
  }
  
  return byte_size;
}

SPVM_DATA_ARRAY* SPVM_RUNTIME_API_create_data_array_byte(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  int32_t data_array_byte_size = sizeof(SPVM_DATA_ARRAY) + sizeof(int8_t) * length;
  SPVM_DATA_ARRAY* data_array = SPVM_RUNTIME_ALLOCATOR_malloc(api, allocator, data_array_byte_size);
  
  // Fatal memory allocation error
  if (!data_array) {
    fprintf(stderr, "Failed to allocate memory(create_data_array_from_pv)");
    abort();
  }
  
  // Set type
  data_array->type = SPVM_DATA_C_TYPE_ARRAY;
  
  // Set sub type
  data_array->value_type = SPVM_DATA_ARRAY_C_VALUE_TYPE_BYTE;
  
  // Set reference count
  data_array->ref_count = 0;
  
  // Set array length
  data_array->length = length;
  
  assert(data_array_byte_size == SPVM_RUNTIME_API_calcurate_data_byte_size(api, (SPVM_DATA*)data_array));
  
  return data_array;
}

SPVM_DATA_ARRAY* SPVM_RUNTIME_API_create_data_array_byte_from_pv(SPVM_API* api, const char* pv) {
  (void)api;
  
  int32_t length = strlen(pv);
  SPVM_DATA_ARRAY* data_array = SPVM_RUNTIME_API_create_data_array_byte(api, length);
  
  // Copy string
  memcpy((void*)((intptr_t)data_array + sizeof(SPVM_DATA_ARRAY)), pv, length);
  
  return data_array;
}

void SPVM_RUNTIME_API_dec_ref_count(SPVM_API* api, SPVM_DATA* data) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  if (data != NULL) {
    
    assert(data->ref_count > 0);
    
    // Decrement reference count
    data->ref_count -= 1;
    
    // If reference count is zero, free address.
    if (data->ref_count == 0) {
      
      if (data->type == SPVM_DATA_C_TYPE_ARRAY) {
        SPVM_DATA_ARRAY* data_array = (SPVM_DATA_ARRAY*)data;
        if (data_array->value_type == SPVM_DATA_ARRAY_C_VALUE_TYPE_REF) {
          
          // Array length
          int32_t length = data_array->length;
          
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SPVM_DATA* data_element = *(SPVM_DATA**)((intptr_t)data_array + sizeof(SPVM_DATA_OBJECT) + sizeof(void*) * i);
              SPVM_RUNTIME_API_dec_ref_count(api, data_element);
            }
          }
        }
        SPVM_RUNTIME_ALLOCATOR_free_data(api, runtime->allocator, data);
      }
      // Reference is object
      else if (data->type == SPVM_DATA_C_TYPE_OBJECT) {
        SPVM_DATA_OBJECT* data_object = (SPVM_DATA_OBJECT*)data;
        
        int32_t package_constant_pool_index = data_object->package_constant_pool_index;
        SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
        memcpy(&constant_pool_package, &runtime->constant_pool[package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
        
        int32_t ref_fields_length = constant_pool_package.ref_fields_length;
        
        {
          int32_t i;
          for (i = 0; i < ref_fields_length; i++) {
            SPVM_DATA* data_field = *(SPVM_DATA**)((intptr_t)data_object + sizeof(SPVM_DATA_OBJECT) + sizeof(void*) * i);
            SPVM_RUNTIME_API_dec_ref_count(api, data_field);
          }
        }
        
        SPVM_RUNTIME_ALLOCATOR_free_data(api, runtime->allocator, (SPVM_DATA*)data_object);
      }
    }
  }
}

void SPVM_RUNTIME_API_inc_ref_count(SPVM_API* api, SPVM_DATA* data) {
  (void)api;
  
  if (data != NULL) {
    assert(data->ref_count >= 0);
    // Increment reference count
    data->ref_count += 1;
  }
}

void SPVM_RUNTIME_API_push_return_value_byte(SPVM_API* api, int8_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].byte_value = value;
}

void SPVM_RUNTIME_API_push_return_value_short(SPVM_API* api, int16_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].short_value = value;
}

void SPVM_RUNTIME_API_push_return_value_int(SPVM_API* api, int32_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].int_value = value;
}

void SPVM_RUNTIME_API_push_return_value_long(SPVM_API* api, int64_t value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].long_value = value;
}

void SPVM_RUNTIME_API_push_return_value_float(SPVM_API* api, float value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].float_value = value;
}

void SPVM_RUNTIME_API_push_return_value_double(SPVM_API* api, double value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].double_value = value;
}

void SPVM_RUNTIME_API_push_ret(SPVM_API* api, void* value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].address_value = value;
}

int8_t SPVM_RUNTIME_API_pop_return_value_byte(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int8_t ret = runtime->call_stack[runtime->operand_stack_top].byte_value;
  runtime->operand_stack_top--;
  return ret;
}

int16_t SPVM_RUNTIME_API_pop_return_value_short(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int16_t ret = runtime->call_stack[runtime->operand_stack_top].short_value;
  runtime->operand_stack_top--;
  return ret;
}

int32_t SPVM_RUNTIME_API_pop_return_value_int(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t ret = runtime->call_stack[runtime->operand_stack_top].int_value;
  runtime->operand_stack_top--;
  return ret;
}

int64_t SPVM_RUNTIME_API_pop_return_value_long(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;

  int64_t ret = runtime->call_stack[runtime->operand_stack_top].long_value;
  runtime->operand_stack_top--;
  return ret;
}

float SPVM_RUNTIME_API_pop_return_value_float(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  float ret = runtime->call_stack[runtime->operand_stack_top].float_value;
  runtime->operand_stack_top--;
  return ret;
}

double SPVM_RUNTIME_API_pop_return_value_double(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  double ret = runtime->call_stack[runtime->operand_stack_top].double_value;
  runtime->operand_stack_top--;
  return ret;
}

void* SPVM_RUNTIME_API_pop_return_value_address(SPVM_API* api) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  void* ret = runtime->call_stack[runtime->operand_stack_top].address_value;
  runtime->operand_stack_top--;
  return ret;
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

void* SPVM_RUNTIME_API_get_var_address(SPVM_API* api, int32_t index) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].address_value;
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

void SPVM_RUNTIME_API_push_var_address(SPVM_API* api, void* value) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].address_value = value;
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

SPVM_VALUE* SPVM_RUNTIME_API_get_fields(SPVM_API* api, SPVM_DATA_OBJECT* data_object) {
  (void)api;
  
  return (SPVM_VALUE*)((intptr_t)data_object + sizeof(SPVM_DATA_OBJECT));
}

int32_t SPVM_RUNTIME_API_get_field_index(SPVM_API* api, SPVM_DATA_OBJECT* data_object, const char* name) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t* constant_pool = runtime->constant_pool;
  SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
  memcpy(&constant_pool_package, &constant_pool[data_object->package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
  
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
    fprintf(stderr, "Can't find filed name \"%s\"\n", name);
    abort();
  }
  
  return field_index;
}

int32_t SPVM_RUNTIME_API_get_fields_length(SPVM_API* api, SPVM_DATA_OBJECT* data_object) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t* constant_pool = runtime->constant_pool;
  SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
  memcpy(&constant_pool_package, &constant_pool[data_object->package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
  int32_t length = constant_pool_package.fields_length;
  
  return length;
}

void SPVM_RUNTIME_API_set_byte_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, int8_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  fields[field_index].byte_value = value;
}

void SPVM_RUNTIME_API_set_short_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, int16_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  fields[field_index].short_value = value;
}

void SPVM_RUNTIME_API_set_int_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, int32_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  fields[field_index].int_value = value;
}

void SPVM_RUNTIME_API_set_long_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, int64_t value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  fields[field_index].long_value = value;
}

void SPVM_RUNTIME_API_set_float_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, float value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  fields[field_index].float_value = value;
}

void SPVM_RUNTIME_API_set_double_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, double value) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  fields[field_index].double_value = value;
}

int8_t SPVM_RUNTIME_API_get_byte_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  int8_t byte_value = fields[field_index].byte_value;
  
  return byte_value;
}

int16_t SPVM_RUNTIME_API_get_short_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  int16_t short_value = fields[field_index].short_value;
  
  return short_value;
}

int32_t SPVM_RUNTIME_API_get_int_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  int32_t int_value = fields[field_index].int_value;
  
  return int_value;
}

int64_t SPVM_RUNTIME_API_get_long_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  int64_t long_value = fields[field_index].long_value;
  
  return long_value;
}

float SPVM_RUNTIME_API_get_float_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  float float_value = fields[field_index].float_value;
  
  return float_value;
}

double SPVM_RUNTIME_API_get_double_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  double double_value = fields[field_index].double_value;
  
  return double_value;
}

SPVM_DATA* SPVM_RUNTIME_API_get_ref_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index) {
  SPVM_VALUE* fields = SPVM_RUNTIME_API_get_fields(api, data_object);
  SPVM_DATA* address_value = fields[field_index].address_value;
  
  return address_value;
}

int32_t SPVM_RUNTIME_API_dump_field_names(SPVM_API* api, SPVM_DATA_OBJECT* data_object) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  int32_t* constant_pool = runtime->constant_pool;
  SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
  memcpy(&constant_pool_package, &constant_pool[data_object->package_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
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

int32_t SPVM_RUNTIME_API_get_ref_count(SPVM_API* api, SPVM_DATA* data) {
  (void)api;
  
  return data->ref_count;
}

int32_t SPVM_RUNTIME_API_get_array_length(SPVM_API* api, SPVM_DATA_ARRAY* data_array) {
  (void)api;
  
  return data_array->length;
}

int8_t* SPVM_RUNTIME_API_get_array_values_byte(SPVM_API* api, SPVM_DATA_ARRAY* data_array) {
  (void)api;

  return (int8_t*)((intptr_t)data_array + sizeof(SPVM_DATA_ARRAY));
}

int16_t* SPVM_RUNTIME_API_get_array_values_short(SPVM_API* api, SPVM_DATA_ARRAY* data_array) {
  (void)api;
  
  return (int16_t*)((intptr_t)data_array + sizeof(SPVM_DATA_ARRAY));
}

int32_t* SPVM_RUNTIME_API_get_array_values_int(SPVM_API* api, SPVM_DATA_ARRAY* data_array) {
  (void)api;
  
  return (int32_t*)((intptr_t)data_array + sizeof(SPVM_DATA_ARRAY));
}

int64_t* SPVM_RUNTIME_API_get_array_values_long(SPVM_API* api, SPVM_DATA_ARRAY* data_array) {
  (void)api;
  
  return (int64_t*)((intptr_t)data_array + sizeof(SPVM_DATA_ARRAY));
}

float* SPVM_RUNTIME_API_get_array_values_float(SPVM_API* api, SPVM_DATA_ARRAY* data_array) {
  (void)api;
  
  return (float*)((intptr_t)data_array + sizeof(SPVM_DATA_ARRAY));
}

double* SPVM_RUNTIME_API_get_array_values_double(SPVM_API* api, SPVM_DATA_ARRAY* data_array) {
  (void)api;
  
  return (double*)((intptr_t)data_array + sizeof(SPVM_DATA_ARRAY));
}

SPVM_DATA** SPVM_RUNTIME_API_get_array_values_ref(SPVM_API* api, SPVM_DATA_ARRAY* data_array) {
  (void)api;
  
  return (SPVM_DATA**)((intptr_t)data_array + sizeof(SPVM_DATA_ARRAY));
}

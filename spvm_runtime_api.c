#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_allocator.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_package.h"
#include "spvm_constant_pool_field.h"
#include "spvm_data_api.h"

inline int64_t SPVM_RUNTIME_API_calcurate_data_byte_size(SPVM_RUNTIME* runtime, SPVM_DATA* data) {
  
  int64_t byte_size;
  
  // Reference is string
  if (data->type == SPVM_DATA_C_TYPE_ARRAY) {
    SPVM_DATA_ARRAY* data_array = (SPVM_DATA_ARRAY*)data;
    byte_size = SPVM_DATA_C_HEADER_BYTE_SIZE + data_array->length * SPVM_DATA_ARRAY_C_VALUE_SIZES[data_array->value_type];
  }
  // Reference is object
  else if (data->type == SPVM_DATA_C_TYPE_OBJECT) {
    SPVM_DATA_OBJECT* data_object = (SPVM_DATA_OBJECT*)data;
    SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
    memcpy(&constant_pool_package, &runtime->constant_pool[data_object->package_constant_pool_address], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
    byte_size = SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * constant_pool_package.fields_length;
  }
  else {
    assert(0);
  }
  
  return byte_size;
}

inline SPVM_DATA_ARRAY* SPVM_RUNTIME_API_create_data_array_byte(SPVM_RUNTIME* runtime, int32_t length) {
  (void)runtime;
  
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Allocate array
  int32_t data_array_byte_size = SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(int8_t) * length;
  SPVM_DATA_ARRAY* data_array = SPVM_RUNTIME_ALLOCATOR_malloc(runtime, allocator, data_array_byte_size);
  
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
  
  assert(data_array_byte_size == SPVM_RUNTIME_API_calcurate_data_byte_size(runtime, (SPVM_DATA*)data_array));
  
  return data_array;
}

inline SPVM_DATA_ARRAY* SPVM_RUNTIME_API_create_data_array_byte_from_pv(SPVM_RUNTIME* runtime, const char* pv) {
  (void)runtime;
  
  int32_t length = strlen(pv);
  SPVM_DATA_ARRAY* data_array = SPVM_RUNTIME_API_create_data_array_byte(runtime, length);
  
  // Copy string
  memcpy((void*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE), pv, length);
  
  return data_array;
}

inline void SPVM_RUNTIME_API_dec_ref_count(SPVM_RUNTIME* runtime, SPVM_DATA* data) {
  (void)runtime;
  
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
          
          for (int32_t i = 0; i < length; i++) {
            SPVM_DATA* data_element = *(SPVM_DATA**)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(void*) * i);
            SPVM_RUNTIME_API_dec_ref_count(runtime, data_element);
          }
        }
        SPVM_RUNTIME_ALLOCATOR_free_data(runtime, runtime->allocator, data);
      }
      // Reference is object
      else if (data->type == SPVM_DATA_C_TYPE_OBJECT) {
        SPVM_DATA_OBJECT* data_object = (SPVM_DATA_OBJECT*)data;
        
        int32_t package_constant_pool_address = data_object->package_constant_pool_address;
        SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
        memcpy(&constant_pool_package, &data_object->constant_pool[package_constant_pool_address], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
        
        int32_t ref_fields_length = constant_pool_package.ref_fields_length;
        
        for (int i = 0; i < ref_fields_length; i++) {
          SPVM_DATA* data_field = *(SPVM_DATA**)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(void*) * i);
          SPVM_RUNTIME_API_dec_ref_count(runtime, data_field);
        }
        
        SPVM_RUNTIME_ALLOCATOR_free_data(runtime, runtime->allocator, (SPVM_DATA*)data_object);
      }
    }
  }
}

inline void SPVM_RUNTIME_API_inc_ref_count(SPVM_RUNTIME* runtime, SPVM_DATA* data) {
  (void)runtime;
  
  if (data != NULL) {
    assert(data->ref_count >= 0);
    // Increment reference count
    data->ref_count += 1;
  }
}

inline void SPVM_RUNTIME_API_push_return_value_byte(SPVM_RUNTIME* runtime, int8_t value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].byte_value = value;
}

inline void SPVM_RUNTIME_API_push_return_value_short(SPVM_RUNTIME* runtime, int16_t value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].short_value = value;
}

inline void SPVM_RUNTIME_API_push_return_value_int(SPVM_RUNTIME* runtime, int32_t value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].int_value = value;
}

inline void SPVM_RUNTIME_API_push_return_value_long(SPVM_RUNTIME* runtime, int64_t value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].long_value = value;
}

inline void SPVM_RUNTIME_API_push_return_value_float(SPVM_RUNTIME* runtime, float value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].float_value = value;
}

inline void SPVM_RUNTIME_API_push_return_value_double(SPVM_RUNTIME* runtime, double value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].double_value = value;
}

inline void SPVM_RUNTIME_API_push_ret(SPVM_RUNTIME* runtime, void* value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].address_value = value;
}

inline int8_t SPVM_RUNTIME_API_pop_return_value_byte(SPVM_RUNTIME* runtime) {
  (void)runtime;
  
  int8_t ret = runtime->call_stack[runtime->operand_stack_top].byte_value;
  runtime->operand_stack_top--;
  return ret;
}

inline int16_t SPVM_RUNTIME_API_pop_return_value_short(SPVM_RUNTIME* runtime) {
  (void)runtime;
  
  int16_t ret = runtime->call_stack[runtime->operand_stack_top].short_value;
  runtime->operand_stack_top--;
  return ret;
}

inline int32_t SPVM_RUNTIME_API_pop_return_value_int(SPVM_RUNTIME* runtime) {
  (void)runtime;
  
  int32_t ret = runtime->call_stack[runtime->operand_stack_top].int_value;
  runtime->operand_stack_top--;
  return ret;
}

inline int64_t SPVM_RUNTIME_API_pop_return_value_long(SPVM_RUNTIME* runtime) {
  (void)runtime;

  int64_t ret = runtime->call_stack[runtime->operand_stack_top].long_value;
  runtime->operand_stack_top--;
  return ret;
}

inline float SPVM_RUNTIME_API_pop_return_value_float(SPVM_RUNTIME* runtime) {
  (void)runtime;
  
  float ret = runtime->call_stack[runtime->operand_stack_top].float_value;
  runtime->operand_stack_top--;
  return ret;
}

inline double SPVM_RUNTIME_API_pop_return_value_double(SPVM_RUNTIME* runtime) {
  (void)runtime;
  
  double ret = runtime->call_stack[runtime->operand_stack_top].double_value;
  runtime->operand_stack_top--;
  return ret;
}

inline void* SPVM_RUNTIME_API_pop_return_value_address(SPVM_RUNTIME* runtime) {
  (void)runtime;
  
  void* ret = runtime->call_stack[runtime->operand_stack_top].address_value;
  runtime->operand_stack_top--;
  return ret;
}

inline int8_t SPVM_RUNTIME_API_get_var_byte(SPVM_RUNTIME* runtime, int32_t index) {
  (void)runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].byte_value;
}

inline int16_t SPVM_RUNTIME_API_get_var_short(SPVM_RUNTIME* runtime, int32_t index) {
  (void)runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].short_value;
}

inline int32_t SPVM_RUNTIME_API_get_var_int(SPVM_RUNTIME* runtime, int32_t index) {
  (void)runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].int_value;
}

inline int64_t SPVM_RUNTIME_API_get_var_long(SPVM_RUNTIME* runtime, int32_t index) {
  (void)runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].long_value;
}

inline float SPVM_RUNTIME_API_get_var_float(SPVM_RUNTIME* runtime, int32_t index) {
  (void)runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].float_value;
}

inline double SPVM_RUNTIME_API_get_var_double(SPVM_RUNTIME* runtime, int32_t index) {
  (void)runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].double_value;
}

inline void* SPVM_RUNTIME_API_get_var_address(SPVM_RUNTIME* runtime, int32_t index) {
  (void)runtime;
  
  return runtime->call_stack[runtime->call_stack_base + (size_t)index].address_value;
}

inline void SPVM_RUNTIME_API_push_var_byte(SPVM_RUNTIME* runtime, int8_t value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].byte_value = value;
}

inline void SPVM_RUNTIME_API_push_var_short(SPVM_RUNTIME* runtime, int16_t value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].short_value = value;
}

inline void SPVM_RUNTIME_API_push_var_int(SPVM_RUNTIME* runtime, int32_t value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].int_value = value;
}

inline void SPVM_RUNTIME_API_push_var_long(SPVM_RUNTIME* runtime, int64_t value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].long_value = value;
}

inline void SPVM_RUNTIME_API_push_var_float(SPVM_RUNTIME* runtime, float value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].float_value = value;
}

inline void SPVM_RUNTIME_API_push_var_double(SPVM_RUNTIME* runtime, double value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].double_value = value;
}

inline void SPVM_RUNTIME_API_push_var_address(SPVM_RUNTIME* runtime, void* value) {
  (void)runtime;
  
  runtime->operand_stack_top++;
  runtime->call_stack[runtime->operand_stack_top].address_value = value;
}


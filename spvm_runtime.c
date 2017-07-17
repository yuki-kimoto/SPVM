#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_allocator.h"
#include "spvm_bytecode.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_field.h"
#include "spvm_constant_pool_package.h"
#include "spvm_base_object.h"
#include "spvm_array.h"
#include "spvm_object.h"
#include "spvm_util_allocator.h"
#include "spvm_value.h"
#include "spvm_api.h"

SPVM_RUNTIME* SPVM_RUNTIME_new() {
  
  SPVM_RUNTIME* runtime = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(1, sizeof(SPVM_RUNTIME));

  runtime->constant_pool = NULL;
  runtime->bytecodes = NULL;
  
  // Runtime memory allocator
  runtime->allocator = SPVM_RUNTIME_ALLOCATOR_new(runtime);
  
  runtime->call_stack_capacity = 0xFF;
  runtime->call_stack = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(runtime->call_stack_capacity, sizeof(SPVM_VALUE));
  
  SPVM_API* api = SPVM_RUNTIME_new_api(runtime);
  
  api->runtime = runtime;
  runtime->api = api;
  
  runtime->call_stack_base = -1;
  runtime->operand_stack_top = -1;
  runtime->abort = 0;
  
  // Packages length
  runtime->packages_length = 0;
  
  // Indexes of package
  runtime->package_indexes_constant_pool_index = -1;
  
  // Subroutines length
  runtime->subs_length = 0;
  
  // Indexes of package
  runtime->sub_indexes_constant_pool_index = -1;
  
  // Exception
  runtime->exception = NULL;

#ifdef DEBUG
  runtime->object_count = 0;
#endif
  
  return runtime;
}

SPVM_API* SPVM_RUNTIME_new_api(SPVM_RUNTIME* runtime) {
  (void)runtime;
  
  SPVM_API* api = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(1, sizeof(SPVM_API));
  
  // Array functions
  api->get_array_length = (int32_t (*)(SPVM_API*, SPVM_API_ARRAY*))SPVM_RUNTIME_API_get_array_length;
  api->get_byte_array_elements = (int8_t* (*)(SPVM_API*, SPVM_API_ARRAY*))SPVM_RUNTIME_API_get_byte_array_elements;
  api->get_short_array_elements = (int16_t* (*)(SPVM_API*, SPVM_API_ARRAY*))SPVM_RUNTIME_API_get_short_array_elements;
  api->get_int_array_elements = (int32_t* (*)(SPVM_API*, SPVM_API_ARRAY*))SPVM_RUNTIME_API_get_int_array_elements;
  api->get_long_array_elements = (int64_t* (*)(SPVM_API*, SPVM_API_ARRAY*))SPVM_RUNTIME_API_get_long_array_elements;
  api->get_float_array_elements = (float* (*)(SPVM_API*, SPVM_API_ARRAY*))SPVM_RUNTIME_API_get_float_array_elements;
  api->get_double_array_elements = (double* (*)(SPVM_API*, SPVM_API_ARRAY*))SPVM_RUNTIME_API_get_double_array_elements;
  api->get_object_array_elements = (SPVM_API_BASE_OBJECT** (*)(SPVM_API*, SPVM_API_ARRAY*))SPVM_RUNTIME_API_get_object_array_elements;
  
  // Object functions
  api->get_field_id = (int32_t (*)(SPVM_API*, SPVM_API_OBJECT*, const char*))SPVM_RUNTIME_API_get_field_id;
  api->get_byte_field = (int8_t (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t))SPVM_RUNTIME_API_get_byte_field;
  api->get_short_field = (int16_t (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t))SPVM_RUNTIME_API_get_short_field;
  api->get_int_field = (int32_t (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t))SPVM_RUNTIME_API_get_int_field;
  api->get_long_field = (int64_t (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t))SPVM_RUNTIME_API_get_long_field;
  api->get_float_field = (float (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t))SPVM_RUNTIME_API_get_float_field;
  api->get_double_field = (double (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t))SPVM_RUNTIME_API_get_double_field;
  api->get_object_field = (SPVM_API_BASE_OBJECT* (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t))SPVM_RUNTIME_API_get_object_field;
  api->set_byte_field = (void (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int8_t))SPVM_RUNTIME_API_set_byte_field;
  api->set_short_field = (void (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int16_t))SPVM_RUNTIME_API_set_short_field;
  api->set_int_field = (void (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int32_t))SPVM_RUNTIME_API_set_int_field;
  api->set_long_field = (void (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int64_t))SPVM_RUNTIME_API_set_long_field;
  api->set_float_field = (void (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t, float))SPVM_RUNTIME_API_set_float_field;
  api->set_double_field = (void (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t, double))SPVM_RUNTIME_API_set_double_field;
  api->set_object_field = (void (*)(SPVM_API*, SPVM_API_OBJECT*, int32_t, SPVM_API_BASE_OBJECT*))SPVM_RUNTIME_API_set_object_field;
  
  // Call subroutine fucntions
  api->push_var_byte = (void (*)(SPVM_API*, int8_t))SPVM_RUNTIME_API_push_var_byte;
  api->push_var_short = (void (*)(SPVM_API*, int16_t))SPVM_RUNTIME_API_push_var_short;
  api->push_var_int = (void (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_push_var_int;
  api->push_var_long = (void (*)(SPVM_API*, int64_t))SPVM_RUNTIME_API_push_var_long;
  api->push_var_float = (void (*)(SPVM_API*, float))SPVM_RUNTIME_API_push_var_float;
  api->push_var_double = (void (*)(SPVM_API*, double))SPVM_RUNTIME_API_push_var_double;
  api->push_var_object = (void (*)(SPVM_API*, SPVM_API_BASE_OBJECT*))SPVM_RUNTIME_API_push_var_object;
  api->get_sub_id = (int32_t (*)(SPVM_API*, const char*))SPVM_RUNTIME_API_get_sub_id;
  api->call_sub = (void (*)(SPVM_API*, int32_t))SPVM_RUNTIME_call_sub;
  api->pop_retval_byte = (int8_t (*)(SPVM_API*))SPVM_RUNTIME_API_pop_retval_byte;
  api->pop_retval_short = (int16_t (*)(SPVM_API*))SPVM_RUNTIME_API_pop_retval_short;
  api->pop_retval_int = (int32_t (*)(SPVM_API*))SPVM_RUNTIME_API_pop_retval_int;
  api->pop_retval_long = (int64_t (*)(SPVM_API*))SPVM_RUNTIME_API_pop_retval_long;
  api->pop_retval_float = (float (*)(SPVM_API*))SPVM_RUNTIME_API_pop_retval_float;
  api->pop_retval_double = (double (*)(SPVM_API*))SPVM_RUNTIME_API_pop_retval_double;
  api->pop_retval_object = (SPVM_API_BASE_OBJECT* (*)(SPVM_API*))SPVM_RUNTIME_API_pop_retval_object;
  
  // Malloc funtctions
  api->get_package_id = (int32_t (*)(SPVM_API*, const char*))SPVM_RUNTIME_API_get_package_id;
  api->malloc_object_noinc = (SPVM_API_OBJECT* (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_malloc_object_noinc;
  api->malloc_byte_array_noinc = (SPVM_API_ARRAY* (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_malloc_byte_array_noinc;
  api->malloc_short_array_noinc = (SPVM_API_ARRAY* (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_malloc_short_array_noinc;
  api->malloc_int_array_noinc = (SPVM_API_ARRAY* (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_malloc_int_array_noinc;
  api->malloc_long_array_noinc = (SPVM_API_ARRAY* (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_malloc_long_array_noinc;
  api->malloc_float_array_noinc = (SPVM_API_ARRAY* (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_malloc_float_array_noinc;
  api->malloc_double_array_noinc = (SPVM_API_ARRAY* (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_malloc_double_array_noinc;
  api->malloc_object_array_noinc = (SPVM_API_ARRAY* (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_malloc_object_array_noinc;
  
  // Functions used in subroutine
  api->get_var_byte = (int8_t (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_get_var_byte;
  api->get_var_short = (int16_t (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_get_var_short;
  api->get_var_int = (int32_t (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_get_var_int;
  api->get_var_long = (int64_t (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_get_var_long;
  api->get_var_float = (float (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_get_var_float;
  api->get_var_double = (double (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_get_var_double;
  api->get_var_object = (SPVM_API_BASE_OBJECT* (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_get_var_object;
  api->push_retval_byte = (void (*)(SPVM_API*, int8_t))SPVM_RUNTIME_API_push_retval_byte;
  api->push_retval_short = (void (*)(SPVM_API*, int16_t))SPVM_RUNTIME_API_push_retval_short;
  api->push_retval_int = (void (*)(SPVM_API*, int32_t))SPVM_RUNTIME_API_push_retval_int;
  api->push_retval_long = (void (*)(SPVM_API*, int64_t))SPVM_RUNTIME_API_push_retval_long;
  api->push_retval_float = (void (*)(SPVM_API*, float))SPVM_RUNTIME_API_push_retval_float;
  api->push_retval_double = (void (*)(SPVM_API*, double))SPVM_RUNTIME_API_push_retval_double;
  api->push_retval_object = (void (*)(SPVM_API*, SPVM_API_BASE_OBJECT*))SPVM_RUNTIME_API_push_retval_object;

  // Exception
  api->set_exception = (void (*)(SPVM_API* api, SPVM_API_ARRAY* exception))SPVM_RUNTIME_API_set_exception;
  api->get_exception = (SPVM_API_ARRAY* (*)(SPVM_API* api))SPVM_RUNTIME_API_get_exception;
  
  // Reference count
  api->dec_ref_count = (void (*)(SPVM_API* api, SPVM_API_BASE_OBJECT* base_object))SPVM_RUNTIME_API_dec_ref_count;
  api->inc_ref_count = (void (*)(SPVM_API* api, SPVM_API_BASE_OBJECT* base_object))SPVM_RUNTIME_API_inc_ref_count;

  return api;
}

void SPVM_RUNTIME_call_sub(SPVM_API* api, int32_t sub_constant_pool_index) {
  (void)api;
  
  // Jump table for direct threaded code
  static const void* jump[] = {
    &&case_SPVM_BYTECODE_C_CODE_NOP,
    &&case_SPVM_BYTECODE_C_CODE_UNDEF,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_BYTE_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_BYTE_1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_SHORT_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_SHORT_1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_M1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_2,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_3,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_4,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_5,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_M1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_2,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_3,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_4,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_5,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_2,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_DOUBLE_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_DOUBLE_1,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_CONSTANT,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_CONSTANT2,
    &&case_SPVM_BYTECODE_C_CODE_ADD_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_ADD_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_ADD_INT,
    &&case_SPVM_BYTECODE_C_CODE_ADD_LONG,
    &&case_SPVM_BYTECODE_C_CODE_ADD_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_ADD_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_INT,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_LONG,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_INT,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_LONG,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_INT,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_LONG,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_INT,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_LONG,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_INT,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_LONG,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_INT,
    &&case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_LONG,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_INT,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_LONG,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG,
    &&case_SPVM_BYTECODE_C_CODE_BIT_AND_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_BIT_AND_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_BIT_AND_INT,
    &&case_SPVM_BYTECODE_C_CODE_BIT_AND_LONG,
    &&case_SPVM_BYTECODE_C_CODE_BIT_OR_BYTE ,
    &&case_SPVM_BYTECODE_C_CODE_BIT_OR_SHORT ,
    &&case_SPVM_BYTECODE_C_CODE_BIT_OR_INT,
    &&case_SPVM_BYTECODE_C_CODE_BIT_OR_LONG,
    &&case_SPVM_BYTECODE_C_CODE_BIT_XOR_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_BIT_XOR_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_BIT_XOR_INT,
    &&case_SPVM_BYTECODE_C_CODE_BIT_XOR_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_INC_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_INC_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_INC_INT,
    &&case_SPVM_BYTECODE_C_CODE_INC_LONG,
    &&case_SPVM_BYTECODE_C_CODE_LOAD,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_0,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_1,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_2,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_3,
    &&case_SPVM_BYTECODE_C_CODE_STORE,
    &&case_SPVM_BYTECODE_C_CODE_STORE_0,
    &&case_SPVM_BYTECODE_C_CODE_STORE_1,
    &&case_SPVM_BYTECODE_C_CODE_STORE_2,
    &&case_SPVM_BYTECODE_C_CODE_STORE_3,
    &&case_SPVM_BYTECODE_C_CODE_STORE_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_POP,
    &&case_SPVM_BYTECODE_C_CODE_MALLOC_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_MALLOC_STRING,
    &&case_SPVM_BYTECODE_C_CODE_MALLOC_ARRAY,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LENGTH,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_INT,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_LONG,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_INT,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_LONG,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_CMP_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CMP_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CMP_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CMP_FLOAT_L,
    &&case_SPVM_BYTECODE_C_CODE_CMP_FLOAT_G,
    &&case_SPVM_BYTECODE_C_CODE_CMP_DOUBLE_L,
    &&case_SPVM_BYTECODE_C_CODE_CMP_DOUBLE_G,
    &&case_SPVM_BYTECODE_C_CODE_IF_EQ_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_NE_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_LT_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_GE_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_GT_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_LE_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_EQ_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_NE_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_LT_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_GE_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_GT_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_LE_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_EQ_CMP_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_IF_NE_CMP_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_IF_NULL,
    &&case_SPVM_BYTECODE_C_CODE_IF_NON_NULL,
    &&case_SPVM_BYTECODE_C_CODE_TABLE_SWITCH,
    &&case_SPVM_BYTECODE_C_CODE_LOOKUP_SWITCH,
    &&case_SPVM_BYTECODE_C_CODE_GOTO,
    &&case_SPVM_BYTECODE_C_CODE_CALL_SUB,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_VOID,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_INT,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_LONG,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_DIE,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_EXCEPTION,
    &&case_SPVM_BYTECODE_C_CODE_STORE_EXCEPTION,
    &&case_SPVM_BYTECODE_C_CODE_WIDE,
  };
  
  // Program counter
  register uint8_t* pc = NULL;
  
  // Runtime
  SPVM_RUNTIME* runtime = api->runtime;
  
  // Constant pool
  int32_t* constant_pool = runtime->constant_pool;
  
  // Bytecode
  uint8_t* bytecodes = runtime->bytecodes;
  
  // Variables
  SPVM_VALUE* vars = &runtime->call_stack[runtime->call_stack_base];
  
  // Call stack
  SPVM_VALUE* call_stack = runtime->call_stack;
  
  // Top position of operand stack
  register int32_t operand_stack_top = runtime->operand_stack_top;
  
  int32_t call_stack_base = runtime->call_stack_base;
  int32_t call_stack_base_start = call_stack_base;
  
  // Offten used variables
  SPVM_ARRAY* array = NULL;
  SPVM_ARRAY* array_exception = NULL;
  SPVM_OBJECT* object = NULL;
  SPVM_CONSTANT_POOL_SUB constant_pool_sub;
  int32_t index;
  int32_t success;
  
  // Goto subroutine
  goto CALLSUB_COMMON;
  
  case_SPVM_BYTECODE_C_CODE_CALL_SUB: {
    // Get subroutine ID
    sub_constant_pool_index = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
    
    CALLSUB_COMMON:
      memcpy(&constant_pool_sub, &constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));

      // Extend call stack(current size + 2(return address + call stack base before) + lexical variable area + operand_stack area)
      int32_t call_stack_max = operand_stack_top + 2 + constant_pool_sub.my_vars_length + constant_pool_sub.operand_stack_max;
      
      while (call_stack_max > runtime->call_stack_capacity) {
        runtime->call_stack_capacity = runtime->call_stack_capacity * 2;
        runtime->call_stack = call_stack = realloc(call_stack, sizeof(SPVM_VALUE) * runtime->call_stack_capacity);
      }

      operand_stack_top -= constant_pool_sub.args_length;

      // Prepare arguments
      memmove(&call_stack[operand_stack_top + 4], &call_stack[operand_stack_top + 1], constant_pool_sub.args_length * sizeof(SPVM_VALUE));
      
      // Save return address(operand + (throw or goto exception handler))
      if (call_stack_base == call_stack_base_start) {
        call_stack[operand_stack_top + 1].address_value = (uint8_t*)-1;
      }
      else {
        call_stack[operand_stack_top + 1].address_value = (uint8_t*)((intptr_t)pc + 5 + 3);
      }
      
      // Save sub_constant_pool_index
      call_stack[operand_stack_top + 2].int_value = sub_constant_pool_index;
      
      // Save vars base before
      call_stack[operand_stack_top + 3].int_value = call_stack_base;
      
      // Set vars base
      call_stack_base = operand_stack_top + 4;

      // If arg is object, increment reference count
      if (constant_pool_sub.object_args_length) {
        int32_t object_arg_indexes_constant_pool_index = constant_pool_sub.object_arg_indexes_constant_pool_index;
        int32_t object_args_length = constant_pool_sub.object_args_length;
        {
          int32_t i;
          for (i = 0; i < object_args_length; i++) {
            int32_t arg_index = constant_pool[object_arg_indexes_constant_pool_index + i];
            SPVM_BASE_OBJECT* object = (SPVM_BASE_OBJECT*)call_stack[call_stack_base + arg_index].object_value;
            if (object != NULL) {
              object->ref_count++;
            }
          }
        }
      }
      
      // Initialize my variables
      if (constant_pool_sub.my_vars_length > 0) {
        memset(&call_stack[call_stack_base + constant_pool_sub.args_length], 0, (constant_pool_sub.my_vars_length - constant_pool_sub.args_length) * sizeof(SPVM_VALUE));
      }
      
      // Set variables to local variable
      vars = &call_stack[call_stack_base];
      
      // Set operant stack top
      operand_stack_top = call_stack_base + constant_pool_sub.my_vars_length - 1;
      
      // Call native sub
      if (constant_pool_sub.is_native) {
        // Set runtimeironment
        runtime->operand_stack_top = operand_stack_top;
        runtime->call_stack_base = call_stack_base;
        
        // Call native sub
        void (*native_address)(SPVM_API* api) = constant_pool_sub.native_address;
        (*native_address)(api);
        
        // Get runtimeiromnet
        operand_stack_top = runtime->operand_stack_top;
        call_stack_base = runtime->call_stack_base;
        
        if (__builtin_expect(runtime->abort, 0)) {
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          static const void* return_jump[] = {
            &&case_SPVM_BYTECODE_C_CODE_RETURN_VOID,
            &&case_SPVM_BYTECODE_C_CODE_RETURN_BYTE,
            &&case_SPVM_BYTECODE_C_CODE_RETURN_SHORT,
            &&case_SPVM_BYTECODE_C_CODE_RETURN_INT,
            &&case_SPVM_BYTECODE_C_CODE_RETURN_LONG,
            &&case_SPVM_BYTECODE_C_CODE_RETURN_FLOAT,
            &&case_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE,
            &&case_SPVM_BYTECODE_C_CODE_RETURN_OBJECT,
          };
          
          goto *return_jump[constant_pool_sub.return_type_id + 1];
        }
      }
      // Call normal sub
      else {
        pc = &bytecodes[constant_pool_sub.bytecode_base];
      }
      goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_RETURN_BYTE:
  case_SPVM_BYTECODE_C_CODE_RETURN_SHORT:
  case_SPVM_BYTECODE_C_CODE_RETURN_INT:
  case_SPVM_BYTECODE_C_CODE_RETURN_LONG:
  case_SPVM_BYTECODE_C_CODE_RETURN_FLOAT:
  case_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE:
  {
    // Get return value
    SPVM_VALUE return_value = call_stack[operand_stack_top];

    // Restore operand stack top
    operand_stack_top = call_stack_base - 4;
    
    // Get return address
    uint8_t* return_address = call_stack[call_stack_base - 3].address_value;
    
    // Get sub_constant_pool_index
    sub_constant_pool_index = call_stack[call_stack_base - 2].int_value;

    // Decrement object my vars reference count
    memcpy(&constant_pool_sub, &constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
    int32_t object_my_vars_length = constant_pool_sub.object_my_vars_length;
    int32_t object_my_var_indexes_constant_pool_index = constant_pool_sub.object_my_var_indexes_constant_pool_index;
    if (object_my_vars_length) {
      {
        int32_t i;
        for (i = 0; i < object_my_vars_length; i++) {
          int32_t my_var_index = constant_pool[object_my_var_indexes_constant_pool_index + i];
          SPVM_BASE_OBJECT* object = (SPVM_BASE_OBJECT*)call_stack[call_stack_base + my_var_index].object_value;
          
          if (object != NULL) {
            SPVM_RUNTIME_API_dec_ref_count(api, object);
          }
        }
      }
    }
    
    // Restore call stack base
    call_stack_base = call_stack[call_stack_base - 1].int_value;
    
    // Push return value
    operand_stack_top++;
    call_stack[operand_stack_top] = return_value;
    
    // Finish call sub
    if (__builtin_expect(call_stack_base == call_stack_base_start, 0)) {
      runtime->call_stack_base = call_stack_base;
      runtime->operand_stack_top = operand_stack_top;
      runtime->abort = 0;
      return;
    }
    else {
      // Restore vars
      vars = &call_stack[call_stack_base];
      
      pc = return_address;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_RETURN_OBJECT: {
    
    // Get return value
    SPVM_BASE_OBJECT* return_value = call_stack[operand_stack_top].object_value;
    
    // Restore operand stack top
    operand_stack_top = call_stack_base - 4;
    
    // Get return address
    uint8_t* return_address = call_stack[call_stack_base - 3].address_value;
    
    // Get sub_constant_pool_index
    sub_constant_pool_index = call_stack[call_stack_base - 2].int_value;

    // Increment ref count of return value not to release by decrement
    if (return_value != NULL) {
      return_value->ref_count++;
    }
    
    // Decrement object my vars reference count
    memcpy(&constant_pool_sub, &constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
    int32_t object_my_vars_length = constant_pool_sub.object_my_vars_length;
    int32_t object_my_var_indexes_constant_pool_index = constant_pool_sub.object_my_var_indexes_constant_pool_index;
    if (object_my_vars_length) {
      {
        int32_t i;
        for (i = 0; i < object_my_vars_length; i++) {
          int32_t my_var_index = constant_pool[object_my_var_indexes_constant_pool_index + i];
          SPVM_BASE_OBJECT* object = (SPVM_BASE_OBJECT*)call_stack[call_stack_base + my_var_index].object_value;
          
          if (object != NULL) {
            SPVM_RUNTIME_API_dec_ref_count(api, object);
          }
        }
      }
    }

    // Increment ref count of return value not to release by decrement
    if (return_value != NULL) {
      return_value->ref_count--;
    }
    
    // Restore call stack base
    call_stack_base = call_stack[call_stack_base - 1].int_value;
    
    // Push return value
    operand_stack_top++;
    call_stack[operand_stack_top].object_value = return_value;
    
    // Finish call sub
    if (__builtin_expect(call_stack_base == call_stack_base_start, 0)) {
      runtime->call_stack_base = call_stack_base;
      runtime->operand_stack_top = operand_stack_top;
      runtime->abort = 0;
      return;
    }
    else {
      // Restore vars
      vars = &call_stack[call_stack_base];
      
      pc = return_address;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_RETURN_VOID: {
    
    // Restore operand stack top
    operand_stack_top = call_stack_base - 4;
    
    // Return address
    uint8_t* return_address = call_stack[call_stack_base - 3].address_value;

    // Get sub_constant_pool_index
    sub_constant_pool_index = call_stack[call_stack_base - 2].int_value;

    // Decrement object my vars reference count
    memcpy(&constant_pool_sub, &constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
    int32_t object_my_vars_length = constant_pool_sub.object_my_vars_length;
    int32_t object_my_var_indexes_constant_pool_index = constant_pool_sub.object_my_var_indexes_constant_pool_index;
    if (object_my_vars_length) {
      {
        int32_t i;
        for (i = 0; i < object_my_vars_length; i++) {
          int32_t my_var_index = constant_pool[object_my_var_indexes_constant_pool_index + i];
          SPVM_BASE_OBJECT* object = (SPVM_BASE_OBJECT*)call_stack[call_stack_base + my_var_index].object_value;
          
          if (object != NULL) {
            SPVM_RUNTIME_API_dec_ref_count(api, object);
          }
        }
      }
    }
    
    // Restore vars base
    call_stack_base = call_stack[call_stack_base - 1].int_value;
    
    // Finish call sub
    if (__builtin_expect(call_stack_base == call_stack_base_start, 0)) {
      runtime->call_stack_base = call_stack_base;
      runtime->operand_stack_top = operand_stack_top;
      runtime->abort = 0;
      return;
    }
    else {
      // Restore vars
      vars = &call_stack[call_stack_base];

      pc = return_address;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_LOAD_EXCEPTION: {
    operand_stack_top++;
    call_stack[operand_stack_top].object_value = (SPVM_BASE_OBJECT*)runtime->exception;
    pc++;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_STORE_EXCEPTION: {
    
    SPVM_RUNTIME_API_set_exception(api, (SPVM_ARRAY*)call_stack[operand_stack_top].object_value);
    
    operand_stack_top--;
    
    pc++;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_DIE: {
    
    // Restore operand stack top
    operand_stack_top = call_stack_base - 4;
    
    // Return address
    uint8_t* return_address = call_stack[call_stack_base - 3].address_value;
    
    // Get sub_constant_pool_index
    sub_constant_pool_index = call_stack[call_stack_base - 2].int_value;
    
    // Decrement object my vars reference count
    memcpy(&constant_pool_sub, &constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
    int32_t object_my_vars_length = constant_pool_sub.object_my_vars_length;
    int32_t object_my_var_indexes_constant_pool_index = constant_pool_sub.object_my_var_indexes_constant_pool_index;
    if (object_my_vars_length) {
      {
        int32_t i;
        for (i = 0; i < object_my_vars_length; i++) {
          int32_t my_var_index = constant_pool[object_my_var_indexes_constant_pool_index + i];
          SPVM_BASE_OBJECT* object = (SPVM_BASE_OBJECT*)call_stack[call_stack_base + my_var_index].object_value;
          
          if (object != NULL) {
            SPVM_RUNTIME_API_dec_ref_count(api, object);
          }
        }
      }
    }
    
    // Get constant pool sub
    memcpy(&constant_pool_sub, &constant_pool[sub_constant_pool_index], sizeof(SPVM_CONSTANT_POOL_SUB));
    
    // Sub name
    int32_t sub_name_constant_pool_index = constant_pool_sub.abs_name_constant_pool_index;
    const char* sub_name = (char*)&constant_pool[sub_name_constant_pool_index + 1];
    
    // File name
    int32_t file_name_constant_pool_index = constant_pool_sub.file_name_constant_pool_index;
    const char* file_name = (char*)&constant_pool[file_name_constant_pool_index + 1];
    
    // stack trace strings
    const char* from = "\n  from ";
    const char* at = " at ";
    
    // Total string length
    int32_t total_length = 0;
    total_length += SPVM_RUNTIME_API_get_array_length(api, runtime->exception);
    total_length += strlen(from);
    total_length += strlen(sub_name);
    total_length += strlen(at);
    total_length += strlen(file_name);
    
    // Create exception message
    SPVM_ARRAY* new_array_exception = SPVM_RUNTIME_API_malloc_byte_array_noinc(api, total_length);
    memcpy(
      (void*)((intptr_t)new_array_exception + sizeof(SPVM_ARRAY)),
      (void*)((intptr_t)runtime->exception + sizeof(SPVM_ARRAY)),
      SPVM_RUNTIME_API_get_array_length(api, runtime->exception)
    );
    sprintf(
      (char*)((intptr_t)new_array_exception + sizeof(SPVM_ARRAY) + SPVM_RUNTIME_API_get_array_length(api, runtime->exception)),
      "%s%s%s%s",
      from,
      sub_name,
      at,
      file_name
    );
    
    // Restore vars base
    call_stack_base = call_stack[call_stack_base - 1].int_value;
    
    // Set exception
    SPVM_RUNTIME_API_set_exception(api, new_array_exception);
    
    // Abort
    runtime->abort = 1;
    
    // Finish call sub with exception
    if (call_stack_base == call_stack_base_start) {
      runtime->call_stack_base = call_stack_base;
      runtime->operand_stack_top = operand_stack_top;
      return;
    }
    else {
      // Restore vars
      vars = &call_stack[call_stack_base];
      
      pc = (uint8_t*)((intptr_t)return_address - 3);
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_NOP:
    // Not used
    assert(0);
  case_SPVM_BYTECODE_C_CODE_UNDEF:
    operand_stack_top++;
    call_stack[operand_stack_top].object_value = (void*)NULL;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_BYTE_0:
    // Currently no used logic
    assert(0);
    
    operand_stack_top++;
    call_stack[operand_stack_top].byte_value = 0;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_BYTE_1:
    // Currently no used logic
    assert(0);
    
    operand_stack_top++;
    call_stack[operand_stack_top].byte_value = 1;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_SHORT_0:
    // Currently no used logic
    assert(0);
    
    operand_stack_top++;
    call_stack[operand_stack_top].short_value = 0;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_SHORT_1:
    // Currently no used logic
    assert(0);
    
    operand_stack_top++;
    call_stack[operand_stack_top].short_value = 1;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_M1:
    operand_stack_top++;
    call_stack[operand_stack_top].int_value = -1;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_0:
    operand_stack_top++;
    call_stack[operand_stack_top].int_value = 0;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_1:
    operand_stack_top++;
    call_stack[operand_stack_top].int_value = 1;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_2:
    operand_stack_top++;
    call_stack[operand_stack_top].int_value = 2;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_3:
    operand_stack_top++;
    call_stack[operand_stack_top].int_value = 3;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_4:
    operand_stack_top++;
    call_stack[operand_stack_top].int_value = 4;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_5:
    operand_stack_top++;
    call_stack[operand_stack_top].int_value = 5;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_M1:
    operand_stack_top++;
    call_stack[operand_stack_top].long_value = -1L;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_0:
    operand_stack_top++;
    call_stack[operand_stack_top].long_value = 0L;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_1:
    operand_stack_top++;
    call_stack[operand_stack_top].long_value = 1L;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_2:
    
    operand_stack_top++;
    call_stack[operand_stack_top].long_value = 2L;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_3:
    operand_stack_top++;
    call_stack[operand_stack_top].long_value = 3L;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_4:
    operand_stack_top++;
    call_stack[operand_stack_top].long_value = 4L;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_5:
    operand_stack_top++;
    call_stack[operand_stack_top].long_value = 5L;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_0:
    operand_stack_top++;
    call_stack[operand_stack_top].float_value = 0.F;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_1:
    operand_stack_top++;
    call_stack[operand_stack_top].float_value = 1.F;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_2:
    operand_stack_top++;
    call_stack[operand_stack_top].float_value = 2.F;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_DOUBLE_0:
    operand_stack_top++;
    call_stack[operand_stack_top].double_value = 0.0;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONSTANT_DOUBLE_1:
    operand_stack_top++;
    call_stack[operand_stack_top].double_value = 1.0;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_BYTE:
    operand_stack_top++;
    call_stack[operand_stack_top].byte_value = (int8_t)*(pc + 1);
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_SHORT:
    operand_stack_top++;
    call_stack[operand_stack_top].short_value = (int16_t)(int8_t)*(pc + 1);
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_SHORT:
    operand_stack_top++;
    call_stack[operand_stack_top].short_value = (int16_t)((*(pc + 1) << 8) +  *(pc + 2));
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_INT:
    operand_stack_top++;
    call_stack[operand_stack_top].int_value = (int32_t)(int8_t)*(pc + 1);
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_LONG:
    operand_stack_top++;
    call_stack[operand_stack_top].long_value = (int64_t)(int16_t)((*(pc + 1) << 8) +  *(pc + 2));
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_LONG:
    operand_stack_top++;
    call_stack[operand_stack_top].long_value = (int64_t)(int8_t)*(pc + 1);
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_INT:
    operand_stack_top++;
    call_stack[operand_stack_top].int_value = (int32_t)(int16_t)((*(pc + 1) << 8) +  *(pc + 2));
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD_CONSTANT:
    operand_stack_top++;
    memcpy(&call_stack[operand_stack_top], &constant_pool[(*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4)], sizeof(int32_t));
    pc += 5;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD_CONSTANT2:
    operand_stack_top++;
    memcpy(&call_stack[operand_stack_top], &constant_pool[(*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4)], sizeof(int64_t));
    pc += 5;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD:
    operand_stack_top++;
    call_stack[operand_stack_top] = vars[*(pc + 1)];
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD_0:
    operand_stack_top++;
    call_stack[operand_stack_top] = vars[0];
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD_1:
    operand_stack_top++;
    call_stack[operand_stack_top] = vars[1];
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD_2:
    operand_stack_top++;
    call_stack[operand_stack_top] = vars[2];
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD_3:
    operand_stack_top++;
    call_stack[operand_stack_top] = vars[3];
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 1].object_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of byte to get the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of byte to get the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].byte_value
          = *(int8_t*)((intptr_t)array + sizeof(SPVM_ARRAY) + sizeof(int8_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 1].object_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of short to get the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of short to get the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].short_value
          = *(int16_t*)((intptr_t)array + sizeof(SPVM_ARRAY) + sizeof(int16_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 1].object_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of int to get the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of int to get the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].int_value = *(int32_t*)((intptr_t)array + sizeof(SPVM_ARRAY) + sizeof(int32_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 1].object_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of long to get the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of long to get the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].long_value = *(int64_t*)((intptr_t)array + sizeof(SPVM_ARRAY) + sizeof(int64_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 1].object_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of float to get the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of float to get the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].float_value = *(float*)((intptr_t)array + sizeof(SPVM_ARRAY) + sizeof(float) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 1].object_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of double to get the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of double to get the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].double_value = *(double*)((intptr_t)array + sizeof(SPVM_ARRAY) + sizeof(double) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_OBJECT:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 1].object_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of reference to get the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of reference to get the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].object_value = *(void**)((intptr_t)array + sizeof(SPVM_ARRAY) + sizeof(void*) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 2].object_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of byte to set the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of byte to set the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int8_t*)((intptr_t)call_stack[operand_stack_top - 2].object_value + sizeof(SPVM_ARRAY) + sizeof(int8_t) * call_stack[operand_stack_top - 1].int_value)
          = call_stack[operand_stack_top].byte_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 2].object_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of short to set the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of short to set the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int16_t*)((intptr_t)call_stack[operand_stack_top - 2].object_value + sizeof(SPVM_ARRAY) + sizeof(int16_t) * call_stack[operand_stack_top - 1].int_value)
          = call_stack[operand_stack_top].short_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 2].object_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of int to set the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of int to set the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int32_t*)((intptr_t)array + sizeof(SPVM_ARRAY) + sizeof(int32_t) * index) = call_stack[operand_stack_top].int_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 2].object_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of long to set the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of int to set the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int64_t*)((intptr_t)array + sizeof(SPVM_ARRAY) + sizeof(int64_t) * index) = call_stack[operand_stack_top].long_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 2].object_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of float to set the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of float to set the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(float*)((intptr_t)array + sizeof(SPVM_ARRAY) + sizeof(float) * index) = call_stack[operand_stack_top - 1].float_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE:
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 2].object_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of double to set the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of double to set the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(double*)((intptr_t)call_stack[operand_stack_top - 2].object_value + sizeof(SPVM_ARRAY) + sizeof(double) * call_stack[operand_stack_top - 1].int_value)
          = call_stack[operand_stack_top].double_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_OBJECT: {
    array = (SPVM_ARRAY*)call_stack[operand_stack_top - 2].object_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The array of reference to set the element must not be undef");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The index of the array of reference to set the element is out of range");
        SPVM_RUNTIME_API_set_exception(api, array_exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        SPVM_BASE_OBJECT** base_object_address = (SPVM_BASE_OBJECT**)((intptr_t)array + sizeof(SPVM_ARRAY) + sizeof(void*) * index);
        
        // Increment reference count
        if (call_stack[operand_stack_top].object_value != NULL) {
          call_stack[operand_stack_top].object_value->ref_count++;
        }
        
        // Decrement reference count
        if (*base_object_address != NULL) {
          SPVM_RUNTIME_API_dec_ref_count(api, *base_object_address);
        }
        
        // Store address
        *base_object_address = call_stack[operand_stack_top].object_value;
        
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_STORE:
    vars[*(pc + 1)] = call_stack[operand_stack_top];
    operand_stack_top--;
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_STORE_0:
    vars[0] = call_stack[operand_stack_top];
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_STORE_1:
    vars[1] = call_stack[operand_stack_top];
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_STORE_2:
    vars[2] = call_stack[operand_stack_top];
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_STORE_3:
    vars[3] = call_stack[operand_stack_top];
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_STORE_OBJECT:
    index = *(pc + 1);
    
    // Decrement reference count
    if (vars[index].object_value != NULL) {
      SPVM_RUNTIME_API_dec_ref_count(api, vars[index].object_value);
    }
    
    // Store object
    vars[index].object_value = call_stack[operand_stack_top].object_value;
    
    // Increment new value reference count
    if (vars[index].object_value != NULL) {
      vars[index].object_value->ref_count++;
    }
    
    operand_stack_top--;
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_POP:
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_ADD_BYTE:
    call_stack[operand_stack_top - 1].byte_value += call_stack[operand_stack_top].byte_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_ADD_SHORT:
    call_stack[operand_stack_top - 1].short_value += call_stack[operand_stack_top].short_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_ADD_INT:
    call_stack[operand_stack_top - 1].int_value += call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_ADD_LONG:
    call_stack[operand_stack_top - 1].long_value += call_stack[operand_stack_top].long_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_ADD_FLOAT:
    call_stack[operand_stack_top - 1].float_value += call_stack[operand_stack_top].float_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_ADD_DOUBLE:
    call_stack[operand_stack_top - 1].double_value += call_stack[operand_stack_top].double_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_SUBTRACT_BYTE:
    call_stack[operand_stack_top - 1].byte_value -= call_stack[operand_stack_top].byte_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_SUBTRACT_SHORT:
    call_stack[operand_stack_top - 1].short_value -= call_stack[operand_stack_top].short_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_SUBTRACT_INT:
    call_stack[operand_stack_top - 1].int_value -= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_SUBTRACT_LONG:
    call_stack[operand_stack_top - 1].long_value -= call_stack[operand_stack_top].long_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_SUBTRACT_FLOAT:
    call_stack[operand_stack_top - 1].float_value -= call_stack[operand_stack_top].float_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_SUBTRACT_DOUBLE:
    call_stack[operand_stack_top - 1].double_value -= call_stack[operand_stack_top].double_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_MULTIPLY_BYTE:
    call_stack[operand_stack_top - 1].byte_value *= call_stack[operand_stack_top].byte_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_MULTIPLY_SHORT:
    call_stack[operand_stack_top - 1].short_value *= call_stack[operand_stack_top].short_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_MULTIPLY_INT:
    call_stack[operand_stack_top - 1].int_value *= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_MULTIPLY_LONG:
    call_stack[operand_stack_top - 1].long_value *= call_stack[operand_stack_top].long_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_MULTIPLY_FLOAT:
    call_stack[operand_stack_top - 1].float_value *= call_stack[operand_stack_top].float_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_MULTIPLY_DOUBLE:
    call_stack[operand_stack_top - 1].double_value *= call_stack[operand_stack_top].double_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_DIVIDE_BYTE:
    call_stack[operand_stack_top - 1].byte_value /= call_stack[operand_stack_top].byte_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_DIVIDE_SHORT:
    call_stack[operand_stack_top - 1].short_value /= call_stack[operand_stack_top].short_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_DIVIDE_INT:
    call_stack[operand_stack_top - 1].int_value /= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_DIVIDE_LONG:
    call_stack[operand_stack_top - 1].long_value /= call_stack[operand_stack_top].long_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_DIVIDE_FLOAT:
    call_stack[operand_stack_top - 1].float_value /= call_stack[operand_stack_top].float_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_DIVIDE_DOUBLE:
    call_stack[operand_stack_top - 1].double_value /= call_stack[operand_stack_top].double_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_REMAINDER_BYTE:
    call_stack[operand_stack_top - 1].byte_value
      = call_stack[operand_stack_top - 1].byte_value % call_stack[operand_stack_top].byte_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_REMAINDER_SHORT:
    call_stack[operand_stack_top - 1].short_value
      = call_stack[operand_stack_top - 1].short_value % call_stack[operand_stack_top].short_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_REMAINDER_INT:
    call_stack[operand_stack_top - 1].int_value
      = call_stack[operand_stack_top - 1].int_value % call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_REMAINDER_LONG:
    // z = a - (a/b) * b;
    call_stack[operand_stack_top - 1].long_value
      = call_stack[operand_stack_top - 1].long_value % call_stack[operand_stack_top].long_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_REMAINDER_FLOAT:
    call_stack[operand_stack_top - 1].float_value
      = (float)fmod((double)call_stack[operand_stack_top - 1].float_value, (double)call_stack[operand_stack_top].float_value);
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_REMAINDER_DOUBLE:
    call_stack[operand_stack_top - 1].double_value
      = fmod(call_stack[operand_stack_top - 1].double_value, call_stack[operand_stack_top].double_value);
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_NEGATE_BYTE:
    call_stack[operand_stack_top].byte_value = -call_stack[operand_stack_top].byte_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_NEGATE_SHORT:
    call_stack[operand_stack_top].short_value = -call_stack[operand_stack_top].short_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_NEGATE_INT:
    call_stack[operand_stack_top].int_value = -call_stack[operand_stack_top].int_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_NEGATE_LONG:
    call_stack[operand_stack_top].long_value = -call_stack[operand_stack_top].long_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_NEGATE_FLOAT:
    call_stack[operand_stack_top].float_value = -call_stack[operand_stack_top].float_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_NEGATE_DOUBLE:
    call_stack[operand_stack_top].double_value = -call_stack[operand_stack_top].double_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_BYTE:
    call_stack[operand_stack_top - 1].byte_value <<= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_SHORT:
    call_stack[operand_stack_top - 1].short_value <<= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_INT:
    call_stack[operand_stack_top - 1].int_value <<= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_LONG:
    call_stack[operand_stack_top - 1].long_value <<= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_BYTE:
    call_stack[operand_stack_top - 1].byte_value >>= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_SHORT:
    call_stack[operand_stack_top - 1].short_value >>= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_INT:
    call_stack[operand_stack_top - 1].int_value >>= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_LONG:
    call_stack[operand_stack_top - 1].long_value >>= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE:
    call_stack[operand_stack_top - 1].byte_value
      = (int8_t)(((uint8_t)call_stack[operand_stack_top - 1].byte_value) >> call_stack[operand_stack_top].int_value);
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT:
    call_stack[operand_stack_top - 1].short_value
      = (int16_t)(((uint16_t)call_stack[operand_stack_top - 1].short_value) >> call_stack[operand_stack_top].int_value);
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
    call_stack[operand_stack_top - 1].int_value
      = (int32_t)(((uint32_t)call_stack[operand_stack_top - 1].int_value) >> call_stack[operand_stack_top].int_value);
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
    call_stack[operand_stack_top - 1].long_value
      = (int64_t)(((uint64_t)call_stack[operand_stack_top - 1].long_value) >> call_stack[operand_stack_top].int_value);
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_AND_BYTE:
    call_stack[operand_stack_top - 1].byte_value &= call_stack[operand_stack_top].byte_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_AND_SHORT:
    call_stack[operand_stack_top - 1].short_value &= call_stack[operand_stack_top].short_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_AND_INT:
    call_stack[operand_stack_top - 1].int_value &= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_AND_LONG:
    call_stack[operand_stack_top - 1].long_value &= call_stack[operand_stack_top].long_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_OR_BYTE:
    call_stack[operand_stack_top - 1].byte_value |= call_stack[operand_stack_top].byte_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_OR_SHORT:
    call_stack[operand_stack_top - 1].short_value |= call_stack[operand_stack_top].short_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_OR_INT:
    call_stack[operand_stack_top - 1].int_value |= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_OR_LONG:
    call_stack[operand_stack_top - 1].long_value |= call_stack[operand_stack_top].long_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_XOR_BYTE:
    call_stack[operand_stack_top - 1].byte_value ^= call_stack[operand_stack_top].byte_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_XOR_SHORT:
    call_stack[operand_stack_top - 1].short_value ^= call_stack[operand_stack_top].short_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_XOR_INT:
    call_stack[operand_stack_top - 1].int_value ^= call_stack[operand_stack_top].int_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_BIT_XOR_LONG:
    call_stack[operand_stack_top - 1].long_value ^= call_stack[operand_stack_top].long_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_INC_BYTE:
    vars[*(pc + 1)].byte_value += (int8_t)*(pc + 2);
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_INC_SHORT:
    vars[*(pc + 1)].short_value += (int8_t)*(pc + 2);
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_INC_INT:
    vars[*(pc + 1)].int_value += (int8_t)*(pc + 2);
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_INC_LONG:
    vars[*(pc + 1)].long_value += (int8_t)*(pc + 2);
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_LONG:
    call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].int_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_FLOAT:
    call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].int_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_DOUBLE:
    call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].int_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_INT:
    call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].long_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_FLOAT:
    call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].long_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_DOUBLE:
    call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].long_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_INT:
    call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].float_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_LONG:
    call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].float_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE:
    call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].float_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_INT:
    call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].double_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_LONG:
    call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].double_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT:
    call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].double_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_BYTE:
    call_stack[operand_stack_top].byte_value = (int8_t)(call_stack[operand_stack_top].int_value);
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_SHORT:
    call_stack[operand_stack_top].short_value = (int16_t)(call_stack[operand_stack_top].int_value);
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_INT:
    call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].byte_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_INT:
    call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].short_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_LONG:
    call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].byte_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_FLOAT:
    call_stack[operand_stack_top - 1].float_value = (float)call_stack[operand_stack_top].byte_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_DOUBLE:
    call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].byte_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_BYTE:
    call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].short_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_LONG:
    call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].short_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_FLOAT:
    call_stack[operand_stack_top - 1].float_value = (float)call_stack[operand_stack_top].short_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_DOUBLE:
    call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].short_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_BYTE:
    call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].long_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_SHORT:
    call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top].long_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_BYTE:
    // TODO
    call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top - 1].float_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_SHORT:
    // TODO
    call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top - 1].float_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_BYTE:
    // TODO
    call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].double_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_SHORT:
    // TODO
    call_stack[operand_stack_top].byte_value = (int16_t)call_stack[operand_stack_top].double_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_SHORT:
    call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top].byte_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_BYTE:
    // z = (x > y) + (x < y) * -1
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].byte_value > call_stack[operand_stack_top].byte_value)
      + (call_stack[operand_stack_top - 1].byte_value < call_stack[operand_stack_top].byte_value) * -1;
    
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_SHORT:
    // z = (x > y) + (x < y) * -1
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].short_value > call_stack[operand_stack_top].short_value)
      + (call_stack[operand_stack_top - 1].short_value < call_stack[operand_stack_top].short_value) * -1;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_LONG:
    // z = (x > y) + (x < y) * -1
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].long_value > call_stack[operand_stack_top].long_value)
      + (call_stack[operand_stack_top - 1].long_value < call_stack[operand_stack_top].long_value) * -1;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_FLOAT_L:
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].float_value > call_stack[operand_stack_top].float_value)
      + (call_stack[operand_stack_top - 1].float_value < call_stack[operand_stack_top].float_value) * -1
      + -!!(
        isnan(call_stack[operand_stack_top - 1].float_value)
        | isnan(call_stack[operand_stack_top - 1].float_value)
      );
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_FLOAT_G:
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].float_value > call_stack[operand_stack_top].float_value)
      + (call_stack[operand_stack_top - 1].float_value < call_stack[operand_stack_top].float_value) * -1
      + !!(
        isnan(call_stack[operand_stack_top - 1].float_value)
        | isnan(call_stack[operand_stack_top - 1].float_value)
      );
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_DOUBLE_L:
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].double_value > call_stack[operand_stack_top].double_value)
      + (call_stack[operand_stack_top - 1].double_value < call_stack[operand_stack_top].double_value) * -1
      + -!!(
        isnan(call_stack[operand_stack_top - 1].double_value)
        | isnan(call_stack[operand_stack_top].double_value)
      );
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_DOUBLE_G:
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].double_value > call_stack[operand_stack_top].double_value)
      + (call_stack[operand_stack_top - 1].double_value < call_stack[operand_stack_top].double_value) * -1
      + !!(
        isnan(call_stack[operand_stack_top - 1].double_value)
        | isnan(call_stack[operand_stack_top].double_value)
      );
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_EQ_ZERO:
    success = call_stack[operand_stack_top].int_value == 0;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top--;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_NE_ZERO:
    success = call_stack[operand_stack_top].int_value != 0;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top--;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_LT_ZERO:
    success = call_stack[operand_stack_top].int_value < 0;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top--;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_GE_ZERO:
    success = call_stack[operand_stack_top].int_value >= 0;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top--;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_GT_ZERO:
    success = call_stack[operand_stack_top].int_value > 0;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top--;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_LE_ZERO:
    success = call_stack[operand_stack_top].int_value <= 0;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top--;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_EQ_CMP:
    success = call_stack[operand_stack_top - 1].int_value == call_stack[operand_stack_top].int_value;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top -= 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_NE_CMP:
    success = call_stack[operand_stack_top - 1].int_value != call_stack[operand_stack_top].int_value;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top -= 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_LT_CMP:
    success = call_stack[operand_stack_top - 1].int_value < call_stack[operand_stack_top].int_value;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top -= 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_GE_CMP:
    success = call_stack[operand_stack_top - 1].int_value >= call_stack[operand_stack_top].int_value;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top -= 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_GT_CMP:
    success = call_stack[operand_stack_top - 1].int_value > call_stack[operand_stack_top].int_value;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top -= 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_LE_CMP:
    success = call_stack[operand_stack_top - 1].int_value <= call_stack[operand_stack_top].int_value;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top -= 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_EQ_CMP_OBJECT:
    success = call_stack[operand_stack_top - 1].object_value == call_stack[operand_stack_top].object_value;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top -= 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_NE_CMP_OBJECT:
    success = call_stack[operand_stack_top - 1].object_value != call_stack[operand_stack_top].object_value;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top -= 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_GOTO:
    pc += (int16_t)((*(pc + 1) << 8) +  *(pc + 2));
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_TABLE_SWITCH: {
    // Padding
    int32_t padding = (sizeof(int32_t) - 1) - ((intptr_t)pc % sizeof(int32_t));
    
    // default offset
    int32_t default_offset = *(int32_t*)(pc + padding + 1);
    
    // min
    int32_t min = *(int32_t*)(pc + padding + sizeof(int32_t) + 1);
    
    // max
    int32_t max = *(int32_t*)(pc + padding + sizeof(int32_t) * 2 + 1);
    
    if (call_stack[operand_stack_top].int_value >= min && call_stack[operand_stack_top].int_value <= max) {
      int32_t branch_offset
        = *(int32_t*)((pc + padding + sizeof(int32_t) * 3 + 1) + (call_stack[operand_stack_top].int_value - min) * sizeof(int32_t));
      pc += branch_offset;
    }
    else {
      pc += default_offset;
    }
    
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_LOOKUP_SWITCH: {

    // Padding
    int32_t padding = (sizeof(int32_t) - 1) - ((intptr_t)pc % sizeof(int32_t));

    /*
    1  default
    5  npare
    9  match  13 branch // min
    17 match 21 branch
    25 match 29 branch // max
    */
    
    // default offset
    int32_t default_offset = *(int32_t*)(pc + padding + 1);
    
    // npare
    int32_t pair_count = *(int32_t*)(pc + padding + sizeof(int32_t) + 1);
    
    // min
    int32_t min = *(int32_t*)(pc + padding + sizeof(int32_t) * 2 + 1);
    
    // max
    int32_t max = *(int32_t*)(pc + padding + sizeof(int32_t) * 2 + 1 + ((pair_count - 1) * sizeof(int32_t) * 2));
    
    if (call_stack[operand_stack_top].int_value >= min && call_stack[operand_stack_top].int_value <= max) {
      // 2 branch searching
      int32_t cur_min_pos = 0;
      int32_t cur_max_pos = pair_count - 1;

      while (1) {
        if (cur_max_pos < cur_min_pos) {
          pc += default_offset;
          goto *jump[*pc];
        }
        int32_t cur_half_pos = cur_min_pos + (cur_max_pos - cur_min_pos) / 2;
        int32_t cur_half = *(int32_t*)(pc + padding + sizeof(int32_t) * 2 + 1 + (cur_half_pos * sizeof(int32_t) * 2));
        
        if (call_stack[operand_stack_top].int_value > cur_half) {
          cur_min_pos = cur_half_pos + 1;
        }
        else if (call_stack[operand_stack_top].int_value < cur_half) {
          cur_max_pos = cur_half_pos - 1;
        }
        else {
          int32_t branch_offset = *(int32_t*)(pc + padding + sizeof(int32_t) * 2 + 1 + (cur_half_pos * sizeof(int32_t) * 2) + sizeof(int32_t));
          pc += branch_offset;
          goto *jump[*pc];
        }
      }
    }
    else {
      pc += default_offset;
    }
    
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_MALLOC_OBJECT:
    // Get subroutine ID
    index = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
    
    object = SPVM_RUNTIME_API_malloc_object_noinc(api, index);

    // Memory allocation error
    if (__builtin_expect(!object, 0)) {
      // Sub name
      index = constant_pool_sub.abs_name_constant_pool_index;
      const char* sub_name = (char*)&constant_pool[index + 1];
      
      // File name
      index = constant_pool_sub.file_name_constant_pool_index;
      const char* file_name = (char*)&constant_pool[index + 1];
      
      fprintf(stderr, "Failed to allocate memory(malloc PACKAGE) from %s at %s\n", sub_name, file_name);
      abort();
    }
    
    // Push object
    operand_stack_top++;
    call_stack[operand_stack_top].object_value = (SPVM_BASE_OBJECT*)object;
    
    pc += 5;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_MALLOC_ARRAY: {
    int32_t value_type = *(pc + 1);
    
    // length
    int32_t length = call_stack[operand_stack_top].int_value;
    
    switch(value_type) {
      case SPVM_ARRAY_C_VALUE_TYPE_BYTE:
        array = SPVM_RUNTIME_API_malloc_byte_array_noinc(api, length);
        break;
      case SPVM_ARRAY_C_VALUE_TYPE_SHORT:
        array = SPVM_RUNTIME_API_malloc_short_array_noinc(api, length);
        break;
      case SPVM_ARRAY_C_VALUE_TYPE_INT:
        array = SPVM_RUNTIME_API_malloc_int_array_noinc(api, length);
        break;
      case SPVM_ARRAY_C_VALUE_TYPE_LONG:
        array = SPVM_RUNTIME_API_malloc_long_array_noinc(api, length);
        break;
      case SPVM_ARRAY_C_VALUE_TYPE_FLOAT:
        array = SPVM_RUNTIME_API_malloc_float_array_noinc(api, length);
        break;
      case SPVM_ARRAY_C_VALUE_TYPE_DOUBLE:
        array = SPVM_RUNTIME_API_malloc_double_array_noinc(api, length);
        break;
      case SPVM_ARRAY_C_VALUE_TYPE_OBJECT:
        array = SPVM_RUNTIME_API_malloc_object_array_noinc(api, length);
        break;
      default:
        assert(0);
    }
    
    // Memory allocation error
    if (!array) {
      // Error message
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "Failed to allocate memory(malloc ARRAY)");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    
    // Set array
    call_stack[operand_stack_top].object_value = (SPVM_BASE_OBJECT*)array;
    
    pc += 2;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_MALLOC_STRING:
    index = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
    
    array = SPVM_RUNTIME_API_create_array_byte_from_pv(api, (char*)&constant_pool[index + 1]);
    if (__builtin_expect(array != NULL, 1)) {
      // Set string
      operand_stack_top++;
      call_stack[operand_stack_top].object_value = (SPVM_BASE_OBJECT*)array;
      
      pc += 5;
      goto *jump[*pc];
    }
    // Memory allocation error
    else {
      // Sub name
      index = constant_pool_sub.abs_name_constant_pool_index;
      const char* sub_name = (char*)&constant_pool[index + 1];
      
      // File name
      index = constant_pool_sub.file_name_constant_pool_index;
      const char* file_name = (char*)&constant_pool[index + 1];
      
      fprintf(stderr, "Failed to allocate memory(malloc STRING) from %s at %s\n", sub_name, file_name);
      abort();
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LENGTH:
    call_stack[operand_stack_top].int_value = (int32_t)((SPVM_ARRAY*)call_stack[operand_stack_top].object_value)->length;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_WIDE:
    // iload, fload, aload, lload, dload, istore, fstore, astore, lstore, dstore, or iinc
    
    switch(*(pc + 1)) {
      case SPVM_BYTECODE_C_CODE_LOAD:
        operand_stack_top++;
        call_stack[operand_stack_top] = vars[(*(pc + 2) << 8) + *(pc + 3)];
        pc +=4;
        break;
      case SPVM_BYTECODE_C_CODE_STORE:
        vars[(*(pc + 2) << 8) + *(pc + 3)] = call_stack[operand_stack_top];
        operand_stack_top--;
        pc +=4;
        break;
      case SPVM_BYTECODE_C_CODE_STORE_OBJECT:
        index = (*(pc + 2) << 8) + *(pc + 3);
        
        // Decrement reference count
        if (vars[index].object_value != NULL) {
          SPVM_RUNTIME_API_dec_ref_count(api, vars[index].object_value);
        }
        
        // Store object
        vars[index].object_value = call_stack[operand_stack_top].object_value;
        
        // Increment new value reference count
        if (vars[index].object_value != NULL) {
          vars[index].object_value->ref_count++;
        }
        
        operand_stack_top--;
        pc +=4;
        break;
      case SPVM_BYTECODE_C_CODE_INC_BYTE:
        vars[(*(pc + 2) << 8) + *(pc + 3)].byte_value += (int8_t)((*(pc + 4) << 8) + *(pc + 5));
        pc += 6;
        break;
      case SPVM_BYTECODE_C_CODE_INC_SHORT:
        vars[(*(pc + 2) << 8) + *(pc + 3)].short_value += (int16_t)((*(pc + 4) << 8) + *(pc + 5));
        pc += 6;
        break;
      case SPVM_BYTECODE_C_CODE_INC_INT:
        vars[(*(pc + 2) << 8) + *(pc + 3)].int_value += (int32_t)((*(pc + 4) << 8) + *(pc + 5));
        pc += 6;
        break;
      case SPVM_BYTECODE_C_CODE_INC_LONG:
        vars[(*(pc + 2) << 8) + *(pc + 3)].long_value += (int64_t)((*(pc + 4) << 8) + *(pc + 5));
        pc += 6;
        break;
    }
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_NULL:
    success = call_stack[operand_stack_top].object_value == (void*)NULL;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top--;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_NON_NULL:
    success = call_stack[operand_stack_top].object_value != (void*)NULL;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top--;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to get an byte field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].byte_value
        = *(int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to get an short field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].short_value
        = *(int16_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_INT:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to get an int field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].int_value
        = *(int32_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_LONG:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to get an long field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].long_value
        = *(int64_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to get an float field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top - 1].float_value
        = *(float*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to get an double field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].double_value
        = *(double*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_OBJECT:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to get an reference field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].object_value
        = *(void**)((intptr_t)call_stack[operand_stack_top].object_value + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to set an byte field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(int8_t*)((intptr_t)object + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top].byte_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to set an short field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(int16_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top].short_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_INT:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to set an int field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(int32_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top].int_value;
      
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_LONG:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to set an long field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(int64_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top].long_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to set an float field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(float*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top - 1].float_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE: 
    object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to set an double field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(double*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top].double_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_OBJECT:
    object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      array_exception = SPVM_RUNTIME_API_create_array_byte_from_pv(api, "The object to set an reference field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, array_exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      SPVM_BASE_OBJECT** base_object_address = (SPVM_BASE_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index);
      
      // Increment reference count
      if (call_stack[operand_stack_top].object_value != NULL) {
        call_stack[operand_stack_top].object_value->ref_count++;
      }
      
      // Decrement reference count
      if (*base_object_address != NULL) {
        SPVM_RUNTIME_API_dec_ref_count(api, *base_object_address);
      }
      
      // Store object
      *base_object_address = call_stack[operand_stack_top].object_value;
      
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
}

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime) {

  // Free exception
  SPVM_RUNTIME_API_set_exception(runtime->api, NULL);
  
  // Free call stack
  free(runtime->call_stack);
  
  free(runtime->api);
  
  // Free runtime allocator
  SPVM_RUNTIME_ALLOCATOR_free(runtime, runtime->allocator);

  free(runtime);
}

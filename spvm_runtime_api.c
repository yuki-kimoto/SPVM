#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>

#include "spvm_runtime_api.h"
#include "spvm_object.h"
#include "spvm_runtime.h"
#include "spvm_runtime_allocator.h"
#include "spvm_api.h"
#include "spvm_global.h"
#include "spvm_type.h"
#include "spvm_hash.h"
#include "spvm_util_allocator.h"

#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_field.h"
#include "spvm_compiler.h"
#include "spvm_my.h"
#include "spvm_op.h"
#include "spvm_list.h"
#include "spvm_op_checker.h"
#include "spvm_basic_type.h"









static const void* SPVM_NATIVE_INTERFACE[]  = {
  SPVM_RUNTIME_API_get_array_length,
  SPVM_RUNTIME_API_get_byte_array_elements,
  SPVM_RUNTIME_API_get_short_array_elements,
  SPVM_RUNTIME_API_get_int_array_elements,
  SPVM_RUNTIME_API_get_long_array_elements,
  SPVM_RUNTIME_API_get_float_array_elements,
  SPVM_RUNTIME_API_get_double_array_elements,
  SPVM_RUNTIME_API_get_object_array_accessent,
  SPVM_RUNTIME_API_set_object_array_accessent,
  SPVM_RUNTIME_API_get_field_id,
  SPVM_RUNTIME_API_get_byte_field,
  SPVM_RUNTIME_API_get_short_field,
  SPVM_RUNTIME_API_get_int_field,
  SPVM_RUNTIME_API_get_long_field,
  SPVM_RUNTIME_API_get_float_field,
  SPVM_RUNTIME_API_get_double_field,
  SPVM_RUNTIME_API_get_object_field,
  SPVM_RUNTIME_API_set_byte_field,
  SPVM_RUNTIME_API_set_short_field,
  SPVM_RUNTIME_API_set_int_field,
  SPVM_RUNTIME_API_set_long_field,
  SPVM_RUNTIME_API_set_float_field,
  SPVM_RUNTIME_API_set_double_field,
  SPVM_RUNTIME_API_set_object_field,
  SPVM_RUNTIME_API_get_sub_id,
  SPVM_RUNTIME_API_get_sub_id_interface_method,
  SPVM_RUNTIME_API_get_class_method_sub_id,
  SPVM_RUNTIME_API_get_basic_type_id,
  SPVM_RUNTIME_API_call_void_sub,
  SPVM_RUNTIME_API_call_byte_sub,
  SPVM_RUNTIME_API_call_short_sub,
  SPVM_RUNTIME_API_call_int_sub,
  SPVM_RUNTIME_API_call_long_sub,
  SPVM_RUNTIME_API_call_float_sub,
  SPVM_RUNTIME_API_call_double_sub,
  SPVM_RUNTIME_API_call_object_sub,
  SPVM_RUNTIME_API_new_object,
  SPVM_RUNTIME_API_new_byte_array,
  SPVM_RUNTIME_API_new_short_array,
  SPVM_RUNTIME_API_new_int_array,
  SPVM_RUNTIME_API_new_long_array,
  SPVM_RUNTIME_API_new_float_array,
  SPVM_RUNTIME_API_new_double_array,
  SPVM_RUNTIME_API_new_object_array,
  SPVM_RUNTIME_API_new_multi_array,
  SPVM_RUNTIME_API_new_string,
  SPVM_RUNTIME_API_new_string_chars,
  SPVM_RUNTIME_API_get_string_length,
  SPVM_RUNTIME_API_get_exception,
  SPVM_RUNTIME_API_set_exception,
  SPVM_RUNTIME_API_get_ref_count,
  SPVM_RUNTIME_API_inc_ref_count,
  SPVM_RUNTIME_API_dec_ref_count,
  SPVM_RUNTIME_API_inc_dec_ref_count,
  SPVM_RUNTIME_API_get_objects_count,
  SPVM_RUNTIME_API_get_runtime,
  SPVM_RUNTIME_API_dec_ref_count_only,
  SPVM_RUNTIME_API_weaken,
  SPVM_RUNTIME_API_isweak,
  SPVM_RUNTIME_API_unweaken,
  SPVM_RUNTIME_API_concat,
  SPVM_RUNTIME_API_weaken_object_field,
  SPVM_RUNTIME_API_create_exception_stack_trace,
  SPVM_RUNTIME_API_check_cast,
  NULL, // object_header_byte_size
  NULL, // object_ref_count_byte_offset
  NULL, // object_basic_type_id_byte_offset
  NULL, // object_dimension_byte_offset
  NULL, // object_units_length_byte_offset
  NULL, // runtime_exception_byte_offset
};

int32_t SPVM_RUNTIME_API_check_cast(SPVM_API* api, int32_t cast_basic_type_id, int32_t cast_type_dimension, SPVM_OBJECT* object) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;
  
  return SPVM_OP_CHECKER_can_assign(compiler, cast_basic_type_id, cast_type_dimension, object->basic_type_id, object->dimension);
}

SPVM_OBJECT* SPVM_RUNTIME_API_create_exception_stack_trace(SPVM_API* api, SPVM_OBJECT* exception, int32_t sub_id, int32_t current_line) {

  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;
  
  // Constant pool sub
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;
  
  // Sub name
  const char* sub_name = sub->abs_name;
  
  // File name
  const char* file_name = sub->file_name;
  
  // stack trace strings
  const char* from = "\n  from ";
  const char* at = "() at ";

  // Exception
  int8_t* exception_bytes = api->get_byte_array_elements(api, exception);
  int32_t exception_length = api->get_array_length(api, exception);
  
  // Total string length
  int32_t total_length = 0;
  total_length += exception_length;
  total_length += strlen(from);
  total_length += strlen(sub_name);
  total_length += strlen(at);
  total_length += strlen(file_name);

  const char* line = " line ";
  char line_str[20];
  
  sprintf(line_str, "%" PRId32, current_line);
  total_length += strlen(line);
  total_length += strlen(line_str);
  
  // Create exception message
  SPVM_API_OBJECT* new_exception = api->new_string(api, NULL, total_length);
  int8_t* new_exception_bytes = api->get_byte_array_elements(api, new_exception);
  
  memcpy(
    (void*)(new_exception_bytes),
    (void*)(exception_bytes),
    exception_length
  );

  sprintf(
    (char*)new_exception_bytes + exception_length,
    "%s%s%s%s%s%" PRId32,
    from,
    sub_name,
    at,
    file_name,
    line,
    current_line
  );
  
  return new_exception;
}

void SPVM_RUNTIME_API_print(SPVM_API* api, SPVM_OBJECT* string) {
  (void)api;
  
  int8_t* bytes = api->get_byte_array_elements(api, string);
  int32_t string_length = api->get_array_length(api, string);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putchar((char)bytes[i]);
    }
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_concat(SPVM_API* api, SPVM_OBJECT* string1, SPVM_OBJECT* string2) {
  (void)api;

  if (string1 == NULL) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, ". operater left string must be defined(string . string)");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return NULL;
  }
  else if (string2 == NULL) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, ". operater right string must be defined(string . string)");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return NULL;
  }
  
  int32_t string1_length = SPVM_RUNTIME_API_get_array_length(api, string1);
  int32_t string2_length = SPVM_RUNTIME_API_get_array_length(api, string2);
  
  int32_t string3_length = string1_length + string2_length;
  SPVM_OBJECT* string3 = SPVM_RUNTIME_API_new_string(api, NULL, string3_length);
  
  int8_t* string1_bytes = SPVM_RUNTIME_API_get_byte_array_elements(api, string1);
  int8_t* string2_bytes = SPVM_RUNTIME_API_get_byte_array_elements(api, string2);
  int8_t* string3_bytes = SPVM_RUNTIME_API_get_byte_array_elements(api, string3);
  
  memcpy(string3_bytes, string1_bytes, string1_length);
  memcpy(string3_bytes + string1_length, string2_bytes, string2_length);
  
  return string3;
}

void SPVM_RUNTIME_API_free_runtime(SPVM_API* api, SPVM_RUNTIME* runtime) {
  (void)api;
  
  // Free exception
  SPVM_RUNTIME_API_set_exception(runtime->api, NULL);
  
  // Free runtime allocator
  SPVM_RUNTIME_ALLOCATOR_free(runtime, runtime->allocator);

  free(runtime);
}

SPVM_RUNTIME* SPVM_RUNTIME_API_new_runtime() {
  
  SPVM_RUNTIME* runtime = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME));
  
  // Runtime memory allocator
  runtime->allocator = SPVM_RUNTIME_ALLOCATOR_new(runtime);
  
  SPVM_API* api = (SPVM_API*)SPVM_NATIVE_INTERFACE;
  
  api->object_header_byte_size = (void*)(intptr_t)sizeof(SPVM_OBJECT);
  api->object_ref_count_byte_offset = (void*)(intptr_t)offsetof(SPVM_OBJECT, ref_count);
  api->object_basic_type_id_byte_offset = (void*)(intptr_t)offsetof(SPVM_OBJECT, basic_type_id);
  api->object_dimension_byte_offset = (void*)(intptr_t)offsetof(SPVM_OBJECT, dimension);
  api->object_units_length_byte_offset = (void*)(intptr_t)offsetof(SPVM_OBJECT, units_length);
  
  runtime->api = api;
  
  return runtime;
}

SPVM_RUNTIME* SPVM_RUNTIME_API_get_runtime() {
  
  return SPVM_GLOBAL_RUNTIME;
}

void SPVM_RUNTIME_API_set_runtime(SPVM_API* api, SPVM_RUNTIME* runtime) {
  (void)api;
  
  SPVM_GLOBAL_RUNTIME = runtime;
}

int32_t SPVM_RUNTIME_API_get_objects_count(SPVM_API* api) {
  (void)api;
  return SPVM_RUNTIME_API_get_runtime()->objects_count;
}

void SPVM_RUNTIME_API_free_weaken_back_refs(SPVM_API* api, SPVM_OBJECT* weaken_back_refs, int32_t weaken_back_refs_length) {
  
  SPVM_OBJECT** weaken_back_refs_elements = (SPVM_OBJECT**)((intptr_t)weaken_back_refs + sizeof(SPVM_OBJECT));
  
  {
    int32_t i;
    for (i = 0; i < weaken_back_refs_length; i++) {
      *(SPVM_OBJECT**)weaken_back_refs_elements[i] = NULL;
    }
  }
  
  SPVM_RUNTIME_API_dec_ref_count(api, weaken_back_refs);
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
    object->weaken_back_refs = SPVM_RUNTIME_API_new_address_array(api, 1);
    object->weaken_back_refs->ref_count++;
  }
  
  int32_t capacity = object->weaken_back_refs->units_length;
  int32_t length = object->weaken_back_refs_length;
  
  // Extend capacity
  assert(capacity >= length);
  if (length == capacity) {
    int32_t new_capacity = capacity * 2;
    SPVM_OBJECT* new_weaken_back_refs = SPVM_RUNTIME_API_new_address_array(api, new_capacity);
    new_weaken_back_refs->ref_count++;
    
    SPVM_OBJECT** weaken_back_refs_elements = (SPVM_OBJECT**)((intptr_t)object->weaken_back_refs + sizeof(SPVM_OBJECT));
    SPVM_OBJECT** new_weaken_back_refs_elements = (SPVM_OBJECT**)((intptr_t)new_weaken_back_refs + sizeof(SPVM_OBJECT));
    memcpy(new_weaken_back_refs_elements, weaken_back_refs_elements, length * sizeof(void*));
    
    // Old object become NULL
    memset(weaken_back_refs_elements, 0, length * sizeof(void*));
    
    // Free old weaken back references
    SPVM_RUNTIME_API_dec_ref_count(api, object->weaken_back_refs);
    
    object->weaken_back_refs = new_weaken_back_refs;
  }
  
  SPVM_OBJECT*** weaken_back_refs_elements = (SPVM_OBJECT***)((intptr_t)object->weaken_back_refs + sizeof(SPVM_OBJECT));
  weaken_back_refs_elements[length] = object_address;
  object->weaken_back_refs_length++;
}

int32_t SPVM_RUNTIME_API_isweak(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  int32_t isweak = (intptr_t)object & 1;
  
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
      memmove(&weaken_back_refs_elements[found_index], &weaken_back_refs_elements[found_index + 1], move_length * sizeof(SPVM_OBJECT*));
    }
  }
  object->weaken_back_refs_length--;
}

void SPVM_RUNTIME_API_set_exception(SPVM_API* api, SPVM_OBJECT* exception) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  if (runtime->exception != NULL) {
    SPVM_RUNTIME_API_dec_ref_count(api, (SPVM_OBJECT*)runtime->exception);
  }
  
  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&runtime->exception, exception);
  
  if (runtime->exception != NULL) {
    runtime->exception->ref_count++;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_get_exception(SPVM_API* api) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  return runtime->exception;
}

// Use only internal
SPVM_OBJECT* SPVM_RUNTIME_API_new_address_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Alloc length + 1. Last element value is 0 to use c string functions easily
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + ((int64_t)length + 1) * (int64_t)sizeof(void*);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  // Set array length
  object->units_length = length;
  
  object->unit_byte_size = sizeof(void*);
  
  object->category = SPVM_OBJECT_C_CATEGORY_ADDRESS_ARRAY;
  
  return object;
}

// Use only internal
SPVM_OBJECT* SPVM_RUNTIME_API_new_call_stack_object(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Alloc length + 1. Last element value is 0 to use c string functions easily
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + ((int64_t)length + 1) * (int64_t)sizeof(SPVM_API_VALUE);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  // Set array length
  object->units_length = length;
  
  object->unit_byte_size = sizeof(SPVM_API_VALUE);
  
  object->category = SPVM_OBJECT_C_CATEGORY_CALL_STACK;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_byte_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Alloc length + 1. Last element value is 0 to use c string functions easily
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + ((int64_t)length + 1) * (int64_t)sizeof(int8_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size + 1);
  
  ((int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_BYTE;
  
  // Set array length
  object->units_length = length;
  
  object->unit_byte_size = sizeof(int8_t);
  
  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_short_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Alloc length + 1. Last element value is 0 to use c string functions easily
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + ((int64_t)length + 1) * (int64_t)sizeof(int16_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((int16_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_SHORT;
  
  // Set array length
  object->units_length = length;

  object->unit_byte_size = sizeof(int16_t);

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_int_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Alloc length + 1. Last element value is 0 to use c string functions easily
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + ((int64_t)length + 1) * (int64_t)sizeof(int32_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((int32_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_INT;

  // Set array length
  object->units_length = length;

  object->unit_byte_size = sizeof(int32_t);

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_long_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Alloc length + 1. Last element value is 0 to use c string functions easily
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + ((int64_t)length + 1) * (int64_t)sizeof(int64_t);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((int64_t*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_LONG;

  // Set array length
  object->units_length = length;

  object->unit_byte_size = sizeof(int64_t);

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_float_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Alloc length + 1. Last element value is 0 to use c string functions easily
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + ((int64_t)length + 1) * (int64_t)sizeof(float);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((float*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_FLOAT;

  // Set array length
  object->units_length = length;

  object->unit_byte_size = sizeof(float);

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_double_array(SPVM_API* api, int32_t length) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Alloc length + 1. Last element value is 0 to use c string functions easily
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + ((int64_t)length + 1) * (int64_t)sizeof(double);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((double*)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_DOUBLE;
  
  // Set array length
  object->units_length = length;

  object->unit_byte_size = sizeof(double);

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_array(SPVM_API* api, int32_t basic_type_id, int32_t length) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;

  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Alloc length + 1. Last element value is 0 to use c string functions easily
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + ((int64_t)length + 1) * (int64_t)sizeof(SPVM_OBJECT*);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);

  object->basic_type_id = basic_type->id;
  object->dimension = 1;

  // Set array length
  object->units_length = length;
  
  object->unit_byte_size = sizeof(SPVM_OBJECT*);

  object->category = SPVM_OBJECT_C_CATEGORY_OBJECT_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_multi_array(SPVM_API* api, int32_t basic_type_id, int32_t dimension, int32_t length) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Alloc length + 1. Last element value is 0 to use c string functions easily
  int64_t array_byte_size = (int64_t)sizeof(SPVM_OBJECT) + ((int64_t)length + 1) * (int64_t)sizeof(SPVM_OBJECT*);
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, array_byte_size);
  
  ((SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT)))[length] = 0;
  
  object->basic_type_id = basic_type_id;
  object->dimension = dimension;
  
  // Set array length
  object->units_length = length;
  
  object->unit_byte_size = sizeof(SPVM_OBJECT*);

  object->category = SPVM_OBJECT_C_CATEGORY_OBJECT_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object(SPVM_API* api, int32_t basic_type_id) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;
  
  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);

  SPVM_OP* op_package = SPVM_HASH_search(compiler->op_package_symtable, basic_type->name, strlen(basic_type->name));
  SPVM_PACKAGE* package = op_package->uv.package;
  
  int32_t fields_length = package->op_fields->length;
  int32_t field_byte_size = sizeof(SPVM_API_VALUE);
  
  // Alloc length + 1. Last element value is 0 to use c string functions easily
  int64_t object_byte_size = (int64_t)sizeof(SPVM_OBJECT) + (int64_t)(fields_length + 1) * field_byte_size;
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_malloc_zero(api, allocator, object_byte_size);
  
  object->basic_type_id = basic_type->id;
  object->dimension = 0;

  object->units_length = fields_length;
  object->unit_byte_size = field_byte_size;

  // Object type id
  object->category = SPVM_OBJECT_C_CATEGORY_OBJECT;
  
  // Has destructor
  if (package->op_sub_destructor) {
    object->has_destructor = 1;
  }
  
  return object;
}

int32_t SPVM_RUNTIME_API_get_array_length(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  return object->units_length;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_string(SPVM_API* api, int8_t* bytes, int32_t length) {
  (void)api;

  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_byte_array(api, length);
  
  if (length > 0) {
    if (bytes == NULL) {
      memset((void*)((intptr_t)object + sizeof(SPVM_OBJECT)), 0, length);
    }
    else {
      memcpy((void*)((intptr_t)object + sizeof(SPVM_OBJECT)), (char*)bytes, length);
    }
  }

  
  int8_t* bytes2 = (int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT));

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_string_chars(SPVM_API* api, const char* chars) {
  (void)api;
  
  assert(chars);
  
  int32_t length = (int32_t)strlen(chars);
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_string(api, (int8_t*)chars, length);

  return object;
}

int32_t SPVM_RUNTIME_API_get_string_length(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;

  return object->units_length;
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

SPVM_OBJECT* SPVM_RUNTIME_API_get_object_array_accessent(SPVM_API* api, SPVM_OBJECT* object, int32_t index) {
  (void)api;
  
  SPVM_OBJECT** values = (SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT));

  assert(object);
  assert(index >= 0);
  assert(index <= object->units_length);
  
  SPVM_OBJECT* object_value = values[index];
  
  return object_value;
}

void SPVM_RUNTIME_API_set_object_array_accessent(SPVM_API* api, SPVM_OBJECT* object, int32_t index, SPVM_OBJECT* object_value) {
  (void)api;
  
  SPVM_OBJECT** values = (SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT));
  
  assert(object);
  assert(index >= 0);
  assert(index <= object->units_length);
  
  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&values[index], object_value);
}

void SPVM_RUNTIME_API_inc_dec_ref_count(SPVM_API* api, SPVM_OBJECT* object) {
  SPVM_RUNTIME_API_inc_ref_count(api, object);
  SPVM_RUNTIME_API_dec_ref_count(api, object);
}

void SPVM_RUNTIME_API_dec_ref_count_only(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  if (object != NULL) {
    assert(object->ref_count > 0);
    // Increment reference count
    object->ref_count--;
  }
}

void SPVM_RUNTIME_API_dec_ref_count(SPVM_API* api, SPVM_OBJECT* object) {
  
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
    SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
    SPVM_COMPILER* compiler = runtime->compiler;
    
    if (__builtin_expect(object->has_destructor, 0)) {
      if (object->in_destroy) {
        return;
      }
      else {
        SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, object->basic_type_id);
        SPVM_OP* op_package = SPVM_HASH_search(compiler->op_package_symtable, basic_type->name, strlen(basic_type->name));
        SPVM_PACKAGE* package = op_package->uv.package;
        
        // Call destructor
        SPVM_API_VALUE args[1];
        args[0].object_value = object;
        object->in_destroy = 1;
        SPVM_RUNTIME_API_call_void_sub(api, package->op_sub_destructor->uv.sub->id, args);
        object->in_destroy = 0;
        
        if (object->ref_count < 0) {
          printf("object reference count become minus in DESTROY()\n");
          abort();
        }
      }
    }
    
    if (object->category == SPVM_OBJECT_C_CATEGORY_OBJECT_ARRAY) {
      int32_t length = object->units_length;
      {
        int32_t i;
        for (i = 0; i < length; i++) {
          SPVM_OBJECT** object_field_address = (SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_OBJECT*) * i);
          if (*object_field_address != NULL) {
            SPVM_RUNTIME_API_dec_ref_count(api, *object_field_address);
          }
        }
      }
    }
    else if (object->category == SPVM_OBJECT_C_CATEGORY_OBJECT) {
      
      // Type
      SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, object->basic_type_id);
      SPVM_OP* op_package = SPVM_HASH_search(compiler->op_package_symtable, basic_type->name, strlen(basic_type->name));
      SPVM_PACKAGE* package = op_package->uv.package;
      
      {
        int32_t index;
        for (index = 0; index < package->object_field_ids->length; index++) {
          int32_t object_field_id = (intptr_t)SPVM_LIST_fetch(package->object_field_ids, index);
          SPVM_OBJECT** object_field_address = (SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_API_VALUE) * object_field_id);
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
      if (__builtin_expect(object->weaken_back_refs != NULL, 0)) {
        SPVM_RUNTIME_API_free_weaken_back_refs(api, object->weaken_back_refs, object->weaken_back_refs_length);
      }
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

void SPVM_RUNTIME_API_call_void_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  (void)SPVM_RUNTIME_call_sub(api, sub_id, args);
}

int8_t SPVM_RUNTIME_API_call_byte_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.byte_value;
}

int16_t SPVM_RUNTIME_API_call_short_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.short_value;
}

int32_t SPVM_RUNTIME_API_call_int_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.int_value;
}

int64_t SPVM_RUNTIME_API_call_long_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.long_value;
}

float SPVM_RUNTIME_API_call_float_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.float_value;
}

double SPVM_RUNTIME_API_call_double_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.double_value;
}

SPVM_OBJECT* SPVM_RUNTIME_API_call_object_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
  
  return return_value.object_value;
}

int32_t SPVM_RUNTIME_API_get_field_id(SPVM_API* api, SPVM_OBJECT* object, const char* name) {
  (void)api;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;
  
  // Type
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, object->basic_type_id);
  SPVM_OP* op_package = SPVM_HASH_search(compiler->op_package_symtable, basic_type->name, strlen(basic_type->name));
  
  SPVM_LIST* op_fields = op_package->uv.package->op_fields;
  
  int32_t field_id = -1;
  {
    for (field_id = 0; field_id < op_fields->length; field_id++) {
      SPVM_OP* op_field = SPVM_LIST_fetch(op_fields, field_id);
      SPVM_FIELD* field = op_field->uv.field;
      if (strcmp(name, field->op_name->uv.name) == 0) {
        return field->id;
      }
    }
  }
  
  return field_id;
}

int32_t SPVM_RUNTIME_API_get_sub_id(SPVM_API* api, const char* name) {
  (void)api;
  
  if (name == NULL) {
    return 0;
  }
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;
  
  SPVM_OP* op_sub = SPVM_HASH_search(compiler->op_sub_symtable, name, strlen(name));
  int32_t sub_id = op_sub->uv.sub->id;
  
  return sub_id;
}

int32_t SPVM_RUNTIME_API_get_sub_id_interface_method(SPVM_API* api, SPVM_OBJECT* object, int32_t decl_sub_id) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;
  
  SPVM_OP* op_sub_decl_sub = SPVM_LIST_fetch(compiler->op_subs, decl_sub_id);

  const char* method_signature = op_sub_decl_sub->uv.sub->method_signature;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, object->basic_type_id);
  SPVM_OP* op_package = SPVM_HASH_search(compiler->op_package_symtable, basic_type->name, strlen(basic_type->name));  
  SPVM_PACKAGE* package = op_package->uv.package;
  
  SPVM_SUB* sub_call_sub = SPVM_HASH_search(package->method_signature_symtable, method_signature, strlen(method_signature));
  
  return  sub_call_sub->id;
}

int32_t SPVM_RUNTIME_API_get_method_sub_id(SPVM_API* api, SPVM_OBJECT* object, const char* sub_name) {
  (void)api;
  
  if (sub_name == NULL) {
    return 0;
  }
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, object->basic_type_id);
  SPVM_OP* op_package = SPVM_HASH_search(compiler->op_package_symtable, basic_type->name, strlen(basic_type->name));
  SPVM_PACKAGE* package = op_package->uv.package;
  
  int32_t sub_id = -1;
  int32_t sub_index;
  for (sub_index = 0; sub_index < package->op_subs->length; sub_index++) {
    SPVM_OP* op_sub = SPVM_LIST_fetch(package->op_subs, sub_index);
    if (strcmp(op_sub->uv.sub->op_name->uv.name, sub_name) == 0) {
      sub_id = op_sub->uv.sub->id;
      break;
    }
  }
  
  return sub_id;
}

int32_t SPVM_RUNTIME_API_get_class_method_sub_id(SPVM_API* api, const char* package_name, const char* sub_name) {
  (void)api;
  
  if (sub_name == NULL) {
    return 0;
  }
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;
  
  SPVM_OP* op_package = SPVM_HASH_search(compiler->op_package_symtable, package_name, strlen(package_name));
  SPVM_PACKAGE* package = op_package->uv.package;
  
  int32_t sub_id = -1;
  int32_t sub_index;
  for (sub_index = 0; sub_index < package->op_subs->length; sub_index++) {
    SPVM_OP* op_sub = SPVM_LIST_fetch(package->op_subs, sub_index);
    if (strcmp(op_sub->uv.sub->op_name->uv.name, sub_name) == 0) {
      sub_id = op_sub->uv.sub->id;
      break;
    }
  }
  
  return sub_id;
}


int32_t SPVM_RUNTIME_API_get_basic_type_id(SPVM_API* api, const char* name) {
  (void)api;
  
  if (name == NULL) {
    return 0;
  }
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_HASH_search(compiler->basic_type_symtable, name, strlen(name));
  if (basic_type) {
    int32_t basic_type_id = basic_type->id;
    return basic_type_id;
  }
  else {
    return -1;
  }
}

int8_t SPVM_RUNTIME_API_get_byte_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(get_byte_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return 0;
  }
  
  int8_t value = *(int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id);
  
  return value;
}

int16_t SPVM_RUNTIME_API_get_short_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(get_short_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return 0;
  }

  int16_t value = *(int16_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id);
  
  return value;
}

int32_t SPVM_RUNTIME_API_get_int_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(get_int_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return 0;
  }

  int32_t value = *(int32_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id);
  
  return value;
}
int64_t SPVM_RUNTIME_API_get_long_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(get_long_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return 0;
  }

  int64_t value = *(int64_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id);
  
  return value;
}

float SPVM_RUNTIME_API_get_float_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(get_float_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return 0;
  }

  float value = *(float*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id);
  
  return value;
}

double SPVM_RUNTIME_API_get_double_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(get_double_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return 0;
  }

  double value = *(double*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id);
  
  return value;
}

void SPVM_RUNTIME_API_weaken_object_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {

  if (__builtin_expect(!object, 0)) {
    SPVM_OBJECT* exception = api->new_string_chars(api, "Object to weaken an object field must not be undefined.");
    api->set_exception(api, exception);
    return;
  }

  SPVM_OBJECT** object_address = (SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id);
  
  // Weaken object field
  if (*object_address != NULL) {
    SPVM_RUNTIME_API_weaken(api, object_address);
  }
  
  return;
}

SPVM_OBJECT* SPVM_RUNTIME_API_get_object_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(get_object_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return NULL;
  }

  SPVM_API_OBJECT* value = *(SPVM_API_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id);
  
  return value;
}

void SPVM_RUNTIME_API_set_byte_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, int8_t value) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(set_byte_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return;
  }

  *(int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id) = value;
}

void SPVM_RUNTIME_API_set_short_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, int16_t value) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(set_short_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return;
  }

  *(int16_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id) = value;
}

void SPVM_RUNTIME_API_set_int_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, int32_t value) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(set_int_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return;
  }

  *(int32_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id) = value;
}

void SPVM_RUNTIME_API_set_long_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, int64_t value) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(set_long_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return;
  }

  *(int64_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id) = value;
}

void SPVM_RUNTIME_API_set_float_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, float value) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(set_float_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return;
  }
  
  *(float*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id) = value;
}

void SPVM_RUNTIME_API_set_double_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, double value) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(set_double_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return;
  }

  *(double*)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id) = value;
}

void SPVM_RUNTIME_API_set_object_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_id, SPVM_OBJECT* value) {

  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_chars(api, "Object must be not undef(set_object_field).");
    SPVM_RUNTIME_API_set_exception(api, exception);
    return;
  }
  
  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + field_id), value);
}

int32_t SPVM_RUNTIME_API_get_fields_length(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, object->basic_type_id);
  SPVM_OP* op_package = SPVM_HASH_search(compiler->op_package_symtable, basic_type->name, strlen(basic_type->name));
  SPVM_PACKAGE* package = op_package->uv.package;

  int32_t length = package->op_fields->length;
  
  return length;
}


int32_t SPVM_RUNTIME_API_dump_field_names(SPVM_API* api, SPVM_OBJECT* object) {
  (void)api;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  SPVM_COMPILER* compiler = runtime->compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, object->basic_type_id);
  SPVM_OP* op_package = SPVM_HASH_search(compiler->op_package_symtable, basic_type->name, strlen(basic_type->name));
  SPVM_PACKAGE* package = op_package->uv.package;

  {
    int32_t i;
    for (i = 0; i < package->op_fields->length; i++) {
      SPVM_FIELD* field = SPVM_LIST_fetch(package->op_fields, i);
      fprintf(stderr, "%s\n", field->op_name->uv.name);
    }
  }
  
  return package->op_fields->length;
}

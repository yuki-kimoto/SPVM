#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_object.h"
#include "spvm_native.h"

#include "spvm_list.h"
#include "spvm_hash.h"

#include "spvm_util_allocator.h"
#include "spvm_runtime_allocator.h"

#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"

// Only use constant
#include "spvm_package.h"
#include "spvm_basic_type.h"
#include "spvm_type.h"

int32_t SPVM_RUNTIME_API_call_entry_point_sub(SPVM_ENV* env, const char* package_name, int32_t argc, const char *argv[]) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  // Package
  int32_t sub_id = -1;
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  if (package) {
  
    const char* sub_name = "main";
    
    SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));
    if (sub) {
      sub_id = sub->id;
    }
    else {
      fprintf(stderr, "Can't find entry point subroutine %s", sub_name);
      exit(EXIT_FAILURE);
    }
  }
  else {
    fprintf(stderr, "Can't find entry point package %s\n", package_name);
  }
  
  // Enter scope
  int32_t scope_id = env->enter_scope(env);
  
  // new byte[][args_length] object
  int32_t arg_type_basic_id = env->get_basic_type_id(env, "byte");
  void* cmd_args_obj = env->new_multi_array(env, arg_type_basic_id, 1, argc);
  
  // Set command line arguments
  for (int32_t arg_index = 0; arg_index < argc; arg_index++) {
    void* cmd_arg_obj = env->new_string(env, argv[arg_index], strlen(argv[arg_index]));
    env->set_object_array_element(env, cmd_args_obj, arg_index, cmd_arg_obj);
  }
  
  SPVM_VALUE stack[255];
  stack[0].oval = cmd_args_obj;
  
  // Run
  int32_t exception_flag = env->call_sub(env, sub_id, stack);
  
  int32_t status_code;
  if (exception_flag) {
    SPVM_RUNTIME_API_print(env, runtime->exception);
    printf("\n");
    status_code = 255;
  }
  else {
    status_code = stack[0].ival;
  }
  
  // Leave scope
  env->leave_scope(env, scope_id);
  
  return status_code;
}

int32_t SPVM_RUNTIME_API_is_array_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)env;
  
  return dimension > 0 && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_RUNTIME_API_get_width(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  int32_t is_value_type = SPVM_RUNTIME_API_is_value_type(env, basic_type_id, dimension, flag);
  
  int32_t width;
  if (is_value_type) {
    
    SPVM_RUNTIME_BASIC_TYPE* basic_type = basic_type_id >= 0 ? &runtime->basic_types[basic_type_id] : NULL;
    assert(basic_type);
    assert(basic_type->name_id >= 0);
    
    const char* basic_type_name = runtime->symbols[basic_type->name_id];
    SPVM_RUNTIME_PACKAGE* package = basic_type->package_id >= 0 ? &runtime->packages[basic_type->package_id] : NULL;
    
    assert(package);
    
    width = package->fields->length;
  }
  else {
    width = 1;
  }
  
  return width;
}

int32_t SPVM_RUNTIME_API_has_interface(SPVM_ENV* env, int32_t object_basic_type_id, int32_t object_type_dimension, int32_t interface_basic_type_id, int32_t interface_type_dimension) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;

  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object_basic_type_id >= 0 ? &runtime->basic_types[object_basic_type_id] : NULL;
  SPVM_RUNTIME_BASIC_TYPE* interface_basic_type = interface_basic_type_id >= 0 ? &runtime->basic_types[interface_basic_type_id] : NULL;

  SPVM_RUNTIME_PACKAGE* object_package = object_basic_type->package_id >= 0 ? &runtime->packages[object_basic_type->package_id] : NULL;
  SPVM_RUNTIME_PACKAGE* interface_package = interface_basic_type->package_id >= 0 ? &runtime->packages[interface_basic_type->package_id] : NULL;
  
  assert(object_package);
  assert(interface_package);
  
  assert(interface_package->subs->length == 1);
  
  SPVM_RUNTIME_SUB* sub_interface = SPVM_LIST_fetch(interface_package->subs, 0);
  
  const char* sub_interface_signature = runtime->symbols[sub_interface->signature_id];
  
  SPVM_RUNTIME_SUB* found_sub = SPVM_HASH_fetch(object_package->sub_signature_symtable, sub_interface_signature, strlen(sub_interface_signature));
  
  if (found_sub) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_RUNTIME_API_is_value_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = basic_type_id >= 0 ? &runtime->basic_types[basic_type_id] : NULL;
  
  int32_t is_value_t;
  if (dimension == 0 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = runtime->symbols[basic_type->name_id];;
    SPVM_RUNTIME_PACKAGE* package = basic_type->package_id >= 0 ? &runtime->packages[basic_type->package_id] : NULL;
    // Package
    if (package) {
      if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
        is_value_t = 1;
      }
      else {
        is_value_t = 0;
      }
    }
    // Numeric type
    else {
      is_value_t = 0;
    }
  }
  // Array
  else {
    is_value_t = 0;
  }
  
  return is_value_t;
}

int32_t SPVM_RUNTIME_API_is_object_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)env;
  
  if (dimension > 0 || ((dimension == 0 && basic_type_id > SPVM_BASIC_TYPE_C_ID_DOUBLE) && !(flag & SPVM_TYPE_C_FLAG_REF))) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_RUNTIME_API_is_ref_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)env;
  (void)dimension;
  
  return flag & SPVM_TYPE_C_FLAG_REF;
}

int32_t SPVM_RUNTIME_API_is_numeric_ref_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)env;
  
  if (dimension == 0 && (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) && (flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_RUNTIME_API_is_value_ref_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
  
  int32_t is_value_ref_type;
  if (dimension == 0 && (flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = runtime->symbols[basic_type->name_id];
    SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, basic_type_name, strlen(basic_type_name));
    // Package
    if (package) {
      if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
        is_value_ref_type = 1;
      }
      else {
        is_value_ref_type = 0;
      }
    }
    // Numeric type
    else {
      is_value_ref_type = 0;
    }
  }
  // Array
  else {
    is_value_ref_type = 0;
  }
  
  return is_value_ref_type;
}

int32_t SPVM_RUNTIME_API_enter_scope(SPVM_ENV* env) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t mortal_stack_top = runtime->mortal_stack_top;
  
  return mortal_stack_top;
}

void SPVM_RUNTIME_API_push_mortal(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object != NULL) {
    // Extend mortal stack
    if (runtime->mortal_stack_top >= runtime->mortal_stack_capacity) {
      int32_t new_mortal_stack_capacity = runtime->mortal_stack_capacity * 2;
      SPVM_OBJECT** new_mortal_stack = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(void*) * new_mortal_stack_capacity);
      memcpy(new_mortal_stack, runtime->mortal_stack, sizeof(void*) * runtime->mortal_stack_capacity);
      runtime->mortal_stack_capacity = new_mortal_stack_capacity;
      runtime->mortal_stack = new_mortal_stack;
    }
    
    runtime->mortal_stack[runtime->mortal_stack_top] = object;
    runtime->mortal_stack_top++;
    
    object->ref_count++;
  }
}

void SPVM_RUNTIME_API_leave_scope(SPVM_ENV* env, int32_t original_mortal_stack_top) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;

  int32_t mortal_stack_index;
  for (mortal_stack_index = original_mortal_stack_top; mortal_stack_index < runtime->mortal_stack_top; mortal_stack_index++) {
    SPVM_OBJECT* object = runtime->mortal_stack[mortal_stack_index];
    
    if (object != NULL) {
      if (object->ref_count > 1) {
        object->ref_count--;
      }
      else {
        SPVM_RUNTIME_API_dec_ref_count(env, object);
      }
    }
    
    runtime->mortal_stack[mortal_stack_index] = NULL;
  }
  
  runtime->mortal_stack_top = original_mortal_stack_top;
}

SPVM_OBJECT* SPVM_RUNTIME_API_create_exception_stack_trace(SPVM_ENV* env, SPVM_OBJECT* exception, const char* package_name, const char* sub_name, const char* file, int32_t line) {
  
  // stack trace symbols
  const char* from_part = "\n  from ";
  const char* arrow_part = "->";
  const char* at_part = " at ";

  // Exception
  int8_t* exception_bytes = env->get_byte_array_elements(env, exception);
  int32_t exception_length = env->get_array_length(env, exception);
  
  // Total string length
  int32_t total_length = 0;
  total_length += exception_length;
  total_length += strlen(from_part);
  total_length += strlen(package_name);
  total_length += strlen(arrow_part);
  total_length += strlen(sub_name);
  total_length += strlen(at_part);
  total_length += strlen(file);

  const char* line_part = " line ";
  char line_str[20];
  
  sprintf(line_str, "%" PRId32, line);
  total_length += strlen(line_part);
  total_length += strlen(line_str);
  
  // Create exception message
  void* new_exception = env->new_string_raw(env, NULL, total_length);
  int8_t* new_exception_bytes = env->get_byte_array_elements(env, new_exception);
  
  memcpy(
    (void*)(new_exception_bytes),
    (void*)(exception_bytes),
    exception_length
  );

  sprintf(
    (char*)new_exception_bytes + exception_length,
    "%s%s%s%s%s%s%s%" PRId32,
    from_part,
    package_name,
    arrow_part,
    sub_name,
    at_part,
    file,
    line_part,
    line
  );
  
  return new_exception;
}

void SPVM_RUNTIME_API_print(SPVM_ENV* env, SPVM_OBJECT* string) {
  (void)env;
  
  int8_t* bytes = env->get_byte_array_elements(env, string);
  int32_t string_length = env->get_array_length(env, string);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putchar((char)bytes[i]);
    }
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_concat(SPVM_ENV* env, SPVM_OBJECT* string1, SPVM_OBJECT* string2) {
  (void)env;

  int32_t string1_length = SPVM_RUNTIME_API_get_array_length(env, string1);
  int32_t string2_length = SPVM_RUNTIME_API_get_array_length(env, string2);
  
  int32_t string3_length = string1_length + string2_length;
  SPVM_OBJECT* string3 = SPVM_RUNTIME_API_new_string_raw(env, NULL, string3_length);
  
  int8_t* string1_bytes = SPVM_RUNTIME_API_get_byte_array_elements(env, string1);
  int8_t* string2_bytes = SPVM_RUNTIME_API_get_byte_array_elements(env, string2);
  int8_t* string3_bytes = SPVM_RUNTIME_API_get_byte_array_elements(env, string3);
  
  memcpy(string3_bytes, string1_bytes, string1_length);
  memcpy(string3_bytes + string1_length, string2_bytes, string2_length);
  
  return string3;
}

int32_t SPVM_RUNTIME_API_get_memory_blocks_count(SPVM_ENV* env) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  return runtime->memory_blocks_count;
}

void SPVM_RUNTIME_API_free_weaken_back_refs(SPVM_ENV* env, void** weaken_back_refs, int32_t weaken_back_refs_length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  {
    int32_t i;
    for (i = 0; i < weaken_back_refs_length; i++) {
      *(void**)weaken_back_refs[i] = NULL;
    }
  }
  
  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, weaken_back_refs);
}

void SPVM_RUNTIME_API_weaken(SPVM_ENV* env, SPVM_OBJECT** object_address) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;
  
  if (*object_address == NULL) {
    return;
  }
  
  if (SPVM_RUNTIME_API_isweak(env, *object_address)) {
    return;
  }
  
  SPVM_OBJECT* object = *object_address;
  
  // Decrelement reference count
  if (object->ref_count == 1) {
    // If reference count is 1, the object is freeed without weaken
    SPVM_RUNTIME_API_dec_ref_count(env, *object_address);
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
    object->weaken_back_refs_capacity = 1;
    object->weaken_back_refs = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(void*) * object->weaken_back_refs_capacity);
  }
  
  int32_t capacity = object->weaken_back_refs_capacity;
  int32_t length = object->weaken_back_refs_length;
  
  // Extend capacity
  assert(capacity >= length);
  if (length == capacity) {
    int32_t new_capacity = capacity * 2;
    void** new_weaken_back_refs = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(void*) * new_capacity);
    
    void** weaken_back_refs = object->weaken_back_refs;
    memcpy(new_weaken_back_refs, weaken_back_refs, length * sizeof(void*));
    
    // Old object become NULL
    memset(weaken_back_refs, 0, length * sizeof(void*));
    
    // Free old weaken back references
    SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, object->weaken_back_refs);
    
    object->weaken_back_refs = new_weaken_back_refs;
    object->weaken_back_refs_capacity = new_capacity;
  }
  
  object->weaken_back_refs[length] = object_address;
  object->weaken_back_refs_length++;
}

int32_t SPVM_RUNTIME_API_isweak(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  int32_t isweak = (intptr_t)object & 1;
  
  return isweak;
}

void SPVM_RUNTIME_API_unweaken(SPVM_ENV* env, SPVM_OBJECT** object_address) {
  (void)env;
  
  if (*object_address == NULL) {
    return;
  }
  
  if (!SPVM_RUNTIME_API_isweak(env, *object_address)) {
    return;
  }
  
  // Unweaken
  *object_address = (SPVM_OBJECT*)((intptr_t)*object_address & ~(intptr_t)1);
  
  SPVM_OBJECT* object = *object_address;
  
  // Increment reference count
  object->ref_count++;

  int32_t length = object->weaken_back_refs_length;
  
  void** weaken_back_refs = object->weaken_back_refs;
  
  {
    int32_t i;
    int32_t found_index = -1;
    for (i = 0; i < length; i++) {
      if (weaken_back_refs[i] == object_address) {
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
      memmove(&weaken_back_refs[found_index], &weaken_back_refs[found_index + 1], move_length * sizeof(void*));
    }
  }
  object->weaken_back_refs_length--;
}

void SPVM_RUNTIME_API_set_exception(SPVM_ENV* env, SPVM_OBJECT* exception) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (runtime->exception != NULL) {
    SPVM_RUNTIME_API_dec_ref_count(env, (SPVM_OBJECT*)runtime->exception);
  }
  
  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&runtime->exception, exception);
  
  if (runtime->exception != NULL) {
    runtime->exception->ref_count++;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_get_exception(SPVM_ENV* env) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  return runtime->exception;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_byte_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_byte_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_short_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_short_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_int_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_int_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_long_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_long_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_float_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_float_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_double_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_double_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_array(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_object_array_raw(env, basic_type_id, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_multi_array(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_multi_array_raw(env, basic_type_id, element_dimension, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_value_t_array(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_value_t_array_raw(env, basic_type_id, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object(SPVM_ENV* env, int32_t basic_type_id) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_object_raw(env, basic_type_id);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_pointer(SPVM_ENV* env, int32_t basic_type_id, void* pointer) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_pointer_raw(env, basic_type_id, pointer);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_string(SPVM_ENV* env, const char* bytes, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_string_raw(env, bytes, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_byte_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  // If lenght is less than 0, return NULL.
  if (length < 0) {
    return NULL;
  }
  
  // Create object
  SPVM_RUNTIME* runtime = env->runtime;
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Body byte size. Alloc length + 1
  size_t body_byte_size = (length + 1) * sizeof(SPVM_VALUE_byte);
  if (body_byte_size > SIZE_MAX) {
    return NULL;
  }
  
  // Alloc body by 0
  void* body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, body_byte_size);
  if (body == NULL) {
    return NULL;
  }
  
  // Set object fields
  object->body = body;
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_BYTE;
  object->elements_length = length;
  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_short_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_short));
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_SHORT;
  
  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_int_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_int));
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_INT;

  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_long_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (length < 0) {
    return NULL;
  }
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));
  
  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_long));
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_LONG;

  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_float_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_float));
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_FLOAT;

  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_double_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_double));
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_DOUBLE;
  
  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_object));
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];

  object->basic_type_id = basic_type->id;
  object->type_dimension = 1;

  // Set array length
  object->elements_length = length;
  
  object->category = SPVM_OBJECT_C_CATEGORY_OBJECT_ARRAY;
  
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_multi_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_object));
  
  object->basic_type_id = basic_type_id;
  object->type_dimension = element_dimension + 1;
  
  // Set array length
  object->elements_length = length;
  
  object->category = SPVM_OBJECT_C_CATEGORY_OBJECT_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_value_t_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;

  // valut_t array dimension must be 1
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
  const char* basic_type_name = runtime->symbols[basic_type->name_id];
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, basic_type_name, strlen(basic_type_name));
  int32_t fields_length = package->fields->length;
  SPVM_RUNTIME_FIELD* field_first = SPVM_LIST_fetch(package->fields, 0);
  int32_t field_basic_type_id = field_first->basic_type_id;

  int32_t unit_size;
  if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE) {
    unit_size = sizeof(int8_t);
  }
  else if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_SHORT) {
    unit_size = sizeof(int16_t);
  }
  else if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_INT) {
    unit_size = sizeof(int32_t);
  }
  else if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_LONG) {
    unit_size = sizeof(int64_t);
  }
  else if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
    unit_size = sizeof(float);
  }
  else if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
    unit_size = sizeof(double);
  }
  else {
    assert(0);
  }

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * unit_size * fields_length);

  object->basic_type_id = basic_type->id;
  object->type_dimension = 1;

  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_VALUE_T_ARRAY;

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_raw(SPVM_ENV* env, int32_t basic_type_id) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
  
  SPVM_RUNTIME_PACKAGE* package;
  if (basic_type->package_id < 0) {
    package = NULL;
  }
  else {
    package = &runtime->packages[basic_type->package_id];
  }
  if (!package) {
    return NULL;
  }

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  int32_t fields_length = package->fields->length;
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (fields_length + 1) * sizeof(SPVM_VALUE));
  
  object->basic_type_id = basic_type->id;
  object->type_dimension = 0;

  object->elements_length = fields_length;

  // Object type id
  object->category = SPVM_OBJECT_C_CATEGORY_OBJECT;
  
  // Has destructor
  if (package->destructor_sub_id >= 0) {
    object->has_destructor = 1;
  }
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_pointer_raw(SPVM_ENV* env, int32_t basic_type_id, void* pointer) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];

  SPVM_RUNTIME_PACKAGE* package;
  if (basic_type->package_id < 0) {
    package = NULL;
  }
  else {
    package = &runtime->packages[basic_type->package_id];
  }
  if (!package) {
    return NULL;
  }

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  object->body = pointer;

  object->basic_type_id = basic_type->id;
  object->type_dimension = 0;

  object->elements_length = 1;

  // Object type id
  object->category = SPVM_OBJECT_C_CATEGORY_OBJECT;
  
  // Has destructor
  if (package->destructor_sub_id >= 0) {
    object->has_destructor = 1;
  }
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_string_raw(SPVM_ENV* env, const char* bytes, int32_t length) {
  (void)env;

  if (length == 0) {
    length = strlen((char*)bytes);
  }

  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_byte_array_raw(env, length);
  
  if (length > 0) {
    if (bytes == NULL) {
      memset(object->body, 0, length);
    }
    else {
      memcpy(object->body, (char*)bytes, length);
    }
  }

  return object;
}

int32_t SPVM_RUNTIME_API_get_array_length(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return object->elements_length;
}

int8_t* SPVM_RUNTIME_API_get_byte_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;

  return *(SPVM_VALUE_byte**)&object->body;
}

int16_t* SPVM_RUNTIME_API_get_short_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return *(SPVM_VALUE_short**)&object->body;
}

int32_t* SPVM_RUNTIME_API_get_int_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return *(SPVM_VALUE_int**)&object->body;
}

int64_t* SPVM_RUNTIME_API_get_long_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return *(SPVM_VALUE_long**)&object->body;
}

float* SPVM_RUNTIME_API_get_float_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return *(SPVM_VALUE_float**)&object->body;
}

double* SPVM_RUNTIME_API_get_double_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return *(SPVM_VALUE_double**)&object->body;
}

SPVM_OBJECT* SPVM_RUNTIME_API_get_object_array_element(SPVM_ENV* env, SPVM_OBJECT* object, int32_t index) {
  (void)env;
  
  assert(object);
  assert(index >= 0);
  assert(index <= object->elements_length);
  
  SPVM_OBJECT* oval = (*(SPVM_VALUE_object**)&(*(void**)object))[index];
  
  return oval;
}

void SPVM_RUNTIME_API_set_object_array_element(SPVM_ENV* env, SPVM_OBJECT* object, int32_t index, SPVM_OBJECT* oval) {
  (void)env;
  
  void* object_address = &((*(SPVM_VALUE_object**)&(*(void**)object))[index]);
  
  assert(object);
  assert(index >= 0);
  assert(index <= object->elements_length);
  
  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_address, oval);
}

void* SPVM_RUNTIME_API_get_pointer(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return object->body;
}

void SPVM_RUNTIME_API_inc_dec_ref_count(SPVM_ENV* env, SPVM_OBJECT* object) {
  SPVM_RUNTIME_API_inc_ref_count(env, object);
  SPVM_RUNTIME_API_dec_ref_count(env, object);
}

void SPVM_RUNTIME_API_dec_ref_count_only(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  if (object != NULL) {
    assert(object->ref_count > 0);
    // Increment reference count
    object->ref_count--;
  }
}

void SPVM_RUNTIME_API_dec_ref_count(SPVM_ENV* env, SPVM_OBJECT* object) {
  
  assert(object != NULL);
  assert(object->ref_count > 0);
  
  if (object->ref_count < 1) {
    fprintf(stderr, "Found invalid reference count object(SPVM_RUNTIME_API_dec_ref_count())");
    abort();
  }
  
  // Decrement reference count
  object->ref_count--;
  
  // If reference count is zero, free address.
  if (object->ref_count == 0) {
    SPVM_RUNTIME* runtime = env->runtime;
    
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[object->basic_type_id];
    SPVM_RUNTIME_PACKAGE* package;
    if (basic_type->package_id < 0) {
      package = NULL;
    }
    else {
      package = &runtime->packages[basic_type->package_id];
    }
    int32_t is_pointer = 0;
    if (package) {
      if (package->flag & SPVM_PACKAGE_C_FLAG_IS_POINTER) {
        is_pointer = 1;
      }
    }

    if (object->category == SPVM_OBJECT_C_CATEGORY_OBJECT_ARRAY) {
      int32_t length = object->elements_length;
      {
        int32_t index;
        for (index = 0; index < length; index++) {
          SPVM_OBJECT** object_field_address = (SPVM_OBJECT**)&((*(SPVM_VALUE_object**)&(*(void**)object))[index]);
          if (*object_field_address != NULL) {
            SPVM_RUNTIME_API_dec_ref_count(env, *object_field_address);
          }
        }
      }
    }
    else if (object->category == SPVM_OBJECT_C_CATEGORY_OBJECT) {
      
      if (object->has_destructor) {
        if (object->in_destroy) {
          return;
        }
        else {
          // Call destructor
          SPVM_VALUE args[1];
          args[0].oval = object;
          object->in_destroy = 1;
          SPVM_RUNTIME_call_sub(env, package->destructor_sub_id, args);
          object->in_destroy = 0;
          
          if (object->ref_count < 0) {
            printf("object reference count become minus in DESTROY()\n");
            abort();
          }
        }
      }
      
      {
        int32_t index;
        for (index = 0; index < package->object_field_indexes->length; index++) {
          int32_t object_field_index = (intptr_t)SPVM_LIST_fetch(package->object_field_indexes, index);
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          
          SPVM_OBJECT** object_field_address = (SPVM_OBJECT**)&fields[object_field_index];
          if (*object_field_address != NULL) {
            // If object is weak, unweaken
            if (SPVM_RUNTIME_API_isweak(env, *object_field_address)) {
              SPVM_RUNTIME_API_unweaken(env, object_field_address);
            }
            else {
              SPVM_RUNTIME_API_dec_ref_count(env, *object_field_address);
            }
          }
        }
      }
      if (object->weaken_back_refs != NULL) {
        SPVM_RUNTIME_API_free_weaken_back_refs(env, object->weaken_back_refs, object->weaken_back_refs_length);
      }
    }
    
    // Free object body
    if (object->body != NULL && !is_pointer) {
      SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, object->body);
    }
    
    // Free object
    SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, object);
  }
}

void SPVM_RUNTIME_API_inc_ref_count(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  if (object != NULL) {
    assert(object->ref_count >= 0);
    // Increment reference count
    object->ref_count++;
  }
}

int32_t SPVM_RUNTIME_API_get_ref_count(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return object->ref_count;
}

int32_t SPVM_RUNTIME_API_get_field_index(SPVM_ENV* env, const char* package_name, const char* signature) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Package
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  if (!package) {
    return -1;
  }
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_HASH_fetch(package->field_signature_symtable, signature, strlen(signature));
  
  if (!field) {
    return -2;
  }
  
  int32_t field_index = field->index;
  
  return field_index;
}

int32_t SPVM_RUNTIME_API_get_package_var_id(SPVM_ENV* env, const char* package_name, const char* signature) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Package
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  if (!package) {
    return -1;
  }
  
  // Field
  SPVM_RUNTIME_PACKAGE_VAR* package_var = SPVM_HASH_fetch(package->package_var_signature_symtable, signature, strlen(signature));
  
  if (!package_var) {
    return -2;
  }
  
  int32_t package_var_id = package_var->id;
  
  return package_var_id;
}

int32_t SPVM_RUNTIME_API_get_sub_id(SPVM_ENV* env, const char* package_name, const char* sub_signature) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  if (package == NULL) {
    return -1;
  }
  
  SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_signature_symtable, sub_signature, strlen(sub_signature));
  if (sub == NULL) {
    return -1;
  }
  
  int32_t sub_id = sub->id;
  
  return sub_id;
}

int32_t SPVM_RUNTIME_API_get_sub_id_method_call(SPVM_ENV* env, SPVM_OBJECT* object, const char* sub_signature) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[object->basic_type_id];
  const char* basic_type_name = runtime->symbols[basic_type->name_id];
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, basic_type_name, strlen(basic_type_name));  
  if (package == NULL) {
    return -1;
  }
  
  SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_signature_symtable, sub_signature, strlen(sub_signature));
  if (sub == NULL) {
    return -1;
  }
  
  return sub->id;
}

int32_t SPVM_RUNTIME_API_get_basic_type_id(SPVM_ENV* env, const char* name) {
  (void)env;
  
  if (name == NULL) {
    return 0;
  }
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_HASH_fetch(runtime->basic_type_symtable, name, strlen(name));
  if (basic_type) {
    int32_t basic_type_id = basic_type->id;
    return basic_type_id;
  }
  else {
    return -1;
  }
}

int8_t SPVM_RUNTIME_API_get_byte_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  SPVM_VALUE_byte value = *(SPVM_VALUE_byte*)&fields[field_index];
  
  return value;
}

int16_t SPVM_RUNTIME_API_get_short_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  SPVM_VALUE_short value = *(SPVM_VALUE_short*)&fields[field_index];
  
  return value;
}

int32_t SPVM_RUNTIME_API_get_int_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  SPVM_VALUE_int value = *(SPVM_VALUE_int*)&fields[field_index];
  
  return value;
}

int64_t SPVM_RUNTIME_API_get_long_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  SPVM_VALUE_long value = *(SPVM_VALUE_long*)&fields[field_index];
  
  return value;
}

float SPVM_RUNTIME_API_get_float_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  SPVM_VALUE_float value = *(SPVM_VALUE_float*)&fields[field_index];
  
  return value;
}

double SPVM_RUNTIME_API_get_double_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  SPVM_VALUE_double value = *(SPVM_VALUE_double*)&fields[field_index];
  
  return value;
}

SPVM_OBJECT* SPVM_RUNTIME_API_get_object_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  
  void* value = *(SPVM_VALUE_object*)&fields[field_index];
  
  return value;
}

void SPVM_RUNTIME_API_set_byte_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int8_t value) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  *(SPVM_VALUE_byte*)&fields[field_index] = value;
}

void SPVM_RUNTIME_API_set_short_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int16_t value) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  *(SPVM_VALUE_short*)&fields[field_index] = value;
}

void SPVM_RUNTIME_API_set_int_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int32_t value) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  *(SPVM_VALUE_int*)&fields[field_index] = value;
}

void SPVM_RUNTIME_API_set_long_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int64_t value) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  *(SPVM_VALUE_long*)&fields[field_index] = value;
}

void SPVM_RUNTIME_API_set_float_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, float value) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  *(SPVM_VALUE_float*)&fields[field_index] = value;
}

void SPVM_RUNTIME_API_set_double_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, double value) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);

  *(SPVM_VALUE_double*)&fields[field_index] = value;
}

void SPVM_RUNTIME_API_set_object_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, SPVM_OBJECT* value) {

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  
  void* object_field_address = (SPVM_VALUE_object*)&fields[field_index];

  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_field_address, value);
}

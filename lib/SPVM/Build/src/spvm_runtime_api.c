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
#include "spvm_global.h"

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

static const void* SPVM_ENV_RUNTIME[]  = {
  SPVM_RUNTIME_API_get_array_length,
  SPVM_RUNTIME_API_get_byte_array_elements,
  SPVM_RUNTIME_API_get_short_array_elements,
  SPVM_RUNTIME_API_get_int_array_elements,
  SPVM_RUNTIME_API_get_long_array_elements,
  SPVM_RUNTIME_API_get_float_array_elements,
  SPVM_RUNTIME_API_get_double_array_elements,
  SPVM_RUNTIME_API_get_object_array_element,
  SPVM_RUNTIME_API_set_object_array_element,
  SPVM_RUNTIME_API_get_field_index,
  SPVM_RUNTIME_API_get_byte_field,
  SPVM_RUNTIME_API_get_short_field,
  SPVM_RUNTIME_API_get_int_field,
  SPVM_RUNTIME_API_get_long_field,
  SPVM_RUNTIME_API_get_float_field,
  SPVM_RUNTIME_API_get_double_field,
  SPVM_RUNTIME_API_get_object_field,
  SPVM_RUNTIME_API_get_pointer,
  SPVM_RUNTIME_API_set_byte_field,
  SPVM_RUNTIME_API_set_short_field,
  SPVM_RUNTIME_API_set_int_field,
  SPVM_RUNTIME_API_set_long_field,
  SPVM_RUNTIME_API_set_float_field,
  SPVM_RUNTIME_API_set_double_field,
  SPVM_RUNTIME_API_set_object_field,
  SPVM_RUNTIME_API_get_sub_id,
  SPVM_RUNTIME_API_get_sub_id_method_call,
  SPVM_RUNTIME_API_get_basic_type_id,
  SPVM_RUNTIME_API_new_object_raw,
  SPVM_RUNTIME_API_new_byte_array_raw,
  SPVM_RUNTIME_API_new_short_array_raw,
  SPVM_RUNTIME_API_new_int_array_raw,
  SPVM_RUNTIME_API_new_long_array_raw,
  SPVM_RUNTIME_API_new_float_array_raw,
  SPVM_RUNTIME_API_new_double_array_raw,
  SPVM_RUNTIME_API_new_object_array_raw,
  SPVM_RUNTIME_API_new_multi_array_raw,
  SPVM_RUNTIME_API_new_value_t_array_raw,
  SPVM_RUNTIME_API_new_string_raw,
  SPVM_RUNTIME_API_new_pointer_raw,
  SPVM_RUNTIME_API_get_exception,
  SPVM_RUNTIME_API_set_exception,
  SPVM_RUNTIME_API_get_ref_count,
  SPVM_RUNTIME_API_inc_ref_count,
  SPVM_RUNTIME_API_dec_ref_count,
  SPVM_RUNTIME_API_inc_dec_ref_count,
  SPVM_RUNTIME_API_get_memory_blocks_count,
  SPVM_RUNTIME_API_get_runtime,
  SPVM_RUNTIME_API_dec_ref_count_only,
  SPVM_RUNTIME_API_weaken,
  SPVM_RUNTIME_API_isweak,
  SPVM_RUNTIME_API_unweaken,
  SPVM_RUNTIME_API_concat,
  SPVM_RUNTIME_API_weaken_object_field,
  SPVM_RUNTIME_API_create_exception_stack_trace,
  SPVM_RUNTIME_API_check_cast,
  (void*)(intptr_t)sizeof(SPVM_OBJECT), // object_header_byte_size
  (void*)(intptr_t)offsetof(SPVM_OBJECT, ref_count), // object_ref_count_byte_offset
  (void*)(intptr_t)offsetof(SPVM_OBJECT, basic_type_id), // object_basic_type_id_byte_offset
  (void*)(intptr_t)offsetof(SPVM_OBJECT, dimension), // object_dimension_byte_offset
  (void*)(intptr_t)offsetof(SPVM_OBJECT, elements_length), // object_elements_length_byte_offset
  SPVM_RUNTIME_call_sub,
  SPVM_RUNTIME_API_enter_scope,
  SPVM_RUNTIME_API_push_mortal,
  SPVM_RUNTIME_API_leave_scope,
  SPVM_RUNTIME_API_new_object,
  SPVM_RUNTIME_API_new_byte_array,
  SPVM_RUNTIME_API_new_short_array,
  SPVM_RUNTIME_API_new_int_array,
  SPVM_RUNTIME_API_new_long_array,
  SPVM_RUNTIME_API_new_float_array,
  SPVM_RUNTIME_API_new_double_array,
  SPVM_RUNTIME_API_new_object_array,
  SPVM_RUNTIME_API_new_multi_array,
  SPVM_RUNTIME_API_new_value_t_array,
  SPVM_RUNTIME_API_new_string,
  SPVM_RUNTIME_API_new_pointer,
  SPVM_RUNTIME_API_get_package_var_id,
  (void*)(intptr_t)offsetof(SPVM_RUNTIME, package_vars_heap), // runtime_package_vars_heap_byte_offset
};

int32_t SPVM_RUNTIME_API_get_width(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  _Bool is_value_type = SPVM_RUNTIME_API_is_value_type(env, basic_type_id, dimension, flag);
  
  int32_t width;
  if (is_value_type) {
    
    SPVM_RUNTIME_BASIC_TYPE* basic_type = basic_type_id >= 0 ? SPVM_LIST_fetch(runtime->basic_types, basic_type_id) : NULL;
    assert(basic_type);
    
    const char* basic_type_name = basic_type->name;
    SPVM_RUNTIME_PACKAGE* package = basic_type->package_id >= 0 ? SPVM_LIST_fetch(runtime->packages, basic_type->package_id) : NULL;
    
    assert(package);
    
    width = package->fields->length;
  }
  else {
    width = 1;
  }
  
  return width;
}

int32_t SPVM_RUNTIME_API_is_value_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = basic_type_id >= 0 ? SPVM_LIST_fetch(runtime->basic_types, basic_type_id) : NULL;
  
  int32_t is_value_t;
  if (dimension == 0 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_RUNTIME_PACKAGE* package = basic_type->package_id >= 0 ? SPVM_LIST_fetch(runtime->packages, basic_type->package_id) : NULL;
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

SPVM_ENV* SPVM_RUNTIME_API_get_env_runtime() {
  return (SPVM_ENV*)SPVM_ENV_RUNTIME;
}

int32_t SPVM_RUNTIME_API_enter_scope(SPVM_ENV* env) {
  (void)env;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  int32_t mortal_stack_top = runtime->mortal_stack_top;
  
  return mortal_stack_top;
}

void SPVM_RUNTIME_API_push_mortal(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;

  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
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
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

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

int32_t SPVM_RUNTIME_API_has_interface(SPVM_ENV* env, SPVM_RUNTIME_PACKAGE* package, SPVM_RUNTIME_PACKAGE* interface) {
  (void)env;
  
  // When left package is interface, right package have all methods which left package have
  assert(interface->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE);
  assert(!(package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE));
  
  SPVM_LIST* subs_interface = interface->subs;
  SPVM_LIST* subs_package = package->subs;
  
  int32_t has_interface_cache = (intptr_t)SPVM_HASH_fetch(package->has_interface_cache_symtable, interface->name, strlen(interface->name));
  
  int32_t is_cached = has_interface_cache & 1;
  int32_t has_interface;
  if (is_cached) {
    has_interface = has_interface_cache & 2;
  }
  else {
    has_interface = 1;
    
    {
      int32_t sub_index_interface;
      for (sub_index_interface = 0; sub_index_interface < subs_interface->length; sub_index_interface++) {
        SPVM_RUNTIME_SUB* sub_interface = SPVM_LIST_fetch(subs_interface, sub_index_interface);
        
        _Bool found = 0;
        {
          int32_t sub_index_package;
          for (sub_index_package = 0; sub_index_package < subs_package->length; sub_index_package++) {
            SPVM_RUNTIME_SUB* sub_package = SPVM_LIST_fetch(subs_package, sub_index_package);
            
            if (strcmp(sub_interface->signature, sub_package->signature) == 0) {
              found = 1;
            }
          }
        }
        if (!found) {
          has_interface = 0;
          break;
        }
      }
    }
    
    // 1 bit : is cached
    // 2 bit : has interface
    int32_t new_has_interface_cache = 0;
    new_has_interface_cache |= 1;
    if (has_interface) {
      new_has_interface_cache |= 2;
    }
    
    SPVM_HASH_insert(package->has_interface_cache_symtable, interface->name, strlen(interface->name), (void*)(intptr_t)new_has_interface_cache);
  }
  
  return has_interface;
}

int32_t SPVM_RUNTIME_API_check_cast(SPVM_ENV* env, int32_t dist_basic_type_id, int32_t dist_type_dimension, SPVM_OBJECT* object) {
  (void)env;
  
  int32_t src_basic_type_id = object->basic_type_id;
  int32_t src_type_dimension = object->dimension;

  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  _Bool check_cast;
  
  // Dist type is same as source type
  if (dist_basic_type_id == src_basic_type_id && dist_type_dimension == src_type_dimension) {
    check_cast = 1;
  }
  // Dist type is difference from source type
  else {
    // Dist type dimension is less than or equal to source type dimension
    if (dist_type_dimension <= src_type_dimension) {
      // Dist basic type is any object
      if (dist_basic_type_id == SPVM_BASIC_TYPE_C_ID_ANY_OBJECT) {
        if (src_type_dimension == 0) {
          // Source basic type is value type
          SPVM_RUNTIME_BASIC_TYPE* src_basic_type = SPVM_LIST_fetch(runtime->basic_types, src_basic_type_id);
          SPVM_RUNTIME_PACKAGE* src_base_package = SPVM_LIST_fetch(runtime->packages, src_basic_type->package_id);
          if (src_base_package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
            check_cast = 0;
          }
          // Source basic type is not value type
          else {
            check_cast = 1;
          }
        }
        // Source type is array
        else {
          check_cast = 1;
        }
      }
      // Dist basic type is object (except for any object)
      else {
        // Dist type dimension is equal to source type dimension
        if (dist_type_dimension == src_type_dimension) {
          // Dist basic type is same as source basic type
          if (dist_basic_type_id == src_basic_type_id) {
            check_cast = 1;
          }
          // Dist basic type is different from source basic type
          else {
            SPVM_RUNTIME_BASIC_TYPE* dist_basic_type = SPVM_LIST_fetch(runtime->basic_types, dist_basic_type_id);
            SPVM_RUNTIME_BASIC_TYPE* src_basic_type = SPVM_LIST_fetch(runtime->basic_types, src_basic_type_id);
            SPVM_RUNTIME_PACKAGE* dist_package = SPVM_LIST_fetch(runtime->basic_types, dist_basic_type->package_id);
            SPVM_RUNTIME_PACKAGE* src_package = SPVM_LIST_fetch(runtime->basic_types, src_basic_type->package_id);
            
            // Dist basic type and source basic type is package
            if (dist_package && src_package) {
              
              // Dist base type is interface
              if (dist_package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
                check_cast = SPVM_RUNTIME_API_has_interface(env, src_package, dist_package);
              }
              // Dist base type is not interface
              else {
                check_cast = 0;
              }
            }
            // Dist basic type is not package or source basic type is not package
            else {
              check_cast = 0;
            }
          }
        }
        // Dist type dimension is different from source type dimension
        else {
          check_cast = 0;
        }
      }
    }
    // Dist type dimension is greater than source type dimension
    else if (dist_type_dimension > src_type_dimension) {
      check_cast = 0;
    }
  }
  
  return check_cast;
}

SPVM_OBJECT* SPVM_RUNTIME_API_create_exception_stack_trace(SPVM_ENV* env, SPVM_OBJECT* exception, const char* package_name, const char* sub_name, const char* file, int32_t line) {
  
  // stack trace strings
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

  if (string1 == NULL) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_raw(env, ". operater left string must be defined(string . string)", 0);
    SPVM_RUNTIME_API_set_exception(env, exception);
    return NULL;
  }
  else if (string2 == NULL) {
    SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string_raw(env, ". operater right string must be defined(string . string)", 0);
    SPVM_RUNTIME_API_set_exception(env, exception);
    return NULL;
  }
  
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

SPVM_RUNTIME* SPVM_RUNTIME_API_get_runtime() {
  
  return SPVM_GLOBAL_RUNTIME;
}

void SPVM_RUNTIME_API_set_runtime(SPVM_ENV* env, SPVM_RUNTIME* runtime) {
  (void)env;
  
  SPVM_GLOBAL_RUNTIME = runtime;
}

int32_t SPVM_RUNTIME_API_get_memory_blocks_count(SPVM_ENV* env) {
  (void)env;
  return SPVM_RUNTIME_API_get_runtime()->memory_blocks_count;
}

void SPVM_RUNTIME_API_free_weaken_back_refs(SPVM_ENV* env, void** weaken_back_refs, int32_t weaken_back_refs_length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
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

  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
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
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
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
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
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

SPVM_OBJECT* SPVM_RUNTIME_API_new_string(SPVM_ENV* env, char* bytes, int32_t length) {
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
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
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
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_BYTE;
  object->elements_length = length;
  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_short_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_short));
  
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_SHORT;
  
  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_int_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_int));
  
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_INT;

  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_long_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  if (length < 0) {
    return NULL;
  }
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));
  
  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_long));
  
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_LONG;

  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_float_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_float));
  
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_FLOAT;

  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_double_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_double));
  
  object->dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_DOUBLE;
  
  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_object));
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_LIST_fetch(runtime->basic_types, basic_type_id);

  object->basic_type_id = basic_type->id;
  object->dimension = 1;

  // Set array length
  object->elements_length = length;
  
  object->category = SPVM_OBJECT_C_CATEGORY_OBJECT_ARRAY;
  
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_multi_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_object));
  
  object->basic_type_id = basic_type_id;
  object->dimension = element_dimension + 1;
  
  // Set array length
  object->elements_length = length;
  
  object->category = SPVM_OBJECT_C_CATEGORY_OBJECT_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_value_t_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;

  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  // valut_t array dimension must be 1
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_LIST_fetch(runtime->basic_types, basic_type_id);
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, basic_type->name, strlen(basic_type->name));
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
  object->dimension = 1;

  // Set array length
  object->elements_length = length;

  object->category = SPVM_OBJECT_C_CATEGORY_VALUE_T_ARRAY;

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_raw(SPVM_ENV* env, int32_t basic_type_id) {
  (void)env;
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_LIST_fetch(runtime->basic_types, basic_type_id);
  
  SPVM_RUNTIME_PACKAGE* package;
  if (basic_type->package_id < 0) {
    package = NULL;
  }
  else {
    package = SPVM_LIST_fetch(runtime->packages, basic_type->package_id);
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
  object->dimension = 0;

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
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_LIST_fetch(runtime->basic_types, basic_type_id);

  SPVM_RUNTIME_PACKAGE* package;
  if (basic_type->package_id < 0) {
    package = NULL;
  }
  else {
    package = SPVM_LIST_fetch(runtime->packages, basic_type->package_id);
  }
  if (!package) {
    return NULL;
  }

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  object->body = pointer;

  object->basic_type_id = basic_type->id;
  object->dimension = 0;

  object->elements_length = 1;

  // Object type id
  object->category = SPVM_OBJECT_C_CATEGORY_OBJECT;
  
  // Has destructor
  if (package->destructor_sub_id >= 0) {
    object->has_destructor = 1;
  }
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_string_raw(SPVM_ENV* env, char* bytes, int32_t length) {
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
    SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
    
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_LIST_fetch(runtime->basic_types, object->basic_type_id);
    SPVM_RUNTIME_PACKAGE* package;
    if (basic_type->package_id < 0) {
      package = NULL;
    }
    else {
      package = SPVM_LIST_fetch(runtime->packages, basic_type->package_id);
    }
    _Bool is_pointer = 0;
    if (package) {
      if (package->category == SPVM_PACKAGE_C_CATEGORY_POINTER) {
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
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
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
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
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

  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
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
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_LIST_fetch(runtime->basic_types, object->basic_type_id);
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, basic_type->name, strlen(basic_type->name));  
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
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
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

int32_t SPVM_RUNTIME_API_weaken_object_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index) {

  if (!object) {
    SPVM_OBJECT* exception = env->new_string_raw(env, "Object to weaken an object field must not be undefined.", 0);
    env->set_exception(env, exception);
    return SPVM_EXCEPTION;
  }

  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  SPVM_OBJECT** object_field_address = (SPVM_OBJECT**)&fields[field_index];
  
  // Weaken object field
  if (*object_field_address != NULL) {
    SPVM_RUNTIME_API_weaken(env, object_field_address);
  }
  
  return SPVM_SUCCESS;
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

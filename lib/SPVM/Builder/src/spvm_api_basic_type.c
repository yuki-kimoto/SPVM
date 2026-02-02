// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <assert.h>

#include "spvm_native.h"

#include "spvm_basic_type.h"
#include "spvm_compiler.h"
#include "spvm_runtime.h"

#include "spvm_api_runtime.h"
#include "spvm_api_basic_type.h"
#include "spvm_api_method.h"
#include "spvm_api_arg.h"
#include "spvm_api_type.h"

#include "spvm_allocator.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_method.h"
#include "spvm_runtime_arg.h"

SPVM_API_BASIC_TYPE* SPVM_API_BASIC_TYPE_new_api() {
  
  void* native_apis_init[]  = {
    SPVM_API_BASIC_TYPE_get_name,
    SPVM_API_BASIC_TYPE_get_id,
    SPVM_API_BASIC_TYPE_get_category,
    SPVM_API_BASIC_TYPE_get_parent,
    SPVM_API_BASIC_TYPE_get_version_string,
    SPVM_API_BASIC_TYPE_get_class_dir,
    SPVM_API_BASIC_TYPE_get_class_rel_file,
    SPVM_API_BASIC_TYPE_is_pointer,
    SPVM_API_BASIC_TYPE_is_anon,
    SPVM_API_BASIC_TYPE_get_class_var_by_index,
    SPVM_API_BASIC_TYPE_get_class_var_by_name,
    SPVM_API_BASIC_TYPE_get_class_vars_length,
    SPVM_API_BASIC_TYPE_get_field_by_index,
    SPVM_API_BASIC_TYPE_get_field_by_name,
    SPVM_API_BASIC_TYPE_get_fields_length,
    SPVM_API_BASIC_TYPE_get_method_by_index,
    SPVM_API_BASIC_TYPE_get_method_by_name,
    SPVM_API_BASIC_TYPE_get_methods_length,
    SPVM_API_BASIC_TYPE_get_anon_basic_type_by_index,
    SPVM_API_BASIC_TYPE_get_anon_basic_types_length,
    SPVM_API_BASIC_TYPE_has_interface,
    SPVM_API_BASIC_TYPE_is_super_class,
    SPVM_API_BASIC_TYPE_get_file,
    SPVM_API_BASIC_TYPE_get_current_runtime,
    SPVM_API_BASIC_TYPE_get_basic_type_in_version_from,
    SPVM_API_BASIC_TYPE_get_fields_size,
    SPVM_API_BASIC_TYPE_get_monitor_var_type,
  };
  
  SPVM_API_BASIC_TYPE* native_apis = calloc(1, sizeof(native_apis_init));
  
  memcpy(native_apis, native_apis_init, sizeof(native_apis_init));
  
  return native_apis;
}

void SPVM_API_BASIC_TYPE_free_api(SPVM_API_BASIC_TYPE* api) {
  
  free(api);
}

const char* SPVM_API_BASIC_TYPE_get_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return  basic_type->name;
}

int32_t SPVM_API_BASIC_TYPE_get_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->id;
}

int32_t SPVM_API_BASIC_TYPE_get_category(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->category;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_BASIC_TYPE_get_parent(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->parent;
}

const char* SPVM_API_BASIC_TYPE_get_version_string(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->version_string;
}

const char* SPVM_API_BASIC_TYPE_get_class_dir(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->class_dir;
}

const char* SPVM_API_BASIC_TYPE_get_class_rel_file(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->class_rel_file;
}

int32_t SPVM_API_BASIC_TYPE_is_pointer(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->is_pointer;
}

int32_t SPVM_API_BASIC_TYPE_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->is_anon;
}

SPVM_RUNTIME_CLASS_VAR* SPVM_API_BASIC_TYPE_get_class_var_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t class_var_index) {
  
  if (class_var_index < 0) {
    return NULL;
  }
  
  if (class_var_index >= basic_type->class_vars_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = &basic_type->class_vars[class_var_index];
  
  return class_var;
}

SPVM_RUNTIME_CLASS_VAR* SPVM_API_BASIC_TYPE_get_class_var_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* class_var_name) {
  
  SPVM_RUNTIME_CLASS_VAR* found_class_var = NULL;
  if (basic_type->class_vars_length > 0) {
    for (int32_t class_var_index = 0; class_var_index <  basic_type->class_vars_length; class_var_index++) {
      SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_BASIC_TYPE_get_class_var_by_index(runtime, basic_type, class_var_index);
      const char* class_var_name_current = class_var->name;
      if (strcmp(class_var_name_current, class_var_name) == 0) {
        found_class_var = class_var;
        break;
      }
    }
  }
  
  return found_class_var;
}

int32_t SPVM_API_BASIC_TYPE_get_class_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->class_vars_length;
}

SPVM_RUNTIME_FIELD* SPVM_API_BASIC_TYPE_get_field_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t field_index) {
  
  if (field_index < 0) {
    return NULL;
  }
  
  if (field_index >= basic_type->fields_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_FIELD* field = &basic_type->fields[field_index];
  
  return field;
}

SPVM_RUNTIME_FIELD* SPVM_API_BASIC_TYPE_get_field_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* field_name) {
  
  SPVM_RUNTIME_FIELD* found_field = NULL;
  if (basic_type->fields_length > 0) {
    for (int32_t field_index = 0; field_index <  basic_type->fields_length; field_index++) {
      SPVM_RUNTIME_FIELD* field = SPVM_API_BASIC_TYPE_get_field_by_index(runtime, basic_type, field_index);
      const char* field_name_current = field->name;
      if (strcmp(field_name_current, field_name) == 0) {
        found_field = field;
        break;
      }
    }
  }
  
  return found_field;
}

int32_t SPVM_API_BASIC_TYPE_get_fields_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->fields_length;
}

SPVM_RUNTIME_METHOD* SPVM_API_BASIC_TYPE_get_method_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t method_index) {
  
  if (method_index < 0) {
    return NULL;
  }
  
  if (method_index >= basic_type->methods_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_METHOD* method = &basic_type->methods[method_index];
  
  return method;
}

SPVM_RUNTIME_METHOD* SPVM_API_BASIC_TYPE_get_method_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* method_name) {
  
  SPVM_RUNTIME_METHOD* found_method = NULL;
  if (basic_type->methods_length > 0) {
    // Performe binary searching because methods are sorted by the names
    int32_t current_min_index = 0;
    int32_t current_max_index = basic_type->methods_length - 1;
    
    while (1) {
      if (current_max_index < current_min_index) {
        break;
      }
      
      int32_t current_half_index = current_min_index +(current_max_index - current_min_index) / 2;
      
      SPVM_RUNTIME_METHOD* method = SPVM_API_BASIC_TYPE_get_method_by_index(runtime, basic_type, current_half_index);
      const char* current_half_method_name = method->name;
      
      int32_t cmp_result = strcmp(method_name, current_half_method_name);
      
      if (cmp_result > 0) {
        current_min_index = current_half_index + 1;
      }
      else if (cmp_result < 0) {
        current_max_index = current_half_index - 1;
      }
      else {
        found_method = method;
        break;
      }
    }
  }
  
  return found_method;
}

int32_t SPVM_API_BASIC_TYPE_get_methods_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->methods_length;
}

int32_t SPVM_API_BASIC_TYPE_get_anon_basic_types_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->anon_basic_types_length;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_BASIC_TYPE_get_anon_basic_type_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t anon_basic_type_index) {
  
  if (anon_basic_type_index < 0) {
    return NULL;
  }
  
  if (anon_basic_type_index >= basic_type->anon_basic_types_length) {
    return NULL;
  }
  
  SPVM_RUNTIME_BASIC_TYPE* anon_basic_type = basic_type->anon_basic_types[anon_basic_type_index];
  
  return anon_basic_type;
}

int32_t SPVM_API_BASIC_TYPE_has_interface(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* src_basic_type, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type) {
  
  SPVM_COMPILER* compiler = runtime->compiler;
  
  int32_t has_interface = SPVM_BASIC_TYPE_has_interface(compiler, src_basic_type->id, dist_basic_type->id, NULL);
  
  return has_interface;
}

int32_t SPVM_API_BASIC_TYPE_is_super_class(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type, SPVM_RUNTIME_BASIC_TYPE* src_basic_type) {
  
  SPVM_COMPILER* compiler = runtime->compiler;
  
  int32_t is_super_class_basic_type = SPVM_BASIC_TYPE_is_super_class(compiler, dist_basic_type->id, src_basic_type->id);
  
  return is_super_class_basic_type;
}

const char* SPVM_API_BASIC_TYPE_get_file(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->file;
}

SPVM_RUNTIME* SPVM_API_BASIC_TYPE_get_current_runtime(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->current_runtime;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_BASIC_TYPE_get_basic_type_in_version_from(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->basic_type_in_version_from;
}

int32_t SPVM_API_BASIC_TYPE_get_fields_size(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->fields_size;
}

int32_t SPVM_API_BASIC_TYPE_get_monitor_var_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t* ret_basic_type_id, int32_t* ret_dimension, int32_t* ret_flag) {
  assert(ret_basic_type_id);
  assert(ret_dimension);
  assert(ret_flag);

  if (basic_type->has_monitor_var) {
    *ret_basic_type_id = basic_type->monitor_var_basic_type->id;
    *ret_dimension = basic_type->monitor_var_type_dimension;
    *ret_flag = basic_type->monitor_var_type_flag;
    
    return 0;
  }
  
  return 1;
}

int32_t SPVM_API_BASIC_TYPE_has_monitor_var(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return (int32_t)basic_type->has_monitor_var;
}

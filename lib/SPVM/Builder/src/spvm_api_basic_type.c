// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_basic_type.h"

#include "spvm_allocator.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_method.h"

SPVM_API_BASIC_TYPE* SPVM_API_BASIC_TYPE_new_api() {
  
  void* native_apis_init[]  = {
    SPVM_API_BASIC_TYPE_get_name,
    SPVM_API_BASIC_TYPE_get_id,
    SPVM_API_BASIC_TYPE_get_category,
    SPVM_API_BASIC_TYPE_get_parent,
    SPVM_API_BASIC_TYPE_get_version_string,
    SPVM_API_BASIC_TYPE_get_module_dir,
    SPVM_API_BASIC_TYPE_get_module_rel_file,
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

const char* SPVM_API_BASIC_TYPE_get_module_dir(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->module_dir;
}

const char* SPVM_API_BASIC_TYPE_get_module_rel_file(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->module_rel_file;
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
    int32_t cur_min_index = 0;
    int32_t cur_max_index = basic_type->methods_length - 1;
    
    while (1) {
      if (cur_max_index < cur_min_index) {
        break;
      }
      
      int32_t cur_half_index = cur_min_index +(cur_max_index - cur_min_index) / 2;
      
      SPVM_RUNTIME_METHOD* method = SPVM_API_BASIC_TYPE_get_method_by_index(runtime, basic_type, cur_half_index);
      const char* cur_half_method_name = method->name;
      
      int32_t cmp_result = strcmp(method_name, cur_half_method_name);
      
      if (cmp_result > 0) {
        cur_min_index = cur_half_index + 1;
      }
      else if (cmp_result < 0) {
        cur_max_index = cur_half_index - 1;
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
  
  SPVM_RUNTIME_BASIC_TYPE* anon_basic_type = &basic_type->anon_basic_types[anon_basic_type_index];
  
  return anon_basic_type;
}

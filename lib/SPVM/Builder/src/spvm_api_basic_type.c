// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

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

int32_t SPVM_API_BASIC_TYPE_has_interface(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, SPVM_RUNTIME_BASIC_TYPE* interface_basic_type) {
  
  if (!(interface_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE)) {
    return 0;
  }
  
  if (!(basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS || basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE)) {
    return 0;
  }
  
  for (int32_t interface_method_index = 0; interface_method_index < interface_basic_type->methods_length; interface_method_index++) {
    SPVM_RUNTIME_METHOD* interface_method = SPVM_API_BASIC_TYPE_get_method_by_index(runtime, interface_basic_type, interface_method_index);
    
    for (int32_t method_index = 0; method_index < basic_type->methods_length; method_index++) {
      SPVM_RUNTIME_METHOD* method = SPVM_API_BASIC_TYPE_get_method_by_name(runtime, interface_basic_type, interface_method->name);
      
      int32_t method_compatibility = SPVM_API_BASIC_TYPE_check_method_compatibility(runtime, basic_type, method, interface_basic_type, interface_method);
      
      if (method_compatibility == 0) {
        return 0;
      }
    }
  }
  
  return 1;
}

int32_t SPVM_API_BASIC_TYPE_check_method_compatibility(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, SPVM_RUNTIME_METHOD* method, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type, SPVM_RUNTIME_METHOD* dist_method) {
  
  if (dist_method->is_required && !method) {
    if (!dist_method->is_class_method) {
      return 0;
    }
  }
  
  if (method) {
    if (method->is_class_method) {
      if (!dist_method->is_class_method) {
        return 0;
      }
    }
    
    if (!(method->required_args_length == dist_method->required_args_length)) {
      return 0;
    }
    
    if (!(method->args_length >= dist_method->args_length)) {
      return 0;
    }
    
    for (int32_t arg_index = 1; arg_index < dist_method->args_length; arg_index++) {
      SPVM_RUNTIME_ARG* method_arg = SPVM_API_METHOD_get_arg_by_index(runtime, method, arg_index);
      SPVM_RUNTIME_ARG* dist_method_arg = SPVM_API_METHOD_get_arg_by_index(runtime, dist_method, arg_index);
      
      SPVM_RUNTIME_BASIC_TYPE* method_arg_basic_type = method_arg->basic_type;
      int32_t method_arg_type_dimension = method_arg->type_dimension;
      int32_t method_arg_type_flag = method_arg->type_flag;
      
      SPVM_RUNTIME_BASIC_TYPE* dist_method_arg_basic_type = dist_method_arg->basic_type;
      int32_t dist_method_arg_type_dimension = dist_method_arg->type_dimension;
      int32_t dist_method_arg_type_flag = dist_method_arg->type_flag;
      
      int32_t assignability_for_method = SPVM_API_BASIC_TYPE_can_assign_for_method_definition(runtime, method_arg->basic_type, method_arg->type_dimension, method_arg->type_flag, dist_method_arg->basic_type, dist_method_arg->type_dimension, dist_method_arg->type_flag);
      
      if (!assignability_for_method) {
        return 0;
      }
    }
    
    SPVM_RUNTIME_BASIC_TYPE* method_return_basic_type = method->return_basic_type;
    int32_t method_return_type_dimension = method->return_type_dimension;
    int32_t method_return_type_flag = method->return_type_flag;
    
    SPVM_RUNTIME_BASIC_TYPE* dist_method_return_basic_type = dist_method->return_basic_type;
    int32_t dist_method_return_type_dimension = dist_method->return_type_dimension;
    int32_t dist_method_return_type_flag = dist_method->return_type_flag;
    
    int32_t assignability_for_method_definition = SPVM_API_BASIC_TYPE_can_assign_for_method_definition(
      runtime,
      dist_method_return_basic_type, dist_method_return_type_dimension, dist_method_return_type_flag,
      method_return_basic_type, method_return_type_dimension, method_return_type_flag
    );
    
    if (!assignability_for_method_definition) {
      return 0;
    }
  }
  
  return 1;
}

int32_t SPVM_API_BASIC_TYPE_can_assign_for_method_definition (
  SPVM_RUNTIME* runtime,
  SPVM_RUNTIME_BASIC_TYPE* dist_type_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag,
  SPVM_RUNTIME_BASIC_TYPE* src_type_basic_type, int32_t src_type_dimension, int32_t src_type_flag)
{
  int32_t assignability = 0;
  
  if (SPVM_API_RUNTIME_is_any_object_type(runtime, dist_type_basic_type, dist_type_dimension, dist_type_flag)) {
    if (SPVM_API_TYPE_is_object_type(runtime, src_type_basic_type, src_type_dimension, src_type_flag)) {
      assignability = 1;
    }
    else {
      assignability = 0;
    }
  }
  else if (SPVM_API_RUNTIME_is_any_object_array_type(runtime, dist_type_basic_type, dist_type_dimension, dist_type_flag)) {
    if (SPVM_API_RUNTIME_is_object_array_type(runtime, src_type_basic_type, src_type_dimension, src_type_flag)) {
      assignability = 1;
    }
    else {
      assignability = 0;
    }
  }
  else {
    if (dist_type_dimension == src_type_dimension && dist_type_flag == src_type_flag) {
      if (SPVM_API_BASIC_TYPE_is_class_type(runtime, dist_type_basic_type)) {
        if (dist_type_basic_type->id == src_type_basic_type->id) {
          assignability = 1;
        }
        else {
          assignability = SPVM_API_BASIC_TYPE_is_super_class(runtime, dist_type_basic_type, src_type_basic_type);
        }
      }
      else {
        if (dist_type_basic_type->id == src_type_basic_type->id) {
          assignability = 1;
        }
        else {
          assignability = 0;
        }
      }
    }
    else {
      assignability = 0;
    }
  }
  
  return assignability;
}

int32_t SPVM_API_BASIC_TYPE_is_class_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  int32_t is_class_type;
  
  int32_t basic_type_category = basic_type->category;
  
  switch (basic_type_category) {
    case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
    {
      is_class_type = 1;
      break;
    }
    default: {
      is_class_type = 0;
    }
  }
  
  return is_class_type;
}

int32_t SPVM_API_BASIC_TYPE_is_super_class(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* super_basic_type, SPVM_RUNTIME_BASIC_TYPE* child_basic_type) {

  int32_t is_super_class_basic_type = 0;
  
  if (!(super_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS)) {
    return 0;
  }
  
  if (!(child_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS)) {
    return 0;
  }
  
  SPVM_RUNTIME_BASIC_TYPE* parent_basic_type = child_basic_type->parent;
  
  while (1) {
    if (parent_basic_type) {
      if (parent_basic_type->id == super_basic_type->id) {
        is_super_class_basic_type = 1;
        break;
      }
      else {
        parent_basic_type = parent_basic_type->parent;
      }
    }
    else {
      is_super_class_basic_type = 0;
      break;
    }
  }
  
  return is_super_class_basic_type;
}

const char* SPVM_API_BASIC_TYPE_get_file(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type) {
  
  return basic_type->file;
}

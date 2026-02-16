// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>

static const char* FILE_NAME = "Native/MethodCall.c";

int32_t SPVM__Native__MethodCall__new_method_with_env_stack_common(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_call_type) {
  
  int32_t error_id = 0;
  
  void* obj_self_env = stack[0].oval;
  
  void* obj_self_stack = stack[1].oval;
  
  void* obj_instance = stack[2].oval;
  
  void* obj_basic_type_name = stack[2].oval;
  
  void* obj_method_name = stack[3].oval;
  
  SPVM_ENV* self_env = NULL;
  if (obj_self_env) {
    self_env = env->get_pointer(env, stack, obj_self_env);
  }
  else {
    self_env = env;
    
    void* obj_address_self_env = env->new_pointer_object_by_name(env, stack, "Address", self_env, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    stack[0].oval = obj_address_self_env;
    env->call_class_method_by_name(env, stack, "Native::Env", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    obj_self_env = stack[0].oval;
    
    env->set_no_free(env, stack, obj_self_env, 1);
  }
  
  SPVM_VALUE* self_stack = NULL;
  if (obj_self_stack) {
    self_stack = env->get_pointer(env, stack, obj_self_stack);
  }
  else {
    self_stack = stack;
    
    void* obj_address_self_stack = env->new_pointer_object_by_name(env, stack, "Address", self_stack, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    stack[0].oval = obj_address_self_stack;
    env->call_class_method_by_name(env, stack, "Native::Stack", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    obj_self_stack = stack[0].oval;
    
    env->set_no_free(env, stack, obj_self_stack, 1);
  }
  
  int32_t is_binary_compatible_stack = env->is_binary_compatible_stack(self_env, self_stack);
  
  if (!is_binary_compatible_stack) {
    return env->die(env, stack, "The runtime stack $stack is not compatible with the runtime environemnt $env.", __func__, __FILE__, __LINE__);
  }
  
  void* method = NULL;
  
  const char* method_disp = NULL;
  if (method_call_type == 0) {
    
    if (!obj_basic_type_name) {
      return env->die(env, stack, "The basic type name $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
    }
    
    const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
    
    if (!obj_method_name) {
      return env->die(env, stack, "The method name $method_name must be defined.", __func__, FILE_NAME, __LINE__);
    }
    
    const char* method_name = env->get_chars(env, stack, obj_method_name);
    
    method = self_env->get_class_method(self_env, self_stack, basic_type_name, method_name);
    if (!method) {
      return env->die(env, stack, "The \"%s\" class method in the \"%s\" class cannot be found.", __func__, FILE_NAME, __LINE__, method_name, basic_type_name);
    }
  }
  else if (method_call_type == 1) {
    
    if (!obj_basic_type_name) {
      return env->die(env, stack, "The basic type name $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
    }
    
    const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
    
    if (!obj_method_name) {
      return env->die(env, stack, "The method name $method_name must be defined.", __func__, FILE_NAME, __LINE__);
    }
    
    const char* method_name = env->get_chars(env, stack, obj_method_name);
    
    method = self_env->get_instance_method_static(self_env, self_stack, basic_type_name, method_name);
    if (!method) {
      return env->die(env, stack, "The \"%s\" instance method in the \"%s\" class cannot be found.", __func__, FILE_NAME, __LINE__, method_name, basic_type_name);
    }
  }
  else if (method_call_type == 2) {
    
    if (!obj_instance) {
      return env->die(env, stack, "The instance $instance must be defined.", __func__, FILE_NAME, __LINE__);
    }
    
    if (!obj_method_name) {
      return env->die(env, stack, "The method name $method_name must be defined.", __func__, FILE_NAME, __LINE__);
    }
    
    const char* method_name = env->get_chars(env, stack, obj_method_name);
    
    method = self_env->get_instance_method(self_env, self_stack, obj_instance, method_name);
    if (!method) {
      return env->die(env, stack, "The \"%s\" instance method cannot be found.", __func__, FILE_NAME, __LINE__, method_name);
    }
  }
  
  void* obj_address_method = env->new_pointer_object_by_name(env, stack, "Address", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_method;
  env->call_class_method_by_name(env, stack, "Native::Method", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_method = stack[0].oval;
  env->set_no_free(env, stack, obj_method, 1);
  
  void* obj_self = env->new_pointer_object_by_name(env, stack, "Native::MethodCall", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_self, "method", obj_method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_self, "env", obj_self_env, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_self, "stack", obj_self_stack, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_self;
  
  return 0;
}

int32_t SPVM__Native__MethodCall__new_class_method_with_env_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = SPVM__Native__MethodCall__new_method_with_env_stack_common(env, stack, 0);
  
  return error_id;
}

int32_t SPVM__Native__MethodCall__new_instance_method_static_with_env_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = SPVM__Native__MethodCall__new_method_with_env_stack_common(env, stack, 1);
  
  return error_id;
}

int32_t SPVM__Native__MethodCall__new_instance_method_with_env_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = SPVM__Native__MethodCall__new_method_with_env_stack_common(env, stack, 2);
  
  return error_id;
}

int32_t SPVM__Native__MethodCall__call(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_args = stack[1].oval;
  
  void* obj_error_id_ref = stack[2].oval;
  
  if (obj_error_id_ref) {
    int32_t error_id_ref_length = env->length(env, stack, obj_error_id_ref);
    
    if (!(error_id_ref_length == 1)) {
      return env->die(env, stack, "If the reference to an error id $error_id_ref exists, the length of it must be 1.", __func__, FILE_NAME, __LINE__);
    }
  }
  
  if (!obj_args) {
    obj_args = env->new_object_array_by_name(env, stack, "object", 0, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
  }
  
  int32_t args_length = env->length(env, stack, obj_args);
  
  void* obj_method = env->get_field_object_by_name(env, stack, obj_self, "method", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->runtime;
  
  void* method = env->get_pointer(env, stack, obj_method);
  
  const char* method_name = env->api->method->get_name(runtime, method);
  
  void* basic_type = env->api->method->get_current_basic_type(runtime, method);
  
  const char* class_name = env->api->basic_type->get_name(runtime, basic_type);
  
  int32_t method_required_args_length = env->api->method->get_required_args_length(runtime, method);
  
  if (!(args_length >= method_required_args_length)) {
    return env->die(env, stack, "%s#%s method failed to execute. Too few arguments.", __func__, FILE_NAME, __LINE__, class_name, method_name);
  }
  
  int32_t method_args_length = env->api->method->get_args_length(runtime, method);
  
  if (!(args_length <= method_args_length)) {
    args_length = method_args_length;
  }
  
  void* obj_self_env = env->get_field_object_by_name(env, stack, obj_self, "env", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  SPVM_ENV* self_env = env->get_pointer(env, stack, obj_self_env);
  
  void* obj_self_stack = env->get_field_object_by_name(env, stack, obj_self, "stack", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  SPVM_VALUE* self_stack = env->get_pointer(env, stack, obj_self_stack);
  
  int32_t stack_index = 0;
  for (int32_t arg_index = 0; arg_index < args_length; arg_index++) {
    void* obj_arg = env->get_elem_object(env, stack, obj_args, arg_index);
    
    void* method_arg = env->api->method->get_arg_by_index(runtime, method, arg_index);
    
    void* method_arg_basic_type = env->api->arg->get_basic_type(runtime, method_arg);
    int32_t method_arg_basic_type_id = env->api->basic_type->get_id(runtime, method_arg_basic_type);
    int32_t method_arg_type_dimension = env->api->arg->get_type_dimension(runtime, method_arg);
    int32_t method_arg_type_flag = env->api->arg->get_type_flag(runtime, method_arg);
    int32_t method_arg_basic_type_category = env->api->basic_type->get_category(runtime, method_arg_basic_type);
    
    int32_t method_arg_is_object_type = env->api->type->is_object_type(runtime, method_arg_basic_type, method_arg_type_dimension, method_arg_type_flag);
    
    if (method_arg_is_object_type) {
      
      if (obj_arg) {
        void* arg_basic_type = env->get_object_basic_type(env, stack, obj_arg);
        const char* arg_basic_type_name = env->api->basic_type->get_name(runtime, arg_basic_type);
        
        int32_t arg_type_dimension = env->get_object_type_dimension(env, stack, obj_arg);
        
        int32_t can_assign = env->api->type->can_assign(
          runtime,
          method_arg_basic_type, method_arg_type_dimension, method_arg_type_flag,
          arg_basic_type, method_arg_type_dimension, 0
        );
        
        if (!can_assign) {
          return env->die(env, stack, "%s#%s method failed to execute. The %dth argument cannot be assigned.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
        }
        
        int32_t is_binary_compatible_object = self_env->is_binary_compatible_object(self_env, self_stack, obj_arg);
        
        if (!is_binary_compatible_object) {
          return env->die(env, stack, "%s#%s method failed to execute. The object of the %dth argument is not binary compatible.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
        }
      }
      
      self_stack[stack_index].oval = obj_arg;
      
      stack_index++;
    }
    else {
      if (!obj_arg) {
        return env->die(env, stack, "%s#%s method failed to execute. The %dth argument must be defined.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
      }
      
      int32_t method_arg_type_is_ref = method_arg_type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF;
      
      if (!method_arg_type_is_ref) {
        if (method_arg_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC) {
          switch (method_arg_basic_type_id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Byte", 0)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the Byte class.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int8_t value = env->get_field_byte_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              self_stack[stack_index].bval = value;
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Short", 0)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the Short class.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int16_t value = env->get_field_short_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              self_stack[stack_index].sval = value;
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Int", 0)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the Int class.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int32_t value = env->get_field_int_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              self_stack[stack_index].ival = value;
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Long", 0)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the Long class.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int64_t value = env->get_field_long_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              self_stack[stack_index].lval = value;
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Float", 0)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the Float class.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              float value = env->get_field_float_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              self_stack[stack_index].fval = value;
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Double", 0)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the Double class.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              double value = env->get_field_double_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              self_stack[stack_index].dval = value;
              break;
            }
            default: {
              assert(0);
            }
          }
          stack_index++;
        }
        else if (method_arg_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM) {
          int32_t method_arg_width = env->api->type->get_type_width(runtime, method_arg_basic_type, method_arg_type_dimension, method_arg_type_flag);
          
          int32_t arg_array_length = env->length(env, stack, obj_arg);
          
          if (!(arg_array_length == method_arg_width)) {
            return env->die(env, stack, "%s#%s method failed to execute. The array length of the %dth argument must be %d.", class_name, method_name, arg_index + 1, method_arg_width, __func__, FILE_NAME, __LINE__);
          }
          
          void* method_arg_mulnum_field = env->api->basic_type->get_field_by_index(runtime, method_arg_basic_type, 0);
          void* method_arg_mulnum_field_basic_type = env->api->field->get_basic_type(runtime, method_arg_mulnum_field);
          int32_t method_arg_mulnum_field_basic_type_id = env->api->basic_type->get_id(runtime, method_arg_mulnum_field_basic_type);
          
          switch (method_arg_mulnum_field_basic_type_id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "byte", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the byte[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int8_t* value_ref = env->get_elems_byte(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                self_stack[stack_index + i].bval = value_ref[i];
              }
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "short", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the short[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int16_t* value_ref = env->get_elems_short(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                self_stack[stack_index + i].sval = value_ref[i];
              }
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "int", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the int[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int32_t* value_ref = env->get_elems_int(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                self_stack[stack_index + i].ival = value_ref[i];
              }
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
              if (!env->is_type_by_name(env, stack, obj_arg, "long", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the long[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int64_t* value_ref = env->get_elems_long(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                self_stack[stack_index + i].lval = value_ref[i];
              }
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "float", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the float[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              float* value_ref = env->get_elems_float(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                self_stack[stack_index + i].fval = value_ref[i];
              }
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "double", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the double[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              double* value_ref = env->get_elems_double(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                self_stack[stack_index + i].dval = value_ref[i];
              }
              
              break;
            }
            default: {
              assert(0);
            }
          }
          stack_index += method_arg_width;
        }
        else {
          assert(0);
        }
      }
      else {
        if (method_arg_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC) {
          int32_t arg_array_length = env->length(env, stack, obj_arg);
          
          if (!(arg_array_length == 1)) {
            return env->die(env, stack, "%s#%s method failed to execute. The array length of the %dth argument must be 1.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
          }
          
          switch(method_arg_basic_type_id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "byte", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the byte[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int8_t* value_ref = env->get_elems_byte(env, stack, obj_arg);
              
              self_stack[stack_index].bref = value_ref;
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "short", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the short[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int16_t* value_ref = env->get_elems_short(env, stack, obj_arg);
              
              self_stack[stack_index].sref = value_ref;
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "int", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the int[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int32_t* value_ref = env->get_elems_int(env, stack, obj_arg);
              
              self_stack[stack_index].iref = value_ref;
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
              if (!env->is_type_by_name(env, stack, obj_arg, "long", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the long[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int64_t* value_ref = env->get_elems_long(env, stack, obj_arg);
              
              self_stack[stack_index].lref = value_ref;
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "float", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the float[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              float* value_ref = env->get_elems_float(env, stack, obj_arg);
              
              self_stack[stack_index].fref = value_ref;
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "double", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the double[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              double* value_ref = env->get_elems_double(env, stack, obj_arg);
              
              self_stack[stack_index].dref = value_ref;
              
              break;
            }
            default: {
              assert(0);
            }
          }
        }
        else if (method_arg_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM) {
          int32_t method_arg_width = env->api->basic_type->get_fields_length(runtime, method_arg_basic_type);
          
          int32_t arg_array_length = env->length(env, stack, obj_arg);
          
          if (!(arg_array_length == method_arg_width)) {
            return env->die(env, stack, "%s#%s method failed to execute. The array length of the %dth argument must be %d.", class_name, method_name, arg_index + 1, method_arg_width, __func__, FILE_NAME, __LINE__);
          }
          
          void* method_arg_mulnum_field = env->api->basic_type->get_field_by_index(runtime, method_arg_basic_type, 0);
          void* method_arg_mulnum_field_basic_type = env->api->field->get_basic_type(runtime, method_arg_mulnum_field);
          int32_t method_arg_mulnum_field_basic_type_id = env->api->basic_type->get_id(runtime, method_arg_mulnum_field_basic_type);
          
          switch(method_arg_mulnum_field_basic_type_id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "byte", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the byte[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int8_t* value_ref = env->get_elems_byte(env, stack, obj_arg);
              
              self_stack[stack_index].bref = value_ref;
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "short", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the short[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int16_t* value_ref = env->get_elems_short(env, stack, obj_arg);
              
              self_stack[stack_index].sref = value_ref;
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "int", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the int[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int32_t* value_ref = env->get_elems_int(env, stack, obj_arg);
              
              self_stack[stack_index].iref = value_ref;
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
              if (!env->is_type_by_name(env, stack, obj_arg, "long", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the long[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              int64_t* value_ref = env->get_elems_long(env, stack, obj_arg);
              
              self_stack[stack_index].lref = value_ref;
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "float", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the float[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              float* value_ref = env->get_elems_float(env, stack, obj_arg);
              
              self_stack[stack_index].fref = value_ref;
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "double", 1)) {
                return env->die(env, stack, "%s#%s method failed to execute. The type of the %dth argument must be the double[] type.", __func__, FILE_NAME, __LINE__, class_name, method_name, arg_index + 1);
              }
              
              double* value_ref = env->get_elems_double(env, stack, obj_arg);
              
              self_stack[stack_index].dref = value_ref;
              
              break;
            }
            default: {
              assert(0);
            }
          }
        }
        else {
          assert(0);
        }
        
        stack_index++;
      }
    }
  }
  
  int32_t stack_length = stack_index;
  
  int32_t error_id_exception_thrown = env->get_basic_type_id_by_name(env, stack, "Native::MethodCall::Error::ExceptionThrown", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  int32_t self_error_id = self_env->call_method(self_env, self_stack, method, stack_length, __func__, FILE_NAME, __LINE__);
  if (obj_error_id_ref) {
    int32_t* error_id_ref = env->get_elems_int(env, stack, obj_error_id_ref);
    *error_id_ref = self_error_id;
  }
  
  if (self_error_id) {
    env->set_exception(env, stack, env->get_exception(env, self_stack));
    return error_id_exception_thrown;
  }
  
  void* method_return_basic_type = env->api->method->get_return_basic_type(runtime, method);
  int32_t method_return_basic_type_id = env->api->basic_type->get_id(runtime, method_return_basic_type);
  int32_t method_return_type_dimension = env->api->method->get_return_type_dimension(runtime, method);
  int32_t method_return_type_flag = env->api->method->get_return_type_flag(runtime, method);
  
  int32_t method_return_basic_type_category = env->api->basic_type->get_category(runtime, method_return_basic_type);
  
  int32_t method_return_is_object_type = env->api->type->is_object_type(runtime, method_return_basic_type, method_return_type_dimension, method_return_type_flag);
  
  if (method_return_is_object_type) {
    if (self_stack[0].oval) {
      int32_t is_binary_compatible_object = env->is_binary_compatible_object(env, stack, self_stack[0].oval);
      
      if (!is_binary_compatible_object) {
        return env->die(env, stack, "The return object is not binary compatible.", __func__, FILE_NAME, __LINE__);
      }
    }
  }
  else {
    int32_t method_return_type_is_ref = method_return_type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF;
    
    assert(!method_return_type_is_ref);
    
    if (method_return_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC) {
      switch (method_return_basic_type_id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
          
          self_stack[0].ival = self_stack[0].bval;
          env->call_class_method_by_name(env, stack, "Byte", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
          
          self_stack[0].ival = self_stack[0].sval;
          env->call_class_method_by_name(env, stack, "Short", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
          
          env->call_class_method_by_name(env, stack, "Int", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
          
          env->call_class_method_by_name(env, stack, "Long", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
          
          env->call_class_method_by_name(env, stack, "Float", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
          
          env->call_class_method_by_name(env, stack, "Double", "new", 1, &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          break;
        }
        default: {
          assert(0);
        }
      }
    }
    else if (method_return_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM) {
      int32_t method_return_width = env->api->type->get_type_width(runtime, method_return_basic_type, method_return_type_dimension, method_return_type_flag);
      
      void* method_return_mulnum_field = env->api->basic_type->get_field_by_index(runtime, method_return_basic_type, 0);
      void* method_return_mulnum_field_basic_type = env->api->field->get_basic_type(runtime, method_return_mulnum_field);
      int32_t method_return_mulnum_field_basic_type_id = env->api->basic_type->get_id(runtime, method_return_mulnum_field_basic_type);
      
      switch (method_return_mulnum_field_basic_type_id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
          void* obj_return_value = env->new_byte_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          int8_t* return_value_ref = env->get_elems_byte(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = self_stack[i].bval;
          }
          
          self_stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
          void* obj_return_value = env->new_short_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          int16_t* return_value_ref = env->get_elems_short(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = self_stack[i].sval;
          }
          
          self_stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
          void* obj_return_value = env->new_int_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          int32_t* return_value_ref = env->get_elems_int(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = self_stack[i].ival;
          }
          
          self_stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
          void* obj_return_value = env->new_long_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          int64_t* return_value_ref = env->get_elems_long(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = self_stack[i].lval;
          }
          
          self_stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
          void* obj_return_value = env->new_float_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          float* return_value_ref = env->get_elems_float(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = self_stack[i].fval;
          }
          
          self_stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
          void* obj_return_value = env->new_double_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          double* return_value_ref = env->get_elems_double(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = self_stack[i].dval;
          }
          
          self_stack[0].oval = obj_return_value;
          
          break;
        }
        default: {
          assert(0);
        }
      }
    }
    else if (method_return_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID) {
      self_stack[0].oval = NULL;
    }
    else {
      assert(0);
    }
  }
  
  return 0;
}

int32_t SPVM__Native__MethodCall__get_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_self_env = env->get_field_object_by_name(env, stack, obj_self, "env", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  SPVM_ENV* self_env = env->get_pointer(env, stack, obj_self_env);
  
  void* obj_self_stack = env->get_field_object_by_name(env, stack, obj_self, "stack", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  SPVM_VALUE* self_stack = env->get_pointer(env, stack, obj_self_stack);
  
  void* obj_exception = self_env->get_exception(self_env, self_stack);
  
  stack[0].oval = obj_exception;
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_exception = stack[1].oval;
  
  void* obj_self_env = env->get_field_object_by_name(env, stack, obj_self, "env", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  SPVM_ENV* self_env = env->get_pointer(env, stack, obj_self_env);
  
  void* obj_self_stack = env->get_field_object_by_name(env, stack, obj_self, "stack", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  SPVM_VALUE* self_stack = env->get_pointer(env, stack, obj_self_stack);
  
  self_env->set_exception(self_env, self_stack, obj_exception);
  
  return 0;
}


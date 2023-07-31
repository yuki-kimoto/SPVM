// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>

static const char* FILE_NAME = "Native/MethodCall.c";

int32_t SPVM__Native__MethodCall__new_class_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_basic_type_name = stack[0].oval;
  
  if (!obj_basic_type_name) {
    return env->die(env, stack, "The $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  void* obj_method_name = stack[1].oval;
  
  if (!obj_method_name) {
    return env->die(env, stack, "The $method_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* method = env->get_class_method(env, stack, basic_type_name, method_name);
  if (!method) {
    return env->die(env, stack, "The \"%s\" method in the \"%s\" class cannot be found.", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_method = env->new_pointer_object_by_name(env, stack, "Native::Method", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* obj_method_call = env->new_pointer_object_by_name(env, stack, "Native::MethodCall", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_method_call, "method", obj_method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__Native__MethodCall__new_instance_method_static(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_basic_type_name = stack[0].oval;
  
  if (!obj_basic_type_name) {
    return env->die(env, stack, "The $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  void* obj_method_name = stack[1].oval;
  
  if (!obj_method_name) {
    return env->die(env, stack, "The $method_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* method = env->get_instance_method_static(env, stack, basic_type_name, method_name);
  if (!method) {
    return env->die(env, stack, "The \"%s\" method in the \"%s\" class cannot be found.", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_method = env->new_pointer_object_by_name(env, stack, "Native::Method", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* obj_method_call = env->new_pointer_object_by_name(env, stack, "Native::MethodCall", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_method_call, "method", obj_method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__Native__MethodCall__new_instance_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_invocant = stack[0].oval;
  
  if (!obj_invocant) {
    return env->die(env, stack, "The $invocant must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_method_name = stack[1].oval;
  
  if (!obj_method_name) {
    return env->die(env, stack, "The $method_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* method = env->get_instance_method(env, stack, obj_invocant, method_name);
  if (!method) {
    return env->die(env, stack, "The \"%s\" method cannot be found.", method_name, __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_method = env->new_pointer_object_by_name(env, stack, "Native::Method", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* obj_method_call = env->new_pointer_object_by_name(env, stack, "Native::MethodCall", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_method_call, "method", obj_method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__Native__MethodCall__call(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_args = stack[1].oval;
  
  if (!obj_args) {
    return env->die(env, stack, "The $args must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t args_length = env->length(env, stack, obj_args);
  
  void* obj_method = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "method", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* method = env->get_pointer(env, stack, obj_method);
  
  void* runtime = env->runtime;
  
  int32_t method_required_args_length = env->api->method->get_required_args_length(runtime, method);
  
  if (!(args_length >= method_required_args_length)) {
    return env->die(env, stack, "Too few arguments.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t method_args_length = env->api->method->get_args_length(runtime, method);
  
  if (!(args_length <= method_args_length)) {
    return env->die(env, stack, "Too many arguments.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t stack_index = 0;
  for (int32_t arg_index = 0; arg_index < args_length; arg_index++) {
    void* obj_arg = env->get_elem_object(env, stack, obj_args, arg_index);
    
    void* method_arg = env->api->method->get_arg_by_index(runtime, method, arg_index);
    
    void* method_arg_basic_type = env->api->arg->get_basic_type(runtime, method_arg);
    int32_t method_arg_basic_type_id = env->api->basic_type->get_id(runtime, method_arg_basic_type);
    int32_t method_arg_type_dimension = env->api->arg->get_type_dimension(runtime, method_arg);
    int32_t method_arg_type_flag = env->api->arg->get_type_flag(runtime, method_arg);
    int32_t method_arg_basic_type_category = env->api->basic_type->get_category(runtime, method_arg_basic_type);
    
    int32_t method_arg_is_object_type = env->api->runtime->is_object_type(runtime, method_arg_basic_type, method_arg_type_dimension, method_arg_type_flag);
    
    if (method_arg_is_object_type) {
      if (obj_arg) {
        void* arg_basic_type = env->get_object_basic_type(env, stack, obj_arg);
        int32_t arg_type_dimension = env->get_object_type_dimension(env, stack, obj_arg);
        
        int32_t can_assign = env->api->runtime->can_assign(
          runtime,
          method_arg_basic_type, method_arg_type_dimension, method_arg_type_flag,
          arg_basic_type, method_arg_type_dimension, 0
        );
        
        if (!can_assign) {
          return env->die(env, stack, "The %dth argument cannot be assigned.", arg_index + 1, __func__, FILE_NAME, __LINE__);
        }
      }
      
      stack[0].oval = obj_arg;
      
      stack_index++;
    }
    else {
      if (!obj_arg) {
        return env->die(env, stack, "The %dth argument must be defined.", arg_index + 1, __func__, FILE_NAME, __LINE__);
      }
      
      int32_t method_arg_type_is_ref = method_arg_type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF;
      
      int32_t stack_index = arg_index;
      
      if (!method_arg_type_is_ref) {
        if (method_arg_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC) {
          switch (method_arg_basic_type_id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Byte", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the Byte class.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              int8_t value = env->get_field_byte_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              stack[stack_index].bval = value;
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Short", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the Short class.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              int16_t value = env->get_field_short_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              stack[stack_index].sval = value;
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Int", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the Int class.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              int32_t value = env->get_field_int_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              stack[stack_index].ival = value;
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Long", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the Long class.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              int64_t value = env->get_field_long_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              stack[stack_index].lval = value;
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Float", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the Float class.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              float value = env->get_field_float_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              stack[stack_index].fval = value;
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "Double", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the Double class.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              double value = env->get_field_double_by_name(env, stack, obj_arg, "value", &error_id, __func__, FILE_NAME, __LINE__);
              if (error_id) { return error_id; }
              
              stack[stack_index].dval = value;
              break;
            }
            default: {
              assert(0);
            }
          }
          stack_index++;
        }
        else if (method_arg_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM) {
          int32_t method_arg_width = env->api->runtime->get_type_width(runtime, method_arg_basic_type, method_arg_type_dimension, method_arg_type_flag);
          
          int32_t arg_array_length = env->length(env, stack, obj_arg);
          
          if (!(arg_array_length == method_arg_width)) {
            return env->die(env, stack, "The array length of the %dth argument must be %d.", arg_index + 1, method_arg_width, __func__, FILE_NAME, __LINE__);
          }
          
          switch(method_arg_basic_type_id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "byte[]", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the byte[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              int8_t* value_ref = env->get_elems_byte(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                stack[stack_index + i].bval = value_ref[i];
              }
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "short[]", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the short[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              int16_t* value_ref = env->get_elems_short(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                stack[stack_index + i].sval = value_ref[i];
              }
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "int[]", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the int[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              int32_t* value_ref = env->get_elems_int(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                stack[stack_index + i].ival = value_ref[i];
              }
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
              if (!env->is_type_by_name(env, stack, obj_arg, "long[]", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the long[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              int64_t* value_ref = env->get_elems_long(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                stack[stack_index + i].lval = value_ref[i];
              }
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
              if (!env->is_type_by_name(env, stack, obj_arg, "float[]", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the float[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              float* value_ref = env->get_elems_float(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                stack[stack_index + i].fval = value_ref[i];
              }
              
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
              if (!env->is_type_by_name(env, stack, obj_arg, "double[]", 0)) {
                return env->die(env, stack, "The type of the %dth argument must be the double[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
              }
              
              double* value_ref = env->get_elems_double(env, stack, obj_arg);
              
              for (int32_t i = 0; i < method_arg_width; i++) {
                stack[stack_index + i].dval = value_ref[i];
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
            return env->die(env, stack, "The array length of the %dth argument must be 1.", arg_index + 1, __func__, FILE_NAME, __LINE__);
          }
        }
        else if (method_arg_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM) {
          int32_t method_arg_width = env->api->runtime->get_type_width(runtime, method_arg_basic_type, method_arg_type_dimension, method_arg_type_flag);
          
          int32_t arg_array_length = env->length(env, stack, obj_arg);
          
          if (!(arg_array_length == method_arg_width)) {
            return env->die(env, stack, "The array length of the %dth argument must be %d.", arg_index + 1, method_arg_width, __func__, FILE_NAME, __LINE__);
          }
        }
        else {
          assert(0);
        }
        
        switch(method_arg_basic_type_id) {
          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
            if (!env->is_type_by_name(env, stack, obj_arg, "byte[]", 0)) {
              return env->die(env, stack, "The type of the %dth argument must be the byte[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
            }
            
            int8_t* value_ref = env->get_elems_byte(env, stack, obj_arg);
            
            stack[stack_index].bref = value_ref;
            
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
            if (!env->is_type_by_name(env, stack, obj_arg, "short[]", 0)) {
              return env->die(env, stack, "The type of the %dth argument must be the short[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
            }
            
            int16_t* value_ref = env->get_elems_short(env, stack, obj_arg);
            
            stack[stack_index].sref = value_ref;
            
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
            if (!env->is_type_by_name(env, stack, obj_arg, "int[]", 0)) {
              return env->die(env, stack, "The type of the %dth argument must be the int[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
            }
            
            int32_t* value_ref = env->get_elems_int(env, stack, obj_arg);
            
            stack[stack_index].iref = value_ref;
            
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
            if (!env->is_type_by_name(env, stack, obj_arg, "long[]", 0)) {
              return env->die(env, stack, "The type of the %dth argument must be the long[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
            }
            
            int64_t* value_ref = env->get_elems_long(env, stack, obj_arg);
            
            stack[stack_index].lref = value_ref;
            
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
            if (!env->is_type_by_name(env, stack, obj_arg, "float[]", 0)) {
              return env->die(env, stack, "The type of the %dth argument must be the float[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
            }
            
            float* value_ref = env->get_elems_float(env, stack, obj_arg);
            
            stack[stack_index].fref = value_ref;
            
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
            if (!env->is_type_by_name(env, stack, obj_arg, "double[]", 0)) {
              return env->die(env, stack, "The type of the %dth argument must be the double[] type.", arg_index + 1, __func__, FILE_NAME, __LINE__);
            }
            
            double* value_ref = env->get_elems_double(env, stack, obj_arg);
            
            stack[stack_index].dref = value_ref;
            
            break;
          }
          default: {
            assert(0);
          }
        }
        stack_index++;
      }
    }
  }
  
  int32_t stack_length = stack_index;
  
  error_id = env->call_method(env, stack, method, stack_length);
  if (error_id) { return error_id; }
  
  void* method_return_basic_type = env->api->method->get_return_basic_type(runtime, method);
  int32_t method_return_basic_type_id = env->api->basic_type->get_id(runtime, method_return_basic_type);
  int32_t method_return_type_dimension = env->api->method->get_return_type_dimension(runtime, method);
  int32_t method_return_type_flag = env->api->method->get_return_type_flag(runtime, method);
  int32_t method_return_basic_type_category = env->api->basic_type->get_category(runtime, method_return_basic_type);
  
  int32_t method_return_is_object_type = env->api->runtime->is_object_type(runtime, method_return_basic_type, method_return_type_dimension, method_return_type_flag);
  
  if (method_return_is_object_type) {
    // Nothing to do
  }
  else {
    
    int32_t method_return_type_is_ref = method_return_type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF;
    
    assert(!method_return_type_is_ref);
    
    if (method_return_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC) {
      switch (method_return_basic_type_id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
          
          int8_t return_value = stack[0].bval;
          
          void* obj_return_value = env->new_object_by_name(env, stack, "Byte", &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
          
          int16_t return_value = stack[0].sval;
          
          void* obj_return_value = env->new_object_by_name(env, stack, "Short", &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
          
          int32_t return_value = stack[0].ival;
          
          void* obj_return_value = env->new_object_by_name(env, stack, "Int", &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
          
          int64_t return_value = stack[0].lval;
          
          void* obj_return_value = env->new_object_by_name(env, stack, "Long", &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
          
          float return_value = stack[0].fval;
          
          void* obj_return_value = env->new_object_by_name(env, stack, "Float", &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
          
          double return_value = stack[0].dval;
          
          void* obj_return_value = env->new_object_by_name(env, stack, "Double", &error_id, __func__, FILE_NAME, __LINE__);
          if (error_id) { return error_id; }
          
          stack[0].oval = obj_return_value;
          
          break;
        }
        default: {
          assert(0);
        }
      }
    }
    else if (method_return_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM) {
      int32_t method_return_width = env->api->runtime->get_type_width(runtime, method_return_basic_type, method_return_type_dimension, method_return_type_flag);
      
      switch(method_return_basic_type_id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
          void* obj_return_value = env->new_byte_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          int8_t* return_value_ref = env->get_elems_byte(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = stack[i].bval;
          }
          
          stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
          void* obj_return_value = env->new_short_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          int16_t* return_value_ref = env->get_elems_short(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = stack[i].sval;
          }
          
          stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
          void* obj_return_value = env->new_int_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          int32_t* return_value_ref = env->get_elems_int(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = stack[i].ival;
          }
          
          stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
          void* obj_return_value = env->new_long_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          int64_t* return_value_ref = env->get_elems_long(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = stack[i].lval;
          }
          
          stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
          void* obj_return_value = env->new_float_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          float* return_value_ref = env->get_elems_float(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = stack[i].fval;
          }
          
          stack[0].oval = obj_return_value;
          
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
          void* obj_return_value = env->new_double_array(env, stack, method_return_width);
          if (error_id) { return error_id; }
          
          double* return_value_ref = env->get_elems_double(env, stack, obj_return_value);
          
          for (int32_t i = 0; i < method_return_width; i++) {
            return_value_ref[i] = stack[i].dval;
          }
          
          stack[0].oval = obj_return_value;
          
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
  }
}

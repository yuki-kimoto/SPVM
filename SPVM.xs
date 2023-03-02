#define PERL_NO_GET_CONTEXT     /* For performance */
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#undef call_method
#undef leave_scope

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

#include "spvm_native.h"

static const char* FILE_NAME = "SPVM.xs";

SV* SPVM_XS_UTIL_new_sv_object(pTHX_ void* object, const char* class) {
  
  // Create object
  size_t iv_object = PTR2IV(object);
  SV* sviv_object = sv_2mortal(newSViv(iv_object));
  SV* sv_object = sv_2mortal(newRV_inc(sviv_object));

  HV* hv_data = (HV*)sv_2mortal((SV*)newHV());
  (void)hv_store(hv_data, "object", strlen("object"), SvREFCNT_inc(sv_object), 0);
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));
  
  HV* hv_class = gv_stashpv(class, 0);
  sv_bless(sv_data, hv_class);
  
  return sv_data;
}

SV* SPVM_XS_UTIL_new_sv_blessed_object(pTHX_ SV* sv_api, SV* sv_env, SV* sv_stack, void* object, const char* class) {
  
  // Create object
  size_t iv_object = PTR2IV(object);
  SV* sviv_object = sv_2mortal(newSViv(iv_object));
  SV* sv_object = sv_2mortal(newRV_inc(sviv_object));

  HV* hv_data = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));

  (void)hv_store(hv_data, "object", strlen("object"), SvREFCNT_inc(sv_object), 0);
  (void)hv_store(hv_data, "api", strlen("api"), SvREFCNT_inc(sv_api), 0);
  (void)hv_store(hv_data, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);
  (void)hv_store(hv_data, "stack", strlen("stack"), SvREFCNT_inc(sv_stack), 0);

  HV* hv_class = gv_stashpv(class, 0);
  sv_bless(sv_data, hv_class);
  
  return sv_data;
}

void* SPVM_XS_UTIL_get_object(pTHX_ SV* sv_data) {
  
  if (SvOK(sv_data)) {
    HV* hv_data = (HV*)SvRV(sv_data);
    
    SV** sv_object_ptr = hv_fetch(hv_data, "object", strlen("object"), 0);
    SV* sv_object = sv_object_ptr ? *sv_object_ptr : &PL_sv_undef;
    size_t iv_object = SvIV(SvRV(sv_object));
    void* object = INT2PTR(void*, iv_object);
    
    return object;
  }
  else {
    return NULL;
  }
}

SPVM_ENV* SPVM_XS_UTIL_get_env(pTHX_ SV* sv_env) {
  
  SPVM_ENV* env;
  if (sv_derived_from(sv_env, "SPVM::Builder::Env")) {
    HV* hv_env = (HV*)SvRV(sv_env);
    SV** sv_native_env_ptr = hv_fetch(hv_env, "object", strlen("object"), 0);
    SV* sv_native_env = sv_native_env_ptr ? *sv_native_env_ptr : &PL_sv_undef;
    env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_native_env)));
  }
  else if (sv_derived_from(sv_env, "SPVM::BlessedObject::Class")) {
    HV* hv_env = (HV*)SvRV(sv_env);
    
    // Stack
    SV** sv_blessed_object_stack_ptr = hv_fetch(hv_env, "stack", strlen("stack"), 0);
    SV* sv_blessed_object_stack = sv_blessed_object_stack_ptr ? *sv_blessed_object_stack_ptr : &PL_sv_undef;
    HV* hv_blessed_object_stack = (HV*)SvRV(sv_blessed_object_stack);
    SV** sv_native_blessed_object_stack_ptr = hv_fetch(hv_blessed_object_stack, "object", strlen("object"), 0);
    SV* sv_native_blessed_object_stack = sv_native_blessed_object_stack_ptr ? *sv_native_blessed_object_stack_ptr : &PL_sv_undef;
    SPVM_VALUE* blessed_object_stack = INT2PTR(SPVM_VALUE*, SvIV(SvRV(sv_native_blessed_object_stack)));
    
    // Env
    SV** sv_blessed_object_env_ptr = hv_fetch(hv_env, "env", strlen("env"), 0);
    SV* sv_blessed_object_env = sv_blessed_object_env_ptr ? *sv_blessed_object_env_ptr : &PL_sv_undef;
    HV* hv_blessed_object_env = (HV*)SvRV(sv_blessed_object_env);
    SV** sv_native_blessed_object_env_ptr = hv_fetch(hv_blessed_object_env, "object", strlen("object"), 0);
    SV* sv_native_blessed_object_env = sv_native_blessed_object_env_ptr ? *sv_native_blessed_object_env_ptr : &PL_sv_undef;
    SPVM_ENV* blessed_object_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_native_blessed_object_env)));

    SV** sv_obj_env_ptr = hv_fetch(hv_env, "object", strlen("object"), 0);
    SV* sv_obj_env = sv_obj_env_ptr ? *sv_obj_env_ptr : &PL_sv_undef;
    void* obj_env = INT2PTR(void*, SvIV(SvRV(sv_obj_env)));
    
    env = blessed_object_env->get_pointer(blessed_object_env, blessed_object_stack, obj_env);
  }
  
  return env;
}

SPVM_VALUE* SPVM_XS_UTIL_get_stack(pTHX_ SV* sv_stack) {
  
  SPVM_VALUE* stack;
  if (sv_derived_from(sv_stack, "SPVM::Builder::Stack")) {
    HV* hv_stack = (HV*)SvRV(sv_stack);
    SV** sv_native_stack_ptr = hv_fetch(hv_stack, "object", strlen("object"), 0);
    SV* sv_native_stack = sv_native_stack_ptr ? *sv_native_stack_ptr : &PL_sv_undef;
    stack = INT2PTR(SPVM_VALUE*, SvIV(SvRV(sv_native_stack)));
  }
  else if (sv_derived_from(sv_stack, "SPVM::BlessedObject::Class")) {
    HV* hv_stack = (HV*)SvRV(sv_stack);
    
    // Stack
    SV** sv_blessed_object_stack_ptr = hv_fetch(hv_stack, "stack", strlen("stack"), 0);
    SV* sv_blessed_object_stack = sv_blessed_object_stack_ptr ? *sv_blessed_object_stack_ptr : &PL_sv_undef;
    HV* hv_blessed_object_stack = (HV*)SvRV(sv_blessed_object_stack);
    SV** sv_native_blessed_object_stack_ptr = hv_fetch(hv_blessed_object_stack, "object", strlen("object"), 0);
    SV* sv_native_blessed_object_stack = sv_native_blessed_object_stack_ptr ? *sv_native_blessed_object_stack_ptr : &PL_sv_undef;
    SPVM_VALUE* blessed_object_stack = INT2PTR(SPVM_VALUE*, SvIV(SvRV(sv_native_blessed_object_stack)));
    
    // Env
    SV** sv_blessed_object_env_ptr = hv_fetch(hv_stack, "env", strlen("env"), 0);
    SV* sv_blessed_object_env = sv_blessed_object_env_ptr ? *sv_blessed_object_env_ptr : &PL_sv_undef;
    HV* hv_blessed_object_env = (HV*)SvRV(sv_blessed_object_env);
    SV** sv_native_blessed_object_env_ptr = hv_fetch(hv_blessed_object_env, "object", strlen("object"), 0);
    SV* sv_native_blessed_object_env = sv_native_blessed_object_env_ptr ? *sv_native_blessed_object_env_ptr : &PL_sv_undef;
    SPVM_ENV* blessed_object_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_native_blessed_object_env)));

    SV** sv_obj_stack_ptr = hv_fetch(hv_stack, "object", strlen("object"), 0);
    SV* sv_obj_stack = sv_obj_stack_ptr ? *sv_obj_stack_ptr : &PL_sv_undef;
    void* obj_stack = INT2PTR(void*, SvIV(SvRV(sv_obj_stack)));
    
    stack = blessed_object_env->get_pointer(blessed_object_env, blessed_object_stack, obj_stack);
  }
  
  return stack;
}

void* SPVM_XS_UTIL_new_mulnum_array(pTHX_ SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, SV* sv_elems, SV** sv_error) {
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    *sv_error = sv_2mortal(newSVpvf("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__));
    return NULL;
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Runtime
  void* runtime = env->runtime;
  
  int32_t basic_type_id = env->api->runtime->get_basic_type_id_by_name(env->runtime, basic_type_name);
  
  if (basic_type_id < 0) {
    *sv_error = sv_2mortal(newSVpvf("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__));
    return NULL;
  }
  
  // New array
  void* array = env->new_mulnum_array(env, stack, basic_type_id, length);

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;

    if (sv_derived_from(sv_element, "HASH")) {
      
      int32_t class_id = env->api->runtime->get_basic_type_class_id(env->runtime, basic_type_id);
      int32_t class_fields_length = env->api->runtime->get_class_fields_length(env->runtime, class_id);
      int32_t class_fields_base_id = env->api->runtime->get_class_fields_base_id(env->runtime, class_id);
      
      int32_t mulnum_field_id = class_fields_base_id;
      int32_t mulnum_field_type_id = env->api->runtime->get_field_type_id(env->runtime, mulnum_field_id);

      void* elems = (void*)env->get_elems_int(env, stack, array);
      
      HV* hv_value = (HV*)SvRV(sv_element);
      int32_t fields_length = class_fields_length;
      // Field exists check
      int32_t hash_keys_length = 0;
      while (hv_iternext(hv_value)) {
        hash_keys_length++;
      }
      
      for (int32_t field_index = 0; field_index < class_fields_length; field_index++) {
        int32_t mulnum_field_id = class_fields_base_id + field_index;
        int32_t mulnum_field_name_id = env->api->runtime->get_field_name_id(env->runtime, mulnum_field_id);
        
        const char* mulnum_field_name = env->api->runtime->get_constant_string_value(env->runtime, mulnum_field_name_id, NULL);
        
        SV** sv_field_value_ptr = hv_fetch(hv_value, mulnum_field_name, strlen(mulnum_field_name), 0);
        SV* sv_field_value;
        if (sv_field_value_ptr) {
          sv_field_value = *sv_field_value_ptr;
        }
        else {
          *sv_error = sv_2mortal(newSVpvf("The \"%s\" field of the %dth element must be defined\n    %s at %s line %d\n", mulnum_field_name, index + 1, __func__, FILE_NAME, __LINE__));
          return NULL;
        }

        int32_t mulnum_field_type_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, mulnum_field_type_id);
        switch (mulnum_field_type_basic_type_id) {
          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
            ((int8_t*)elems)[(fields_length * index) + field_index] = (int8_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
            ((int16_t*)elems)[(fields_length * index) + field_index] = (int16_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
            ((int32_t*)elems)[(fields_length * index) + field_index] = (int32_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
            ((int64_t*)elems)[(fields_length * index) + field_index] = (int64_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
            ((float*)elems)[(fields_length * index) + field_index] = (float)SvNV(sv_field_value);
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
            ((double*)elems)[(fields_length * index) + field_index] = (double)SvNV(sv_field_value);
            break;
          }
          default:
            assert(0);
        }
      }
    }
    else {
      *sv_error = sv_2mortal(newSVpvf("The element must be a hash reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__));
      return NULL;
    }
  }
  
  return array;
}

MODULE = SPVM::ExchangeAPI		PACKAGE = SPVM::ExchangeAPI

SV*
xs_call_method(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  // Invocant
  SV* sv_invocant = ST(1);
  
  // Method name
  SV* sv_method_name = ST(2);
  const char* method_name = SvPV_nolen(sv_method_name);
  
  // Class Name
  int32_t method_id;
  const char* class_name;
  int32_t class_method_call;
  if (sv_isobject(sv_invocant)) {
    class_method_call = 0;
    if (!sv_derived_from(sv_invocant, "SPVM::BlessedObject::Class")) {
      croak("The invocant must be a SPVM::BlessedObject::Class object");
    }
    
    HV* hv_invocant = (HV*)SvRV(sv_invocant);
    
    // Env
    SV** sv_env_ptr = hv_fetch(hv_invocant, "env", strlen("env"), 0);
    SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
    SPVM_ENV* object_env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
    
    if (!(object_env == env)) {
      croak("The env of the argument is differnt from the env of the invocant");
    }
    
    // Stack
    SV** sv_stack_ptr = hv_fetch(hv_invocant, "stack", strlen("stack"), 0);
    SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
    SPVM_VALUE* object_stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
    
    if (!(object_stack == stack)) {
      croak("The stack of the argument is differnt from the stack of the invocant");
    }
    
    void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_invocant);
    int32_t object_basic_type_id = env->get_object_basic_type_id(env, stack, object);
    int32_t object_basic_type_name_id = env->api->runtime->get_basic_type_name_id(env->runtime, object_basic_type_id);
    class_name = env->api->runtime->get_name(env->runtime, object_basic_type_name_id);
    
    char* found_char = strrchr(method_name, ':');
    if (found_char) {
      if (!(*(found_char - 1) == ':')) {
        croak("Invalid static instance method call");
      }
      *(found_char - 1) = '\0';
      const char* class_name = method_name;
      method_name = found_char + 1;
      
      method_id = env->get_instance_method_id_static(env, stack, class_name, method_name);
      
      *(found_char - 1) = ':';
    }
    else {
      method_id = env->get_instance_method_id(env, stack, object, method_name);
    }
    
    ST(1) = sv_method_name;
    ST(2) = sv_invocant;
  }
  else {
    class_method_call = 1;
    class_name = SvPV_nolen(sv_invocant);
    method_id = env->get_class_method_id(env, stack, class_name, method_name);
  }
  
  // Runtime
  void* runtime = env->runtime;
  
  // Method not found
  if (method_id < 0) {
    croak("The \"%s\" method in the \"%s\" class is not found\n    %s at %s line %d\n", method_name, class_name, __func__, FILE_NAME, __LINE__);
  }
  
  // Base index of SPVM arguments
  int32_t spvm_args_base;
  if (class_method_call) {
    spvm_args_base = 3;
  }
  else {
    spvm_args_base = 2;
  }

  int32_t method_is_class_method = env->api->runtime->get_method_is_class_method(env->runtime, method_id);
  int32_t method_args_length = env->api->runtime->get_method_args_length(env->runtime, method_id);
  int32_t method_required_args_length = env->api->runtime->get_method_required_args_length(env->runtime, method_id);
  int32_t method_args_base_id = env->api->runtime->get_method_args_base_id(env->runtime, method_id);
  int32_t method_return_type_id = env->api->runtime->get_method_return_type_id(env->runtime, method_id);
  
  // Check argument count
  int32_t call_method_args_length = items - spvm_args_base;
  
  if (call_method_args_length < method_required_args_length) {
    croak("Too few arguments are passed to the \"%s\" method in the \"%s\" class\n    %s at %s line %d\n", method_name, class_name, __func__, FILE_NAME, __LINE__);
  }
  else if (call_method_args_length > method_args_length) {
    croak("Too many arguments are passed to the \"%s\" method in the \"%s\" class\n    %s at %s line %d\n", method_name, class_name, __func__, FILE_NAME, __LINE__);
  }
  
  // 0-255 are used as arguments and return values. 256 is used as exception variable. 257 is used as mortal native_stack.
  int32_t stack_index = 0;

  // Arguments have reference type
  int32_t args_have_ref = 0;

  // Reference native_stack.
  int32_t ref_stack_index = 0;
  SPVM_VALUE ref_stack[256];
  int32_t ref_stack_indexes[256];

  // Arguments
  for (int32_t args_index = 0; args_index < method_args_length; args_index++) {
    
    if (args_index >= call_method_args_length) {
      break;
    }
    
    int32_t args_index_nth = args_index + (spvm_args_base - 2);
    
    // Get value from Perl argument native_stack
    SV* sv_value = ST(spvm_args_base + args_index);
    
    int32_t arg_id = method_args_base_id + args_index;
    int32_t arg_type_id = env->api->runtime->get_arg_type_id(env->runtime, arg_id);
    int32_t arg_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, arg_type_id);
    int32_t arg_basic_type_category = env->api->runtime->get_basic_type_category(env->runtime, arg_basic_type_id);
    int32_t arg_type_dimension = env->api->runtime->get_type_dimension(env->runtime, arg_type_id);
    int32_t arg_type_flag = env->api->runtime->get_type_flag(env->runtime, arg_type_id);
    
    if (arg_type_dimension == 0) {
      if (arg_type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF) {
        switch (arg_basic_type_category) {
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
            switch (arg_basic_type_id) {
              // Perl reference to SPVM byte reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                args_have_ref = 1;
                
                int32_t is_iok_scalar_ref;
                if (SvROK(sv_value)) {
                  is_iok_scalar_ref = SvIOK(SvRV(sv_value));
                }
                else {
                  is_iok_scalar_ref = 0;
                }
                
                if (!is_iok_scalar_ref) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be an interger reference\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                
                SV* sv_value_deref = SvRV(sv_value);
                int8_t value = (int8_t)SvIV(sv_value_deref);
                ref_stack[ref_stack_index].bval = value;
                stack[stack_index].oval = &ref_stack[ref_stack_index];
                ref_stack_indexes[args_index] = ref_stack_index;
                ref_stack_index++;
                stack_index++;
                break;
              }
              // Perl reference to SPVM short reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                args_have_ref = 1;
                int32_t is_iok_scalar_ref;
                if (SvROK(sv_value)) {
                  is_iok_scalar_ref = SvIOK(SvRV(sv_value));
                }
                else {
                  is_iok_scalar_ref = 0;
                }
                if (!is_iok_scalar_ref) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be an interger reference\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                SV* sv_value_deref = SvRV(sv_value);
                int16_t value = (int16_t)SvIV(sv_value_deref);
                ref_stack[ref_stack_index].sval = value;
                stack[stack_index].oval = &ref_stack[ref_stack_index];
                ref_stack_indexes[args_index] = ref_stack_index;
                ref_stack_index++;
                stack_index++;
                break;
              }
              // Perl reference to SPVM int reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                args_have_ref = 1;
                int32_t is_iok_scalar_ref;
                if (SvROK(sv_value)) {
                  is_iok_scalar_ref = SvIOK(SvRV(sv_value));
                }
                else {
                  is_iok_scalar_ref = 0;
                }
                if (!is_iok_scalar_ref) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be an interger reference\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                SV* sv_value_deref = SvRV(sv_value);
                int32_t value = (int32_t)SvIV(sv_value_deref);
                ref_stack[ref_stack_index].ival = value;
                stack[stack_index].oval = &ref_stack[ref_stack_index];
                ref_stack_indexes[args_index] = ref_stack_index;
                ref_stack_index++;
                stack_index++;
                break;
              }
              // Perl reference to SPVM long reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                args_have_ref = 1;
                int32_t is_iok_scalar_ref;
                if (SvROK(sv_value)) {
                  is_iok_scalar_ref = SvIOK(SvRV(sv_value));
                }
                else {
                  is_iok_scalar_ref = 0;
                }
                if (!is_iok_scalar_ref) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be an interger reference\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                SV* sv_value_deref = SvRV(sv_value);
                int64_t value = (int64_t)SvIV(sv_value_deref);
                ref_stack[ref_stack_index].lval = value;
                stack[stack_index].oval = &ref_stack[ref_stack_index];
                ref_stack_indexes[args_index] = ref_stack_index;
                ref_stack_index++;
                stack_index++;
                break;
              }
              // Perl reference to SPVM long reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                args_have_ref = 1;
                int32_t is_nok_scalar_ref;
                if (SvROK(sv_value)) {
                  is_nok_scalar_ref = SvNOK(SvRV(sv_value));
                }
                else {
                  is_nok_scalar_ref = 0;
                }
                if (!is_nok_scalar_ref) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a floating-point reference\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                SV* sv_value_deref = SvRV(sv_value);
                float value = (float)SvNV(sv_value_deref);
                ref_stack[ref_stack_index].fval = value;
                stack[stack_index].oval = &ref_stack[ref_stack_index];
                ref_stack_indexes[args_index] = ref_stack_index;
                ref_stack_index++;
                stack_index++;
                break;
              }
              // Perl reference to SPVM double reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                args_have_ref = 1;
                int32_t is_nok_scalar_ref;
                if (SvROK(sv_value)) {
                  is_nok_scalar_ref = SvNOK(SvRV(sv_value));
                }
                else {
                  is_nok_scalar_ref = 0;
                }
                if (!is_nok_scalar_ref) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a floating-point reference\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                SV* sv_value_deref = SvRV(sv_value);
                double value = (double)SvNV(sv_value_deref);
                ref_stack[ref_stack_index].dval = value;
                stack[stack_index].oval = &ref_stack[ref_stack_index];
                ref_stack_indexes[args_index] = ref_stack_index;
                ref_stack_index++;
                stack_index++;
                break;
              }
            }
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
          {
            args_have_ref = 1;
            HV* hv_value = NULL;
            if (SvOK(sv_value)) {
              if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
                SV* hv_value_ref = SvRV(sv_value);
                if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
                  hv_value = (HV*)SvRV(hv_value_ref);
                }
              }
            }
            if (hv_value == NULL) {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a scalar reference of a hash reference\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
            }
            int32_t arg_class_id = env->api->runtime->get_basic_type_class_id(env->runtime, arg_basic_type_id);
            int32_t arg_class_fields_length = env->api->runtime->get_class_fields_length(env->runtime, arg_class_id);
            int32_t arg_class_fields_base_id = env->api->runtime->get_class_fields_base_id(env->runtime, arg_class_id);
            int32_t arg_class_field_type_id = env->api->runtime->get_field_type_id(env->runtime, arg_class_fields_base_id);
            int32_t arg_class_field_type_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, arg_class_field_type_id);
            assert(arg_class_field_type_basic_type_id >= 0);
            for (int32_t field_index = 0; field_index < arg_class_fields_length; field_index++) {
              int32_t mulnum_field_id = arg_class_fields_base_id + field_index;
              int32_t mulnum_field_name_id = env->api->runtime->get_field_name_id(env->runtime, mulnum_field_id);
              const char* mulnum_field_name = env->api->runtime->get_constant_string_value(env->runtime, mulnum_field_name_id, NULL);
              SV** sv_field_value_ptr = hv_fetch(hv_value, mulnum_field_name, strlen(mulnum_field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                int32_t arg_class_name_id = env->api->runtime->get_class_name_id(env->runtime, arg_class_id);
                const char* arg_class_name = env->api->runtime->get_constant_string_value(env->runtime, arg_class_name_id, NULL);
                croak("The %dth argument of the \"%s\" field in the \"%s\" class is not found\n    %s at %s line %d\n", args_index_nth, mulnum_field_name, arg_class_name, __func__, FILE_NAME, __LINE__);
              }
              switch(arg_class_field_type_basic_type_id) {
                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                  int8_t value = (int8_t)SvIV(sv_field_value);
                  ((int8_t*)&ref_stack[ref_stack_index])[field_index] = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                  int16_t value = (int16_t)SvIV(sv_field_value);
                  ((int16_t*)&ref_stack[ref_stack_index])[field_index] = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                  int32_t value = (int32_t)SvIV(sv_field_value);
                  ((int32_t*)&ref_stack[ref_stack_index])[field_index] = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                  int64_t value = (int64_t)SvIV(sv_field_value);
                  ((int64_t*)&ref_stack[ref_stack_index])[field_index] = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                  float value = (float)SvNV(sv_field_value);
                  ((float*)&ref_stack[ref_stack_index])[field_index] = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                  double value = (double)SvNV(sv_field_value);
                  ((double*)&ref_stack[ref_stack_index])[field_index] = value;
                  break;
                }
                default: {
                  assert(0);
                }
              }
            }
            stack[stack_index].oval = &ref_stack[ref_stack_index];
            ref_stack_indexes[args_index] = ref_stack_index;
            ref_stack_index += arg_class_fields_length;
            stack_index++;
            break;
          }
          default: {
            assert(0);
          }
        }
      }
      // Non reference
      else {
        switch (arg_basic_type_category) {
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
            switch(arg_basic_type_id) {
              // Perl scalar to SPVM byte
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
                if (!(SvOK(sv_value) && SvNIOK(sv_value))) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a number\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                int8_t value = (int8_t)SvIV(sv_value);
                stack[stack_index].bval = value;
                stack_index++;
                break;
              }
              // Perl scalar to SPVM short
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
                if (!(SvOK(sv_value) && SvNIOK(sv_value))) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a number\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                int16_t value = (int16_t)SvIV(sv_value);
                stack[stack_index].sval = value;
                stack_index++;
                break;
              }
              // Perl scalar to SPVM int
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
                if (!(SvOK(sv_value) && SvNIOK(sv_value))) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a number\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                int32_t value = (int32_t)SvIV(sv_value);
                stack[stack_index].ival = value;
                stack_index++;
                break;
              }
              // Perl scalar to SPVM long
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
                if (!(SvOK(sv_value) && SvNIOK(sv_value))) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a number\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                int64_t value = (int64_t)SvIV(sv_value);
                stack[stack_index].lval = value;
                stack_index++;
                break;
              }
              // Perl scalar to SPVM float
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
                if (!(SvOK(sv_value) && SvNIOK(sv_value))) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a number\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                float value = (float)SvNV(sv_value);
                stack[stack_index].fval = value;
                stack_index++;
                break;
              }
              // Perl scalar to SPVM double
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
                if (!(SvOK(sv_value) && SvNIOK(sv_value))) {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a number\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
                double value = (double)SvNV(sv_value);
                stack[stack_index].dval = value;
                stack_index++;
                break;
              }
              default: {
                assert(0);
              }
            }
            break;
          }
          // Perl SPVM::BlessedObject::Class to SPVM class
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
          {
            if (!SvOK(sv_value)) {
              stack[stack_index].oval = NULL;
            }
            else {
              if (arg_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING) {
                // Perl non-ref scalar to SPVM string
                // If Perl value is non-ref scalar, the value is converted to SPVM::BlessedObject::String object
                if (!SvROK(sv_value)) {
                  // Convert Perl decoded string to loose UTF-8 bytes.
                  SV* sv_value_copy = sv_2mortal(newSVsv(sv_value));
                  const char* chars = SvPV_nolen(sv_value_copy);
                  int32_t length = SvCUR(sv_value_copy);
                  void* string = env->new_string(env, stack, chars, length);
                  
                  SV* sv_string = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, string, "SPVM::BlessedObject::String");
                  
                  sv_value = sv_string;
                }
                
                // Perl SPVM::BlessedObject::String to SPVM string
                if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject::String")) {
                  void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
                  
                  stack[stack_index].oval = object;
                }
                else {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::String object\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
              }
              else if (arg_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT) {
                if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject")) {
                  void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
                  stack[stack_index].oval = object;
                }
                else {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject object\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
              }
              else {
                if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject::Class")) {
                  void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
                  
                  if (!env->isa(env, stack, object, arg_basic_type_id, arg_type_dimension)) {
                    croak("The %dth argument of the \"%s\" method in the \"%s\" class must be assinged to the argument type\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                  }
                  
                  stack[stack_index].oval = object;
                }
                else {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::Class object\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
              }
            }
            stack_index++;
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
          {
            int32_t arg_class_id = env->api->runtime->get_basic_type_class_id(env->runtime, arg_basic_type_id);
            int32_t arg_class_fields_length = env->api->runtime->get_class_fields_length(env->runtime, arg_class_id);
            int32_t arg_class_fields_base_id = env->api->runtime->get_class_fields_base_id(env->runtime, arg_class_id);
            int32_t arg_class_field_type_id = env->api->runtime->get_field_type_id(env->runtime, arg_class_fields_base_id);
            int32_t arg_class_field_type_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, arg_class_field_type_id);
            assert(arg_class_field_type_basic_type_id >= 0);
            
            // Perl hash reference to SPVM multi numeric type
            if (sv_derived_from(sv_value, "HASH")) {
              HV* hv_value = (HV*)SvRV(sv_value);
              for (int32_t field_index = 0; field_index < arg_class_fields_length; field_index++) {
                int32_t mulnum_field_id = arg_class_fields_base_id + field_index;
                int32_t mulnum_field_name_id = env->api->runtime->get_field_name_id(env->runtime, mulnum_field_id);

                const char* mulnum_field_name = env->api->runtime->get_constant_string_value(env->runtime, mulnum_field_name_id, NULL);
                SV** sv_field_value_ptr = hv_fetch(hv_value, mulnum_field_name, strlen(mulnum_field_name), 0);
                SV* sv_field_value;
                if (sv_field_value_ptr) {
                  sv_field_value = *sv_field_value_ptr;
                }
                else {
                  int32_t arg_class_name_id = env->api->runtime->get_class_name_id(env->runtime, arg_class_id);
                  const char* arg_class_name = env->api->runtime->get_constant_string_value(env->runtime, arg_class_name_id, NULL);
                  croak("The \"%s\" field in the %dth argument must be defined. The field is defined in the \"%s\" class\n    %s at %s line %d\n", mulnum_field_name, args_index_nth, arg_class_name, __func__, FILE_NAME, __LINE__);
                }
                
                switch (arg_class_field_type_basic_type_id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    int8_t value = (int8_t)SvIV(sv_field_value);
                    stack[stack_index + field_index].bval = value;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    int16_t value = (int16_t)SvIV(sv_field_value);
                    stack[stack_index + field_index].sval = value;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    int32_t value = (int32_t)SvIV(sv_field_value);
                    stack[stack_index + field_index].ival = value;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    int64_t value = (int64_t)SvIV(sv_field_value);
                    stack[stack_index + field_index].lval = value;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    float value = (float)SvNV(sv_field_value);
                    stack[stack_index + field_index].fval = value;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    double value = (double)SvNV(sv_field_value);
                    stack[stack_index + field_index].dval = value;
                    break;
                  }
                  default: {
                    assert(0);
                  }
                }
              }
              stack_index += arg_class_fields_length;
            }
            else {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a hash reference\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
            }
            break;
          }
          default: {
            assert(0);
          }
        }
      }
    }
    else if (arg_type_dimension == 1) {
      switch (arg_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
          // Perl undef to SPVM undef
          if (!SvOK(sv_value)) {
            stack[stack_index].oval = NULL;
          }
          else {
            // Argument: Perl array referecne to SPVM array
            if (SvROK(sv_value) && sv_derived_from(sv_value, "ARRAY")) {
              
              SV* sv_elems = sv_value;
              AV* av_elems = (AV*)SvRV(sv_elems);
              int32_t length = av_len(av_elems) + 1;
              
              assert(arg_type_dimension == 1);
              
              switch (arg_basic_type_id) {
                // Argument: Perl array referecne to SPVM byte array
                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                  void* array = env->new_byte_array(env, stack, length);
                  int8_t* elems = env->get_elems_byte(env, stack, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int8_t)SvIV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                // Argument: Perl array referecne to SPVM short array
                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                  void* array = env->new_short_array(env, stack, length);
                  int16_t* elems = env->get_elems_short(env, stack, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int16_t)SvIV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                // Argument: Perl array referecne to SPVM int array
                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                  void* array = env->new_int_array(env, stack, length);
                  int32_t* elems = env->get_elems_int(env, stack, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int32_t)SvIV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                // Argument: Perl array referecne to SPVM long array
                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                  void* array = env->new_long_array(env, stack, length);
                  int64_t* elems = env->get_elems_long(env, stack, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int64_t)SvIV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                // Argument: Perl array referecne to SPVM float array
                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                  void* array = env->new_float_array(env, stack, length);
                  float* elems = env->get_elems_float(env, stack, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (float)SvNV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                // Argument: Perl array referecne to SPVM double array
                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                  void* array = env->new_double_array(env, stack, length);
                  double* elems = env->get_elems_double(env, stack, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (double)SvNV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                default: {
                  assert(0);
                }
              }
            }
            
            if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject::Array")) {
              void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
              
              int32_t isa = env->isa(env, stack, object, arg_basic_type_id, arg_type_dimension);
              if (!isa) {
                void* obj_compile_type_name = env->get_compile_type_name(env, stack, arg_basic_type_id, arg_type_dimension, arg_type_flag);
                const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
                croak("The object must be assigned to the %s type of the %dth argument of the \"%s\" method in the \"%s\" class\n    %s at %s line %d\n", compile_type_name, args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
              }
              
              stack[stack_index].oval = object;
            }
            else {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::Array object\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
            }
          }
          
          stack_index++;
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
        {
          // Perl undef to SPVM undef
          if (!SvOK(sv_value)) {
            stack[stack_index].oval = NULL;
          }
          else {
            // Argument: Perl array referecne to SPVM array
            if (SvROK(sv_value) && sv_derived_from(sv_value, "ARRAY")) {
              
              SV* sv_elems = sv_value;
              AV* av_elems = (AV*)SvRV(sv_elems);
              int32_t length = av_len(av_elems) + 1;
              
              SV* sv_error = NULL;
              const char* arg_basic_type_name = env->api->runtime->get_name(env->runtime, env->api->runtime->get_basic_type_name_id(env->runtime, arg_basic_type_id));
              void* array = SPVM_XS_UTIL_new_mulnum_array(aTHX_ env, stack, arg_basic_type_name, sv_value, &sv_error);
              if (sv_error) {
                croak_sv(sv_error);
              }
              SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
              sv_value = sv_array;
            }
            
            if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject::Array")) {
              void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
              
              int32_t isa = env->isa(env, stack, object, arg_basic_type_id, arg_type_dimension);
              if (!isa) {
                void* obj_compile_type_name = env->get_compile_type_name(env, stack, arg_basic_type_id, arg_type_dimension, arg_type_flag);
                const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
                croak("The object must be assigned to the %s type of the %dth argument of the \"%s\" method in the \"%s\" class\n    %s at %s line %d\n", compile_type_name, args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
              }
              
              stack[stack_index].oval = object;
            }
            else {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::Array object\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
            }
          }
          
          stack_index++;
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
        {
          // Perl undef to SPVM undef
          if (!SvOK(sv_value)) {
            stack[stack_index].oval = NULL;
          }
          else {
            // Perl array referecne of argument to SPVM array
            if (SvROK(sv_value) && sv_derived_from(sv_value, "ARRAY")) {
              // String array
              if (arg_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING) {
                SV* sv_elems = sv_value;
                AV* av_elems = (AV*)SvRV(sv_elems);
                int32_t length = av_len(av_elems) + 1;
                void* array = env->new_object_array(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, length);
                for (int32_t i = 0; i < length; i++) {
                  SV** sv_elem_ptr = av_fetch(av_elems, i, 0);
                  SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
                  if (!SvOK(sv_elem)) {
                    env->set_elem_object(env, stack, array, i, NULL);
                  }
                  else {
                    if (!SvROK(sv_elem)) {
                      SV* sv_elem_copy = sv_2mortal(newSVsv(sv_elem));
                      const char* chars = SvPV_nolen(sv_elem_copy);
                      int32_t length = SvCUR(sv_elem_copy);
                      void* string = env->new_string(env, stack, chars, length);
                      SV* sv_string = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, string, "SPVM::BlessedObject::String");
                      sv_elem = sv_string;
                    }
                    if (sv_isobject(sv_elem) && sv_derived_from(sv_elem, "SPVM::BlessedObject::String")) {
                      void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_elem);
                      env->set_elem_object(env, stack, array, i, object);
                    }
                    else {
                      croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::String object\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                    }
                  }
                }
                SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
                sv_value = sv_array;
              }
            }
            
            if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject::Array")) {
              void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
              
              int32_t isa = env->isa(env, stack, object, arg_basic_type_id, arg_type_dimension);
              if (!isa) {
                void* obj_compile_type_name = env->get_compile_type_name(env, stack, arg_basic_type_id, arg_type_dimension, arg_type_flag);
                const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
                croak("The object must be assigned to the %s type of the %dth argument of the \"%s\" method in the \"%s\" class\n    %s at %s line %d\n", compile_type_name, args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
              }
              
              stack[stack_index].oval = object;
            }
            else {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::Array object\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
            }
          }
          
          stack_index++;
          break;
        }
        default: {
          assert(0);
        }
      }
    }
    else if (arg_type_dimension > 1) {
      // Perl undef to SPVM undef
      if (!SvOK(sv_value)) {
        stack[stack_index].oval = NULL;
      }
      else {
        // Perl array referecne of argument to SPVM array
        if (SvROK(sv_value) && sv_derived_from(sv_value, "ARRAY")) {
          // String array
          if (arg_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING) {
            SV* sv_elems = sv_value;
            AV* av_elems = (AV*)SvRV(sv_elems);
            int32_t length = av_len(av_elems) + 1;
            void* array = env->new_object_array(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, length);
            for (int32_t i = 0; i < length; i++) {
              SV** sv_elem_ptr = av_fetch(av_elems, i, 0);
              SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
              if (!SvOK(sv_elem)) {
                env->set_elem_object(env, stack, array, i, NULL);
              }
              else {
                if (!SvROK(sv_elem)) {
                  SV* sv_elem_copy = sv_2mortal(newSVsv(sv_elem));
                  const char* chars = SvPV_nolen(sv_elem_copy);
                  int32_t length = SvCUR(sv_elem_copy);
                  void* string = env->new_string(env, stack, chars, length);
                  SV* sv_string = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, string, "SPVM::BlessedObject::String");
                  sv_elem = sv_string;
                }
                if (sv_isobject(sv_elem) && sv_derived_from(sv_elem, "SPVM::BlessedObject::String")) {
                  void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_elem);
                  env->set_elem_object(env, stack, array, i, object);
                }
                else {
                  croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::String object\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
                }
              }
            }
            SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
            sv_value = sv_array;
          }
        }
        
        if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject::Array")) {
          void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
          
          int32_t object_basic_type_id = env->get_object_basic_type_id(env, stack, object);
          int32_t object_type_dimension = env->get_object_type_dimension(env, stack, object);
          
          int32_t isa = env->isa(env, stack, object, arg_basic_type_id, arg_type_dimension);
          if (!isa) {
            void* obj_compile_type_name = env->get_compile_type_name(env, stack, arg_basic_type_id, arg_type_dimension, arg_type_flag);
            const char* compile_type_name = env->get_chars(env, stack, obj_compile_type_name);
            croak("The object must be assigned to the %s type of the %dth argument of the \"%s\" method in the \"%s\" class\n    %s at %s line %d\n", compile_type_name, args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
          }
          
          stack[stack_index].oval = object;
        }
        else {
          croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::Array object\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
        }
      }
      
      stack_index++;
      break;
    }
    else {
      assert(0);
    }
  }
  
  // Return
  int32_t method_return_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, method_return_type_id);
  int32_t method_return_type_dimension = env->api->runtime->get_type_dimension(env->runtime, method_return_type_id);
  int32_t method_return_basic_type_category = env->api->runtime->get_basic_type_category(env->runtime, method_return_basic_type_id);
  
  // Call method
  int32_t args_native_stack_length = stack_index;
  int32_t excetpion_flag = excetpion_flag = env->call_method(env, stack, method_id, args_native_stack_length);
  
  // Create Perl return value
  if (excetpion_flag) {
    void* exception = env->get_exception(env, stack);
    int32_t length = env->length(env, stack, exception);
    const char* exception_chars = env->get_chars(env, stack, exception);
    SV* sv_exception = sv_2mortal(newSVpvn((char*)exception_chars, length));
    croak("%s\n    %s at %s line %d\n", SvPV_nolen(sv_exception), __func__, FILE_NAME, __LINE__);
  }
  else {
    SV* sv_return_value = NULL;
    if (method_return_type_dimension == 0) {
      switch (method_return_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID: {
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
          switch (method_return_basic_type_id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
              sv_return_value = sv_2mortal(newSViv(stack[0].bval));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
              sv_return_value = sv_2mortal(newSViv(stack[0].sval));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
              sv_return_value = sv_2mortal(newSViv(stack[0].ival));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
              sv_return_value = sv_2mortal(newSViv(stack[0].lval));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
              sv_return_value = sv_2mortal(newSVnv(stack[0].fval));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
              sv_return_value = sv_2mortal(newSVnv(stack[0].dval));
              break;
            }
            default: {
              assert(0);
            }
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
        {
          int32_t method_return_class_id = env->api->runtime->get_basic_type_class_id(env->runtime, method_return_basic_type_id);
          int32_t method_return_class_fields_length = env->api->runtime->get_class_fields_length(env->runtime, method_return_class_id);
          int32_t method_return_class_fields_base_id = env->api->runtime->get_class_fields_base_id(env->runtime, method_return_class_id);
          int32_t method_return_mulnum_field_id = method_return_class_fields_base_id;
          int32_t method_return_mulnum_field_type_id = env->api->runtime->get_field_type_id(env->runtime, method_return_mulnum_field_id);
          int32_t method_return_mulnum_field_type_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, method_return_mulnum_field_type_id);
          
          HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
          for (int32_t field_index = 0; field_index < method_return_class_fields_length; field_index++) {
            SV* sv_field_value = NULL;
            switch (method_return_mulnum_field_type_basic_type_id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                sv_field_value = sv_2mortal(newSViv(stack[field_index].bval));
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                sv_field_value = sv_2mortal(newSViv(stack[field_index].sval));
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                sv_field_value = sv_2mortal(newSViv(stack[field_index].ival));
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                sv_field_value = sv_2mortal(newSViv(stack[field_index].lval));
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                sv_field_value = sv_2mortal(newSVnv(stack[field_index].fval));
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                sv_field_value = sv_2mortal(newSVnv(stack[field_index].dval));
                break;
              }
              default: {
                assert(0);
              }
            }
            
            int32_t mulnum_field_id = method_return_class_fields_base_id + field_index;
            int32_t mulnum_field_name_id = env->api->runtime->get_field_name_id(env->runtime, mulnum_field_id);
            const char* mulnum_field_name = env->api->runtime->get_constant_string_value(env->runtime, mulnum_field_name_id, NULL);
            (void)hv_store(hv_value, mulnum_field_name, strlen(mulnum_field_name), SvREFCNT_inc(sv_field_value), 0);
            sv_return_value = sv_2mortal(newRV_inc((SV*)hv_value));
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
        {
          void* return_value = (void*)stack[0].oval;
          sv_return_value = NULL;
          if (return_value != NULL) {
            env->inc_ref_count(env, stack, return_value);
            
            // Array
            if (env->get_object_type_dimension(env, stack, return_value) > 0) {
              sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, return_value, "SPVM::BlessedObject::Array");
            }
            else {
              
              int32_t return_value_basic_type_id = env->get_object_basic_type_id(env, stack, return_value);
              // String
              if (return_value_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING) {
                sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, return_value, "SPVM::BlessedObject::String");
              }
              // Object
              else {
                sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, return_value, "SPVM::BlessedObject::Class");
              }
            }
          }
          // undef
          else {
            sv_return_value = &PL_sv_undef;
          }
          break;
        }
        default: {
          assert(0);
        }
      }
    }
    else if (method_return_type_dimension == 1) {
      void* return_value = (void*)stack[0].oval;
      sv_return_value = NULL;
      if (return_value != NULL) {
        env->inc_ref_count(env, stack, return_value);
        
        // Array
        if (env->get_object_type_dimension(env, stack, return_value) > 0) {
          sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, return_value, "SPVM::BlessedObject::Array");
        }
        else {
          
          int32_t return_value_basic_type_id = env->get_object_basic_type_id(env, stack, return_value);
          // String
          if (return_value_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING) {
            sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, return_value, "SPVM::BlessedObject::String");
          }
          // Object
          else {
            sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, return_value, "SPVM::BlessedObject::Class");
          }
        }
      }
      // undef
      else {
        sv_return_value = &PL_sv_undef;
      }
    }
    else if (method_return_type_dimension > 1) {
      void* return_value = (void*)stack[0].oval;
      sv_return_value = NULL;
      if (return_value != NULL) {
        env->inc_ref_count(env, stack, return_value);
        sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, return_value, "SPVM::BlessedObject::Class");
      }
      // undef
      else {
        sv_return_value = &PL_sv_undef;
      }
    }
  
    // Restore reference value
    if (args_have_ref) {
      for (int32_t args_index = 0; args_index < method_args_length; args_index++) {
        SV* sv_value = ST(spvm_args_base + args_index);
        
        int32_t arg_id = method_args_base_id + args_index;
        int32_t arg_type_id = env->api->runtime->get_arg_type_id(env->runtime, arg_id);
        
        // Convert to runtime type
        int32_t arg_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, arg_type_id);
        int32_t arg_type_dimension = env->api->runtime->get_type_dimension(env->runtime, arg_type_id);
        int32_t arg_type_flag = env->api->runtime->get_type_flag(env->runtime, arg_type_id);
        int32_t arg_basic_type_category = env->api->runtime->get_basic_type_category(env->runtime, arg_basic_type_id);
        
        if (arg_type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF) {
          int32_t ref_stack_index = ref_stack_indexes[args_index];
          switch (arg_basic_type_category) {
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
              switch (arg_basic_type_id) {
                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
                  SV* sv_value_deref = SvRV(sv_value);
                  sv_setiv(sv_value_deref, ref_stack[ref_stack_index].bval);
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
                  SV* sv_value_deref = SvRV(sv_value);
                  sv_setiv(sv_value_deref, ref_stack[ref_stack_index].sval);
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
                  SV* sv_value_deref = SvRV(sv_value);
                  sv_setiv(sv_value_deref, ref_stack[ref_stack_index].ival);
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
                  SV* sv_value_deref = SvRV(sv_value);
                  sv_setiv(sv_value_deref, ref_stack[ref_stack_index].lval);
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
                  SV* sv_value_deref = SvRV(sv_value);
                  sv_setnv(sv_value_deref, ref_stack[ref_stack_index].fval);
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
                  SV* sv_value_deref = SvRV(sv_value);
                  sv_setnv(sv_value_deref, ref_stack[ref_stack_index].dval);
                  break;
                }
                default: {
                  assert(0);
                }
              }
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
            {
              HV* hv_value = (HV*)SvRV(SvRV(sv_value));
              int32_t arg_class_id = env->api->runtime->get_basic_type_class_id(env->runtime, arg_basic_type_id);
              int32_t arg_class_fields_length = env->api->runtime->get_class_fields_length(env->runtime, arg_class_id);
              int32_t arg_class_fields_base_id = env->api->runtime->get_class_fields_base_id(env->runtime, arg_class_id);
              int32_t arg_class_field_type_id = env->api->runtime->get_field_type_id(env->runtime, arg_class_fields_base_id);
              int32_t arg_class_field_type_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, arg_class_field_type_id);
              int32_t arg_mulnum_field_id = arg_class_fields_base_id;
              int32_t arg_mulnum_field_name_id = env->api->runtime->get_field_name_id(env->runtime, arg_mulnum_field_id);
              for (int32_t field_index = 0; field_index < arg_class_fields_length; field_index++) {
                int32_t mulnum_field_id = arg_class_fields_base_id + field_index;
                int32_t mulnum_field_name_id = env->api->runtime->get_field_name_id(env->runtime, mulnum_field_id);
                const char* mulnum_field_name = env->api->runtime->get_constant_string_value(env->runtime, mulnum_field_name_id, NULL);
                SV* sv_field_value;
                switch (arg_class_field_type_basic_type_id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    sv_field_value = sv_2mortal(newSViv(((int8_t*)&ref_stack[ref_stack_index])[field_index]));
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    sv_field_value = sv_2mortal(newSViv(((int16_t*)&ref_stack[ref_stack_index])[field_index]));
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    sv_field_value = sv_2mortal(newSViv(((int32_t*)&ref_stack[ref_stack_index])[field_index]));
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    sv_field_value = sv_2mortal(newSViv(((int64_t*)&ref_stack[ref_stack_index])[field_index]));
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    sv_field_value = sv_2mortal(newSVnv(((float*)&ref_stack[ref_stack_index])[field_index]));
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    sv_field_value = sv_2mortal(newSVnv(((double*)&ref_stack[ref_stack_index])[field_index]));
                    break;
                  }
                  default: {
                    assert(0);
                  }
                }
                (void)hv_store(hv_value, mulnum_field_name, strlen(mulnum_field_name), SvREFCNT_inc(sv_field_value), 0);
              }
            }
          }
        }
        else {
          assert(0);
        }
      }
    }
    int32_t return_count;
    if (method_return_type_dimension == 0 && method_return_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID) {
      return_count = 0;
    }
    else {
      XPUSHs(sv_return_value);
      return_count = 1;
    }
  
    XSRETURN(return_count);
  }
}

SV*
xs_array_to_elems(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_array = ST(1);
  
  // Runtime
  void* runtime = env->runtime;

  // Array must be a SPVM::BlessedObject::Array or SPVM::BlessedObject::Array
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array"))) {
    croak("The array must be a SPVM::BlessedObject::Array object\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
  
  int32_t length = env->length(env, stack, array);

  int32_t basic_type_id = env->get_object_basic_type_id(env, stack, array);
  int32_t dimension = env->get_object_type_dimension(env, stack, array);
  int32_t is_array_type = dimension > 0;
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  if (is_array_type) {
    int32_t element_type_dimension = dimension - 1;
    
    int32_t array_is_mulnum_array = env->is_mulnum_array(env, stack, array);
    int32_t array_is_object_array = env->is_object_array(env, stack, array);

    if (array_is_mulnum_array) {
      
      for (int32_t index = 0; index < length; index++) {
        int32_t class_id = env->api->runtime->get_basic_type_class_id(env->runtime, env->get_object_basic_type_id(env, stack, array));
        int32_t class_fields_length = env->api->runtime->get_class_fields_length(env->runtime, class_id);
        int32_t class_fields_base_id = env->api->runtime->get_class_fields_base_id(env->runtime, class_id);
        
        int32_t mulnum_field_id = class_fields_base_id;
        int32_t mulnum_field_type_id = env->api->runtime->get_field_type_id(env->runtime, mulnum_field_id);

        void* elems = (void*)env->get_elems_int(env, stack, array);
        
        HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
        int32_t field_length = class_fields_length;
        for (int32_t field_index = 0; field_index < class_fields_length; field_index++) {
          int32_t mulnum_field_id = class_fields_base_id + field_index;
          int32_t mulnum_field_name_id = env->api->runtime->get_field_name_id(env->runtime, mulnum_field_id);

          const char* mulnum_field_name = env->api->runtime->get_constant_string_value(env->runtime, mulnum_field_name_id, NULL);

          SV* sv_field_value;
          int32_t mulnum_field_type_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, mulnum_field_type_id);
          switch (mulnum_field_type_basic_type_id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
              int8_t field_value = ((int8_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
              int16_t field_value = ((int16_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
              int32_t field_value = ((int32_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
              int64_t field_value = ((int64_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
              float field_value = ((float*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSVnv(field_value));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
              double field_value = ((double*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSVnv(field_value));
              break;
            }
            default: {
              assert(0);
            }
          }
          SvREFCNT_inc(sv_field_value);
          (void)hv_store(hv_value, mulnum_field_name, strlen(mulnum_field_name), sv_field_value, 0);
        }
        SV* sv_value = sv_2mortal(newRV_inc((SV*)hv_value));
        av_push(av_values, SvREFCNT_inc(sv_value));
      }
    }
    else if (array_is_object_array) {
      if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING) {
        for (int32_t i = 0; i < length; i++) {
          void* object = env->get_elem_object(env, stack, array, i);
          
          SV* sv_value;
          if (object != NULL) {
            env->inc_ref_count(env, stack, object);
            sv_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, object, "SPVM::BlessedObject::String");
          }
          else {
            sv_value = &PL_sv_undef;
          }
          
          av_push(av_values, SvREFCNT_inc(sv_value));
        }
      }
      else {
        for (int32_t index = 0; index < length; index++) {
          // Index
          void* value = env->get_elem_object(env, stack, array, index);
          if (value == NULL) {
            av_push(av_values, &PL_sv_undef);
          }
          else {
            env->inc_ref_count(env, stack, value);
            int32_t element_type_is_array_type = element_type_dimension > 0;
            SV* sv_value;
            if (element_type_is_array_type) {
              sv_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, value, "SPVM::BlessedObject::Array");
            }
            else {
              sv_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, value, "SPVM::BlessedObject::Class");
            }
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
        }
      }
    }
    else {
      switch (basic_type_id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, stack, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, stack, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          int32_t* elems = env->get_elems_int(env, stack, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, stack, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          float* elems = env->get_elems_float(env, stack, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSVnv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, stack, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSVnv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        default:
          assert(0);
      }
    }
  }
  else {
    croak("The object must be an array type\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }

  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
xs_array_to_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_array = ST(1);
  
  // Runtime
  void* runtime = env->runtime;

  // Array must be a SPVM::BlessedObject::Array object or SPVM::BlessedObject::String
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array"))) {
    croak("The array must be a SPVM::BlessedObject::Array\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }

  // Get object
  void* array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
  
  int32_t length = env->length(env, stack, array);

  int32_t basic_type_id = env->get_object_basic_type_id(env, stack, array);
  int32_t dimension = env->get_object_type_dimension(env, stack, array);
  int32_t is_array_type = dimension > 0;
  
  SV* sv_bin;
  if (is_array_type) {
    int32_t element_type_dimension = dimension - 1;

    int32_t array_is_mulnum_array = env->is_mulnum_array(env, stack, array);
    int32_t array_is_object_array = env->is_object_array(env, stack, array);

    if (array_is_mulnum_array) {
      int32_t class_id = env->api->runtime->get_basic_type_class_id(env->runtime, basic_type_id);
      int32_t class_fields_length = env->api->runtime->get_class_fields_length(env->runtime, class_id);
      int32_t class_fields_base_id = env->api->runtime->get_class_fields_base_id(env->runtime, class_id);

      int32_t mulnum_field_id = class_fields_base_id;
      int32_t mulnum_field_type_id = env->api->runtime->get_field_type_id(env->runtime, mulnum_field_id);

      int32_t field_length = class_fields_length;

      int32_t mulnum_field_type_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, mulnum_field_type_id);
      switch (mulnum_field_type_basic_type_id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 2));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          int32_t* elems = env->get_elems_int(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 4));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 8));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          float* elems = env->get_elems_float(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 4));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 8));
          break;
        }
        default: {
          assert(0);
        }
      }
    }
    else if (array_is_object_array) {
      croak("The array can't be an object array\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    else {
      switch (basic_type_id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 2));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          int32_t* elems = env->get_elems_int(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 4));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 8));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          float* elems = env->get_elems_float(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 4));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, stack, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 8));
          break;
        }
        default: {
          assert(0);
        }
      }
    }
  }
  else {
    croak("The object must be an array type\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_bin);
  XSRETURN(1);
}

SV*
xs_string_object_to_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_string = ST(1);
  
  // Runtime
  void* runtime = env->runtime;

  // String must be a SPVM::BlessedObject::String or SPVM::BlessedObject::String
  if (!(SvROK(sv_string) && sv_derived_from(sv_string, "SPVM::BlessedObject::String"))) {
    croak("The string must be a SPVM::BlessedObject::String object\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // Get object
  void* string = SPVM_XS_UTIL_get_object(aTHX_ sv_string);
  
  int32_t length = env->length(env, stack, string);
  const char* chars = env->get_chars(env, stack, string);

  SV* sv_return_value = sv_2mortal(newSVpv(chars, length));

  XPUSHs(sv_return_value);
  XSRETURN(1);
}

SV*
xs_array_length(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_array = ST(1);

  // Runtime
  void* runtime = env->runtime;

  // Array must be a SPVM::BlessedObject::Array or SPVM::BlessedObject::Array
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array"))) {
    croak("The array must be a SPVM::BlessedObject::Array object\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
  
  int32_t length = env->length(env, stack, array);


  SV* sv_length = sv_2mortal(newSViv(length));
  
  XPUSHs(sv_length);
  XSRETURN(1);
}

SV*
xs_array_set(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_array = ST(1);
  SV* sv_index = ST(2);
  SV* sv_value = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
  
  // Length
  int32_t length = env->length(env, stack, array);
  
  // Check range
  if (!(index >= 0 || index < length)) {
    croak("The index must be more than or equal to 0 and less than the length");
  }

  int32_t basic_type_id = env->get_object_basic_type_id(env, stack, array);
  int32_t dimension = env->get_object_type_dimension(env, stack, array);

  if (dimension == 1) {
    switch (basic_type_id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
        // Value
        int8_t value = (int8_t)SvIV(sv_value);
        
        // Set element
        int8_t* elements = env->get_elems_byte(env, stack, array);
        
        elements[index] = value;
        
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
        // Value
        int16_t value = (int16_t)SvIV(sv_value);
        
        // Set element
        int16_t* elements = env->get_elems_short(env, stack, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
        // Value
        int32_t value = (int32_t)SvIV(sv_value);
        
        // Set element
        int32_t* elements = env->get_elems_int(env, stack, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
        // Value
        int64_t value = (int64_t)SvIV(sv_value);
        
        // Set element
        int64_t* elements = env->get_elems_long(env, stack, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
        // Value
        float value = (float)SvNV(sv_value);
        
        // Set element
        float* elements = env->get_elems_float(env, stack, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
        // Value
        double value = (double)SvNV(sv_value);
        
        // Set element
        double* elements = env->get_elems_double(env, stack, array);
        
        elements[index] = value;
        break;
      }
      default: {
        // Get object
        void* value = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
        
        env->set_elem_object(env, stack, array, index, value);
      }
    }
  }
  else if (dimension > 1) {
    
    // Get object
    void* value = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
    
    env->set_elem_object(env, stack, array, index, value);
  }
  else {
    assert(0);
  }
  
  XSRETURN(0);
}

SV*
xs_array_get(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_array = ST(1);
  SV* sv_index = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
  
  // Length
  int32_t length = env->length(env, stack, array);
  
  // Check range
  if (!(index >= 0 || index < length)) {
    croak("The index must be more than or equal to 0 and less than the length");
  }

  int32_t basic_type_id = env->get_object_basic_type_id(env, stack, array);
  int32_t dimension = env->get_object_type_dimension(env, stack, array);

  SV* sv_value = NULL;
  _Bool is_object = 0;
  if (dimension == 1) {
    switch (basic_type_id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
        // Get element
        int8_t* elements = env->get_elems_byte(env, stack, array);
        int8_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
        // Get element
        int16_t* elements = env->get_elems_short(env, stack, array);
        int16_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
        // Get element
        int32_t* elements = env->get_elems_int(env, stack, array);
        int32_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
        // Get element
        int64_t* elements = env->get_elems_long(env, stack, array);
        int64_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
        // Get element
        float* elements = env->get_elems_float(env, stack, array);
        float value = elements[index];
        sv_value = sv_2mortal(newSVnv(value));
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
        // Get element
        double* elements = env->get_elems_double(env, stack, array);
        double value = elements[index];
        sv_value = sv_2mortal(newSVnv(value));
        break;
      }
      default:
        is_object = 1;
    }
  }
  else if (dimension > 1) {
    is_object = 1;
  }
  else {
    assert(0);
  }
  
  if (is_object) {
    void* runtime = env->runtime;
    
    // Element dimension
    int32_t element_dimension = env->get_object_type_dimension(env, stack, array) - 1;
    
    // Index
    void* value = env->get_elem_object(env, stack, array, index);
    if (value != NULL) {
      env->inc_ref_count(env, stack, value);
    }
    
    if (element_dimension == 0) {
      sv_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, value, "SPVM::BlessedObject::Class");
    }
    else if (element_dimension > 0) {
      sv_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, value, "SPVM::BlessedObject::Array");
    }
  }
  
  XPUSHs(sv_value);
  XSRETURN(1);
}

SV*
xs_new_string_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }

    AV* av_elems = (AV*)SvRV(sv_elems);

    int32_t length = av_len(av_elems) + 1;

    // New array
    void* array = env->new_object_array(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, length);

    for (int32_t i = 0; i < length; i++) {
      SV** sv_str_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_str_value = sv_str_value_ptr ? *sv_str_value_ptr : &PL_sv_undef;
      if (SvOK(sv_str_value)) {
        // Copy
        SV* sv_str_value_copy = sv_2mortal(newSVsv(sv_str_value));
        
        int32_t length = sv_len(sv_str_value_copy);
        const char* chars = SvPV_nolen(sv_str_value_copy);
        
        void* string = env->new_string_raw(env, stack, chars, length);
        env->set_elem_object(env, stack, array, i, string);
      }
      else {
        env->set_elem_object(env, stack, array, i, NULL);
      }
    }

    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_string(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_value = ST(1);
  
  SV* sv_string;
  if (SvOK(sv_value)) {
    
    if (SvROK(sv_value)) {
      croak("The string can't be a reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    else {
      // Copy
      SV* sv_value_tmp = sv_2mortal(newSVsv(sv_value));
      
      // Encode to UTF-8
      
      int32_t length = sv_len(sv_value_tmp);
      
      const char* value = SvPV_nolen(sv_value_tmp);
      
      void* string = env->new_string(env, stack, value, length);
      
      sv_string = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, string, "SPVM::BlessedObject::String");
    }
  }
  else {
    croak("The string must be defined\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

SV*
xs_new_string_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_binary = ST(1);
  
  SV* sv_string;
  if (SvOK(sv_binary)) {
    if (SvROK(sv_binary)) {
      croak("The binary can't be a reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    else {
      int32_t binary_length = sv_len(sv_binary);
      int32_t string_length = binary_length;
      int8_t* binary = (int8_t*)SvPV_nolen(sv_binary);
      
      // New string
      void* string = env->new_string(env, stack, (const char*)binary, string_length);

      const char* chars = env->get_chars(env, stack, string);
      memcpy((char*)chars, binary, string_length);
      
      // New sv string
      sv_string = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, string, "SPVM::BlessedObject::String");
    }
  }
  else {
    croak("The binary must be defined\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

SV*
xs_new_address_object(...)
  PPCODE:
{
  (void)RETVAL;
  
  int32_t e = 0;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_address = ST(1);
  
  void* address = (void*)(intptr_t)SvIV(sv_address);
  
  void* obj_address = env->new_pointer_object_by_name(env, stack, "Address", address, &e, __func__, FILE_NAME, __LINE__);
  if (e) {
    croak("Can't create the Address object");
  }
  SV* sv_obj_address = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, obj_address, "SPVM::BlessedObject::Class");
  
  XPUSHs(sv_obj_address);
  XSRETURN(1);
}

SV*
xs_new_byte_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array Length
    int32_t length = av_len(av_elems) + 1;
    
    // New byte array
    void* array = env->new_byte_array(env, stack, length);
    
    // Copy Perl elements to SPVM elements
    int8_t* elems = env->get_elems_byte(env, stack, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int8_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_byte_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array Length
    int32_t length = av_len(av_elems) + 1;
    
    // New byte array
    void* array = env->new_byte_array(env, stack, length);
    
    // Copy Perl elements to SPVM elements
    int8_t* elems = env->get_elems_byte(env, stack, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint8_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_byte_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("The length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* array = env->new_byte_array(env, stack, length);
  
  // New sv array
  SV* sv_byte_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_byte_array);
  XSRETURN(1);
}

SV*
xs_new_byte_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length;
    int8_t* binary = (int8_t*)SvPV_nolen(sv_binary);
    
    // New array
    void* array = env->new_byte_array(env, stack, array_length);

    int8_t* elems = env->get_elems_byte(env, stack, array);
    memcpy(elems, binary, array_length);
    
    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_short_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    void* array = env->new_short_array(env, stack, length);
    
    // Copy Perl elements to SPVM elements
    int16_t* elems = env->get_elems_short(env, stack, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int16_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_short_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    void* array = env->new_short_array(env, stack, length);
    
    // Copy Perl elements to SPVM elements
    int16_t* elems = env->get_elems_short(env, stack, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint16_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_short_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("The length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* array = env->new_short_array(env, stack, length);
  
  // New sv array
  SV* sv_short_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_short_array);
  XSRETURN(1);
}

SV*
xs_new_short_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(int16_t);
    int16_t* binary = (int16_t*)SvPV_nolen(sv_binary);
    
    // Environment
    
    // New array
    void* array = env->new_short_array(env, stack, array_length);

    int16_t* elems = env->get_elems_short(env, stack, array);
    memcpy(elems, binary, array_length * sizeof(int16_t));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_int_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    void* array = env->new_int_array(env, stack, length);
    
    // Copy Perl elements to SPVM erlements
    int32_t* elems = env->get_elems_int(env, stack, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int32_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_int_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    void* array = env->new_int_array(env, stack, length);
    
    // Copy Perl elements to SPVM erlements
    int32_t* elems = env->get_elems_int(env, stack, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint32_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_int_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("The length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* array = env->new_int_array(env, stack, length);
  
  // New sv array
  SV* sv_int_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_int_array);
  XSRETURN(1);
}

SV*
xs_new_int_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(int32_t);
    int32_t* binary = (int32_t*)SvPV_nolen(sv_binary);
    
    // New array
    void* array = env->new_int_array(env, stack, array_length);

    int32_t* elems = env->get_elems_int(env, stack, array);
    memcpy(elems, binary, array_length * sizeof(int32_t));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_long_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    void* array = env->new_long_array(env, stack, length);
    
    // Copy Perl elements to SPVM elements
    int64_t* elems = env->get_elems_long(env, stack, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int64_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_long_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    void* array = env->new_long_array(env, stack, length);
    
    // Copy Perl elements to SPVM elements
    int64_t* elems = env->get_elems_long(env, stack, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint64_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_long_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("The length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* array = env->new_long_array(env, stack, length);
  
  // New sv array
  SV* sv_long_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_long_array);
  XSRETURN(1);
}

SV*
xs_new_long_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(int64_t);
    int64_t* binary = (int64_t*)SvPV_nolen(sv_binary);
    
    // New array
    void* array = env->new_long_array(env, stack, array_length);

    int64_t* elems = env->get_elems_long(env, stack, array);
    memcpy(elems, binary, array_length * sizeof(int64_t));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_float_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    void* array = env->new_float_array(env, stack, length);

    float* elems = env->get_elems_float(env, stack, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (float)SvNV(sv_value);
    }
    
    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_float_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("The length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* array = env->new_float_array(env, stack, length);
  
  // New sv array
  SV* sv_float_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_float_array);
  XSRETURN(1);
}

SV*
xs_new_float_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(float);
    float* binary = (float*)SvPV_nolen(sv_binary);
    
    // New array
    void* array = env->new_float_array(env, stack, array_length);

    float* elems = env->get_elems_float(env, stack, array);
    memcpy(elems, binary, array_length * sizeof(float));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_double_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    void* array = env->new_double_array(env, stack, length);

    double* elems = env->get_elems_double(env, stack, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (double)SvNV(sv_value);
    }
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_double_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("The length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* array = env->new_double_array(env, stack, length);
  
  // New sv array
  SV* sv_double_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_double_array);
  XSRETURN(1);
}

SV*
xs_new_double_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(double);
    double* binary = (double*)SvPV_nolen(sv_binary);
    
    // New array
    void* array = env->new_double_array(env, stack, array_length);

    double* elems = env->get_elems_double(env, stack, array);
    memcpy(elems, binary, array_length * sizeof(double));
    
    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_string_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_length = ST(1);

  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("The length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // Element type id
  const char* basic_type_name = "string";
  
  int32_t basic_type_id = env->api->runtime->get_basic_type_id_by_name(env->runtime, basic_type_name);
  
  // New array
  void* array = env->new_object_array(env, stack, basic_type_id, length);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_new_object_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_basic_type_name = ST(1);
  SV* sv_length = ST(2);

  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("The length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  int32_t basic_type_id = env->api->runtime->get_basic_type_id_by_name(env->runtime, basic_type_name);
  assert(basic_type_id >= 0);
  
  // New array
  void* array = env->new_object_array(env, stack, basic_type_id, length);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_object_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_basic_type_name = ST(1);
  SV* sv_elems = ST(2);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Runtime
  void* runtime = env->runtime;
  
 int32_t basic_type_id = env->api->runtime->get_basic_type_id_by_name(env->runtime, basic_type_name);
  assert(basic_type_id >= 0);
  
  // New array
  void* array = env->new_object_array(env, stack, basic_type_id, length);

  int32_t array_basic_type_id  = env->get_object_basic_type_id(env, stack, array);
  int32_t array_type_dimension = env->get_object_type_dimension(env, stack, array);
  int32_t element_type_dimension = array_type_dimension - 1;

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;
    
    if (!SvOK(sv_element)) {
      env->set_elem_object(env, stack, array, index, NULL);
    }
    else if (sv_isobject(sv_element) && sv_derived_from(sv_element, "SPVM::BlessedObject")) {
      void* element = SPVM_XS_UTIL_get_object(aTHX_ sv_element);

      int32_t elem_isa = env->elem_isa(env, stack, array, element);
      if (elem_isa) {
        env->set_elem_object(env, stack, array, index, element);
      }
      else {
        void* obj_element_type_name = env->get_type_name(env, stack, element);
        const char* element_type_name = env->get_chars(env, stack, obj_element_type_name);
        croak("The element must be assigned to the %s type\n    %s at %s line %d\n", element_type_name, __func__, FILE_NAME, __LINE__);
      }
    }
    else {
      croak("The element must be a SPVM::BlessedObject object\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_muldim_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_basic_type_name = ST(1);
  SV* sv_element_type_dimension = ST(2);
  SV* sv_elems = ST(3);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("The elements must be an array reference\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Runtime
  void* runtime = env->runtime;

  int32_t element_type_dimension = (int32_t)SvIV(sv_element_type_dimension);

  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
 int32_t basic_type_id = env->api->runtime->get_basic_type_id_by_name(env->runtime, basic_type_name);
  assert(basic_type_id >= 0);
  
  // New array
  void* array = env->new_muldim_array(env, stack, basic_type_id, element_type_dimension, length);
  
  int32_t array_basic_type_id = env->get_object_basic_type_id(env, stack, array);

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;
    
    if (!SvOK(sv_element)) {
      env->set_elem_object(env, stack, array, index, NULL);
    }
    else if (sv_isobject(sv_element) && sv_derived_from(sv_element, "SPVM::BlessedObject")) {
      void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_element);
      
      int32_t elem_isa = env->elem_isa(env, stack, array, object);
      if (elem_isa) {
        env->set_elem_object(env, stack, array, index, object);
      }
      else {
        croak("The object must be assigned to the element of the array\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
      }
    }
    else {
      croak("The element must be inherit SPVM::BlessedObject object\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_mulnum_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_basic_type_name = ST(1);
  SV* sv_elems = ST(2);

  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SV* sv_error = NULL;
  void* array = SPVM_XS_UTIL_new_mulnum_array(aTHX_ env, stack, basic_type_name, sv_elems, &sv_error);
  
  if (sv_error) {
    croak_sv(sv_error);
  }
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_mulnum_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_basic_type_name = ST(1);
  SV* sv_binary = ST(2);
  
  if (!SvOK(sv_binary)) {
    croak("The binary must be defined\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  void* binary = (void*)SvPV_nolen(sv_binary);
  
  int32_t binary_length = sv_len(sv_binary);
  
  // Runtime
  void* runtime = env->runtime;
  
  int32_t basic_type_id = env->api->runtime->get_basic_type_id_by_name(env->runtime, basic_type_name);
  
  if (basic_type_id < 0) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }

  int32_t class_id = env->api->runtime->get_basic_type_class_id(env->runtime, basic_type_id);
  int32_t class_fields_length = env->api->runtime->get_class_fields_length(env->runtime, class_id);
  int32_t class_fields_base_id = env->api->runtime->get_class_fields_base_id(env->runtime, class_id);
  
  int32_t mulnum_field_id = class_fields_base_id;
  int32_t mulnum_field_type_id = env->api->runtime->get_field_type_id(env->runtime, mulnum_field_id);

  int32_t field_length = class_fields_length;

  int32_t field_native_stack_length;
  int32_t mulnum_field_type_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, mulnum_field_type_id);
  switch (mulnum_field_type_basic_type_id) {
    case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
      field_native_stack_length = 1;
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
      field_native_stack_length = 2;
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
      field_native_stack_length = 4;
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
      field_native_stack_length = 8;
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
      field_native_stack_length = 4;
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
      field_native_stack_length = 8;
      break;
    }
    default: {
      assert(0);
    }
  }
  
  if (binary_length % (field_length * field_native_stack_length) != 0) {
    croak("The size of the binary data is invalid\n    %s at %s line %d", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t array_length = binary_length / field_length / field_native_stack_length;

  void* array = env->new_mulnum_array(env, stack, basic_type_id, array_length);

  int32_t dimension = env->get_object_type_dimension(env, stack, array);
  
  switch (mulnum_field_type_basic_type_id) {
    case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
      int8_t* elems = env->get_elems_byte(env, stack, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_native_stack_length);
      }
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
      int16_t* elems = env->get_elems_short(env, stack, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_native_stack_length);
      }
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
      int32_t* elems = env->get_elems_int(env, stack, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_native_stack_length);
      }
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
      int64_t* elems = env->get_elems_long(env, stack, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_native_stack_length);
      }
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
      float* elems = env->get_elems_float(env, stack, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_native_stack_length);
      }
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
      double* elems = env->get_elems_double(env, stack, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_native_stack_length);
      }
      break;
    }
    default:
      assert(0);
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
xs_get_exception(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  void* str_exception = env->get_exception(env, stack);
  
  SV* sv_exception;
  if (str_exception) {
    env->inc_ref_count(env, stack, str_exception);
    sv_exception = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, str_exception, "SPVM::BlessedObject::String");
  }
  else {
    sv_exception = &PL_sv_undef;
  }
  
  XPUSHs(sv_exception);
  XSRETURN(1);
}

SV*
_xs_set_exception(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_exception = ST(1);
  
  if (SvOK(sv_exception)) {
    if (!(sv_isobject(sv_exception) && sv_derived_from(sv_exception, "SPVM::BlessedObject::String"))) {
      croak("The exception must be a SPVM::BlessedObject::String object");
    }
    void* exception = SPVM_XS_UTIL_get_object(aTHX_ sv_exception);
    env->set_exception(env, stack, exception);
  }
  else {
    env->set_exception(env, stack, NULL);
  }
  
  XSRETURN(0);
}

SV*
xs_get_memory_blocks_count(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t memory_blocks_count = env->get_memory_blocks_count(env);
  SV* sv_memory_blocks_count = sv_2mortal(newSViv(memory_blocks_count));
  
  XPUSHs(sv_memory_blocks_count);
  XSRETURN(1);
}

MODULE = SPVM::BlessedObject		PACKAGE = SPVM::BlessedObject

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_object = ST(0);
  HV* hv_object = (HV*)SvRV(sv_object);

  assert(SvOK(sv_object));
  
  // Get object
  void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_object);

  // API
  SV** sv_api_ptr = hv_fetch(hv_object, "api", strlen("api"), 0);
  SV* sv_api = sv_api_ptr ? *sv_api_ptr : &PL_sv_undef;
  HV* hv_api = (HV*)SvRV(sv_api);

  // Env
  SV** sv_env_ptr = hv_fetch(hv_api, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_api, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  assert(env->get_ref_count(env, stack, object));
  
  // Decrement reference count
  env->dec_ref_count(env, stack, object);
  
  XSRETURN(0);
}

MODULE = SPVM::BlessedObject::Class		PACKAGE = SPVM::BlessedObject::Class

SV*
get_class_name(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_object = ST(0);
  HV* hv_object = (HV*)SvRV(sv_object);
  
  assert(SvOK(sv_object));
  
  // Get object
  void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_object);

  // API
  SV** sv_api_ptr = hv_fetch(hv_object, "api", strlen("api"), 0);
  SV* sv_api = sv_api_ptr ? *sv_api_ptr : &PL_sv_undef;
  HV* hv_api = (HV*)SvRV(sv_api);

  // Env
  SV** sv_env_ptr = hv_fetch(hv_api, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_api, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t object_basic_type_id = env->get_object_basic_type_id(env, stack, object);
  int32_t object_basic_type_name_id = env->api->runtime->get_basic_type_name_id(env->runtime, object_basic_type_id);
  const char* class_name = env->api->runtime->get_name(env->runtime, object_basic_type_name_id);
  
  SV* sv_class_name = sv_2mortal(newSVpv(class_name, 0));
  
  XPUSHs(sv_class_name);
  XSRETURN(1);
}


MODULE = SPVM::Builder::Compiler		PACKAGE = SPVM::Builder::Compiler

SV*
create_compiler(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  // Create compiler native_env
  SPVM_ENV* api_env = SPVM_NATIVE_new_env_raw();
  size_t iv_api_env = PTR2IV(api_env);
  SV* sviv_api_env = sv_2mortal(newSViv(iv_api_env));
  SV* sv_api_env = sv_2mortal(newRV_inc(sviv_api_env));
  (void)hv_store(hv_self, "api_env", strlen("api_env"), SvREFCNT_inc(sv_api_env), 0);

  // Create compiler
  void* compiler = api_env->api->compiler->new_object();

  size_t iv_compiler = PTR2IV(compiler);
  SV* sviv_compiler = sv_2mortal(newSViv(iv_compiler));
  SV* sv_compiler = sv_2mortal(newRV_inc(sviv_compiler));
  (void)hv_store(hv_self, "compiler", strlen("compiler"), SvREFCNT_inc(sv_compiler), 0);

  XSRETURN(0);
}

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  SV** sv_api_env_ptr = hv_fetch(hv_self, "api_env", strlen("api_env"), 0);
  SV* sv_api_env = sv_api_env_ptr ? *sv_api_env_ptr : &PL_sv_undef;
  SPVM_ENV* api_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_api_env)));
  
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  void* compiler = INT2PTR(void*, SvIV(SvRV(sv_compiler)));

  // Free compiler
  api_env->api->compiler->free_object(compiler);
  
  api_env->free_env_raw(api_env);
  
  XSRETURN(0);
}

SV*
compile(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_class_name = ST(1);
  SV* sv_start_file = ST(2);
  SV* sv_start_line = ST(3);
  
  HV* hv_self = (HV*)SvRV(sv_self);

  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  void* compiler = INT2PTR(void*, SvIV(SvRV(sv_compiler)));
  
  // Include directries
  SV** sv_module_dirs_ptr = hv_fetch(hv_self, "module_dirs", strlen("module_dirs"), 0);
  SV* sv_module_dirs = sv_module_dirs_ptr ? *sv_module_dirs_ptr : &PL_sv_undef;
  
  // Name
  const char* class_name = SvPV_nolen(sv_class_name);
  
  // File
  const char* start_file = SvPV_nolen(sv_start_file);
  
  // Line
  int32_t start_line = (int32_t)SvIV(sv_start_line);

  SV** sv_api_env_ptr = hv_fetch(hv_self, "api_env", strlen("api_env"), 0);
  SV* sv_api_env = sv_api_env_ptr ? *sv_api_env_ptr : &PL_sv_undef;
  SPVM_ENV* api_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_api_env)));

  // Set starting file
  api_env->api->compiler->set_start_file(compiler, start_file);
  
  // Set starting line
  api_env->api->compiler->set_start_line(compiler, start_line);
  
  // Add include paths
  AV* av_module_dirs;
  if (SvOK(sv_module_dirs)) {
    av_module_dirs = (AV*)SvRV(sv_module_dirs);
  }
  else {
    av_module_dirs = (AV*)sv_2mortal((SV*)newAV());
  }
  int32_t av_module_dirs_length = (int32_t)av_len(av_module_dirs) + 1;
  for (int32_t i = 0; i < av_module_dirs_length; i++) {
    SV** sv_include_dir_ptr = av_fetch(av_module_dirs, i, 0);
    SV* sv_include_dir = sv_include_dir_ptr ? *sv_include_dir_ptr : &PL_sv_undef;
    char* include_dir = SvPV_nolen(sv_include_dir);
    api_env->api->compiler->add_module_dir(compiler, include_dir);
  }

  // Compile SPVM
  int32_t compile_error_code = api_env->api->compiler->compile(compiler, class_name);
  
  SV* sv_success = &PL_sv_undef;
  if (compile_error_code == 0) {
    sv_success = sv_2mortal(newSViv(1));
  }

  XPUSHs(sv_success);
  
  XSRETURN(1);
}

SV*
build_runtime(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_class_name = ST(1);
  SV* sv_start_file = ST(2);
  SV* sv_start_line = ST(3);
  
  HV* hv_self = (HV*)SvRV(sv_self);

  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  void* compiler = INT2PTR(void*, SvIV(SvRV(sv_compiler)));
  
  SV** sv_api_env_ptr = hv_fetch(hv_self, "api_env", strlen("api_env"), 0);
  SV* sv_api_env = sv_api_env_ptr ? *sv_api_env_ptr : &PL_sv_undef;
  SPVM_ENV* api_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_api_env)));

  // Build runtime information
  void* runtime = api_env->api->runtime->new_object(api_env);

  // Runtime allocator
  void* runtime_allocator = api_env->api->runtime->get_allocator(runtime);
  
  // SPVM 32bit codes
  int32_t* runtime_codes = api_env->api->compiler->create_runtime_codes(compiler, runtime_allocator);
  
  // Build runtime
  api_env->api->runtime->build(runtime, runtime_codes);

  SV* sv_runtime = SPVM_XS_UTIL_new_sv_object(aTHX_ runtime, "SPVM::Builder::Runtime");

  XPUSHs(sv_runtime);
  
  XSRETURN(1);
}

SV*
get_error_messages(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);

  HV* hv_self = (HV*)SvRV(sv_self);

  // The api_environment
  SV** sv_api_env_ptr = hv_fetch(hv_self, "api_env", strlen("api_env"), 0);
  SV* sv_api_env = sv_api_env_ptr ? *sv_api_env_ptr : &PL_sv_undef;
  SPVM_ENV* api_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_api_env)));
  
  // Compiler
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  void* compiler = INT2PTR(void*, SvIV(SvRV(sv_compiler)));

  AV* av_error_messages = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_error_messages = sv_2mortal(newRV_inc((SV*)av_error_messages));

  int32_t error_messages_length = api_env->api->compiler->get_error_messages_length(compiler);

  for (int32_t i = 0; i < error_messages_length; i++) {
    const char* error_message = api_env->api->compiler->get_error_message(compiler, i);
    SV* sv_error_message = sv_2mortal(newSVpv(error_message, 0));
    av_push(av_error_messages, SvREFCNT_inc(sv_error_message));
  }
  
  XPUSHs(sv_error_messages);
  XSRETURN(1);
}

MODULE = SPVM::Builder::Runtime		PACKAGE = SPVM::Builder::Runtime

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  // Runtime
  SV** sv_native_runtime_ptr = hv_fetch(hv_self, "object", strlen("object"), 0);
  SV* sv_native_runtime = sv_native_runtime_ptr ? *sv_native_runtime_ptr : &PL_sv_undef;
  void* runtime = INT2PTR(void*, SvIV(SvRV(sv_native_runtime)));

  SPVM_ENV* api_env = SPVM_NATIVE_new_env_raw();

  // Free native_runtime
  api_env->api->runtime->free_object(runtime);

  api_env->free_env_raw(api_env);

  XSRETURN(0);
}

SV*
get_method_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_runtime = ST(0);
  void* runtime = SPVM_XS_UTIL_get_object(aTHX_ sv_runtime);
  
  SV* sv_class_name = ST(1);
  SV* sv_category = ST(2);

  // Name
  const char* class_name = SvPV_nolen(sv_class_name);

  SPVM_ENV* api_env = SPVM_NATIVE_new_env_raw();
  
  AV* av_method_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_method_names = sv_2mortal(newRV_inc((SV*)av_method_names));
  
  int32_t class_id = api_env->api->runtime->get_class_id_by_name(runtime, class_name);
  int32_t methods_length = api_env->api->runtime->get_class_methods_length(runtime, class_id);
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    int32_t method_id = api_env->api->runtime->get_method_id_by_index(runtime, class_id, method_index);
    const char* method_name = api_env->api->runtime->get_name(runtime, api_env->api->runtime->get_method_name_id(runtime, method_id));
    SV* sv_method_name = sv_2mortal(newSVpv(method_name, 0));
    int32_t is_push = 0;
    if (SvOK(sv_category)) {
      if(strEQ(SvPV_nolen(sv_category), "native") && api_env->api->runtime->get_method_is_native(runtime, method_id)) {
        av_push(av_method_names, SvREFCNT_inc(sv_method_name));
      }
      else if (strEQ(SvPV_nolen(sv_category), "precompile") && api_env->api->runtime->get_method_is_precompile(runtime, method_id)) {
        av_push(av_method_names, SvREFCNT_inc(sv_method_name));
      }
    }
    else {
      av_push(av_method_names, SvREFCNT_inc(sv_method_name));
    }
  }

  api_env->free_env_raw(api_env);
  
  XPUSHs(sv_method_names);
  XSRETURN(1);
}

SV*
get_anon_class_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_runtime = ST(0);
  void* runtime = SPVM_XS_UTIL_get_object(aTHX_ sv_runtime);

  SV* sv_class_name = ST(1);

  // Name
  const char* class_name = SvPV_nolen(sv_class_name);

  SPVM_ENV* api_env = SPVM_NATIVE_new_env_raw();
  
  AV* av_anon_class_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_anon_class_names = sv_2mortal(newRV_inc((SV*)av_anon_class_names));
  
  // Copy class load path to builder
  int32_t class_id = api_env->api->runtime->get_class_id_by_name(runtime, class_name);
  
  int32_t methods_length = api_env->api->runtime->get_class_methods_length(runtime, class_id);
  
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    
    int32_t method_id = api_env->api->runtime->get_method_id_by_index(runtime, class_id, method_index);
    int32_t is_anon_method = api_env->api->runtime->get_method_is_anon(runtime, method_id);
    
    if (is_anon_method) {
      int32_t anon_class_id = api_env->api->runtime->get_method_class_id(runtime, method_id);
      const char* anon_class_name = api_env->api->runtime->get_name(runtime, api_env->api->runtime->get_class_name_id(runtime, anon_class_id));
      SV* sv_anon_class_name = sv_2mortal(newSVpv(anon_class_name, 0));
      av_push(av_anon_class_names, SvREFCNT_inc(sv_anon_class_name));
    }
  }

  api_env->free_env_raw(api_env);
  
  XPUSHs(sv_anon_class_names);
  XSRETURN(1);
}

SV*
get_class_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_runtime = ST(0);
  void* runtime = SPVM_XS_UTIL_get_object(aTHX_ sv_runtime);

  SPVM_ENV* api_env = SPVM_NATIVE_new_env_raw();

  AV* av_class_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_class_names = sv_2mortal(newRV_inc((SV*)av_class_names));
  
  int32_t classes_length = api_env->api->runtime->get_classes_length(runtime);
  for (int32_t class_id = 0; class_id < classes_length; class_id++) {
    const char* class_name = api_env->api->runtime->get_name(runtime, api_env->api->runtime->get_class_name_id(runtime, class_id));
    SV* sv_class_name = sv_2mortal(newSVpv(class_name, 0));
    av_push(av_class_names, SvREFCNT_inc(sv_class_name));
  }

  api_env->free_env_raw(api_env);
  
  XPUSHs(sv_class_names);
  XSRETURN(1);
}

SV*
get_module_file(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_runtime = ST(0);
  void* runtime = SPVM_XS_UTIL_get_object(aTHX_ sv_runtime);

  SV* sv_class_name = ST(1);

  // Name
  const char* class_name = SvPV_nolen(sv_class_name);
  
  SPVM_ENV* api_env = SPVM_NATIVE_new_env_raw();

  // Copy class load path to builder
  int32_t class_id = api_env->api->runtime->get_class_id_by_name(runtime, class_name);
  const char* module_file;
  SV* sv_module_file;

  if (class_id >= 0) {
    int32_t module_rel_file_id = api_env->api->runtime->get_class_module_rel_file_id(runtime, class_id);
    int32_t module_dir_id = api_env->api->runtime->get_class_module_dir_id(runtime, class_id);
    const char* module_dir = NULL;
    const char* module_dir_sep;
    if (module_dir_id >= 0) {
      module_dir_sep = "/";
      module_dir = api_env->api->runtime->get_constant_string_value(runtime, module_dir_id, NULL);
    }
    else {
      module_dir_sep = "";
      module_dir = "";
    }
    const char* module_rel_file = api_env->api->runtime->get_constant_string_value(runtime, module_rel_file_id, NULL);

    sv_module_file = sv_2mortal(newSVpv(module_dir, 0));
    sv_catpv(sv_module_file, module_dir_sep);
    sv_catpv(sv_module_file, module_rel_file);
  }
  else {
    sv_module_file = &PL_sv_undef;
  }

  api_env->free_env_raw(api_env);
  
  XPUSHs(sv_module_file);
  XSRETURN(1);
}

SV*
get_runtime_codes(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_runtime = ST(1);
  void* runtime = SPVM_XS_UTIL_get_object(aTHX_ sv_runtime);

  // Environment
  SPVM_ENV* api_env = SPVM_NATIVE_new_env_raw();
  
  // SPVM 32bit codes
  int32_t* runtime_codes = api_env->api->runtime->get_runtime_codes(runtime);
  int32_t runtime_codes_length = api_env->api->runtime->get_runtime_codes_length(runtime);
  
  AV* av_runtime_codes = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_runtime_codes = sv_2mortal(newRV_inc((SV*)av_runtime_codes));
  for (int32_t i = 0; i < runtime_codes_length; i++) {
    int32_t spvm_32bit_code = runtime_codes[i];
    SV* sv_spvm_32bit_code = sv_2mortal(newSViv(spvm_32bit_code));
    av_push(av_runtime_codes, SvREFCNT_inc(sv_spvm_32bit_code));
  }

  // Free native_env
  api_env->free_env_raw(api_env);
  
  XPUSHs(sv_runtime_codes);

  XSRETURN(1);
}

SV*
set_native_method_address(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_runtime = ST(0);
  void* runtime = SPVM_XS_UTIL_get_object(aTHX_ sv_runtime);

  SV* sv_class_name = ST(1);
  SV* sv_method_name = ST(2);
  SV* sv_native_address = ST(3);

  SPVM_ENV* api_env = SPVM_NATIVE_new_env_raw();
  
  // Class name
  const char* class_name = SvPV_nolen(sv_class_name);

  // Method name
  const char* method_name = SvPV_nolen(sv_method_name);
  
  // Method id
  int32_t method_id = api_env->api->runtime->get_method_id_by_name(runtime, class_name, method_name);
  
  // Native address
  void* native_address = INT2PTR(void*, SvIV(sv_native_address));
  
  api_env->api->runtime->set_native_method_address(runtime, method_id, native_address);

  assert(native_address == api_env->api->runtime->get_native_method_address(runtime, method_id));

  // Free native_env
  api_env->free_env_raw(api_env);

  XSRETURN(0);
}

SV*
build_precompile_class_source(...)
  PPCODE:
{
  SV* sv_runtime = ST(0);
  void* runtime = SPVM_XS_UTIL_get_object(aTHX_ sv_runtime);

  SV* sv_class_name = ST(1);
  const char* class_name = SvPV_nolen(sv_class_name);
  
  // Create precompile source
  SPVM_ENV* env = SPVM_NATIVE_new_env_raw();
  
  // New allocator
  void* allocator = env->api->allocator->new_object();
  
  // New string buffer
  void* string_buffer = env->api->string_buffer->new_object(allocator, 0);

  void* precompile = env->api->precompile->new_object();
  
  env->api->precompile->set_runtime(precompile, runtime);
  
  env->api->precompile->build_class_source(precompile, string_buffer, class_name);
  
  env->api->precompile->free_object(precompile);

  const char* string_buffer_value = env->api->string_buffer->get_value(string_buffer);
  int32_t string_buffer_length = env->api->string_buffer->get_length(string_buffer);
  SV* sv_precompile_source = sv_2mortal(newSVpv(string_buffer_value, string_buffer_length));

  // Free string buffer
  env->api->string_buffer->free_object(string_buffer);

  // Free allocator
  env->api->allocator->free_object(allocator);

  // Free native_env
  env->free_env_raw(env);
  
  XPUSHs(sv_precompile_source);
  XSRETURN(1);
}

SV*
build_env(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_runtime = ST(0);
  void* runtime = SPVM_XS_UTIL_get_object(aTHX_ sv_runtime);

  // Create native_env
  SPVM_ENV* env = SPVM_NATIVE_new_env_raw();

  // Set runtime information
  env->runtime = runtime;
  
  // Initialize native_env
  env->init_env(env);

  SV* sv_env = SPVM_XS_UTIL_new_sv_object(aTHX_ env, "SPVM::Builder::Env");
  HV* hv_env = (HV*)SvRV(sv_env);

  (void)hv_store(hv_env, "runtime", strlen("runtime"), SvREFCNT_inc(sv_runtime), 0);
  
  XPUSHs(sv_env);
  XSRETURN(1);
}

MODULE = SPVM::Builder::Env		PACKAGE = SPVM::Builder::Env

SV*
set_command_info_program_name(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SPVM_ENV* env = SPVM_XS_UTIL_get_object(aTHX_ sv_env);
  
  SV* sv_program_name = ST(1);
  const char* program_name = SvPV_nolen(sv_program_name);
  int32_t program_name_length = strlen(program_name);
  
  {
    SPVM_VALUE* my_stack = env->new_stack(env);
    int32_t scope_id = env->enter_scope(env, my_stack);
    
    // Program name - string
    void* obj_program_name = env->new_string(env, my_stack, program_name, program_name_length);
    
    // Set command info
    {
      int32_t e;
      e = env->set_command_info_program_name(env, obj_program_name);
      assert(e == 0);
    }
    
    env->leave_scope(env, my_stack, scope_id);
    env->free_stack(env, my_stack);
  }
  
  XSRETURN(0);
}

SV*
set_command_info_argv(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SPVM_ENV* env = SPVM_XS_UTIL_get_object(aTHX_ sv_env);
  
  SV* sv_argv = ST(1);
  AV* av_argv = (AV*)SvRV(sv_argv);
  int32_t argv_length = av_len(av_argv) + 1;
  
  {
    SPVM_VALUE* my_stack = env->new_stack(env);
    int32_t scope_id = env->enter_scope(env, my_stack);
    
    void* obj_argv = env->new_object_array(env, my_stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, argv_length);
    for (int32_t index = 0; index < argv_length; index++) {
      SV** sv_arg_ptr = av_fetch(av_argv, index, 0);
      SV* sv_arg = sv_arg_ptr ? *sv_arg_ptr : &PL_sv_undef;
      
      const char* arg = SvPV_nolen(sv_arg);
      int32_t arg_length = strlen(arg);
      
      void* obj_arg = env->new_string(env, my_stack, arg, arg_length);
      env->set_elem_object(env, my_stack, obj_argv, index, obj_arg);
    }
    
    // Set command info
    {
      int32_t e;
      e = env->set_command_info_argv(env, obj_argv);
      assert(e == 0);
    }
    
    env->leave_scope(env, my_stack, scope_id);
    env->free_stack(env, my_stack);
  }
  
  XSRETURN(0);
}

SV*
set_command_info_base_time(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SPVM_ENV* env = SPVM_XS_UTIL_get_object(aTHX_ sv_env);
  
  SV* sv_base_time = ST(1);
  int64_t base_time = SvIV(sv_base_time);
  
  {
    SPVM_VALUE* my_stack = env->new_stack(env);
    int32_t scope_id = env->enter_scope(env, my_stack);
    
    // Set command info
    {
      int32_t e;
      e = env->set_command_info_base_time(env, base_time);
      assert(e == 0);
    }
    
    env->leave_scope(env, my_stack, scope_id);
    env->free_stack(env, my_stack);
  }
  
  XSRETURN(0);
}

SV*
call_init_blocks(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SPVM_ENV* env = SPVM_XS_UTIL_get_object(aTHX_ sv_env);
  
  env->call_init_blocks(env);

  XSRETURN(0);
}

SV*
build_stack(...)
  PPCODE:
{
  (void)RETVAL;
  
  // Env
  SV* sv_env = ST(0);
  SPVM_ENV* env = SPVM_XS_UTIL_get_object(aTHX_ sv_env);

  // Create native_stack
  SPVM_VALUE* stack = env->new_stack(env);
  SV* sv_stack = SPVM_XS_UTIL_new_sv_object(aTHX_ stack, "SPVM::Builder::Stack");
  HV* hv_stack = (HV*)SvRV(sv_stack);

  (void)hv_store(hv_stack, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);

  XPUSHs(sv_stack);
  XSRETURN(1);
}

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_self);
  
  // Cleanup global varialbes
  env->cleanup_global_vars(env);
  
  env->free_env_raw(env);
  
  XSRETURN(0);
}

MODULE = SPVM::Builder::Stack		PACKAGE = SPVM::Builder::Stack

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  // Stack
  SV** sv_native_stack_ptr = hv_fetch(hv_self, "object", strlen("object"), 0);
  SV* sv_native_stack = sv_native_stack_ptr ? *sv_native_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = INT2PTR(SPVM_VALUE*, SvIV(SvRV(sv_native_stack)));
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);

  // Free native_stack
  env->free_stack(env, stack);
  
  XSRETURN(0);
}

MODULE = SPVM		PACKAGE = SPVM

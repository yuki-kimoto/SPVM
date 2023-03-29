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
  (void)hv_store(hv_data, "__api", strlen("__api"), SvREFCNT_inc(sv_api), 0);
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
  if (sv_isobject(sv_env) && sv_derived_from(sv_env, "SPVM::Builder::Env")) {
    HV* hv_env = (HV*)SvRV(sv_env);
    SV** sv_native_env_ptr = hv_fetch(hv_env, "object", strlen("object"), 0);
    SV* sv_native_env = sv_native_env_ptr ? *sv_native_env_ptr : &PL_sv_undef;
    env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_native_env)));
  }
  else if (sv_isobject(sv_env) && sv_derived_from(sv_env, "SPVM::BlessedObject::Class")) {
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

    SV** sv_env_ptr = hv_fetch(hv_env, "object", strlen("object"), 0);
    SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
    void* spvm_env = INT2PTR(void*, SvIV(SvRV(sv_env)));
    
    env = blessed_object_env->get_pointer(blessed_object_env, blessed_object_stack, spvm_env);
  }
  
  return env;
}

SPVM_VALUE* SPVM_XS_UTIL_get_stack(pTHX_ SV* sv_stack) {
  
  SPVM_VALUE* stack;
  if (sv_isobject(sv_stack) && sv_derived_from(sv_stack, "SPVM::Builder::Stack")) {
    HV* hv_stack = (HV*)SvRV(sv_stack);
    SV** sv_native_stack_ptr = hv_fetch(hv_stack, "object", strlen("object"), 0);
    SV* sv_native_stack = sv_native_stack_ptr ? *sv_native_stack_ptr : &PL_sv_undef;
    stack = INT2PTR(SPVM_VALUE*, SvIV(SvRV(sv_native_stack)));
  }
  else if (sv_isobject(sv_stack) && sv_derived_from(sv_stack, "SPVM::BlessedObject::Class")) {
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

    SV** sv_stack_ptr = hv_fetch(hv_stack, "object", strlen("object"), 0);
    SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
    void* spvm_stack = INT2PTR(void*, SvIV(SvRV(sv_stack)));
    
    stack = blessed_object_env->get_pointer(blessed_object_env, blessed_object_stack, spvm_stack);
  }
  
  return stack;
}

SV* SPVM_XS_UTIL_new_string(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_string, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error = 0;
  if (SvOK(sv_string)) {
    if (sv_isobject(sv_string) && sv_derived_from(sv_string, "SPVM::BlessedObject::String")) {
      // Nothing
    }
    else if (SvROK(sv_string)) {
      error = 1;
    }
    else {
      STRLEN length = -1;
      const char* string = SvPV(sv_string, length);
      void* spvm_string = env->new_string(env, stack, string, (int32_t)length);
      sv_string = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_string, "SPVM::BlessedObject::String");
    }
  }
  else {
    sv_string = &PL_sv_undef;
  }
  
  if (error) {
    *sv_error = sv_2mortal(newSVpvf(" must be a non-reference scalar or a SPVM::BlessedObject::String object or undef"));
  }
  
  return sv_string;
}

SV* SPVM_XS_UTIL_new_address_object(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_address, SV** sv_error) {
  
  int32_t e = 0;
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error = 0;
  if (SvOK(sv_address)) {
    if (sv_isobject(sv_address) && sv_derived_from(sv_address, "SPVM::BlessedObject::Class")) {
      void* spvm_address = SPVM_XS_UTIL_get_object(aTHX_ sv_address);
      int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ADDRESS_CLASS;
      int32_t type_dimension = 1;
      if (!env->isa(env, stack, spvm_address, basic_type_id, type_dimension)) {
        error = 1;
      }
    }
    else if (SvROK(sv_address)) {
      error = 1;
    }
    else {
      void* address = (void*)(intptr_t)SvIV(sv_address);
      void* spvm_address = env->new_pointer_object_by_name(env, stack, "Address", address, &e, __func__, FILE_NAME, __LINE__);
      assert(e == 0);
      sv_address = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_address, "SPVM::BlessedObject::Class");
    }
  }
  else {
    sv_address = &PL_sv_undef;
  }
  
  if (error) {
    *sv_error = sv_2mortal(newSVpvf(" must be a non-reference scalar or a SPVM::BlessedObject::Class object of the Address class or undef"));
  }
  
  return sv_address;
}

SV* SPVM_XS_UTIL_new_byte_array(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t spvm_array_basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(spvm_array_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && spvm_array_type_dimension == 1)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_byte_array(env, stack, length);
      
      int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          error_elem = 1;
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          break;
        }
        elems[i] = (int8_t)SvIV(sv_elem);
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the byte[] type or undef"));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_byte_array_unsigned(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t spvm_array_basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(spvm_array_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && spvm_array_type_dimension == 1)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_byte_array(env, stack, length);
      
      int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          error_elem = 1;
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          break;
        }
        elems[i] = (int8_t)(uint8_t)SvUV(sv_elem);
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the byte[] type or undef"));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_short_array(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t spvm_array_basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(spvm_array_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT && spvm_array_type_dimension == 1)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_short_array(env, stack, length);
      
      int16_t* elems = env->get_elems_short(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          error_elem = 1;
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          break;
        }
        elems[i] = (int16_t)SvIV(sv_elem);
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the short[] or undef"));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_short_array_unsigned(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t spvm_array_basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(spvm_array_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && spvm_array_type_dimension == 1)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_short_array(env, stack, length);
      
      int16_t* elems = env->get_elems_short(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          error_elem = 1;
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          break;
        }
        elems[i] = (int16_t)(uint16_t)SvUV(sv_elem);
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the short[] type or undef"));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_int_array(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t spvm_array_basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(spvm_array_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT && spvm_array_type_dimension == 1)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_int_array(env, stack, length);
      
      int32_t* elems = env->get_elems_int(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          error_elem = 1;
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          break;
        }
        elems[i] = (int32_t)SvIV(sv_elem);
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the int[] or undef"));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_int_array_unsigned(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t spvm_array_basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(spvm_array_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && spvm_array_type_dimension == 1)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_int_array(env, stack, length);
      
      int32_t* elems = env->get_elems_int(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          error_elem = 1;
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          break;
        }
        elems[i] = (int32_t)(uint32_t)SvUV(sv_elem);
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the int[] type or undef"));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_long_array(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t spvm_array_basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(spvm_array_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG && spvm_array_type_dimension == 1)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_long_array(env, stack, length);
      
      int64_t* elems = env->get_elems_long(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          error_elem = 1;
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          break;
        }
        elems[i] = (int64_t)SvIV(sv_elem);
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the long[] or undef"));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_long_array_unsigned(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t spvm_array_basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(spvm_array_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && spvm_array_type_dimension == 1)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_long_array(env, stack, length);
      
      int64_t* elems = env->get_elems_long(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          error_elem = 1;
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          break;
        }
        elems[i] = (int64_t)(uint64_t)SvUV(sv_elem);
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the long[] type or undef"));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_float_array(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t spvm_array_basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(spvm_array_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT && spvm_array_type_dimension == 1)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_float_array(env, stack, length);
      
      float* elems = env->get_elems_float(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          error_elem = 1;
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          break;
        }
        elems[i] = (float)SvNV(sv_elem);
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the float[] or undef"));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_double_array(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t spvm_array_basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(spvm_array_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE && spvm_array_type_dimension == 1)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_double_array(env, stack, length);
      
      double* elems = env->get_elems_double(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          error_elem = 1;
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          break;
        }
        elems[i] = (double)SvNV(sv_elem);
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the double[] or undef"));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_string_array(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t spvm_array_basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(spvm_array_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && spvm_array_type_dimension == 1)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_string_array(env, stack, length);
      
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        SV* sv_error_elem = &PL_sv_undef;
        sv_elem = SPVM_XS_UTIL_new_string(aTHX_ sv_self, sv_env, sv_stack, sv_elem, &sv_error_elem);
        
        if (SvOK(sv_error_elem)) {
          error_elem = 1;
          *sv_error = sv_2mortal(newSVpvf("'s %dth element %s", i + 1, SvPV_nolen(sv_error_elem)));
          break;
        }
        void* spvm_elem = SPVM_XS_UTIL_get_object(aTHX_ sv_elem);
        env->set_elem_string(env, stack, spvm_array, i, spvm_elem);
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the string[] type or undef"));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_object_array(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, int32_t basic_type_id, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t type_dimension = 1;
      if (!env->isa(env, stack, spvm_array, basic_type_id, type_dimension)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_object_array(env, stack, basic_type_id, length);
      
      for (int32_t index = 0; index < length; index++) {
        SV** sv_elem_ptr = av_fetch(av_array, index, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!SvOK(sv_elem)) {
          env->set_elem_object(env, stack, spvm_array, index, NULL);
        }
        else if (sv_isobject(sv_elem) && sv_derived_from(sv_elem, "SPVM::BlessedObject")) {
          void* elem = SPVM_XS_UTIL_get_object(aTHX_ sv_elem);
          
          int32_t elem_isa = env->elem_isa(env, stack, spvm_array, elem);
          if (elem_isa) {
            env->set_elem_object(env, stack, spvm_array, index, elem);
          }
          else {
            void* spvm_elem_type_name = env->get_type_name(env, stack, elem);
            const char* elem_type_name = env->get_chars(env, stack, spvm_elem_type_name);
            *sv_error = sv_2mortal(newSVpvf("'s %dth element must be the \"%s\" assignable type", index + 1, elem_type_name));
            error_elem = 1;
            break;
          }
        }
        else {
            *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a SPVM::BlessedObject or undef", index + 1));
            error_elem = 1;
            break;
        }
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    const char* basic_type_name = env->api->runtime->get_name(env->runtime, env->api->runtime->get_basic_type_name_id(env->runtime, basic_type_id));
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the %s[] assignable type or undef", basic_type_name));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_muldim_array(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, int32_t basic_type_id, int32_t type_dimension, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      if (!env->isa(env, stack, spvm_array, basic_type_id, type_dimension)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_muldim_array(env, stack, basic_type_id, type_dimension, length);
      
      for (int32_t index = 0; index < length; index++) {
        SV** sv_elem_ptr = av_fetch(av_array, index, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!SvOK(sv_elem)) {
          env->set_elem_object(env, stack, spvm_array, index, NULL);
        }
        else if (sv_isobject(sv_elem) && sv_derived_from(sv_elem, "SPVM::BlessedObject")) {
          void* elem = SPVM_XS_UTIL_get_object(aTHX_ sv_elem);
          
          int32_t elem_isa = env->elem_isa(env, stack, spvm_array, elem);
          if (elem_isa) {
            env->set_elem_object(env, stack, spvm_array, index, elem);
          }
          else {
            void* spvm_elem_type_name = env->get_type_name(env, stack, elem);
            const char* elem_type_name = env->get_chars(env, stack, spvm_elem_type_name);
            *sv_error = sv_2mortal(newSVpvf("'s %dth element must be the \"%s\" assignable type", index + 1, elem_type_name));
            error_elem = 1;
            break;
          }
        }
        else {
            *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a SPVM::BlessedObject or undef", index + 1));
            error_elem = 1;
            break;
        }
      }
      
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    const char* array_type_name = env->get_compile_type_name(env, stack, basic_type_id, type_dimension, 0);
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the %s assignable type or undef", array_type_name));
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_mulnum_array(pTHX_ SV* sv_self, SV* sv_env, SV* sv_stack, int32_t basic_type_id, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_array = 0;
  int32_t error_elem = 0;
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_array);
      int32_t type_dimension = 1;
      if (!env->isa(env, stack, spvm_array, basic_type_id, type_dimension)) {
        error_array = 1;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      error_array = 1;
    }
    else {
      AV* av_array = (AV*)SvRV(sv_array);
      
      int32_t length = av_len(av_array) + 1;
      
      // Runtime
      void* runtime = env->runtime;
      
      // New array
      void* spvm_array = env->new_mulnum_array(env, stack, basic_type_id, length);
      
      for (int32_t index = 0; index < length; index++) {
        SV** sv_elem_ptr = av_fetch(av_array, index, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (SvROK(sv_elem) && sv_derived_from(sv_elem, "HASH")) {
          
          int32_t class_id = env->api->runtime->get_basic_type_class_id(env->runtime, basic_type_id);
          int32_t class_fields_length = env->api->runtime->get_class_fields_length(env->runtime, class_id);
          int32_t class_fields_base_id = env->api->runtime->get_class_fields_base_id(env->runtime, class_id);
          
          int32_t mulnum_field_id = class_fields_base_id;
          int32_t mulnum_field_type_id = env->api->runtime->get_field_type_id(env->runtime, mulnum_field_id);
          
          void* elems = (void*)env->get_elems_int(env, stack, spvm_array);
          
          HV* hv_value = (HV*)SvRV(sv_elem);
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
              *sv_error = sv_2mortal(newSVpvf("'s \"%s\" field of the %dth element must be defined\n    %s at %s line %d\n", mulnum_field_name, index + 1, __func__, FILE_NAME, __LINE__));
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
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a hash reference\n    %s at %s line %d\n", index + 1, __func__, FILE_NAME, __LINE__));
          return NULL;
        }
      }
      if (!error_elem) {
        sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
      }
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  if (error_elem) {
    // Nothing
  }
  else if (error_array) {
    const char* basic_type_name = env->api->runtime->get_name(env->runtime, env->api->runtime->get_basic_type_name_id(env->runtime, basic_type_id));
    *sv_error = sv_2mortal(newSVpvf(" must be an array reference or a SPVM::BlessedObject::Array object of the %s[] type or undef", basic_type_name));
  }
  
  return sv_array;
}

MODULE = SPVM::ExchangeAPI		PACKAGE = SPVM::ExchangeAPI

SV*
_xs_call_method(...)
  PPCODE:
{
  (void)RETVAL;
  
  int32_t args_length = items;
  
  // SPVM::ExchangeAPI::Error
  SV* sv_error_ret = ST(args_length - 1);
  if (sv_isobject(sv_error_ret) && sv_derived_from(sv_error_ret, "SPVM::ExchangeAPI::Error")) {
    args_length -= 1;
  }
  else {
    sv_error_ret = &PL_sv_undef;
  }
  
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
    if (!(sv_isobject(sv_invocant) && sv_derived_from(sv_invocant, "SPVM::BlessedObject::Class"))) {
      croak("The $invocant must be a SPVM::BlessedObject::Class object\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    HV* hv_invocant = (HV*)SvRV(sv_invocant);
    
    // Env
    SV** sv_env_ptr = hv_fetch(hv_invocant, "env", strlen("env"), 0);
    SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
    SPVM_ENV* object_env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
    
    if (!(object_env == env)) {
      croak("The env of the argument is differnt from the env of the invocant\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    // Stack
    SV** sv_stack_ptr = hv_fetch(hv_invocant, "stack", strlen("stack"), 0);
    SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
    SPVM_VALUE* object_stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
    
    if (!(object_stack == stack)) {
      croak("The stack of the argument is differnt from the stack of the invocant\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_invocant);
    int32_t object_basic_type_id = env->get_object_basic_type_id(env, stack, object);
    int32_t object_basic_type_name_id = env->api->runtime->get_basic_type_name_id(env->runtime, object_basic_type_id);
    class_name = env->api->runtime->get_name(env->runtime, object_basic_type_name_id);
    
    char* found_char = strrchr(method_name, ':');
    if (found_char) {
      if (!(*(found_char - 1) == ':')) {
        croak("The static method call must be valid\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
      }
      *(found_char - 1) = '\0';
      const char* class_name = method_name;
      method_name = found_char + 1;
      
      int32_t static_call_basic_type_id = env->api->runtime->get_basic_type_id_by_name(env->runtime, class_name);
      if (static_call_basic_type_id < 0) {
        croak("The \"%s\" class is not found\n    %s at %s line %d\n", class_name, __func__, FILE_NAME, __LINE__);
      }
      
      int32_t isa = env->isa(env, stack, object, static_call_basic_type_id, 0);
      if (!isa) {
        croak("The invocant must be assinged to the \"%s\" class\n    %s at %s line %d\n", class_name, __func__, FILE_NAME, __LINE__);
      }
      
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
  int32_t call_method_args_length = args_length - spvm_args_base;
  
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

  // Arguments conversion
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
    
    int32_t arg_type_is_not_ref = !(arg_type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF);
    
    // Argument conversion
    if (arg_type_dimension == 0) {
      if (arg_type_is_not_ref) {
        switch (arg_basic_type_category) {
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
            if (!(SvOK(sv_value) && !SvROK(sv_value))) {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a non-reference scalar\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
            }
            
            switch(arg_basic_type_id) {
              // Argument conversion - byte
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
                int8_t value = (int8_t)SvIV(sv_value);
                stack[stack_index].bval = value;
                break;
              }
              // Argument conversion - short
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
                int16_t value = (int16_t)SvIV(sv_value);
                stack[stack_index].sval = value;
                break;
              }
              // Argument conversion - int
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
                int32_t value = (int32_t)SvIV(sv_value);
                stack[stack_index].ival = value;
                break;
              }
              // Argument conversion - long
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
                int64_t value = (int64_t)SvIV(sv_value);
                stack[stack_index].lval = value;
                break;
              }
              // Argument conversion - float
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
                float value = (float)SvNV(sv_value);
                stack[stack_index].fval = value;
                break;
              }
              // Argument conversion - double
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
                double value = (double)SvNV(sv_value);
                stack[stack_index].dval = value;
                break;
              }
              default: {
                assert(0);
              }
            }
            stack_index++;
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING: {
            // Argument conversion - string
            SV* sv_error = &PL_sv_undef;
            sv_value = SPVM_XS_UTIL_new_string(aTHX_ sv_self, sv_env, sv_stack, sv_value, &sv_error);
            if (SvOK(sv_error)) {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", args_index_nth, method_name, class_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
            }
            void* spvm_string = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
            
            stack[stack_index].oval = spvm_string;
            
            stack_index++;
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT: {
            // Argument conversion - any object
            void* spvm_value;
            if (!SvOK(sv_value)) {
              spvm_value = NULL;
            }
            else if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject")) {
              spvm_value = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
            }
            else {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject object or undef\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
            }
            stack[stack_index].oval = spvm_value;
            
            stack_index++;
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
          {
            // Argument conversion - class or interface
            int32_t error = 0;
            void* spvm_value;
            if (!SvOK(sv_value)) {
              spvm_value = NULL;
            }
            else if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject::Class")) {
              spvm_value = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
              
              if (!env->isa(env, stack, spvm_value, arg_basic_type_id, arg_type_dimension)) {
                error = 1;
              }
            }
            else {
              error = 1;
            }
            
            if (error) {
              void* spvm_compile_type_name = env->get_compile_type_name(env, stack, arg_basic_type_id, arg_type_dimension, arg_type_flag);
              const char* compile_type_name = env->get_chars(env, stack, spvm_compile_type_name);
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::Class object of a \"%s\" assignable type or undef\n    %s at %s line %d\n", args_index_nth, method_name, class_name, compile_type_name, __func__, FILE_NAME, __LINE__);
            }
            
            stack[stack_index].oval = spvm_value;
            
            stack_index++;
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
          {
            // Argument conversion - multi-numeric
            if (!(SvROK(sv_value) && sv_derived_from(sv_value, "HASH"))) {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a hash reference\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
            }
            
            int32_t arg_class_id = env->api->runtime->get_basic_type_class_id(env->runtime, arg_basic_type_id);
            int32_t arg_class_fields_length = env->api->runtime->get_class_fields_length(env->runtime, arg_class_id);
            int32_t arg_class_fields_base_id = env->api->runtime->get_class_fields_base_id(env->runtime, arg_class_id);
            int32_t arg_class_field_type_id = env->api->runtime->get_field_type_id(env->runtime, arg_class_fields_base_id);
            int32_t arg_class_field_type_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, arg_class_field_type_id);
            assert(arg_class_field_type_basic_type_id >= 0);
            
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
                croak("The \"%s\" field of the \"%s\" class sepcified in the %dth argument of the \"%s\" method in the \"%s\" class is not found\n    %s at %s line %d\n", mulnum_field_name, arg_class_name, args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);

              }
              
              switch (arg_class_field_type_basic_type_id) {
                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                  // Argument conversion - multi-numeric byte
                  int8_t value = (int8_t)SvIV(sv_field_value);
                  stack[stack_index + field_index].bval = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                  // Argument conversion - multi-numeric short
                  int16_t value = (int16_t)SvIV(sv_field_value);
                  stack[stack_index + field_index].sval = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                  // Argument conversion - multi-numeric int
                  int32_t value = (int32_t)SvIV(sv_field_value);
                  stack[stack_index + field_index].ival = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                  // Argument conversion - multi-numeric long
                  int64_t value = (int64_t)SvIV(sv_field_value);
                  stack[stack_index + field_index].lval = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                  // Argument conversion - multi-numeric float
                  float value = (float)SvNV(sv_field_value);
                  stack[stack_index + field_index].fval = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                  // Argument conversion - multi-numeric double
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
            break;
          }
          default: {
            assert(0);
          }
        }
      }
      // Reference argument
      else {
        args_have_ref = 1;
        
        switch (arg_basic_type_category) {
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
            // Argument conversion - numeric reference
            if (!(SvROK(sv_value) && sv_derived_from(sv_value , "SCALAR"))) {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a scalar reference\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
            }
            
            SV* sv_value_deref = SvRV(sv_value);
            
            switch (arg_basic_type_id) {
              // Argument conversion - byte reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                int8_t value = (int8_t)SvIV(sv_value_deref);
                ref_stack[ref_stack_index].bval = value;
                break;
              }
              // Argument conversion - short reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                int16_t value = (int16_t)SvIV(sv_value_deref);
                ref_stack[ref_stack_index].sval = value;
                break;
              }
              // Argument conversion - int reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                int32_t value = (int32_t)SvIV(sv_value_deref);
                ref_stack[ref_stack_index].ival = value;
                break;
              }
              // Argument conversion - long reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                int64_t value = (int64_t)SvIV(sv_value_deref);
                ref_stack[ref_stack_index].lval = value;
                break;
              }
              // Argument conversion - float reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                float value = (float)SvNV(sv_value_deref);
                ref_stack[ref_stack_index].fval = value;
                break;
              }
              // Argument conversion - double reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                double value = (double)SvNV(sv_value_deref);
                ref_stack[ref_stack_index].dval = value;
                break;
              }
            }
            
            stack[stack_index].oval = &ref_stack[ref_stack_index];
            ref_stack_indexes[args_index] = ref_stack_index;
            ref_stack_index++;
            stack_index++;
            
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
          {
            // Argument conversion - multi-numeric reference
            if (!(SvROK(sv_value) && SvROK(SvRV(sv_value)) && sv_derived_from(SvRV(sv_value) , "HASH"))) {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a reference to a hash reference\n    %s at %s line %d\n", args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
            }
            
            SV* hv_value_ref = SvRV(sv_value);
            
            HV* hv_value = (HV*)SvRV(hv_value_ref);
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
                croak("The \"%s\" field of the \"%s\" class sepcified in the %dth argument of the \"%s\" method in the \"%s\" class is not found\n    %s at %s line %d\n", mulnum_field_name, arg_class_name, args_index_nth, method_name, class_name, __func__, FILE_NAME, __LINE__);
              }
              switch(arg_class_field_type_basic_type_id) {
                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                  // Argument conversion - multi-numeric byte reference
                  int8_t value = (int8_t)SvIV(sv_field_value);
                  ((int8_t*)&ref_stack[ref_stack_index])[field_index] = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                  // Argument conversion - multi-numeric short reference
                  int16_t value = (int16_t)SvIV(sv_field_value);
                  ((int16_t*)&ref_stack[ref_stack_index])[field_index] = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                  // Argument conversion - multi-numeric int reference
                  int32_t value = (int32_t)SvIV(sv_field_value);
                  ((int32_t*)&ref_stack[ref_stack_index])[field_index] = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                  // Argument conversion - multi-numeric long reference
                  int64_t value = (int64_t)SvIV(sv_field_value);
                  ((int64_t*)&ref_stack[ref_stack_index])[field_index] = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                  // Argument conversion - multi-numeric float reference
                  float value = (float)SvNV(sv_field_value);
                  ((float*)&ref_stack[ref_stack_index])[field_index] = value;
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                  // Argument conversion - multi-numeric double reference
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
    }
    else if (arg_type_dimension == 1) {
      switch (arg_basic_type_category) {
        // Argument conversion - numeric array
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
          SV* sv_error = &PL_sv_undef;
          switch (arg_basic_type_id) {
            // Argument conversion - byte array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
              sv_value = SPVM_XS_UTIL_new_byte_array(aTHX_ sv_self, sv_env, sv_stack, sv_value, &sv_error);
              break;
            }
            // Argument conversion - short array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
              sv_value = SPVM_XS_UTIL_new_short_array(aTHX_ sv_self, sv_env, sv_stack, sv_value, &sv_error);
              break;
            }
            // Argument conversion - int array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
              sv_value = SPVM_XS_UTIL_new_int_array(aTHX_ sv_self, sv_env, sv_stack, sv_value, &sv_error);
              break;
            }
            // Argument conversion - long array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
              sv_value = SPVM_XS_UTIL_new_long_array(aTHX_ sv_self, sv_env, sv_stack, sv_value, &sv_error);
              break;
            }
            // Argument conversion - float array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
              sv_value = SPVM_XS_UTIL_new_float_array(aTHX_ sv_self, sv_env, sv_stack, sv_value, &sv_error);
              break;
            }
            // Argument conversion - double array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
              sv_value = SPVM_XS_UTIL_new_double_array(aTHX_ sv_self, sv_env, sv_stack, sv_value, &sv_error);
              break;
            }
            default: {
              assert(0);
            }
          }
          
          if (SvOK(sv_error)) {
            croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", args_index_nth, method_name, class_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
          }
          
          void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
          
          stack[stack_index].oval = spvm_array;
          
          stack_index++;
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
        {
          SV* sv_error = &PL_sv_undef;
          sv_value = SPVM_XS_UTIL_new_mulnum_array(aTHX_ sv_self, sv_env, sv_stack, arg_basic_type_id, sv_value, &sv_error);
          
          if (SvOK(sv_error)) {
            croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", args_index_nth, method_name, class_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
          }
          
          void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
          
          stack[stack_index].oval = spvm_array;
            
          stack_index++;
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING: {
          SV* sv_error = &PL_sv_undef;
          
          sv_value = SPVM_XS_UTIL_new_string_array(aTHX_ sv_self, sv_env, sv_stack, sv_value, &sv_error);
          
          if (SvOK(sv_error)) {
            croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", args_index_nth, method_name, class_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
          }
          
          void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
          
          stack[stack_index].oval = spvm_array;
          
          stack_index++;
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
        {
          // Argument conversion - array of class or interface or any object
          SV* sv_error = &PL_sv_undef;
          
          sv_value = SPVM_XS_UTIL_new_object_array(aTHX_ sv_self, sv_env, sv_stack, arg_basic_type_id, sv_value, &sv_error);
          
          if (SvOK(sv_error)) {
            croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", args_index_nth, method_name, class_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
          }
          
          void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
          
          stack[stack_index].oval = spvm_array;
          
          stack_index++;
          break;
        }
        default: {
          assert(0);
        }
      }
    }
    else if (arg_type_dimension > 1) {
      
      // Argument conversion - multi-dimensional array
      SV* sv_error = &PL_sv_undef;
      
      sv_value = SPVM_XS_UTIL_new_muldim_array(aTHX_ sv_self, sv_env, sv_stack, arg_basic_type_id, arg_type_dimension, sv_value, &sv_error);
      
      if (SvOK(sv_error)) {
        croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", args_index_nth, method_name, class_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
      }
      
      void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_value);
      
      stack[stack_index].oval = spvm_array;
      
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
  int32_t error_code_ret = env->call_method(env, stack, method_id, args_native_stack_length);
  
  if (error_code_ret) {
    if (SvOK(sv_error_ret)) {
      HV* hv_error_ret = (HV*)SvRV(sv_error_ret);
      SV* sv_error_code_ret = sv_2mortal(newSViv(error_code_ret));
      (void)hv_store(hv_error_ret, "code", strlen("code"), SvREFCNT_inc(sv_error_code_ret), 0);
    }
    
    void* exception = env->get_exception(env, stack);
    int32_t length = env->length(env, stack, exception);
    const char* exception_chars = env->get_chars(env, stack, exception);
    SV* sv_exception = sv_2mortal(newSVpvn((char*)exception_chars, length));
    croak("%s\n    %s at %s line %d\n", SvPV_nolen(sv_exception), __func__, FILE_NAME, __LINE__);
  }
  
  // Return value conversion
  SV* sv_return_value = NULL;
  if (method_return_type_dimension == 0) {
    switch (method_return_basic_type_category) {
      // Return value conversion - void
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID: {
        break;
      }
      // Return value conversion - numeric
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
        switch (method_return_basic_type_id) {
          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
            // Return value conversion - byte
            sv_return_value = sv_2mortal(newSViv(stack[0].bval));
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
            // Return value conversion - short
            sv_return_value = sv_2mortal(newSViv(stack[0].sval));
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
            // Return value conversion - int
            sv_return_value = sv_2mortal(newSViv(stack[0].ival));
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
            // Return value conversion - long
            sv_return_value = sv_2mortal(newSViv(stack[0].lval));
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
            // Return value conversion - float
            sv_return_value = sv_2mortal(newSVnv(stack[0].fval));
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
            // Return value conversion - double
            sv_return_value = sv_2mortal(newSVnv(stack[0].dval));
            break;
          }
          default: {
            assert(0);
          }
        }
        break;
      }
      // Return value conversion - multi-numeric
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
              // Return value conversion - multi-numeric byte
              sv_field_value = sv_2mortal(newSViv(stack[field_index].bval));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
              // Return value conversion - multi-numeric short
              sv_field_value = sv_2mortal(newSViv(stack[field_index].sval));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
              // Return value conversion - multi-numeric int
              sv_field_value = sv_2mortal(newSViv(stack[field_index].ival));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
              // Return value conversion - multi-numeric long
              sv_field_value = sv_2mortal(newSViv(stack[field_index].lval));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
              // Return value conversion - multi-numeric float
              sv_field_value = sv_2mortal(newSVnv(stack[field_index].fval));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
              // Return value conversion - multi-numeric double
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
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING: {
        // Return value conversion - string
        void* return_value = (void*)stack[0].oval;
        sv_return_value = NULL;
        if (return_value != NULL) {
          env->inc_ref_count(env, stack, return_value);
          int32_t return_value_basic_type_id = env->get_object_basic_type_id(env, stack, return_value);
          sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, return_value, "SPVM::BlessedObject::String");
        }
        // undef
        else {
          sv_return_value = &PL_sv_undef;
        }
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
      {
        // Return value conversion - any object
        void* return_value = (void*)stack[0].oval;
        sv_return_value = NULL;
        if (return_value != NULL) {
          env->inc_ref_count(env, stack, return_value);
          int32_t return_value_basic_type_id = env->get_object_basic_type_id(env, stack, return_value);
          int32_t return_value_type_dimension = env->get_object_type_dimension(env, stack, return_value);
          if (return_value_type_dimension > 0) {
            sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, return_value, "SPVM::BlessedObject::Array");
          }
          else {
            sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, return_value, "SPVM::BlessedObject::Class");
          }
        }
        // undef
        else {
          sv_return_value = &PL_sv_undef;
        }
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
      case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
      {
        // Return value conversion - class or interface
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
        break;
      }
      default: {
        assert(0);
      }
    }
  }
  else if (method_return_type_dimension > 0) {
    // Return value conversion - array
    void* return_value = (void*)stack[0].oval;
    sv_return_value = NULL;
    if (return_value != NULL) {
      env->inc_ref_count(env, stack, return_value);
      sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, return_value, "SPVM::BlessedObject::Array");
    }
    else {
      sv_return_value = &PL_sv_undef;
    }
  }
  
  // Restore reference
  if (args_have_ref) {
    for (int32_t args_index = 0; args_index < method_args_length; args_index++) {
      SV* sv_value = ST(spvm_args_base + args_index);
      
      // Argument type
      int32_t arg_id = method_args_base_id + args_index;
      int32_t arg_type_id = env->api->runtime->get_arg_type_id(env->runtime, arg_id);
      int32_t arg_basic_type_id = env->api->runtime->get_type_basic_type_id(env->runtime, arg_type_id);
      int32_t arg_type_dimension = env->api->runtime->get_type_dimension(env->runtime, arg_type_id);
      int32_t arg_type_flag = env->api->runtime->get_type_flag(env->runtime, arg_type_id);
      int32_t arg_basic_type_category = env->api->runtime->get_basic_type_category(env->runtime, arg_basic_type_id);
      
      // Restore reference - numeric
      if (arg_type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF) {
        int32_t ref_stack_index = ref_stack_indexes[args_index];
        switch (arg_basic_type_category) {
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
            switch (arg_basic_type_id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
                // Restore reference - byte
                SV* sv_value_deref = SvRV(sv_value);
                sv_setiv(sv_value_deref, ref_stack[ref_stack_index].bval);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
                // Restore reference - short
                SV* sv_value_deref = SvRV(sv_value);
                sv_setiv(sv_value_deref, ref_stack[ref_stack_index].sval);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
                // Restore reference - int
                SV* sv_value_deref = SvRV(sv_value);
                sv_setiv(sv_value_deref, ref_stack[ref_stack_index].ival);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
                // Restore reference - long
                SV* sv_value_deref = SvRV(sv_value);
                sv_setiv(sv_value_deref, ref_stack[ref_stack_index].lval);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
                // Restore reference - float
                SV* sv_value_deref = SvRV(sv_value);
                sv_setnv(sv_value_deref, ref_stack[ref_stack_index].fval);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
                // Restore reference - double
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
          // Restore reference value - multi-numeric
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
                  // Restore reference value - multi-numeric byte
                  sv_field_value = sv_2mortal(newSViv(((int8_t*)&ref_stack[ref_stack_index])[field_index]));
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                  // Restore reference value - multi-numeric short
                  sv_field_value = sv_2mortal(newSViv(((int16_t*)&ref_stack[ref_stack_index])[field_index]));
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                  // Restore reference value - multi-numeric int
                  sv_field_value = sv_2mortal(newSViv(((int32_t*)&ref_stack[ref_stack_index])[field_index]));
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                  // Restore reference value - multi-numeric long
                  sv_field_value = sv_2mortal(newSViv(((int64_t*)&ref_stack[ref_stack_index])[field_index]));
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                  // Restore reference value - multi-numeric float
                  sv_field_value = sv_2mortal(newSVnv(((float*)&ref_stack[ref_stack_index])[field_index]));
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                  // Restore reference value - multi-numeric double
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
  
  // Count of return value
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

SV*
_xs_dump(...)
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
  
  SV* sv_object = ST(1);
  
  // Array must be a SPVM::BlessedObject or SPVM::BlessedObject
  if (SvOK(sv_object)) {
    if (!(SvROK(sv_object) && sv_derived_from(sv_object, "SPVM::BlessedObject"))) {
      croak("The $object must be a SPVM::BlessedObject object\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
  }
  
  // Get object
  void* object = SPVM_XS_UTIL_get_object(aTHX_ sv_object);
  
  void* spvm_dump = env->dump(env, stack, object);
  
  const char* dump = env->get_chars(env, stack, spvm_dump);
  int32_t dump_length = env->length(env, stack, spvm_dump);
  
  SV* sv_dump = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_dump, "SPVM::BlessedObject::String");
  
  XPUSHs(sv_dump);
  XSRETURN(1);
}

SV*
_xs_new_string(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_string = SPVM_XS_UTIL_new_string(aTHX_ sv_self, sv_env, sv_stack, sv_string, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $string%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

SV*
_xs_new_address_object(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_address = SPVM_XS_UTIL_new_address_object(aTHX_ sv_self, sv_env, sv_stack, sv_address, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $address%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_address);
  XSRETURN(1);
}

SV*
_xs_new_byte_array(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_byte_array(aTHX_ sv_self, sv_env, sv_stack, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_byte_array_unsigned(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_byte_array_unsigned(aTHX_ sv_self, sv_env, sv_stack, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_byte_array_len(...)
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
    croak("The $length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* spvm_array = env->new_byte_array(env, stack, length);
  
  // New sv array
  SV* sv_byte_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_byte_array);
  XSRETURN(1);
}

SV*
_xs_new_byte_array_from_bin(...)
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
  
  void* spvm_array = NULL;
  if (SvOK(sv_binary)) {
    STRLEN length;
    int8_t* binary = (int8_t*)SvPV(sv_binary, length);
    
    // New array
    spvm_array = env->new_byte_array(env, stack, (int32_t)length);
    
    int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
    memcpy(elems, binary, length);
  }
  else {
    croak("The $binary must be defined\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_short_array(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_short_array(aTHX_ sv_self, sv_env, sv_stack, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_short_array_unsigned(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_short_array_unsigned(aTHX_ sv_self, sv_env, sv_stack, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_short_array_len(...)
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
    croak("The $length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* spvm_array = env->new_short_array(env, stack, length);
  
  // New sv array
  SV* sv_short_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_short_array);
  XSRETURN(1);
}

SV*
_xs_new_short_array_from_bin(...)
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
  
  void* spvm_array = NULL;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    
    if (!(binary_length % 2 == 0)) {
      croak("The length of the $binary must be divisible by 2\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    int32_t array_length = binary_length / sizeof(int16_t);
    int16_t* binary = (int16_t*)SvPV_nolen(sv_binary);
    
    // New array
    spvm_array = env->new_short_array(env, stack, array_length);

    int16_t* elems = env->get_elems_short(env, stack, spvm_array);
    memcpy(elems, binary, array_length * sizeof(int16_t));
  }
  else {
    croak("The $binary must be defined\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_int_array(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_int_array(aTHX_ sv_self, sv_env, sv_stack, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_int_array_unsigned(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_int_array_unsigned(aTHX_ sv_self, sv_env, sv_stack, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_int_array_len(...)
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
    croak("The $length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* spvm_array = env->new_int_array(env, stack, length);
  
  // New sv array
  SV* sv_int_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_int_array);
  XSRETURN(1);
}

SV*
_xs_new_int_array_from_bin(...)
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
  
  void* spvm_array = NULL;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    
    if (!(binary_length % 4 == 0)) {
      croak("The length of the $binary must be divisible by 4\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    int32_t array_length = binary_length / sizeof(int32_t);
    int32_t* binary = (int32_t*)SvPV_nolen(sv_binary);
    
    // New array
    spvm_array = env->new_int_array(env, stack, array_length);
    
    int32_t* elems = env->get_elems_int(env, stack, spvm_array);
    memcpy(elems, binary, array_length * sizeof(int32_t));
  }
  else {
    croak("The $binary must be defined\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_long_array(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_long_array(aTHX_ sv_self, sv_env, sv_stack, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_long_array_unsigned(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_long_array_unsigned(aTHX_ sv_self, sv_env, sv_stack, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_long_array_len(...)
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
    croak("The $length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* spvm_array = env->new_long_array(env, stack, length);
  
  // New sv array
  SV* sv_long_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_long_array);
  XSRETURN(1);
}

SV*
_xs_new_long_array_from_bin(...)
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
  
  void* spvm_array = NULL;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    
    if (!(binary_length % 8 == 0)) {
      croak("The length of the $binary must be divisible by 8\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    int32_t array_length = binary_length / sizeof(int64_t);
    int64_t* binary = (int64_t*)SvPV_nolen(sv_binary);
    
    // New array
    spvm_array = env->new_long_array(env, stack, array_length);
    
    int64_t* elems = env->get_elems_long(env, stack, spvm_array);
    memcpy(elems, binary, array_length * sizeof(int64_t));
  }
  else {
    croak("The $binary must be defined\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
    
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_float_array(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_float_array(aTHX_ sv_self, sv_env, sv_stack, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_float_array_len(...)
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
    croak("The $length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* spvm_array = env->new_float_array(env, stack, length);
  
  // New sv array
  SV* sv_float_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_float_array);
  XSRETURN(1);
}

SV*
_xs_new_float_array_from_bin(...)
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
  
  void* spvm_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    
    if (!(binary_length % 4 == 0)) {
      croak("The length of the $binary must be divisible by 4\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    int32_t array_length = binary_length / sizeof(float);
    float* binary = (float*)SvPV_nolen(sv_binary);
    
    // New array
    spvm_array = env->new_float_array(env, stack, array_length);
    
    float* elems = env->get_elems_float(env, stack, spvm_array);
    memcpy(elems, binary, array_length * sizeof(float));
  }
  else {
    croak("The $binary must be defined\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_double_array(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_double_array(aTHX_ sv_self, sv_env, sv_stack, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_double_array_len(...)
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
    croak("The $length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* spvm_array = env->new_double_array(env, stack, length);
  
  // New sv array
  SV* sv_double_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_double_array);
  XSRETURN(1);
}

SV*
_xs_new_double_array_from_bin(...)
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
  
  void* spvm_array = NULL;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    
    if (!(binary_length % 8 == 0)) {
      croak("The length of the $binary must be divisible by 8\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    int32_t array_length = binary_length / sizeof(double);
    double* binary = (double*)SvPV_nolen(sv_binary);
    
    // New array
    spvm_array = env->new_double_array(env, stack, array_length);

    double* elems = env->get_elems_double(env, stack, spvm_array);
    memcpy(elems, binary, array_length * sizeof(double));
  }
  else {
    croak("The $binary must be defined\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_string_array(...)
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
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_string_array(aTHX_ sv_self, sv_env, sv_stack, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_string_array_len(...)
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
    croak("The $length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* spvm_array = env->new_string_array(env, stack, length);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_object_array_len(...)
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
    croak("The $length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  int32_t basic_type_id = env->api->runtime->get_basic_type_id_by_name(env->runtime, basic_type_name);
  if (basic_type_id < 0) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  // New array
  void* spvm_array = env->new_object_array(env, stack, basic_type_id, length);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
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
  SV* sv_array = ST(2);
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  int32_t basic_type_id = env->api->runtime->get_basic_type_id_by_name(env->runtime, basic_type_name);
  if (basic_type_id < 0) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_object_array(aTHX_ sv_self, sv_env, sv_stack, basic_type_id, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
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
  SV* sv_type_dimension = ST(2);
  SV* sv_array = ST(3);
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  int32_t basic_type_id = env->api->runtime->get_basic_type_id_by_name(env->runtime, basic_type_name);
  if (basic_type_id < 0) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  int32_t type_dimension = (int32_t)SvIV(sv_type_dimension);
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_muldim_array(aTHX_ sv_self, sv_env, sv_stack, basic_type_id, type_dimension, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
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
  SV* sv_array = ST(2);

  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);

  int32_t basic_type_id = env->api->runtime->get_basic_type_id_by_name(env->runtime, basic_type_name);
  if (basic_type_id < 0) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_mulnum_array(aTHX_ sv_self, sv_env, sv_stack, basic_type_id, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
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
    croak("The $binary must be defined\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
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
  
  if (binary_length % (field_native_stack_length * field_length) != 0) {
    croak("The length of the $binary must be divisible by %d * %d\n    %s at %s line %d", field_native_stack_length, field_length, __func__, FILE_NAME, __LINE__);
  }
  
  int32_t array_length = binary_length / field_length / field_native_stack_length;

  void* spvm_array = env->new_mulnum_array(env, stack, basic_type_id, array_length);

  int32_t dimension = env->get_object_type_dimension(env, stack, spvm_array);
  
  int32_t copy_length = field_length * array_length * field_native_stack_length;
  switch (mulnum_field_type_basic_type_id) {
    case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
      int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
      if (array_length > 0) {
        memcpy(elems, binary, copy_length);
      }
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
      int16_t* elems = env->get_elems_short(env, stack, spvm_array);
      if (array_length > 0) {
        memcpy(elems, binary, copy_length);
      }
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
      int32_t* elems = env->get_elems_int(env, stack, spvm_array);
      if (array_length > 0) {
        memcpy(elems, binary, copy_length);
      }
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
      int64_t* elems = env->get_elems_long(env, stack, spvm_array);
      if (array_length > 0) {
        memcpy(elems, binary, copy_length);
      }
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
      float* elems = env->get_elems_float(env, stack, spvm_array);
      if (array_length > 0) {
        memcpy(elems, binary, copy_length);
      }
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
      double* elems = env->get_elems_double(env, stack, spvm_array);
      if (array_length > 0) {
        memcpy(elems, binary, copy_length);
      }
      break;
    }
    default:
      assert(0);
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, sv_env, sv_stack, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_get_exception(...)
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
  
  SV* sv_message = ST(1);
  
  SV* sv_error = &PL_sv_undef;
  sv_message = SPVM_XS_UTIL_new_string(aTHX_ sv_self, sv_env, sv_stack, sv_message, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("The $message%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_message = SPVM_XS_UTIL_get_object(aTHX_ sv_message);
  
  env->set_exception(env, stack, spvm_message);
  
  XSRETURN(0);
}

SV*
_xs_get_memory_blocks_count(...)
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
  SV** sv_api_ptr = hv_fetch(hv_object, "__api", strlen("__api"), 0);
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

MODULE = SPVM::BlessedObject::String		PACKAGE = SPVM::BlessedObject::String

SV*
_xs_to_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  // API
  SV** sv_api_ptr = hv_fetch(hv_self, "__api", strlen("__api"), 0);
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
  
  assert(SvROK(sv_self) && sv_derived_from(sv_self, "SPVM::BlessedObject::String"));
  
  // Get object
  void* spvm_string = SPVM_XS_UTIL_get_object(aTHX_ sv_self);
  
  int32_t length = env->length(env, stack, spvm_string);
  const char* chars = env->get_chars(env, stack, spvm_string);
  
  SV* sv_return_value = sv_2mortal(newSVpv(chars, length));
  
  XPUSHs(sv_return_value);
  XSRETURN(1);
}

MODULE = SPVM::BlessedObject::Array		PACKAGE = SPVM::BlessedObject::Array

SV*
_xs_length(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // API
  SV** sv_api_ptr = hv_fetch(hv_self, "__api", strlen("__api"), 0);
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
  
  // Runtime
  void* runtime = env->runtime;
  
  assert(SvROK(sv_self) && sv_derived_from(sv_self, "SPVM::BlessedObject::Array"));
  
  // Get object
  void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_self);
  
  int32_t length = env->length(env, stack, spvm_array);
  
  SV* sv_length = sv_2mortal(newSViv(length));
  
  XPUSHs(sv_length);
  XSRETURN(1);
}

SV*
_xs_to_elems(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // API
  SV** sv_api_ptr = hv_fetch(hv_self, "__api", strlen("__api"), 0);
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
  
  // Runtime
  void* runtime = env->runtime;
  
  assert(SvROK(sv_self) && sv_derived_from(sv_self, "SPVM::BlessedObject::Array"));
  
  // Get object
  void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_self);
  
  int32_t length = env->length(env, stack, spvm_array);
  
  int32_t basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
  int32_t dimension = env->get_object_type_dimension(env, stack, spvm_array);
  int32_t is_array_type = dimension > 0;
  
  assert(is_array_type);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  if (is_array_type) {
    int32_t elem_type_dimension = dimension - 1;
    
    int32_t array_is_mulnum_array = env->is_mulnum_array(env, stack, spvm_array);
    int32_t array_is_object_array = env->is_object_array(env, stack, spvm_array);
    
    if (array_is_mulnum_array) {
      
      for (int32_t index = 0; index < length; index++) {
        int32_t class_id = env->api->runtime->get_basic_type_class_id(env->runtime, env->get_object_basic_type_id(env, stack, spvm_array));
        int32_t class_fields_length = env->api->runtime->get_class_fields_length(env->runtime, class_id);
        int32_t class_fields_base_id = env->api->runtime->get_class_fields_base_id(env->runtime, class_id);
        
        int32_t mulnum_field_id = class_fields_base_id;
        int32_t mulnum_field_type_id = env->api->runtime->get_field_type_id(env->runtime, mulnum_field_id);
        
        void* elems = (void*)env->get_elems_int(env, stack, spvm_array);
        
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
          void* object = env->get_elem_string(env, stack, spvm_array, i);
          
          SV* sv_value;
          if (object != NULL) {
            env->inc_ref_count(env, stack, object);
            sv_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, sv_env, sv_stack, object, "SPVM::BlessedObject::String");
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
          void* value = env->get_elem_object(env, stack, spvm_array, index);
          if (value == NULL) {
            av_push(av_values, &PL_sv_undef);
          }
          else {
            env->inc_ref_count(env, stack, value);
            int32_t elem_type_is_array_type = elem_type_dimension > 0;
            SV* sv_value;
            if (elem_type_is_array_type) {
              sv_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, sv_env, sv_stack, value, "SPVM::BlessedObject::Array");
            }
            else {
              sv_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, sv_env, sv_stack, value, "SPVM::BlessedObject::Class");
            }
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
        }
      }
    }
    else {
      switch (basic_type_id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, stack, spvm_array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          int32_t* elems = env->get_elems_int(env, stack, spvm_array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, stack, spvm_array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          float* elems = env->get_elems_float(env, stack, spvm_array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSVnv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, stack, spvm_array);
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

  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
_xs_to_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // API
  SV** sv_api_ptr = hv_fetch(hv_self, "__api", strlen("__api"), 0);
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
  
  // Runtime
  void* runtime = env->runtime;
  
  assert(SvROK(sv_self) && sv_derived_from(sv_self, "SPVM::BlessedObject::Array"));
  
  // Get object
  void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_self);
  
  int32_t length = env->length(env, stack, spvm_array);
  
  int32_t basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
  int32_t dimension = env->get_object_type_dimension(env, stack, spvm_array);
  int32_t is_array_type = dimension > 0;
  assert(is_array_type);
  
  SV* sv_binary;
  if (is_array_type) {
    int32_t elem_type_dimension = dimension - 1;
    
    int32_t array_is_mulnum_array = env->is_mulnum_array(env, stack, spvm_array);
    int32_t array_is_object_array = env->is_object_array(env, stack, spvm_array);
    
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
          int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, field_length * length));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, field_length * length * 2));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          int32_t* elems = env->get_elems_int(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, field_length * length * 4));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, field_length * length * 8));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          float* elems = env->get_elems_float(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, field_length * length * 4));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, field_length * length * 8));
          break;
        }
        default: {
          assert(0);
        }
      }
    }
    else if (array_is_object_array) {
      croak("The object array can't be converted to a binary\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    else {
      switch (basic_type_id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, length));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, length * 2));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          int32_t* elems = env->get_elems_int(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, length * 4));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, length * 8));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          float* elems = env->get_elems_float(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, length * 4));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, length * 8));
          break;
        }
        default: {
          assert(0);
        }
      }
    }
  }
  
  XPUSHs(sv_binary);
  XSRETURN(1);
}

SV*
_xs_set(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // API
  SV** sv_api_ptr = hv_fetch(hv_self, "__api", strlen("__api"), 0);
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
  
  SV* sv_index = ST(1);
  SV* sv_elem = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Array
  void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_self);
  
  // Length
  int32_t length = env->length(env, stack, spvm_array);
  
  // Check range
  if (!(index >= 0 && index < length)) {
    croak("The $index must be greatr than or equal to 0 and less than the length of the array\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
  int32_t type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
  
  if (type_dimension == 1) {
    switch (basic_type_id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
        // Value
        int8_t elem = (int8_t)SvIV(sv_elem);
        
        // Set element
        int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
        
        elems[index] = elem;
        
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
        // Value
        int16_t elem = (int16_t)SvIV(sv_elem);
        
        // Set element
        int16_t* elems = env->get_elems_short(env, stack, spvm_array);
        
        elems[index] = elem;
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
        // Value
        int32_t elem = (int32_t)SvIV(sv_elem);
        
        // Set element
        int32_t* elems = env->get_elems_int(env, stack, spvm_array);
        
        elems[index] = elem;
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
        // Value
        int64_t elem = (int64_t)SvIV(sv_elem);
        
        // Set element
        int64_t* elems = env->get_elems_long(env, stack, spvm_array);
        
        elems[index] = elem;
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
        // Value
        float elem = (float)SvNV(sv_elem);
        
        // Set element
        float* elems = env->get_elems_float(env, stack, spvm_array);
        
        elems[index] = elem;
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
        // Value
        double elem = (double)SvNV(sv_elem);
        
        // Set element
        double* elems = env->get_elems_double(env, stack, spvm_array);
        
        elems[index] = elem;
        break;
      }
      default: {
        // Get object
        void* elem = SPVM_XS_UTIL_get_object(aTHX_ sv_elem);
        
        env->set_elem_object(env, stack, spvm_array, index, elem);
      }
    }
  }
  else if (type_dimension > 1) {
    
    // Get object
    void* elem = SPVM_XS_UTIL_get_object(aTHX_ sv_elem);
    
    int32_t elem_isa = env->elem_isa(env, stack, spvm_array, elem);
    if (!elem_isa) {
      croak("The $elem must be assigned to the element of the array\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    env->set_elem_object(env, stack, spvm_array, index, elem);
  }
  else {
    assert(0);
  }
  
  XSRETURN(0);
}

SV*
_xs_get(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // API
  SV** sv_api_ptr = hv_fetch(hv_self, "__api", strlen("__api"), 0);
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
  
  SV* sv_index = ST(1);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Array
  void* spvm_array = SPVM_XS_UTIL_get_object(aTHX_ sv_self);
  
  // Length
  int32_t length = env->length(env, stack, spvm_array);
  
  // Check range
  if (!(index >= 0 && index < length)) {
    croak("The $index must be greater than or equal to 0 and less than the length of the array\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t basic_type_id = env->get_object_basic_type_id(env, stack, spvm_array);
  int32_t type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
  
  assert(type_dimension >= 1);
  SV* sv_elem = NULL;
  int32_t elem_is_object = 0;
  if (type_dimension == 1) {
    switch (basic_type_id) {
      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
        // Get element
        int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
        int8_t elem = elems[index];
        sv_elem = sv_2mortal(newSViv(elem));
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
        // Get element
        int16_t* elems = env->get_elems_short(env, stack, spvm_array);
        int16_t elem = elems[index];
        sv_elem = sv_2mortal(newSViv(elem));
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
        // Get element
        int32_t* elems = env->get_elems_int(env, stack, spvm_array);
        int32_t elem = elems[index];
        sv_elem = sv_2mortal(newSViv(elem));
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
        // Get element
        int64_t* elems = env->get_elems_long(env, stack, spvm_array);
        int64_t elem = elems[index];
        sv_elem = sv_2mortal(newSViv(elem));
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
        // Get element
        float* elems = env->get_elems_float(env, stack, spvm_array);
        float elem = elems[index];
        sv_elem = sv_2mortal(newSVnv(elem));
        break;
      }
      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
        // Get element
        double* elems = env->get_elems_double(env, stack, spvm_array);
        double elem = elems[index];
        sv_elem = sv_2mortal(newSVnv(elem));
        break;
      }
      default: {
        elem_is_object = 1;
      }
    }
  }
  else if (type_dimension > 1) {
    elem_is_object = 1;
  }
  
  if (elem_is_object) {
    void* runtime = env->runtime;
    
    // Element type dimension
    int32_t elem_type_dimension = env->get_object_type_dimension(env, stack, spvm_array) - 1;
    
    // Index
    void* elem = env->get_elem_object(env, stack, spvm_array, index);
    
    if (elem_type_dimension == 0) {
      sv_elem = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, sv_env, sv_stack, elem, "SPVM::BlessedObject::Class");
    }
    else if (elem_type_dimension > 0) {
      sv_elem = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, sv_env, sv_stack, elem, "SPVM::BlessedObject::Array");
    }
  }
  
  XPUSHs(sv_elem);
  XSRETURN(1);
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
  SV** sv_api_ptr = hv_fetch(hv_object, "__api", strlen("__api"), 0);
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
    SV* sv_32bit_code = sv_2mortal(newSViv(spvm_32bit_code));
    av_push(av_runtime_codes, SvREFCNT_inc(sv_32bit_code));
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
    void* spvm_program_name = env->new_string(env, my_stack, program_name, program_name_length);
    
    // Set command info
    {
      int32_t e;
      e = env->set_command_info_program_name(env, spvm_program_name);
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
    
    void* spvm_argv = env->new_object_array(env, my_stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, argv_length);
    for (int32_t index = 0; index < argv_length; index++) {
      SV** sv_arg_ptr = av_fetch(av_argv, index, 0);
      SV* sv_arg = sv_arg_ptr ? *sv_arg_ptr : &PL_sv_undef;
      
      const char* arg = SvPV_nolen(sv_arg);
      int32_t arg_length = strlen(arg);
      
      void* spvm_arg = env->new_string(env, my_stack, arg, arg_length);
      env->set_elem_string(env, my_stack, spvm_argv, index, spvm_arg);
    }
    
    // Set command info
    {
      int32_t e;
      e = env->set_command_info_argv(env, spvm_argv);
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

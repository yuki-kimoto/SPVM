#define PERL_NO_GET_CONTEXT     /* For performance */
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#undef call_method
#undef leave_scope

#include "spvm_native.h"

#if !defined(SvIsBOOL)
  #define SvIsBOOL(value) 0
#endif

static const char* FILE_NAME = "SPVM.xs";

void* SPVM_XS_UTIL_get_pointer(pTHX_ SV* sv_data) {
  
  if (SvOK(sv_data)) {
    HV* hv_data = (HV*)SvRV(sv_data);
    
    SV** sv_pointer_ptr = hv_fetch(hv_data, "pointer", strlen("pointer"), 0);
    SV* sv_pointer = sv_pointer_ptr ? *sv_pointer_ptr : &PL_sv_undef;
    size_t iv_pointer = SvIV(SvRV(sv_pointer));
    void* pointer = INT2PTR(void*, iv_pointer);
    
    return pointer;
  }
  else {
    return NULL;
  }
}

void* SPVM_XS_UTIL_get_spvm_object(pTHX_ SV* sv_blessed_object) {
  
  if (SvOK(sv_blessed_object)) {
    HV* hv_blessed_object = (HV*)SvRV(sv_blessed_object);
    
    SV** sv_spvm_object_ptr = hv_fetch(hv_blessed_object, "spvm_object", strlen("spvm_object"), 0);
    SV* sv_spvm_object = sv_spvm_object_ptr ? *sv_spvm_object_ptr : &PL_sv_undef;
    void** spvm_object_ref = (void**)SvPV_nolen(sv_spvm_object);
    void* spvm_object = *spvm_object_ref;
    
    return spvm_object;
  }
  else {
    return NULL;
  }
}

SPVM_ENV* SPVM_XS_UTIL_get_env(pTHX_ SV* sv_env) {
  
  SPVM_ENV* env;
  if (sv_isobject(sv_env) && sv_derived_from(sv_env, "SPVM::Builder::Env")) {
    env = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env);
  }
  else if (sv_isobject(sv_env) && sv_derived_from(sv_env, "SPVM::BlessedObject::Class")) {
    void* spvm_env = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_env);
    
    SPVM_ENV* env_api = SPVM_NATIVE_new_env();
    
    env = env_api->get_pointer(env_api, NULL, spvm_env);
    
    env_api->free_env(env_api);
  }
  
  return env;
}

SPVM_VALUE* SPVM_XS_UTIL_get_stack(pTHX_ SV* sv_stack) {
  
  SPVM_VALUE* stack;
  if (sv_isobject(sv_stack) && sv_derived_from(sv_stack, "SPVM::Builder::Stack")) {
    stack = SPVM_XS_UTIL_get_pointer(aTHX_ sv_stack);
  }
  else if (sv_isobject(sv_stack) && sv_derived_from(sv_stack, "SPVM::BlessedObject::Class")) {
    void* spvm_stack = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_stack);
    
    SPVM_ENV* env_api = SPVM_NATIVE_new_env();
    
    stack = env_api->get_pointer(env_api, NULL, spvm_stack);
    
    env_api->free_env(env_api);
  }
  
  return stack;
}

SV* SPVM_XS_UTIL_new_sv_blessed_object(pTHX_ SV* sv_api, void* spvm_object, const char* class) {
  
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  SV* sv_spvm_object = sv_2mortal(newSVpv("", sizeof(void*)));
  void** spvm_object_ref = (void**)SvPV_nolen(sv_spvm_object);
  *spvm_object_ref = NULL;
  
  env->assign_object(env, stack, spvm_object_ref, spvm_object);
  
  HV* hv_blessed_object = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_blessed_object = sv_2mortal(newRV_inc((SV*)hv_blessed_object));
  
  (void)hv_store(hv_blessed_object, "spvm_object", strlen("spvm_object"), SvREFCNT_inc(sv_spvm_object), 0);
  
  if (SvOK(sv_api)) {
    (void)hv_store(hv_blessed_object, "__api", strlen("__api"), SvREFCNT_inc(sv_api), 0);
  }
  
  HV* hv_class = gv_stashpv(class, 0);
  sv_bless(sv_blessed_object, hv_class);
  
  return sv_blessed_object;
}

SV* SPVM_XS_UTIL_new_sv_pointer_object(pTHX_ void* pointer, const char* class) {
  
  size_t iv_pointer = PTR2IV(pointer);
  SV* sviv_pointer = sv_2mortal(newSViv(iv_pointer));
  SV* sv_pointer = sv_2mortal(newRV_inc(sviv_pointer));
  
  HV* hv_pointer_object = (HV*)sv_2mortal((SV*)newHV());
  (void)hv_store(hv_pointer_object, "pointer", strlen("pointer"), SvREFCNT_inc(sv_pointer), 0);
  SV* sv_pointer_object = sv_2mortal(newRV_inc((SV*)hv_pointer_object));
  
  HV* hv_class = gv_stashpv(class, 0);
  sv_bless(sv_pointer_object, hv_class);
  
  return sv_pointer_object;
}

SV* SPVM_XS_UTIL_new_string(pTHX_ SV* sv_api, SV* sv_string, SV** sv_error) {
  
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  if (SvOK(sv_string)) {
    if (sv_isobject(sv_string) && sv_derived_from(sv_string, "SPVM::BlessedObject::String")) {
      // Nothing
    }
    else if (SvROK(sv_string)) {
      *sv_error = sv_2mortal(newSVpvf(" cannnot be a reference"));
      return &PL_sv_undef;
    }
    else {
      STRLEN length = -1;
      const char* string = SvPV(sv_string, length);
      void* spvm_string = env->new_string_no_mortal(env, stack, string, (int32_t)length);
      sv_string = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_string, "SPVM::BlessedObject::String");
    }
  }
  else {
    sv_string = &PL_sv_undef;
  }
  
  return sv_string;
}

SV* SPVM_XS_UTIL_new_address_object(pTHX_ SV* sv_api, SV* sv_address, SV** sv_error) {
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  int32_t error_id = 0;
  
  *sv_error = &PL_sv_undef;
  
  if (SvOK(sv_address)) {
    if (sv_isobject(sv_address) && sv_derived_from(sv_address, "SPVM::BlessedObject::Class")) {
      void* spvm_address = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_address);
      int32_t type_dimension = 1;
      if (!env->is_type_by_name(env, stack, spvm_address, "Address", type_dimension)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Class object, it must be the Address type"));
        return &PL_sv_undef;
      }
    }
    else if (SvROK(sv_address)) {
      *sv_error = sv_2mortal(newSVpvf(" cannnot be a reference"));
      return &PL_sv_undef;
    }
    else {
      void* address = (void*)(intptr_t)SvIV(sv_address);
      void* basic_type = env->get_basic_type(env, stack, "Address");
      
      void* spvm_address = env->new_pointer_object_no_mortal(env, stack, basic_type, address);
      
      sv_address = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_address, "SPVM::BlessedObject::Class");
    }
  }
  else {
    sv_address = &PL_sv_undef;
  }
  
  return sv_address;
}

SV* SPVM_XS_UTIL_new_byte_array(pTHX_ SV* sv_api, SV* sv_array, SV** sv_error) {
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  *sv_error = &PL_sv_undef;
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      const char* spvm_array_basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(strcmp(spvm_array_basic_type_name, "byte") == 0 && spvm_array_type_dimension == 1)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be the byte[] type"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_byte_array_no_mortal(env, stack, length);
      
      int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          return &PL_sv_undef;
        }
        elems[i] = (int8_t)SvIV(sv_elem);
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_byte_array_unsigned(pTHX_ SV* sv_api, SV* sv_array, SV** sv_error) {
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  *sv_error = &PL_sv_undef;
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      const char* spvm_array_basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(strcmp(spvm_array_basic_type_name, "byte") == 0 && spvm_array_type_dimension == 1)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be the byte[] type"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_byte_array_no_mortal(env, stack, length);
      
      int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          return &PL_sv_undef;
        }
        elems[i] = (int8_t)(uint8_t)SvUV(sv_elem);
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_short_array(pTHX_ SV* sv_api, SV* sv_array, SV** sv_error) {
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  *sv_error = &PL_sv_undef;
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      const char* spvm_array_basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(strcmp(spvm_array_basic_type_name, "short") == 0 && spvm_array_type_dimension == 1)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be the short[] type"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_short_array_no_mortal(env, stack, length);
      
      int16_t* elems = env->get_elems_short(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          return &PL_sv_undef;
        }
        elems[i] = (int16_t)SvIV(sv_elem);
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_short_array_unsigned(pTHX_ SV* sv_api, SV* sv_array, SV** sv_error) {
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  *sv_error = &PL_sv_undef;
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      const char* spvm_array_basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(strcmp(spvm_array_basic_type_name, "short") == 0 && spvm_array_type_dimension == 1)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be the short[] type"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_short_array_no_mortal(env, stack, length);
      
      int16_t* elems = env->get_elems_short(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          return &PL_sv_undef;
        }
        elems[i] = (int16_t)(uint16_t)SvUV(sv_elem);
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_int_array(pTHX_ SV* sv_api, SV* sv_array, SV** sv_error) {
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  *sv_error = &PL_sv_undef;
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      const char* spvm_array_basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(strcmp(spvm_array_basic_type_name, "int") == 0 && spvm_array_type_dimension == 1)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be the int[] type"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_int_array_no_mortal(env, stack, length);
      
      int32_t* elems = env->get_elems_int(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          return &PL_sv_undef;
        }
        elems[i] = (int32_t)SvIV(sv_elem);
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_int_array_unsigned(pTHX_ SV* sv_api, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      const char* spvm_array_basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(strcmp(spvm_array_basic_type_name, "int") == 0 && spvm_array_type_dimension == 1)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be the int[] type"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_int_array_no_mortal(env, stack, length);
      
      int32_t* elems = env->get_elems_int(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          return &PL_sv_undef;
        }
        elems[i] = (int32_t)(uint32_t)SvUV(sv_elem);
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_long_array(pTHX_ SV* sv_api, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      const char* spvm_array_basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(strcmp(spvm_array_basic_type_name, "long") == 0 && spvm_array_type_dimension == 1)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be the long[] type"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_long_array_no_mortal(env, stack, length);
      
      int64_t* elems = env->get_elems_long(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          return &PL_sv_undef;
        }
        elems[i] = (int64_t)SvIV(sv_elem);
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_long_array_unsigned(pTHX_ SV* sv_api, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      const char* spvm_array_basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(strcmp(spvm_array_basic_type_name, "long") == 0 && spvm_array_type_dimension == 1)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be the long[] type"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_long_array_no_mortal(env, stack, length);
      
      int64_t* elems = env->get_elems_long(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          return &PL_sv_undef;
        }
        elems[i] = (int64_t)(uint64_t)SvUV(sv_elem);
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_float_array(pTHX_ SV* sv_api, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      const char* spvm_array_basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(strcmp(spvm_array_basic_type_name, "float") == 0 && spvm_array_type_dimension == 1)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be the float[] type"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_float_array_no_mortal(env, stack, length);
      
      float* elems = env->get_elems_float(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          return &PL_sv_undef;
        }
        elems[i] = (float)SvNV(sv_elem);
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_double_array(pTHX_ SV* sv_api, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      const char* spvm_array_basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(strcmp(spvm_array_basic_type_name, "double") == 0 && spvm_array_type_dimension == 1)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be the double[] type"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_double_array_no_mortal(env, stack, length);
      
      double* elems = env->get_elems_double(env, stack, spvm_array);
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!(SvOK(sv_elem) && !SvROK(sv_elem))) {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          return &PL_sv_undef;
        }
        elems[i] = (double)SvNV(sv_elem);
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_string_array(pTHX_ SV* sv_api, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      const char* spvm_array_basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
      int32_t spvm_array_type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
      if (!(strcmp(spvm_array_basic_type_name, "string") == 0 && spvm_array_type_dimension == 1)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be the string[] type"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_string_array_no_mortal(env, stack, length);
      
      for (int32_t i = 0; i < length; i++) {
        SV** sv_elem_ptr = av_fetch(av_array, i, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        SV* sv_error_elem = &PL_sv_undef;
        sv_elem = SPVM_XS_UTIL_new_string(aTHX_ sv_api, sv_elem, &sv_error_elem);
        
        if (SvOK(sv_error_elem)) {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a non-reference scalar", i + 1));
          return &PL_sv_undef;
        }
        void* spvm_elem = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_elem);
        env->set_elem_string(env, stack, spvm_array, i, spvm_elem);
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_object_array(pTHX_ SV* sv_api, void* basic_type, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      int32_t type_dimension = 1;
      if (!env->isa(env, stack, spvm_array, basic_type, type_dimension)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be assignable"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_object_array_no_mortal(env, stack, basic_type, length);
      
      for (int32_t index = 0; index < length; index++) {
        SV** sv_elem_ptr = av_fetch(av_array, index, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!SvOK(sv_elem)) {
          env->set_elem_object(env, stack, spvm_array, index, NULL);
        }
        else if (sv_isobject(sv_elem) && sv_derived_from(sv_elem, "SPVM::BlessedObject")) {
          void* elem = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_elem);
          
          int32_t elem_isa = env->elem_isa(env, stack, spvm_array, elem);
          if (elem_isa) {
            env->set_elem_object(env, stack, spvm_array, index, elem);
          }
          else {
            void* spvm_elem_type_name = env->get_type_name(env, stack, elem);
            const char* elem_type_name = env->get_chars(env, stack, spvm_elem_type_name);
            *sv_error = sv_2mortal(newSVpvf("'s %dth element must be the \"%s\" assignable type", index + 1, elem_type_name));
            return &PL_sv_undef;
          }
        }
        else {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be an SPVM::BlessedObject or undef", index + 1));
          return &PL_sv_undef;
        }
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_muldim_array(pTHX_ SV* sv_api, void* basic_type, int32_t type_dimension, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      if (!env->isa(env, stack, spvm_array, basic_type, type_dimension)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be assignable"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      // Elements
      AV* av_array = (AV*)SvRV(sv_array);
      
      // Array length
      int32_t length = av_len(av_array) + 1;
      
      // New array
      void* spvm_array = env->new_muldim_array_no_mortal(env, stack, basic_type, type_dimension, length);
      
      for (int32_t index = 0; index < length; index++) {
        SV** sv_elem_ptr = av_fetch(av_array, index, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (!SvOK(sv_elem)) {
          env->set_elem_object(env, stack, spvm_array, index, NULL);
        }
        else if (sv_isobject(sv_elem) && sv_derived_from(sv_elem, "SPVM::BlessedObject")) {
          void* elem = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_elem);
          
          int32_t elem_isa = env->elem_isa(env, stack, spvm_array, elem);
          if (elem_isa) {
            env->set_elem_object(env, stack, spvm_array, index, elem);
          }
          else {
            void* spvm_elem_type_name = env->get_type_name(env, stack, elem);
            const char* elem_type_name = env->get_chars(env, stack, spvm_elem_type_name);
            *sv_error = sv_2mortal(newSVpvf("'s %dth element must be the \"%s\" assignable type", index + 1, elem_type_name));
            return &PL_sv_undef;
          }
        }
        else {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be an SPVM::BlessedObject or undef", index + 1));
          return &PL_sv_undef;
        }
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_mulnum_array(pTHX_ SV* sv_api, void* basic_type, SV* sv_array, SV** sv_error) {
  
  *sv_error = &PL_sv_undef;
  
  HV* hv_self = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  SV** sv_stack_ptr = hv_fetch(hv_self, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  if (SvOK(sv_array)) {
    if (sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array")) {
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_array);
      int32_t type_dimension = 1;
      if (!env->isa(env, stack, spvm_array, basic_type, type_dimension)) {
        *sv_error = sv_2mortal(newSVpvf(": If it is an SPVM::BlessedObject::Array object, the type must be assignable"));
        return &PL_sv_undef;
      }
    }
    else if (!(SvROK(sv_array) && sv_derived_from(sv_array, "ARRAY"))) {
      *sv_error = sv_2mortal(newSVpvf(": If it is a reference, it must be an array reference"));
      return &PL_sv_undef;
    }
    else {
      AV* av_array = (AV*)SvRV(sv_array);
      
      int32_t length = av_len(av_array) + 1;
      
      // Runtime
      void* runtime = env->runtime;
      
      // New array
      void* spvm_array = env->new_mulnum_array_no_mortal(env, stack, basic_type, length);
      
      for (int32_t index = 0; index < length; index++) {
        SV** sv_elem_ptr = av_fetch(av_array, index, 0);
        SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
        
        if (SvROK(sv_elem) && sv_derived_from(sv_elem, "HASH")) {
          
          const char* basic_type_name = env->api->basic_type->get_name(env->runtime, basic_type);
          int32_t basic_type_fields_length = env->api->basic_type->get_fields_length(env->runtime, basic_type);
          
          void* elems = (void*)env->get_elems_int(env, stack, spvm_array);
          
          HV* hv_value = (HV*)SvRV(sv_elem);
          int32_t fields_length = basic_type_fields_length;
          // Field exists check
          int32_t hash_keys_length = 0;
          while (hv_iternext(hv_value)) {
            hash_keys_length++;
          }
          
          for (int32_t field_index = 0; field_index < basic_type_fields_length; field_index++) {
            void* mulnum_field = env->api->basic_type->get_field_by_index(runtime, basic_type, field_index);
            
            const char* mulnum_field_name = env->api->field->get_name(env->runtime, mulnum_field);
            
            SV** sv_field_value_ptr = hv_fetch(hv_value, mulnum_field_name, strlen(mulnum_field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              *sv_error = sv_2mortal(newSVpvf("'s %dth element's hash reference must have the \"%s\" key for the \"%s\" field of the \"%s\" basic type\n    %s at %s line %d\n", index + 1, mulnum_field_name, mulnum_field_name, basic_type_name, __func__, FILE_NAME, __LINE__));
              return &PL_sv_undef;
            }
            
            void* mulnum_field_basic_type = env->api->field->get_basic_type(env->runtime, mulnum_field);
            int32_t mulnum_field_basic_type_id = env->api->basic_type->get_id(env->runtime, mulnum_field_basic_type);
            switch (mulnum_field_basic_type_id) {
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
              default: {
                assert(0);
              }
            }
          }
        }
        else {
          *sv_error = sv_2mortal(newSVpvf("'s %dth element must be a hash reference\n    %s at %s line %d\n", index + 1, __func__, FILE_NAME, __LINE__));
          return &PL_sv_undef;
        }
      }
      
      sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_array, "SPVM::BlessedObject::Array");
    }
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  return sv_array;
}

MODULE = SPVM::ExchangeAPI		PACKAGE = SPVM::ExchangeAPI

SV*
_xs_call_method(...)
  PPCODE:
{
  
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
  
  // Basic Type Name
  void* method = NULL;
  const char* basic_type_name = NULL;
  int32_t class_method_call;
  if (sv_isobject(sv_invocant)) {
    class_method_call = 0;
    if (!(sv_isobject(sv_invocant) && sv_derived_from(sv_invocant, "SPVM::BlessedObject::Class"))) {
      croak("$invocant must be an SPVM::BlessedObject::Class object\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
    
    HV* hv_invocant = (HV*)SvRV(sv_invocant);
    
    void* object = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_invocant);
    basic_type_name = env->get_object_basic_type_name(env, stack, object);
    
    char* found_char = strrchr(method_name, ':');
    if (found_char) {
      if (!(*(found_char - 1) == ':')) {
        croak("The static method call must be valid\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
      }
      *(found_char - 1) = '\0';
      const char* basic_type_name = method_name;
      method_name = found_char + 1;
      
      void* static_call_basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
      if (!static_call_basic_type) {
        croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
      }
      
      int32_t isa = env->isa(env, stack, object, static_call_basic_type, 0);
      if (!isa) {
        croak("The invocant must be assinged to the \"%s\" basic type\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
      }
      
      method = env->api->basic_type->get_method_by_name(env->runtime, static_call_basic_type, method_name);
      *(found_char - 1) = ':';
    }
    else {
      method = env->get_instance_method(env, stack, object, method_name);
    }
    
    if (method) {
      int32_t is_class_method = env->api->method->is_class_method(env->runtime, method);
      if (is_class_method) {
        method = NULL;
      }
    }
    
    ST(1) = sv_method_name;
    ST(2) = sv_invocant;
  }
  else {
    class_method_call = 1;
    basic_type_name = SvPV_nolen(sv_invocant);
    void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
    
    method = env->api->basic_type->get_method_by_name(env->runtime, basic_type, method_name);
    
    if (method) {
      int32_t is_class_method = env->api->method->is_class_method(env->runtime, method);
      if (!is_class_method) {
        method = NULL;
      }
    }
  }
  
  // Runtime
  void* runtime = env->runtime;
  
  // Method not found
  if (!method) {
    croak("The \"%s\" method in the \"%s\" class is not found\n    %s at %s line %d\n", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  // Base index of SPVM arguments
  int32_t spvm_args_base;
  if (class_method_call) {
    spvm_args_base = 3;
  }
  else {
    spvm_args_base = 2;
  }

  int32_t method_args_length = env->api->method->get_args_length(env->runtime, method);
  int32_t method_required_args_length = env->api->method->get_required_args_length(env->runtime, method);
  
  // Check argument count
  int32_t call_method_args_length = args_length - spvm_args_base;
  
  if (call_method_args_length < method_required_args_length) {
    croak("Too few arguments are passed to the \"%s\" method in the \"%s\" class\n    %s at %s line %d\n", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  else if (call_method_args_length > method_args_length) {
    croak("Too many arguments are passed to the \"%s\" method in the \"%s\" class\n    %s at %s line %d\n", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  int32_t stack_index = 0;
  
  AV* av_refs = NULL;
  
  int32_t has_ref_arg = 0;
  for (int32_t arg_index = 0; arg_index < method_args_length; arg_index++) {
    void* arg = env->api->method->get_arg_by_index(env->runtime, method, arg_index);
    int32_t arg_type_flag = env->api->arg->get_type_flag(env->runtime, arg);
    if (arg_type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF) {
      has_ref_arg = 1;
      av_refs = (AV*)sv_2mortal((SV*)newAV());
      break;
    }
  }
  
  // Arguments conversion
  for (int32_t arg_index = 0; arg_index < method_args_length; arg_index++) {
    
    if (arg_index >= call_method_args_length) {
      break;
    }
    
    int32_t arg_index_nth = arg_index + (spvm_args_base - 2);
    
    // Get value from Perl argument native_stack
    SV* sv_value = ST(spvm_args_base + arg_index);
    
    void* arg = env->api->method->get_arg_by_index(env->runtime, method, arg_index);
    void* arg_basic_type = env->api->arg->get_basic_type(env->runtime, arg);
    int32_t arg_basic_type_id = env->api->basic_type->get_id(env->runtime, arg_basic_type);
    int32_t arg_type_dimension = env->api->arg->get_type_dimension(env->runtime, arg);
    int32_t arg_type_flag = env->api->arg->get_type_flag(env->runtime, arg);
    int32_t arg_basic_type_category = env->api->basic_type->get_category(env->runtime, arg_basic_type);
    
    int32_t arg_type_is_not_ref = !(arg_type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF);
    
    // Argument conversion
    if (arg_type_dimension == 0) {
      if (arg_type_is_not_ref) {
        switch (arg_basic_type_category) {
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
            if (!(SvOK(sv_value) && !SvROK(sv_value))) {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a non-reference scalar\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
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
            sv_value = SPVM_XS_UTIL_new_string(aTHX_ sv_self, sv_value, &sv_error);
            if (SvOK(sv_error)) {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
            }
            void* spvm_string = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_value);
            
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
            else {
              int32_t created_as_string = SvPOK(sv_value) && !SvIsBOOL(sv_value);
              
              if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject")) {
                spvm_value = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_value);
              }
              else if (created_as_string) {
                warn("AAA");
                STRLEN length = -1;
                const char* string = SvPV(sv_value, length);
                spvm_value = env->new_string_no_mortal(env, stack, string, (int32_t)length);
                SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_value, "SPVM::BlessedObject::String");
              }
              else {
                croak("The %dth argument of the \"%s\" method in the \"%s\" class must be an SPVM::BlessedObject object or a string or undef\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
              }
            }
            stack[stack_index].oval = spvm_value;
            
            stack_index++;
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
          {
            int32_t error = 0;
            void* spvm_value;
            if (!SvOK(sv_value)) {
              spvm_value = NULL;
            }
            else if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject::Class")) {
              spvm_value = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_value);
              
              if (!env->isa(env, stack, spvm_value, arg_basic_type, arg_type_dimension)) {
                error = 1;
              }
            }
            else {
              error = 1;
            }
            
            if (error) {
              const char* arg_basic_type_name = env->api->basic_type->get_name(env->runtime, arg_basic_type);
              void* spvm_compile_type_name = env->get_compile_type_name(env, stack, arg_basic_type_name, arg_type_dimension, arg_type_flag);
              const char* compile_type_name = env->get_chars(env, stack, spvm_compile_type_name);
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be an SPVM::BlessedObject::Class object of a \"%s\" assignable type or undef\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, compile_type_name, __func__, FILE_NAME, __LINE__);
            }
            
            stack[stack_index].oval = spvm_value;
            
            stack_index++;
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
          {
            // Argument conversion - multi-numeric
            if (!(SvROK(sv_value) && sv_derived_from(sv_value, "HASH"))) {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a hash reference\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
            }
            
            int32_t arg_basic_type_fields_length = env->api->basic_type->get_fields_length(env->runtime, arg_basic_type);
            void* arg_basic_type_field_first = env->api->basic_type->get_field_by_index(runtime, arg_basic_type, 0);

            void* arg_basic_type_field_basic_type = env->api->field->get_basic_type(env->runtime, arg_basic_type_field_first);
            int32_t arg_basic_type_field_basic_type_id = env->api->basic_type->get_id(env->runtime, arg_basic_type_field_basic_type);
            assert(arg_basic_type_field_basic_type_id >= 0);
            
            HV* hv_value = (HV*)SvRV(sv_value);
            for (int32_t field_index = 0; field_index < arg_basic_type_fields_length; field_index++) {
              void* mulnum_field = env->api->basic_type->get_field_by_index(runtime, arg_basic_type, field_index);
              const char* mulnum_field_name = env->api->field->get_name(env->runtime, mulnum_field);
              SV** sv_field_value_ptr = hv_fetch(hv_value, mulnum_field_name, strlen(mulnum_field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                const char* arg_basic_type_name = env->api->basic_type->get_name(env->runtime, arg_basic_type);
                croak("The hash reference for the %dth argument of the \"%s\" method in the \"%s\" class must have the \"%s\" key for the \"%s\" field of the \"%s\" basic type\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, mulnum_field_name, mulnum_field_name, arg_basic_type_name, __func__, FILE_NAME, __LINE__);

              }
              
              switch (arg_basic_type_field_basic_type_id) {
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
            stack_index += arg_basic_type_fields_length;
            break;
          }
          default: {
            assert(0);
          }
        }
      }
      // Reference argument
      else {
        
        switch (arg_basic_type_category) {
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
            // Argument conversion - numeric reference
            if (!(SvROK(sv_value) && sv_derived_from(sv_value , "SCALAR"))) {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a scalar reference\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
            }
            
            SV* sv_value_deref = SvRV(sv_value);
            
            switch (arg_basic_type_id) {
              // Argument conversion - byte reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                int8_t value = (int8_t)SvIV(sv_value_deref);
                
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(int8_t)));
                int8_t* ref = (int8_t*)SvPV_nolen(sv_ref);
                memcpy((void*)ref, &value, sizeof(int8_t));
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].bref = ref;
                
                break;
              }
              // Argument conversion - short reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                int16_t value = (int16_t)SvIV(sv_value_deref);
                
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(int16_t)));
                int16_t* ref = (int16_t*)SvPV_nolen(sv_ref);
                memcpy((void*)ref, &value, sizeof(int16_t));
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].sref = ref;
                
                break;
              }
              // Argument conversion - int reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                int32_t value = (int32_t)SvIV(sv_value_deref);
                
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(int32_t)));
                int32_t* ref = (int32_t*)SvPV_nolen(sv_ref);
                memcpy((void*)ref, &value, sizeof(int32_t));
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].iref = ref;
                
                break;
              }
              // Argument conversion - long reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                int64_t value = (int64_t)SvIV(sv_value_deref);
                
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(int64_t)));
                int64_t* ref = (int64_t*)SvPV_nolen(sv_ref);
                memcpy((void*)ref, &value, sizeof(int64_t));
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].lref = ref;
                
                break;
              }
              // Argument conversion - float reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                float value = (float)SvNV(sv_value_deref);
                
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(float)));
                float* ref = (float*)SvPV_nolen(sv_ref);
                memcpy((void*)ref, &value, sizeof(float));
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].fref = ref;
                
                break;
              }
              // Argument conversion - double reference
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                double value = (double)SvNV(sv_value_deref);
                
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(double)));
                double* ref = (double*)SvPV_nolen(sv_ref);
                memcpy((void*)ref, &value, sizeof(double));
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].dref = ref;
                
                break;
              }
            }
            
            stack_index++;
            
            break;
          }
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
          {
            // Argument conversion - multi-numeric reference
            if (!(SvROK(sv_value) && SvROK(SvRV(sv_value)) && sv_derived_from(SvRV(sv_value) , "HASH"))) {
              croak("The %dth argument of the \"%s\" method in the \"%s\" class must be a reference to a hash reference\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
            }
            
            SV* hv_value_ref = SvRV(sv_value);
            
            HV* hv_value = (HV*)SvRV(hv_value_ref);
            int32_t arg_basic_type_fields_length = env->api->basic_type->get_fields_length(env->runtime, arg_basic_type);
            void* arg_basic_type_field_first = env->api->basic_type->get_field_by_index(runtime, arg_basic_type, 0);
            void* arg_basic_type_field_basic_type = env->api->field->get_basic_type(env->runtime, arg_basic_type_field_first);
            int32_t arg_basic_type_field_basic_type_id = env->api->basic_type->get_id(env->runtime, arg_basic_type_field_basic_type);
            assert(arg_basic_type_field_basic_type_id >= 0);

            switch(arg_basic_type_field_basic_type_id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(int8_t) * arg_basic_type_fields_length));
                int8_t* ref = (int8_t*)SvPV_nolen(sv_ref);
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].bref = ref;
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(int16_t) * arg_basic_type_fields_length));
                int16_t* ref = (int16_t*)SvPV_nolen(sv_ref);
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].sref = ref;
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(int32_t) * arg_basic_type_fields_length));
                int32_t* ref = (int32_t*)SvPV_nolen(sv_ref);
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].iref = ref;
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(int64_t) * arg_basic_type_fields_length));
                int64_t* ref = (int64_t*)SvPV_nolen(sv_ref);
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].lref = ref;
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(float) * arg_basic_type_fields_length));
                float* ref = (float*)SvPV_nolen(sv_ref);
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].fref = ref;
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                SV* sv_ref = sv_2mortal(newSVpv("", sizeof(double) * arg_basic_type_fields_length));
                double* ref = (double*)SvPV_nolen(sv_ref);
                av_store(av_refs, arg_index,SvREFCNT_inc(sv_ref));
                stack[stack_index].dref = ref;
                
                break;
              }
              default: {
                assert(0);
              }
            }
            
            for (int32_t field_index = 0; field_index < arg_basic_type_fields_length; field_index++) {
              void* mulnum_field = env->api->basic_type->get_field_by_index(runtime, arg_basic_type, field_index);
              const char* mulnum_field_name = env->api->field->get_name(env->runtime, mulnum_field);
              SV** sv_field_value_ptr = hv_fetch(hv_value, mulnum_field_name, strlen(mulnum_field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                const char* arg_basic_type_name = env->api->basic_type->get_name(env->runtime, arg_basic_type);
                croak("The hash reference for the %dth argument of the \"%s\" method in the \"%s\" class must have the \"%s\" key for the \"%s\" field of the \"%s\" basic type\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, mulnum_field_name, mulnum_field_name, arg_basic_type_name, __func__, FILE_NAME, __LINE__);
              }
              switch(arg_basic_type_field_basic_type_id) {
                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                  // Argument conversion - multi-numeric byte reference
                  int8_t value = (int8_t)SvIV(sv_field_value);
                  
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  int8_t* ref = (int8_t*)SvPV_nolen(sv_ref);
                  memcpy((void*)(ref + field_index), &value, sizeof(int8_t));
                  
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                  // Argument conversion - multi-numeric short reference
                  int16_t value = (int16_t)SvIV(sv_field_value);
                  
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  int16_t* ref = (int16_t*)SvPV_nolen(sv_ref);
                  memcpy((void*)(ref + field_index), &value, sizeof(int16_t));
                  
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                  // Argument conversion - multi-numeric int reference
                  int32_t value = (int32_t)SvIV(sv_field_value);
                  
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  int32_t* ref = (int32_t*)SvPV_nolen(sv_ref);
                  memcpy((void*)(ref + field_index), &value, sizeof(int32_t));
                  
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                  // Argument conversion - multi-numeric long reference
                  int64_t value = (int64_t)SvIV(sv_field_value);
                  
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  int64_t* ref = (int64_t*)SvPV_nolen(sv_ref);
                  memcpy((void*)(ref + field_index), &value, sizeof(int64_t));
                  
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                  // Argument conversion - multi-numeric float reference
                  float value = (float)SvNV(sv_field_value);
                  
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  float* ref = (float*)SvPV_nolen(sv_ref);
                  memcpy((void*)(ref + field_index), &value, sizeof(float));
                  
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                  // Argument conversion - multi-numeric double reference
                  double value = (double)SvNV(sv_field_value);
                  
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  double* ref = (double*)SvPV_nolen(sv_ref);
                  memcpy((void*)(ref + field_index), &value, sizeof(double));
                  
                  break;
                }
                default: {
                  assert(0);
                }
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
    }
    else if (arg_type_dimension == 1) {
      switch (arg_basic_type_category) {
        // Argument conversion - numeric array
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
          SV* sv_error = &PL_sv_undef;
          switch (arg_basic_type_id) {
            // Argument conversion - byte array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
              sv_value = SPVM_XS_UTIL_new_byte_array(aTHX_ sv_self, sv_value, &sv_error);
              break;
            }
            // Argument conversion - short array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
              sv_value = SPVM_XS_UTIL_new_short_array(aTHX_ sv_self, sv_value, &sv_error);
              break;
            }
            // Argument conversion - int array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
              sv_value = SPVM_XS_UTIL_new_int_array(aTHX_ sv_self, sv_value, &sv_error);
              break;
            }
            // Argument conversion - long array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
              sv_value = SPVM_XS_UTIL_new_long_array(aTHX_ sv_self, sv_value, &sv_error);
              break;
            }
            // Argument conversion - float array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
              sv_value = SPVM_XS_UTIL_new_float_array(aTHX_ sv_self, sv_value, &sv_error);
              break;
            }
            // Argument conversion - double array
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
              sv_value = SPVM_XS_UTIL_new_double_array(aTHX_ sv_self, sv_value, &sv_error);
              break;
            }
            default: {
              assert(0);
            }
          }
          
          if (SvOK(sv_error)) {
            croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
          }
          
          void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_value);
          
          stack[stack_index].oval = spvm_array;
          
          stack_index++;
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
        {
          SV* sv_error = &PL_sv_undef;
          sv_value = SPVM_XS_UTIL_new_mulnum_array(aTHX_ sv_self, arg_basic_type, sv_value, &sv_error);
          
          if (SvOK(sv_error)) {
            croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
          }
          
          void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_value);
          
          stack[stack_index].oval = spvm_array;
            
          stack_index++;
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING: {
          SV* sv_error = &PL_sv_undef;
          
          sv_value = SPVM_XS_UTIL_new_string_array(aTHX_ sv_self, sv_value, &sv_error);
          
          if (SvOK(sv_error)) {
            croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
          }
          
          void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_value);
          
          stack[stack_index].oval = spvm_array;
          
          stack_index++;
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
        {
          SV* sv_error = &PL_sv_undef;
          
          sv_value = SPVM_XS_UTIL_new_object_array(aTHX_ sv_self, arg_basic_type, sv_value, &sv_error);
          
          if (SvOK(sv_error)) {
            croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
          }
          
          void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_value);
          
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
      
      // Argument conversion - multi-type_dimensional array
      SV* sv_error = &PL_sv_undef;
      
      sv_value = SPVM_XS_UTIL_new_muldim_array(aTHX_ sv_self, arg_basic_type, arg_type_dimension, sv_value, &sv_error);
      
      if (SvOK(sv_error)) {
        croak("The %dth argument of the \"%s\" method in the \"%s\" class%s\n    %s at %s line %d\n", arg_index_nth, method_name, basic_type_name, SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
      }
      
      void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_value);
      
      stack[stack_index].oval = spvm_array;
      
      stack_index++;
      break;
    }
    else {
      assert(0);
    }
  }
  
  // Return
  void* method_return_basic_type = env->api->method->get_return_basic_type(env->runtime, method);
  int32_t method_return_basic_type_id = env->api->basic_type->get_id(env->runtime, method_return_basic_type);
  int32_t method_return_type_dimension = env->api->method->get_return_type_dimension(env->runtime, method);
  
  int32_t method_return_basic_type_category = env->api->basic_type->get_category(env->runtime, method_return_basic_type);
  
  // Call method
  int32_t call_method_args_width = stack_index;
  int32_t error_id = env->call_method_no_mortal(env, stack, method, call_method_args_width);
  
  if (error_id) {
    if (SvOK(sv_error_ret)) {
      HV* hv_error_ret = (HV*)SvRV(sv_error_ret);
      SV* sv_error_id = sv_2mortal(newSViv(error_id));
      (void)hv_store(hv_error_ret, "id", strlen("id"), SvREFCNT_inc(sv_error_id), 0);
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
        int32_t method_return_basic_type_fields_length = env->api->basic_type->get_fields_length(env->runtime, method_return_basic_type);
        void* method_return_mulnum_field = env->api->basic_type->get_field_by_index(runtime, method_return_basic_type, 0);
        void* method_return_mulnum_field_basic_type = env->api->field->get_basic_type(env->runtime, method_return_mulnum_field);
        int32_t method_return_mulnum_field_basic_type_id = env->api->basic_type->get_id(env->runtime, method_return_mulnum_field_basic_type);
        
        HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
        for (int32_t field_index = 0; field_index < method_return_basic_type_fields_length; field_index++) {
          SV* sv_field_value = NULL;
          switch (method_return_mulnum_field_basic_type_id) {
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
          
          void* mulnum_field = env->api->basic_type->get_field_by_index(runtime, method_return_basic_type, field_index);
          const char* mulnum_field_name = env->api->field->get_name(env->runtime, mulnum_field);
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
          sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, return_value, "SPVM::BlessedObject::String");
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
          const char* return_value_basic_type_name = env->get_object_basic_type_name(env, stack, return_value);
          int32_t return_value_type_dimension = env->get_object_type_dimension(env, stack, return_value);
          if (return_value_type_dimension > 0) {
            sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, return_value, "SPVM::BlessedObject::Array");
          }
          else {
            if (strcmp(return_value_basic_type_name, "string") == 0) {
              sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, return_value, "SPVM::BlessedObject::String");
            }
            else {
              sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, return_value, "SPVM::BlessedObject::Class");
            }
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
        void* return_value = (void*)stack[0].oval;
        sv_return_value = NULL;
        if (return_value != NULL) {
          sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, return_value, "SPVM::BlessedObject::Class");
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
      sv_return_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, return_value, "SPVM::BlessedObject::Array");
    }
    else {
      sv_return_value = &PL_sv_undef;
    }
  }
  
  // Restore reference
  if (has_ref_arg) {
    for (int32_t arg_index = 0; arg_index < method_args_length; arg_index++) {
      SV* sv_value = ST(spvm_args_base + arg_index);
      
      // Argument type
      void* arg = env->api->method->get_arg_by_index(env->runtime, method, arg_index);
      void* arg_basic_type = env->api->arg->get_basic_type(env->runtime, arg);
      int32_t arg_basic_type_id = env->api->basic_type->get_id(env->runtime, arg_basic_type);
      int32_t arg_type_dimension = env->api->arg->get_type_dimension(env->runtime, arg);
      int32_t arg_type_flag = env->api->arg->get_type_flag(env->runtime, arg);
      int32_t arg_basic_type_category = env->api->basic_type->get_category(env->runtime, arg_basic_type);
      
      // Restore reference - numeric
      if (arg_type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF) {
        switch (arg_basic_type_category) {
          case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
            switch (arg_basic_type_id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE : {
                // Restore reference - byte
                SV* sv_value_deref = SvRV(sv_value);
                SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                int8_t* ref = (int8_t*)SvPV_nolen(sv_ref);
                sv_setiv(sv_value_deref, *ref);
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT : {
                // Restore reference - short
                SV* sv_value_deref = SvRV(sv_value);
                SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                int16_t* ref = (int16_t*)SvPV_nolen(sv_ref);
                sv_setiv(sv_value_deref, *ref);
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT : {
                // Restore reference - int
                SV* sv_value_deref = SvRV(sv_value);
                SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                int32_t* ref = (int32_t*)SvPV_nolen(sv_ref);
                sv_setiv(sv_value_deref, *ref);
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG : {
                // Restore reference - long
                SV* sv_value_deref = SvRV(sv_value);
                SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                int64_t* ref = (int64_t*)SvPV_nolen(sv_ref);
                sv_setiv(sv_value_deref, *ref);
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT : {
                // Restore reference - float
                SV* sv_value_deref = SvRV(sv_value);
                SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                float* ref = (float*)SvPV_nolen(sv_ref);
                sv_setnv(sv_value_deref, *ref);
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE : {
                // Restore reference - double
                SV* sv_value_deref = SvRV(sv_value);
                SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                double* ref = (double*)SvPV_nolen(sv_ref);
                sv_setnv(sv_value_deref, *ref);
                
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
            int32_t arg_basic_type_fields_length = env->api->basic_type->get_fields_length(env->runtime, arg_basic_type);
            void* arg_basic_type_field_first = env->api->basic_type->get_field_by_index(runtime, arg_basic_type, 0);
            void* arg_basic_type_field_basic_type = env->api->field->get_basic_type(env->runtime, arg_basic_type_field_first);
            int32_t arg_basic_type_field_basic_type_id = env->api->basic_type->get_id(env->runtime, arg_basic_type_field_basic_type);
            for (int32_t field_index = 0; field_index < arg_basic_type_fields_length; field_index++) {
              void* mulnum_field = env->api->basic_type->get_field_by_index(runtime, arg_basic_type, field_index);
              const char* mulnum_field_name = env->api->field->get_name(env->runtime, mulnum_field);
              SV* sv_field_value;
              switch (arg_basic_type_field_basic_type_id) {
                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                  // Restore reference value - multi-numeric byte
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  int8_t* ref = (int8_t*)SvPV_nolen(sv_ref);
                  sv_field_value = sv_2mortal(newSViv(*(ref + field_index)));
                  
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                  // Restore reference value - multi-numeric short
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  int16_t* ref = (int16_t*)SvPV_nolen(sv_ref);
                  sv_field_value = sv_2mortal(newSViv(*(ref + field_index)));
                  
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                  // Restore reference value - multi-numeric int
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  int32_t* ref = (int32_t*)SvPV_nolen(sv_ref);
                  sv_field_value = sv_2mortal(newSViv(*(ref + field_index)));
                  
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                  // Restore reference value - multi-numeric long
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  int64_t* ref = (int64_t*)SvPV_nolen(sv_ref);
                  sv_field_value = sv_2mortal(newSViv(*(ref + field_index)));
                  
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                  // Restore reference value - multi-numeric float
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  float* ref = (float*)SvPV_nolen(sv_ref);
                  sv_field_value = sv_2mortal(newSVnv(*(ref + field_index)));
                  
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                  // Restore reference value - multi-numeric double
                  SV** sv_ref_ptr = av_fetch(av_refs, arg_index, 0);
                  SV* sv_ref = sv_ref_ptr ? *sv_ref_ptr : &PL_sv_undef;
                  double* ref = (double*)SvPV_nolen(sv_ref);
                  sv_field_value = sv_2mortal(newSVnv(*(ref + field_index)));
                  
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
  
  // Array must be an SPVM::BlessedObject or SPVM::BlessedObject
  if (SvOK(sv_object)) {
    if (!(SvROK(sv_object) && sv_derived_from(sv_object, "SPVM::BlessedObject"))) {
      croak("$object must be an SPVM::BlessedObject object\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
    }
  }
  
  // Get object
  void* object = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_object);
  
  void* spvm_dump = env->dump_no_mortal(env, stack, object);
  
  const char* dump = env->get_chars(env, stack, spvm_dump);
  int32_t dump_length = env->length(env, stack, spvm_dump);
  
  SV* sv_dump = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_dump, "SPVM::BlessedObject::String");
  
  XPUSHs(sv_dump);
  XSRETURN(1);
}

SV*
_xs_new_string(...)
  PPCODE:
{
  
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
  sv_string = SPVM_XS_UTIL_new_string(aTHX_ sv_self, sv_string, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$string%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

SV*
_xs_new_address_object(...)
  PPCODE:
{
  
  int32_t error_id = 0;
  
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
  sv_address = SPVM_XS_UTIL_new_address_object(aTHX_ sv_self, sv_address, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$address%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_address);
  XSRETURN(1);
}

SV*
_xs_new_byte_array(...)
  PPCODE:
{
  
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
  sv_array = SPVM_XS_UTIL_new_byte_array(aTHX_ sv_self, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_byte_array_unsigned(...)
  PPCODE:
{
  
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
  sv_array = SPVM_XS_UTIL_new_byte_array_unsigned(aTHX_ sv_self, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_byte_array_len(...)
  PPCODE:
{
  
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
    croak("$length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_array = env->new_byte_array_no_mortal(env, stack, length);
  
  SV* sv_byte_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_byte_array);
  XSRETURN(1);
}

SV*
_xs_new_byte_array_from_bin(...)
  PPCODE:
{
  
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
  
  if (!(SvOK(sv_binary) && !SvROK(sv_binary))) {
    croak("$binary must be a defined non-reference scalar\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  STRLEN length = -1;
  int8_t* binary = (int8_t*)SvPV(sv_binary, length);
  
  // New array
  void* spvm_array = env->new_byte_array_no_mortal(env, stack, (int32_t)length);
  
  int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
  memcpy(elems, binary, length);
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_short_array(...)
  PPCODE:
{
  
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
  sv_array = SPVM_XS_UTIL_new_short_array(aTHX_ sv_self, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_short_array_unsigned(...)
  PPCODE:
{
  
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
  sv_array = SPVM_XS_UTIL_new_short_array_unsigned(aTHX_ sv_self, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_short_array_len(...)
  PPCODE:
{
  
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
    croak("$length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_array = env->new_short_array_no_mortal(env, stack, length);
  
  SV* sv_short_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_short_array);
  XSRETURN(1);
}

SV*
_xs_new_short_array_from_bin(...)
  PPCODE:
{
  
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
  
  if (!(SvOK(sv_binary) && !SvROK(sv_binary))) {
    croak("$binary must be a defined non-reference scalar\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  STRLEN binary_length = -1;
  int16_t* binary = (int16_t*)SvPV(sv_binary, binary_length);
  
  if (!(binary_length % 2 == 0)) {
    croak("The length of $binary must be divisible by 2\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t array_length = binary_length / sizeof(int16_t);
  
  // New array
  void* spvm_array = env->new_short_array_no_mortal(env, stack, array_length);

  int16_t* elems = env->get_elems_short(env, stack, spvm_array);
  memcpy(elems, binary, array_length * sizeof(int16_t));
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_int_array(...)
  PPCODE:
{
  
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
  sv_array = SPVM_XS_UTIL_new_int_array(aTHX_ sv_self, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_int_array_unsigned(...)
  PPCODE:
{
  
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
  sv_array = SPVM_XS_UTIL_new_int_array_unsigned(aTHX_ sv_self, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_int_array_len(...)
  PPCODE:
{
  
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
    croak("$length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_array = env->new_int_array_no_mortal(env, stack, length);
  
  SV* sv_int_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_int_array);
  XSRETURN(1);
}

SV*
_xs_new_int_array_from_bin(...)
  PPCODE:
{
  
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
  
  if (!(SvOK(sv_binary) && !SvROK(sv_binary))) {
    croak("$binary must be a defined non-reference scalar\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  STRLEN binary_length = -1;
  int32_t* binary = (int32_t*)SvPV(sv_binary, binary_length);
  
  if (!(binary_length % 4 == 0)) {
    croak("The length of $binary must be divisible by 4\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t array_length = binary_length / sizeof(int32_t);
  
  void* spvm_array = env->new_int_array_no_mortal(env, stack, array_length);
  
  int32_t* elems = env->get_elems_int(env, stack, spvm_array);
  memcpy(elems, binary, array_length * sizeof(int32_t));
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_long_array(...)
  PPCODE:
{
  
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
  sv_array = SPVM_XS_UTIL_new_long_array(aTHX_ sv_self, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_long_array_unsigned(...)
  PPCODE:
{
  
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
  sv_array = SPVM_XS_UTIL_new_long_array_unsigned(aTHX_ sv_self, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_long_array_len(...)
  PPCODE:
{
  
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
    croak("$length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_array = env->new_long_array_no_mortal(env, stack, length);
  
  SV* sv_long_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_long_array);
  XSRETURN(1);
}

SV*
_xs_new_long_array_from_bin(...)
  PPCODE:
{
  
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
  
  if (!(SvOK(sv_binary) && !SvROK(sv_binary))) {
    croak("$binary must be a defined non-reference scalar\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  STRLEN binary_length = -1;
  int64_t* binary = (int64_t*)SvPV(sv_binary, binary_length);
  
  if (!(binary_length % 8 == 0)) {
    croak("The length of $binary must be divisible by 8\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t array_length = binary_length / sizeof(int64_t);
  
  // New array
  void* spvm_array = env->new_long_array_no_mortal(env, stack, array_length);
  
  int64_t* elems = env->get_elems_long(env, stack, spvm_array);
  memcpy(elems, binary, array_length * sizeof(int64_t));
    
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_float_array(...)
  PPCODE:
{
  
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
  sv_array = SPVM_XS_UTIL_new_float_array(aTHX_ sv_self, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_float_array_len(...)
  PPCODE:
{
  
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
    croak("$length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_array = env->new_float_array_no_mortal(env, stack, length);
  
  SV* sv_float_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_float_array);
  XSRETURN(1);
}

SV*
_xs_new_float_array_from_bin(...)
  PPCODE:
{
  
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
  
  if (!(SvOK(sv_binary) && !SvROK(sv_binary))) {
    croak("$binary must be a defined non-reference scalar\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  STRLEN binary_length = -1;
  float* binary = (float*)SvPV(sv_binary, binary_length);
  
  if (!(binary_length % 4 == 0)) {
    croak("The length of $binary must be divisible by 4\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t array_length = binary_length / sizeof(float);
  
  // New array
  void* spvm_array = env->new_float_array_no_mortal(env, stack, array_length);
  
  float* elems = env->get_elems_float(env, stack, spvm_array);
  memcpy(elems, binary, array_length * sizeof(float));
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_double_array(...)
  PPCODE:
{
  
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
  sv_array = SPVM_XS_UTIL_new_double_array(aTHX_ sv_self, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_double_array_len(...)
  PPCODE:
{
  
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
    croak("$length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_array = env->new_double_array_no_mortal(env, stack, length);
  
  SV* sv_double_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_double_array);
  XSRETURN(1);
}

SV*
_xs_new_double_array_from_bin(...)
  PPCODE:
{
  
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
  
  if (!(SvOK(sv_binary) && !SvROK(sv_binary))) {
    croak("$binary must be a defined non-reference scalar\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  STRLEN binary_length = -1;
  double* binary = (double*)SvPV(sv_binary, binary_length);
  
  if (!(binary_length % 8 == 0)) {
    croak("The length of $binary must be divisible by 8\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t array_length = binary_length / sizeof(double);
  
  void* spvm_array = env->new_double_array_no_mortal(env, stack, array_length);
  
  double* elems = env->get_elems_double(env, stack, spvm_array);
  memcpy(elems, binary, array_length * sizeof(double));
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_string_array(...)
  PPCODE:
{
  
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
  sv_array = SPVM_XS_UTIL_new_string_array(aTHX_ sv_self, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_string_array_len(...)
  PPCODE:
{
  
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
    croak("$length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_array = env->new_string_array_no_mortal(env, stack, length);
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_object_array(...)
  PPCODE:
{
  
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
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  int32_t elem_type_dimension = 0;
  int32_t is_object_array = env->api->type->is_object_type(env->runtime, basic_type, elem_type_dimension, 0);
  if (!is_object_array) {
    croak("$type_name must be an object array type\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_object_array(aTHX_ sv_self, basic_type, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_object_array_len(...)
  PPCODE:
{
  
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
    croak("$length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  int32_t elem_type_dimension = 0;
  int32_t is_object_array = env->api->type->is_object_type(env->runtime, basic_type, elem_type_dimension, 0);
  if (!is_object_array) {
    croak("$type_name must be an object array type\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_array = env->new_object_array_no_mortal(env, stack, basic_type, length);
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_mulnum_array(...)
  PPCODE:
{
  
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

  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  int32_t elem_type_dimension = 0;
  int32_t basic_type_category = env->api->basic_type->get_category(env->runtime, basic_type);
  int32_t is_mulnum_array = basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM;
  if (!is_mulnum_array) {
    croak("$type_name must be a multi-numeric array type\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_mulnum_array(aTHX_ sv_self, basic_type, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_mulnum_array_len(...)
  PPCODE:
{
  
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
    croak("$length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  int32_t elem_type_dimension = 0;
  int32_t basic_type_category = env->api->basic_type->get_category(env->runtime, basic_type);
  int32_t is_mulnum_array = basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM;
  if (!is_mulnum_array) {
    croak("$type_name must be a multi-numeric array type\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_array = env->new_mulnum_array_no_mortal(env, stack, basic_type, length);
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_mulnum_array_from_bin(...)
  PPCODE:
{
  
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
  
  if (!(SvOK(sv_binary) && !SvROK(sv_binary))) {
    croak("$binary must be a defined non-reference scalar\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  STRLEN binary_length = -1;
  void* binary = (void*)SvPV(sv_binary, binary_length);
  
  // Runtime
  void* runtime = env->runtime;
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  int32_t basic_type_id = env->api->basic_type->get_id(env->runtime, basic_type);
  
  int32_t elem_type_dimension = 0;
  int32_t basic_type_category = env->api->basic_type->get_category(env->runtime, basic_type);
  int32_t is_mulnum_array = basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM;
  if (!is_mulnum_array) {
    croak("$type_name must be a multi-numeric array type\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t basic_type_fields_length = env->api->basic_type->get_fields_length(env->runtime, basic_type);
  
  int32_t fields_length = basic_type_fields_length;
  
  int32_t field_size;
  void* mulnum_field = env->api->basic_type->get_field_by_index(runtime, basic_type, 0);
  void* mulnum_field_basic_type = env->api->field->get_basic_type(env->runtime, mulnum_field);
  int32_t mulnum_field_basic_type_id = env->api->basic_type->get_id(env->runtime, mulnum_field_basic_type);
  switch (mulnum_field_basic_type_id) {
    case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
      field_size = 1;
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
      field_size = 2;
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
      field_size = 4;
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
      field_size = 8;
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
      field_size = 4;
      break;
    }
    case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
      field_size = 8;
      break;
    }
    default: {
      assert(0);
    }
  }
  
  if (binary_length % (field_size * fields_length) != 0) {
    croak("The length of $binary must be divisible by %d * %d\n    %s at %s line %d", field_size, fields_length, __func__, FILE_NAME, __LINE__);
  }
  
  int32_t array_length = binary_length / fields_length / field_size;

  void* spvm_array = env->new_mulnum_array_no_mortal(env, stack, basic_type, array_length);

  int32_t type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
  
  int32_t copy_length = fields_length * array_length * field_size;
  switch (mulnum_field_basic_type_id) {
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
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_muldim_array(...)
  PPCODE:
{
  
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
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  int32_t type_dimension = (int32_t)SvIV(sv_type_dimension);
  
  SV* sv_error = &PL_sv_undef;
  sv_array = SPVM_XS_UTIL_new_muldim_array(aTHX_ sv_self, basic_type, type_dimension, sv_array, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$array%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_new_muldim_array_len(...)
  PPCODE:
{
  
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
  SV* sv_length = ST(3);
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  int32_t type_dimension = (int32_t)SvIV(sv_type_dimension);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("$length must be greater than or equal to 0\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_array = env->new_muldim_array_no_mortal(env, stack, basic_type, type_dimension, length);
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, spvm_array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_xs_get_exception(...)
  PPCODE:
{
  
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
    sv_exception = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_self, str_exception, "SPVM::BlessedObject::String");
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
  sv_message = SPVM_XS_UTIL_new_string(aTHX_ sv_self, sv_message, &sv_error);
  
  if (SvOK(sv_error)) {
    croak("$message%s\n    %s at %s line %d\n", SvPV_nolen(sv_error), __func__, FILE_NAME, __LINE__);
  }
  
  void* spvm_message = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_message);
  
  env->set_exception(env, stack, spvm_message);
  
  XSRETURN(0);
}

SV*
_xs_get_memory_blocks_count(...)
  PPCODE:
{
  
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
  
  int32_t memory_blocks_count = env->get_memory_blocks_count(env, stack);
  SV* sv_memory_blocks_count = sv_2mortal(newSViv(memory_blocks_count));
  
  XPUSHs(sv_memory_blocks_count);
  XSRETURN(1);
}

MODULE = SPVM::BlessedObject		PACKAGE = SPVM::BlessedObject

SV*
DESTROY(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  SV** sv_spvm_object_ptr = hv_fetch(hv_self, "spvm_object", strlen("spvm_object"), 0);
  SV* sv_spvm_object = sv_spvm_object_ptr ? *sv_spvm_object_ptr : &PL_sv_undef;
  void** spvm_object_ref = (void**)SvPV_nolen(sv_spvm_object);
  
  SV** sv_api_ptr = hv_fetch(hv_self, "__api", strlen("__api"), 0);
  SV* sv_api = sv_api_ptr ? *sv_api_ptr : &PL_sv_undef;
  HV* hv_api = (HV*)SvRV(sv_api);
  
  SV** sv_env_ptr = hv_fetch(hv_api, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_env(aTHX_ sv_env);
  
  // Stack
  SV** sv_stack_ptr = hv_fetch(hv_api, "stack", strlen("stack"), 0);
  SV* sv_stack = sv_stack_ptr ? *sv_stack_ptr : &PL_sv_undef;
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_stack(aTHX_ sv_stack);
  
  env->assign_object(env, stack, spvm_object_ref, NULL);
  
  XSRETURN(0);
}

SV*
_xs___get_type_name(...)
  PPCODE:
{
  
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
  
  assert(SvROK(sv_self) && sv_derived_from(sv_self, "SPVM::BlessedObject"));
  
  // Get object
  void* spvm_object = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_self);
  
  void* spvm_type_name = env->get_type_name_no_mortal(env, stack, spvm_object);
  const char* type_name = env->get_chars(env, stack, spvm_type_name);
  int32_t type_name_length = env->length(env, stack, spvm_type_name);
  
  SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, spvm_type_name, "SPVM::BlessedObject::String");
  
  SV* sv_type_name = sv_2mortal(newSVpv(type_name, type_name_length));
  
  XPUSHs(sv_type_name);
  XSRETURN(1);
}

MODULE = SPVM::BlessedObject::String		PACKAGE = SPVM::BlessedObject::String

SV*
_xs_to_bin(...)
  PPCODE:
{
  
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
  void* spvm_string = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_self);
  
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
  void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_self);
  
  int32_t length = env->length(env, stack, spvm_array);
  
  SV* sv_length = sv_2mortal(newSViv(length));
  
  XPUSHs(sv_length);
  XSRETURN(1);
}

SV*
_xs_to_elems(...)
  PPCODE:
{
  
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
  void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_self);
  
  int32_t length = env->length(env, stack, spvm_array);
  
  const char* basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  int32_t basic_type_id = env->api->basic_type->get_id(env->runtime, basic_type);
  int32_t type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
  int32_t is_array_type = type_dimension > 0;
  
  assert(is_array_type);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  if (is_array_type) {
    int32_t elem_type_dimension = type_dimension - 1;
    
    int32_t array_is_mulnum_array = env->is_mulnum_array(env, stack, spvm_array);
    int32_t array_is_object_array = env->is_object_array(env, stack, spvm_array);
    
    if (array_is_mulnum_array) {
      
      for (int32_t index = 0; index < length; index++) {
        
        int32_t basic_type_fields_length = env->api->basic_type->get_fields_length(env->runtime, basic_type);
        void* elems = (void*)env->get_elems_int(env, stack, spvm_array);
        
        HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
        int32_t fields_length = basic_type_fields_length;
        for (int32_t field_index = 0; field_index < basic_type_fields_length; field_index++) {
          void* mulnum_field = env->api->basic_type->get_field_by_index(runtime, basic_type, field_index);
          const char* mulnum_field_name = env->api->field->get_name(env->runtime, mulnum_field);
          
          SV* sv_field_value;
          void* mulnum_field_basic_type = env->api->field->get_basic_type(env->runtime, mulnum_field);
          int32_t mulnum_field_basic_type_id = env->api->basic_type->get_id(env->runtime, mulnum_field_basic_type);
          switch (mulnum_field_basic_type_id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
              int8_t field_value = ((int8_t*)elems)[(fields_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
              int16_t field_value = ((int16_t*)elems)[(fields_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
              int32_t field_value = ((int32_t*)elems)[(fields_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
              int64_t field_value = ((int64_t*)elems)[(fields_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
              float field_value = ((float*)elems)[(fields_length * index) + field_index];
              sv_field_value = sv_2mortal(newSVnv(field_value));
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
              double field_value = ((double*)elems)[(fields_length * index) + field_index];
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
            sv_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, object, "SPVM::BlessedObject::String");
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
            int32_t elem_type_is_array_type = elem_type_dimension > 0;
            SV* sv_value;
            if (elem_type_is_array_type) {
              sv_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, value, "SPVM::BlessedObject::Array");
            }
            else {
              sv_value = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, value, "SPVM::BlessedObject::Class");
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
  void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_self);
  
  int32_t length = env->length(env, stack, spvm_array);
  
  const char* basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  int32_t basic_type_id = env->api->basic_type->get_id(env->runtime, basic_type);
  int32_t type_dimension = env->get_object_type_dimension(env, stack, spvm_array);
  int32_t is_array_type = type_dimension > 0;
  assert(is_array_type);
  
  SV* sv_binary;
  if (is_array_type) {
    int32_t elem_type_dimension = type_dimension - 1;
    
    int32_t array_is_mulnum_array = env->is_mulnum_array(env, stack, spvm_array);
    int32_t array_is_object_array = env->is_object_array(env, stack, spvm_array);
    
    if (array_is_mulnum_array) {
      int32_t basic_type_fields_length = env->api->basic_type->get_fields_length(env->runtime, basic_type);
      
      int32_t fields_length = basic_type_fields_length;
      
      void* mulnum_field = env->api->basic_type->get_field_by_index(runtime, basic_type, 0);
      void* mulnum_field_basic_type = env->api->field->get_basic_type(env->runtime, mulnum_field);
      int32_t mulnum_field_basic_type_id = env->api->basic_type->get_id(env->runtime, mulnum_field_basic_type);
      switch (mulnum_field_basic_type_id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, fields_length * length));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, fields_length * length * 2));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          int32_t* elems = env->get_elems_int(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, fields_length * length * 4));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, fields_length * length * 8));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          float* elems = env->get_elems_float(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, fields_length * length * 4));
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, stack, spvm_array);
          
          sv_binary = sv_2mortal(newSVpvn((char*)elems, fields_length * length * 8));
          break;
        }
        default: {
          assert(0);
        }
      }
    }
    else if (array_is_object_array) {
      croak("The object array cannnot be converted to a binary\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
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
  void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_self);
  
  // Length
  int32_t length = env->length(env, stack, spvm_array);
  
  // Check range
  if (!(index >= 0 && index < length)) {
    croak("$index must be greatr than or equal to 0 and less than the length of the array\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  int32_t basic_type_id = env->api->basic_type->get_id(env->runtime, basic_type);
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
        void* elem = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_elem);
        
        env->set_elem_object(env, stack, spvm_array, index, elem);
      }
    }
  }
  else if (type_dimension > 1) {
    
    // Get object
    void* elem = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_elem);
    
    int32_t elem_isa = env->elem_isa(env, stack, spvm_array, elem);
    if (!elem_isa) {
      croak("$elem must be assigned to the element of the array\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
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
  void* spvm_array = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_self);
  
  // Length
  int32_t length = env->length(env, stack, spvm_array);
  
  // Check range
  if (!(index >= 0 && index < length)) {
    croak("$index must be greater than or equal to 0 and less than the length of the array\n    %s at %s line %d\n", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_object_basic_type_name(env, stack, spvm_array);
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    croak("The \"%s\" basic type is not found\n    %s at %s line %d\n", basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  int32_t basic_type_id = env->api->basic_type->get_id(env->runtime, basic_type);
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
      sv_elem = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, elem, "SPVM::BlessedObject::Class");
    }
    else if (elem_type_dimension > 0) {
      sv_elem = SPVM_XS_UTIL_new_sv_blessed_object(aTHX_ sv_api, elem, "SPVM::BlessedObject::Array");
    }
  }
  
  XPUSHs(sv_elem);
  XSRETURN(1);
}

MODULE = SPVM::BlessedObject::Class		PACKAGE = SPVM::BlessedObject::Class

SV*
get_basic_type_name(...)
  PPCODE:
{
  
  SV* sv_object = ST(0);
  HV* hv_object = (HV*)SvRV(sv_object);
  
  assert(SvOK(sv_object));
  
  // Get object
  void* object = SPVM_XS_UTIL_get_spvm_object(aTHX_ sv_object);

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
  
  const char* basic_type_name = env->get_object_basic_type_name(env, stack, object);
  
  SV* sv_basic_type_name = sv_2mortal(newSVpv(basic_type_name, 0));
  
  XPUSHs(sv_basic_type_name);
  XSRETURN(1);
}


MODULE = SPVM::Builder::Compiler		PACKAGE = SPVM::Builder::Compiler

SV*
DESTROY(...)
  PPCODE:
{
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  SV** sv_env_api_ptr = hv_fetch(hv_self, "env_api", strlen("env_api"), 0);
  SV* sv_env_api = sv_env_api_ptr ? *sv_env_api_ptr : &PL_sv_undef;
  SPVM_ENV* env_api = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env_api);
  
  void* compiler = SPVM_XS_UTIL_get_pointer(aTHX_ sv_self);
  
  // Free compiler
  env_api->api->compiler->free_instance(compiler);
  
  XSRETURN(0);
}

SV*
create_native_compiler(...)
  PPCODE:
{
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  SV** sv_env_api_ptr = hv_fetch(hv_self, "env_api", strlen("env_api"), 0);
  SV* sv_env_api = sv_env_api_ptr ? *sv_env_api_ptr : &PL_sv_undef;
  SPVM_ENV* env_api = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env_api);
  
  void* compiler = env_api->api->compiler->new_instance();
  
  size_t iv_compiler = PTR2IV(compiler);
  SV* sviv_compiler = sv_2mortal(newSViv(iv_compiler));
  SV* sv_compiler = sv_2mortal(newRV_inc(sviv_compiler));
  (void)hv_store(hv_self, "pointer", strlen("pointer"), SvREFCNT_inc(sv_compiler), 0);
  
  void* runtime = env_api->api->compiler->get_runtime(compiler);
  
  SV* sv_runtime = SPVM_XS_UTIL_new_sv_pointer_object(aTHX_ runtime, "SPVM::Builder::Runtime");
  (void)hv_store(hv_self, "runtime", strlen("runtime"), SvREFCNT_inc(sv_runtime), 0);
  
  XSRETURN(0);
}

SV*
get_class_file(...)
  PPCODE:
{
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  SV* sv_class_name = ST(1);
  const char* class_name = SvPV_nolen(sv_class_name);
  
  SV** sv_env_api_ptr = hv_fetch(hv_self, "env_api", strlen("env_api"), 0);
  SV* sv_env_api = sv_env_api_ptr ? *sv_env_api_ptr : &PL_sv_undef;
  SPVM_ENV* env_api = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env_api)));
  
  void* compiler = SPVM_XS_UTIL_get_pointer(aTHX_ sv_self);
  
  void* class_file = env_api->api->compiler->get_class_file(compiler, class_name);
  SV* sv_class_file = &PL_sv_undef;
  if (class_file) {
    HV* hv_class_file = (HV*)sv_2mortal((SV*)newHV());
    
    (void)hv_store(hv_class_file, "class_name", strlen("class_name"), SvREFCNT_inc(sv_class_name), 0);
    
    const char* file = env_api->api->class_file->get_file(compiler, class_file);
    if (file) {
      SV* sv_file = sv_2mortal(newSVpv(file, 0));
      (void)hv_store(hv_class_file, "file", strlen("file"), SvREFCNT_inc(sv_file), 0);
    }
    
    const char* dir = env_api->api->class_file->get_dir(compiler, class_file);
    if (dir) {
      SV* sv_dir = sv_2mortal(newSVpv(dir, 0));
      (void)hv_store(hv_class_file, "dir", strlen("dir"), SvREFCNT_inc(sv_dir), 0);
    }
    
    const char* rel_file = env_api->api->class_file->get_rel_file(compiler, class_file);
    if (rel_file) {
      SV* sv_rel_file = sv_2mortal(newSVpv(rel_file, 0));
      (void)hv_store(hv_class_file, "rel_file", strlen("rel_file"), SvREFCNT_inc(sv_rel_file), 0);
    }
    
    const char* content = env_api->api->class_file->get_content(compiler, class_file);
    if (content) {
      SV* sv_content = sv_2mortal(newSVpv(content, 0));
      (void)hv_store(hv_class_file, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
    }
    
    int32_t content_length = env_api->api->class_file->get_content_length(compiler, class_file);
    SV* sv_content_length = sv_2mortal(newSViv(content_length));
    (void)hv_store(hv_class_file, "content_length", strlen("content_length"), SvREFCNT_inc(sv_content_length), 0);
    
    sv_class_file = sv_2mortal(newRV_inc((SV*)hv_class_file));
  }
  
  XPUSHs(sv_class_file);
  
  XSRETURN(1);
}

SV*
compile(...)
  PPCODE:
{
  
  SV* sv_self = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_start_file = ST(2);
  SV* sv_start_line = ST(3);
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  void* compiler = SPVM_XS_UTIL_get_pointer(aTHX_ sv_self);
  
  // Include directries
  SV** sv_include_dirs_ptr = hv_fetch(hv_self, "include_dirs", strlen("include_dirs"), 0);
  SV* sv_include_dirs = sv_include_dirs_ptr ? *sv_include_dirs_ptr : &PL_sv_undef;
  
  // Name
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  // File
  const char* start_file = SvPV_nolen(sv_start_file);
  
  // Line
  int32_t start_line = (int32_t)SvIV(sv_start_line);
  
  SV** sv_env_api_ptr = hv_fetch(hv_self, "env_api", strlen("env_api"), 0);
  SV* sv_env_api = sv_env_api_ptr ? *sv_env_api_ptr : &PL_sv_undef;
  SPVM_ENV* env_api = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env_api);
  
  // Set starting file
  env_api->api->compiler->set_start_file(compiler, start_file);
  
  // Set starting line
  env_api->api->compiler->set_start_line(compiler, start_line);
  
  // Add include paths
  AV* av_include_dirs;
  if (SvOK(sv_include_dirs)) {
    av_include_dirs = (AV*)SvRV(sv_include_dirs);
  }
  else {
    av_include_dirs = (AV*)sv_2mortal((SV*)newAV());
  }
  int32_t av_include_dirs_length = (int32_t)av_len(av_include_dirs) + 1;
  for (int32_t i = 0; i < av_include_dirs_length; i++) {
    SV** sv_include_dir_ptr = av_fetch(av_include_dirs, i, 0);
    SV* sv_include_dir = sv_include_dir_ptr ? *sv_include_dir_ptr : &PL_sv_undef;
    char* include_dir = SvPV_nolen(sv_include_dir);
    env_api->api->compiler->add_include_dir(compiler, include_dir);
  }
  
  // Compile SPVM
  int32_t status = env_api->api->compiler->compile(compiler, basic_type_name);
  
  SV* sv_success = &PL_sv_undef;
  if (status == 0) {
    sv_success = sv_2mortal(newSViv(1));
  }
  
  XPUSHs(sv_success);
  
  XSRETURN(1);
}

SV*
get_error_messages(...)
  PPCODE:
{
  
  SV* sv_self = ST(0);
  
  HV* hv_self = (HV*)SvRV(sv_self);
  
  SV** sv_env_api_ptr = hv_fetch(hv_self, "env_api", strlen("env_api"), 0);
  SV* sv_env_api = sv_env_api_ptr ? *sv_env_api_ptr : &PL_sv_undef;
  SPVM_ENV* env_api = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env_api);
  
  void* compiler = SPVM_XS_UTIL_get_pointer(aTHX_ sv_self);
  
  AV* av_error_messages = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_error_messages = sv_2mortal(newRV_inc((SV*)av_error_messages));
  
  int32_t error_messages_length = env_api->api->compiler->get_error_messages_length(compiler);
  
  for (int32_t i = 0; i < error_messages_length; i++) {
    const char* error_message = env_api->api->compiler->get_error_message(compiler, i);
    SV* sv_error_message = sv_2mortal(newSVpv(error_message, 0));
    av_push(av_error_messages, SvREFCNT_inc(sv_error_message));
  }
  
  XPUSHs(sv_error_messages);
  XSRETURN(1);
}

MODULE = SPVM::Builder::Runtime		PACKAGE = SPVM::Builder::Runtime

SV*
get_method_names(...)
  PPCODE:
{
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  void* runtime = SPVM_XS_UTIL_get_pointer(aTHX_ sv_self);
  
  SV* sv_basic_type_name = ST(1);
  SV* sv_category = ST(2);
  
  // Name
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SV** sv_env_api_ptr = hv_fetch(hv_self, "env_api", strlen("env_api"), 0);
  SV* sv_env_api = sv_env_api_ptr ? *sv_env_api_ptr : &PL_sv_undef;
  SPVM_ENV* env_api = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env_api);
  
  AV* av_method_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_method_names = sv_2mortal(newRV_inc((SV*)av_method_names));
  
  void* basic_type = env_api->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  
  int32_t methods_length = env_api->api->basic_type->get_methods_length(runtime, basic_type);
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    void* method = env_api->api->basic_type->get_method_by_index(runtime, basic_type, method_index);
    const char* method_name = env_api->api->method->get_name(runtime, method);
    SV* sv_method_name = sv_2mortal(newSVpv(method_name, 0));
    int32_t is_push = 0;
    if (SvOK(sv_category)) {
      if(strEQ(SvPV_nolen(sv_category), "native") && env_api->api->method->is_native(runtime, method)) {
        av_push(av_method_names, SvREFCNT_inc(sv_method_name));
      }
      else if (strEQ(SvPV_nolen(sv_category), "precompile") && env_api->api->method->is_precompile(runtime, method)) {
        av_push(av_method_names, SvREFCNT_inc(sv_method_name));
      }
    }
    else {
      av_push(av_method_names, SvREFCNT_inc(sv_method_name));
    }
  }
  
  XPUSHs(sv_method_names);
  XSRETURN(1);
}

SV*
get_basic_type_names(...)
  PPCODE:
{
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  void* runtime = SPVM_XS_UTIL_get_pointer(aTHX_ sv_self);
  
  SV** sv_env_api_ptr = hv_fetch(hv_self, "env_api", strlen("env_api"), 0);
  SV* sv_env_api = sv_env_api_ptr ? *sv_env_api_ptr : &PL_sv_undef;
  SPVM_ENV* env_api = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env_api);
  
  AV* av_basic_type_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_basic_type_names = sv_2mortal(newRV_inc((SV*)av_basic_type_names));
  
  int32_t basic_types_length = env_api->api->runtime->get_basic_types_length(runtime);
  for (int32_t basic_type_id = 0; basic_type_id < basic_types_length; basic_type_id++) {
    void* basic_type = env_api->api->runtime->get_basic_type_by_id(runtime, basic_type_id);
    int32_t basic_type_category = env_api->api->basic_type->get_category(runtime, basic_type);
    const char* basic_type_name = env_api->api->basic_type->get_name(runtime, basic_type);
    SV* sv_basic_type_name = sv_2mortal(newSVpv(basic_type_name, 0));
    av_push(av_basic_type_names, SvREFCNT_inc(sv_basic_type_name));
  }
  
  XPUSHs(sv_basic_type_names);
  XSRETURN(1);
}

SV*
get_class_file(...)
  PPCODE:
{
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  void* runtime = SPVM_XS_UTIL_get_pointer(aTHX_ sv_self);
  
  SV* sv_basic_type_name = ST(1);
  
  // Name
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SV** sv_env_api_ptr = hv_fetch(hv_self, "env_api", strlen("env_api"), 0);
  SV* sv_env_api = sv_env_api_ptr ? *sv_env_api_ptr : &PL_sv_undef;
  SPVM_ENV* env_api = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env_api);
  
  void* basic_type = env_api->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  
  const char* class_file;
  SV* sv_class_file = &PL_sv_undef;
  
  if (basic_type) {
    int32_t basic_type_category = env_api->api->basic_type->get_category(runtime, basic_type);
    if (basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS || basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE || basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM) {
      const char* class_dir = env_api->api->basic_type->get_class_dir(runtime, basic_type);
      const char* class_dir_sep;
      if (class_dir) {
        class_dir_sep = "/";
      }
      else {
        class_dir_sep = "";
        class_dir = "";
      }
      const char* class_rel_file = env_api->api->basic_type->get_class_rel_file(runtime, basic_type);
      
      sv_class_file = sv_2mortal(newSVpv(class_dir, 0));
      sv_catpv(sv_class_file, class_dir_sep);
      sv_catpv(sv_class_file, class_rel_file);
    }
  }
  
  XPUSHs(sv_class_file);
  XSRETURN(1);
}

SV*
set_native_method_address(...)
  PPCODE:
{
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  void* runtime = SPVM_XS_UTIL_get_pointer(aTHX_ sv_self);

  SV* sv_basic_type_name = ST(1);
  SV* sv_method_name = ST(2);
  SV* sv_native_address = ST(3);
  
  SV** sv_env_api_ptr = hv_fetch(hv_self, "env_api", strlen("env_api"), 0);
  SV* sv_env_api = sv_env_api_ptr ? *sv_env_api_ptr : &PL_sv_undef;
  SPVM_ENV* env_api = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env_api);
  
  // Basic type name
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  void* basic_type = env_api->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  
  // Method name
  const char* method_name = SvPV_nolen(sv_method_name);
  
  // Method
  void* method = env_api->api->basic_type->get_method_by_name(runtime, basic_type, method_name);
  
  // Native address
  void* native_address = INT2PTR(void*, SvIV(sv_native_address));
  
  env_api->api->method->set_native_address(runtime, method, native_address);
  
  assert(native_address == env_api->api->method->get_native_address(runtime, method));
  
  XSRETURN(0);
}

SV*
build_precompile_class_source(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  void* runtime = SPVM_XS_UTIL_get_pointer(aTHX_ sv_self);
  
  SV* sv_basic_type_name = ST(1);
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SV** sv_env_api_ptr = hv_fetch(hv_self, "env_api", strlen("env_api"), 0);
  SV* sv_env_api = sv_env_api_ptr ? *sv_env_api_ptr : &PL_sv_undef;
  SPVM_ENV* env_api = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env_api);
  
  // New allocator
  void* allocator = env_api->api->allocator->new_instance();
  
  // New string buffer
  void* string_buffer = env_api->api->string_buffer->new_instance(allocator, 0);
  
  void* basic_type = env_api->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  
  env_api->api->runtime->build_precompile_class_source(runtime, string_buffer, basic_type);
  
  const char* string_buffer_value = env_api->api->string_buffer->get_string(string_buffer);
  int32_t string_buffer_length = env_api->api->string_buffer->get_length(string_buffer);
  SV* sv_precompile_source = sv_2mortal(newSVpv(string_buffer_value, string_buffer_length));
  
  // Free string buffer
  env_api->api->string_buffer->free_instance(string_buffer);
  
  // Free allocator
  env_api->api->allocator->free_instance(allocator);
  
  XPUSHs(sv_precompile_source);
  XSRETURN(1);
}

MODULE = SPVM::Builder::Env		PACKAGE = SPVM::Builder::Env

SV*
new(...)
  PPCODE:
{
  SV* sv_class = ST(0);
  
  SV* sv_compiler = ST(1);
  
  SPVM_ENV* new_env = SPVM_NATIVE_new_env();
  
  SV* sv_self = SPVM_XS_UTIL_new_sv_pointer_object(aTHX_ new_env, "SPVM::Builder::Env");
  HV* hv_self = (HV*)SvRV(sv_self);
  
  if (SvOK(sv_compiler)) {
    void* compiler = SPVM_XS_UTIL_get_pointer(aTHX_ sv_compiler);
    void* runtime = new_env->api->compiler->get_runtime(compiler);
    new_env->runtime = runtime;
    new_env->api->runtime->set_compiler(runtime, compiler);
    (void)hv_store(hv_self, "compiler", strlen("compiler"), SvREFCNT_inc(sv_compiler), 0);
  }
  
  XPUSHs(sv_self);
  XSRETURN(1);
}

SV*
DESTROY(...)
  PPCODE:
{
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SPVM_ENV* env = SPVM_XS_UTIL_get_pointer(aTHX_ sv_self);
  
  env->free_env(env);
  
  XSRETURN(0);
}

SV*
new_stack(...)
  PPCODE:
{
  
  // Env
  SV* sv_env = ST(0);
  SPVM_ENV* env = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env);

  // Create native_stack
  SPVM_VALUE* stack = env->new_stack(env);
  SV* sv_stack = SPVM_XS_UTIL_new_sv_pointer_object(aTHX_ stack, "SPVM::Builder::Stack");
  HV* hv_stack = (HV*)SvRV(sv_stack);

  (void)hv_store(hv_stack, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);

  XPUSHs(sv_stack);
  XSRETURN(1);
}

MODULE = SPVM::Builder::Stack		PACKAGE = SPVM::Builder::Stack

SV*
DESTROY(...)
  PPCODE:
{
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Stack
  SPVM_VALUE* stack = SPVM_XS_UTIL_get_pointer(aTHX_ sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = SPVM_XS_UTIL_get_pointer(aTHX_ sv_env);
  
  // Free native_stack
  env->free_stack(env, stack);
  
  XSRETURN(0);
}

MODULE = SPVM		PACKAGE = SPVM

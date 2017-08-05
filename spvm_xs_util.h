#ifndef SPVM_XS_UTIL_H
#define SPVM_XS_UTIL_H

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "spvm_api.h"
#include "spvm_type.h"

#include <stdint.h>

SPVM_API* SPVM_XS_UTIL_get_api() {
  SV* sv_api = get_sv("SPVM::API", 0);
  SV* sviv_api = SvRV(sv_api);
  size_t iv_api = SvIV(sviv_api);
  
  SPVM_API* api = INT2PTR(SPVM_API*, iv_api);
  
  return api;
}

const char* SPVM_XS_UTIL_get_type_name(int32_t type_id) {
  AV* av_type_names = get_av("SPVM::TYPE_NAMES", 0);
  SV** sv_type_name_ptr = av_fetch(av_type_names, type_id, 0);
  SV* sv_type_name = *sv_type_name_ptr;
  const char* type_name = SvPV_nolen(sv_type_name);
  
  return type_name;
}

int32_t SPVM_XS_UTIL_get_type_id(SV* sv_object) {
  HV* hv_object = (HV*)SvRV(sv_object);
  SV** sv_type_id_ptr = hv_fetch(hv_object, "type_id", strlen("type_id"), 0);
  SV* sv_type_id = sv_type_id_ptr ? *sv_type_id_ptr : &PL_sv_undef;
  
  if (SvOK(sv_type_id)) {
    return (int32_t)SvIV(sv_type_id);
  }
  else {
    return -1;
  }
}

int32_t SPVM_XS_UTIL_get_field_type_id(const char* package_name, const char* field_name) {
  // Field symbol table
  HV* hv_field_symtable = get_hv("SPVM::FIELD_SYMTABLE", 0);
  
  SV** sv_package_info_ptr = hv_fetch(hv_field_symtable, package_name, strlen(package_name), 0);
  if (sv_package_info_ptr) {
    SV* sv_package_info = *sv_package_info_ptr;
    HV* hv_package_info = (HV*)SvRV(sv_package_info);
    
    SV** sv_field_info_ptr = hv_fetch(hv_package_info, field_name, strlen(field_name), 0);
    if (sv_field_info_ptr) {
      SV* sv_field_info = *sv_field_info_ptr;
      HV* hv_field_info = (HV*)SvRV(sv_field_info);
      
      SV** sv_field_type_id_ptr = hv_fetch(hv_field_info, "type_id", strlen("type_id"), 0);
      if (sv_field_type_id_ptr) {
        SV* sv_field_type_id = *sv_field_type_id_ptr;
        int32_t field_type_id = SvIV(sv_field_type_id);
        
        return field_type_id;
      }
      else {
        return SPVM_API_ERROR_NO_ID;
      }
    }
    else {
      return SPVM_API_ERROR_NO_ID;
    }
  }
  else {
    return SPVM_API_ERROR_NO_ID;
  }
}

int32_t SPVM_XS_UTIL_get_field_id(const char* package_name, const char* field_name) {
  // Field symbol table
  HV* hv_field_symtable = get_hv("SPVM::FIELD_SYMTABLE", 0);
  
  SV** sv_package_info_ptr = hv_fetch(hv_field_symtable, package_name, strlen(package_name), 0);
  if (sv_package_info_ptr) {
    SV* sv_package_info = *sv_package_info_ptr;
    HV* hv_package_info = (HV*)SvRV(sv_package_info);
    
    SV** sv_field_info_ptr = hv_fetch(hv_package_info, field_name, strlen(field_name), 0);
    if (sv_field_info_ptr) {
      SV* sv_field_info = *sv_field_info_ptr;
      HV* hv_field_info = (HV*)SvRV(sv_field_info);
      
      SV** sv_field_id_ptr = hv_fetch(hv_package_info, "id", strlen("id"), 0);
      if (sv_field_id_ptr) {
        SV* sv_field_id = *sv_field_id_ptr;
        int32_t field_id = (int32_t)SvIV(sv_field_id);
        
        return field_id;
      }
      else {
        return SPVM_API_ERROR_NO_ID;
      }
    }
    else {
      return SPVM_API_ERROR_NO_ID;
    }
  }
  else {
    return SPVM_API_ERROR_NO_ID;
  }
}

SV* SPVM_XS_UTIL_new_sv_byte_array(SPVM_API_ARRAY* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Byte", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  // Set type id
  SV* sv_type_id = sv_2mortal(newSViv(SPVM_TYPE_C_ID_ARRAY_BYTE));
  hv_store(hv_array, "type_id", strlen("type_id"), SvREFCNT_inc(sv_type_id), 0);
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_string(SPVM_API_ARRAY* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::String", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  // Set type id
  SV* sv_type_id = sv_2mortal(newSViv(SPVM_TYPE_C_ID_STRING));
  hv_store(hv_array, "type_id", strlen("type_id"), SvREFCNT_inc(sv_type_id), 0);

  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_short_array(SPVM_API_ARRAY* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Short", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  // Set type id
  SV* sv_type_id = sv_2mortal(newSViv(SPVM_TYPE_C_ID_ARRAY_SHORT));
  hv_store(hv_array, "type_id", strlen("type_id"), SvREFCNT_inc(sv_type_id), 0);

  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_int_array(SPVM_API_ARRAY* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Int", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  // Set type id
  SV* sv_type_id = sv_2mortal(newSViv(SPVM_TYPE_C_ID_ARRAY_INT));
  hv_store(hv_array, "type_id", strlen("type_id"), SvREFCNT_inc(sv_type_id), 0);

  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_long_array(SPVM_API_ARRAY* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Long", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  // Set type id
  SV* sv_type_id = sv_2mortal(newSViv(SPVM_TYPE_C_ID_ARRAY_LONG));
  hv_store(hv_array, "type_id", strlen("type_id"), SvREFCNT_inc(sv_type_id), 0);
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_float_array(SPVM_API_ARRAY* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Float", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  // Set type id
  SV* sv_type_id = sv_2mortal(newSViv(SPVM_TYPE_C_ID_ARRAY_FLOAT));
  hv_store(hv_array, "type_id", strlen("type_id"), SvREFCNT_inc(sv_type_id), 0);
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_double_array(SPVM_API_ARRAY* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Double", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  // Set type id
  SV* sv_type_id = sv_2mortal(newSViv(SPVM_TYPE_C_ID_ARRAY_DOUBLE));
  hv_store(hv_array, "type_id", strlen("type_id"), SvREFCNT_inc(sv_type_id), 0);

  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_object_array(int32_t type_id, SPVM_API_ARRAY* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Object", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  // Set type id
  SV* sv_type_id = sv_2mortal(newSViv(type_id));
  hv_store(hv_array, "type_id", strlen("type_id"), SvREFCNT_inc(sv_type_id), 0);
  
  return sv_array;
}


SV* SPVM_XS_UTIL_new_sv_object(int32_t type_id, SPVM_API_OBJECT* object) {
  // Create object
  HV* hv_object = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_object = sv_2mortal(newRV_inc((SV*)hv_object));
  HV* hv_class = gv_stashpv("SPVM::Object", 0);
  sv_bless(sv_object, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(object);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_object, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  // Set type id
  SV* sv_type_id = sv_2mortal(newSViv(type_id));
  hv_store(hv_object, "type_id", strlen("type_id"), SvREFCNT_inc(sv_type_id), 0);

  return sv_object;
}

SPVM_API_ARRAY* SPVM_XS_UTIL_get_array(SV* sv_array) {
  
  HV* hv_array = (HV*)SvRV(sv_array);
  SV** sv_content_ptr = hv_fetch(hv_array, "content", strlen("content"), 0);
  if (sv_content_ptr) {
    SV* sv_content = *sv_content_ptr;
    SV* sviv_content = SvRV(sv_content);
    size_t iv_content = SvIV(sviv_content);
    SPVM_API_ARRAY* array = INT2PTR(SPVM_API_ARRAY*, iv_content);
    
    return array;
  }
  else {
    return NULL;
  }
}

SPVM_API_OBJECT* SPVM_XS_UTIL_get_object(SV* sv_object) {
  
  HV* hv_object = (HV*)SvRV(sv_object);
  SV** sv_content_ptr = hv_fetch(hv_object, "content", strlen("content"), 0);
  
  assert(sv_content_ptr);
  
  SV* sv_content = *sv_content_ptr;
  SV* sviv_content = SvRV(sv_content);
  size_t iv_content = SvIV(sviv_content);
  SPVM_API_OBJECT* object = INT2PTR(SPVM_API_OBJECT*, iv_content);
  
  return object;
}

int32_t SPVM_XS_UTIL_get_package_id(const char* package) {
  HV* hv_package_symtable = get_hv("SPVM::PACKAGE_SYMTABLE", 0);

  SV** sv_package_ptr = hv_fetch(hv_package_symtable, package, strlen(package), 0);
  if (sv_package_ptr) {
    SV* sv_package_info = *sv_package_ptr;
    HV* hv_package_info = (HV*)SvRV(sv_package_info);
    
    SV** sv_package_id_ptr = hv_fetch(hv_package_info, "id", strlen("id"), 0);
    if (sv_package_id_ptr) {
      SV* sv_package_id = *sv_package_id_ptr;
      int32_t package_id = (int32_t)SvIV(sv_package_id);
      return package_id;
    }
    else {
      return SPVM_API_ERROR_NO_ID;
    }
  }
  else {
    return SPVM_API_ERROR_NO_ID;
  }
}

int32_t SPVM_XS_UTIL_get_type_id_from_package_name(const char* package_name) {
  HV* hv_package_symtable = get_hv("SPVM::PACKAGE_SYMTABLE", 0);

  SV** sv_package_info_ptr = hv_fetch(hv_package_symtable, package_name, strlen(package_name), 0);
  if (sv_package_info_ptr) {
    SV* sv_package_info = *sv_package_info_ptr;
    HV* hv_package_info = (HV*)SvRV(sv_package_info);
    
    SV** sv_type_id_ptr = hv_fetch(hv_package_info, "type_id", strlen("type_id"), 0);
    if (sv_type_id_ptr) {
      SV* sv_type_id = *sv_type_id_ptr;
      int32_t type_id = (int32_t)SvIV(sv_type_id);
      return type_id;
    }
    else {
      return SPVM_API_ERROR_NO_ID;
    }
  }
  else {
    return SPVM_API_ERROR_NO_ID;
  }
}

#endif

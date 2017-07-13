#ifndef SPVM_XS_UTIL_H
#define SPVM_XS_UTIL_H

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "spvm_api.h"

SPVM_API* SPVM_XS_UTIL_get_api() {
    SV* sv_api = get_sv("SPVM::API", 0);
    SV* sviv_api = SvRV(sv_api);
    size_t iv_api = SvIV(sviv_api);
    
    SPVM_API* api = INT2PTR(SPVM_API*, iv_api);
    
    return api;
}

SV* SPVM_XS_UTIL_new_sv_array_object(const char* type, SPVM_API_ARRAY_OBJECT* array_object) {
  // Create array_object
  HV* hv_array_object = sv_2mortal((SV*)newHV());
  SV* sv_array_object = sv_2mortal(newRV_inc((SV*)hv_array_object));
  HV* hv_class = gv_stashpv("SPVM::ArrayObject", 0);
  sv_bless(sv_array_object, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array_object);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array_object, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  // Set type
  SV* sv_type = sv_2mortal(newSVpv(type, 0));
  hv_store(hv_array_object, "type", strlen("type"), SvREFCNT_inc(sv_type), 0);
  
  return sv_array_object;
}

SPVM_API_ARRAY_OBJECT* SPVM_XS_UTIL_get_array_object(SV* sv_array_object) {
  
  HV* hv_array_object = (HV*)SvRV(sv_array_object);
  SV** sv_content_ptr = hv_fetch(hv_array_object, "content", strlen("content"), 0);
  SV* sv_content = sv_content_ptr ? *sv_content_ptr : &PL_sv_undef;
  SV* sviv_content = SvRV(sv_content);
  size_t iv_content = SvIV(sviv_content);
  SPVM_API_ARRAY_OBJECT* array_object = INT2PTR(SPVM_API_ARRAY_OBJECT*, iv_content);
  
  return array_object;
}

#endif

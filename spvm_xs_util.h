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

#endif

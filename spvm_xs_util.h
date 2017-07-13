#ifndef SPVM_XS_UTIL_H
#define SPVM_XS_UTIL_H

// Get API macro
#define SPVM_XS_UTIL_SET_API(api) \
  do { \
    SV* sv_api = get_sv("SPVM::API", 0); \
    SV* sviv_api = SvRV(sv_api); \
    size_t iv_api = SvIV(sviv_api); \
    api = INT2PTR(SPVM_API*, iv_api); \
  } while (0)

#endif

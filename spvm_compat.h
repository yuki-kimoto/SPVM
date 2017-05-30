#ifndef SPVM_COMPAT_H
#define SPVM_COMPAT_H

#include "spvm_base.h"

char* SPVM_COMPAT_SVpv(SPVM_SV* sv);
void SPVM_COMPAT_sv_catpvn(SPVM_SV*, const char*, size_t);
SPVM_SV* SPVM_COMPAT_newSVsv(SPVM_SV* sv);
SPVM_SV* SPVM_COMPAT_newSVpvn(SPVM* spvm, const char* pv, size_t length);
void SPVM_SvREFCNT_dec(SPVM_SV* sv);

#endif

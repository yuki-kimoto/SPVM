#include <assert.h>
#include <string.h>

#include "spvm.h"
#include "spvm_sv.h"
#include "spvm_allocator_util.h"

char* SPVM_COMPAT_SVpv(SPVM_SV* sv) {
  return sv->buffer;
}

void SPVM_COMPAT_sv_catpvn(SPVM_SV* sv, const char* pv, size_t length) {
  char* new_buffer = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(sv->length + length + 1, sizeof(char));
  strncpy(new_buffer, sv->buffer, sv->length);
  strncpy(new_buffer + sv->length, pv, length);
  sv->buffer = new_buffer;
  sv->buffer[sv->length + length] = '\0';
  sv->length = sv->length + length;
}

void SPVM_SvREFCNT_dec(SPVM_SV* sv) {
  sv->ref_count--;
}

SPVM_SV* SPVM_COMPAT_newSVsv(SPVM_SV* sv) {
  
  return sv;
}

SPVM_SV* SPVM_COMPAT_newSVpvn(SPVM* spvm, const char* pv, size_t length) {
  (void)spvm;
  
  SPVM_SV* sv = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(1, sizeof(SPVM_SV));
  
  sv->buffer = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(length + 1, sizeof(int8_t));
  strncpy(sv->buffer, pv, length);
  sv->buffer[length] = '\0';
  
  sv->ref_count = 1;
  sv->length = length;
  
  return sv;
}

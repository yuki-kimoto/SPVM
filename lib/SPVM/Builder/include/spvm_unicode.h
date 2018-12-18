#ifndef SPVM_UNICODE_H
#define SPVM_UNICODE_H

#include "spvm_base.h"

/** Memory could not be allocated. */
#define SPVM_UNICODE_ERROR_NOMEM -1
/** The given string is too long to be processed. */
#define SPVM_UNICODE_ERROR_OVERFLOW -2
/** The given string is not a legal UTF-8 string. */
#define SPVM_UNICODE_ERROR_INVALIDUTF8 -3
/** The @ref SPVM_UNICODE_REJECTNA flag was set and an unassigned codepoint was found. */
#define SPVM_UNICODE_ERROR_NOTASSIGNED -4
/** Invalid options have been used. */
#define SPVM_UNICODE_ERROR_INVALIDOPTS -5

#define SPVM_UNICODE_UTF8_COUNT(ch)  (((ch) & 0xc0) == 0x80)

int32_t SPVM_UNICODE_convert_unicode_to_utf8(int32_t uc, uint8_t* dst);
int32_t SPVM_UNICODE_convert_unicode_to_utf8(int32_t uc, uint8_t* dst);
int32_t SPVM_UNICODE_codepoint_valid(int32_t uc);
int32_t SPVM_UNICODE_iterate(const uint8_t *str, int32_t strlen, int32_t *dst);

#endif

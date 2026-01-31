// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <errno.h>
#include <stddef.h>
#include <assert.h>

static const char* FILE_NAME = "Fn.c";

int32_t SPVM__Fn__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].dval = DBL_MAX;
  
  return 0;
}

int32_t SPVM__Fn__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].dval = DBL_MIN;
  
  return 0;
}

int32_t SPVM__Fn__DOUBLE_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].dval = DBL_MAX;
  
  return 0;
}

int32_t SPVM__Fn__DOUBLE_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].dval = DBL_MIN;
  
  return 0;
}

int32_t SPVM__Fn__FLOAT_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].fval = FLT_MAX;
  
  return 0;
}

int32_t SPVM__Fn__FLOAT_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].fval = FLT_MIN;
  
  return 0;
}

int32_t SPVM__Fn__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].fval = FLT_MAX;
  
  return 0;
}

int32_t SPVM__Fn__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].fval = FLT_MIN;
  
  return 0;
}

static ptrdiff_t SPVM__Fn__static__convert_code_point_to_utf8_char(int32_t uc, uint8_t *dst) {
  if (uc < 0x00) {
    return 0;
  } else if (uc < 0x80) {
    dst[0] = (uint8_t) uc;
    return 1;
  } else if (uc < 0x800) {
    dst[0] = (uint8_t)(0xC0 + (uc >> 6));
    dst[1] = (uint8_t)(0x80 + (uc & 0x3F));
    return 2;
  // Note: we allow encoding 0xd800-0xdfff here, so as not to change
  // the API, however, these are actually invalid in UTF-8
  } else if (uc < 0x10000) {
    dst[0] = (uint8_t)(0xE0 + (uc >> 12));
    dst[1] = (uint8_t)(0x80 + ((uc >> 6) & 0x3F));
    dst[2] = (uint8_t)(0x80 + (uc & 0x3F));
    return 3;
  } else if (uc < 0x110000) {
    dst[0] = (uint8_t)(0xF0 + (uc >> 18));
    dst[1] = (uint8_t)(0x80 + ((uc >> 12) & 0x3F));
    dst[2] = (uint8_t)(0x80 + ((uc >> 6) & 0x3F));
    dst[3] = (uint8_t)(0x80 + (uc & 0x3F));
    return 4;
  } else return 0;
}

int32_t SPVM__Fn___chr_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t code_point = stack[0].ival;
  
  assert(code_point >= 0);
  assert(code_point < 0x110000);
  
  uint8_t utf8_bytes[4];
  int32_t utf8_bytes_length = (int32_t)SPVM__Fn__static__convert_code_point_to_utf8_char(code_point, utf8_bytes);
  
  assert(utf8_bytes_length > 0);
  
  void* utf8_string = env->new_string(env, stack, (char*)utf8_bytes, utf8_bytes_length);
  
  stack[0].oval = utf8_string;
  
  return 0;
}

// https://code.woboq.org/userspace/glibc/stdlib/rand_r.c.html
static int SPVM__Fn__static__rand_r (uint32_t *seed)
{
  uint32_t next = *seed;
  int result;
  next *= 1103515245;
  next += 12345;
  result = (uint32_t) (next / 65536) % 2048;
  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (uint32_t) (next / 65536) % 1024;
  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (uint32_t) (next / 65536) % 1024;
  *seed = next;
  return result;
}

int32_t SPVM__Fn__crand(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t* seed_ref = stack[0].iref;
  
  if (!seed_ref) {
    return env->die(env, stack, "The reference of the seed $seed_ref must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t random_value = SPVM__Fn__static__rand_r((uint32_t *) seed_ref);
  
  stack[0].ival = random_value;
  
  return 0;
}

#define utf_cont(ch)  (((ch) & 0xc0) == 0x80)
#define SPVM_UTF8PROC_ERROR_INVALIDUTF8 -3
static ptrdiff_t spvm_utf8proc_iterate(const uint8_t *str, ptrdiff_t strlen, int32_t *dst) {
  uint32_t uc;
  const uint8_t *end;

  *dst = -1;
  if (!strlen) return 0;
  end = str + ((strlen < 0) ? 4 : strlen);
  uc = *str++;
  if (uc < 0x80) {
    *dst = uc;
    return 1;
  }
  // Must be between 0xc2 and 0xf4 inclusive to be valid
  if ((uc - 0xc2) > (0xf4-0xc2)) return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
  if (uc < 0xe0) {         // 2-byte sequence
     // Must have valid continuation character
     if (str >= end || !utf_cont(*str)) return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
     *dst = ((uc & 0x1f)<<6) | (*str & 0x3f);
     return 2;
  }
  if (uc < 0xf0) {        // 3-byte sequence
     if ((str + 1 >= end) || !utf_cont(*str) || !utf_cont(str[1]))
        return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
     // Check for surrogate chars
     if (uc == 0xed && *str > 0x9f)
         return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
     uc = ((uc & 0xf)<<12) | ((*str & 0x3f)<<6) | (str[1] & 0x3f);
     if (uc < 0x800)
         return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
     *dst = uc;
     return 3;
  }
  // 4-byte sequence
  // Must have 3 valid continuation characters
  if ((str + 2 >= end) || !utf_cont(*str) || !utf_cont(str[1]) || !utf_cont(str[2]))
     return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
  // Make sure in correct range (0x10000 - 0x10ffff)
  if (uc == 0xf0) {
    if (*str < 0x90) return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
  } else if (uc == 0xf4) {
    if (*str > 0x8f) return SPVM_UTF8PROC_ERROR_INVALIDUTF8;
  }
  *dst = ((uc & 7)<<18) | ((*str & 0x3f)<<12) | ((str[1] & 0x3f)<<6) | (str[2] & 0x3f);
  return 4;
}

int32_t SPVM__Fn__get_code_point(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_string = stack[0].oval;
  int32_t* offset_ref = stack[1].iref;
  
  if (!obj_string) {
    return env->die(env, stack, "The string $string must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!offset_ref) {
    return env->die(env, stack, "The reference of the offset $offset_ref must be must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(*offset_ref >= 0)) {
    return env->die(env, stack, "The offset $$offset_ref must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* string = env->get_chars(env, stack, obj_string);
  int32_t string_len = env->length(env, stack, obj_string);
  
  if (!(*offset_ref < string_len)) {
    return env->die(env, stack, "The value of the offset $offset must be less than the length of the string $string.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t dst;
  int32_t utf8_char_len = (int32_t)spvm_utf8proc_iterate((const uint8_t*)(string + *offset_ref), string_len, &dst);
  
  assert(utf8_char_len != 0);
  
  int32_t uchar;
  if (utf8_char_len > 0) {
    uchar = dst;
    *offset_ref += utf8_char_len;
  }
  else if (utf8_char_len == SPVM_UTF8PROC_ERROR_INVALIDUTF8) {
    env->die(env, stack, "An invalid UTF-8 is gotten.", __func__, FILE_NAME, __LINE__);
    
    int32_t error_id_unicode_invalid_utf8 = env->get_basic_type_id_by_name(env, stack, "Error::Unicode::InvalidUTF8", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    return error_id_unicode_invalid_utf8;
  }
  else {
    assert(0);
  }
  
  stack[0].ival = uchar;
  
  return 0;
}

int32_t SPVM__Fn__is_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* object = stack[0].oval;
  
  int32_t is_array;
  if (env->is_array(env, stack, object)) {
    is_array = 1;
  }
  else {
    is_array = 0;
  }
  
  stack[0].ival = is_array;
  
  return 0;
}

int32_t SPVM__Fn__is_class(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* object = stack[0].oval;
  
  int32_t is_class;
  if (env->is_class(env, stack, object)) {
    is_class = 1;
  }
  else {
    is_class = 0;
  }
  
  stack[0].ival = is_class;
  
  return 0;
}

int32_t SPVM__Fn__is_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* object = stack[0].oval;
  
  int32_t is_mulnum_array;
  if (env->is_mulnum_array(env, stack, object)) {
    is_mulnum_array = 1;
  }
  else {
    is_mulnum_array = 0;
  }
  
  stack[0].ival = is_mulnum_array;
  
  return 0;
}

int32_t SPVM__Fn__is_numeric_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* object = stack[0].oval;
  
  int32_t is_numeric_array;
  if (env->is_numeric_array(env, stack, object)) {
    is_numeric_array = 1;
  }
  else {
    is_numeric_array = 0;
  }
  
  stack[0].ival = is_numeric_array;
  
  return 0;
}

int32_t SPVM__Fn__is_object_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* object = stack[0].oval;
  
  int32_t is_object_array;
  if (env->is_object_array(env, stack, object)) {
    is_object_array = 1;
  }
  else {
    is_object_array = 0;
  }
  
  stack[0].ival = is_object_array;
  
  return 0;
}

int32_t SPVM__Fn__is_pointer_class(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* object = stack[0].oval;
  
  int32_t is_pointer_class;
  if (env->is_pointer_class(env, stack, object)) {
    is_pointer_class = 1;
  }
  else {
    is_pointer_class = 0;
  }
  
  stack[0].ival = is_pointer_class;
  
  return 0;
}

int32_t SPVM__Fn__memcpy(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The destination $dest must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(env->is_string(env, stack, obj_dest) || env->is_numeric_array(env, stack, obj_dest) || env->is_mulnum_array(env, stack, obj_dest))) {
    return env->die(env, stack, "The type of the dest $dest must be string type, a numeric array type, or a multi-numeric array type.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source $source must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(env->is_string(env, stack, obj_source) || env->is_numeric_array(env, stack, obj_source) || env->is_mulnum_array(env, stack, obj_source))) {
    return env->die(env, stack, "The type of the source $source must be string type, a numeric array type, or a multi-numeric array type.", __func__, FILE_NAME, __LINE__);
  }
  
  if (env->is_read_only(env, stack, obj_dest)) {
    return env->die(env, stack, "The destination $dest cannnot be be a read-only string.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length $length must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  char* dest = (char*)env->get_chars(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  int32_t dest_elem_size = env->get_elem_size(env, stack, obj_dest);
  int32_t dest_byte_length = dest_elem_size * dest_length;
  
  if (!(dest_offset + length <= dest_byte_length)) {
    return env->die(env, stack, "The offset $dest_offset + the length $length must be less than or equal to the length of the dest $obj_dest.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* source = env->get_chars(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  int32_t source_elem_size = env->get_elem_size(env, stack, obj_source);
  int32_t source_byte_length = source_elem_size * source_length;
  
  if (!(source_offset + length <= source_byte_length)) {
    return env->die(env, stack, "The offset $source_offset + the length $length must be less than or equal to the length of the source $source.", __func__, FILE_NAME, __LINE__);
  }
  
  memcpy((char*)(dest + dest_offset), (char*)(source + source_offset), length);
  
  return 0;
}

int32_t SPVM__Fn__memmove(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!obj_dest) {
    return env->die(env, stack, "The destination $dest must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(env->is_string(env, stack, obj_dest) || env->is_numeric_array(env, stack, obj_dest) || env->is_mulnum_array(env, stack, obj_dest))) {
    return env->die(env, stack, "The type of the dest $dest must be string type, a numeric array type, or a multi numeric array type.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The source $source must be defined.", __func__, FILE_NAME, __LINE__);
  }

  if (!(env->is_string(env, stack, obj_source) || env->is_numeric_array(env, stack, obj_source) || env->is_mulnum_array(env, stack, obj_source))) {
    return env->die(env, stack, "The type of the source $source must be string type, a numeric array type, or a multi numeric array type.", __func__, FILE_NAME, __LINE__);
  }

  if (env->is_read_only(env, stack, obj_dest)) {
    return env->die(env, stack, "The destination $dest must not be a read-only string.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length $length must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  char* dest = (char*)env->get_chars(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  int32_t dest_elem_size = env->get_elem_size(env, stack, obj_dest);
  int32_t dest_byte_length = dest_elem_size * dest_length;
  
  if (!(dest_offset + length <= dest_byte_length)) {
    return env->die(env, stack, "The offset $dest_offset + the length $length must be less than or equal to the length of the dest $obj_dest.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* source = env->get_chars(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  int32_t source_elem_size = env->get_elem_size(env, stack, obj_source);
  int32_t source_byte_length = source_elem_size * source_length;
  
  if (!(source_offset + length <= source_byte_length)) {
    return env->die(env, stack, "The offset $source_offset + the length $length must be less than or equal to the length of the source $obj_source.", __func__, FILE_NAME, __LINE__);
  }
  
  memmove((char*)(dest + dest_offset), (char*)(source + source_offset), length);
  
  return 0;
}

int32_t SPVM__Fn__sizeof_native_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t sizeof_native_int = sizeof(int);
  
  stack[0].ival = sizeof_native_int;
  
  return 0;
}

int32_t SPVM__Fn__sizeof_native_pointer(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t sizeof_native_pointer = sizeof(void*);
  
  stack[0].ival = sizeof_native_pointer;
  
  return 0;
}

int32_t SPVM__Fn__shorten(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* string = stack[0].oval;
  int32_t length = stack[1].ival;
  
  if (!string) {
    return env->die(env, stack, "The string $string must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length $length must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  
  env->shorten(env, stack, string, length);
  
  return 0;
}

int32_t SPVM__Fn__to_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  
  if (!obj_string) {
    return env->die(env, stack, "The string $string must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* string = env->get_chars(env, stack, obj_string);
  
  char *end;
  errno = 0;
  double num = strtod(string, &end);
  if (*end != '\0') {
    return env->die(env, stack, "The string $string must be the string that can be parsed as a double number.", __func__, FILE_NAME, __LINE__);
  }
  else if (errno == ERANGE) {
    return env->die(env, stack, "The string $string must be a double number in correct range.", __func__, FILE_NAME, __LINE__);
  }
  
  stack[0].dval = num;
  
  return 0;
}

int32_t SPVM__Fn__to_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  
  if (!obj_string) {
    return env->die(env, stack, "The string $string must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* string = env->get_chars(env, stack, obj_string);
  
  char *end;
  errno = 0;
  float num = strtof(string, &end);
  if (*end != '\0') {
    return env->die(env, stack, "The string $string must be the string that can be parsed as a float number.", __func__, FILE_NAME, __LINE__);
  }
  else if (errno == ERANGE) {
    return env->die(env, stack, "The string $string must be a float number in correct range.", __func__, FILE_NAME, __LINE__);
  }
  
  stack[0].fval = num;
  
  return 0;
}

int32_t SPVM__Fn__to_int_with_base(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  int32_t digit = stack[1].ival;
  
  if (!obj_string) {
    return env->die(env, stack, "The string $string must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(digit == 2 || digit == 8 || digit == 10 || digit == 16)) {
    return env->die(env, stack, "The digit $digit must be one of 2, 8, 10, or 16.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* string = env->get_chars(env, stack, obj_string);
  
  char *end;
  errno = 0;
  int64_t num = strtol(string, &end, digit);
  if (*end != '\0') {
    return env->die(env, stack, "The string $string must be the string that can be parsed as a %d-digit 32-bit integer", __func__, FILE_NAME, __LINE__, digit);
  }
  else if (errno == ERANGE || num < INT32_MIN || num > INT32_MAX) {
    return env->die(env, stack, "The string $string must be a 32-bit integer in correct range.", __func__, FILE_NAME, __LINE__);
  }
  
  stack[0].ival = (int32_t)num;
  
  return 0;
}

int32_t SPVM__Fn__to_long_with_base(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  int32_t digit = stack[1].ival;
  
  if (!obj_string) {
    return env->die(env, stack, "The string $string must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(digit == 2 || digit == 8 || digit == 10 || digit == 16)) {
    return env->die(env, stack, "The digit $digit must be one of 2, 8, 10, or 16.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* string = env->get_chars(env, stack, obj_string);
  
  char *end;
  errno = 0;
  int64_t num = strtoll(string, &end, digit);
  if (*end != '\0') {
    return env->die(env, stack, "The string $string must be the string that can be parsed as a %d-digit 64-bit integer", __func__, FILE_NAME, __LINE__, digit);
  }
  else if (errno == ERANGE) {
    return env->die(env, stack, "The string $string must be a 64-bit integer in correct range.", __func__, FILE_NAME, __LINE__);
  }
  
  stack[0].lval = (int64_t)num;
  
  return 0;
}

int32_t SPVM__Fn__object_to_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* object = stack[0].oval;
  
  int32_t int_value = (int32_t)(intptr_t)object;
  
  stack[0].ival = int_value;
  
  return 0;
}

int32_t SPVM__Fn__object_to_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* object = stack[0].oval;
  
  int64_t long_value = (int64_t)(intptr_t)object;
  
  stack[0].lval = long_value;
  
  return 0;
}

int32_t SPVM__Fn__get_version_string(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_basic_type_name = stack[0].oval;
  
  if (!obj_basic_type_name) {
    return env->die(env, stack, "The basic type name $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    return env->die(env, stack, "The class specified by the basic type name $basic_type_name must be loaded.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* version_string = env->get_version_string(env, stack, basic_type);
  
  void* obj_version_string = NULL;
  if (version_string) {
    obj_version_string = env->new_string(env, stack, version_string, strlen(version_string));
  }
  
  stack[0].oval = obj_version_string;
  
  return 0;
}

int32_t SPVM__Fn__get_spvm_version_number(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  double spvm_version_number = env->get_spvm_version_number(env, stack);
  
  stack[0].dval = spvm_version_number;
  
  return 0;
}

int32_t SPVM__Fn__get_version_number(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_basic_type_name = stack[0].oval;
  
  if (!obj_basic_type_name) {
    return env->die(env, stack, "The basic type name $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    return env->die(env, stack, "The class specified by the basic type name $basic_type_name must be loaded.", __func__, FILE_NAME, __LINE__);
  }
  
  double version_number = env->get_version_number(env, stack, basic_type);
  
  stack[0].dval = version_number;
  
  return 0;
}

int32_t SPVM__Fn__get_spvm_version_string(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* spvm_version = env->get_spvm_version_string(env, stack);
  
  void* obj_spvm_version = env->new_string(env, stack, spvm_version, strlen(spvm_version));
  
  stack[0].oval = obj_spvm_version;
  
  return 0;
}

int32_t SPVM__Fn__get_memory_blocks_count(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t memory_blocks_count = env->get_memory_blocks_count(env, stack);
  
  stack[0].ival = memory_blocks_count;
  
  return 0;
}

int32_t SPVM__Fn__get_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_basic_type_name = stack[0].oval;
  
  if (!obj_basic_type_name) {
    return env->die(env, stack, "The basic type name $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (!(basic_type_id >= 0)) {
    return env->die(env, stack, "The basic type \"%s\" is not found.", __func__, FILE_NAME, __LINE__, basic_type_name);
  }
  
  stack[0].ival = basic_type_id;
  
  return 0;
}

int32_t SPVM__Fn__get_compile_type_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_basic_type_name = stack[0].oval;
  
  if (!obj_basic_type_name) {
    return env->die(env, stack, "The basic type name $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  int32_t type_dimension = stack[1].ival;
  
  if (!(type_dimension >= 0 && type_dimension <= 255)) {
    return env->die(env, stack, "The type dimension $type_dimension must be grether than or equal to 0 and less than or equal to 255.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t type_flag = stack[2].ival;
  
  void* obj_compile_type_name = env->get_compile_type_name(env, stack, basic_type_name, type_dimension, type_flag);
  
  stack[0].oval = obj_compile_type_name;
  
  return 0;
}

int32_t SPVM__Fn__array_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_array = stack[0].oval;
  
  if (!obj_array) {
    return env->die(env, stack, "The array $array must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t is_array = env->is_array(env, stack, obj_array);
  
  if (!is_array) {
    return env->die(env, stack, "The type of the array $array must be an array type.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t length = env->length(env, stack, obj_array);
  
  stack[0].ival = length;
  
  return 0;
}

int32_t SPVM__Fn__get_elem_size(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_array = stack[0].oval;
  
  if (!obj_array) {
    return env->die(env, stack, "The array $array must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t is_array = env->is_array(env, stack, obj_array);
  
  if (!is_array) {
    return env->die(env, stack, "The type of the array $array must be an array type.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t elem_size = env->get_elem_size(env, stack, obj_array);
  
  stack[0].ival = elem_size;
  
  return 0;
}

int32_t SPVM__Fn__print_stderr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  
  env->print_stderr(env, stack, obj_string);
  
  return 0;
}

int32_t SPVM__Fn__say_stderr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  
  env->print_stderr(env, stack, obj_string);
  
  fputc('\n', env->spvm_stderr(env, stack));
  
  return 0;
}

int32_t SPVM__Fn__memcmp(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_data1 = stack[0].oval;
  int32_t data1_offset = stack[1].ival;
  void* obj_data2 = stack[2].oval;
  int32_t data2_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_data1) {
    return env->die(env, stack, "The data1 $data1 must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(env->is_string(env, stack, obj_data1) || env->is_numeric_array(env, stack, obj_data1) || env->is_mulnum_array(env, stack, obj_data1))) {
    return env->die(env, stack, "The type of the data1 $data1 must be string type, a numeric array type, or a multi-numeric array type.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_data2) {
    return env->die(env, stack, "The data2 $data2 must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(env->is_string(env, stack, obj_data2) || env->is_numeric_array(env, stack, obj_data2) || env->is_mulnum_array(env, stack, obj_data2))) {
    return env->die(env, stack, "The type of the data2 $data2 must be string type, a numeric array type, or a multi-numeric array type.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length $length must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  
  char* data1 = (char*)env->get_chars(env, stack, obj_data1);
  int32_t data1_length = env->length(env, stack, obj_data1);
  int32_t data1_elem_size = env->get_elem_size(env, stack, obj_data1);
  int32_t data1_byte_length = data1_elem_size * data1_length;
  
  if (!(data1_offset + length <= data1_byte_length)) {
    return env->die(env, stack, "The offset $data1_offset + the length $length must be less than or equal to the length of the data1 $obj_data1.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* data2 = env->get_chars(env, stack, obj_data2);
  int32_t data2_length = env->length(env, stack, obj_data2);
  int32_t data2_elem_size = env->get_elem_size(env, stack, obj_data2);
  int32_t data2_byte_length = data2_elem_size * data2_length;
  
  if (!(data2_offset + length <= data2_byte_length)) {
    return env->die(env, stack, "The offset $data2_offset + the length $length must be less than or equal to the length of the data2 $data2.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t cmp = memcmp((char*)(data1 + data1_offset), (char*)(data2 + data2_offset), length);
  
  stack[0].ival = cmp;
  
  return 0;
}

int32_t SPVM__Fn__system_is_little_endian(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t system_is_little_endian = 0;
  
  // Copied from https://dev.to/ajipelumi/c-function-to-check-endianness-5d25
  {
    unsigned int i = 1;
    char *c;
    
    c = (char *) &i; /* points to the first byte of the integer i */
    if (*c == 1) /* 1st byte looks like 0x01 */
    {
      system_is_little_endian = 1;
    }
  }
  
  stack[0].ival = system_is_little_endian;
  
  return 0;
}

int32_t SPVM__Fn__no_free(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* object = stack[0].oval;
  
  if (!object) {
    return env->die(env, stack, "The object $object must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t no_free = env->no_free(env, stack, object);
  
  stack[0].ival = no_free;
  
  return 0;
}

int32_t SPVM__Fn__set_no_free(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* object = stack[0].oval;
  
  if (!object) {
    return env->die(env, stack, "The object $object must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t no_free = stack[1].ival;
  
  env->set_no_free(env, stack, object, no_free);
  
  return 0;
}

int32_t SPVM__Fn__get_pointer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_object = stack[0].oval;
  
  if (!obj_object) {
    return env->die(env, stack, "The object $object must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* pointer = env->get_pointer(env, stack, obj_object);
  
  void* obj_address = env->new_object_by_name(env, stack, "Address", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_pointer(env, stack, obj_address, pointer);
  
  stack[0].oval = obj_address;
  
  return 0;
}

int32_t SPVM__Fn__set_pointer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_object = stack[0].oval;
  
  if (!obj_object) {
    return env->die(env, stack, "The object $object must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_address = stack[1].oval;
  
  if (!obj_address) {
    return env->die(env, stack, "The address $address must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* pointer = env->get_pointer(env, stack, obj_address);
  
  env->set_pointer(env, stack, obj_object, pointer);
  
  return 0;
}

int32_t SPVM__Fn__has_null_pointer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_object = stack[0].oval;
  
  if (!obj_object) {
    return env->die(env, stack, "The object $object must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* pointer = env->get_pointer(env, stack, obj_object);
  
  int32_t has_null_pointer = pointer == NULL;
  
  stack[0].ival = has_null_pointer;
  
  return 0;
}

int32_t SPVM__Fn__eq_pointer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_object1 = stack[0].oval;
  
  if (!obj_object1) {
    return env->die(env, stack, "The object $object1 must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_object2 = stack[1].oval;
  
  if (!obj_object2) {
    return env->die(env, stack, "The object $object2 must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* pointer1 = env->get_pointer(env, stack, obj_object1);
  
  void* pointer2 = env->get_pointer(env, stack, obj_object2);
  
  int32_t equal = pointer1 == pointer2;
  
  stack[0].ival = equal;
  
  return 0;
}

int32_t SPVM__Fn__pointer_to_string(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_object = stack[0].oval;
  
  if (!obj_object) {
    return env->die(env, stack, "The object $object must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* pointer = env->get_pointer(env, stack, obj_object);
  
  char tmp_buffer[64] = {0};
  
  snprintf(tmp_buffer, 64, "%p", pointer);
  
  void* obj_string = env->new_string_nolen(env, stack, tmp_buffer);
  
  stack[0].oval = obj_string;
  
  return 0;
}

int32_t SPVM__Fn__dump_object_internal(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_object = stack[0].oval;
  
  void* obj_dump = env->dump_object_internal(env, stack, obj_object);
  
  stack[0].oval = obj_dump;
  
  return 0;
}

int32_t SPVM__Fn__get_seed(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t seed = env->get_seed(env, stack);
  
  stack[0].ival = seed;
  
  return 0;
}

int32_t SPVM__Fn__set_seed(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t seed = stack[0].ival;
  
  env->set_seed(env, stack, seed);
  
  return 0;
}

int32_t SPVM__Fn__seed_initialized(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t seed_initialized = env->seed_initialized(env, stack);
  
  stack[0].ival = seed_initialized;
  
  return 0;
}

int32_t SPVM__Fn__get_basic_type_name_in_version_from(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_basic_type_name = stack[0].oval;
  
  if (!obj_basic_type_name) {
    return env->die(env, stack, "The basic type name $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  if (!basic_type) {
    return env->die(env, stack, "The class specified by the basic type name $basic_type_name must be loaded.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name_in_version_from = env->get_basic_type_name_in_version_from(env, stack, basic_type);
  
  void* obj_basic_type_name_in_version_from = NULL;
  if (basic_type_name_in_version_from) {
    obj_basic_type_name_in_version_from = env->new_string(env, stack, basic_type_name_in_version_from, strlen(basic_type_name_in_version_from));
  }
  
  stack[0].oval = obj_basic_type_name_in_version_from;
  
  return 0;
}

int32_t SPVM__Fn__destroy_cache_class_vars(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  env->destroy_cache_class_vars(env, stack);
  
  return 0;
}

int32_t SPVM__Fn__get_basic_type_name_by_id(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t basic_type_id = stack[0].ival;
  
  // Get the basic type by ID
  void* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, basic_type_id);
  
  // Throw an exception if the basic type is not found
  if (!basic_type) {
    return env->die(env, stack, "The basic type ID %d is not found.", __func__, FILE_NAME, __LINE__, basic_type_id);
  }
  
  // Get the basic type name
  const char* basic_type_name = env->api->basic_type->get_name(env->runtime, basic_type);
  
  // Create a new SPVM string object
  void* obj_basic_type_name = env->new_string(env, stack, basic_type_name, strlen(basic_type_name));
  
  stack[0].oval = obj_basic_type_name;
  
  return 0;
}

int32_t SPVM__Fn__get_current_method_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  /* Get the level argument from stack[0] */
  int32_t level = stack[0].ival;
  
  /* Adjustment:
     level 0 should be the currently executing method (the caller of this function).
     Since SPVM__Fn__get_current_method_name is level 0 in the physical stack,
     we add 1 to skip it.
  */
  int32_t adjusted_level = level + 1;
  
  int32_t error_id = 0;
  
  /* Get the method at the adjusted level */
  void* current_method = env->get_current_method(env, stack, adjusted_level, &error_id);
  
  /* If get_current_method fails (e.g. out of range), re-throw the exception */
  if (error_id) {
    return env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, FILE_NAME, __LINE__);
  }
  
  /* Get the method name */
  const char* method_name = env->api->method->get_name(env->runtime, current_method);
  
  /* Create a new SPVM string object */
  void* obj_method_name = env->new_string_nolen(env, stack, method_name);
  
  stack[0].oval = obj_method_name;
  
  return 0;
}

int32_t SPVM__Fn__get_current_basic_type_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  /* Get the level argument from stack[0] */
  int32_t level = stack[0].ival;
  
  /* Adjustment:
     level 0 should be the basic type of the currently executing method.
     Add 1 to skip this native method frame.
  */
  int32_t adjusted_level = level + 1;
  
  int32_t error_id = 0;
  
  /* Get the method at the adjusted level */
  void* current_method = env->get_current_method(env, stack, adjusted_level, &error_id);
  
  /* If get_current_method fails (e.g. out of range), re-throw the exception */
  if (error_id) {
    return env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, FILE_NAME, __LINE__);
  }
  
  /* Get the basic type of the method */
  void* basic_type = env->api->method->get_current_basic_type(env->runtime, current_method);
  
  /* Get the basic type name */
  const char* basic_type_name = env->api->basic_type->get_name(env->runtime, basic_type);
  
  /* Create a new SPVM string object using new_string_nolen */
  void* obj_basic_type_name = env->new_string_nolen(env, stack, basic_type_name);
  
  stack[0].oval = obj_basic_type_name;
  
  return 0;
}

int32_t SPVM__Fn__build_exception_message(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  /* Get the level argument from stack[0] */
  int32_t level = stack[0].ival;
  
  /* Adjustment for the current call:
     Since SPVM__Fn__build_exception_message itself is a method call, 
     we need to increment the level by 1 to skip this method and start 
     the stack trace from the actual caller's perspective.
  */
  int32_t adjusted_level = level + 1;
  
  /* Call the Native API with the adjusted level */
  void* obj_message = env->build_exception_message(env, stack, adjusted_level);
  
  /* Set the result to stack[0] */
  stack[0].oval = obj_message;
  
  return 0;
}

int32_t SPVM__Fn__get_call_depth(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  /* Get the raw call depth from the runtime via Native API.
     This includes the current call to SPVM__Fn__get_call_depth itself.
  */
  int32_t raw_depth = env->get_call_depth(env, stack);
  
  /* Adjustment:
     Subtract 1 to skip the current 'get_call_depth' method itself,
     providing the depth from the caller's perspective.
  */
  int32_t adjusted_depth = raw_depth - 1;
  
  /* Safety check to ensure depth is not negative */
  if (adjusted_depth < 0) {
    adjusted_depth = 0;
  }
  
  stack[0].ival = adjusted_depth;
  
  return 0;
}

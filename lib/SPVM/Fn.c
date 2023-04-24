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
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MAX;
  
  return 0;
}

int32_t SPVM__Fn__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MIN;
  
  return 0;
}

int32_t SPVM__Fn__DOUBLE_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MAX;
  
  return 0;
}

int32_t SPVM__Fn__DOUBLE_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MIN;
  
  return 0;
}

int32_t SPVM__Fn__FLOAT_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MAX;
  
  return 0;
}

int32_t SPVM__Fn__FLOAT_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MIN;
  
  return 0;
}

int32_t SPVM__Fn__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MAX;
  
  return 0;
}

int32_t SPVM__Fn__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
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
  (void)env;
  
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
  
  int32_t random_value = SPVM__Fn__static__rand_r(seed_ref);
  
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
  (void)env;
  
  void* obj_string = stack[0].oval;
  int32_t* offset_ref = stack[1].iref;

  if (!obj_string) {
    return env->die(env, stack, "The $string must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(*offset_ref >= 0)) {
    return env->die(env, stack, "The $offset must be greater than or equal to 0", __func__, FILE_NAME, __LINE__);
  }
  
  const char* string = env->get_chars(env, stack, obj_string);
  int32_t string_len = env->length(env, stack, obj_string);
  
  if (!(*offset_ref < string_len)) {
    // GET_CODE_POINT_ERROR_OVER_STRING_RANGE
    stack[0].ival = -1;
    return 0;
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
    // GET_CODE_POINT_ERROR_INVALID_UTF8
    uchar = -2;
  }
  else {
    assert(0);
  }
  
  stack[0].ival = uchar;
  
  return 0;
}

int32_t SPVM__Fn__is_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
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
  (void)env;
  
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
  (void)env;
  
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
  (void)env;
  
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
  (void)env;
  
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
  (void)env;
  
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
  int32_t obj_dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t obj_source_offset = stack[3].ival;
  int32_t length = stack[4].ival;
  
  if (!obj_dest) {
    return env->die(env, stack, "The $dest must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(env->is_string(env, stack, obj_dest) || env->is_numeric_array(env, stack, obj_dest) || env->is_mulnum_array(env, stack, obj_dest))) {
    return env->die(env, stack, "The $type of the $dest must be the $string type, the $numeric array type, or the $multi numeric array type", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The $source must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(env->is_string(env, stack, obj_source) || env->is_numeric_array(env, stack, obj_source) || env->is_mulnum_array(env, stack, obj_source))) {
    return env->die(env, stack, "The $type of the $source must be the $string type, the $numeric array type, or the $multi numeric array type", __func__, FILE_NAME, __LINE__);
  }
  
  if (env->is_read_only(env, stack, obj_dest)) {
    return env->die(env, stack, "The $dest cannnot be be a read-only string", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The $length must be greater than or equal to 0", __func__, FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  char* dest = (char*)env->get_chars(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  int32_t dest_elem_size = env->get_elem_size(env, stack, obj_dest);
  int32_t dest_byte_length = dest_elem_size * dest_length;
  
  if (!(obj_dest_offset + length <= dest_byte_length)) {
    return env->die(env, stack, "The $offset of the $obj_dest + the $length must be less than or equal to the length of the $obj_dest", __func__, FILE_NAME, __LINE__);
  }
  
  const char* source = env->get_chars(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  int32_t source_elem_size = env->get_elem_size(env, stack, obj_source);
  int32_t source_byte_length = source_elem_size * source_length;
  
  if (!(obj_source_offset + length <= source_byte_length)) {
    return env->die(env, stack, "The $offset of the $obj_source + the $length must be less than or equal to the length of the $obj_source", __func__, FILE_NAME, __LINE__);
  }
  
  memcpy((char*)(dest + obj_dest_offset), (char*)(source + obj_source_offset), length);
  
  return 0;
}

int32_t SPVM__Fn__memmove(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dest = stack[0].oval;
  int32_t obj_dest_offset = stack[1].ival;
  void* obj_source = stack[2].oval;
  int32_t obj_source_offset = stack[3].ival;
  int32_t length = stack[4].ival;

  if (!obj_dest) {
    return env->die(env, stack, "The $dest must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(env->is_string(env, stack, obj_dest) || env->is_numeric_array(env, stack, obj_dest) || env->is_mulnum_array(env, stack, obj_dest))) {
    return env->die(env, stack, "The $type of the $dest must be the $string type, the $numeric array type, or the $multi numeric array type", __func__, FILE_NAME, __LINE__);
  }
  
  if (!obj_source) {
    return env->die(env, stack, "The $source must be defined", __func__, FILE_NAME, __LINE__);
  }

  if (!(env->is_string(env, stack, obj_source) || env->is_numeric_array(env, stack, obj_source) || env->is_mulnum_array(env, stack, obj_source))) {
    return env->die(env, stack, "The $type of the $source must be the $string type, the $numeric array type, or the $multi numeric array type", __func__, FILE_NAME, __LINE__);
  }

  if (env->is_read_only(env, stack, obj_dest)) {
    return env->die(env, stack, "The $dest must not be a read-only string", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The $length must be greater than or equal to 0", __func__, FILE_NAME, __LINE__);
  }
  
  if (length == 0) {
    return 0;
  }
  
  char* dest = (char*)env->get_chars(env, stack, obj_dest);
  int32_t dest_length = env->length(env, stack, obj_dest);
  int32_t dest_elem_size = env->get_elem_size(env, stack, obj_dest);
  int32_t dest_byte_length = dest_elem_size * dest_length;
  
  if (!(obj_dest_offset + length <= dest_byte_length)) {
    return env->die(env, stack, "The $offset of the $obj_dest + the $length must be less than or equal to the length of the $obj_dest", __func__, FILE_NAME, __LINE__);
  }
  
  const char* source = env->get_chars(env, stack, obj_source);
  int32_t source_length = env->length(env, stack, obj_source);
  int32_t source_elem_size = env->get_elem_size(env, stack, obj_source);
  int32_t source_byte_length = source_elem_size * source_length;
  
  if (!(obj_source_offset + length <= source_byte_length)) {
    return env->die(env, stack, "The $offset of the $obj_source + the $length must be less than or equal to the length of the $obj_source", __func__, FILE_NAME, __LINE__);
  }
  
  memmove((char*)(dest + obj_dest_offset), (char*)(source + obj_source_offset), length);
  
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
  (void)env;
  
  void* string = stack[0].oval;
  int32_t length = stack[1].ival;
  
  if (!string) {
    return env->die(env, stack, "The $string must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The $length must be greater than or equal to 0", __func__, FILE_NAME, __LINE__);
  }
  
  env->shorten(env, stack, string, length);
  
  return 0;
}

int32_t SPVM__Fn__to_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  
  if (!obj_string) {
    return env->die(env, stack, "The $string must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  const char* string = env->get_chars(env, stack, obj_string);
  
  char *end;
  errno = 0;
  double num = strtod(string, &end);
  if (*end != '\0') {
    return env->die(env, stack, "The $string must be the string that can be parsed as a double number", __func__, FILE_NAME, __LINE__);
  }
  else if (errno == ERANGE) {
    return env->die(env, stack, "The $string must be a double number in the $correct range", __func__, FILE_NAME, __LINE__);
  }
  
  stack[0].dval = num;
  
  return 0;
}

int32_t SPVM__Fn__to_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  
  if (!obj_string) {
    return env->die(env, stack, "The $string must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  const char* string = env->get_chars(env, stack, obj_string);
  
  char *end;
  errno = 0;
  float num = strtof(string, &end);
  if (*end != '\0') {
    return env->die(env, stack, "The $string must be the string that can be parsed as a float number", __func__, FILE_NAME, __LINE__);
  }
  else if (errno == ERANGE) {
    return env->die(env, stack, "The $string must be a float number in the $correct range", __func__, FILE_NAME, __LINE__);
  }
  
  stack[0].fval = num;
  
  return 0;
}

int32_t SPVM__Fn__to_int_with_base(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  int32_t digit = stack[1].ival;
  
  if (!obj_string) {
    return env->die(env, stack, "The $string must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(digit == 2 || digit == 8 || digit == 10 || digit == 16)) {
    return env->die(env, stack, "The $digit must be one of 2, 8, 10, or 16", __func__, FILE_NAME, __LINE__);
  }
  
  const char* string = env->get_chars(env, stack, obj_string);
  
  char *end;
  errno = 0;
  int64_t num = strtol(string, &end, digit);
  if (*end != '\0') {
    return env->die(env, stack, "The $string must be the string that can be parsed as a %d-digit 32-bit integer", digit, __func__, FILE_NAME, __LINE__);
  }
  else if (errno == ERANGE || num < INT32_MIN || num > INT32_MAX) {
    return env->die(env, stack, "The $string must be a 32-bit integer in the $correct range", __func__, FILE_NAME, __LINE__);
  }
  
  stack[0].ival = (int32_t)num;
  
  return 0;
}

int32_t SPVM__Fn__to_long_with_base(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  int32_t digit = stack[1].ival;
  
  if (!obj_string) {
    return env->die(env, stack, "The $string must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(digit == 2 || digit == 8 || digit == 10 || digit == 16)) {
    return env->die(env, stack, "The $digit must be one of 2, 8, 10, or 16", __func__, FILE_NAME, __LINE__);
  }
  
  const char* string = env->get_chars(env, stack, obj_string);
  
  char *end;
  errno = 0;
  int64_t num = strtoll(string, &end, digit);
  if (*end != '\0') {
    return env->die(env, stack, "The $string must be the string that can be parsed as a %d-digit 64-bit integer", digit, __func__, FILE_NAME, __LINE__);
  }
  else if (errno == ERANGE) {
    return env->die(env, stack, "The $string must be a 64-bit integer in the $correct range", __func__, FILE_NAME, __LINE__);
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
  void* obj_class_name = stack[0].oval;
  
  if (!obj_class_name) {
    return env->die(env, stack, "The $class_name must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  const char* class_name = env->get_chars(env, stack, obj_class_name);
  
  int32_t class_id = env->get_class_id(env, stack, class_name);
  if (class_id < 0) {
    return env->die(env, stack, "The class specified by the $class_name must be loaded", __func__, FILE_NAME, __LINE__);
  }
  
  const char* version_string = env->get_version_string(env, stack, class_id);
  
  void* obj_version_string = NULL;
  if (version_string) {
    obj_version_string = env->new_string(env, stack, version_string, strlen(version_string));
  }
  
  stack[0].oval = obj_version_string;
  
  return 0;
}

int32_t SPVM__Fn__get_version_number(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_class_name = stack[0].oval;
  
  if (!obj_class_name) {
    return env->die(env, stack, "The $class_name must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  const char* class_name = env->get_chars(env, stack, obj_class_name);
  
  int32_t class_id = env->get_class_id(env, stack, class_name);
  if (class_id < 0) {
    return env->die(env, stack, "The class specified by the $class_name must be loaded", __func__, FILE_NAME, __LINE__);
  }
  
  double version_number = env->get_version_number(env, stack, class_id);
  
  stack[0].dval = version_number;
  
  return 0;
}

int32_t SPVM__Fn__get_spvm_version(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* spvm_version = env->get_spvm_version(env, stack);
  
  void* obj_spvm_version = env->new_string(env, stack, spvm_version, strlen(spvm_version));
  
  stack[0].oval = obj_spvm_version;
  
  return 0;
}

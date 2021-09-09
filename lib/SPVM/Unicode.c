#include "spvm_native.h"

#include "utf8proc.h"

const char* MFILE = "SPVM/Unicode.c";

int32_t SPVM__Unicode__uchar(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  void* obj_str = stack[0].oval;
  
  const char* str = env->get_chars(env, obj_str);
  int32_t str_len = env->length(env, obj_str);
  
  int32_t* offset_ref = stack[1].iref;
  
  if (*offset_ref < 0 || *offset_ref > str_len - 1) {
    stack[0].ival = -1;
    return 0;
  }
  
  utf8proc_int32_t dst;
  int32_t uchar_len = (int32_t)utf8proc_iterate((const utf8proc_uint8_t*)(str + *offset_ref), str_len, &dst);

  int32_t uchar;
  if (uchar_len > 0) {
    uchar = dst;
    *offset_ref += uchar_len;
  }
  else if (uchar_len == 0) {
    uchar = -1;
  }
  else if (uchar_len == UTF8PROC_ERROR_INVALIDUTF8) {
    uchar = -2;
  }
  
  stack[0].ival = uchar;
  
  return 0;
}

int32_t SPVM__Unicode__uchar_to_utf8(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t uchar = stack[0].ival;
  
  char tmp_utf8_bytes[4];
  int32_t utf8_len = (int32_t)utf8proc_encode_char((utf8proc_int32_t)uchar, (utf8proc_uint8_t*)tmp_utf8_bytes);
  
  if (utf8_len == 0) {
    stack[0].oval = NULL;
    return 0;
  }
  
  void* obj_utf8_bytes = env->new_byte_array(env, utf8_len);
  
  int8_t* utf8_bytes = env->get_elems_byte(env, obj_utf8_bytes);
  memcpy((char*)utf8_bytes, tmp_utf8_bytes, utf8_len);
  
  void* utf8_string = env->new_string(env, (char*)utf8_bytes, utf8_len);
  
  stack[0].oval = utf8_string;
  
  return 0;
}

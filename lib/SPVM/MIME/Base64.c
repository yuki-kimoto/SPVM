#include "spvm_native.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
static const char base64chars[] =
   "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

#define XX      255     /* illegal base64 char */
#define EQ      254     /* padding */

static const unsigned char index_64[256] = {
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,62, XX,XX,XX,63,
    52,53,54,55, 56,57,58,59, 60,61,XX,XX, XX,EQ,XX,XX,
    XX, 0, 1, 2,  3, 4, 5, 6,  7, 8, 9,10, 11,12,13,14,
    15,16,17,18, 19,20,21,22, 23,24,25,XX, XX,XX,XX,XX,
    XX,26,27,28, 29,30,31,32, 33,34,35,36, 37,38,39,40,
    41,42,43,44, 45,46,47,48, 49,50,51,XX, XX,XX,XX,XX,
 
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
};

static const size_t max_input_length = 1000000;

size_t calc_encoded_length(size_t n) {
  return (((4 * n / 3) + 3) & ~3) + 1;
}

size_t calc_decoded_length(size_t n) {
  return (n * 3 + 3) / 4 + 10;
}

int32_t SPNATIVE__SPVM__MIME__Base64__encode_b64(SPVM_ENV *env, SPVM_VALUE *stack) {
  if (!stack[0].oval) {
    SPVM_CROAK("string must not be undef", "SPVM/MIME/Base64.c", __LINE__);
  }

  const char* input = (const char*)env->belems(env, stack[0].oval);
  const size_t length = strnlen(input, max_input_length);
  const size_t encoded_capacity = calc_encoded_length(length);
  
  void* obuffer = env->new_barray_raw(env, encoded_capacity + 1);
  env->inc_ref_count(env, obuffer);
  char* result = (char *)(env->belems(env, obuffer));
  size_t result_index = 0;

  for (size_t x = 0; x < length; x += 3) {
    uint32_t n = ((uint32_t)input[x]) << 16;
    if (x + 1 < length) {
      n += ((uint32_t)input[x + 1]) << 8;
    }
    if (x + 2 < length) {
      n += (uint8_t)input[x + 2];
    }

    uint8_t n0 = (uint8_t)(n >> 18) & 63;
    uint8_t n1 = (uint8_t)(n >> 12) & 63;
    uint8_t n2 = (uint8_t)(n >> 6) & 63;
    uint8_t n3 = (uint8_t)n & 63;

    if (result_index >= encoded_capacity) {    
      env->dec_ref_count(env, obuffer);  
      SPVM_CROAK("index is over than estimated encoded length", "SPVM/MIME/Base64.c", __LINE__);
    }
    result[result_index++] = base64chars[n0];
    if (result_index >= encoded_capacity) {
      env->dec_ref_count(env, obuffer);
      SPVM_CROAK("index is over than estimated encoded length", "SPVM/MIME/Base64.c", __LINE__);
    }
    result[result_index++] = base64chars[n1];

    if (x + 1 < length) {
      if (result_index >= encoded_capacity) {      
        env->dec_ref_count(env, obuffer);
        SPVM_CROAK("index is over than estimated encoded length", "SPVM/MIME/Base64.c", __LINE__);
      }
      result[result_index++] = base64chars[n2];
    }

    if (x + 2 < length) {
      if (result_index >= encoded_capacity) {
        env->dec_ref_count(env, obuffer);
        SPVM_CROAK("index is over than estimated encoded length", "SPVM/MIME/Base64.c", __LINE__);
      }
      result[result_index++] = base64chars[n3];
    }
  }

  size_t pad_count = length % 3;
  if (pad_count > 0) {
    for (; pad_count < 3; pad_count++) {
      if (result_index >= encoded_capacity) {
        return 1;
      }
      result[result_index++] = '=';
    }
  }
  if (result_index >= encoded_capacity) {
    env->dec_ref_count(env, obuffer);
    SPVM_CROAK("index is over than estimated encoded length", "SPVM/MIME/Base64.c", __LINE__);
  }

  const size_t encoded_length = result_index;
  result[encoded_length] = 0;

  void* oline = env->new_barray_raw(env, encoded_length);
  int8_t* line = env->belems(env, oline);
  memcpy(line, result, encoded_length);

  env->dec_ref_count(env, obuffer);
  stack[0].oval = oline;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__MIME__Base64__decode_b64(SPVM_ENV *env, SPVM_VALUE *stack) {
  if (!stack[0].oval) {
    SPVM_CROAK("string must not be undef", "SPVM/MIME/Base64.c", __LINE__);
  }

  const char* input = (const char*)env->belems(env, stack[0].oval);
  const size_t length = strnlen(input, max_input_length);
  size_t input_index = 0;
  uint32_t buf = 0;
  size_t buf_iter = 0;

  const size_t decoded_capacity = calc_decoded_length(length);
  void* obuffer = env->new_barray_raw(env, decoded_capacity + 1);
  env->inc_ref_count(env, obuffer);
  char* result = (char *)(env->belems(env, obuffer));
  size_t result_index = 0;

  while (input_index < length) {
    uint8_t c = index_64[(uint8_t)input[input_index++]];

    switch (c) {
    case XX:
      continue;
    case EQ:
      input_index = length;
      continue;
    default:
      buf = buf << 6 | c;
      buf_iter++;
      if (buf_iter == 4) {
        if (result_index + 3 > decoded_capacity) {
          SPVM_CROAK("index is over than estimated decoded length", "SPVM/MIME/Base64.c", __LINE__);
        }
        result[result_index++] = (buf >> 16) & 255;
        result[result_index++] = (buf >> 8) & 255;
        result[result_index++] = buf & 255;
        buf = buf_iter = 0;
      }
    }
  }

  if (buf_iter == 3) {
    if (result_index + 2 > decoded_capacity) {
      SPVM_CROAK("index is over than estimated decoded length", "SPVM/MIME/Base64.c", __LINE__);
    }
    result[result_index++] = (buf >> 10) & 255;
    result[result_index++] = (buf >> 2) & 255;
  } else if (buf_iter == 2) {
    if (result_index + 1 > decoded_capacity) {
      SPVM_CROAK("index is over than estimated decoded length", "SPVM/MIME/Base64.c", __LINE__);
    }
    result[result_index++] = (buf >> 4) & 255;
  }

  const size_t decoded_length = result_index;
  result[decoded_length] = 0;

  void* oline = env->new_barray_raw(env, decoded_length);
  int8_t* line = env->belems(env, oline);
  memcpy(line, result, decoded_length);

  env->dec_ref_count(env, obuffer);
  stack[0].oval = oline;

  return SPVM_SUCCESS;
}

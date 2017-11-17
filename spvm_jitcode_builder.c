#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#include "spvm_jitcode_builder.h"
#include "spvm_compiler.h"
#include "spvm_string_buffer.h"

void SPVM_JITCODE_BUILDER_build_jitcode(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(0);
  
  // API header
  SPVM_STRING_BUFFER_add(string_buffer, "#include <spvm_api.h>\n");
  
  // Operator macro
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_BYTE(x, y) ((int8_t)x + (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_SHORT(x, y) ((int16_t)x + (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_INT(x, y) ((int32_t)x + (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_LONG(x, y) ((int64_t)x + (int64_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_FLOAT(x, y) ((float)x + (float)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_DOUBLE(x, y) ((double)x + (double)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_BYTE(x, y) ((int8_t)x - (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_SHORT(x, y) ((int16_t)x - (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_INT(x, y) ((int32_t)x - (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_LONG(x, y) ((int64_t)x - (int64_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_FLOAT(x, y) ((float)x - (float)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_DOUBLE(x, y) ((double)x - (double)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_BYTE(x, y) ((int8_t)x * (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_SHORT(x, y) ((int16_t)x * (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_INT(x, y) ((int32_t)x * (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_LONG(x, y) ((int64_t)x * (int64_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_FLOAT(x, y) ((float)x * (float)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_DOUBLE(x, y) ((double)x * (double)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_BYTE(x, y) ((int8_t)x / (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_SHORT(x, y) ((int16_t)x / (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_INT(x, y) ((int32_t)x / (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_LONG(x, y) ((int64_t)x / (int64_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_FLOAT(x, y) ((float)x / (float)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_DOUBLE(x, y) ((double)x / (double)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_BYTE(x, y) ((int8_t)x % (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_SHORT(x, y) ((int16_t)x % (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_INT(x, y) ((int32_t)x % (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_LONG(x, y) ((int64_t)x % (int64_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_FLOAT(x, y) ((float)x % (float)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_DOUBLE(x, y) ((double)x % (double)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_LEFT_SHIFT_BYTE(x, y) ((int8_t)x << (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_LEFT_SHIFT_SHORT(x, y) ((int16_t)x << (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_LEFT_SHIFT_INT(x, y) ((int32_t)x << (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_LEFT_SHIFT_LONG(x, y) ((int64_t)x << (int32_t)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_BYTE(x, y) ((int8_t)x >> (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_SHORT(x, y) ((int16_t)x >> (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_INT(x, y) ((int32_t)x >> (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_LONG(x, y) ((int64_t)x >> (int32_t)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_UNSIGNED_BYTE(x, y) ((int8_t)((uint8_t)x >> (int32_t)y))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_UNSIGNED_SHORT(x, y) ((int16_t)((uint16_t)x >> (int32_t)y))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_UNSIGNED_INT(x, y) ((int32_t)((uint32_t)x >> (int32_t)y))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_UNSIGNED_LONG(x, y) ((int64_t)((uint64_t)x >> (int32_t)y))\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_AND_BYTE(x, y) ((int8_t)x & (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_AND_SHORT(x, y) ((int16_t)x & (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_AND_INT(x, y) ((int32_t)x & (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_AND_LONG(x, y) ((int64_t)x & (int64_t)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_OR_BYTE(x, y) ((int8_t)x | (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_OR_SHORT(x, y) ((int16_t)x | (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_OR_INT(x, y) ((int32_t)x | (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_OR_LONG(x, y) ((int64_t)x | (int64_t)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_XOR_BYTE(x, y) ((int8_t)x ^ (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_XOR_SHORT(x, y) ((int16_t)x ^ (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_XOR_INT(x, y) ((int32_t)x ^ (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_XOR_LONG(x, y) ((int64_t)x ^ (int64_t)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_AND(x, y) ((x) && (y))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_OR(x, y) ((x) || (y))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_NOT(x) (!(x))\n");
}

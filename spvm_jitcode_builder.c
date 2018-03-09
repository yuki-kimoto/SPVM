#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>

#include "spvm_jitcode_builder.h"
#include "spvm_string_buffer.h"
#include "spvm_sub.h"
#include "spvm_op.h"
#include "spvm_list.h"
#include "spvm_type.h"
#include "spvm_object.h"
#include "spvm_runtime.h"
#include "spvm_type.h"
#include "spvm_my.h"
#include "spvm_constant_pool.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_package.h"
#include "spvm_constant_pool_field.h"
#include "spvm_constant_pool_type.h"
#include "spvm_opcode.h"
#include "spvm_opcode_array.h"
#include "spvm_runtime_api.h"

#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_field.h"
#include "spvm_compiler.h"
#include "spvm_my.h"
#include "spvm_op.h"

void SPVM_JITCODE_BUILDER_add_var(SPVM_STRING_BUFFER* string_buffer, int32_t index) {
  SPVM_STRING_BUFFER_add(string_buffer, "vars[");
  SPVM_STRING_BUFFER_add_int(string_buffer, index);
  SPVM_STRING_BUFFER_add(string_buffer, "]");
}

void SPVM_JITCODE_BUILDER_add_operand(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t var_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)type_name);
  SPVM_STRING_BUFFER_add(string_buffer, "*)&");
  SPVM_JITCODE_BUILDER_add_var(string_buffer, var_index);
}

void SPVM_JITCODE_BUILDER_add_bool(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = !!");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_eq(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_JITCODE_BUILDER_add_ne(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " != ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_JITCODE_BUILDER_add_gt(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " > ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_JITCODE_BUILDER_add_ge(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >= ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_JITCODE_BUILDER_add_lt(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " < ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_JITCODE_BUILDER_add_le(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " <= ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_JITCODE_BUILDER_add_add(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " + ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_subtract(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " - ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_multiply(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " * ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_divide_integral(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->new_string(api, \"0 division\", 0));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");

  SPVM_STRING_BUFFER_add(string_buffer, "  } else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_JITCODE_BUILDER_add_divide_floating_point(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_remainder_integral(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* exception = api->new_string(api, \"0 division\", 0);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, exception);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " % /* REMAINDER */ "); // % have undarstandable bug.
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_JITCODE_BUILDER_add_left_shift(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " << (");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  if (strcmp(type_name, "SPVM_API_int") == 0) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x1f))");
  }
  else if (strcmp(type_name, "SPVM_API_long") == 0) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x3f))");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_right_shift_unsigned(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)type_name);
  SPVM_STRING_BUFFER_add(string_buffer, ")((u");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)type_name);
  SPVM_STRING_BUFFER_add(string_buffer, ")");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> (");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  if (strcmp(type_name, "int32_t") == 0) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x1f))");
  }
  else if (strcmp(type_name, "int64_t") == 0) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x3f))");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_JITCODE_BUILDER_add_right_shift(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> (");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  if (strcmp(type_name, "SPVM_API_int") == 0) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x1f))");
  }
  else if (strcmp(type_name, "SPVM_API_long") == 0) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x3f))");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_bit_and(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " & ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_bit_or(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " | ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_bit_xor(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " ^ ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_negate(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = -");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_plus(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_complement(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ~");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_inc(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t number) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " += ");
  SPVM_STRING_BUFFER_add_int(string_buffer, number);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_convert(SPVM_STRING_BUFFER* string_buffer, const char* out_type_name, const char* in_type_name, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, out_type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)out_type_name);
  SPVM_STRING_BUFFER_add(string_buffer, ")");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, in_type_name, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_load_constant_0(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = 0");
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_array_load(SPVM_STRING_BUFFER* string_buffer, const char* element_type_name, int32_t out_index, int32_t array_index, int32_t index_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", array_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      api->set_exception(api, api->new_string(api, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      croak_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", index_index);
  SPVM_STRING_BUFFER_add(string_buffer, " < 0 || ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", index_index);
  SPVM_STRING_BUFFER_add(string_buffer, "  >= *(int32_t*)((intptr_t)");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", array_index);
  SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_RUNTIME_C_OBJECT_LENGTH_BYTE_OFFSET), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        api->set_exception(api, api->new_string(api, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        croak_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, element_type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)element_type_name);
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", array_index);
  SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)element_type_name);
  SPVM_STRING_BUFFER_add(string_buffer, ") * ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", index_index);
  SPVM_STRING_BUFFER_add(string_buffer, "); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_JITCODE_BUILDER_add_array_store(SPVM_STRING_BUFFER* string_buffer, const char* element_type_name, int32_t array_index, int32_t index_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", array_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->new_string(api, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", index_index);
  SPVM_STRING_BUFFER_add(string_buffer, " < 0 || ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", index_index);
  SPVM_STRING_BUFFER_add(string_buffer, "  >= *(int32_t*)((intptr_t)");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", array_index);
  SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_RUNTIME_C_OBJECT_LENGTH_BYTE_OFFSET), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        api->set_exception(api, api->new_string(api, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        croak_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "      *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)element_type_name);
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", array_index);
  SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)element_type_name);
  SPVM_STRING_BUFFER_add(string_buffer, ") * ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ") = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, element_type_name, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_JITCODE_BUILDER_add_move(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_get_field(SPVM_STRING_BUFFER* string_buffer, const char* field_type_name, int32_t out_index, int32_t object_index, int32_t field_byte_offset) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", object_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->new_string(api, \"Object must be not undef.\", 0));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, field_type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_type_name);
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", object_index);
  SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + ");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_byte_offset);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_JITCODE_BUILDER_add_set_field(SPVM_STRING_BUFFER* string_buffer, const char* field_type_name, int32_t object_index, int32_t field_byte_offset, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", object_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->new_string(api, \"Object must be not undef.\", 0));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_type_name);
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", object_index);
  SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + ");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_byte_offset);
  SPVM_STRING_BUFFER_add(string_buffer, ") = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, field_type_name, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

char* SPVM_JITCODE_BUILDER_get_type_name(int32_t type_code) {
  
  switch (type_code ) {
    case SPVM_TYPE_C_CODE_VOID:
      assert(0);
      break;
    case SPVM_TYPE_C_CODE_BYTE:
      return "SPVM_API_byte";
      break;
    case SPVM_TYPE_C_CODE_SHORT:
      return "SPVM_API_short";
      break;
    case SPVM_TYPE_C_CODE_INT:
      return "SPVM_API_int";
      break;
    case SPVM_TYPE_C_CODE_LONG:
      return "SPVM_API_long";
      break;
    case SPVM_TYPE_C_CODE_FLOAT:
      return "SPVM_API_float";
      break;
    case SPVM_TYPE_C_CODE_DOUBLE:
      return "SPVM_API_double";
      break;
    default:
      return "SPVM_API_OBJECT*";
  }
}

void SPVM_JITCODE_BUILDER_build_sub_jitcode(SPVM_STRING_BUFFER* string_buffer, int32_t sub_id) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool
  int32_t* constant_pool = runtime->constant_pool;
  
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];

  // Subroutine return type id
  int32_t sub_return_type_id = constant_pool_sub->return_type_id;
  
  // Subroutine return type
  SPVM_CONSTANT_POOL_TYPE* sub_return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[sub_return_type_id];
  
  // Subroutine return type code
  int32_t sub_return_type_code = sub_return_type->code;

  assert(!constant_pool_sub->is_native);
  
  // Include header
  SPVM_STRING_BUFFER_add(string_buffer, "#ifndef SPVM_JITCODE_BUILDER_H\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_BUILDER_H\n");
  
  // API header
  SPVM_STRING_BUFFER_add(string_buffer, "#include <spvm_api.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Constant macro
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_NULL 0\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE ");
  SPVM_STRING_BUFFER_add_int(string_buffer, SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE);
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_OBJECT_LENGTH_BYTE_OFFSET ");
  SPVM_STRING_BUFFER_add_int(string_buffer, SPVM_RUNTIME_C_OBJECT_LENGTH_BYTE_OFFSET);
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_OBJECT_REF_COUNT_BYTE_OFFSET ");
  SPVM_STRING_BUFFER_add_int(string_buffer, SPVM_RUNTIME_C_OBJECT_REF_COUNT_BYTE_OFFSET);
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_RUNTIME_EXCEPTION_BYTE_OFFSET ");
  SPVM_STRING_BUFFER_add_int(string_buffer, SPVM_RUNTIME_C_RUNTIME_EXCEPTION_BYTE_OFFSET);
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Inline macro function
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_REF_COUNT_BYTE_OFFSET)))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_REF_COUNT_BYTE_OFFSET))++)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_REF_COUNT_BYTE_OFFSET))--)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_ISWEAK(object) ((intptr_t)object & 1)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#endif\n");
  
  int32_t sub_abs_name_id = constant_pool_sub->abs_name_id;
  
  // Subroutine name
  const char* sub_abs_name = (char*)&constant_pool[sub_abs_name_id + 1];

  // Arguments length
  int32_t args_length = constant_pool_sub->args_length;
  
  // Arguments type ids base
  int32_t arg_type_ids_base = constant_pool_sub->arg_type_ids_base;

  // Return type code
  int32_t return_type_id = constant_pool_sub->return_type_id;
  SPVM_CONSTANT_POOL_TYPE* return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[return_type_id];
  int32_t return_type_code = return_type->code;
  
  // Return type
  switch (return_type->code) {
    case SPVM_TYPE_C_CODE_VOID:
      SPVM_STRING_BUFFER_add(string_buffer, "void ");
      break;
    case SPVM_TYPE_C_CODE_BYTE:
      SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_byte ");
      break;
    case SPVM_TYPE_C_CODE_SHORT:
      SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_short ");
      break;
    case SPVM_TYPE_C_CODE_INT:
      SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_int ");
      break;
    case SPVM_TYPE_C_CODE_LONG:
      SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_long ");
      break;
    case SPVM_TYPE_C_CODE_FLOAT:
      SPVM_STRING_BUFFER_add(string_buffer, "float ");
      break;
    case SPVM_TYPE_C_CODE_DOUBLE:
      SPVM_STRING_BUFFER_add(string_buffer, "double ");
      break;
    default:
      SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_OBJECT* ");
  }

  // Subroutine name. Replace : to _
  SPVM_STRING_BUFFER_add(string_buffer, "SPVM_JITCODE_");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_abs_name);
  {
    int32_t index = string_buffer->length - strlen(sub_abs_name);
    
    while (index < string_buffer->length) {
      if (string_buffer->buffer[index] == ':') {
        string_buffer->buffer[index] = '_';
      }
      index++;
    }
  }

  // Arguments
  SPVM_STRING_BUFFER_add(string_buffer, "(SPVM_API* api, SPVM_API_VALUE* args)");
  
  // Block start
  SPVM_STRING_BUFFER_add(string_buffer, " {\n");
  
  // Variables
  if (constant_pool_sub->mys_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_VALUE vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, constant_pool_sub->mys_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }
  
  if (constant_pool_sub->auto_dec_ref_count_stack_max_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_VALUE auto_dec_ref_count_stack[");
    SPVM_STRING_BUFFER_add_int(string_buffer, constant_pool_sub->auto_dec_ref_count_stack_max_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t auto_dec_ref_count_stack_top = -1;\n");
  }
  
  if (constant_pool_sub->call_sub_arg_stack_max > 0 ) {
    SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_VALUE call_sub_args[");
    SPVM_STRING_BUFFER_add_int(string_buffer, constant_pool_sub->call_sub_arg_stack_max);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }
  
  // Call subroutine argument stack top
  SPVM_STRING_BUFFER_add(string_buffer, "int32_t call_sub_arg_stack_top = -1;\n");
  
  // Copy arguments to variables
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < args_length; arg_index++) {
      int32_t arg_type_id = constant_pool[arg_type_ids_base + arg_index];

      // Argument type code
      SPVM_CONSTANT_POOL_TYPE* constant_pool_arg_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[arg_type_id];
      int32_t arg_type_code = constant_pool_arg_type->code;
      const char* arg_type_name = SPVM_JITCODE_BUILDER_get_type_name(arg_type_code);

      // Assign argument
      SPVM_STRING_BUFFER_add(string_buffer, "  ");
      SPVM_JITCODE_BUILDER_add_operand(string_buffer, arg_type_name, arg_index);
      SPVM_STRING_BUFFER_add(string_buffer, " = ");
      SPVM_STRING_BUFFER_add(string_buffer, "*(");
      SPVM_STRING_BUFFER_add(string_buffer, SPVM_JITCODE_BUILDER_get_type_name(arg_type_code));
      SPVM_STRING_BUFFER_add(string_buffer, "*)&args[");
      SPVM_STRING_BUFFER_add_int(string_buffer, arg_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      
      SPVM_STRING_BUFFER_add(string_buffer, ";\n");
    }
  }
  
  // If arg is object, increment reference count
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < args_length; arg_index++) {
      int32_t arg_type_id = constant_pool[arg_type_ids_base + arg_index];

      // Argument type code
      SPVM_CONSTANT_POOL_TYPE* constant_pool_arg_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[arg_type_id];
      
      if (!constant_pool_arg_type->is_numeric) {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", arg_index);
        SPVM_STRING_BUFFER_add(string_buffer, " != SPVM_RUNTIME_C_NULL) { SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", arg_index);
        SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
  }
  
  // Condition flag
  SPVM_STRING_BUFFER_add(string_buffer, "  register int32_t condition_flag;\n");
  
  // Return value
  if (sub_return_type_code != SPVM_TYPE_C_CODE_VOID) {
    SPVM_STRING_BUFFER_add(string_buffer, "  ");
    switch (return_type_code) {
      case SPVM_TYPE_C_CODE_BYTE : {
        SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_byte");
        break;
      }
      case  SPVM_TYPE_C_CODE_SHORT : {
        SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_short");
        break;
      }
      case  SPVM_TYPE_C_CODE_INT : {
        SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_int");
        break;
      }
      case  SPVM_TYPE_C_CODE_LONG : {
        SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_long");
        break;
      }
      case  SPVM_TYPE_C_CODE_FLOAT : {
        SPVM_STRING_BUFFER_add(string_buffer, "float");
        break;
      }
      case  SPVM_TYPE_C_CODE_DOUBLE : {
        SPVM_STRING_BUFFER_add(string_buffer, "double");
        break;
      }
      default : {
        SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_OBJECT*");
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, " return_value;\n");
  }
  
  // Exception
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t croak_flag = 0;\n");
  
  SPVM_OPCODE* opcodes = runtime->opcodes;
  int32_t opcode_base = constant_pool_sub->opcode_base;
  int32_t opcode_length = constant_pool_sub->opcode_length;
  int32_t opcode_index = opcode_base;
  
  SPVM_OPCODE* opcode = NULL;
  while (opcode_index < opcode_base + opcode_length) {

    // Line label
    SPVM_STRING_BUFFER_add(string_buffer, "L");
    SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index);
    SPVM_STRING_BUFFER_add(string_buffer, ": ");
    
    opcode = &(opcodes[opcode_index]);

    SPVM_STRING_BUFFER_add(string_buffer, "// ");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_OPCODE_C_CODE_NAMES[opcode->code]);
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
    
    switch (opcode->code) {
      case SPVM_OPCODE_C_CODE_NOP:
        abort();
      case SPVM_OPCODE_C_CODE_BOOL_INT:
        SPVM_JITCODE_BUILDER_add_bool(string_buffer, "SPVM_API_int", opcode->operand0);
        break;
      case SPVM_OPCODE_C_CODE_BOOL_LONG:
        SPVM_JITCODE_BUILDER_add_bool(string_buffer, "SPVM_API_long", opcode->operand0);
        break;
      case SPVM_OPCODE_C_CODE_BOOL_FLOAT:
        SPVM_JITCODE_BUILDER_add_bool(string_buffer, "float", opcode->operand0);
        break;
      case SPVM_OPCODE_C_CODE_BOOL_DOUBLE:
        SPVM_JITCODE_BUILDER_add_bool(string_buffer, "double", opcode->operand0);
        break;
      case SPVM_OPCODE_C_CODE_BOOL_OBJECT:
        SPVM_JITCODE_BUILDER_add_bool(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        break;
      case SPVM_OPCODE_C_CODE_IS_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL);\n");
        break;
      case SPVM_OPCODE_C_CODE_IS_NOT_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " != SPVM_RUNTIME_C_NULL);\n");
        break;
      case SPVM_OPCODE_C_CODE_EQ_INT:
        SPVM_JITCODE_BUILDER_add_eq(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_EQ_LONG:
        SPVM_JITCODE_BUILDER_add_eq(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_EQ_FLOAT:
        SPVM_JITCODE_BUILDER_add_eq(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_EQ_DOUBLE:
        SPVM_JITCODE_BUILDER_add_eq(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_EQ_OBJECT:
        SPVM_JITCODE_BUILDER_add_eq(string_buffer, "SPVM_API_OBJECT*", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_NE_INT:
        SPVM_JITCODE_BUILDER_add_ne(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_NE_LONG:
        SPVM_JITCODE_BUILDER_add_ne(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_NE_FLOAT:
        SPVM_JITCODE_BUILDER_add_ne(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_NE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_ne(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_NE_OBJECT:
        SPVM_JITCODE_BUILDER_add_ne(string_buffer, "SPVM_API_OBJECT*", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_GT_INT:
        SPVM_JITCODE_BUILDER_add_gt(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_GT_LONG:
        SPVM_JITCODE_BUILDER_add_gt(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_GT_FLOAT:
        SPVM_JITCODE_BUILDER_add_gt(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_GT_DOUBLE:
        SPVM_JITCODE_BUILDER_add_gt(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_GE_INT:
        SPVM_JITCODE_BUILDER_add_ge(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_GE_LONG:
        SPVM_JITCODE_BUILDER_add_ge(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_GE_FLOAT:
        SPVM_JITCODE_BUILDER_add_ge(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_GE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_ge(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_LT_INT:
        SPVM_JITCODE_BUILDER_add_lt(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_LT_LONG:
        SPVM_JITCODE_BUILDER_add_lt(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_LT_FLOAT:
        SPVM_JITCODE_BUILDER_add_lt(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_LT_DOUBLE:
        SPVM_JITCODE_BUILDER_add_lt(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_LE_INT:
        SPVM_JITCODE_BUILDER_add_le(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_LE_LONG:
        SPVM_JITCODE_BUILDER_add_le(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_LE_FLOAT:
        SPVM_JITCODE_BUILDER_add_le(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_LE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_le(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_ADD_INT:
        SPVM_JITCODE_BUILDER_add_add(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ADD_LONG:
        SPVM_JITCODE_BUILDER_add_add(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ADD_FLOAT:
        SPVM_JITCODE_BUILDER_add_add(string_buffer, "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ADD_DOUBLE:
        SPVM_JITCODE_BUILDER_add_add(string_buffer, "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_INT:
        SPVM_JITCODE_BUILDER_add_subtract(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_LONG:
        SPVM_JITCODE_BUILDER_add_subtract(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_FLOAT:
        SPVM_JITCODE_BUILDER_add_subtract(string_buffer, "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_DOUBLE:
        SPVM_JITCODE_BUILDER_add_subtract(string_buffer, "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_INT:
        SPVM_JITCODE_BUILDER_add_multiply(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_LONG:
        SPVM_JITCODE_BUILDER_add_multiply(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_FLOAT:
        SPVM_JITCODE_BUILDER_add_multiply(string_buffer, "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_DOUBLE:
        SPVM_JITCODE_BUILDER_add_multiply(string_buffer, "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_INT:
        SPVM_JITCODE_BUILDER_add_divide_integral(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_LONG: 
        SPVM_JITCODE_BUILDER_add_divide_integral(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_FLOAT:
        SPVM_JITCODE_BUILDER_add_divide_floating_point(string_buffer, "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_divide_floating_point(string_buffer, "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_INT:
        SPVM_JITCODE_BUILDER_add_remainder_integral(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_LONG: 
        SPVM_JITCODE_BUILDER_add_remainder_integral(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_FLOAT:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "float", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = (float)fmod((double)");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "float", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", (double)");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "float", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_DOUBLE:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "double", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = fmod(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "double", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "double", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_CODE_LEFT_SHIFT_INT:
        SPVM_JITCODE_BUILDER_add_left_shift(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_LEFT_SHIFT_LONG:
        SPVM_JITCODE_BUILDER_add_left_shift(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_INT:
        SPVM_JITCODE_BUILDER_add_right_shift(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_LONG:
        SPVM_JITCODE_BUILDER_add_right_shift(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
        SPVM_JITCODE_BUILDER_add_right_shift_unsigned(string_buffer, "int32_t", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
        SPVM_JITCODE_BUILDER_add_right_shift_unsigned(string_buffer, "int64_t", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_BIT_AND_INT:
        SPVM_JITCODE_BUILDER_add_bit_and(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_BIT_AND_LONG:
        SPVM_JITCODE_BUILDER_add_bit_and(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_BIT_OR_INT:
        SPVM_JITCODE_BUILDER_add_bit_or(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_BIT_OR_LONG:
        SPVM_JITCODE_BUILDER_add_bit_or(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_BIT_XOR_INT:
        SPVM_JITCODE_BUILDER_add_bit_xor(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_BIT_XOR_LONG:
        SPVM_JITCODE_BUILDER_add_bit_xor(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_PLUS_INT:
        SPVM_JITCODE_BUILDER_add_plus(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_PLUS_LONG:
        SPVM_JITCODE_BUILDER_add_plus(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_PLUS_FLOAT:
        SPVM_JITCODE_BUILDER_add_plus(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_PLUS_DOUBLE:
        SPVM_JITCODE_BUILDER_add_plus(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_INT:
        SPVM_JITCODE_BUILDER_add_negate(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_LONG:
        SPVM_JITCODE_BUILDER_add_negate(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_FLOAT:
        SPVM_JITCODE_BUILDER_add_negate(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_negate(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_COMPLEMENT_INT:
        SPVM_JITCODE_BUILDER_add_complement(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_COMPLEMENT_LONG:
        SPVM_JITCODE_BUILDER_add_complement(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_BYTE:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_SHORT:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_INT:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_LONG:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_FLOAT:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_DOUBLE:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_BYTE_0:
        SPVM_JITCODE_BUILDER_add_load_constant_0(string_buffer, "SPVM_API_byte", opcode->operand0);
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_SHORT_0:
        SPVM_JITCODE_BUILDER_add_load_constant_0(string_buffer, "SPVM_API_short", opcode->operand0);
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_INT_0:
        SPVM_JITCODE_BUILDER_add_load_constant_0(string_buffer, "SPVM_API_int", opcode->operand0);
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_LONG_0:
        SPVM_JITCODE_BUILDER_add_load_constant_0(string_buffer, "SPVM_API_long", opcode->operand0);
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_FLOAT_0:
        SPVM_JITCODE_BUILDER_add_load_constant_0(string_buffer, "SPVM_API_float", opcode->operand0);
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_DOUBLE_0: {
        SPVM_JITCODE_BUILDER_add_load_constant_0(string_buffer, "SPVM_API_double", opcode->operand0);
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_byte", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_byte(string_buffer, *(SPVM_API_byte*)&constant_pool[opcode->operand1]);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_short", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_short(string_buffer, *(SPVM_API_short*)&constant_pool[opcode->operand1]);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, *(SPVM_API_int*)&constant_pool[opcode->operand1]);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_long", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_long(string_buffer, *(SPVM_API_long*)&constant_pool[opcode->operand1]);
        SPVM_STRING_BUFFER_add(string_buffer, "UL;\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_float", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_float(string_buffer, *(SPVM_API_float*)&constant_pool[opcode->operand1]);
        SPVM_STRING_BUFFER_add(string_buffer, "f;\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_double", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_double(string_buffer, *(SPVM_API_double*)&constant_pool[opcode->operand1]);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = SPVM_RUNTIME_C_NULL;\n");
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_BYTE:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_SHORT:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_INT:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_LONG:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_FLOAT:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_DOUBLE:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_OBJECT:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_OBJECT*", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_BYTE:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_SHORT:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_INT:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_LONG:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_FLOAT:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_OBJECT:
      {
        char* element_type_name = "SPVM_API_OBJECT*";
        
        SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->new_string(api, \"Array must not be undef\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "  else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0 || ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "  >= *(int32_t*)((intptr_t)");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_RUNTIME_C_OBJECT_LENGTH_BYTE_OFFSET), 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        api->set_exception(api, api->new_string(api, \"Index is out of range\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT** object_address = (SPVM_API_OBJECT**)((intptr_t)");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(void*) * ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (*object_address != SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*object_address) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*object_address); }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        else { api->dec_ref_count(api, *object_address); }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "      *object_address = ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, (char*)element_type_name, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "      if (*object_address != SPVM_RUNTIME_C_NULL) { SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(*object_address); }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_MOVE_BYTE:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_MOVE_SHORT:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_MOVE_INT:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_MOVE_LONG:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_MOVE_FLOAT:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_MOVE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_MOVE_OBJECT:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_OBJECT*", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_REF_COUNT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " != SPVM_RUNTIME_C_NULL) { SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_DEC_REF_COUNT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " != SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ") > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { api->dec_ref_count(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_PUSH_AUTO_DEC_REF_COUNT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  auto_dec_ref_count_stack_top++;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  *(int32_t*)&auto_dec_ref_count_stack[auto_dec_ref_count_stack_top] = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_LEAVE_SCOPE: {
        if (constant_pool_sub->auto_dec_ref_count_stack_max_length > 0) {
          SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    int32_t auto_dec_ref_count_stack_current_base = ");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      int32_t auto_dec_ref_count_index;\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      for (auto_dec_ref_count_index = auto_dec_ref_count_stack_current_base; auto_dec_ref_count_index <= auto_dec_ref_count_stack_top; auto_dec_ref_count_index++) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        int32_t var_index = *(int32_t*)&auto_dec_ref_count_stack[auto_dec_ref_count_index];\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        if (*(SPVM_API_OBJECT**)&vars[var_index] != SPVM_RUNTIME_C_NULL) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "          if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(SPVM_API_OBJECT**)&vars[var_index]) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(SPVM_API_OBJECT**)&vars[var_index]); }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "          else { api->dec_ref_count(api, *(SPVM_API_OBJECT**)&vars[var_index]); }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    auto_dec_ref_count_stack_top = auto_dec_ref_count_stack_current_base - 1;\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->new_object(api, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_BYTE_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_byte_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_CODE_NEW_SHORT_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_short_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_CODE_NEW_INT_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_int_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_CODE_NEW_LONG_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_long_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_CODE_NEW_FLOAT_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_float_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_CODE_NEW_DOUBLE_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_double_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_CODE_NEW_OBJECT_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->new_object_array(api, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_STRING: {
        int32_t name_id = opcode->operand1;
        int32_t length = constant_pool[name_id];
        char* name = (char*)&constant_pool[name_id + 1];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->new_string(api, \"");
        
        {
          int32_t i;
          for (i = 0; i < length; i++) {
            SPVM_STRING_BUFFER_add_hex_char(string_buffer, name[i]);
          }
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "\", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, length);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LENGTH: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->new_string(api, \"Can't get array length of undef value.\", 0));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int32_t*)((intptr_t)");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_RUNTIME_C_OBJECT_LENGTH_BYTE_OFFSET);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_BYTE: {
        int32_t field_id = opcode->operand2;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, field_byte_offset);
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_SHORT: {
        int32_t field_id = opcode->operand2;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, field_byte_offset);
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_INT: {
        int32_t field_id = opcode->operand2;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, field_byte_offset);
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_LONG: {
        int32_t field_id = opcode->operand2;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, field_byte_offset);
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_FLOAT: {
        int32_t field_id = opcode->operand2;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_float", opcode->operand0, opcode->operand1, field_byte_offset);
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_DOUBLE: {
        int32_t field_id = opcode->operand2;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_double", opcode->operand0, opcode->operand1, field_byte_offset);
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_OBJECT: {
        int32_t field_id = opcode->operand2;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_OBJECT*", opcode->operand0, opcode->operand1, field_byte_offset);
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_BYTE: {
        int32_t field_id = opcode->operand1;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_byte", opcode->operand0, field_byte_offset, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_SHORT: {
        int32_t field_id = opcode->operand1;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_short", opcode->operand0, field_byte_offset, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_INT: {
        int32_t field_id = opcode->operand1;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_int", opcode->operand0, field_byte_offset, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_LONG: {
        int32_t field_id = opcode->operand1;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_long", opcode->operand0, field_byte_offset, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_FLOAT: {
        int32_t field_id = opcode->operand1;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_float", opcode->operand0, field_byte_offset, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_DOUBLE: {
        int32_t field_id = opcode->operand1;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_double", opcode->operand0, field_byte_offset, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_OBJECT:
      {
        int32_t field_id = opcode->operand1;
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->new_string(api, \"Object must be not undef.\", 0));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT** field_address = (SPVM_API_OBJECT**)((intptr_t)");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + ");
        SPVM_STRING_BUFFER_add_int(string_buffer, field_byte_offset);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if(*field_address != SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (SPVM_RUNTIME_C_INLINE_ISWEAK(*field_address)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        api->unweaken(api, field_address);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*field_address) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*field_address); }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else { api->dec_ref_count(api, *field_address); }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *field_address = ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, "  ;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if(*field_address != SPVM_RUNTIME_C_NULL) { SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(*field_address); }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_WEAKEN_FIELD_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  api->weaken_object_field(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (api->get_exception(api)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_STRING:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_string(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_BYTE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_byte(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_byte", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_SHORT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_short(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_short", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_INT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_int(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_LONG:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_long(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_long", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_FLOAT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_float(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_float", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_DOUBLE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_float(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_double", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_GOTO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_IF_EQ_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (condition_flag == 0) { goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "; }\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_IF_NE_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (condition_flag) { goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "; }\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "   = api->get_exception(api);\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  api->set_exception(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_BYTE:
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_SHORT:
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_INT:
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_LONG:
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_FLOAT:
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_DOUBLE:
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_OBJECT:
      {
        char* package_var_type = NULL;
        switch (opcode->code) {
          case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_BYTE:
            package_var_type = "SPVM_API_byte";
            break;
          case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_SHORT:
            package_var_type = "SPVM_API_short";
            break;
          case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_INT:
            package_var_type = "SPVM_API_int";
            break;
          case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_LONG:
            package_var_type = "SPVM_API_long";
            break;
          case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_FLOAT:
            package_var_type = "float";
            break;
          case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_DOUBLE:
            package_var_type = "double";
            break;
          case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_OBJECT:
            package_var_type = "SPVM_API_OBJECT*";
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, package_var_type, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(");
        SPVM_STRING_BUFFER_add(string_buffer, package_var_type);
        SPVM_STRING_BUFFER_add(string_buffer, "*)");
        SPVM_STRING_BUFFER_add(string_buffer, "&(*(SPVM_API_VALUE**)(api->get_runtime(api) + ");
        SPVM_STRING_BUFFER_add_int(string_buffer, offsetof(SPVM_RUNTIME, package_vars));
        SPVM_STRING_BUFFER_add(string_buffer, "))[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "]");
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_BYTE:
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_SHORT:
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_INT:
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_LONG:
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_FLOAT:
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_DOUBLE:
      {
        char* package_var_type = NULL;
        switch (opcode->code) {
          case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_BYTE:
            package_var_type = "SPVM_API_byte";
            break;
          case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_SHORT:
            package_var_type = "SPVM_API_short";
            break;
          case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_INT:
            package_var_type = "SPVM_API_int";
            break;
          case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_LONG:
            package_var_type = "SPVM_API_long";
            break;
          case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_FLOAT:
            package_var_type = "float";
            break;
          case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_DOUBLE:
            package_var_type = "double";
            break;
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  *(");
        SPVM_STRING_BUFFER_add(string_buffer, package_var_type);
        SPVM_STRING_BUFFER_add(string_buffer, "*)");
        SPVM_STRING_BUFFER_add(string_buffer, "&(*(SPVM_API_VALUE**)(api->get_runtime(api) + ");
        SPVM_STRING_BUFFER_add_int(string_buffer, offsetof(SPVM_RUNTIME, package_vars));
        SPVM_STRING_BUFFER_add(string_buffer, "))[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "]");
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, package_var_type, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT** package_var_address = (SPVM_API_OBJECT**)");
        SPVM_STRING_BUFFER_add(string_buffer, "&(*(SPVM_API_VALUE**)(api->get_runtime(api) + ");
        SPVM_STRING_BUFFER_add_int(string_buffer, offsetof(SPVM_RUNTIME, package_vars));
        SPVM_STRING_BUFFER_add(string_buffer, "))[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "]");
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (*(SPVM_API_OBJECT**)package_var_address != SPVM_RUNTIME_C_NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*package_var_address) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*package_var_address); }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else { api->dec_ref_count(api, *(SPVM_API_OBJECT**)package_var_address); }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_API_OBJECT**)package_var_address = ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (*(SPVM_API_OBJECT**)package_var_address != SPVM_RUNTIME_C_NULL) { SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(*package_var_address); }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_PUSH_ARG: {
        SPVM_STRING_BUFFER_add(string_buffer, "call_sub_arg_stack_top++;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "call_sub_args[call_sub_arg_stack_top] = vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CALL_SUB:
      {
        // Get subroutine ID
        int32_t call_sub_id = opcode->operand1;
        
        // Constant pool sub
        SPVM_CONSTANT_POOL_SUB* constant_pool_sub_call_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[call_sub_id];
        
        // Subroutine argument length
        int32_t call_sub_args_length = constant_pool_sub_call_sub->args_length;

        // Subroutine argment type ids base
        int32_t call_sub_arg_type_ids_base = constant_pool_sub_call_sub->arg_type_ids_base;

        int32_t call_sub_abs_name_id = constant_pool_sub_call_sub->abs_name_id;
        
        // Subroutine name
        const char* call_sub_abs_name = (char*)&constant_pool[call_sub_abs_name_id + 1];

        int32_t call_sub_return_type_id = constant_pool_sub_call_sub->return_type_id;
        SPVM_CONSTANT_POOL_TYPE* call_sub_return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[call_sub_return_type_id];

        // Return type code
        int32_t call_sub_return_type_code = call_sub_return_type->code;

        // Set callar subroutine id
        SPVM_STRING_BUFFER_add(string_buffer, "*(int32_t*)(api->get_runtime(api) + ");
        SPVM_STRING_BUFFER_add_int(string_buffer, offsetof(SPVM_RUNTIME, caller_sub_id));
        SPVM_STRING_BUFFER_add(string_buffer, ") = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, sub_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  // ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)call_sub_abs_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        // Get subroutine ID
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t call_sub_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        // Call subroutine
        if (call_sub_return_type_code == SPVM_TYPE_C_CODE_VOID) {
          SPVM_STRING_BUFFER_add(string_buffer, "    api->call_void_sub(api, call_sub_id");
        }
        else if (call_sub_return_type_code == SPVM_TYPE_C_CODE_BYTE) {
          SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_API_byte*)&vars[");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, "] = api->call_byte_sub(api, call_sub_id");
        }
        else if (call_sub_return_type_code == SPVM_TYPE_C_CODE_SHORT) {
          SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_API_short*)&vars[");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, "] = api->call_short_sub(api, call_sub_id");
        }
        else if (call_sub_return_type_code == SPVM_TYPE_C_CODE_INT) {
          SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_API_int*)&vars[");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, "] = api->call_int_sub(api, call_sub_id");
        }
        else if (call_sub_return_type_code == SPVM_TYPE_C_CODE_LONG) {
          SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_API_long*)&vars[");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, "] = api->call_long_sub(api, call_sub_id");
        }
        else if (call_sub_return_type_code == SPVM_TYPE_C_CODE_FLOAT) {
          SPVM_STRING_BUFFER_add(string_buffer, "    *(float*)&vars[");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, "] = api->call_float_sub(api, call_sub_id");
        }
        else if (call_sub_return_type_code == SPVM_TYPE_C_CODE_DOUBLE) {
          SPVM_STRING_BUFFER_add(string_buffer, "    *(double*)&vars[");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, "] = api->call_double_sub(api, call_sub_id");
        }
        else {
          SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_API_OBJECT**)&vars[");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, "] = api->call_object_sub(api, call_sub_id");
        }

        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        if (call_sub_args_length > 0) {
          SPVM_STRING_BUFFER_add(string_buffer, "call_sub_args");
        }
        else {
          SPVM_STRING_BUFFER_add(string_buffer, "SPVM_RUNTIME_C_NULL");
        }
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if (api->get_exception(api)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "call_sub_arg_stack_top -= ");
        SPVM_STRING_BUFFER_add_int(string_buffer, call_sub_args_length);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_IF_CROAK_CATCH: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (croak_flag) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->create_exception_stack_trace(api, ");
        SPVM_STRING_BUFFER_add(string_buffer, " api->get_exception(api), ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, "));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer,  opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_IF_CROAK_RETURN: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (croak_flag) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->create_exception_stack_trace(api, ");
        SPVM_STRING_BUFFER_add(string_buffer, " api->get_exception(api), ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, "));\n");
        if (sub_return_type_code != SPVM_TYPE_C_CODE_VOID) {
          SPVM_STRING_BUFFER_add(string_buffer, "    return_value = 0;\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    goto label_SPVM_OPCODE_C_CODE_RETURN;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_CROAK_FLAG_TRUE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  croak_flag = 1;\n");
        break;
      }
      case SPVM_OPCODE_C_CODE_RETURN:
      {
        // Get return value
        if (sub_return_type_code != SPVM_TYPE_C_CODE_VOID) {
          const char* return_type_name = SPVM_JITCODE_BUILDER_get_type_name(return_type_code);
          SPVM_STRING_BUFFER_add(string_buffer, "  return_value = ");
          SPVM_JITCODE_BUILDER_add_operand(string_buffer, return_type_name, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        
        // Increment ref count of return value not to release by decrement
        if (return_type_code > SPVM_TYPE_C_CODE_DOUBLE) {
          SPVM_STRING_BUFFER_add(string_buffer, "  if (return_value != SPVM_RUNTIME_C_NULL) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(return_value);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  goto label_SPVM_OPCODE_C_CODE_RETURN;\n");
        
        break;
      }
      case SPVM_OPCODE_C_CODE_TABLE_SWITCH: {
        // 1  default
        // 5  npare
        // 9  match1 offset1 // min
        // 17 match2 offset2
        // 25 match3 offset3 // max
        
        // default offset
        int32_t default_branch = opcode->operand1;
        
        int32_t min = (opcode + 1)->operand0;
        
        int32_t max = (opcode + 1)->operand1;
        
        // case count
        int32_t length = max - min + 1;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  switch(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ") {\n");
        {
          int32_t case_index;
          for (case_index = 0; case_index < length; case_index++) {
            int32_t branch = (opcode + 2 + case_index)->operand1;
            
            SPVM_STRING_BUFFER_add(string_buffer, "    case ");
            SPVM_STRING_BUFFER_add_int(string_buffer, min + case_index);
            SPVM_STRING_BUFFER_add(string_buffer, ": goto L");
            SPVM_STRING_BUFFER_add_int(string_buffer, branch);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    default: goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, default_branch);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        opcode_index += (2 + length);
        continue;
      }
      case SPVM_OPCODE_C_CODE_LOOKUP_SWITCH: {
        // 1  default
        // 5  npare
        // 9  match1 offset1 // min
        // 17 match2 offset2
        // 25 match3 offset3 // max
        
        // default offset
        int32_t default_branch = opcode->operand1;
        
        // case count
        int32_t case_count = opcode->operand2;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  switch(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ") {\n");
        {
          int32_t case_index;
          for (case_index = 0; case_index < case_count; case_index++) {
            int32_t match = (opcode + 1 + case_index)->operand0;
            int32_t branch = (opcode + 1 + case_index)->operand1;
            
            SPVM_STRING_BUFFER_add(string_buffer, "    case ");
            SPVM_STRING_BUFFER_add_int(string_buffer, match);
            SPVM_STRING_BUFFER_add(string_buffer, ": goto L");
            SPVM_STRING_BUFFER_add_int(string_buffer, branch);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    default: goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, default_branch);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        opcode_index += (1 + case_count);
        continue;
      }
    }
    opcode_index++;
  }

  {
    
    SPVM_STRING_BUFFER_add(string_buffer, "  // RETURN_PROCESS\n");
    SPVM_STRING_BUFFER_add(string_buffer, "  label_SPVM_OPCODE_C_CODE_RETURN:\n");
    
    // Decrement auto decremenet variable
    if (constant_pool_sub->auto_dec_ref_count_stack_max_length > 0) {
      SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
      SPVM_STRING_BUFFER_add(string_buffer, "    int32_t auto_dec_ref_count_index;\n");
      SPVM_STRING_BUFFER_add(string_buffer, "    for (auto_dec_ref_count_index = 0; auto_dec_ref_count_index <= auto_dec_ref_count_stack_top; auto_dec_ref_count_index++) {\n");
      SPVM_STRING_BUFFER_add(string_buffer, "      int32_t var_index = *(int32_t*)&auto_dec_ref_count_stack[auto_dec_ref_count_index];\n");
      SPVM_STRING_BUFFER_add(string_buffer, "      if (*(SPVM_API_OBJECT**)&vars[var_index] != SPVM_RUNTIME_C_NULL) {\n");
      SPVM_STRING_BUFFER_add(string_buffer, "        if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(SPVM_API_OBJECT**)&vars[var_index]) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(SPVM_API_OBJECT**)&vars[var_index]); }\n");
      SPVM_STRING_BUFFER_add(string_buffer, "        else { api->dec_ref_count(api, *(SPVM_API_OBJECT**)&vars[var_index]); }\n");
      SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
      SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
      SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
    }
    
    // No exception
    SPVM_STRING_BUFFER_add(string_buffer, "  if (!croak_flag) {\n");
    if (return_type_code > SPVM_TYPE_C_CODE_DOUBLE) {
      SPVM_STRING_BUFFER_add(string_buffer, "    if (return_value != SPVM_RUNTIME_C_NULL) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(return_value); }\n");
    }
    SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, SPVM_RUNTIME_C_NULL);\n");
    SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
    
    if (sub_return_type_code == SPVM_TYPE_C_CODE_VOID) {
      SPVM_STRING_BUFFER_add(string_buffer, "  return;\n");
    }
    else {
      SPVM_STRING_BUFFER_add(string_buffer, "  return return_value;\n");
    }
  }
  
  // Close subroutine
  SPVM_STRING_BUFFER_add(string_buffer, "}\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
}

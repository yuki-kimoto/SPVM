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
#include "spvm_opcode_array.h"
#include "spvm_constant.h"

void SPVM_JITCODE_BUILDER_add_var(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t index) {
  if (strcmp(type_name, "SPVM_API_OBJECT*") == 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, index);
    SPVM_STRING_BUFFER_add(string_buffer, "]");
  }
  else {
    SPVM_STRING_BUFFER_add(string_buffer, "var");
    SPVM_STRING_BUFFER_add_int(string_buffer, index);
  }
}

void SPVM_JITCODE_BUILDER_add_operand(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t var_index) {
  if (strcmp(type_name, "SPVM_API_OBJECT*") == 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "*(");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)type_name);
    SPVM_STRING_BUFFER_add(string_buffer, "*)&");
  }
  SPVM_JITCODE_BUILDER_add_var(string_buffer, type_name, var_index);
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

char* SPVM_JITCODE_BUILDER_get_type_name(int32_t type_id) {
  
  switch (type_id ) {
    case SPVM_TYPE_C_ID_VOID:
      assert(0);
      break;
    case SPVM_TYPE_C_ID_BYTE:
      return "SPVM_API_byte";
      break;
    case SPVM_TYPE_C_ID_SHORT:
      return "SPVM_API_short";
      break;
    case SPVM_TYPE_C_ID_INT:
      return "SPVM_API_int";
      break;
    case SPVM_TYPE_C_ID_LONG:
      return "SPVM_API_long";
      break;
    case SPVM_TYPE_C_ID_FLOAT:
      return "SPVM_API_float";
      break;
    case SPVM_TYPE_C_ID_DOUBLE:
      return "SPVM_API_double";
      break;
    default:
      return "SPVM_API_OBJECT*";
  }
}

void SPVM_JITCODE_BUILDER_build_sub_jitcode(SPVM_STRING_BUFFER* string_buffer, int32_t sub_id) {
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();

  SPVM_COMPILER* compiler = runtime->compiler;

  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;

  // Subroutine return type
  SPVM_TYPE* sub_return_type = sub->op_return_type->uv.type;
  
  // Subroutine return type id
  int32_t sub_return_type_id = sub_return_type->id;

  assert(!sub->is_native);
  
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

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_OBJECT_TYPE_ID_BYTE_OFFSET ");
  SPVM_STRING_BUFFER_add_int(string_buffer, SPVM_RUNTIME_C_OBJECT_TYPE_ID_BYTE_OFFSET);
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
  
  // Subroutine name
  const char* sub_abs_name = sub->abs_name;

  // Return type
  switch (sub_return_type_id) {
    case SPVM_TYPE_C_ID_VOID:
      SPVM_STRING_BUFFER_add(string_buffer, "void ");
      break;
    case SPVM_TYPE_C_ID_BYTE:
      SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_byte ");
      break;
    case SPVM_TYPE_C_ID_SHORT:
      SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_short ");
      break;
    case SPVM_TYPE_C_ID_INT:
      SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_int ");
      break;
    case SPVM_TYPE_C_ID_LONG:
      SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_long ");
      break;
    case SPVM_TYPE_C_ID_FLOAT:
      SPVM_STRING_BUFFER_add(string_buffer, "float ");
      break;
    case SPVM_TYPE_C_ID_DOUBLE:
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
  if (sub->op_mys->length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_VALUE vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, sub->op_mys->length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }
  
  {
    int32_t my_index;
    for (my_index = 0; my_index < sub->op_mys->length; my_index++) {
      SPVM_OP* op_my = SPVM_LIST_fetch(sub->op_mys, my_index);
      SPVM_MY* my = op_my->uv.my;
      SPVM_TYPE* type = my->op_type->uv.type;
      if (!SPVM_TYPE_is_object(compiler, type)) {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_STRING_BUFFER_add(string_buffer, SPVM_JITCODE_BUILDER_get_type_name(type->id));
        SPVM_STRING_BUFFER_add(string_buffer, " var");
        SPVM_STRING_BUFFER_add_int(string_buffer, my->index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
      }
    }
  }
  
  if (sub->object_var_index_stack_max > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_VALUE object_var_index_stack[");
    SPVM_STRING_BUFFER_add_int(string_buffer, sub->object_var_index_stack_max);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t object_var_index_stack_top = -1;\n");
  }
  
  if (sub->call_sub_arg_stack_max > 0 ) {
    SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_VALUE call_sub_args[");
    SPVM_STRING_BUFFER_add_int(string_buffer, sub->call_sub_arg_stack_max);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }
  
  // Call subroutine argument stack top
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t call_sub_arg_stack_top = -1;\n");

  // Copy arguments to variables
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < sub->op_args->length; arg_index++) {
      
      SPVM_OP* op_arg = SPVM_LIST_fetch(sub->op_args, arg_index);
      SPVM_TYPE* arg_type = op_arg->uv.my->op_type->uv.type;
      int32_t arg_type_id = arg_type->id;
      const char* arg_type_name = SPVM_JITCODE_BUILDER_get_type_name(arg_type_id);

      // Assign argument
      SPVM_STRING_BUFFER_add(string_buffer, "  ");
      SPVM_JITCODE_BUILDER_add_operand(string_buffer, arg_type_name, arg_index);
      SPVM_STRING_BUFFER_add(string_buffer, " = ");
      SPVM_STRING_BUFFER_add(string_buffer, "*(");
      SPVM_STRING_BUFFER_add(string_buffer, SPVM_JITCODE_BUILDER_get_type_name(arg_type_id));
      SPVM_STRING_BUFFER_add(string_buffer, "*)&args[");
      SPVM_STRING_BUFFER_add_int(string_buffer, arg_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      
      SPVM_STRING_BUFFER_add(string_buffer, ";\n");
    }
  }
  
  // If arg is object, increment reference count
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < sub->op_args->length; arg_index++) {
      SPVM_OP* op_arg = SPVM_LIST_fetch(sub->op_args, arg_index);
      SPVM_TYPE* arg_type = op_arg->uv.my->op_type->uv.type;
      
      if (SPVM_TYPE_is_object(compiler, arg_type)) {
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
  if (sub_return_type_id != SPVM_TYPE_C_ID_VOID) {
    SPVM_STRING_BUFFER_add(string_buffer, "  ");
    switch (sub_return_type_id) {
      case SPVM_TYPE_C_ID_BYTE : {
        SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_byte");
        break;
      }
      case  SPVM_TYPE_C_ID_SHORT : {
        SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_short");
        break;
      }
      case  SPVM_TYPE_C_ID_INT : {
        SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_int");
        break;
      }
      case  SPVM_TYPE_C_ID_LONG : {
        SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_long");
        break;
      }
      case  SPVM_TYPE_C_ID_FLOAT : {
        SPVM_STRING_BUFFER_add(string_buffer, "float");
        break;
      }
      case  SPVM_TYPE_C_ID_DOUBLE : {
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
  
  SPVM_OPCODE* opcodes = compiler->opcode_array->values;
  int32_t opcode_base = sub->opcode_base;
  int32_t opcode_length = sub->opcode_length;
  int32_t opcode_index = opcode_base;
  
  SPVM_OPCODE* opcode = NULL;
  while (opcode_index < opcode_base + opcode_length) {

    // Line label
    SPVM_STRING_BUFFER_add(string_buffer, "L");
    SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index);
    SPVM_STRING_BUFFER_add(string_buffer, ": ");
    
    opcode = &(opcodes[opcode_index]);

    SPVM_STRING_BUFFER_add(string_buffer, "// ");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_OPCODE_C_ID_NAMES[opcode->id]);
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
    
    switch (opcode->id) {
      case SPVM_OPCODE_C_ID_NOP:
        abort();
      case SPVM_OPCODE_C_ID_BOOL_INT:
        SPVM_JITCODE_BUILDER_add_bool(string_buffer, "SPVM_API_int", opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_LONG:
        SPVM_JITCODE_BUILDER_add_bool(string_buffer, "SPVM_API_long", opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_FLOAT:
        SPVM_JITCODE_BUILDER_add_bool(string_buffer, "float", opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_DOUBLE:
        SPVM_JITCODE_BUILDER_add_bool(string_buffer, "double", opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_OBJECT:
        SPVM_JITCODE_BUILDER_add_bool(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_IS_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == SPVM_RUNTIME_C_NULL);\n");
        break;
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " != SPVM_RUNTIME_C_NULL);\n");
        break;
      case SPVM_OPCODE_C_ID_EQ_INT:
        SPVM_JITCODE_BUILDER_add_eq(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_LONG:
        SPVM_JITCODE_BUILDER_add_eq(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_FLOAT:
        SPVM_JITCODE_BUILDER_add_eq(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_DOUBLE:
        SPVM_JITCODE_BUILDER_add_eq(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_OBJECT:
        SPVM_JITCODE_BUILDER_add_eq(string_buffer, "SPVM_API_OBJECT*", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_INT:
        SPVM_JITCODE_BUILDER_add_ne(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_LONG:
        SPVM_JITCODE_BUILDER_add_ne(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_FLOAT:
        SPVM_JITCODE_BUILDER_add_ne(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_ne(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_OBJECT:
        SPVM_JITCODE_BUILDER_add_ne(string_buffer, "SPVM_API_OBJECT*", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_INT:
        SPVM_JITCODE_BUILDER_add_gt(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_LONG:
        SPVM_JITCODE_BUILDER_add_gt(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_FLOAT:
        SPVM_JITCODE_BUILDER_add_gt(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_DOUBLE:
        SPVM_JITCODE_BUILDER_add_gt(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_INT:
        SPVM_JITCODE_BUILDER_add_ge(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_LONG:
        SPVM_JITCODE_BUILDER_add_ge(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_FLOAT:
        SPVM_JITCODE_BUILDER_add_ge(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_ge(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_INT:
        SPVM_JITCODE_BUILDER_add_lt(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_LONG:
        SPVM_JITCODE_BUILDER_add_lt(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_FLOAT:
        SPVM_JITCODE_BUILDER_add_lt(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_DOUBLE:
        SPVM_JITCODE_BUILDER_add_lt(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_INT:
        SPVM_JITCODE_BUILDER_add_le(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_LONG:
        SPVM_JITCODE_BUILDER_add_le(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_FLOAT:
        SPVM_JITCODE_BUILDER_add_le(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_le(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_ADD_INT:
        SPVM_JITCODE_BUILDER_add_add(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ADD_LONG:
        SPVM_JITCODE_BUILDER_add_add(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ADD_FLOAT:
        SPVM_JITCODE_BUILDER_add_add(string_buffer, "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ADD_DOUBLE:
        SPVM_JITCODE_BUILDER_add_add(string_buffer, "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_INT:
        SPVM_JITCODE_BUILDER_add_subtract(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_LONG:
        SPVM_JITCODE_BUILDER_add_subtract(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_FLOAT:
        SPVM_JITCODE_BUILDER_add_subtract(string_buffer, "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE:
        SPVM_JITCODE_BUILDER_add_subtract(string_buffer, "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_INT:
        SPVM_JITCODE_BUILDER_add_multiply(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_LONG:
        SPVM_JITCODE_BUILDER_add_multiply(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_FLOAT:
        SPVM_JITCODE_BUILDER_add_multiply(string_buffer, "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE:
        SPVM_JITCODE_BUILDER_add_multiply(string_buffer, "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_INT:
        SPVM_JITCODE_BUILDER_add_divide_integral(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_LONG: 
        SPVM_JITCODE_BUILDER_add_divide_integral(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_FLOAT:
        SPVM_JITCODE_BUILDER_add_divide_floating_point(string_buffer, "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_divide_floating_point(string_buffer, "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_INT:
        SPVM_JITCODE_BUILDER_add_remainder_integral(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_LONG: 
        SPVM_JITCODE_BUILDER_add_remainder_integral(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_FLOAT:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "float", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = (float)fmod((double)");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "float", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", (double)");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "float", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_DOUBLE:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "double", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = fmod(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "double", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "double", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT:
        SPVM_JITCODE_BUILDER_add_left_shift(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG:
        SPVM_JITCODE_BUILDER_add_left_shift(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_INT:
        SPVM_JITCODE_BUILDER_add_right_shift(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_LONG:
        SPVM_JITCODE_BUILDER_add_right_shift(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_INT:
        SPVM_JITCODE_BUILDER_add_right_shift_unsigned(string_buffer, "int32_t", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_LONG:
        SPVM_JITCODE_BUILDER_add_right_shift_unsigned(string_buffer, "int64_t", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_INT:
        SPVM_JITCODE_BUILDER_add_bit_and(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_LONG:
        SPVM_JITCODE_BUILDER_add_bit_and(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_INT:
        SPVM_JITCODE_BUILDER_add_bit_or(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_LONG:
        SPVM_JITCODE_BUILDER_add_bit_or(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_INT:
        SPVM_JITCODE_BUILDER_add_bit_xor(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_LONG:
        SPVM_JITCODE_BUILDER_add_bit_xor(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_PLUS_INT:
        SPVM_JITCODE_BUILDER_add_plus(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_PLUS_LONG:
        SPVM_JITCODE_BUILDER_add_plus(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_PLUS_FLOAT:
        SPVM_JITCODE_BUILDER_add_plus(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_PLUS_DOUBLE:
        SPVM_JITCODE_BUILDER_add_plus(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_INT:
        SPVM_JITCODE_BUILDER_add_negate(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_LONG:
        SPVM_JITCODE_BUILDER_add_negate(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_FLOAT:
        SPVM_JITCODE_BUILDER_add_negate(string_buffer, "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_negate(string_buffer, "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_COMPLEMENT_INT:
        SPVM_JITCODE_BUILDER_add_complement(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_COMPLEMENT_LONG:
        SPVM_JITCODE_BUILDER_add_complement(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_BYTE:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_SHORT:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_INT:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_LONG:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_FLOAT:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_DOUBLE:
        SPVM_JITCODE_BUILDER_add_inc(string_buffer, "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_BYTE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_byte", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_SHORT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_short", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_INT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_int", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_LONG:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_long", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_FLOAT:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_float", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_DOUBLE:
        SPVM_JITCODE_BUILDER_add_convert(string_buffer, "SPVM_API_double", "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_byte", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_byte(string_buffer, *(SPVM_API_byte*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_short", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_short(string_buffer, *(SPVM_API_short*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, *(SPVM_API_int*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_long", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_long(string_buffer, *(SPVM_API_long*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "UL;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_float", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_float(string_buffer, *(SPVM_API_float*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "f;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_double", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_double(string_buffer, *(SPVM_API_double*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = SPVM_RUNTIME_C_NULL;\n");
        break;
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_BYTE:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_SHORT:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_INT:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_LONG:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_FLOAT:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_DOUBLE:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_OBJECT:
        SPVM_JITCODE_BUILDER_add_array_load(string_buffer, "SPVM_API_OBJECT*", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_BYTE:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_SHORT:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_INT:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_LONG:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_FLOAT:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_array_store(string_buffer, "SPVM_API_double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT:
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
      case SPVM_OPCODE_C_ID_MOVE_BYTE:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_SHORT:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_INT:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_LONG:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_FLOAT:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_OBJECT:
        SPVM_JITCODE_BUILDER_add_move(string_buffer, "SPVM_API_OBJECT*", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_REF_COUNT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " != SPVM_RUNTIME_C_NULL) { SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_DEC_REF_COUNT: {
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
      case SPVM_OPCODE_C_ID_PUSH_OBJECT_VAR_INDEX: {
        SPVM_STRING_BUFFER_add(string_buffer, "  object_var_index_stack_top++;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  *(int32_t*)&object_var_index_stack[object_var_index_stack_top] = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }

      case SPVM_OPCODE_C_ID_LEAVE_SCOPE: {
        if (sub->object_var_index_stack_max > 0) {
          SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    int32_t object_var_index_stack_current_base = ");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_var_index_index;\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      for (object_var_index_index = object_var_index_stack_current_base; object_var_index_index <= object_var_index_stack_top; object_var_index_index++) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        int32_t var_index = *(int32_t*)&object_var_index_stack[object_var_index_index];\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        if (*(SPVM_API_OBJECT**)&vars[var_index] != SPVM_RUNTIME_C_NULL) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "          if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(SPVM_API_OBJECT**)&vars[var_index]) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(SPVM_API_OBJECT**)&vars[var_index]); }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "          else { api->dec_ref_count(api, *(SPVM_API_OBJECT**)&vars[var_index]); }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    object_var_index_stack_top = object_var_index_stack_current_base - 1;\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->new_object(api, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_byte_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_short_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_int_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_long_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_float_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add(string_buffer, "api->new_double_array(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = api->new_object_array(api, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t constant_id = opcode->operand1;
        
        SPVM_OP* op_constant = SPVM_LIST_fetch(compiler->op_constants, constant_id);
        SPVM_CONSTANT* constant = op_constant->uv.constant;

        const char* name = constant->value.string_value;
        int32_t length = constant->string_length;
        
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
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH: {
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
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        SPVM_JITCODE_BUILDER_add_get_field(string_buffer, "SPVM_API_OBJECT*", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        SPVM_JITCODE_BUILDER_add_set_field(string_buffer, "SPVM_API_double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT:
      {
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
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
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
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD_OBJECT: {
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
      case SPVM_OPCODE_C_ID_CONCAT_STRING_STRING:
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
      case SPVM_OPCODE_C_ID_CONCAT_STRING_BYTE:
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
      case SPVM_OPCODE_C_ID_CONCAT_STRING_SHORT:
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
      case SPVM_OPCODE_C_ID_CONCAT_STRING_INT:
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
      case SPVM_OPCODE_C_ID_CONCAT_STRING_LONG:
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
      case SPVM_OPCODE_C_ID_CONCAT_STRING_FLOAT:
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
      case SPVM_OPCODE_C_ID_CONCAT_STRING_DOUBLE:
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
      case SPVM_OPCODE_C_ID_GOTO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EQ_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (condition_flag == 0) { goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "; }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IF_NE_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (condition_flag) { goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "; }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "   = api->get_exception(api);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_STORE_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  api->set_exception(api, ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_BYTE:
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_SHORT:
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_INT:
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_LONG:
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_DOUBLE:
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_OBJECT:
      {
        char* package_var_type = NULL;
        switch (opcode->id) {
          case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_BYTE:
            package_var_type = "SPVM_API_byte";
            break;
          case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_SHORT:
            package_var_type = "SPVM_API_short";
            break;
          case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_INT:
            package_var_type = "SPVM_API_int";
            break;
          case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_LONG:
            package_var_type = "SPVM_API_long";
            break;
          case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_FLOAT:
            package_var_type = "float";
            break;
          case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_DOUBLE:
            package_var_type = "double";
            break;
          case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_OBJECT:
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
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_BYTE:
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_SHORT:
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_INT:
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_LONG:
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_DOUBLE:
      {
        char* package_var_type = NULL;
        switch (opcode->id) {
          case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_BYTE:
            package_var_type = "SPVM_API_byte";
            break;
          case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_SHORT:
            package_var_type = "SPVM_API_short";
            break;
          case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_INT:
            package_var_type = "SPVM_API_int";
            break;
          case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_LONG:
            package_var_type = "SPVM_API_long";
            break;
          case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_FLOAT:
            package_var_type = "float";
            break;
          case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_DOUBLE:
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
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_OBJECT: {
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
      case SPVM_OPCODE_C_ID_PUSH_ARG_BYTE:
      case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT:
      case SPVM_OPCODE_C_ID_PUSH_ARG_INT:
      case SPVM_OPCODE_C_ID_PUSH_ARG_LONG:
      case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT:
      case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE:
      case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  call_sub_arg_stack_top++;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        switch (opcode->id) {
          case SPVM_OPCODE_C_ID_PUSH_ARG_BYTE:
            SPVM_STRING_BUFFER_add(string_buffer, "*(SPVM_API_byte*)&");
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT:
            SPVM_STRING_BUFFER_add(string_buffer, "*(SPVM_API_short*)&");
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_INT:
            SPVM_STRING_BUFFER_add(string_buffer, "*(SPVM_API_int*)&");
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_LONG:
            SPVM_STRING_BUFFER_add(string_buffer, "*(SPVM_API_long*)&");
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT:
            SPVM_STRING_BUFFER_add(string_buffer, "*(SPVM_API_float*)&");
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE:
            SPVM_STRING_BUFFER_add(string_buffer, "*(SPVM_API_double*)&");
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT:
            SPVM_STRING_BUFFER_add(string_buffer, "*(SPVM_API_OBJECT**)&");
            break;
        }
        SPVM_STRING_BUFFER_add(string_buffer, "call_sub_args[call_sub_arg_stack_top] = ");
        switch (opcode->id) {
          case SPVM_OPCODE_C_ID_PUSH_ARG_BYTE:
            SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_byte", opcode->operand0);
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT:
            SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_short", opcode->operand0);
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_INT:
            SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand0);
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_LONG:
            SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_long", opcode->operand0);
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT:
            SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_float", opcode->operand0);
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE:
            SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_double", opcode->operand0);
            break;
          case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT:
            SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
            break;
        }
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_CAST: {
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* object = ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t object_type_id = *(int32_t*)(object + SPVM_RUNTIME_C_OBJECT_TYPE_ID_BYTE_OFFSET);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t cast_type_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object_type_id != cast_type_id) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t can_assign = api->check_cast(api, cast_type_id, object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (!can_assign) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT* exception = api->new_string(api, \"Can't cast uncompatible type.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        api->set_exception(api, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        croak_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else { ");
        SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = object; }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB:
      case SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD:
      {
        int32_t decl_sub_id = opcode->operand1;

        // Declare subroutine
        SPVM_OP* op_sub_decl = SPVM_LIST_fetch(compiler->op_subs, decl_sub_id);
        SPVM_SUB* decl_sub = op_sub_decl->uv.sub;
        
        // Declare subroutine return type
        SPVM_TYPE* decl_sub_return_type = decl_sub->op_return_type->uv.type;
        
        // Declare subroutine return type id
        int32_t decl_sub_return_type_id = decl_sub_return_type->id;
        
        // Declare subroutine argument length
        int32_t decl_sub_args_length = decl_sub->op_args->length;

        SPVM_STRING_BUFFER_add(string_buffer, "  // ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub->abs_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        // Call subroutine id
        if (opcode->id == SPVM_OPCODE_C_ID_CALL_SUB) {
          SPVM_STRING_BUFFER_add(string_buffer, "    int32_t call_sub_id = ");
          SPVM_STRING_BUFFER_add_int(string_buffer, decl_sub_id);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        else if (opcode->id == SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD) {
          SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
          SPVM_STRING_BUFFER_add(string_buffer, "];\n");
          
          SPVM_STRING_BUFFER_add(string_buffer, "    int32_t call_sub_id = api->get_sub_id_interface_method(api, object, ");
          SPVM_STRING_BUFFER_add_int(string_buffer, decl_sub_id);
          SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        }
        else {
          assert(0);
        }
        
        // Call subroutine
        if (decl_sub_return_type_id == SPVM_TYPE_C_ID_VOID) {
          SPVM_STRING_BUFFER_add(string_buffer, "    api->call_void_sub(api, call_sub_id");
        }
        else if (decl_sub_return_type_id == SPVM_TYPE_C_ID_BYTE) {
          SPVM_STRING_BUFFER_add(string_buffer, "    ");
          SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_byte", opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, " = api->call_byte_sub(api, call_sub_id");
        }
        else if (decl_sub_return_type_id == SPVM_TYPE_C_ID_SHORT) {
          SPVM_STRING_BUFFER_add(string_buffer, "    ");
          SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, " = api->call_short_sub(api, call_sub_id");
        }
        else if (decl_sub_return_type_id == SPVM_TYPE_C_ID_INT) {
          SPVM_STRING_BUFFER_add(string_buffer, "    ");
          SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_int", opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, " = api->call_int_sub(api, call_sub_id");
        }
        else if (decl_sub_return_type_id == SPVM_TYPE_C_ID_LONG) {
          SPVM_STRING_BUFFER_add(string_buffer, "    ");
          SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_long", opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, " = api->call_long_sub(api, call_sub_id");
        }
        else if (decl_sub_return_type_id == SPVM_TYPE_C_ID_FLOAT) {
          SPVM_STRING_BUFFER_add(string_buffer, "    ");
          SPVM_JITCODE_BUILDER_add_operand(string_buffer, "float", opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, " = api->call_float_sub(api, call_sub_id");
        }
        else if (decl_sub_return_type_id == SPVM_TYPE_C_ID_DOUBLE) {
          SPVM_STRING_BUFFER_add(string_buffer, "    ");
          SPVM_JITCODE_BUILDER_add_operand(string_buffer, "double", opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, " = api->call_double_sub(api, call_sub_id");
        }
        else {
          SPVM_STRING_BUFFER_add(string_buffer, "    ");
          SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, " = api->call_object_sub(api, call_sub_id");
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        if (decl_sub_args_length > 0) {
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
        SPVM_STRING_BUFFER_add_int(string_buffer, decl_sub_args_length);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_CATCH: {
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
      case SPVM_OPCODE_C_ID_IF_CROAK_RETURN: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (croak_flag) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->create_exception_stack_trace(api, ");
        SPVM_STRING_BUFFER_add(string_buffer, " api->get_exception(api), ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, "));\n");
        if (sub_return_type_id != SPVM_TYPE_C_ID_VOID) {
          SPVM_STRING_BUFFER_add(string_buffer, "    return_value = 0;\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CROAK_FLAG_TRUE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  croak_flag = 1;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN:
      {
        // Get return value
        if (sub_return_type_id != SPVM_TYPE_C_ID_VOID) {
          const char* return_type_name = SPVM_JITCODE_BUILDER_get_type_name(sub_return_type_id);
          SPVM_STRING_BUFFER_add(string_buffer, "  return_value = ");
          SPVM_JITCODE_BUILDER_add_operand(string_buffer, return_type_name, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        
        // Increment ref count of return value not to release by decrement
        if (sub_return_type_id > SPVM_TYPE_C_ID_DOUBLE) {
          SPVM_STRING_BUFFER_add(string_buffer, "  if (return_value != SPVM_RUNTIME_C_NULL) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(return_value);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_TABLE_SWITCH: {
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
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {
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

  // No exception
  SPVM_STRING_BUFFER_add(string_buffer, "  if (!croak_flag) {\n");
  if (sub_return_type_id > SPVM_TYPE_C_ID_DOUBLE) {
    SPVM_STRING_BUFFER_add(string_buffer, "    if (return_value != SPVM_RUNTIME_C_NULL) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(return_value); }\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, SPVM_RUNTIME_C_NULL);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  
  if (sub_return_type_id == SPVM_TYPE_C_ID_VOID) {
    SPVM_STRING_BUFFER_add(string_buffer, "  return;\n");
  }
  else {
    SPVM_STRING_BUFFER_add(string_buffer, "  return return_value;\n");
  }
  
  // Close subroutine
  SPVM_STRING_BUFFER_add(string_buffer, "}\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
}

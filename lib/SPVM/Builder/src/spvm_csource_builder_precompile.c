#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>

#include "spvm_native.h"

#include "spvm_list.h"
#include "spvm_hash.h"

#include "spvm_csource_builder_precompile.h"
#include "spvm_string_buffer.h"

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"

#include "spvm_opcode.h"

#include "spvm_object.h"

#include "spvm_util_allocator.h"
#include "spvm_runtime_allocator.h"

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_allocator.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_my.h"
#include "spvm_runtime_info_type.h"
#include "spvm_runtime_info_switch_info.h"
#include "spvm_runtime_info_case_info.h"

// Only use constant value
#include "spvm_package.h"
#include "spvm_package_var.h"
#include "spvm_sub.h"
#include "spvm_basic_type.h"
#include "spvm_field.h"
#include "spvm_type.h"

const char* SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(SPVM_ENV* env, int32_t ctype_id) {
  switch (ctype_id) {
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE:
      return "int8_t";
      break;
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT:
      return "int16_t";
      break;
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT:
      return "int32_t";
      break;
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG:
      return "int64_t";
      break;
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT:
      return "float";
      break;
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE:
      return "double";
      break;
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS:
      return "void*";
      break;
  }
  
  return NULL;
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index) {
  
  if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS) {
    SPVM_STRING_BUFFER_add(string_buffer, "address_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, index);
    SPVM_STRING_BUFFER_add(string_buffer, "]");
  }
  else {
    SPVM_STRING_BUFFER_add(string_buffer, "numeric_vars");
    SPVM_STRING_BUFFER_add_int(string_buffer, index);
  }
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var_value(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index, int32_t field_index) {
  
  SPVM_STRING_BUFFER_add(string_buffer, "numeric_vars");
  SPVM_STRING_BUFFER_add_int(string_buffer, index);
  SPVM_STRING_BUFFER_add(string_buffer, "[");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var_field_index(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index, int32_t field_index) {
  if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS) {
    SPVM_STRING_BUFFER_add(string_buffer, "address_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
    SPVM_STRING_BUFFER_add(string_buffer, "]");
  }
  else {
    SPVM_STRING_BUFFER_add(string_buffer, "numeric_vars");
    SPVM_STRING_BUFFER_add_int(string_buffer, index);
    SPVM_STRING_BUFFER_add(string_buffer, "[");
    SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
    SPVM_STRING_BUFFER_add(string_buffer, "]");
  }
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index, int32_t field_index) {
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var_value(env, string_buffer, ctype_id, var_index, field_index);
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, ctype_id, var_index);
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)*(void**)&");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, var_index);
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&");
  SPVM_STRING_BUFFER_add(string_buffer, "stack[");
  SPVM_STRING_BUFFER_add_int(string_buffer, var_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var_field_index(env, string_buffer, ctype_id, var_index, field_index);
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = !!");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_eq(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ne(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " != ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_gt(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " > ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ge(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >= ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_lt(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " < ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_le(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " <= ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_add(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " + ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_subtract(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " - ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_multiply(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " * ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_integral(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_string_raw(env, \"0 division\", 0));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 1;\n");

  SPVM_STRING_BUFFER_add(string_buffer, "  } else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_floating_point(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_remainder_integral(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* exception = env->new_string_raw(env, \"0 division\", 0);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, exception);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " % /* REMAINDER */ "); // % have undarstandable bug.
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_left_shift(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " << (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x1f))");
  }
  else if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x3f))");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_shift_unsigned(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, ")((u");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, ")");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x1f))");
  }
  else if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x3f))");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_shift(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x1f))");
  }
  else if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG) {
    SPVM_STRING_BUFFER_add(string_buffer, " & 0x3f))");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_and(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " & ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_or(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " | ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_xor(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " ^ ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_negate(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = -");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_plus(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_complement(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ~");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_inc(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t number) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " += ");
  SPVM_STRING_BUFFER_add_int(string_buffer, number);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t out_ctype_id, int32_t in_ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, out_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, out_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, ")");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, in_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_load_constant_0(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = 0");
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, element_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_STRING_BUFFER_add(string_buffer, "(*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "**)&(*(void**)array))[index]; \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "(*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "**)&(*(void**)array))[index] \n");
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, element_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_fetch(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index, int32_t field_length) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  {
    int32_t field_index;
    for (field_index = 0; field_index < field_length; field_index++) {
      SPVM_STRING_BUFFER_add(string_buffer, "        ");
      SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, element_ctype_id, out_index, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, " = ");
      SPVM_STRING_BUFFER_add(string_buffer, "(*(");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
      SPVM_STRING_BUFFER_add(string_buffer, "**)&(*(void**)array))[");
      SPVM_STRING_BUFFER_add_int(string_buffer, field_length);
      SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
      SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]; \n");
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_fetch(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index, int32_t field_length, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, element_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " =");
  SPVM_STRING_BUFFER_add(string_buffer, "(*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "**)&(*(void**)array))[");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_length);
  SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]; \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index, int32_t field_length) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  
  {
    int32_t field_index;
    for (field_index = 0; field_index < field_length; field_index++) {
      SPVM_STRING_BUFFER_add(string_buffer, "      (*(");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
      SPVM_STRING_BUFFER_add(string_buffer, "**)&(*(void**)array))[");
      SPVM_STRING_BUFFER_add_int(string_buffer, field_length);
      SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
      SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      SPVM_STRING_BUFFER_add(string_buffer, " = ");
      SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, element_ctype_id, in_index, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, ";\n");
    }
  }

  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_var_id, int32_t ref_var_id, int32_t field_length) {

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "* value_ref = *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "**)&address_vars[");
  SPVM_STRING_BUFFER_add_int(string_buffer, ref_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  for (int32_t field_index = 0; field_index < field_length; field_index++) {
    SPVM_STRING_BUFFER_add(string_buffer,  "    ");
    SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var_value(env, string_buffer, element_ctype_id, out_var_id, field_index);
    SPVM_STRING_BUFFER_add(string_buffer,  " = ");
    SPVM_STRING_BUFFER_add(string_buffer, "*(");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
    SPVM_STRING_BUFFER_add(string_buffer, "*)&value_ref[");
    SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_get_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_var_id, int32_t ref_var_id, int32_t field_index) {

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* value_ref = *(SPVM_VALUE**)&address_vars[");
  SPVM_STRING_BUFFER_add_int(string_buffer, ref_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&numeric_vars");
  SPVM_STRING_BUFFER_add_int(string_buffer, out_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "");
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&value_ref[");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_set_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t ref_var_id, int32_t in_var_id, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* value_ref = *(SPVM_VALUE**)&address_vars[");
  SPVM_STRING_BUFFER_add_int(string_buffer, ref_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&value_ref[");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]");
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&numeric_vars");
  SPVM_STRING_BUFFER_add_int(string_buffer, in_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index, int32_t field_length, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        (*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "**)&(*(void**)array))[");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_length);
  SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]");
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, element_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_deref(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_deref(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t field_ctype_id, int32_t out_index, int32_t object_index, SPVM_RUNTIME_FIELD* field) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
  const char* field_package_name = runtime->symbols[field_package->name_id];
  const char* field_name = runtime->symbols[field->name_id];

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, object_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Object must be not undef.\", 0));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, field_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, field_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&fields[");
  SPVM_STRING_BUFFER_add_field_index_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t field_ctype_id, int32_t object_index, SPVM_RUNTIME_FIELD* field, int32_t in_index) {
  SPVM_RUNTIME* runtime = env->runtime;

  SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
  const char* field_package_name = runtime->symbols[field_package->name_id];
  const char* field_name = runtime->symbols[field->name_id];

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, object_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Object must be not undef.\", 0));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, field_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&fields[");
  SPVM_STRING_BUFFER_add_field_index_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "] = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, field_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_build_package_csource(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, const char* package_name) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  
  // Head part - include and define
  SPVM_CSOURCE_BUILDER_PRECOMPILE_build_head(env, string_buffer);
  
  // Subroutine decrations
  SPVM_STRING_BUFFER_add(string_buffer, "// Function Declarations\n");
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < package->subs->length; sub_index++) {
      SPVM_RUNTIME_SUB* sub = SPVM_LIST_fetch(package->subs, sub_index);
      const char* sub_name = runtime->symbols[sub->name_id];
      const char* sub_signature = runtime->symbols[sub->signature_id];
      if (sub->flag & SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC) {
        SPVM_STRING_BUFFER_add(string_buffer, "// [SIG]");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_build_sub_declaration(env, string_buffer, package_name, sub_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n\n");
      }
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Subroutine implementations
  SPVM_STRING_BUFFER_add(string_buffer, "// Function Implementations\n");
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < package->subs->length; sub_index++) {
      SPVM_RUNTIME_SUB* sub = SPVM_LIST_fetch(package->subs, sub_index);
      if (sub->flag & SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC) {
        const char* sub_name = runtime->symbols[sub->name_id];
        SPVM_CSOURCE_BUILDER_PRECOMPILE_build_sub_implementation(env, string_buffer, package_name, sub_name);
      }
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_build_head(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer) {
  
  // Include header
  SPVM_STRING_BUFFER_add(string_buffer, "#ifndef SPVM_CSOURCE_BUILDER_PRECOMPILE_H\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_CSOURCE_BUILDER_PRECOMPILE_H\n");
  
  // API header
  SPVM_STRING_BUFFER_add(string_buffer, "#include <spvm_native.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <SPVM/CORE.native/CORE.c>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Inline macro function
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stdlib.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <string.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stdio.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <inttypes.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <math.h>\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_GET_OBJECT_NO_WEAKEN_ADDRESS(object) ((void*)((intptr_t)object & ~(intptr_t)1))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset)))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset))++)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(object)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "do {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object);\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset))--)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT(object)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "do {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(object) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(object); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { env->dec_ref_count(env, object); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_ISWEAK(dist_address) (((intptr_t)*(void**)dist_address) & 1)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(dist_address, src_object) \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "do {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* tmp_object = src_object;\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (tmp_object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(tmp_object);\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (*(void**)(dist_address) != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_RUNTIME_C_INLINE_ISWEAK(dist_address)) { env->unweaken(env, dist_address); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(void**)(dist_address)) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)(dist_address)); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { env->dec_ref_count(env, *(void**)(dist_address)); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)(dist_address) = tmp_object;\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#endif\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_build_sub_declaration(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* sub_name) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));

  assert(sub->flag & SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC);
  
  // Subroutine name
  const char* sub_abs_name = runtime->symbols[sub->abs_name_id];
  
  // Return type
  SPVM_STRING_BUFFER_add(string_buffer, "int32_t ");
        
  // Subroutine name. Replace : to _
  SPVM_STRING_BUFFER_add(string_buffer, "SPVM_PRECOMPILE_");
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
  SPVM_STRING_BUFFER_add(string_buffer, "(SPVM_ENV* env, SPVM_VALUE* stack)");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_build_sub_implementation(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* sub_name) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));

  int32_t sub_return_basic_type_id = sub->return_basic_type_id;
  int32_t sub_return_type_dimension = sub->return_type_dimension;
  int32_t sub_return_type_flag = sub->return_type_flag;
  
  int32_t sub_return_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, sub_return_basic_type_id, sub_return_type_dimension, sub_return_type_flag);
  
  assert(sub->flag & SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC);
  
  SPVM_CSOURCE_BUILDER_PRECOMPILE_build_sub_declaration(env, string_buffer, package_name, sub_name);

  // Block start
  SPVM_STRING_BUFFER_add(string_buffer, " {\n");
  
  if (sub->mortal_stack_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t mortal_stack[");
    SPVM_STRING_BUFFER_add_int(string_buffer, sub->mortal_stack_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t mortal_stack_top = 0;\n");
  }
  
  // Call subroutine argument stack top
  int32_t call_sub_arg_stack_top = 0;

  // Condition flag
  SPVM_STRING_BUFFER_add(string_buffer, "  register int32_t condition_flag;\n");
  
  // Convert string
  SPVM_STRING_BUFFER_add(string_buffer, "  char convert_string[30];\n");

  // Exception
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t exception_flag = 0;\n");

  // Address variable declarations
  int32_t address_vars_alloc_length = sub->address_vars_alloc_length;
  if (address_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  void* address_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, address_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // Numeric variable declarations
  int32_t numeric_vars_alloc_length = sub->numeric_vars_alloc_length;
  
  // Initialize variables with type information
  if (sub->my_ids_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  // Initialize variables\n");
  }
  if (address_vars_alloc_length > 0) {
    {
      int32_t my_index;
      int32_t address_var_id = 0;
      for (my_index = 0; my_index < sub->my_ids_length; my_index++) {
        SPVM_RUNTIME_MY* runtime_my = &runtime->mys[sub->my_ids_base + my_index];
        
        int32_t my_type_is_value_t = SPVM_RUNTIME_API_is_value_type(env, runtime_my->basic_type_id, runtime_my->type_dimension, runtime_my->type_flag);
        int32_t my_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, runtime_my->basic_type_id, runtime_my->type_dimension, runtime_my->type_flag);
        int32_t my_type_is_ref = SPVM_RUNTIME_API_is_ref_type(env, runtime_my->basic_type_id, runtime_my->type_dimension, runtime_my->type_flag);
        
        // Reference type
        if (my_type_is_ref) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, runtime_my->address_var_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = NULL;\n");
          address_var_id++;
        }
        // Value type
        else if (my_type_is_value_t) {
          
        }
        // Object type
        else if (my_type_is_object_type) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, runtime_my->address_var_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = NULL;\n");
          address_var_id++;
        }
        // Numeric type
        else {
          
        }
      }
      SPVM_STRING_BUFFER_add(string_buffer, "\n");
    }
  }

  if (numeric_vars_alloc_length > 0) {
    int32_t numeric_var_id = 0;
    for (int32_t my_index = 0; my_index < sub->my_ids_length; my_index++) {
      SPVM_RUNTIME_MY* runtime_my = &runtime->mys[sub->my_ids_base + my_index];
      
      int32_t my_type_is_value_t = SPVM_RUNTIME_API_is_value_type(env, runtime_my->basic_type_id, runtime_my->type_dimension, runtime_my->type_flag);
      int32_t my_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, runtime_my->basic_type_id, runtime_my->type_dimension, runtime_my->type_flag);
      int32_t my_type_is_ref = SPVM_RUNTIME_API_is_ref_type(env, runtime_my->basic_type_id, runtime_my->type_dimension, runtime_my->type_flag);
      
      // Reference type
      if (my_type_is_ref) {
      }
      // Value type
      else if (my_type_is_value_t) {
        int32_t runtime_my_basic_type_id = runtime_my->basic_type_id;
        SPVM_RUNTIME_BASIC_TYPE* runtime_my_basic_type = &runtime->basic_types[runtime_my_basic_type_id];
        SPVM_RUNTIME_PACKAGE* runtime_my_package = &runtime->packages[runtime_my_basic_type->package_id];
        
        SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(runtime_my_package->fields, 0);
        assert(first_field);
        
        switch (first_field->basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  int8_t ");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  int16_t ");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            SPVM_STRING_BUFFER_add(string_buffer, "  int64_t ");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  float ");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  double ");
            break;
          }
          default:
            assert(0);
        }
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, runtime_my->numeric_var_id, runtime_my_package->fields->length);
        SPVM_STRING_BUFFER_add(string_buffer, " = {");
        
        for (int32_t field_index = 0; field_index < runtime_my_package->fields->length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "0");
          if (field_index != runtime_my_package->fields->length - 1) {
            SPVM_STRING_BUFFER_add(string_buffer, ", ");
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "};\n");

        numeric_var_id += runtime_my_package->fields->length;
      }
      // Object type
      else if (my_type_is_object_type) {
      }
      // Numeric type
      else {
        int32_t my_type_is_numeric_ref_type = SPVM_RUNTIME_API_is_numeric_ref_type(env, runtime_my->basic_type_id, runtime_my->type_dimension, runtime_my->type_flag);
        
        if (my_type_is_numeric_ref_type) {
        }
        else {
          switch (runtime_my->basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              SPVM_STRING_BUFFER_add(string_buffer, "  int8_t ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, runtime_my->numeric_var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
              
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  int16_t ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, runtime_my->numeric_var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, runtime_my->numeric_var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              SPVM_STRING_BUFFER_add(string_buffer, "  int64_t ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, runtime_my->numeric_var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  float ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, runtime_my->numeric_var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              SPVM_STRING_BUFFER_add(string_buffer, "  double ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, runtime_my->numeric_var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
              break;
            }
            default:
              assert(0);
          }
        }
        numeric_var_id++;
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
  }
  
  // Copy arguments to variables with type information
  if (sub->arg_ids_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  // Copy arguments to variables\n");
  }
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < sub->arg_ids_length; arg_index++) {
      SPVM_RUNTIME_MY* runtime_arg = &runtime->args[sub->arg_ids_base + arg_index];

      int32_t arg_type_is_value_t = SPVM_RUNTIME_API_is_value_type(env, runtime_arg->basic_type_id, runtime_arg->type_dimension, runtime_arg->type_flag);
      int32_t arg_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, runtime_arg->basic_type_id, runtime_arg->type_dimension, runtime_arg->type_flag);
      int32_t arg_type_is_ref = SPVM_RUNTIME_API_is_ref_type(env, runtime_arg->basic_type_id, runtime_arg->type_dimension, runtime_arg->type_flag);
      
      // Ref type
      if (arg_type_is_ref) {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, runtime_arg->address_var_id);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, runtime_arg->var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
      }
      // Value type
      else if (arg_type_is_value_t) {
        int32_t runtime_arg_basic_type_id = runtime_arg->basic_type_id;
        SPVM_RUNTIME_BASIC_TYPE* runtime_arg_basic_type = &runtime->basic_types[runtime_arg_basic_type_id];
        SPVM_RUNTIME_PACKAGE* runtime_arg_package = &runtime->packages[runtime_arg_basic_type->package_id];
        
        SPVM_RUNTIME_FIELD* runtime_first_field = SPVM_LIST_fetch(runtime_arg_package->fields, 0);
        assert(runtime_first_field);

        for (int32_t field_index = 0; field_index < runtime_arg_package->fields->length; field_index++) {
          
          switch (runtime_first_field->basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, runtime_arg->numeric_var_id, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, runtime_arg->var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, runtime_arg->numeric_var_id, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, runtime_arg->var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, runtime_arg->numeric_var_id, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, runtime_arg->var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, runtime_arg->numeric_var_id, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, runtime_arg->var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, runtime_arg->numeric_var_id, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, runtime_arg->var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, runtime_arg->numeric_var_id, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, runtime_arg->var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            default:
              assert(0);
          }
        }
      }
      // Object type
      else if (arg_type_is_object_type) {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, runtime_arg->address_var_id);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, runtime_arg->var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
      }
      // Numeric type
      else {
        switch (runtime_arg->basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, runtime_arg->numeric_var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, runtime_arg->var_id);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, runtime_arg->numeric_var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, runtime_arg->var_id);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, runtime_arg->numeric_var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, runtime_arg->var_id);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, runtime_arg->numeric_var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, runtime_arg->var_id);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, runtime_arg->numeric_var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, runtime_arg->var_id);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, runtime_arg->numeric_var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, runtime_arg->var_id);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          default:
            assert(0);
        }
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
  }
  
  // If arg is object, increment reference count
  {
    for (int32_t arg_index = sub->arg_ids_base; arg_index < sub->arg_ids_base + sub->arg_ids_length; arg_index++) {
      SPVM_RUNTIME_MY* arg = &runtime->args[arg_index];
      if (SPVM_RUNTIME_API_is_object_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag)) {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, arg->address_var_id);
        SPVM_STRING_BUFFER_add(string_buffer, " != NULL) { SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, arg->address_var_id);
        SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
  }
  
  // Get field index
  if (sub->info_field_ids_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  // Get field index\n");
  }
  {
    SPVM_HASH* field_abs_name_symtable = SPVM_HASH_new(1);
    for (int32_t info_field_ids_index = 0; info_field_ids_index < sub->info_field_ids_length; info_field_ids_index++) {
      int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + info_field_ids_index];
      SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
      SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
      const char* field_package_name = runtime->symbols[field_package->name_id];
      const char* field_name = runtime->symbols[field->name_id];
      const char* field_abs_name = runtime->symbols[field->abs_name_id];
      const char* field_signature = runtime->symbols[field->signature_id];
      
      SPVM_FIELD* found_field = SPVM_HASH_fetch(field_abs_name_symtable, field_abs_name, strlen(field_abs_name));
      if (!found_field) {
        SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
        SPVM_STRING_BUFFER_add_field_index_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_index(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_STRING_BUFFER_add_field_index_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* exception = env->new_string_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        SPVM_HASH_insert(field_abs_name_symtable, field_abs_name, strlen(field_abs_name), field);
      }
    }
    SPVM_HASH_free(field_abs_name_symtable);
  }
  
  // Get package variable id
  if (sub->info_package_var_ids_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  // Get package variable id\n");
  }
  {
    SPVM_HASH* package_var_abs_name_symtable = SPVM_HASH_new(1);
    for (int32_t info_package_var_ids_index = 0; info_package_var_ids_index < sub->info_package_var_ids_length; info_package_var_ids_index++) {
      int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + info_package_var_ids_index];
      SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
      SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
      const char* package_var_package_name = runtime->symbols[package_var_package->name_id];
      const char* package_var_name = runtime->symbols[package_var->name_id];
      const char* package_var_abs_name = runtime->symbols[package_var->abs_name_id];
      const char* package_var_signature = runtime->symbols[package_var->signature_id];
      
      SPVM_PACKAGE_VAR* found_package_var = SPVM_HASH_fetch(package_var_abs_name_symtable, package_var_abs_name, strlen(package_var_abs_name));
      if (!found_package_var) {
        SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_package_var_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* exception = env->new_string_raw(env, \"Package variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        SPVM_HASH_insert(package_var_abs_name_symtable, package_var_abs_name, strlen(package_var_abs_name), package_var);
      }
    }
    SPVM_HASH_free(package_var_abs_name_symtable);
  }

  // Get sub id
  if (sub->info_sub_ids_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  // Get sub id\n");
  }
  {
    SPVM_HASH* sub_abs_name_symtable = SPVM_HASH_new(1);
    for (int32_t info_sub_ids_index = 0; info_sub_ids_index < sub->info_sub_ids_length; info_sub_ids_index++) {
      int32_t sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + info_sub_ids_index];
      SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
      SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
      const char* sub_package_name = runtime->symbols[sub_package->name_id];
      const char* sub_signature = runtime->symbols[sub->signature_id];
      const char* sub_name = runtime->symbols[sub->name_id];
      const char* sub_abs_name = runtime->symbols[sub->abs_name_id];
      
      SPVM_FIELD* found_sub = SPVM_HASH_fetch(sub_abs_name_symtable, sub_abs_name, strlen(sub_abs_name));
      if (!found_sub) {
        SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
        SPVM_STRING_BUFFER_add_sub_id_name(string_buffer, sub_package_name, sub_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_sub_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_STRING_BUFFER_add_sub_id_name(string_buffer, sub_package_name, sub_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* exception = env->new_string_raw(env, \"Subroutine not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        SPVM_HASH_insert(sub_abs_name_symtable, sub_abs_name, strlen(sub_abs_name), sub);
      }
    }
    SPVM_HASH_free(sub_abs_name_symtable);
  }

  // Get basic type id
  if (sub->info_types_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  // Get basic type id\n");
  }
  {
    SPVM_HASH* basic_type_symtable = SPVM_HASH_new(1);
    int32_t type_index;
    for (type_index = 0; type_index < sub->info_types_length; type_index++) {
      SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + type_index];
      SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[type->basic_type_id];
      const char* basic_type_name = runtime->symbols[basic_type->name_id];
      
      SPVM_RUNTIME_BASIC_TYPE* found_basic_type = SPVM_HASH_fetch(basic_type_symtable, basic_type_name, strlen(basic_type_name));
      if (!found_basic_type) {
        SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* exception = env->new_string_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        SPVM_HASH_insert(basic_type_symtable, basic_type_name, strlen(basic_type_name), basic_type);
      }
    }
    SPVM_HASH_free(basic_type_symtable);
  }
  
  SPVM_OPCODE* opcodes = runtime->opcodes;
  int32_t sub_opcodes_base = sub->opcodes_base;
  int32_t opcodes_length = sub->opcodes_length;
  int32_t opcode_index = 0;
  
  SPVM_OPCODE* opcode = NULL;

  while (opcode_index < opcodes_length) {

    // Line label
    SPVM_STRING_BUFFER_add(string_buffer, "L");
    SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index);
    SPVM_STRING_BUFFER_add(string_buffer, ": ");
    
    opcode = &(opcodes[sub_opcodes_base + opcode_index]);

    int32_t opcode_id = opcode->id == SPVM_OPCODE_C_ID_WIDE ? 255 + opcode->operand3 : opcode->id;

    SPVM_STRING_BUFFER_add(string_buffer, "// ");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_OPCODE_C_ID_NAMES[opcode_id]);
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
    
    switch (opcode_id) {
      case SPVM_OPCODE_C_ID_BOOL_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_OBJECT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_IS_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL);\n");
        break;
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " != NULL);\n");
        break;
      case SPVM_OPCODE_C_ID_EQ_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_eq(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_eq(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_eq(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_eq(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_OBJECT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_eq(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ne(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ne(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ne(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ne(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_OBJECT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ne(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_gt(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_gt(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_gt(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_gt(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ge(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ge(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ge(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ge(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_lt(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_lt(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_lt(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_lt(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_le(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_le(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_le(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_le(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_ISA_OBJECT:
      {
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t basic_type_id = type->basic_type_id;
        int32_t type_dimension = type->dimension;
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = runtime->symbols[basic_type->name_id];
        int32_t dimension = type->dimension;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)(object + (intptr_t)env->object_basic_type_id_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension = *(int32_t*)(object + (intptr_t)env->object_type_dimension_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      condition_flag = (object_basic_type_id == check_basic_type_id && object_type_dimension == check_type_dimension);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      condition_flag = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_ISA_INTERFACE:
      {
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t basic_type_id = type->basic_type_id;
        int32_t type_dimension = type->dimension;
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = runtime->symbols[basic_type->name_id];
        int32_t dimension = type->dimension;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)(object + (intptr_t)env->object_basic_type_id_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension = *(int32_t*)(object + (intptr_t)env->object_type_dimension_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      condition_flag = env->has_interface(env, object_basic_type_id, object_type_dimension, check_basic_type_id, check_type_dimension);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      condition_flag = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_EQ:
      case SPVM_OPCODE_C_ID_STRING_NE:
      case SPVM_OPCODE_C_ID_STRING_GT:
      case SPVM_OPCODE_C_ID_STRING_GE:
      case SPVM_OPCODE_C_ID_STRING_LT:
      case SPVM_OPCODE_C_ID_STRING_LE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object1 = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object2 = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length1 = *(SPVM_VALUE_int*)((intptr_t)object1 + (intptr_t)env->object_elements_length_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t lenght2 = *(SPVM_VALUE_int*)((intptr_t)object2 + (intptr_t)env->object_elements_length_byte_offset);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_byte* bytes1 = *(SPVM_VALUE_byte**)&(*(void**)object1);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_byte* bytes2 = *(SPVM_VALUE_byte**)&(*(void**)object2);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t short_string_length = length1 < lenght2 ? length1 : lenght2;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t retval = memcmp(bytes1, bytes2, short_string_length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t cmp;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (retval) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      cmp = retval < 0 ? -1 : 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } else if (length1 == lenght2) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      cmp = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      cmp = length1 < lenght2 ? -1 : 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_STRING_EQ:
            SPVM_STRING_BUFFER_add(string_buffer, "    condition_flag = (cmp == 0);\n");
            break;
          case SPVM_OPCODE_C_ID_STRING_NE:
            SPVM_STRING_BUFFER_add(string_buffer, "    condition_flag = (cmp != 0);\n");
            break;
          case SPVM_OPCODE_C_ID_STRING_GT:
            SPVM_STRING_BUFFER_add(string_buffer, "    condition_flag = (cmp == 1);\n");
            break;
          case SPVM_OPCODE_C_ID_STRING_GE:
            SPVM_STRING_BUFFER_add(string_buffer, "    condition_flag = (cmp >= 0);\n");
            break;
          case SPVM_OPCODE_C_ID_STRING_LT:
            SPVM_STRING_BUFFER_add(string_buffer, "    condition_flag = (cmp == -1);\n");
            break;
          case SPVM_OPCODE_C_ID_STRING_LE:
            SPVM_STRING_BUFFER_add(string_buffer, "    condition_flag = (cmp <= 0);\n");
            break;
        }
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        break;
      }
      case SPVM_OPCODE_C_ID_ADD_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_add(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ADD_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_add(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ADD_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_add(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ADD_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_add(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_subtract(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_subtract(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_subtract(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_subtract(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_multiply(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_multiply(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_multiply(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_multiply(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_integral(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_LONG: 
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_integral(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_floating_point(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_floating_point(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_remainder_integral(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_LONG: 
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_remainder_integral(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_FLOAT:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = (float)fmod((double)");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", (double)");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_DOUBLE:
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = fmod(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_left_shift(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_left_shift(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_shift(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_shift(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_shift_unsigned(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_shift_unsigned(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_and(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_and(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_or(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_or(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_xor(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_xor(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_negate(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_negate(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_negate(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_negate(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_COMPLEMENT_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_complement(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_COMPLEMENT_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_complement(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;

      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string, \"%\" PRId8, ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string, \"%\" PRId16, ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string, \"%\" PRId32, ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string, \"%\" PRId64, ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string, \"%g\", ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string, \"%g\", ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t string_length = strlen(convert_string);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string = env->new_string_raw(env, convert_string, string_length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", string);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_byte(string_buffer, *(SPVM_VALUE_byte*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_short(string_buffer, *(SPVM_VALUE_short*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, *(SPVM_VALUE_int*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_LONG: {
        int32_t rel_id = opcode->operand2;
        int64_t long_value = runtime->info_long_values[sub->info_long_values_base + rel_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_long(string_buffer, long_value);
        SPVM_STRING_BUFFER_add(string_buffer, "ULL;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_float(string_buffer, *(SPVM_VALUE_float*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "f;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_DOUBLE: {
        int32_t rel_id = opcode->operand2;
        double double_value = runtime->info_double_values[sub->info_double_values_base + rel_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_double(string_buffer, double_value);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_BYTE: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_SHORT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_INT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_LONG: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_FLOAT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_DOUBLE: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_OBJECT:
        SPVM_STRING_BUFFER_add(string_buffer, "  {");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* object = (*(SPVM_VALUE_object**)&(*(void**)array))[index];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", SPVM_RUNTIME_C_INLINE_GET_OBJECT_NO_WEAKEN_ADDRESS(object)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "          env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "          exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* object_address = &((*(SPVM_VALUE_object**)&(*(void**)array))[index]);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          object_address, ");
        SPVM_STRING_BUFFER_add(string_buffer, "        ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, "\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        );\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }");
        
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_UNDEF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0 || ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "  >= *(int32_t*)((intptr_t)");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* object_address = &((*(SPVM_VALUE_object**)&(*(void**)array))[index]);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          object_address,\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          NULL");
        SPVM_STRING_BUFFER_add(string_buffer, "        );\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }");
        
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_BYTE: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_SHORT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_INT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_LONG: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_FLOAT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_DOUBLE: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_OBJECT:
          SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ", ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
          SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_MOVE_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", NULL);\n");
        break;
      case SPVM_OPCODE_C_ID_MOVE_REF:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_VALUE_MOVE_BYTE: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_SHORT: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_INT: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_LONG: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_FLOAT: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_DOUBLE: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_MORTAL: {
        SPVM_STRING_BUFFER_add(string_buffer, "  mortal_stack[mortal_stack_top] = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  mortal_stack_top++;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LEAVE_SCOPE: {
        int32_t original_mortal_stack_top = opcode->operand0;
        if (sub->mortal_stack_length > 0) {
          SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    int32_t original_mortal_stack_top = ");
          SPVM_STRING_BUFFER_add_int(string_buffer, original_mortal_stack_top);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      int32_t mortal_stack_index;\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      for (mortal_stack_index = original_mortal_stack_top; mortal_stack_index < mortal_stack_top; mortal_stack_index++) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        int32_t var_index = mortal_stack[mortal_stack_index];\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        void** object_address = (void**)&address_vars[var_index];\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        if (*object_address != NULL) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "          if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*object_address) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*object_address); }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "          else { env->dec_ref_count(env, *object_address); }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "          *object_address = NULL;\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    mortal_stack_top = original_mortal_stack_top;\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t basic_type_id = type->basic_type_id;
        int32_t type_dimension = type->dimension;
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = runtime->symbols[basic_type->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_byte_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_short_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_int_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_long_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_float_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY:
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_double_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t basic_type_id = type->basic_type_id;
        int32_t type_dimension = type->dimension;
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = runtime->symbols[basic_type->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_object_array_raw(env, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, basic_type_id);
        SPVM_STRING_BUFFER_add(string_buffer, ", length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t basic_type_id = type->basic_type_id;
        int32_t type_dimension = type->dimension;
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = runtime->symbols[basic_type->name_id];
        int32_t element_dimension = type->dimension - 1;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_multi_array_raw(env, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, basic_type_id);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, element_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ", length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_VALUE_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t basic_type_id = type->basic_type_id;
        int32_t type_dimension = type->dimension;
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = runtime->symbols[basic_type->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_value_t_array_raw(env, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, basic_type_id);
        SPVM_STRING_BUFFER_add(string_buffer, ", length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t rel_id = opcode->operand2;
        const char* string_value = runtime->info_string_values[sub->info_string_values_base + rel_id];
        int32_t string_length = runtime->info_string_lengths[sub->info_string_values_base + rel_id];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add(string_buffer, "env->new_string_raw(env, \"");
        
        {
          int32_t i;
          for (i = 0; i < string_length; i++) {
            SPVM_STRING_BUFFER_add_hex_char(string_buffer, string_value[i]);
          }
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "\", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, string_length);
        SPVM_STRING_BUFFER_add(string_buffer, "));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_string_raw(env, \"Can't get array length of undef value.\", 0));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int32_t*)((intptr_t)");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " + (intptr_t)env->object_elements_length_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD: {
        int32_t rel_id = opcode->operand1;
        
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
        const char* field_package_name = runtime->symbols[field_package->name_id];
        const char* field_name = runtime->symbols[field->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_OBJECT* exception = env->new_string_raw(env, \"Object to weaken an object field must not be undefined.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void** object_field_address = (void**)&fields[\n");
        SPVM_STRING_BUFFER_add_field_index_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "      ];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->weaken(env, object_field_address);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_ARRAY_ELEMENT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(!array, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Array must not be undef\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_raw(env, \"Index is out of range\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE_object* elements = *(SPVM_VALUE_object**)&(*(void**)array);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void** object_element_address = (void**)&elements[index];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->weaken(env, object_element_address);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_SCALAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->weaken(env, &object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONCAT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string1 = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string2 = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (string1 == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"\\\".\\\" operater left value must be defined\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else if (string2 == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"\\\".\\\" operater right value must be defined\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* string3 = env->concat(env, string1, string2);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", string3);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
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
      case SPVM_OPCODE_C_ID_PUSH_ARG_BYTE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_INT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_LONG:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = NULL;\n");
        call_sub_arg_stack_top++;
        
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_BYTE: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, call_sub_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_SHORT: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, call_sub_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_INT: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, call_sub_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_LONG: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, call_sub_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_FLOAT: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, call_sub_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_DOUBLE: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, call_sub_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_OBJECT_TYPE: {
        int32_t rel_id = opcode->operand2;

        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t cast_basic_type_id = type->basic_type_id;
        int32_t cast_type_dimension = type->dimension;
        SPVM_RUNTIME_BASIC_TYPE* cast_basic_type = &runtime->basic_types[cast_basic_type_id];
        const char* cast_basic_type_name = runtime->symbols[cast_basic_type->name_id];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, cast_type_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object != NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == check_basic_type_id && object_type_dimension_id == check_type_dimension) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_raw(env, \"Can't cast uncompatible type.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_INTERFACE_TYPE: {
        int32_t rel_id = opcode->operand2;

        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t cast_basic_type_id = type->basic_type_id;
        int32_t cast_type_dimension = type->dimension;
        SPVM_RUNTIME_BASIC_TYPE* cast_basic_type = &runtime->basic_types[cast_basic_type_id];
        const char* cast_basic_type_name = runtime->symbols[cast_basic_type->name_id];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, cast_type_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object != NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (env->has_interface(env, object_basic_type_id, object_type_dimension_id, check_basic_type_id, check_type_dimension)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_raw(env, \"Can't cast uncompatible type.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB:
      case SPVM_OPCODE_C_ID_CALL_METHOD:
      {
        int32_t var_id = opcode->operand0;
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];

        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];

        int32_t decl_sub_return_basic_type_id = decl_sub->return_basic_type_id;
        int32_t decl_sub_return_type_dimension = decl_sub->return_type_dimension;
        int32_t decl_sub_return_type_flag = decl_sub->return_type_flag;
        
        SPVM_RUNTIME_PACKAGE* decl_sub_package = &runtime->packages[decl_sub->package_id];
        const char* decl_sub_abs_name = runtime->symbols[decl_sub->abs_name_id];
        const char* decl_sub_name = runtime->symbols[decl_sub->name_id];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        const char* decl_sub_package_name = runtime->symbols[decl_sub_package->name_id];
        
        // Declare subroutine return type
        int32_t decl_sub_return_type_is_object = SPVM_RUNTIME_API_is_object_type(env, decl_sub_return_basic_type_id, decl_sub_return_type_dimension, decl_sub_return_type_flag);
        int32_t decl_sub_return_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, decl_sub_return_basic_type_id, decl_sub_return_type_dimension, decl_sub_return_type_flag);
        
        // Declare subroutine argument length
        int32_t decl_sub_args_length = decl_sub->arg_ids_length;

        SPVM_STRING_BUFFER_add(string_buffer, "  // ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_abs_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        // Call subroutine id
        if (opcode_id == SPVM_OPCODE_C_ID_CALL_SUB) {
          SPVM_STRING_BUFFER_add(string_buffer, "    int32_t call_sub_id = ");
          SPVM_STRING_BUFFER_add_sub_id_name(string_buffer, decl_sub_package_name, decl_sub_name);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        else if (opcode_id == SPVM_OPCODE_C_ID_CALL_METHOD) {
          SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand2);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    int32_t call_sub_id = env->get_sub_id_method_call(env, object, \"");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_signature);
          SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    if (call_sub_id < 0) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Subroutine not found ");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_package_name);
          SPVM_STRING_BUFFER_add(string_buffer, " ");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_signature);
          SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      return SPVM_EXCEPTION;\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        }
        else {
          assert(0);
        }


        // Subroutine inline expantion in same package
        if (decl_sub->package_id == sub->package_id && decl_sub->flag & SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC) {
          SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = SPVM_PRECOMPILE_");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_abs_name);
          {
            int32_t index = string_buffer->length - strlen(decl_sub_abs_name);
            
            while (index < string_buffer->length) {
              if (string_buffer->buffer[index] == ':') {
                string_buffer->buffer[index] = '_';
              }
              index++;
            }
          }
          SPVM_STRING_BUFFER_add(string_buffer, "(env, stack);\n");
        }
        // Inline expansion is done in native core function
        else if (strcmp(decl_sub_package_name, "SPVM::CORE") == 0 && decl_sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC) {
          SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = SPVM_NATIVE_SPVM__CORE__");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_name);
          SPVM_STRING_BUFFER_add(string_buffer, "(env, stack);\n");
        }
        // Call subroutine
        else {
          SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = env->call_sub(env, call_sub_id, stack);\n");
        }
        
        // Call subroutine
        SPVM_STRING_BUFFER_add(string_buffer, "    if (!exception_flag) {\n");
        if (decl_sub_return_type_is_value_type) {
          int32_t decl_sub_return_basic_type_id = decl_sub->return_basic_type_id;
          SPVM_RUNTIME_BASIC_TYPE* decl_sub_return_basic_type = &runtime->basic_types[decl_sub_return_basic_type_id];
          SPVM_RUNTIME_PACKAGE* decl_sub_return_package = &runtime->packages[decl_sub_return_basic_type->package_id];
          
          SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(decl_sub_return_package->fields, 0);
          assert(first_field);
          
          for (int32_t field_index = 0; field_index < decl_sub_return_package->fields->length; field_index++) {
            switch (first_field->basic_type_id) {
              case SPVM_BASIC_TYPE_C_ID_BYTE: {
                SPVM_STRING_BUFFER_add(string_buffer, "      ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, var_id, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, " = ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_SHORT: {
                SPVM_STRING_BUFFER_add(string_buffer, "      ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, var_id, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, " = ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_INT: {
                SPVM_STRING_BUFFER_add(string_buffer, "      ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, var_id, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, " = ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_LONG: {
                SPVM_STRING_BUFFER_add(string_buffer, "      ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, var_id, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, " = ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                SPVM_STRING_BUFFER_add(string_buffer, "      ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, " = ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                SPVM_STRING_BUFFER_add(string_buffer, "      ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, " = ");
                SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, field_index);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                break;
              }
              default:
                assert(0);
            }
          }
        }
        else if (decl_sub_return_type_is_object) {
          SPVM_STRING_BUFFER_add(string_buffer, " SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, var_id);
          SPVM_STRING_BUFFER_add(string_buffer, ", stack[0].oval);\n");
        }
        else if ((decl_sub_return_type_dimension == 0 && decl_sub_return_basic_type_id != SPVM_BASIC_TYPE_C_ID_VOID)) {
          switch (decl_sub_return_basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, 0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, 0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, 0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, 0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, 0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            default:
              assert(0);
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        call_sub_arg_stack_top -=  decl_sub_args_length;
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_CATCH: {
        SPVM_RUNTIME_SUB* sub = SPVM_LIST_fetch(package->subs, opcode->operand1);
        int32_t sub_id = sub->id;
        int32_t rel_line = opcode->operand2;
        int32_t line = sub->line + rel_line;
        
        const char* sub_name = runtime->symbols[sub->name_id];
        SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
        const char* package_name = runtime->symbols[sub_package->name_id];
        const char* file = runtime->symbols[sub->file_id];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  if (exception_flag) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* sub_package_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* sub_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* file = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)file);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t line = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->create_exception_stack_trace(env, env->get_exception(env), sub_package_name, sub_name, file, line));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer,  opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_RETURN: {
        SPVM_RUNTIME_SUB* sub = SPVM_LIST_fetch(package->subs, opcode->operand1);
        int32_t sub_id = sub->id;
        int32_t rel_line = opcode->operand2;
        int32_t line = sub->line + rel_line;
        
        const char* sub_name = runtime->symbols[sub->name_id];
        SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
        const char* package_name = runtime->symbols[sub_package->name_id];
        const char* file = runtime->symbols[sub->file_id];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  if (exception_flag) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* sub_package_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* sub_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* file = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)file);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t line = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->create_exception_stack_trace(env, env->get_exception(env), sub_package_name, sub_name, file, line));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CROAK_FLAG_TRUE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  exception_flag = 1;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VOID:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_BYTE: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_SHORT: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_INT: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_LONG: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_FLOAT: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_DOUBLE: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_BYTE:
      {
        int32_t var_id = opcode->operand0;
        int32_t sub_return_type_width = opcode->operand2;
        
        for (int32_t field_index = 0; field_index < sub_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, var_id, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_SHORT:
      {
        int32_t var_id = opcode->operand0;
        int32_t sub_return_type_width = opcode->operand2;
        
        // Value type
        for (int32_t field_index = 0; field_index < sub_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, var_id, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
                    
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_INT:
      {
        int32_t var_id = opcode->operand0;
        int32_t sub_return_type_width = opcode->operand2;
        
        // Value type
        for (int32_t field_index = 0; field_index < sub_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, var_id, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
                    
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_LONG:
      {
        int32_t var_id = opcode->operand0;
        int32_t sub_return_type_width = opcode->operand2;
        
        // Value type
        for (int32_t field_index = 0; field_index < sub_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, var_id, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
                    
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_FLOAT:
      {
        int32_t var_id = opcode->operand0;
        int32_t sub_return_type_width = opcode->operand2;
        
        // Value type
        for (int32_t field_index = 0; field_index < sub_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
                    
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_DOUBLE:
      {
        int32_t var_id = opcode->operand0;
        int32_t sub_return_type_width = opcode->operand2;
        
        // Value type
        for (int32_t field_index = 0; field_index < sub_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_field_index(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
                    
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_OBJECT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&stack[0] = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        // Increment ref count of return value not to release by decrement
        SPVM_STRING_BUFFER_add(string_buffer, "  if (*(void**)&stack[0] != NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(*(void**)&stack[0]);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_UNDEF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&stack[0] = NULL;\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {
        int32_t rel_id = opcode->operand2;
        SPVM_RUNTIME_INFO_SWITCH_INFO* switch_info = SPVM_LIST_fetch(runtime->info_switch_infos, sub->info_switch_infos_base + rel_id);
        SPVM_LIST* case_infos = switch_info->case_infos;

        // default field_index
        int32_t default_opcode_rel_index = switch_info->default_opcode_rel_index;
        
        // case count
        int32_t cases_length = case_infos->length;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  switch(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ") {\n");
        {
          int32_t case_index;
          for (case_index = 0; case_index < cases_length; case_index++) {
            SPVM_RUNTIME_INFO_CASE_INFO* case_info = SPVM_LIST_fetch(case_infos, case_index);
            int32_t match = case_info->match;
            int32_t opcode_rel_index = case_info->opcode_rel_index;
            
            SPVM_STRING_BUFFER_add(string_buffer, "    case ");
            SPVM_STRING_BUFFER_add_int(string_buffer, match);
            SPVM_STRING_BUFFER_add(string_buffer, ": goto L");
            SPVM_STRING_BUFFER_add_int(string_buffer, opcode_rel_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    default: goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, default_opcode_rel_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &numeric_vars");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_t_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
        const char* field_package_name = runtime->symbols[field_package->name_id];
        const char* field_name = runtime->symbols[field->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Object must be not undef.\", 0));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object_field = *(SPVM_VALUE_object*)&fields[");
        SPVM_STRING_BUFFER_add_field_index_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", SPVM_RUNTIME_C_INLINE_GET_OBJECT_NO_WEAKEN_ADDRESS(object_field));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT:
      {
        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
        const char* field_package_name = runtime->symbols[field_package->name_id];
        const char* field_name = runtime->symbols[field->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_raw(env, \"Object must be not undef.\", 0));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object_field_address = (SPVM_VALUE_object*)&fields[");
        SPVM_STRING_BUFFER_add_field_index_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(");
        SPVM_STRING_BUFFER_add(string_buffer, "object_field_address,");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, "    );\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF:
      {
        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
        const char* field_package_name = runtime->symbols[field_package->name_id];
        const char* field_name = runtime->symbols[field->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_string_raw(env, \"Object must be not undef.\", 0));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object_field_address = (SPVM_VALUE_object*)&fields[");
        SPVM_STRING_BUFFER_add_field_index_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_field_address, NULL);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_BYTE:
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_SHORT:
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_INT:
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_LONG:
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_DOUBLE:
      {
        int32_t rel_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
        SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
        const char* package_var_package_name = runtime->symbols[package_var_package->name_id];
        const char* package_var_name = runtime->symbols[package_var->name_id];

        int32_t package_var_access_ctype_id;
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_BYTE:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE;
            break;
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_SHORT:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT;
            break;
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_INT:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT;
            break;
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_LONG:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG;
            break;
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_FLOAT:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT;
            break;
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_DOUBLE:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE;
            break;
          default:
            assert(0);
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, package_var_access_ctype_id, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, package_var_access_ctype_id));
        SPVM_STRING_BUFFER_add(string_buffer, "*)");
        SPVM_STRING_BUFFER_add(string_buffer, "&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "]");
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_OBJECT: {
        int32_t rel_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
        SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
        const char* package_var_package_name = runtime->symbols[package_var_package->name_id];
        const char* package_var_name = runtime->symbols[package_var->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", *(void**)");
        SPVM_STRING_BUFFER_add(string_buffer, "&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "]);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_BYTE:
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_SHORT:
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_INT:
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_LONG:
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_DOUBLE:
      {
        int32_t rel_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
        SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
        const char* package_var_package_name = runtime->symbols[package_var_package->name_id];
        const char* package_var_name = runtime->symbols[package_var->name_id];

        int32_t package_var_access_ctype_id;
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_BYTE:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE;
            break;
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_SHORT:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT;
            break;
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_INT:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT;
            break;
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_LONG:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG;
            break;
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_FLOAT:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT;
            break;
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_DOUBLE:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE;
            break;
          default:
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS;
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, package_var_access_ctype_id));
        SPVM_STRING_BUFFER_add(string_buffer, "*)");
        SPVM_STRING_BUFFER_add(string_buffer, "&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "]");
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, package_var_access_ctype_id, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_OBJECT: {
        int32_t rel_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
        SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
        const char* package_var_package_name = runtime->symbols[package_var_package->name_id];
        const char* package_var_name = runtime->symbols[package_var->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "],\n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_UNDEF: {
        int32_t rel_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
        SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
        const char* package_var_package_name = runtime->symbols[package_var_package->name_id];
        const char* package_var_name = runtime->symbols[package_var->name_id];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "], NULL);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", env->get_exception(env));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  env->set_exception(env, ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  env->set_exception(env, NULL);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_END_SUB: {
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_byte value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_byte_object;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_byte*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_short value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_short_object;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_short*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_int value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_int_object;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_int*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_long value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_long_object;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_long*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_float value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_float_object;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_float*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_double value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_double_object;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_double*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_OBJECT_TO_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_byte_object && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_byte*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_OBJECT_TO_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_short_object && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_short*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_OBJECT_TO_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_int_object && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_int*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_OBJECT_TO_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_long_object && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_long*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_OBJECT_TO_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_float_object && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_float*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_OBJECT_TO_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_ADDRESS, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_double_object && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_double*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      default:
        assert(0);
    }
    opcode_index++;
  }
  
  // No exception
  SPVM_STRING_BUFFER_add(string_buffer, "  if (!exception_flag) {\n");
  if (sub_return_type_is_object_type) {
    SPVM_STRING_BUFFER_add(string_buffer, "    if (stack[0].oval != NULL) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(stack[0].oval); }\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "  return exception_flag;\n");
  
  // Close subroutine
  SPVM_STRING_BUFFER_add(string_buffer, "}\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
}

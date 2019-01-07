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

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_arg.h"

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
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT:
      return "void*";
      break;
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF:
      return "void*";
      break;
  }
  
  return NULL;
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index) {
  
  switch (ctype_id) {
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "byte_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "short_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "int_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "long_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "float_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "double_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT: {
      SPVM_STRING_BUFFER_add(string_buffer, "object_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF: {
      SPVM_STRING_BUFFER_add(string_buffer, "ref_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    default:
      assert(0);
  }
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var_value(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index, int32_t field_index) {
  switch (ctype_id) {
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "byte_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "short_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "int_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "long_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "float_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "double_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    default:
      assert(0);
  }
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, ctype_id, var_index);
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)*(void**)&");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, var_index);
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&");
  SPVM_STRING_BUFFER_add(string_buffer, "stack[");
  SPVM_STRING_BUFFER_add_int(string_buffer, var_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index, int32_t field_index) {
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var_value(env, string_buffer, ctype_id, var_index, field_index);
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
  SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_str_raw(env, \"0 division\", 0));\n");
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
  SPVM_STRING_BUFFER_add(string_buffer, "    void* exception = env->new_str_raw(env, \"0 division\", 0);\n");
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
  SPVM_STRING_BUFFER_add(string_buffer, " << ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
  }
  else if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_logical_shift(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, ")((u");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, ")");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
  }
  else if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_arithmetic_shift(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
  }
  else if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
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
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_str_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, element_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_STRING_BUFFER_add(string_buffer, "((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[index]; \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_str_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[index] \n");
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, element_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index, int32_t field_length) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_str_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  {
    int32_t field_index;
    for (field_index = 0; field_index < field_length; field_index++) {
      SPVM_STRING_BUFFER_add(string_buffer, "        ");
      SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, element_ctype_id, out_index, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, " = ");
      SPVM_STRING_BUFFER_add(string_buffer, "((");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
      SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
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

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index, int32_t field_length, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_str_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, element_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " =");
  SPVM_STRING_BUFFER_add(string_buffer, "((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_length);
  SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]; \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index, int32_t field_length) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_str_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  
  {
    int32_t field_index;
    for (field_index = 0; field_index < field_length; field_index++) {
      SPVM_STRING_BUFFER_add(string_buffer, "      ((");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
      SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
      SPVM_STRING_BUFFER_add_int(string_buffer, field_length);
      SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
      SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      SPVM_STRING_BUFFER_add(string_buffer, " = ");
      SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, element_ctype_id, in_index, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, ";\n");
    }
  }

  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index, int32_t field_length, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_str_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        ((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
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

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_var_id, int32_t ref_var_id, int32_t field_length) {

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  switch (element_ctype_id) {
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_byte* value_ref = *(SPVM_VALUE_byte**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_short* value_ref = *(SPVM_VALUE_short**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_int* value_ref = *(SPVM_VALUE_int**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_long* value_ref = *(SPVM_VALUE_long**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_float* value_ref = *(SPVM_VALUE_float**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_double* value_ref = *(SPVM_VALUE_double**)&ref_vars[");
      break;
    }
  }
  SPVM_STRING_BUFFER_add_int(string_buffer, ref_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  for (int32_t field_index = 0; field_index < field_length; field_index++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    *(");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
    SPVM_STRING_BUFFER_add(string_buffer, "*)&");
    switch (element_ctype_id) {
      case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "byte_vars");
        break;
      }
      case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "short_vars");
        break;
      }
      case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "int_vars");
        break;
      }
      case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "long_vars");
        break;
      }
      case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "float_vars");
        break;
      }
      case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "double_vars");
        break;
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, "[");
    SPVM_STRING_BUFFER_add_int(string_buffer, out_var_id);
    SPVM_STRING_BUFFER_add(string_buffer, " + ");
    SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
    SPVM_STRING_BUFFER_add(string_buffer, "] ");
    SPVM_STRING_BUFFER_add(string_buffer,  " = ");
    SPVM_STRING_BUFFER_add(string_buffer, "*(");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
    SPVM_STRING_BUFFER_add(string_buffer, "*)&value_ref[");
    SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_get_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_var_id, int32_t ref_var_id, int32_t field_index) {

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  switch (element_ctype_id) {
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_byte* value_ref = *(SPVM_VALUE_byte**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_short* value_ref = *(SPVM_VALUE_short**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_int* value_ref = *(SPVM_VALUE_int**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_long* value_ref = *(SPVM_VALUE_long**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_float* value_ref = *(SPVM_VALUE_float**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_double* value_ref = *(SPVM_VALUE_double**)&ref_vars[");
      break;
    }
  }
  SPVM_STRING_BUFFER_add_int(string_buffer, ref_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&");
  switch (element_ctype_id) {
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "byte_vars");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "short_vars");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "int_vars");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "long_vars");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "float_vars");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "double_vars");
      break;
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "[");
  SPVM_STRING_BUFFER_add_int(string_buffer, out_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "]");
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&value_ref[");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_set_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t ref_var_id, int32_t in_var_id, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  switch (element_ctype_id) {
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_byte* value_ref = *(SPVM_VALUE_byte**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_short* value_ref = *(SPVM_VALUE_short**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_int* value_ref = *(SPVM_VALUE_int**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_long* value_ref = *(SPVM_VALUE_long**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_float* value_ref = *(SPVM_VALUE_float**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_double* value_ref = *(SPVM_VALUE_double**)&ref_vars[");
      break;
    }
  }
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
  SPVM_STRING_BUFFER_add(string_buffer, "*)&");
  switch (element_ctype_id) {
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "byte_vars");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "short_vars");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "int_vars");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "long_vars");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "float_vars");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "double_vars");
      break;
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "[");
  SPVM_STRING_BUFFER_add_int(string_buffer, in_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
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
  const char* field_package_name = &runtime->string_pool[field_package->name_id];
  const char* field_name = &runtime->string_pool[field->name_id];
  const char* field_signature = &runtime->string_pool[field->signature_id];

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
  SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " = env->field_id(env, \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
  SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (");
  SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Field not found ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
  SPVM_STRING_BUFFER_add(string_buffer, " ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " = env->field_offset(env, ");
  SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    };\n");

  SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, object_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Object must be not undef.\", 0));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, field_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, field_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)object + object_header_byte_size + ");
  SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t field_ctype_id, int32_t object_index, SPVM_RUNTIME_FIELD* field, int32_t in_index) {
  SPVM_RUNTIME* runtime = env->runtime;

  SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
  const char* field_package_name = &runtime->string_pool[field_package->name_id];
  const char* field_name = &runtime->string_pool[field->name_id];
  const char* field_signature = &runtime->string_pool[field->signature_id];

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
  SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " = env->field_id(env, \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
  SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (");
  SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Field not found ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
  SPVM_STRING_BUFFER_add(string_buffer, " ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " = env->field_offset(env, ");
  SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    };\n");

  SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, object_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Object must be not undef.\", 0));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, field_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)object + object_header_byte_size + ");
  SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, ") = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, field_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_build_package_csource(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, const char* package_name) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name);
  
  // Package name
  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
  
  // Head part - include and define
  SPVM_CSOURCE_BUILDER_PRECOMPILE_build_head(env, string_buffer);

  // Package variable id declarations
  SPVM_STRING_BUFFER_add(string_buffer, "// Package variable id declarations\n");
  {
    int32_t no_dup_package_var_access_package_var_ids_length = runtime->constant_pool[package->constant_pool_base + package->no_dup_package_var_access_package_var_ids_constant_pool_id];
    for (int32_t constant_pool_index = 0; constant_pool_index < no_dup_package_var_access_package_var_ids_length; constant_pool_index++) {
      int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + package->no_dup_package_var_access_package_var_ids_constant_pool_id + 1 + constant_pool_index];
      SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
      SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
      const char* package_var_package_name = &runtime->string_pool[package_var_package->name_id];
      const char* package_var_name = &runtime->string_pool[package_var->name_id];
      
      SPVM_STRING_BUFFER_add(string_buffer, "static int32_t ");
      SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
      SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");
    }
  }

  // Field id and index declarations
  SPVM_STRING_BUFFER_add(string_buffer, "// Field id and index declarations\n");
  {
    int32_t no_dup_field_access_field_ids_length = runtime->constant_pool[package->constant_pool_base + package->no_dup_field_access_field_ids_constant_pool_id];
    for (int32_t constant_pool_index = 0; constant_pool_index < no_dup_field_access_field_ids_length; constant_pool_index++) {
      int32_t field_id = runtime->constant_pool[package->constant_pool_base + package->no_dup_field_access_field_ids_constant_pool_id + 1 + constant_pool_index];
      SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
      SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
      const char* field_package_name = &runtime->string_pool[field_package->name_id];
      const char* field_name = &runtime->string_pool[field->name_id];
      
      SPVM_STRING_BUFFER_add(string_buffer, "static int32_t ");
      SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
      SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");
      SPVM_STRING_BUFFER_add(string_buffer, "static int32_t ");
      SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
      SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");
    }
  }

  // Sub id declarations
  SPVM_STRING_BUFFER_add(string_buffer, "// Sub id declarations\n");
  {
    int32_t no_dup_call_sub_sub_ids_length = runtime->constant_pool[package->constant_pool_base + package->no_dup_call_sub_sub_ids_constant_pool_id];
    for (int32_t constant_pool_index = 0; constant_pool_index < no_dup_call_sub_sub_ids_length; constant_pool_index++) {
      int32_t sub_id = runtime->constant_pool[package->constant_pool_base + package->no_dup_call_sub_sub_ids_constant_pool_id + 1 + constant_pool_index];
      SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
      SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
      const char* sub_package_name = &runtime->string_pool[sub_package->name_id];
      const char* sub_name = &runtime->string_pool[sub->name_id];
      
      SPVM_STRING_BUFFER_add(string_buffer, "static int32_t ");
      SPVM_STRING_BUFFER_add_sub_id_name(string_buffer, sub_package_name, sub_name);
      SPVM_STRING_BUFFER_add(string_buffer, " = - 1;\n");
    }
  }

  // Basic type id declarations
  SPVM_STRING_BUFFER_add(string_buffer, "// Basic type id declarations\n");
  {
    int32_t no_dup_basic_type_ids_length = runtime->constant_pool[package->constant_pool_base + package->no_dup_basic_type_ids_constant_pool_id];
    for (int32_t constant_pool_index = 0; constant_pool_index < no_dup_basic_type_ids_length; constant_pool_index++) {
      int32_t basic_type_id = runtime->constant_pool[package->constant_pool_base + package->no_dup_basic_type_ids_constant_pool_id + 1 + constant_pool_index];
      SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
      const char* basic_type_name = &runtime->string_pool[basic_type->name_id];
      
      SPVM_STRING_BUFFER_add(string_buffer, "static int32_t ");
      SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
      SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");
    }
  }
  
  // Subroutine decrations
  SPVM_STRING_BUFFER_add(string_buffer, "// Function Declarations\n");
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < package->subs_length; sub_index++) {
      SPVM_RUNTIME_SUB* sub = &runtime->subs[package->subs_base + sub_index];
      const char* sub_name = &runtime->string_pool[sub->name_id];
      const char* sub_signature = &runtime->string_pool[sub->signature_id];
      if (sub->flag & SPVM_SUB_C_FLAG_PRECOMPILE) {
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
    for (sub_index = 0; sub_index < package->subs_length; sub_index++) {
      SPVM_RUNTIME_SUB* sub = &runtime->subs[package->subs_base + sub_index];
      if (sub->flag & SPVM_SUB_C_FLAG_PRECOMPILE) {
        const char* sub_name = &runtime->string_pool[sub->name_id];
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
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Inline macro function
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stdlib.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <string.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stdio.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <inttypes.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <math.h>\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_API_GET_OBJECT_NO_WEAKEN_ADDRESS(object) ((void*)((intptr_t)object & ~(intptr_t)1))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_API_GET_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset)))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_API_INC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))++)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_API_INC_REF_COUNT(object)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "do {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_INC_REF_COUNT_ONLY(object);\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_API_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))--)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_API_DEC_REF_COUNT(object)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "do {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_RUNTIME_API_GET_REF_COUNT(object) > 1) { SPVM_RUNTIME_API_DEC_REF_COUNT_ONLY(object); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { env->dec_ref_count(env, object); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_API_ISWEAK(dist_address) (((intptr_t)*(void**)dist_address) & 1)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_RUNTIME_API_OBJECT_ASSIGN(dist_address, src_object) \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "do {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* tmp_object = SPVM_RUNTIME_API_GET_OBJECT_NO_WEAKEN_ADDRESS(src_object);\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (tmp_object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_INC_REF_COUNT_ONLY(tmp_object);\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (*(void**)(dist_address) != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_RUNTIME_API_ISWEAK(dist_address)) { env->unweaken(env, dist_address); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_RUNTIME_API_GET_REF_COUNT(*(void**)(dist_address)) > 1) { SPVM_RUNTIME_API_DEC_REF_COUNT_ONLY(*(void**)(dist_address)); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { env->dec_ref_count(env, *(void**)(dist_address)); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)(dist_address) = tmp_object;\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#endif\n");

}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_build_sub_declaration(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* sub_name) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name);
  
  // Package name
  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];

  SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);

  assert(sub->flag & SPVM_SUB_C_FLAG_PRECOMPILE);
  
  // Return type
  SPVM_STRING_BUFFER_add(string_buffer, "int32_t ");
        
  // Subroutine name. Replace : to _
  SPVM_STRING_BUFFER_add(string_buffer, "SPVM_PRECOMPILE_");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)package_name);
  SPVM_STRING_BUFFER_add(string_buffer, (char*)"__");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
  {
    int32_t index = string_buffer->length - (strlen(package_name) + 2 + strlen(sub_name));
    
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
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name);
  
  // Package name
  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];

  SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);

  assert(sub->flag & SPVM_SUB_C_FLAG_PRECOMPILE);
  
  SPVM_CSOURCE_BUILDER_PRECOMPILE_build_sub_declaration(env, string_buffer, package_name, sub_name);

  // Block start
  SPVM_STRING_BUFFER_add(string_buffer, " {\n");
  
  // Object header byte size
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t object_header_byte_size = (intptr_t)env->object_header_byte_size;");
  
  // Call subroutine argument stack top
  int32_t call_sub_arg_stack_top = 0;

  // object variable declarations
  int32_t object_vars_alloc_length = sub->object_vars_alloc_length;
  if (object_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  void* object_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, object_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // ref variable declarations
  int32_t ref_vars_alloc_length = sub->ref_vars_alloc_length;
  if (ref_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  void* ref_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, ref_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // double variable declarations
  int32_t double_vars_alloc_length = sub->double_vars_alloc_length;
  if (double_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  double double_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, double_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // float variable declarations
  int32_t float_vars_alloc_length = sub->float_vars_alloc_length;
  if (float_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  float float_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, float_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // long variable declarations
  int32_t long_vars_alloc_length = sub->long_vars_alloc_length;
  if (long_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int64_t long_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, long_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // int variable declarations
  int32_t int_vars_alloc_length = sub->int_vars_alloc_length;
  if (int_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t int_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, int_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // Exception
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t exception_flag = 0;\n");

  // Condition flag
  SPVM_STRING_BUFFER_add(string_buffer, "  register int32_t condition_flag;\n");

  if (sub->mortal_stack_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t mortal_stack[");
    SPVM_STRING_BUFFER_add_int(string_buffer, sub->mortal_stack_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t mortal_stack_top = 0;\n");
  }
  
  // short variable declarations
  int32_t short_vars_alloc_length = sub->short_vars_alloc_length;
  if (short_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int16_t short_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, short_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // byte variable declarations
  int32_t byte_vars_alloc_length = sub->byte_vars_alloc_length;
  if (byte_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int8_t byte_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, byte_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // Convert string
  SPVM_STRING_BUFFER_add(string_buffer, "  char convert_string_buffer[21];\n");
  
  // Copy arguments to variables with type information
  if (sub->arg_ids_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  // Copy arguments to variables\n");
  }
  {
    int32_t stack_index = 0;
    for (int32_t arg_index = 0; arg_index < sub->arg_ids_length; arg_index++) {
      SPVM_RUNTIME_ARG* arg = &runtime->args[sub->arg_ids_base + arg_index];

      // Numeric type
      int32_t type_width = arg->type_width;
      switch (arg->runtime_type) {
        case SPVM_TYPE_C_RUNTIME_TYPE_BYTE: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, arg->var_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_SHORT: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, arg->var_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_INT: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, arg->var_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_LONG: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, arg->var_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_FLOAT: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, arg->var_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_DOUBLE: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, arg->var_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_BYTE: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, arg->var_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_SHORT: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, arg->var_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_INT: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, arg->var_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_LONG: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, arg->var_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_FLOAT: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, arg->var_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_DOUBLE: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, arg->var_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_ANY_OBJECT:
        case SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE:
        case SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY:
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY:
        case SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY:
        {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, arg->var_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");

          SPVM_STRING_BUFFER_add(string_buffer, "  if (");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, arg->var_id);
          SPVM_STRING_BUFFER_add(string_buffer, " != NULL) { SPVM_RUNTIME_API_INC_REF_COUNT_ONLY(");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, arg->var_id);
          SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_BYTE:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_SHORT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_INT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_LONG:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_FLOAT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_DOUBLE:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_BYTE:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_SHORT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_INT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_LONG:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_FLOAT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_DOUBLE:
        {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, arg->var_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        default : {
          assert(0);
        }
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_IS_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL);\n");
        break;
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_eq(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0, opcode->operand1);
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_ne(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0, opcode->operand1);
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
      case SPVM_OPCODE_C_ID_IS_TYPE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t type_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = &runtime->string_pool[basic_type->name_id];
        int32_t dimension = type_dimension;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      condition_flag = (object_basic_type_id == check_basic_type_id && object_type_dimension == check_type_dimension);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      condition_flag = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_HAS_INTERFACE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t type_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = &runtime->string_pool[basic_type->name_id];
        int32_t dimension = type_dimension;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t interface_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t interface_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      condition_flag = env->has_interface(env, object, interface_basic_type_id);\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object2 = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length1 = *(SPVM_VALUE_int*)((intptr_t)object1 + (intptr_t)env->object_array_length_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t lenght2 = *(SPVM_VALUE_int*)((intptr_t)object2 + (intptr_t)env->object_array_length_offset);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_byte* bytes1 = env->belems(env, object1);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_byte* bytes2 = env->belems(env, object2);\n");
        
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
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_left_shift(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_left_shift(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_arithmetic_shift(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_arithmetic_shift(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_logical_shift(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_logical_shift(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
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
      case SPVM_OPCODE_C_ID_BIT_NOT_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_complement(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_BIT_NOT_LONG:
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
      case SPVM_OPCODE_C_ID_CONVERT_STRING_TO_BYTE_ARRAY:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* src_string = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t src_string_length = env->len(env, src_string);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int8_t* src_string_data = env->belems(env, src_string);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string = env->new_str_raw(env, (const char*)src_string_data, src_string_length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", string);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
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
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%\" PRId8, ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%\" PRId16, ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%\" PRId32, ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%\" PRId64, ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%g\", ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%g\", ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t string_length = strlen(convert_string_buffer);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string = env->new_str_raw(env, convert_string_buffer, string_length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", string);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_CHAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = '");
        SPVM_STRING_BUFFER_add_hex_char(string_buffer, (int8_t)(uint8_t)opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "';\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (int32_t)((opcode->operand1 << 16) + opcode->operand2));
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_LONG: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t high_value = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t low_value = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        
        int64_t long_value = (int64_t)(((uint64_t)(uint32_t)high_value << 32) + (uint64_t)(uint32_t)low_value);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_long(string_buffer, long_value);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_FLOAT: {
        SPVM_VALUE value;
        value.ival = (int32_t)((opcode->operand1 << 16) + opcode->operand2);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_float(string_buffer, value.fval);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_DOUBLE: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t high_value = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t low_value = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];

        SPVM_VALUE value;
        value.lval = (int64_t)(((uint64_t)(uint32_t)high_value << 32) + (uint64_t)(uint32_t)low_value);

        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_double(string_buffer, value.dval);
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_OBJECT:
        SPVM_STRING_BUFFER_add(string_buffer, "  {");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Array must not be undef\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_str_raw(env, \"Index is out of range\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* object = ((SPVM_VALUE_object*)((intptr_t)array + object_header_byte_size))[index];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_BYTE: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_SHORT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_INT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_LONG: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_FLOAT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_DOUBLE: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Array must not be undef\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "          env->set_exception(env, env->new_str_raw(env, \"Index is out of range\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "          exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* object_address = &((SPVM_VALUE_object*)((intptr_t)array + object_header_byte_size))[index];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_RUNTIME_API_OBJECT_ASSIGN(\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          object_address, ");
        SPVM_STRING_BUFFER_add(string_buffer, "        ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Array must not be undef\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0 || ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "  >= *(int32_t*)((intptr_t)");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " + (intptr_t)env->object_array_length_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_str_raw(env, \"Index is out of range\", 0)); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* object_address = &((SPVM_VALUE_object*)((intptr_t)array + object_header_byte_size))[index];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_RUNTIME_API_OBJECT_ASSIGN(\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          object_address,\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          NULL");
        SPVM_STRING_BUFFER_add(string_buffer, "        );\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }");
        
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_BYTE: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_SHORT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_INT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_LONG: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_FLOAT: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_DOUBLE: {
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, field_length, field_index);
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
          SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ", ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
          SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      case SPVM_OPCODE_C_ID_MOVE_UNDEF:
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", NULL);\n");
        break;
      case SPVM_OPCODE_C_ID_MOVE_REF:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_VALUE_MOVE_BYTE: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_SHORT: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_INT: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_LONG: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_FLOAT: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_DOUBLE: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
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
          SPVM_STRING_BUFFER_add(string_buffer, "        void** object_address = (void**)&object_vars[var_index];\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        if (*object_address != NULL) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "          if (SPVM_RUNTIME_API_GET_REF_COUNT(*object_address) > 1) { SPVM_RUNTIME_API_DEC_REF_COUNT_ONLY(*object_address); }\n");
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
        int32_t constant_pool_id = opcode->operand1;
        int32_t basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t type_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = &runtime->string_pool[basic_type->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_obj_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
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
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_barray_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
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
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_sarray_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
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
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_iarray_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
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
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_larray_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
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
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_farray_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
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
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_darray_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t type_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = &runtime->string_pool[basic_type->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_oarray_raw(env, basic_type_id, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t type_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = &runtime->string_pool[basic_type->name_id];
        int32_t element_dimension = type_dimension - 1;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_marray_raw(env, basic_type_id, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, element_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ", length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_VALUE_ARRAY: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t type_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
        const char* basic_type_name = &runtime->string_pool[basic_type->name_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(SPVM_VALUE_int*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_varray_raw(env, basic_type_id, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Array length must be more than or equal to 0\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t string_length = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t string_pool_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        const char* string_value = &runtime->string_pool[string_pool_id];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add(string_buffer, "env->new_str_raw(env, \"");
        
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_str_raw(env, \"Can't get array length of undef value.\", 0));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int32_t*)((intptr_t)");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " + (intptr_t)env->object_array_length_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
        const char* field_package_name = &runtime->string_pool[field_package->name_id];
        const char* field_name = &runtime->string_pool[field->name_id];
        const char* field_signature = &runtime->string_pool[field->signature_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t ");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t ");
        SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->field_offset(env, ");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Object to weaken an object field must not be undefined.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void** ofield_address = (SPVM_VALUE_object*)((intptr_t)object + object_header_byte_size + ");
        SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->weaken(env, ofield_address);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_ARRAY_ELEMENT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(!array, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Array must not be undef\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Index is out of range\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE_object* elements = (void**)((intptr_t)array + env->object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void** object_element_address = (void**)&elements[index];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->weaken(env, object_element_address);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONCAT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string1 = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string2 = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (string1 == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"\\\".\\\" operater left value must be defined\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else if (string2 == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"\\\".\\\" operater right value must be defined\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* string3 = env->concat_raw(env, string1, string2);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_REF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, call_sub_arg_stack_top);
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
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
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
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
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
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
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
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
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
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
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
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_OBJECT_TYPE: {
        int32_t constant_pool_id = opcode->operand2;

        int32_t cast_basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t cast_type_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        SPVM_RUNTIME_BASIC_TYPE* cast_basic_type = &runtime->basic_types[cast_basic_type_id];
        const char* cast_basic_type_name = &runtime->string_pool[cast_basic_type->name_id];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, cast_type_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object != NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == check_basic_type_id && object_type_dimension_id == check_type_dimension) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Can't cast uncompatible type.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_INTERFACE: {
        int32_t constant_pool_id = opcode->operand2;

        int32_t cast_basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t cast_type_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        SPVM_RUNTIME_BASIC_TYPE* cast_basic_type = &runtime->basic_types[cast_basic_type_id];
        const char* cast_basic_type_name = &runtime->string_pool[cast_basic_type->name_id];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t interface_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(string_buffer, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t interface_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, cast_type_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object != NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (env->has_interface(env, object, interface_basic_type_id)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Can't cast uncompatible type.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VOID:
      case SPVM_OPCODE_C_ID_CALL_SUB_BYTE:
      case SPVM_OPCODE_C_ID_CALL_SUB_SHORT:
      case SPVM_OPCODE_C_ID_CALL_SUB_INT:
      case SPVM_OPCODE_C_ID_CALL_SUB_LONG:
      case SPVM_OPCODE_C_ID_CALL_SUB_FLOAT:
      case SPVM_OPCODE_C_ID_CALL_SUB_DOUBLE:
      case SPVM_OPCODE_C_ID_CALL_SUB_OBJECT:
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_BYTE:
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_SHORT:
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_INT:
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_LONG:
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_FLOAT:
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_DOUBLE:
      case SPVM_OPCODE_C_ID_CALL_METHOD_VOID:
      case SPVM_OPCODE_C_ID_CALL_METHOD_BYTE:
      case SPVM_OPCODE_C_ID_CALL_METHOD_SHORT:
      case SPVM_OPCODE_C_ID_CALL_METHOD_INT:
      case SPVM_OPCODE_C_ID_CALL_METHOD_LONG:
      case SPVM_OPCODE_C_ID_CALL_METHOD_FLOAT:
      case SPVM_OPCODE_C_ID_CALL_METHOD_DOUBLE:
      case SPVM_OPCODE_C_ID_CALL_METHOD_OBJECT:
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_BYTE:
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_SHORT:
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_INT:
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_LONG:
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_FLOAT:
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_DOUBLE:
      {
        int8_t is_sub;
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_CALL_SUB_VOID:
          case SPVM_OPCODE_C_ID_CALL_SUB_BYTE:
          case SPVM_OPCODE_C_ID_CALL_SUB_SHORT:
          case SPVM_OPCODE_C_ID_CALL_SUB_INT:
          case SPVM_OPCODE_C_ID_CALL_SUB_LONG:
          case SPVM_OPCODE_C_ID_CALL_SUB_FLOAT:
          case SPVM_OPCODE_C_ID_CALL_SUB_DOUBLE:
          case SPVM_OPCODE_C_ID_CALL_SUB_OBJECT:
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_BYTE:
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_SHORT:
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_INT:
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_LONG:
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_FLOAT:
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_DOUBLE:
            is_sub = 1;
            break;
          case SPVM_OPCODE_C_ID_CALL_METHOD_VOID:
          case SPVM_OPCODE_C_ID_CALL_METHOD_BYTE:
          case SPVM_OPCODE_C_ID_CALL_METHOD_SHORT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_INT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_LONG:
          case SPVM_OPCODE_C_ID_CALL_METHOD_FLOAT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_DOUBLE:
          case SPVM_OPCODE_C_ID_CALL_METHOD_OBJECT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_BYTE:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_SHORT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_INT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_LONG:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_FLOAT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_DOUBLE:
            is_sub = 0;
            break;
          default:
            assert(0);
        }
        
        int32_t var_id = opcode->operand0;
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];

        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];

        SPVM_RUNTIME_PACKAGE* decl_sub_package = &runtime->packages[decl_sub->package_id];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        const char* decl_sub_package_name = &runtime->string_pool[decl_sub_package->name_id];
        
        // Declare subroutine argument length
        int32_t decl_sub_args_length = decl_sub->arg_ids_length;

        SPVM_STRING_BUFFER_add(string_buffer, "  // ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "->");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        // Call subroutine
        if (is_sub) {
          SPVM_STRING_BUFFER_add(string_buffer, "    if (");
          SPVM_STRING_BUFFER_add_sub_id_name(string_buffer, decl_sub_package_name, decl_sub_name);
          SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      ");
          SPVM_STRING_BUFFER_add_sub_id_name(string_buffer, decl_sub_package_name, decl_sub_name);
          SPVM_STRING_BUFFER_add(string_buffer, " = env->sub_id(env, \"");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_package_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_signature);
          SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      if (");
          SPVM_STRING_BUFFER_add_sub_id_name(string_buffer, decl_sub_package_name, decl_sub_name);
          SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Subroutine not found ");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_package_name);
          SPVM_STRING_BUFFER_add(string_buffer, " ");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    int32_t call_sub_id = ");
          SPVM_STRING_BUFFER_add_sub_id_name(string_buffer, decl_sub_package_name, decl_sub_name);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        // Call method
        else {
          SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    int32_t call_sub_id = env->method_sub_id(env, object, \"");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_signature);
          SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    if (call_sub_id == 0) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Subroutine not found ");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_package_name);
          SPVM_STRING_BUFFER_add(string_buffer, " ");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "      return SPVM_EXCEPTION;\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        }
        
        // Subroutine inline expantion in same package
        if (decl_sub->package_id == sub->package_id && decl_sub->flag & SPVM_SUB_C_FLAG_PRECOMPILE) {
          SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = SPVM_PRECOMPILE_");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_package_name);
          SPVM_STRING_BUFFER_add(string_buffer, (char*)"__");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_sub_name);
          {
            int32_t index = string_buffer->length - (strlen(decl_sub_package_name) + 2 + strlen(decl_sub_name));
            
            while (index < string_buffer->length) {
              if (string_buffer->buffer[index] == ':') {
                string_buffer->buffer[index] = '_';
              }
              index++;
            }
          }
          SPVM_STRING_BUFFER_add(string_buffer, "(env, stack);\n");
        }
        // Call subroutine
        else {
          SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = env->call_sub(env, call_sub_id, stack);\n");
        }
        
        // Call subroutine
        SPVM_STRING_BUFFER_add(string_buffer, "    if (!exception_flag) {\n");
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_CALL_SUB_VOID:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VOID:
            break;
          case SPVM_OPCODE_C_ID_CALL_SUB_BYTE:
          case SPVM_OPCODE_C_ID_CALL_METHOD_BYTE: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_SHORT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_SHORT: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_INT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_INT: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_LONG:
          case SPVM_OPCODE_C_ID_CALL_METHOD_LONG: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_FLOAT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_FLOAT: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_DOUBLE:
          case SPVM_OPCODE_C_ID_CALL_METHOD_DOUBLE: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_OBJECT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_OBJECT: {
            SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, ", stack[0].oval);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_BYTE:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_BYTE: {
            int32_t decl_sub_return_type_field_length = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_sub_return_type_field_length; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_SHORT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_SHORT: {
            int32_t decl_sub_return_type_field_length = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_sub_return_type_field_length; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_LONG:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_LONG: {
            int32_t decl_sub_return_type_field_length = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_sub_return_type_field_length; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_FLOAT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_FLOAT: {
            int32_t decl_sub_return_type_field_length = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_sub_return_type_field_length; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_DOUBLE:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_DOUBLE: {
            int32_t decl_sub_return_type_field_length = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_sub_return_type_field_length; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_INT:
          case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_INT: {
            int32_t decl_sub_return_type_field_length = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_sub_return_type_field_length; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          default:
            assert(0);
        }

        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        call_sub_arg_stack_top -=  decl_sub_args_length;
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_CATCH: {
        SPVM_RUNTIME_SUB* sub = &runtime->subs[package->subs_base + opcode->operand1];
        int32_t sub_id = sub->id;
        int32_t rel_line = opcode->operand2;
        int32_t line = sub->line + rel_line;
        
        const char* sub_name = &runtime->string_pool[sub->name_id];
        SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
        const char* package_name = &runtime->string_pool[sub_package->name_id];
        const char* file = &runtime->string_pool[sub->file_id];
        
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
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_stack_trace_raw(env, env->exception(env), sub_package_name, sub_name, file, line));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer,  opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_RETURN: {
        SPVM_RUNTIME_SUB* sub = &runtime->subs[package->subs_base + opcode->operand1];
        int32_t sub_id = sub->id;
        int32_t rel_line = opcode->operand2;
        int32_t line = sub->line + rel_line;
        
        const char* sub_name = &runtime->string_pool[sub->name_id];
        SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
        const char* package_name = &runtime->string_pool[sub_package->name_id];
        const char* file = &runtime->string_pool[sub->file_id];
        
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
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_stack_trace_raw(env, env->exception(env), sub_package_name, sub_name, file, line));\n");
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
        
        // Value type
        for (int32_t field_index = 0; field_index < sub_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, var_id + field_index);
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
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, var_id + field_index);
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
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, var_id + field_index);
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
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, var_id + field_index);
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
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id + field_index);
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
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id + field_index);
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        // Increment ref count of return value not to release by decrement
        SPVM_STRING_BUFFER_add(string_buffer, "  if (*(void**)&stack[0] != NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_INC_REF_COUNT_ONLY(*(void**)&stack[0]);\n");
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
      case SPVM_OPCODE_C_ID_TABLE_SWITCH: {
        int32_t constant_pool_id = opcode->operand1;
        
        // Default branch
        int32_t default_opcode_rel_index = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        // Min
        int32_t min = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        
        // Max
        int32_t max = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 2];
        
        // Range
        int32_t range = max - min + 1;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  switch(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ") {\n");
        for (int32_t i = min; i <= max; i++) {
          int32_t offset = i - min;
          int32_t opcode_rel_index = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 3 + offset];
          
          SPVM_STRING_BUFFER_add(string_buffer, "    case ");
          SPVM_STRING_BUFFER_add_int(string_buffer, i);
          SPVM_STRING_BUFFER_add(string_buffer, ": goto L");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode_rel_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    default: goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, default_opcode_rel_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {
        int32_t constant_pool_id = opcode->operand1;

        // default branch
        int32_t default_opcode_rel_index = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        // case count
        int32_t case_infos_length = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  switch(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ") {\n");
        for (int32_t case_index = 0; case_index < case_infos_length; case_index++) {
          int32_t match = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 2 + (2 * case_index)];
          int32_t opcode_rel_index = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 2 + (2 * case_index) + 1];
          
          SPVM_STRING_BUFFER_add(string_buffer, "    case ");
          SPVM_STRING_BUFFER_add_int(string_buffer, match);
          SPVM_STRING_BUFFER_add(string_buffer, ": goto L");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode_rel_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    default: goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, default_opcode_rel_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &byte_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &short_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &int_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &long_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &float_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &double_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_deref_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
        const char* field_package_name = &runtime->string_pool[field_package->name_id];
        const char* field_name = &runtime->string_pool[field->name_id];
        const char* field_signature = &runtime->string_pool[field->signature_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->field_offset(env, ");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    };\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Object must be not undef.\", 0));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* ofield = *(SPVM_VALUE_object*)((intptr_t)object + object_header_byte_size + ");
        SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ofield);");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
        const char* field_package_name = &runtime->string_pool[field_package->name_id];
        const char* field_name = &runtime->string_pool[field->name_id];
        const char* field_signature = &runtime->string_pool[field->signature_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->field_offset(env, ");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    };\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_str_raw(env, \"Object must be not undef.\", 0));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* ofield_address = (SPVM_VALUE_object*)((intptr_t)object + object_header_byte_size + ");
        SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN(");
        SPVM_STRING_BUFFER_add(string_buffer, "ofield_address,");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, "    );\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        SPVM_RUNTIME_PACKAGE* field_package = &runtime->packages[field->package_id];
        const char* field_package_name = &runtime->string_pool[field_package->name_id];
        const char* field_name = &runtime->string_pool[field->name_id];
        const char* field_signature = &runtime->string_pool[field->signature_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->field_offset(env, ");
        SPVM_STRING_BUFFER_add_field_id_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    };\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_str_raw(env, \"Object must be not undef.\", 0));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* ofield_address = (SPVM_VALUE_object*)((intptr_t)object + object_header_byte_size + ");
        SPVM_STRING_BUFFER_add_field_offset_name(string_buffer, field_package_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_RUNTIME_API_OBJECT_ASSIGN(ofield_address, NULL);");
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
        int32_t constant_pool_id = opcode->operand1;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
        SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
        const char* package_var_package_name = &runtime->string_pool[package_var_package->name_id];
        const char* package_var_name = &runtime->string_pool[package_var->name_id];
        const char* package_var_signature = &runtime->string_pool[package_var->signature_id];

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
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->pkgvar_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Package variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, package_var_access_ctype_id, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, package_var_access_ctype_id));
        SPVM_STRING_BUFFER_add(string_buffer, "*)");
        SPVM_STRING_BUFFER_add(string_buffer, "&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "]");
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_OBJECT: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
        SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
        const char* package_var_package_name = &runtime->string_pool[package_var_package->name_id];
        const char* package_var_name = &runtime->string_pool[package_var->name_id];
        const char* package_var_signature = &runtime->string_pool[package_var->signature_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->pkgvar_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Package variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", *(void**)");
        SPVM_STRING_BUFFER_add(string_buffer, "&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[");
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
        int32_t constant_pool_id = opcode->operand0;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
        SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
        const char* package_var_package_name = &runtime->string_pool[package_var_package->name_id];
        const char* package_var_name = &runtime->string_pool[package_var->name_id];
        const char* package_var_signature = &runtime->string_pool[package_var->signature_id];

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
            package_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT;
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if ( __builtin_expect(");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->pkgvar_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Package variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    *(");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(env, package_var_access_ctype_id));
        SPVM_STRING_BUFFER_add(string_buffer, "*)");
        SPVM_STRING_BUFFER_add(string_buffer, "&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "]");
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, package_var_access_ctype_id, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_OBJECT: {
        int32_t constant_pool_id = opcode->operand0;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
        SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
        const char* package_var_package_name = &runtime->string_pool[package_var_package->name_id];
        const char* package_var_name = &runtime->string_pool[package_var->name_id];
        const char* package_var_signature = &runtime->string_pool[package_var->signature_id];

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if ( __builtin_expect(");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->pkgvar_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Package variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "],\n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_UNDEF: {
        int32_t constant_pool_id = opcode->operand0;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
        SPVM_RUNTIME_PACKAGE* package_var_package = &runtime->packages[package_var->package_id];
        const char* package_var_package_name = &runtime->string_pool[package_var_package->name_id];
        const char* package_var_name = &runtime->string_pool[package_var->name_id];
        const char* package_var_signature = &runtime->string_pool[package_var->signature_id];
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if ( __builtin_expect(");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->pkgvar_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Package variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(string_buffer, package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "], NULL);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", env->exception(env));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  env->set_exception(env, ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
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
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->byte_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_obj_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_byte*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_short value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->short_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_obj_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_short*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_int value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->int_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_obj_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_int*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_long value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->long_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_obj_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_long*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_float value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->float_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_obj_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_float*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE_double value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->double_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_obj_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_VALUE_double*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_OBJECT_TO_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->byte_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_byte*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->short_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_short*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->int_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_int*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->long_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_long*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->float_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_float*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_str_raw(env, \"Can't convert undef value.\", 0);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->double_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(env, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(SPVM_VALUE_double*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_str_raw(env, \"Can't convert imcompatible object type.\", 0);\n");
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
  switch (sub->return_runtime_type) {
    case SPVM_TYPE_C_RUNTIME_TYPE_ANY_OBJECT:
    case SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE:
    case SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY:
    case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY:
    case SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY:
    {
      SPVM_STRING_BUFFER_add(string_buffer, "    if (stack[0].oval != NULL) { SPVM_RUNTIME_API_DEC_REF_COUNT_ONLY(stack[0].oval); }\n");
    }
    break;
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "  return exception_flag;\n");
  
  // Close subroutine
  SPVM_STRING_BUFFER_add(string_buffer, "}\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
}

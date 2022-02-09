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
#include "spvm_opcode.h"
#include "spvm_object.h"
#include "spvm_class.h"
#include "spvm_class_var.h"
#include "spvm_method.h"
#include "spvm_basic_type.h"
#include "spvm_field.h"
#include "spvm_type.h"
#include "spvm_my.h"
#include "spvm_api.h"
#include "spvm_opcode_array.h"
#include "spvm_constant.h"

#include "spvm_compiler.h"
#include "spvm_switch_info.h"
#include "spvm_case_info.h"

const char* SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(SPVM_COMPILER* compiler, int32_t ctype_id) {
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

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index) {
  
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
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BOOL_OBJECT:
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT:
    {
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

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var_value(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index, int32_t field_index) {
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

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, ctype_id, var_index);
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_deref(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)*(void**)&");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, var_index);
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&");
  SPVM_STRING_BUFFER_add(string_buffer, "stack[");
  SPVM_STRING_BUFFER_add_int(string_buffer, var_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index, int32_t field_index) {
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var_value(compiler, string_buffer, ctype_id, var_index, field_index);
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
  if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT) {
    SPVM_STRING_BUFFER_add(string_buffer, " = ");
    SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in_index);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }
  else if (ctype_id == SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BOOL_OBJECT) {
    SPVM_STRING_BUFFER_add(string_buffer, " = !!env->get_bool_object_value(env, ");
    SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in_index);
    SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  }
  else {
    SPVM_STRING_BUFFER_add(string_buffer, " = !!");
    SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in_index);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_eq(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_ne(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " != ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_gt(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " > ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_ge(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >= ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_lt(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " < ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_le(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " <= ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_cmp(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {

  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " > ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " ? 1\n");
  SPVM_STRING_BUFFER_add(string_buffer, "            : ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " < ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " ? -1\n");
  SPVM_STRING_BUFFER_add(string_buffer, "            : 0;\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_add(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " + ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_subtract(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " - ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_multiply(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " * ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_integral(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_string_nolen_raw(env, \"0 division\"));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 1;\n");

  SPVM_STRING_BUFFER_add(string_buffer, "  } else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_unsigned_int(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_string_nolen_raw(env, \"0 division\"));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 1;\n");

  SPVM_STRING_BUFFER_add(string_buffer, "  } else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (uint32_t)");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / (uint32_t)");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_unsigned_long(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_string_nolen_raw(env, \"0 division\"));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 1;\n");

  SPVM_STRING_BUFFER_add(string_buffer, "  } else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (uint64_t)");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / (uint64_t)");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_floating_point(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_remainder_integral(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* exception = env->new_string_nolen_raw(env, \"0 division\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, exception);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " % /* REMAINDER */ "); // % have undarstandable bug.
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_remainder_unsigned_int(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* exception = env->new_string_nolen_raw(env, \"0 division\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, exception);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (uint32_t)");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " % /* REMAINDER */ (uint32_t)"); // % have undarstandable bug.
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_remainder_unsigned_long(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* exception = env->new_string_nolen_raw(env, \"0 division\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, exception);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (uint64_t)");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " % /* REMAINDER */ (uint64_t)"); // % have undarstandable bug.
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_left_shift(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " << ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
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

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_logical_shift(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, ")((u");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, ")");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
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

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_arithmetic_shift(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
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

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_and(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " & ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_or(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " | ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_xor(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " ^ ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_negate(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = -");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_plus(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_complement(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ~");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_inc(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t number) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " += ");
  SPVM_STRING_BUFFER_add_int(string_buffer, number);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t out_ctype_id, int32_t in_ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, out_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, out_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, ")");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, in_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_load_constant_0(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = 0");
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, element_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_STRING_BUFFER_add(string_buffer, "((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[index];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[index]\n");
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, element_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index, int32_t fields_length) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  {
    int32_t field_index;
    for (field_index = 0; field_index < fields_length; field_index++) {
      SPVM_STRING_BUFFER_add(string_buffer, "        ");
      SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, element_ctype_id, out_index, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, " = ");
      SPVM_STRING_BUFFER_add(string_buffer, "((");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
      SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
      SPVM_STRING_BUFFER_add_int(string_buffer, fields_length);
      SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
      SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]; \n");
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index, int32_t fields_length, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, element_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " =");
  SPVM_STRING_BUFFER_add(string_buffer, "((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
  SPVM_STRING_BUFFER_add_int(string_buffer, fields_length);
  SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]; \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index, int32_t fields_length) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  
  {
    int32_t field_index;
    for (field_index = 0; field_index < fields_length; field_index++) {
      SPVM_STRING_BUFFER_add(string_buffer, "      ((");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
      SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
      SPVM_STRING_BUFFER_add_int(string_buffer, fields_length);
      SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
      SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      SPVM_STRING_BUFFER_add(string_buffer, " = ");
      SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, element_ctype_id, in_index, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, ";\n");
    }
  }

  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index, int32_t fields_length, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
  SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
  SPVM_STRING_BUFFER_add(string_buffer, "        ((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
  SPVM_STRING_BUFFER_add_int(string_buffer, fields_length);
  SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]");
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, element_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_var_id, int32_t ref_var_id, int32_t fields_length) {

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  switch (element_ctype_id) {
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int8_t* value_ref = *(int8_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int16_t* value_ref = *(int16_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int32_t* value_ref = *(int32_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int64_t* value_ref = *(int64_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    float* value_ref = *(float**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    double* value_ref = *(double**)&ref_vars[");
      break;
    }
  }
  SPVM_STRING_BUFFER_add_int(string_buffer, ref_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    *(");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
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
    SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
    SPVM_STRING_BUFFER_add(string_buffer, "*)&value_ref[");
    SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_get_field(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_var_id, int32_t ref_var_id, int32_t field_index) {

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  switch (element_ctype_id) {
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int8_t* value_ref = *(int8_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int16_t* value_ref = *(int16_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int32_t* value_ref = *(int32_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int64_t* value_ref = *(int64_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    float* value_ref = *(float**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    double* value_ref = *(double**)&ref_vars[");
      break;
    }
  }
  SPVM_STRING_BUFFER_add_int(string_buffer, ref_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
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
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&value_ref[");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_set_field(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t ref_var_id, int32_t in_var_id, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  switch (element_ctype_id) {
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int8_t* value_ref = *(int8_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int16_t* value_ref = *(int16_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int32_t* value_ref = *(int32_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int64_t* value_ref = *(int64_t**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    float* value_ref = *(float**)&ref_vars[");
      break;
    }
    case SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    double* value_ref = *(double**)&ref_vars[");
      break;
    }
  }
  SPVM_STRING_BUFFER_add_int(string_buffer, ref_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&value_ref[");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]");
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, element_ctype_id));
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

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_deref(compiler, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_deref(compiler, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, SPVM_CLASS* class, int32_t field_ctype_id, int32_t out_index, int32_t object_index, SPVM_FIELD* field) {
  
  
  SPVM_CLASS* field_class = field->class;
  const char* field_class_name = field_class->name;
  const char* field_name = field->name;
  const char* field_signature = field->signature;

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
  SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_id(env, \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
  SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (");
  SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Field not found ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, " ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_offset(env, ");
  SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    };\n");

  SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, object_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Object must be not undef.\"));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, field_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, field_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)object + object_header_byte_size + ");
  SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, SPVM_CLASS* class, int32_t field_ctype_id, int32_t object_index, SPVM_FIELD* field, int32_t in_index) {
  

  SPVM_CLASS* field_class = field->class;
  const char* field_class_name = field_class->name;
  const char* field_name = field->name;
  const char* field_signature = field->signature;

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
  SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_id(env, \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
  SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      if (");
  SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Field not found ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, " ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      ");
  SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_offset(env, ");
  SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    };\n");

  SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, object_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Object must be not undef.\"));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, field_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)object + object_header_byte_size + ");
  SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
  SPVM_STRING_BUFFER_add(string_buffer, ") = ");
  SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, field_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_build_class_csource(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* class_name) {
  
  // Basic type
  SPVM_BASIC_TYPE* basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, class_name, strlen(class_name));
  
  // Class name
  SPVM_CLASS* class = basic_type->class;
  
  // Head part - include and define
  SPVM_CSOURCE_BUILDER_PRECOMPILE_build_head(compiler, string_buffer);

  // Class variable id declarations
  SPVM_STRING_BUFFER_add(string_buffer, "// Class variable id declarations\n");
  for (int32_t i = 0; i < class->info_class_var_ids->length; i++) {
    int32_t class_var_id = (int32_t)(intptr_t)SPVM_LIST_fetch(class->info_class_var_ids, i);
    SPVM_CLASS_VAR* class_var = SPVM_LIST_fetch(compiler->class_vars, class_var_id);
    SPVM_CLASS* class_var_class = class_var->class;
    const char* class_var_class_name = class_var_class->name;
    const char* class_var_name = class_var->name;
    
    SPVM_STRING_BUFFER_add(string_buffer, "static int32_t ");
    SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
    SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");
  }

  // Field id declarations
  SPVM_STRING_BUFFER_add(string_buffer, "// Field id declarations\n");
  for (int32_t i = 0; i < class->info_field_ids->length; i++) {
    int32_t field_id = (int32_t)(intptr_t)SPVM_LIST_fetch(class->info_field_ids, i);
    SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
    SPVM_CLASS* field_class = field->class;
    const char* field_class_name = field_class->name;
    const char* field_name = field->name;
    
    SPVM_STRING_BUFFER_add(string_buffer, "static int32_t ");
    SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
    SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");
    SPVM_STRING_BUFFER_add(string_buffer, "static int32_t ");
    SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
    SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");
  }

  // Method id declarations
  SPVM_STRING_BUFFER_add(string_buffer, "// Method id declarations\n");
  for (int32_t i = 0; i < class->info_method_ids->length; i++) {
    int32_t method_id = (int32_t)(intptr_t)SPVM_LIST_fetch(class->info_method_ids, i);
    SPVM_METHOD* method = SPVM_LIST_fetch(compiler->methods, method_id);
    SPVM_CLASS* method_class = method->class;
    const char* method_class_name = method_class->name;
    const char* method_name = method->name;
    
    SPVM_STRING_BUFFER_add(string_buffer, "static int32_t ");
    SPVM_STRING_BUFFER_add_method_access_id_name(string_buffer, class->name, method_class_name, method_name);
    SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");
  }
  

  // Basic type id declarations
  SPVM_STRING_BUFFER_add(string_buffer, "// Basic type id declarations\n");
  for (int32_t i = 0; i < class->info_basic_type_ids->length; i++) {
    int32_t basic_type_id = (int32_t)(intptr_t)SPVM_LIST_fetch(class->info_basic_type_ids, i);
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    
    SPVM_STRING_BUFFER_add(string_buffer, "static int32_t ");
    SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type->name);
    SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");
  }
  
  // Method decrations
  SPVM_STRING_BUFFER_add(string_buffer, "// Function Declarations\n");
  {
    int32_t method_index;
    for (method_index = 0; method_index < class->methods->length; method_index++) {
      SPVM_METHOD* method = SPVM_LIST_fetch(class->methods, method_index);
      const char* method_name = method->name;
      const char* method_signature = method->signature;
      if (method->flag & SPVM_METHOD_C_FLAG_PRECOMPILE) {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_build_method_declaration(compiler, string_buffer, class_name, method_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
      }
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Method implementations
  SPVM_STRING_BUFFER_add(string_buffer, "// Function Implementations\n");
  {
    int32_t method_index;
    for (method_index = 0; method_index < class->methods->length; method_index++) {
      SPVM_METHOD* method = SPVM_LIST_fetch(class->methods, method_index);
      if (method->flag & SPVM_METHOD_C_FLAG_PRECOMPILE) {
        const char* method_name = method->name;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_build_method_implementation(compiler, string_buffer, class_name, method_name);
      }
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // If class have anon methods, the anon sub source code is merged to this class
  for (int32_t i = 0; i < class->anon_methods->length; i++) {
    SPVM_METHOD* anon_method = SPVM_LIST_fetch(class->anon_methods, i);
    SPVM_CLASS* anon_method_class = anon_method->class;
    SPVM_CSOURCE_BUILDER_PRECOMPILE_build_class_csource(compiler, string_buffer, anon_method_class->name);
  }
}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_build_head(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer) {
  
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

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_API_GET_OBJECT_NO_WEAKEN_ADDRESS(object) ((void*)((intptr_t)object & ~(intptr_t)1))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_API_GET_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset)))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_API_INC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))++)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_API_INC_REF_COUNT(object)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "do {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_INC_REF_COUNT_ONLY(object);\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_API_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))--)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_API_DEC_REF_COUNT(object)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "do {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_API_GET_REF_COUNT(object) > 1) { SPVM_API_DEC_REF_COUNT_ONLY(object); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { env->dec_ref_count(env, object); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_API_ISWEAK(dist_address) (((intptr_t)*(void**)dist_address) & 1)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_API_OBJECT_ASSIGN(dist_address, src_object) \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "do {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* tmp_object = SPVM_API_GET_OBJECT_NO_WEAKEN_ADDRESS(src_object);\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (tmp_object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_INC_REF_COUNT_ONLY(tmp_object);\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (*(void**)(dist_address) != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(SPVM_API_ISWEAK(dist_address), 0)) { env->unweaken(env, dist_address); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_API_GET_REF_COUNT(*(void**)(dist_address)) > 1) { SPVM_API_DEC_REF_COUNT_ONLY(*(void**)(dist_address)); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else { env->dec_ref_count(env, *(void**)(dist_address)); }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)(dist_address) = tmp_object;\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#endif\n");

}

void SPVM_CSOURCE_BUILDER_PRECOMPILE_build_method_declaration(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* class_name, const char* method_name) {
  
  // Basic type
  SPVM_BASIC_TYPE* basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, class_name, strlen(class_name));
  
  // Class name
  SPVM_CLASS* class = basic_type->class;

  SPVM_METHOD* method = SPVM_HASH_fetch(class->method_symtable, method_name, strlen(method_name));

  assert(method->flag & SPVM_METHOD_C_FLAG_PRECOMPILE);
  
  // Return type
  SPVM_STRING_BUFFER_add(string_buffer, "int32_t ");
        
  // Method name. Replace : to _
  SPVM_STRING_BUFFER_add(string_buffer, "SPVMPRECOMPILE__");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)class_name);
  SPVM_STRING_BUFFER_add(string_buffer, (char*)"__");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)method_name);
  {
    int32_t index = string_buffer->length - (strlen(class_name) + 2 + strlen(method_name));
    
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

void SPVM_CSOURCE_BUILDER_PRECOMPILE_build_method_implementation(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* class_name, const char* method_name) {
  
  
  
  // Basic type
  SPVM_BASIC_TYPE* basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, class_name, strlen(class_name));
  
  // Class name
  SPVM_CLASS* class = basic_type->class;

  SPVM_METHOD* method = SPVM_HASH_fetch(class->method_symtable, method_name, strlen(method_name));

  assert(method->flag & SPVM_METHOD_C_FLAG_PRECOMPILE);
  
  SPVM_CSOURCE_BUILDER_PRECOMPILE_build_method_declaration(compiler, string_buffer, class_name, method_name);

  // Block start
  SPVM_STRING_BUFFER_add(string_buffer, " {\n");
  
  // Object header byte size
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t object_header_byte_size = (intptr_t)env->object_header_byte_size;\n");
  
  // Call method argument stack top
  int32_t call_spvm_method_arg_stack_top = 0;

  // object variable declarations
  int32_t object_vars_alloc_length = method->object_vars_alloc_length;
  if (object_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  void* object_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, object_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // ref variable declarations
  int32_t ref_vars_alloc_length = method->ref_vars_alloc_length;
  if (ref_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  void* ref_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, ref_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // double variable declarations
  int32_t double_vars_alloc_length = method->double_vars_alloc_length;
  if (double_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  double double_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, double_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // float variable declarations
  int32_t float_vars_alloc_length = method->float_vars_alloc_length;
  if (float_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  float float_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, float_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // long variable declarations
  int32_t long_vars_alloc_length = method->long_vars_alloc_length;
  if (long_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int64_t long_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, long_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // int variable declarations
  int32_t int_vars_alloc_length = method->int_vars_alloc_length;
  if (int_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t int_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, int_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // Exception
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t exception_flag = 0;\n");

  if (method->mortal_stack_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t mortal_stack[");
    SPVM_STRING_BUFFER_add_int(string_buffer, method->mortal_stack_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t mortal_stack_top = 0;\n");
  }
  
  // short variable declarations
  int32_t short_vars_alloc_length = method->short_vars_alloc_length;
  if (short_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int16_t short_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, short_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // byte variable declarations
  int32_t byte_vars_alloc_length = method->byte_vars_alloc_length;
  if (byte_vars_alloc_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int8_t byte_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, byte_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // Convert string
  SPVM_STRING_BUFFER_add(string_buffer, "  char convert_string_buffer[21];\n");
  
  // Copy arguments to variables with type information
  if (method->args->length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  // Copy arguments to variables\n");
  }
  {
    int32_t stack_index = 0;
    for (int32_t arg_index = 0; arg_index < method->args->length; arg_index++) {
      SPVM_MY* arg = SPVM_LIST_fetch(method->args, arg_index);

      // Numeric type
      int32_t type_width = SPVM_TYPE_get_width(compiler, arg->type->basic_type->id, arg->type->dimension, arg->type->flag);
      switch (arg->type_category) {
        case SPVM_TYPE_C_TYPE_CATEGORY_BYTE: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, arg->mem_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_SHORT: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, arg->mem_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_INT: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, arg->mem_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_LONG: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, arg->mem_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_FLOAT: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, arg->mem_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_DOUBLE: {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, arg->mem_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_BYTE: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, arg->mem_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_SHORT: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, arg->mem_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_INT: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, arg->mem_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_LONG: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, arg->mem_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_FLOAT: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, arg->mem_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_DOUBLE: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, arg->mem_id + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, stack_index + field_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_ANY_OBJECT:
        case SPVM_TYPE_C_TYPE_CATEGORY_CLASS:
        case SPVM_TYPE_C_TYPE_CATEGORY_NUMERIC_ARRAY:
        case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY:
        case SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY:
        case SPVM_TYPE_C_TYPE_CATEGORY_STRING:
        {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, arg->mem_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, stack_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");

          SPVM_STRING_BUFFER_add(string_buffer, "  if (");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, arg->mem_id);
          SPVM_STRING_BUFFER_add(string_buffer, " != NULL) { SPVM_API_INC_REF_COUNT_ONLY(");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, arg->mem_id);
          SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_BYTE:
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_SHORT:
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_INT:
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_LONG:
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_FLOAT:
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_DOUBLE:
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_BYTE:
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_SHORT:
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_INT:
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_LONG:
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_FLOAT:
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_DOUBLE:
        {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, arg->mem_id);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, stack_index);
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

  SPVM_OPCODE* opcodes = compiler->opcode_array->values;
  int32_t method_opcodes_base = method->opcodes_base;
  int32_t opcodes_length = method->opcodes_length;
  int32_t opcode_index = 0;
  
  SPVM_OPCODE* opcode = NULL;

  while (opcode_index < opcodes_length) {

    // Line label
    SPVM_STRING_BUFFER_add(string_buffer, "L");
    SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index);
    SPVM_STRING_BUFFER_add(string_buffer, ": ");
    
    opcode = &(opcodes[method_opcodes_base + opcode_index]);

    int32_t opcode_id = opcode->id;

    SPVM_STRING_BUFFER_add(string_buffer, "// ");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)(SPVM_OPCODE_C_ID_NAMES())[opcode_id]);
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
    
    switch (opcode_id) {
      case SPVM_OPCODE_C_ID_BOOL_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_BOOL_OBJECT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BOOL_OBJECT, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_OBJECT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bool(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " != NULL;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_eq(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_eq(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_eq(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_eq(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_OBJECT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_eq(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_ne(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_ne(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_ne(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_ne(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_OBJECT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_ne(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_gt(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_gt(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_gt(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_gt(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_ge(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_ge(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_ge(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_ge(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_lt(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_lt(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_lt(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_lt(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_le(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_le(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_le(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_le(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_cmp(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_cmp(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_cmp(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_numeric_cmp(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_TYPE:
      {
        int32_t check_basic_type_id = opcode->operand2;
        int32_t check_type_dimension = opcode->operand3;
        SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, check_basic_type_id);
        const char* basic_type_name = basic_type->name;
        int32_t dimension = check_type_dimension;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, "      = env->is_type(env, object, check_basic_type_id, check_type_dimension);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, "      = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_HAS_CALLBACK:
      {
        int32_t check_basic_type_id = opcode->operand2;
        int32_t check_type_dimension = opcode->operand3;
        SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, check_basic_type_id);
        const char* basic_type_name = basic_type->name;
        int32_t dimension = check_type_dimension;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t callback_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t callback_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, "      = env->has_callback(env, object, callback_basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, "      = 0;\n");
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
      case SPVM_OPCODE_C_ID_STRING_CMP:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object1 = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object2 = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object1 == NULL && object2 == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_STRING_EQ: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_NE: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GT: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LT: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_CMP: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else if (object1 != NULL && object2 == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_STRING_EQ: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_NE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GT: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LT: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LE: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_CMP: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else if (object1 == NULL && object2 != NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_STRING_EQ: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_NE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GT: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GE: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LT: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_CMP: {
            SPVM_STRING_BUFFER_add(string_buffer, "-1;\n");
            break;
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t length1 = *(int32_t*)((intptr_t)object1 + (intptr_t)env->object_length_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t lenght2 = *(int32_t*)((intptr_t)object2 + (intptr_t)env->object_length_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      const char* bytes1 = env->get_chars(env, object1);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      const char* bytes2 = env->get_chars(env, object2);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t short_string_length = length1 < lenght2 ? length1 : lenght2;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t retval = memcmp(bytes1, bytes2, short_string_length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t cmp;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (retval) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        cmp = retval < 0 ? -1 : 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } else if (length1 == lenght2) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        cmp = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        cmp = length1 < lenght2 ? -1 : 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_STRING_EQ: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp == 0);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_NE: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp != 0);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GT: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp == 1);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GE: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp >= 0);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LT: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp == -1);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LE: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp <= 0);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_CMP: {
            SPVM_STRING_BUFFER_add(string_buffer, "cmp;\n");
            break;
          }
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        break;
      }
      case SPVM_OPCODE_C_ID_ADD_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_add(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_add(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_add(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_add(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_subtract(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_subtract(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_subtract(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_subtract(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_multiply(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_multiply(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_multiply(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_multiply(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_integral(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_LONG: { 
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_integral(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_floating_point(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_floating_point(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_unsigned_int(compiler, string_buffer, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_divide_unsigned_long(compiler, string_buffer, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_remainder_integral(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_LONG: { 
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_remainder_integral(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_left_shift(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_left_shift(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_remainder_unsigned_int(compiler, string_buffer, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_remainder_unsigned_long(compiler, string_buffer, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_arithmetic_shift(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_arithmetic_shift(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_logical_shift(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_right_logical_shift(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_AND_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_and(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_AND_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_and(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_OR_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_or(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_OR_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_or(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_XOR_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_xor(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_XOR_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_bit_xor(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_negate(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_negate(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_negate(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_negate(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_NOT_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_complement(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_NOT_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_complement(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_convert(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_STRING_TO_BYTE_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* src_string = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t src_string_length = env->length(env, src_string);");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* src_string_data = env->get_chars(env, src_string);");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* byte_array = env->new_byte_array_raw(env, src_string_length);");
        SPVM_STRING_BUFFER_add(string_buffer, "    int8_t* byte_array_data = env->get_elems_byte(env, byte_array);");
        SPVM_STRING_BUFFER_add(string_buffer, "    memcpy(byte_array_data, src_string_data, src_string_length);");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", byte_array);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_ARRAY_TO_STRING: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* src_byte_array = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t src_byte_array_length = env->length(env, src_byte_array);");
        SPVM_STRING_BUFFER_add(string_buffer, "    int8_t* src_byte_array_data = env->get_elems_byte(env, src_byte_array);");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string = env->new_string_raw(env, (const char*)src_byte_array_data, src_byte_array_length);");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
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
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%\" PRId16, ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%\" PRId32, ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%\" PRId64, ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%g\", ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%g\", ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t string_length = strlen(convert_string_buffer);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string = env->new_string_raw(env, convert_string_buffer, string_length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", string);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        break;
      }
      case SPVM_OPCODE_C_ID_INIT_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", NULL);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_INT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_LONG: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = '");
        SPVM_STRING_BUFFER_add_hex_char(string_buffer, (int8_t)(uint8_t)opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "';\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (int32_t)opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_LONG: {
        int32_t constant_id = opcode->operand1;
        SPVM_CONSTANT* constant = class->info_constants->values[constant_id];
        int64_t long_value = constant->value.lval;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_long(string_buffer, long_value);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_FLOAT: {
        SPVM_VALUE value;
        value.ival = (int32_t)opcode->operand1;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE tmp_constant;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = (tmp_constant.ival = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, value.ival);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_constant.fval);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_DOUBLE: {
        int32_t constant_id = opcode->operand1;
        SPVM_CONSTANT* constant = class->info_constants->values[constant_id];
        double double_value = constant->value.dval;

        SPVM_VALUE value;
        value.dval = double_value;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE tmp_constant;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = (tmp_constant.lval = ");
        SPVM_STRING_BUFFER_add_long(string_buffer, value.lval);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_constant.dval);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FETCH_BYTE: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FETCH_SHORT: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FETCH_INT: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FETCH_LONG: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FETCH_FLOAT: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FETCH_DOUBLE: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_OBJECT:
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* object = ((void**)((intptr_t)array + object_header_byte_size))[index];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
        break;
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_FETCH_BYTE: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_FETCH_SHORT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_FETCH_INT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_FETCH_LONG: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_FETCH_FLOAT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_FETCH_DOUBLE: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_fetch(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_BYTE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_SHORT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_INT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_LONG:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_FLOAT:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_DOUBLE:
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "          env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "          exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void** element_address = &((void**)((intptr_t)array + object_header_byte_size))[index];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN(\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          element_address, ");
        SPVM_STRING_BUFFER_add(string_buffer, "        ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, "\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        );\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT_CHECK_TYPE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "          env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "          exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void** element_address = &((void**)((intptr_t)array + object_header_byte_size))[index];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        int32_t is_valid;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          is_valid = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          int32_t array_basic_type_id = *(int32_t*)((intptr_t)array + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          int32_t array_type_dimension = *(uint8_t*)((intptr_t)array + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          int32_t element_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          int32_t element_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          if (array_basic_type_id == element_basic_type_id && array_type_dimension == element_type_dimension + 1) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "            is_valid = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          else if (array_basic_type_id == (intptr_t)env->any_object_basic_type_id && array_type_dimension == element_type_dimension + 1) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "            is_valid = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "            is_valid = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        if (is_valid) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          SPVM_API_OBJECT_ASSIGN(element_address, object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          void* exception = env->new_string_nolen_raw(env, \"Assigned element type is invalid\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        }");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_UNDEF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0 || ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "  >= *(int32_t*)((intptr_t)");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " + (intptr_t)env->object_length_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* object_address = &((void**)((intptr_t)array + object_header_byte_size))[index];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN(\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          object_address,\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          NULL");
        SPVM_STRING_BUFFER_add(string_buffer, "        );\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_STORE_BYTE: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_STORE_SHORT: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_STORE_INT: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_STORE_LONG: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_STORE_FLOAT: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_STORE_DOUBLE: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_STORE_BYTE: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_STORE_SHORT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_STORE_INT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_STORE_LONG: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_STORE_FLOAT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_ARRAY_FIELD_STORE_DOUBLE: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_value_array_field_store(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT: {
          SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT_ASSIGN(&");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ", ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
          SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_UNDEF: {
          SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT_ASSIGN(&");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ", NULL);");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_REF: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_move(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_MOVE_BYTE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_MOVE_SHORT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_MOVE_INT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_MOVE_LONG: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_MOVE_FLOAT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_MOVE_DOUBLE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_GET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_GET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_GET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_GET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_GET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_GET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_SET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_SET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_SET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_SET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_SET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_SET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
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
        if (method->mortal_stack_length > 0) {
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
          SPVM_STRING_BUFFER_add(string_buffer, "          if (SPVM_API_GET_REF_COUNT(*object_address) > 1) { SPVM_API_DEC_REF_COUNT_ONLY(*object_address); }\n");
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
        int32_t basic_type_id = opcode->operand1;
        SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
        const char* basic_type_name = basic_type->name;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for object\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(int32_t*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_byte_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for byte array\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(int32_t*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_short_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for short array\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(int32_t*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_int_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for int array\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(int32_t*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_long_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for long array\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(int32_t*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_float_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for float array\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(int32_t*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_double_array_raw(env, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for double array\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
        const char* basic_type_name = basic_type->name;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(int32_t*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_object_array_raw(env, basic_type_id, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for object array\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
        const char* basic_type_name = basic_type->name;
        int32_t element_dimension = opcode->operand3;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(int32_t*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_muldim_array_raw(env, basic_type_id, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, element_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ", length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for multi dimention array\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
        const char* basic_type_name = basic_type->name;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(int32_t*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_mulnum_array_raw(env, basic_type_id, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for multi dimention array\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_CONSTANT_STRING: {
        int32_t constant_id = opcode->operand1;
        SPVM_CONSTANT* constant = class->info_constants->values[constant_id];
        const char* string_value = constant->value.oval;

        SPVM_STRING_BUFFER_add(string_buffer, "  {");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string = env->new_string_raw(env, \"");
        for (int32_t i = 0; i < constant->string_length; i++) {
          SPVM_STRING_BUFFER_add_hex_char(string_buffer, string_value[i]);
        }
        SPVM_STRING_BUFFER_add(string_buffer, "\", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, constant->string_length);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (string == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for string\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->make_read_only(env, string);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", string);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }");

        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_string_nolen_raw(env, \"Can't get array length of undef value.\"));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int32_t*)((intptr_t)");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " + (intptr_t)env->object_length_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IS_READ_ONLY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t is_read_only = env->is_read_only(env, string);\n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = is_read_only;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD: {
        int32_t field_id = opcode->operand1;
        
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
        SPVM_CLASS* field_class = field->class;
        const char* field_class_name = field_class->name;
        const char* field_name = field->name;
        const char* field_signature = field->signature;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_offset(env, ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Object to weaken an object field must not be undefined.\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void** get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t status = env->weaken(env, get_field_object_address);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (status != 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for weaken back reference\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_UNWEAKEN_FIELD: {
        int32_t field_id = opcode->operand1;
        
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
        SPVM_CLASS* field_class = field->class;
        const char* field_class_name = field_class->name;
        const char* field_name = field->name;
        const char* field_signature = field->signature;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_offset(env, ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Object to weaken an object field must not be undefined.\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void** get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->unweaken(env, get_field_object_address);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ISWEAK_FIELD: {
        int32_t field_id = opcode->operand2;
        
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
        SPVM_CLASS* field_class = field->class;
        const char* field_class_name = field_class->name;
        const char* field_name = field->name;
        const char* field_signature = field->signature;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_offset(env, ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Object to weaken an object field must not be undefined.\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void** get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, "      = env->isweak(env, get_field_object_address);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REFCNT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "       = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "    = env->get_ref_count(env, object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONCAT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string1 = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string2 = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (string1 == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"\\\".\\\" operater left value must be defined\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else if (string2 == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"\\\".\\\" operater right value must be defined\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* string3 = env->concat_raw(env, string1, string2);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", string3);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_REFOP: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "       = NULL;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* type_name = env->get_type_name_raw(env, object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", type_name);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DUMP: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* dump = env->dump_raw(env, object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", dump);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING_LEN: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = *(int32_t*)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (length >= 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = env->new_string_raw(env, NULL, length);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"The new_string_len operator can't allocate enough memory\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"The length of the new_string_len operator must be a positive number\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
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
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " == 0) { goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "; }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IF_NE_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, ") { goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "; }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_BYTE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, call_spvm_method_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_spvm_method_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, call_spvm_method_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_spvm_method_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_INT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, call_spvm_method_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_spvm_method_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_LONG:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, call_spvm_method_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_spvm_method_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, call_spvm_method_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_spvm_method_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, call_spvm_method_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_spvm_method_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, call_spvm_method_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_spvm_method_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_REF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, call_spvm_method_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        call_spvm_method_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, call_spvm_method_arg_stack_top);
        SPVM_STRING_BUFFER_add(string_buffer, " = NULL;\n");
        call_spvm_method_arg_stack_top++;
        
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, call_spvm_method_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_spvm_method_arg_stack_top += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, call_spvm_method_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_spvm_method_arg_stack_top += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_INT: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, call_spvm_method_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_spvm_method_arg_stack_top += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_LONG: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, call_spvm_method_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_spvm_method_arg_stack_top += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, call_spvm_method_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_spvm_method_arg_stack_top += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, call_spvm_method_arg_stack_top + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand_value(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        call_spvm_method_arg_stack_top += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_OBJECT_TYPE: {
        int32_t check_basic_type_id = opcode->operand2;
        int32_t check_type_dimension = opcode->operand3;

        SPVM_BASIC_TYPE* cast_basic_type = SPVM_LIST_fetch(compiler->basic_types, check_basic_type_id);
        const char* cast_basic_type_name = cast_basic_type->name;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t check_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, check_type_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object != NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == check_basic_type_id && object_type_dimension_id == check_type_dimension) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't cast uncompatible type.\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_CALLBACK: {
        int32_t check_basic_type_id = opcode->operand2;

        SPVM_BASIC_TYPE* cast_basic_type = SPVM_LIST_fetch(compiler->basic_types, check_basic_type_id);
        const char* cast_basic_type_name = cast_basic_type->name;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t callback_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_access_id_name(string_buffer, class->name, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object != NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (env->has_callback(env, object, callback_basic_type_id)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't cast uncompatible type.\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_CLASS_METHOD:
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD:
      case SPVM_OPCODE_C_ID_CALL_CALLBACK_METHOD:
      {
        int32_t var_id = opcode->operand0;
        int32_t decl_method_id = opcode->operand1;

        SPVM_METHOD* decl_method = SPVM_LIST_fetch(compiler->methods, decl_method_id);

        SPVM_CLASS* decl_method_class = decl_method->class;
        const char* decl_method_name = decl_method->name;
        const char* decl_method_signature = decl_method->signature;
        const char* decl_method_class_name = decl_method_class->name;
        
        // Declare method argument length
        int32_t decl_method_args_length = decl_method->args->length;

        SPVM_STRING_BUFFER_add(string_buffer, "  // ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "->");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        // Method inline expantion in same class
        if (decl_method->class->id == method->class->id && decl_method->flag & SPVM_METHOD_C_FLAG_PRECOMPILE) {
          
          SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = SPVMPRECOMPILE__");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
          SPVM_STRING_BUFFER_add(string_buffer, (char*)"__");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
          {
            int32_t index = string_buffer->length - (strlen(decl_method_class_name) + 2 + strlen(decl_method_name));
            
            while (index < string_buffer->length) {
              if (string_buffer->buffer[index] == ':') {
                string_buffer->buffer[index] = '_';
              }
              index++;
            }
          }
          SPVM_STRING_BUFFER_add(string_buffer, "(env, stack);\n");
        }
        // Call method
        else {
          switch (opcode_id) {
            case SPVM_OPCODE_C_ID_CALL_CLASS_METHOD: {
              SPVM_STRING_BUFFER_add(string_buffer, "    if (");
              SPVM_STRING_BUFFER_add_method_access_id_name(string_buffer, class->name, decl_method_class_name, decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_STRING_BUFFER_add_method_access_id_name(string_buffer, class->name, decl_method_class_name, decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, " = env->get_class_method_id(env, \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_signature);
              SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      if (");
              SPVM_STRING_BUFFER_add_method_access_id_name(string_buffer, class->name, decl_method_class_name, decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Method not found ");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
              SPVM_STRING_BUFFER_add(string_buffer, "->");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    int32_t call_method_id = ");
              SPVM_STRING_BUFFER_add_method_access_id_name(string_buffer, class->name, decl_method_class_name, decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              
              break;
            }
            case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD: {
              SPVM_STRING_BUFFER_add(string_buffer, "    if (");
              SPVM_STRING_BUFFER_add_method_access_id_name(string_buffer, class->name, decl_method_class_name, decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_STRING_BUFFER_add_method_access_id_name(string_buffer, class->name, decl_method_class_name, decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, " = env->get_instance_method_id_static(env, \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_signature);
              SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      if (");
              SPVM_STRING_BUFFER_add_method_access_id_name(string_buffer, class->name, decl_method_class_name, decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Method not found ");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
              SPVM_STRING_BUFFER_add(string_buffer, "->");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    int32_t call_method_id = ");
              SPVM_STRING_BUFFER_add_method_access_id_name(string_buffer, class->name, decl_method_class_name, decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              
              break;
            }
            case SPVM_OPCODE_C_ID_CALL_CALLBACK_METHOD: {
              SPVM_STRING_BUFFER_add(string_buffer, "    void* object = stack[0].oval;");
              SPVM_STRING_BUFFER_add(string_buffer, "    int32_t call_method_id = env->get_instance_method_id(env, object, \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_signature);
              SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (call_method_id == 0) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Method not found ");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
              SPVM_STRING_BUFFER_add(string_buffer, "->");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      return 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              
              break;
            }
            default: {
              assert(0);
            }
          }
          
          SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = env->call_spvm_method(env, call_method_id, stack);\n");
        }
        
        // Call method
        SPVM_STRING_BUFFER_add(string_buffer, "    if (!exception_flag) {\n");
        switch (decl_method->return_type_category_id) {
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_VOID:
            break;
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_BYTE: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_SHORT: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_INT: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_LONG: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_FLOAT: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_DOUBLE: {
            SPVM_STRING_BUFFER_add(string_buffer, "      ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, 0);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_OBJECT: {
            SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT_ASSIGN(&");
            SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, var_id);
            SPVM_STRING_BUFFER_add(string_buffer, ", stack[0].oval);\n");
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_BYTE: {
            int32_t decl_method_return_type_width = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_SHORT: {
            int32_t decl_method_return_type_width = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_LONG: {
            int32_t decl_method_return_type_width = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_FLOAT: {
            int32_t decl_method_return_type_width = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_DOUBLE: {
            int32_t decl_method_return_type_width = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          case SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_INT: {
            int32_t decl_method_return_type_width = opcode->operand3;
            for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, var_id + field_index);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, field_index);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            }
            break;
          }
          default:
            assert(0);
        }

        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        call_spvm_method_arg_stack_top -=  decl_method_args_length;
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_CATCH: {
        SPVM_METHOD* method = SPVM_LIST_fetch(class->methods, opcode->operand1);
        int32_t line = opcode->operand2;
        
        const char* method_name = method->name;
        SPVM_CLASS* method_class = method->class;
        const char* class_name = method_class->name;
        const char* file = method->class->module_file;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  if (exception_flag) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* method_class_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* method_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)method_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* file = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)file);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t line = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_stack_trace_raw(env, env->get_exception(env), method_class_name, method_name, file, line));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer,  opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_RETURN: {
        SPVM_METHOD* method = SPVM_LIST_fetch(class->methods, opcode->operand1);
        int32_t line = opcode->operand2;
        
        const char* method_name = method->name;
        SPVM_CLASS* method_class = SPVM_LIST_fetch(compiler->classes, method->class->id);
        const char* class_name = method_class->name;
        const char* file = method->class->module_file;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  if (exception_flag) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* method_class_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* method_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)method_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* file = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)file);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t line = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_stack_trace_raw(env, env->get_exception(env), method_class_name, method_name, file, line));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DIE_FLAG_TRUE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  exception_flag = 1;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_PRINT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      const char* bytes = env->get_chars(env, object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t string_length = env->length(env, object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (string_length > 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        size_t ret = fwrite(bytes, 1, string_length, stdout);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_MAKE_READ_ONLY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* string = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->make_read_only(env, string);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_WARN: {
        int32_t line = opcode->operand1;
        
        SPVM_CLASS* method_class = method->class;
        const char* file = method->class->module_file;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t empty_or_undef = 0;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      const char* bytes = env->get_chars(env, object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t string_length = env->length(env, object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (string_length > 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        size_t ret = fwrite(bytes, 1, string_length, stderr);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        int32_t add_line_file;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        if (bytes[string_length - 1] != '\\n') {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "          fprintf(stderr, \" at %s line %d\\n\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, file);
        SPVM_STRING_BUFFER_add(string_buffer, "\", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        empty_or_undef = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      empty_or_undef = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (empty_or_undef) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        fprintf(stderr, \"Warning: something's wrong at %s line %d\\n\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, file);
        SPVM_STRING_BUFFER_add(string_buffer, "\", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_SHORT: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_INT: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_LONG: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_FLOAT: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_DOUBLE: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_BYTE:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        
        // Multi numeric type
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, var_id + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
                    
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_SHORT:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        
        // Multi numeric type
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, var_id + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
                    
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_INT:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        
        // Multi numeric type
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, var_id + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
                    
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_LONG:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        
        // Multi numeric type
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, var_id + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
                    
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_FLOAT:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        
        // Multi numeric type
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
                    
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_DOUBLE:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        
        // Multi numeric type
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_stack(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id + field_index);
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        // Increment ref count of return value not to release by decrement
        SPVM_STRING_BUFFER_add(string_buffer, "  if (*(void**)&stack[0] != NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_INC_REF_COUNT_ONLY(*(void**)&stack[0]);\n");
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
        int32_t switch_id = opcode->operand1;
        
        SPVM_SWITCH_INFO* switch_info = class->info_switch_infos->values[switch_id];

        // Default branch
        int32_t default_opcode_rel_index = switch_info->default_opcode_rel_index;
        
        // Cases length
        int32_t case_infos_length = switch_info->case_infos->length;

        SPVM_STRING_BUFFER_add(string_buffer, "  switch(");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ") {\n");
        for (int32_t case_index = 0; case_index < case_infos_length; case_index++) {
          SPVM_CASE_INFO* case_info = switch_info->case_infos->values[case_index];
          
          int32_t match = case_info->constant->value.ival;
          int32_t opcode_rel_index = case_info->opcode_rel_index;
          
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &byte_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &short_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &int_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &long_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &float_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_var(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &double_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_BYTE: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_SHORT: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_INT: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_LONG: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_FLOAT: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_DOUBLE: {
        int32_t fields_length = opcode->operand3;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_GET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_get_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_GET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_get_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_GET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_get_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_GET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_get_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_GET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_get_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_GET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_get_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_SET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_set_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_SET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_set_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_SET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_set_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_SET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_set_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_SET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_set_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MULNUM_DEREF_SET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_mulnum_deref_set_field(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        int32_t field_id = opcode->operand2;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        int32_t field_id = opcode->operand2;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        int32_t field_id = opcode->operand2;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        int32_t field_id = opcode->operand2;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        int32_t field_id = opcode->operand2;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        int32_t field_id = opcode->operand2;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        int32_t field_id = opcode->operand2;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
        SPVM_CLASS* field_class = field->class;
        const char* field_class_name = field_class->name;
        const char* field_name = field->name;
        const char* field_signature = field->signature;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_offset(env, ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    };\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Object must be not undef.\"));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* get_field_object = *(void**)((intptr_t)object + object_header_byte_size + ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", get_field_object);");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        int32_t field_id = opcode->operand1;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        int32_t field_id = opcode->operand1;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        int32_t field_id = opcode->operand1;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
        
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        int32_t field_id = opcode->operand1;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        int32_t field_id = opcode->operand1;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        int32_t field_id = opcode->operand1;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);

        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_field(compiler, string_buffer, class, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT:
      {
        int32_t field_id = opcode->operand1;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
        SPVM_CLASS* field_class = field->class;
        const char* field_class_name = field_class->name;
        const char* field_name = field->name;
        const char* field_signature = field->signature;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_offset(env, ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    };\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, env->new_string_nolen_raw(env, \"Object must be not undef.\"));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT_ASSIGN(");
        SPVM_STRING_BUFFER_add(string_buffer, "get_field_object_address,");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, "    );\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF:
      {
        int32_t field_id = opcode->operand1;
        SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
        SPVM_CLASS* field_class = field->class;
        const char* field_class_name = field_class->name;
        const char* field_name = field->name;
        const char* field_signature = field->signature;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_field_offset(env, ");
        SPVM_STRING_BUFFER_add_field_access_id_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    };\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_string_nolen_raw(env, \"Object must be not undef.\"));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + ");
        SPVM_STRING_BUFFER_add_field_access_offset_name(string_buffer, class->name, field_class_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT_ASSIGN(get_field_object_address, NULL);");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_get_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_BYTE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_SHORT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_INT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_LONG: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_FLOAT: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE: {
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_set_deref(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE:
      {
        int32_t class_var_id = opcode->operand1;
        SPVM_CLASS_VAR* class_var = SPVM_LIST_fetch(compiler->class_vars, class_var_id);
        SPVM_CLASS* class_var_class = class_var->class;
        const char* class_var_class_name = class_var_class->name;
        const char* class_var_name = class_var->name;
        const char* class_var_signature = class_var->signature;

        int32_t class_var_access_ctype_id;
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE;
            break;
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT;
            break;
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT;
            break;
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG;
            break;
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT;
            break;
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE;
            break;
          default:
            assert(0);
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_class_var_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Class variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, class_var_access_ctype_id, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, class_var_access_ctype_id));
        SPVM_STRING_BUFFER_add(string_buffer, "*)");
        SPVM_STRING_BUFFER_add(string_buffer, "&((SPVM_VALUE*)env->class_vars_heap)[");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "]");
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT: {
        int32_t class_var_id = opcode->operand1;
        SPVM_CLASS_VAR* class_var = SPVM_LIST_fetch(compiler->class_vars, class_var_id);
        SPVM_CLASS* class_var_class = class_var->class;
        const char* class_var_class_name = class_var_class->name;
        const char* class_var_name = class_var->name;
        const char* class_var_signature = class_var->signature;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_class_var_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Class variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", *(void**)");
        SPVM_STRING_BUFFER_add(string_buffer, "&((SPVM_VALUE*)env->class_vars_heap)[");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "]);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE:
      {
        int32_t class_var_id = opcode->operand0;
         SPVM_CLASS_VAR* class_var = SPVM_LIST_fetch(compiler->class_vars, class_var_id);
        SPVM_CLASS* class_var_class = class_var->class;
        const char* class_var_class_name = class_var_class->name;
        const char* class_var_name = class_var->name;
        const char* class_var_signature = class_var->signature;

        int32_t class_var_access_ctype_id;
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE;
            break;
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT;
            break;
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT;
            break;
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG;
            break;
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT;
            break;
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE;
            break;
          default:
            class_var_access_ctype_id = SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT;
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if ( __builtin_expect(");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_class_var_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Class variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    *(");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_CSOURCE_BUILDER_PRECOMPILE_get_ctype_name(compiler, class_var_access_ctype_id));
        SPVM_STRING_BUFFER_add(string_buffer, "*)");
        SPVM_STRING_BUFFER_add(string_buffer, "&((SPVM_VALUE*)env->class_vars_heap)[");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "]");
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, class_var_access_ctype_id, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT: {
        int32_t class_var_id = opcode->operand0;
         SPVM_CLASS_VAR* class_var = SPVM_LIST_fetch(compiler->class_vars, class_var_id);
        SPVM_CLASS* class_var_class = class_var->class;
        const char* class_var_class_name = class_var_class->name;
        const char* class_var_name = class_var->name;
        const char* class_var_signature = class_var->signature;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if ( __builtin_expect(");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_class_var_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Class variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN((void**)&((SPVM_VALUE*)env->class_vars_heap)[");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "],\n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF: {
        int32_t class_var_id = opcode->operand0;
        SPVM_CLASS_VAR* class_var = SPVM_LIST_fetch(compiler->class_vars, class_var_id);
        SPVM_CLASS* class_var_class = class_var->class;
        const char* class_var_class_name = class_var_class->name;
        const char* class_var_name = class_var->name;
        const char* class_var_signature = class_var->signature;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    if ( __builtin_expect(");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0, 0)) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->get_class_var_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Class variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        return 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN((void**)&((SPVM_VALUE*)env->class_vars_heap)[");
        SPVM_STRING_BUFFER_add_class_var_access_id_name(string_buffer, class->name, class_var_class_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "], NULL);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", env->get_exception(env));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  env->set_exception(env, ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  env->set_exception(env, NULL);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_END_METHOD: {
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int8_t value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->byte_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(int8_t*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int16_t value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->short_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(int16_t*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->int_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(int32_t*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int64_t value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->long_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(int64_t*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    float value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->float_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(float*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    double value = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t basic_type_id = (intptr_t)(void*)env->double_object_basic_type_id;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    *(double*)&fields[0] = value;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_OBJECT_TO_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->byte_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int8_t*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't convert imcompatible object type.\");\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->short_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int16_t*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't convert imcompatible object type.\");\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->int_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int32_t*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't convert imcompatible object type.\");\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->long_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int64_t*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't convert imcompatible object type.\");\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->float_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(float*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't convert imcompatible object type.\");\n");
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
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      if (object_basic_type_id == (intptr_t)(void*)env->double_object_basic_type_id && object_type_dimension_id == 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        \n");
        SPVM_CSOURCE_BUILDER_PRECOMPILE_add_operand(compiler, string_buffer, SPVM_CSOURCE_BUILDER_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(double*)&fields[0];\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "        void* exception = env->new_string_nolen_raw(env, \"Can't convert imcompatible object type.\");\n");
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
  switch (method->return_type_category) {
    case SPVM_TYPE_C_TYPE_CATEGORY_ANY_OBJECT:
    case SPVM_TYPE_C_TYPE_CATEGORY_CLASS:
    case SPVM_TYPE_C_TYPE_CATEGORY_NUMERIC_ARRAY:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY:
    case SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY:
    case SPVM_TYPE_C_TYPE_CATEGORY_STRING:
    {
      SPVM_STRING_BUFFER_add(string_buffer, "    if (stack[0].oval != NULL) { SPVM_API_DEC_REF_COUNT_ONLY(stack[0].oval); }\n");
    }
    break;
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "  return exception_flag;\n");
  
  // Close method
  SPVM_STRING_BUFFER_add(string_buffer, "}\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
}

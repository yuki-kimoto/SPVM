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
#include "spvm_dynamic_array.h"
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

void SPVM_JITCODE_BUILDER_add_operand(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t var_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, type_name);
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
  SPVM_STRING_BUFFER_add(string_buffer, "    ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " %% ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_left_shift(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " << ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_JITCODE_BUILDER_add_right_shift_unsigned(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_STRING_BUFFER_add(string_buffer, type_name);
  SPVM_STRING_BUFFER_add(string_buffer, ")((u");
  SPVM_STRING_BUFFER_add(string_buffer, type_name);
  SPVM_STRING_BUFFER_add(string_buffer, ")");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_JITCODE_BUILDER_add_right_shift(SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> ");
  SPVM_JITCODE_BUILDER_add_operand(string_buffer, type_name, in2_index);
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
  SPVM_STRING_BUFFER_add(string_buffer, out_type_name);
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

void SPVM_JITCODE_BUILDER_add_var(SPVM_STRING_BUFFER* string_buffer, int32_t index) {
  SPVM_STRING_BUFFER_add(string_buffer, "var");
  SPVM_STRING_BUFFER_add_int(string_buffer, index);
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

void SPVM_JITCODE_BUILDER_build_jitcode() {

  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(0);
  
  // C library
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stdlib.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stdio.h>\n");
  
  // API header
  SPVM_STRING_BUFFER_add(string_buffer, "#include <spvm_api.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Constant macro
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_C_RUNTIME ");
  SPVM_STRING_BUFFER_add_address(string_buffer, runtime);
  SPVM_STRING_BUFFER_add(string_buffer, "\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_C_OBJECT_HEADER_BYTE_SIZE ");
  SPVM_STRING_BUFFER_add_int(string_buffer, sizeof(SPVM_OBJECT));
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_C_OBJECT_LENGTH_BYTE_OFFSET ");
  SPVM_STRING_BUFFER_add_int(string_buffer, (int32_t)offsetof(SPVM_OBJECT, length));
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_C_OBJECT_REF_COUNT_BYTE_OFFSET ");
  SPVM_STRING_BUFFER_add_int(string_buffer, (int32_t)offsetof(SPVM_OBJECT, ref_count));
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_C_RUNTIME_EXCEPTION_BYTE_OFFSET ");
  SPVM_STRING_BUFFER_add_int(string_buffer, (int32_t)offsetof(SPVM_RUNTIME, exception));
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Inline macro function
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_INLINE_GET_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + SPVM_JITCODE_C_OBJECT_REF_COUNT_BYTE_OFFSET)))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_INLINE_INC_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + SPVM_JITCODE_C_OBJECT_REF_COUNT_BYTE_OFFSET))++)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_INLINE_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + SPVM_JITCODE_C_OBJECT_REF_COUNT_BYTE_OFFSET))--)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_INLINE_GET_EXCEPTION() (*(SPVM_API_OBJECT**)((intptr_t)SPVM_JITCODE_C_RUNTIME + SPVM_JITCODE_C_RUNTIME_EXCEPTION_BYTE_OFFSET))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_INLINE_SET_EXCEPTION_NULL()\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  do { \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if ((*(SPVM_API_OBJECT**)((intptr_t)SPVM_JITCODE_C_RUNTIME + SPVM_JITCODE_C_RUNTIME_EXCEPTION_BYTE_OFFSET)) != NULL) { \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      api->dec_ref_count(api, (*(SPVM_API_OBJECT**)((intptr_t)SPVM_JITCODE_C_RUNTIME + SPVM_JITCODE_C_RUNTIME_EXCEPTION_BYTE_OFFSET))); \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    (*(SPVM_API_OBJECT**)((intptr_t)SPVM_JITCODE_C_RUNTIME + SPVM_JITCODE_C_RUNTIME_EXCEPTION_BYTE_OFFSET)) = NULL; \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  while (0) \\\n\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_INLINE_ISWEAK(object) ((intptr_t)object & 1)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Constant pool
  int32_t* constant_pool = runtime->constant_pool;

  int32_t subs_base = runtime->subs_base;
  int32_t subs_length = runtime->subs_length;

  // Subroutine Implementations
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < subs_length; sub_index++) {
      int32_t sub_id = constant_pool[subs_base + sub_index];
      
      SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];
      int32_t sub_abs_name_id = constant_pool_sub->abs_name_id;
      
      // Subroutine name
      const char* sub_abs_name = (char*)&constant_pool[sub_abs_name_id + 1];

      // Arguments length
      int32_t args_length = constant_pool_sub->args_length;
      
      // Arguments type ids base
      int32_t arg_type_ids_base = constant_pool_sub->arg_type_ids_base;

      // Is void
      int32_t sub_is_void = constant_pool_sub->is_void;

      // Subroutine object my base index
      int32_t sub_object_mys_base = constant_pool_sub->object_mys_base;

      // Subroutine object my length
      int32_t sub_object_mys_length = constant_pool_sub->object_mys_length;
      
      // Return type code
      int32_t return_type_id = constant_pool_sub->return_type_id;
      SPVM_CONSTANT_POOL_TYPE* return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[return_type_id];
      int32_t return_type_code = return_type->code;
      
      // Mys length
      int32_t mys_length = constant_pool_sub->mys_length;
      
      // My type ids base
      int32_t my_type_ids_base = constant_pool_sub->my_type_ids_base;
      
      // Call subroutine argument stack top
      int32_t call_sub_arg_stack_top = -1;
      
      // Call subroutine argument stack
      SPVM_API_VALUE call_sub_arg_stack[255];

      // Eval stack
      int32_t eval_stack[255];
      
      // Eval stack top
      int32_t eval_stack_top = -1;
      
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
      
      // Native subroutine
      if (constant_pool_sub->is_native) {
        // Set exception to NULL
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_JITCODE_INLINE_SET_EXCEPTION_NULL();\n");
        SPVM_STRING_BUFFER_add(string_buffer, "\n");

        // Assign native address
        switch (return_type_code) {
          case SPVM_TYPE_C_CODE_VOID:
            SPVM_STRING_BUFFER_add(string_buffer, "  void ");
            break;
          case SPVM_TYPE_C_CODE_BYTE:
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_byte ");
            break;
          case SPVM_TYPE_C_CODE_SHORT:
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_short ");
            break;
          case SPVM_TYPE_C_CODE_INT:
            SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
            break;
          case SPVM_TYPE_C_CODE_LONG:
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_long ");
            break;
          case SPVM_TYPE_C_CODE_FLOAT:
            SPVM_STRING_BUFFER_add(string_buffer, "  float ");
            break;
          case SPVM_TYPE_C_CODE_DOUBLE:
            SPVM_STRING_BUFFER_add(string_buffer, "  double ");
            break;
          default:
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT* ");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "(*native_address)(SPVM_API*, SPVM_API_VALUE*) = (void*)");
        SPVM_STRING_BUFFER_add_address(string_buffer, constant_pool_sub->native_address);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        if (!constant_pool_sub->is_void) {
          switch (return_type_code) {
            case SPVM_TYPE_C_CODE_VOID:
              break;
            case SPVM_TYPE_C_CODE_BYTE:
              SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_byte ");
              break;
            case SPVM_TYPE_C_CODE_SHORT:
              SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_short ");
              break;
            case SPVM_TYPE_C_CODE_INT:
              SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
              break;
            case SPVM_TYPE_C_CODE_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_long ");
              break;
            case SPVM_TYPE_C_CODE_FLOAT:
              SPVM_STRING_BUFFER_add(string_buffer, "  float ");
              break;
            case SPVM_TYPE_C_CODE_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  double ");
              break;
            default:
              SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT* ");
          }
          SPVM_STRING_BUFFER_add(string_buffer, " return_value_native = ");
        }

        SPVM_STRING_BUFFER_add(string_buffer, "  (*native_address)(api, args);\n");
        if (constant_pool_sub->is_void) {
          SPVM_STRING_BUFFER_add(string_buffer, "  return;\n");
        }
        else {
          SPVM_STRING_BUFFER_add(string_buffer, "  return return_value_native;\n");
        }
      }
      // Normal subroutine
      else {
        // Lexical variables
        {
          int32_t my_index;
          for (my_index = 0; my_index < mys_length; my_index++) {
            int32_t my_type_id = constant_pool[my_type_ids_base + my_index];

            // My type code
            SPVM_CONSTANT_POOL_TYPE* constant_pool_my_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[my_type_id];
            int32_t my_type_code = constant_pool_my_type->code;
            
            switch (my_type_code) {
              case SPVM_TYPE_C_CODE_BYTE : {
                SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_byte ");
                break;
              }
              case  SPVM_TYPE_C_CODE_SHORT : {
                SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_short ");
                break;
              }
              case  SPVM_TYPE_C_CODE_INT : {
                SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
                break;
              }
              case  SPVM_TYPE_C_CODE_LONG : {
                SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_long ");
                break;
              }
              case  SPVM_TYPE_C_CODE_FLOAT : {
                SPVM_STRING_BUFFER_add(string_buffer, "  float ");
                break;
              }
              case  SPVM_TYPE_C_CODE_DOUBLE : {
                SPVM_STRING_BUFFER_add(string_buffer, "  double ");
                break;
              }
              default : {
                SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT* ");
              }
            }
            SPVM_JITCODE_BUILDER_add_var(string_buffer, my_index);
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
        }

        // Copy arguments to variables
        {
          int32_t arg_index;
          for (arg_index = 0; arg_index < args_length; arg_index++) {
            int32_t arg_type_id = constant_pool[arg_type_ids_base + arg_index];

            // Argument type code
            SPVM_CONSTANT_POOL_TYPE* constant_pool_arg_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[arg_type_id];
            int32_t arg_type_code = constant_pool_arg_type->code;

            // Assign argument
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
            SPVM_JITCODE_BUILDER_add_var(string_buffer, arg_index);
            SPVM_STRING_BUFFER_add(string_buffer, " = ");
            SPVM_STRING_BUFFER_add(string_buffer, "*(");
            SPVM_STRING_BUFFER_add(string_buffer, SPVM_JITCODE_BUILDER_get_type_name(arg_type_code));
            SPVM_STRING_BUFFER_add(string_buffer, "*)&args[");
            SPVM_STRING_BUFFER_add_int(string_buffer, arg_index);
            SPVM_STRING_BUFFER_add(string_buffer, "]");
            
            SPVM_STRING_BUFFER_add(string_buffer, ";\n");
          }
        }
      
        
        // Current line
        if (runtime->debug) {
          SPVM_STRING_BUFFER_add(string_buffer, "  int32_t current_line = 0;\n");
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
              SPVM_JITCODE_BUILDER_add_var(string_buffer, arg_index);
              SPVM_STRING_BUFFER_add(string_buffer, " != NULL) { SPVM_JITCODE_INLINE_INC_REF_COUNT(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, arg_index);
              SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
            }
          }
          SPVM_STRING_BUFFER_add(string_buffer, "\n");
        }

        // Condition flag
        SPVM_STRING_BUFFER_add(string_buffer, "  register int32_t condition_flag;\n");
        
        // Return value
        if (!constant_pool_sub->is_void) {
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
          if (opcodes[opcode_index].has_label) {
            SPVM_STRING_BUFFER_add(string_buffer, "L");
          }
          else {
            SPVM_STRING_BUFFER_add(string_buffer, "// L");
          }
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index);
          SPVM_STRING_BUFFER_add(string_buffer, ": ");
          
          opcode = &(opcodes[opcode_index]);

          SPVM_STRING_BUFFER_add(string_buffer, "// ");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_OPCODE_C_CODE_NAMES[opcode->code]);
          SPVM_STRING_BUFFER_add(string_buffer, "\n");
          
          switch (opcode->code) {
            case SPVM_OPCODE_C_CODE_NOP:
              abort();
            case SPVM_OPCODE_C_CODE_BOOL_BYTE:
              SPVM_JITCODE_BUILDER_add_bool(string_buffer, "SPVM_API_byte", opcode->operand0);
              break;
            case SPVM_OPCODE_C_CODE_BOOL_SHORT:
              SPVM_JITCODE_BUILDER_add_bool(string_buffer, "SPVM_API_short", opcode->operand0);
              break;
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
              SPVM_STRING_BUFFER_add(string_buffer, " == NULL);\n");
              break;
            case SPVM_OPCODE_C_CODE_IS_NOT_UNDEF:
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (");
              SPVM_JITCODE_BUILDER_add_operand(string_buffer, "SPVM_API_OBJECT*", opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " != NULL);\n");
              break;
            case SPVM_OPCODE_C_CODE_EQ_BYTE:
              SPVM_JITCODE_BUILDER_add_eq(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
              break;
            case SPVM_OPCODE_C_CODE_EQ_SHORT:
              SPVM_JITCODE_BUILDER_add_eq(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
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
            case SPVM_OPCODE_C_CODE_NE_BYTE:
              SPVM_JITCODE_BUILDER_add_ne(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
              break;
            case SPVM_OPCODE_C_CODE_NE_SHORT:
              SPVM_JITCODE_BUILDER_add_ne(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
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
            case SPVM_OPCODE_C_CODE_GT_BYTE:
              SPVM_JITCODE_BUILDER_add_gt(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
              break;
            case SPVM_OPCODE_C_CODE_GT_SHORT:
              SPVM_JITCODE_BUILDER_add_gt(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
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
            case SPVM_OPCODE_C_CODE_GE_BYTE:
              SPVM_JITCODE_BUILDER_add_ge(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
              break;
            case SPVM_OPCODE_C_CODE_GE_SHORT:
              SPVM_JITCODE_BUILDER_add_ge(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
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
            case SPVM_OPCODE_C_CODE_LT_BYTE:
              SPVM_JITCODE_BUILDER_add_lt(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
              break;
            case SPVM_OPCODE_C_CODE_LT_SHORT:
              SPVM_JITCODE_BUILDER_add_lt(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
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
            case SPVM_OPCODE_C_CODE_LE_BYTE:
              SPVM_JITCODE_BUILDER_add_le(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
              break;
            case SPVM_OPCODE_C_CODE_LE_SHORT:
              SPVM_JITCODE_BUILDER_add_le(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
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
            case SPVM_OPCODE_C_CODE_ADD_BYTE:
              SPVM_JITCODE_BUILDER_add_add(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_ADD_SHORT:
              SPVM_JITCODE_BUILDER_add_add(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
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
            case SPVM_OPCODE_C_CODE_SUBTRACT_BYTE:
              SPVM_JITCODE_BUILDER_add_subtract(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_SUBTRACT_SHORT:
              SPVM_JITCODE_BUILDER_add_subtract(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
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
            case SPVM_OPCODE_C_CODE_MULTIPLY_BYTE:
              SPVM_JITCODE_BUILDER_add_multiply(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_MULTIPLY_SHORT:
              SPVM_JITCODE_BUILDER_add_multiply(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
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
            case SPVM_OPCODE_C_CODE_DIVIDE_BYTE:
              SPVM_JITCODE_BUILDER_add_divide_integral(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_DIVIDE_SHORT:
              SPVM_JITCODE_BUILDER_add_divide_integral(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
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
            case SPVM_OPCODE_C_CODE_REMAINDER_BYTE:
              SPVM_JITCODE_BUILDER_add_remainder_integral(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_REMAINDER_SHORT:
              SPVM_JITCODE_BUILDER_add_remainder_integral(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
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
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_BYTE:
              SPVM_JITCODE_BUILDER_add_left_shift(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_SHORT:
              SPVM_JITCODE_BUILDER_add_left_shift(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_INT:
              SPVM_JITCODE_BUILDER_add_left_shift(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_LONG:
              SPVM_JITCODE_BUILDER_add_left_shift(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_BYTE:
              SPVM_JITCODE_BUILDER_add_right_shift(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_SHORT:
              SPVM_JITCODE_BUILDER_add_right_shift(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_INT:
              SPVM_JITCODE_BUILDER_add_right_shift(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_LONG:
              SPVM_JITCODE_BUILDER_add_right_shift(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE:
              SPVM_JITCODE_BUILDER_add_right_shift_unsigned(string_buffer, "int8_t", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT:
              SPVM_JITCODE_BUILDER_add_right_shift_unsigned(string_buffer, "int16_t", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
              SPVM_JITCODE_BUILDER_add_right_shift_unsigned(string_buffer, "int32_t", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
              SPVM_JITCODE_BUILDER_add_right_shift_unsigned(string_buffer, "int64_t", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_AND_BYTE:
              SPVM_JITCODE_BUILDER_add_bit_and(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_AND_SHORT:
              SPVM_JITCODE_BUILDER_add_bit_and(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_AND_INT:
              SPVM_JITCODE_BUILDER_add_bit_and(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_AND_LONG:
              SPVM_JITCODE_BUILDER_add_bit_and(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_OR_BYTE:
              SPVM_JITCODE_BUILDER_add_bit_or(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_OR_SHORT:
              SPVM_JITCODE_BUILDER_add_bit_or(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_OR_INT:
              SPVM_JITCODE_BUILDER_add_bit_or(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_OR_LONG:
              SPVM_JITCODE_BUILDER_add_bit_or(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_XOR_BYTE:
              SPVM_JITCODE_BUILDER_add_bit_xor(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_XOR_SHORT:
              SPVM_JITCODE_BUILDER_add_bit_xor(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_XOR_INT:
              SPVM_JITCODE_BUILDER_add_bit_xor(string_buffer, "SPVM_API_int", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_BIT_XOR_LONG:
              SPVM_JITCODE_BUILDER_add_bit_xor(string_buffer, "SPVM_API_long", opcode->operand0, opcode->operand1, opcode->operand2);
              break;
            case SPVM_OPCODE_C_CODE_NEGATE_BYTE:
              SPVM_JITCODE_BUILDER_add_negate(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
              break;
            case SPVM_OPCODE_C_CODE_NEGATE_SHORT:
              SPVM_JITCODE_BUILDER_add_negate(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
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
            case SPVM_OPCODE_C_CODE_COMPLEMENT_BYTE:
              SPVM_JITCODE_BUILDER_add_complement(string_buffer, "SPVM_API_byte", opcode->operand0, opcode->operand1);
              break;
            case SPVM_OPCODE_C_CODE_COMPLEMENT_SHORT:
              SPVM_JITCODE_BUILDER_add_complement(string_buffer, "SPVM_API_short", opcode->operand0, opcode->operand1);
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
              SPVM_STRING_BUFFER_add(string_buffer, " = NULL;\n");
              break;
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_BYTE:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_SHORT:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_INT:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_LONG:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_FLOAT:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_DOUBLE:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_OBJECT:
            {
              char* element_type = NULL;
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_BYTE:
                  element_type = "SPVM_API_byte";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_SHORT:
                  element_type = "SPVM_API_short";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_INT:
                  element_type = "SPVM_API_int";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_LONG:
                  element_type = "SPVM_API_long";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_FLOAT:
                  element_type = "float";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_DOUBLE:
                  element_type = "double";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_OBJECT:
                  element_type = "SPVM_API_OBJECT*";
              }
              
              SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " == NULL, 0)) { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      api->set_exception(api, api->new_string(api, \"Array must not be undef\", 0)); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      croak_flag = 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "  else { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, " < 0 || ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, "  >= *(int32_t*)((intptr_t)");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_JITCODE_C_OBJECT_LENGTH_BYTE_OFFSET), 0)) { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        api->set_exception(api, api->new_string(api, \"Index is out of range\", 0)); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        croak_flag = 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = *(");
              SPVM_STRING_BUFFER_add(string_buffer, element_type);
              SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_JITCODE_C_OBJECT_HEADER_BYTE_SIZE + sizeof(");
              SPVM_STRING_BUFFER_add(string_buffer, element_type);
              SPVM_STRING_BUFFER_add(string_buffer, ") * ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, "); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
              break;
            }
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_BYTE:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_SHORT:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_INT:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_LONG:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_FLOAT:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_DOUBLE:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_OBJECT:
            {
              char* element_type = NULL;
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_BYTE:
                  element_type = "SPVM_API_byte";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_SHORT:
                  element_type = "SPVM_API_short";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_INT:
                  element_type = "SPVM_API_int";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_LONG:
                  element_type = "SPVM_API_long";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_FLOAT:
                  element_type = "float";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_DOUBLE:
                  element_type = "double";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_OBJECT:
                  element_type = "SPVM_API_OBJECT*";
              }
              
              SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " == NULL, 0)) { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->new_string(api, \"Array must not be undef\", 0)); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "  else { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " < 0 || ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, "  >= *(int32_t*)((intptr_t)");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_JITCODE_C_OBJECT_LENGTH_BYTE_OFFSET), 0)) { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        api->set_exception(api, api->new_string(api, \"Index is out of range\", 0)); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        croak_flag = 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
              
              if (opcode->code == SPVM_OPCODE_C_CODE_ARRAY_STORE_OBJECT) {
                SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT** object_address = (SPVM_API_OBJECT**)((intptr_t)");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
                SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_JITCODE_C_OBJECT_HEADER_BYTE_SIZE + sizeof(void*) * ");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
                SPVM_STRING_BUFFER_add(string_buffer, ");\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      if (*object_address != NULL) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        if (SPVM_JITCODE_INLINE_GET_REF_COUNT(*object_address) > 1) { SPVM_JITCODE_INLINE_DEC_REF_COUNT_ONLY(*object_address); }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        else { api->dec_ref_count(api, *object_address); }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
                
                SPVM_STRING_BUFFER_add(string_buffer, "      *object_address = ");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand2);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                
                SPVM_STRING_BUFFER_add(string_buffer, "      if (*object_address != NULL) { SPVM_JITCODE_INLINE_INC_REF_COUNT(*object_address); }\n");
              }
              else {
                SPVM_STRING_BUFFER_add(string_buffer, "      *(");
                SPVM_STRING_BUFFER_add(string_buffer, element_type);
                SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
                SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_JITCODE_C_OBJECT_HEADER_BYTE_SIZE + sizeof(");
                SPVM_STRING_BUFFER_add(string_buffer, element_type);
                SPVM_STRING_BUFFER_add(string_buffer, ") * ");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
                SPVM_STRING_BUFFER_add(string_buffer, ") = ");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand2);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              }

              SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_MOVE:
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_INC_REF_COUNT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  if (");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " != NULL) { SPVM_JITCODE_INLINE_INC_REF_COUNT(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_DEC_REF_COUNT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  if (");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " != NULL) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_JITCODE_INLINE_GET_REF_COUNT(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ") > 1) { SPVM_JITCODE_INLINE_DEC_REF_COUNT_ONLY(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    else { api->dec_ref_count(api, ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_NEW_OBJECT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = api->new_object(api, ");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_NEW_BYTE_ARRAY:
            case SPVM_OPCODE_C_CODE_NEW_SHORT_ARRAY:
            case SPVM_OPCODE_C_CODE_NEW_INT_ARRAY:
            case SPVM_OPCODE_C_CODE_NEW_LONG_ARRAY:
            case SPVM_OPCODE_C_CODE_NEW_FLOAT_ARRAY:
            case SPVM_OPCODE_C_CODE_NEW_DOUBLE_ARRAY:
            {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_NEW_BYTE_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "api->new_byte_array(api, ");
                  SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
                  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
                  break;
                case SPVM_OPCODE_C_CODE_NEW_SHORT_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "api->new_short_array(api, ");
                  SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
                  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
                  break;
                case SPVM_OPCODE_C_CODE_NEW_INT_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "api->new_int_array(api, ");
                  SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
                  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
                  break;
                case SPVM_OPCODE_C_CODE_NEW_LONG_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "api->new_long_array(api, ");
                  SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
                  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
                  break;
                case SPVM_OPCODE_C_CODE_NEW_FLOAT_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "api->new_float_array(api, ");
                  SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
                  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
                  break;
                case SPVM_OPCODE_C_CODE_NEW_DOUBLE_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "api->new_double_array(api, ");
                  SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
                  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
                  break;
              }
              break;
            }
            case SPVM_OPCODE_C_CODE_NEW_OBJECT_ARRAY: {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = api->new_object_array(api, ");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ", ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_NEW_STRING: {
              int32_t name_id = opcode->operand1;
              int32_t length = constant_pool[name_id];
              char* name = (char*)&constant_pool[name_id + 1];
              
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = api->new_string(api, (const char*)");
              SPVM_STRING_BUFFER_add_address(string_buffer, name);
              SPVM_STRING_BUFFER_add(string_buffer, ", ");
              SPVM_STRING_BUFFER_add_int(string_buffer, length);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_ARRAY_LENGTH: {
              SPVM_STRING_BUFFER_add(string_buffer, "  if (");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " == NULL) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->new_string(api, \"Can't get array length of undef value.\", 0));\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = *(int32_t*)((intptr_t)");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_JITCODE_C_OBJECT_LENGTH_BYTE_OFFSET);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_GET_FIELD_BYTE:
            case SPVM_OPCODE_C_CODE_GET_FIELD_SHORT:
            case SPVM_OPCODE_C_CODE_GET_FIELD_INT:
            case SPVM_OPCODE_C_CODE_GET_FIELD_LONG:
            case SPVM_OPCODE_C_CODE_GET_FIELD_FLOAT:
            case SPVM_OPCODE_C_CODE_GET_FIELD_DOUBLE:
            case SPVM_OPCODE_C_CODE_GET_FIELD_OBJECT:
            {
              char* field_type = NULL;
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_GET_FIELD_BYTE:
                  field_type = "SPVM_API_byte";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_SHORT:
                  field_type = "SPVM_API_short";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_INT:
                  field_type = "SPVM_API_int";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_LONG:
                  field_type = "SPVM_API_long";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_FLOAT:
                  field_type = "float";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_DOUBLE:
                  field_type = "double";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_OBJECT:
                  field_type = "SPVM_API_OBJECT*";
              }
              
              int32_t field_id = opcode->operand2;
              SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
              int32_t field_byte_offset = constant_pool_field->byte_offset;
              
              SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " == NULL, 0)) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->new_string(api, \"Object must be not undef.\", 0));\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = *(");
              SPVM_STRING_BUFFER_add(string_buffer, field_type);
              SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_JITCODE_C_OBJECT_HEADER_BYTE_SIZE + ");
              SPVM_STRING_BUFFER_add_int(string_buffer, field_byte_offset);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_SET_FIELD_BYTE:
            case SPVM_OPCODE_C_CODE_SET_FIELD_SHORT:
            case SPVM_OPCODE_C_CODE_SET_FIELD_INT:
            case SPVM_OPCODE_C_CODE_SET_FIELD_LONG:
            case SPVM_OPCODE_C_CODE_SET_FIELD_FLOAT:
            case SPVM_OPCODE_C_CODE_SET_FIELD_DOUBLE:
            case SPVM_OPCODE_C_CODE_SET_FIELD_OBJECT:
            {
              int32_t field_id = opcode->operand1;
              SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
              int32_t field_byte_offset = constant_pool_field->byte_offset;
              
              SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " == NULL, 0)) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, api->new_string(api, \"Object must be not undef.\", 0));\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
              if (opcode->code == SPVM_OPCODE_C_CODE_SET_FIELD_OBJECT) {
                SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT** field_address = (SPVM_API_OBJECT**)((intptr_t)");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
                SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_JITCODE_C_OBJECT_HEADER_BYTE_SIZE + ");
                SPVM_STRING_BUFFER_add_int(string_buffer, field_byte_offset);
                SPVM_STRING_BUFFER_add(string_buffer, ");\n");
                SPVM_STRING_BUFFER_add(string_buffer, "    if(*field_address != NULL) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      if (SPVM_JITCODE_INLINE_ISWEAK(*field_address)) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        api->unweaken(api, field_address);\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      if (SPVM_JITCODE_INLINE_GET_REF_COUNT(*field_address) > 1) { SPVM_JITCODE_INLINE_DEC_REF_COUNT_ONLY(*field_address); }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      else { api->dec_ref_count(api, *field_address); }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "    *field_address = ");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand2);
                SPVM_STRING_BUFFER_add(string_buffer, "  ;\n");
                SPVM_STRING_BUFFER_add(string_buffer, "    if(*field_address != NULL) { SPVM_JITCODE_INLINE_INC_REF_COUNT(*field_address); }\n");
              }
              else {
                char* field_type = NULL;
                switch (opcode->code) {
                  case SPVM_OPCODE_C_CODE_SET_FIELD_BYTE:
                    field_type = "SPVM_API_byte";
                    break;
                  case SPVM_OPCODE_C_CODE_SET_FIELD_SHORT:
                    field_type = "SPVM_API_short";
                    break;
                  case SPVM_OPCODE_C_CODE_SET_FIELD_INT:
                    field_type = "SPVM_API_int";
                    break;
                  case SPVM_OPCODE_C_CODE_SET_FIELD_LONG:
                    field_type = "SPVM_API_long";
                    break;
                  case SPVM_OPCODE_C_CODE_SET_FIELD_FLOAT:
                    field_type = "float";
                    break;
                  case SPVM_OPCODE_C_CODE_SET_FIELD_DOUBLE:
                    field_type = "double";
                    break;
                }
                SPVM_STRING_BUFFER_add(string_buffer, "    *(");
                SPVM_STRING_BUFFER_add(string_buffer, field_type);
                SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
                SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_JITCODE_C_OBJECT_HEADER_BYTE_SIZE + ");
                SPVM_STRING_BUFFER_add_int(string_buffer, field_byte_offset);
                SPVM_STRING_BUFFER_add(string_buffer, ") = ");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand2);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              }
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_WEAKEN_FIELD_OBJECT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  api->weaken_object_field(api, ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ", ");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (SPVM_JITCODE_INLINE_GET_EXCEPTION()) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_STRING:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_BYTE:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_SHORT:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_INT:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_LONG:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_FLOAT:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_DOUBLE:
            {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_STRING:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_string(api, ");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_BYTE:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_byte(api, ");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_SHORT:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_short(api, ");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_INT:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_int(api, ");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_LONG:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_long(api, ");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_FLOAT:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_float(api, ");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_DOUBLE:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_double(api, ");
                  break;
              }
              
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ", ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " == NULL) {\n");
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
              SPVM_STRING_BUFFER_add(string_buffer, "; }");
              break;
            }
            case SPVM_OPCODE_C_CODE_PUSH_EVAL: {
              eval_stack_top++;
              eval_stack[eval_stack_top] = opcode->operand0;
              
              break;
            }
            case SPVM_OPCODE_C_CODE_POP_EVAL: {
              eval_stack_top--;
              
              break;
            }
            case SPVM_OPCODE_C_CODE_LOAD_EXCEPTION_VAR: {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, "   = SPVM_JITCODE_INLINE_GET_EXCEPTION();\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_STORE_EXCEPTION_VAR: {
              SPVM_STRING_BUFFER_add(string_buffer, "  api->set_exception(api, ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
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
              
              SPVM_API_VALUE* package_vars = runtime->package_vars;
              int32_t package_var_id = opcode->operand1;
              SPVM_API_VALUE** package_var_address = (SPVM_API_VALUE**)&package_vars[package_var_id];
              
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = *(");
              SPVM_STRING_BUFFER_add(string_buffer, package_var_type);
              SPVM_STRING_BUFFER_add(string_buffer, "*)");
              SPVM_STRING_BUFFER_add_address(string_buffer, package_var_address);
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
              
              SPVM_API_VALUE* package_vars = runtime->package_vars;
              int32_t package_var_id = opcode->operand0;
              SPVM_API_VALUE** package_var_address = (SPVM_API_VALUE**)&package_vars[package_var_id];
              
              SPVM_STRING_BUFFER_add(string_buffer, "  *(");
              SPVM_STRING_BUFFER_add(string_buffer, package_var_type);
              SPVM_STRING_BUFFER_add(string_buffer, "*)");
              SPVM_STRING_BUFFER_add_address(string_buffer, package_var_address);
              SPVM_STRING_BUFFER_add(string_buffer, " = ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_OBJECT: {
              int32_t package_var_id = opcode->operand0;
              SPVM_API_VALUE* package_vars = runtime->package_vars;
              SPVM_API_VALUE** package_var_address = (SPVM_API_VALUE**)&package_vars[package_var_id];
              
              SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT** package_var_address = (SPVM_API_OBJECT**)");
              SPVM_STRING_BUFFER_add_address(string_buffer, package_var_address);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (*(SPVM_API_OBJECT**)package_var_address != NULL) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      if (SPVM_JITCODE_INLINE_GET_REF_COUNT(*package_var_address) > 1) { SPVM_JITCODE_INLINE_DEC_REF_COUNT_ONLY(*package_var_address); }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      else { api->dec_ref_count(api, *(SPVM_API_OBJECT**)package_var_address); }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_API_OBJECT**)package_var_address = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (*(SPVM_API_OBJECT**)package_var_address != NULL) { SPVM_JITCODE_INLINE_INC_REF_COUNT(*package_var_address); }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_PUSH_ARG: {
              call_sub_arg_stack_top++;
              call_sub_arg_stack[call_sub_arg_stack_top].int_value = opcode->operand0;
              
              break;
            }
            case SPVM_OPCODE_C_CODE_CURRENT_LINE:
              if (runtime->debug) {
                SPVM_STRING_BUFFER_add(string_buffer, "  current_line = ");
                SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              }
              break;
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
              
              // Subroutine argument length
              int32_t call_sub_is_void = constant_pool_sub_call_sub->is_void;

              int32_t call_sub_abs_name_id = constant_pool_sub_call_sub->abs_name_id;
              
              // Subroutine name
              const char* call_sub_abs_name = (char*)&constant_pool[call_sub_abs_name_id + 1];

              int32_t call_sub_return_type_id = constant_pool_sub_call_sub->return_type_id;
              SPVM_CONSTANT_POOL_TYPE* call_sub_return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[call_sub_return_type_id];
              
              SPVM_STRING_BUFFER_add(string_buffer, "  // ");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)call_sub_abs_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
              
              if (call_sub_args_length > 0) {
                SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_VALUE call_sub_args[");
                SPVM_STRING_BUFFER_add_int(string_buffer, call_sub_args_length);
                SPVM_STRING_BUFFER_add(string_buffer, "];\n");
              }
              
              {
                int32_t call_sub_arg_index;
                for (call_sub_arg_index = 0; call_sub_arg_index < call_sub_args_length; call_sub_arg_index++) {
                  int32_t call_sub_arg_type_id = constant_pool[call_sub_arg_type_ids_base + call_sub_arg_index];
                  
                  // Argument type code
                  SPVM_CONSTANT_POOL_TYPE* constant_pool_call_sub_arg_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[call_sub_arg_type_id];
                  int32_t call_sub_arg_type_code = constant_pool_call_sub_arg_type->code;
                  
                  SPVM_STRING_BUFFER_add(string_buffer, "    *(");
                  SPVM_STRING_BUFFER_add(string_buffer, SPVM_JITCODE_BUILDER_get_type_name(call_sub_arg_type_code));
                  SPVM_STRING_BUFFER_add(string_buffer, "*)&call_sub_args[");
                  SPVM_STRING_BUFFER_add_int(string_buffer, call_sub_arg_index);
                  SPVM_STRING_BUFFER_add(string_buffer, "]");
                  SPVM_STRING_BUFFER_add(string_buffer, " = ");
                  SPVM_JITCODE_BUILDER_add_var(string_buffer, call_sub_arg_stack[call_sub_arg_index].int_value);
                  
                  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                }
              }
              
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_VALUE call_sub_return_value = api->call_sub(api, ");
              SPVM_STRING_BUFFER_add_int(string_buffer, call_sub_id);
              if (call_sub_args_length > 0) {
                SPVM_STRING_BUFFER_add(string_buffer, ", call_sub_args");
              }
              else {
                SPVM_STRING_BUFFER_add(string_buffer, ", NULL");
              }
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              
              if (!call_sub_is_void) {
                SPVM_STRING_BUFFER_add(string_buffer, "    ");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
                SPVM_STRING_BUFFER_add(string_buffer, " = ");
                SPVM_STRING_BUFFER_add(string_buffer, "*(");
                SPVM_STRING_BUFFER_add(string_buffer, SPVM_JITCODE_BUILDER_get_type_name(call_sub_return_type->code));
                SPVM_STRING_BUFFER_add(string_buffer, "*)&call_sub_return_value;");
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              }
              
              SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_JITCODE_INLINE_GET_EXCEPTION()) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      croak_flag = 1;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

              call_sub_arg_stack_top -= call_sub_args_length;
              
              break;
            }
            case SPVM_OPCODE_C_CODE_IF_CROAK_CATCH: {
              SPVM_STRING_BUFFER_add(string_buffer, "  if (croak_flag) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    croak_flag = 0;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    goto L");
              SPVM_STRING_BUFFER_add_int(string_buffer,  opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_IF_CROAK_RETURN: {
              SPVM_STRING_BUFFER_add(string_buffer, "  if (croak_flag) {\n");
              if (!sub_is_void) {
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
              if (!constant_pool_sub->is_void) {
                SPVM_STRING_BUFFER_add(string_buffer, "  return_value = ");
                SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              }
              SPVM_STRING_BUFFER_add(string_buffer, "  goto label_SPVM_OPCODE_C_CODE_RETURN;\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_TABLE_SWITCH:
              // TABLE_SWITCH is no longer used
              assert(0);
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
              SPVM_JITCODE_BUILDER_add_var(string_buffer, opcode->operand0);
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
          
          // Increment ref count of return value not to release by decrement
          if (return_type_code > SPVM_TYPE_C_CODE_DOUBLE) {
            SPVM_STRING_BUFFER_add(string_buffer, "  if (return_value != NULL) {\n");
            SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_JITCODE_INLINE_INC_REF_COUNT(return_value);\n");
            SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
          }
          
          // Decrement my vars
          {
            int32_t i;
            for (i = 0; i < sub_object_mys_length; i++) {
              int32_t my_var_index = constant_pool[sub_object_mys_base + i];
              SPVM_STRING_BUFFER_add(string_buffer, "  if (");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, my_var_index);
              SPVM_STRING_BUFFER_add(string_buffer, " != NULL) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_JITCODE_INLINE_GET_REF_COUNT(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, my_var_index);
              SPVM_STRING_BUFFER_add(string_buffer, ") > 1) { SPVM_JITCODE_INLINE_DEC_REF_COUNT_ONLY(");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, my_var_index);
              SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    else { api->dec_ref_count(api, ");
              SPVM_JITCODE_BUILDER_add_var(string_buffer, my_var_index);
              SPVM_STRING_BUFFER_add(string_buffer, "); }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
            }
          }
          
          // Decrement ref count of return value
          if (return_type_code > SPVM_TYPE_C_CODE_DOUBLE) {
            SPVM_STRING_BUFFER_add(string_buffer, "  if (return_value != NULL) { SPVM_JITCODE_INLINE_DEC_REF_COUNT_ONLY(return_value); }\n");
          }
          
          // Throw exception
          SPVM_STRING_BUFFER_add(string_buffer, "  if (croak_flag) {\n");
          if (runtime->debug) {
            // Exception stack trace
            SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* exception_stack_trace = api->create_exception_stack_trace(api, ");
            SPVM_STRING_BUFFER_add_int(string_buffer, sub_id);
            SPVM_STRING_BUFFER_add(string_buffer, "    , SPVM_JITCODE_INLINE_GET_EXCEPTION(), current_line);\n");
            SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, exception_stack_trace);\n");
          }
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
          
          // No exception
          SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_JITCODE_INLINE_SET_EXCEPTION_NULL();\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
          
          if (sub_is_void) {
            SPVM_STRING_BUFFER_add(string_buffer, "  return;\n");
          }
          else {
            SPVM_STRING_BUFFER_add(string_buffer, "  return return_value;\n");
          }
        }
      }
      
      // Close subroutine
      SPVM_STRING_BUFFER_add(string_buffer, "}\n");
      SPVM_STRING_BUFFER_add(string_buffer, "\n");
    }
  }

  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Define call_sub
  SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_VALUE SPVM_JITCODE_call_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_VALUE return_value;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  switch(sub_id) {\n");
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < subs_length; sub_index++) {
      int32_t sub_id = constant_pool[subs_base + sub_index];
      
      SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];
      int32_t sub_abs_name_id = constant_pool_sub->abs_name_id;
      
      // Subroutine name
      const char* sub_abs_name = (char*)&constant_pool[sub_abs_name_id + 1];
      
      // Return type code
      int32_t return_type_id = constant_pool_sub->return_type_id;
      SPVM_CONSTANT_POOL_TYPE* return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[return_type_id];
      
      SPVM_STRING_BUFFER_add(string_buffer, "    case ");
      SPVM_STRING_BUFFER_add_int(string_buffer, sub_id);
      SPVM_STRING_BUFFER_add(string_buffer, ":\n");

      SPVM_STRING_BUFFER_add(string_buffer, "      ");

      // Return value
      if (!constant_pool_sub->is_void) {
        SPVM_STRING_BUFFER_add(string_buffer, "*(");
        SPVM_STRING_BUFFER_add(string_buffer, SPVM_JITCODE_BUILDER_get_type_name(return_type->code));
        SPVM_STRING_BUFFER_add(string_buffer, "*)&return_value = ");
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
      SPVM_STRING_BUFFER_add(string_buffer, "(api, args);\n");
      SPVM_STRING_BUFFER_add(string_buffer, "      break;\n");
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "    default:\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      fprintf(stderr, \"Unknown subroutine is called in SPVM_JITCODE_call_sub(). subroutine id is %%d.\", sub_id);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exit(1);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  return return_value;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "}\n");
  
  const char* jit_source_file = runtime->jit_source_file;
  FILE* jitcode_fh = fopen(jit_source_file, "w");
  if (jitcode_fh) {
    fprintf(jitcode_fh, string_buffer->buffer);
    fclose(jitcode_fh);
  }
  else {
    fprintf(stderr, "Can't open file %s", jit_source_file);
    exit(1);
  }
}

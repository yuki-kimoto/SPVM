#ifndef SPVM_PRECOMPILE_H
#define SPVM_PRECOMPILE_H

#include "spvm_native.h"
#include "spvm_typedecl.h"

enum {
  SPVM_PRECOMPILE_C_CTYPE_ID_BYTE,
  SPVM_PRECOMPILE_C_CTYPE_ID_SHORT,
  SPVM_PRECOMPILE_C_CTYPE_ID_INT,
  SPVM_PRECOMPILE_C_CTYPE_ID_LONG,
  SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT,
  SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE,
  SPVM_PRECOMPILE_C_CTYPE_ID_BOOL_OBJECT,
  SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT,
  SPVM_PRECOMPILE_C_CTYPE_ID_REF,
};

// Constant macro
#define SPVM_PRECOMPILE_OBJECT_HEADER_BYTE_SIZE sizeof(SPVM_OBJECT)
#define SPVM_PRECOMPILE_OBJECT_LENGTH_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, length))
#define SPVM_PRECOMPILE_OBJECT_REF_COUNT_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, ref_count))
#define SPVM_PRECOMPILE_RUNTIME_EXCEPTION_BYTE_OFFSET ((int32_t)offsetof(SPVM_RUNTIME, exception))
#define SPVM_PRECOMPILE_TYPE_CODE_VOID (SPVM_NATIVE_C_BASIC_TYPE_ID_VOID)
#define SPVM_PRECOMPILE_TYPE_CODE_BYTE (SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE)
#define SPVM_PRECOMPILE_TYPE_CODE_SHORT (SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT)
#define SPVM_PRECOMPILE_TYPE_CODE_INT (SPVM_NATIVE_C_BASIC_TYPE_ID_INT)
#define SPVM_PRECOMPILE_TYPE_CODE_LONG (SPVM_NATIVE_C_BASIC_TYPE_ID_LONG)
#define SPVM_PRECOMPILE_TYPE_CODE_FLOAT (SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT)
#define SPVM_PRECOMPILE_TYPE_CODE_DOUBLE (SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE)

// Inline macro function
#define SPVM_PRECOMPILE_INLINE_INC_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + SPVM_PRECOMPILE_OBJECT_REF_COUNT_BYTE_OFFSET))++)
#define SPVM_PRECOMPILE_INLINE_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + SPVM_PRECOMPILE_OBJECT_REF_COUNT_BYTE_OFFSET))--)
#define SPVM_PRECOMPILE_INLINE_GET_EXCEPTION() (*(void**)((intptr_t)SPVM_PRECOMPILE_RUNTIME + SPVM_PRECOMPILE_RUNTIME_EXCEPTION_BYTE_OFFSET))
#define SPVM_PRECOMPILE_INLINE_SET_EXCEPTION_NULL() \
  do { \
    if ((*(void**)((intptr_t)SPVM_PRECOMPILE_RUNTIME + SPVM_PRECOMPILE_RUNTIME_EXCEPTION_BYTE_OFFSET)) != NULL) { \
      env->dec_ref_count(env, (*(void**)((intptr_t)SPVM_PRECOMPILE_RUNTIME + SPVM_PRECOMPILE_RUNTIME_EXCEPTION_BYTE_OFFSET))); \
    } \
    (*(void**)((intptr_t)SPVM_PRECOMPILE_RUNTIME + SPVM_PRECOMPILE_RUNTIME_EXCEPTION_BYTE_OFFSET)) = NULL; \
  } \
  while (0) \

#define SPVM_PRECOMPILE_INLINE_ISWEAK(object) ((intptr_t)object & 1)


void SPVM_PRECOMPILE_create_precompile_source(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, const char* class_name);
void SPVM_PRECOMPILE_build_head(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer);
void SPVM_PRECOMPILE_build_method_declaration(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, const char* class_name, const char* method_name);
void SPVM_PRECOMPILE_build_method_implementation(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, const char* class_name, const char* method_name);

const char* SPVM_PRECOMPILE_get_ctype_name(SPVM_ENV* env, int32_t ctype_id);
void SPVM_PRECOMPILE_add_var(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index);
void SPVM_PRECOMPILE_add_var_value(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index, int32_t field_index);
void SPVM_PRECOMPILE_add_operand(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index);
void SPVM_PRECOMPILE_add_operand_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index);
void SPVM_PRECOMPILE_add_stack(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index);
void SPVM_PRECOMPILE_add_operand_value(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index, int32_t field_index);
void SPVM_PRECOMPILE_add_bool(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in_index);
void SPVM_PRECOMPILE_add_numeric_eq(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_numeric_ne(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_numeric_gt(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_numeric_ge(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_numeric_lt(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_numeric_le(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_numeric_cmp(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_add(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_subtract(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_multiply(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_divide_integral(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_divide_unsigned_int(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_divide_unsigned_long(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_divide_floating_point(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_remainder_integral(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_remainder_unsigned_int(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_remainder_unsigned_long(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_left_shift(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_right_logical_shift(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_right_arithmetic_shift(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_bit_and(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_bit_or(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_bit_xor(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index);
void SPVM_PRECOMPILE_add_negate(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index);
void SPVM_PRECOMPILE_add_plus(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index);
void SPVM_PRECOMPILE_add_complement(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index);
void SPVM_PRECOMPILE_add_inc(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t number);
void SPVM_PRECOMPILE_add_convert(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t out_ctype_id, int32_t in_ctype_id, int32_t out_index, int32_t in_index);
void SPVM_PRECOMPILE_add_array_fetch(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index);
void SPVM_PRECOMPILE_add_array_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index);
void SPVM_PRECOMPILE_add_mulnum_array_fetch(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index, int32_t fields_length);
void SPVM_PRECOMPILE_add_mulnum_array_field_fetch(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index, int32_t fields_length, int32_t field_index);
void SPVM_PRECOMPILE_add_mulnum_array_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index, int32_t fields_length);
void SPVM_PRECOMPILE_add_mulnum_array_field_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index, int32_t fields_length, int32_t field_index);
void SPVM_PRECOMPILE_add_mulnum_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_var_id, int32_t ref_var_id, int32_t fields_length);
void SPVM_PRECOMPILE_add_mulnum_deref_get_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_var_id, int32_t ref_var_id, int32_t field_index);
void SPVM_PRECOMPILE_add_mulnum_deref_set_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t ref_var_id, int32_t in_var_id, int32_t field_index);
void SPVM_PRECOMPILE_add_move(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index);
void SPVM_PRECOMPILE_add_get_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index);
void SPVM_PRECOMPILE_add_set_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index);
void SPVM_PRECOMPILE_add_get_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t field_ctype_id, int32_t out_index, int32_t object_index, int32_t field_id);
void SPVM_PRECOMPILE_add_set_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t field_ctype_id, int32_t object_index, int32_t field_id, int32_t in_index);


#endif

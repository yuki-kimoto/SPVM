// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_IMPLEMENT_H
#define SPVM_IMPLEMENT_H

#include <inttypes.h>
#include <stdlib.h>










enum {
  SPVM_IMPLEMENT_C_EXCEPTION_ASSIGN_NOT_SATISFY_ASSIGNMENT_REQUIREMENT,
  SPVM_IMPLEMENT_C_EXCEPTION_ASSIGN_READ_ONLY_STRING_TO_MUTABLE_TYPE,
  SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO,
  SPVM_IMPLEMENT_C_EXCEPTION_STRING_CONCAT_LEFT_UNDEFINED,
  SPVM_IMPLEMENT_C_EXCEPTION_STRING_CONCAT_RIGHT_UNDEFINED,
  SPVM_IMPLEMENT_C_EXCEPTION_NEW_OBJECT_FAILED,
  SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED,
  SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL,
  SPVM_IMPLEMENT_C_EXCEPTION_NEW_STRING_FAILED,
  SPVM_IMPLEMENT_C_EXCEPTION_NEW_STRING_LEN_FAILED,
  SPVM_IMPLEMENT_C_EXCEPTION_NEW_STRING_LEN_LENGTH_SMALL,
  SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED,
  SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE,
  SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ASSIGN_NOT_SATISFY_ASSIGNMENT_REQUIREMENT,
  SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED,
  SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF,
  SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE,
  SPVM_IMPLEMENT_C_EXCEPTION_WEAKEN_BACK_REFERENCE_ALLOCATION_FAILED,
  SPVM_IMPLEMENT_C_EXCEPTION_ERROR_BASIC_TYPE_NOT_FOUND,
  SPVM_IMPLEMENT_C_EXCEPTION_ERROR_FIELD_NOT_FOUND,
  SPVM_IMPLEMENT_C_EXCEPTION_ERROR_CLASS_VAR_NOT_FOUND,
  SPVM_IMPLEMENT_C_EXCEPTION_ERROR_METHOD_NOT_FOUND,
  SPVM_IMPLEMENT_C_EXCEPTION_CALL_INSTANCE_METHOD_INVOCANT_UNDEF,
  SPVM_IMPLEMENT_C_EXCEPTION_CALL_INSTANCE_METHOD_IMPLEMENT_NOT_FOUND,
  SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED,
};













static const char* SPVM_IMPLEMENT_STRING_LITERALS[] = {
  "An assignment failed. %s type cannot be assigned to %s type.",
  "A read-only string cannnot be cast to mutable string type.",
  "A value of an integer type cannnot be divided by 0.",
  "The left operand of . operator must be defined.",
  "The right operand of . operator must be defined.",
  "A new operator failed. Memory allocation failed.",
  "A new operator to create an array failed. Memory allocation failed.",
  "A new operator to create an array failed. The length must be a non-negative integer.",
  "A string creation failed. Memory allocation failed.",
  "The new_string_len operator failed. Memory allocation failed.",
  "The new_string_len operator failed. The length of the string must be a non-negative integer.",
  "An array access failed. The array must be defined.",
  "An array access failed. The index is out of range.",
  "An array element set failed. %s type cannot be assigned to %s type.",
  "An field access failed. The invocant must be defined.",
  "An unboxing conversion failed. The operand must defined.",
  "An unboxing conversion failed. The destination type must be a numeric object type corresponding to the source type of the operand.",
  "The weaken operator failed. The memory allocation for the weaken back reference failed.",
  "%s basic type is not found.",
  "%s#%s field is not found.",
  "%s#%s class variable is not found.",
  "%s#%s method is not found.",
  "Can't call %s method on undefined value.",
  "An instance method call failed. %s#%s method is not found.",
  "An reference access failed. The reference must be defined.",
};

enum {
  SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_EQ,
  SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_NE,
  SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_GT,
  SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_GE,
  SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_LT,
  SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_LE,
  SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_CMP,
};

#define GET_DATA_ADDRESS(object) (intptr_t)*(void**)((intptr_t)object + sizeof(void*))

static inline void* SPVM_IMPLEMENT_GET_BASIC_TYPE_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  
  if (!basic_type) {
    snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_BASIC_TYPE_NOT_FOUND], basic_type_name);
    void* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  
  return basic_type;
}

static inline void* SPVM_IMPLEMENT_GET_FIELD_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name, int32_t* error_id) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  void* field = env->get_field_static(env, stack, basic_type_name, field_name);
  
  if (!field) {
    snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_FIELD_NOT_FOUND], basic_type_name, field_name);
    void* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    return NULL;
  }
  
  return field;
}

static inline int32_t SPVM_IMPLEMENT_GET_FIELD_OFFSET_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name, int32_t* error_id) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  void* field = env->get_field_static(env, stack, basic_type_name, field_name);
  
  if (!field) {
    snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_FIELD_NOT_FOUND], basic_type_name, field_name);
    void* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    return -1;
  }
  
  int32_t field_offset = env->api->field->get_offset(env->runtime, field);
  
  return field_offset;
}

static inline int32_t SPVM_IMPLEMENT_GET_FIELD_EXISTS_OFFSET_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name, int32_t* error_id) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  void* field = env->get_field_static(env, stack, basic_type_name, field_name);
  
  if (!field) {
    snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_FIELD_NOT_FOUND], basic_type_name, field_name);
    void* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    return -1;
  }
  
  int32_t field_exists_offset = env->api->field->get_exists_offset(env->runtime, field);
  
  return field_exists_offset;
}

static inline int32_t SPVM_IMPLEMENT_GET_FIELD_EXISTS_BIT_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name, int32_t* error_id) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  void* field = env->get_field_static(env, stack, basic_type_name, field_name);
  
  if (!field) {
    snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_FIELD_NOT_FOUND], basic_type_name, field_name);
    void* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    return -1;
  }
  
  int32_t field_exists_bit = env->api->field->get_exists_bit(env->runtime, field);
  
  return field_exists_bit;
}

static inline void* SPVM_IMPLEMENT_GET_CLASS_VAR_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  void* class_var = env->get_class_var(env, stack, basic_type_name, class_var_name);
  
  if (!class_var) {
    snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_CLASS_VAR_NOT_FOUND], basic_type_name, class_var_name);
    void* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  
  return class_var;
}

static inline void* SPVM_IMPLEMENT_GET_METHOD_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t* error_id) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  void* method = env->get_method(env, stack, basic_type_name, method_name);
  
  if (!method) {
    snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_METHOD_NOT_FOUND], basic_type_name, method_name);
    void* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  
  return method;
}

static inline void SPVM_IMPLEMENT_MOVE_OBJECT_UNDEF(SPVM_ENV* env, SPVM_VALUE* stack, void** dist_address) {
  env->assign_object(env, stack, dist_address, NULL);
}

static inline void SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(void* object, int32_t object_data_offset, int32_t exists_offset, int32_t exists_bit) {
  
  uint8_t* block = (uint8_t*)((intptr_t)object + object_data_offset + exists_offset);
  
  *block |= (1 << exists_bit);
}

static inline void SPVM_IMPLEMENT_DISABLE_EXISTS_FLAG(void* object, int32_t object_data_offset, int32_t exists_offset, int32_t exists_bit) {
  
  uint8_t* block = (uint8_t*)((intptr_t)object + object_data_offset + exists_offset);
  
  *block &= ~(1 << exists_bit);
}

static inline int32_t SPVM_IMPLEMENT_GET_EXISTS_FLAG(void* object, int32_t object_data_offset, int32_t exists_offset, int32_t exists_bit) {
  
  uint8_t* block = (uint8_t*)((intptr_t)object + object_data_offset + exists_offset);
  
  int32_t flag = !!(*block & (1 << exists_bit));
  
  return flag;
}

#define SPVM_IMPLEMENT_DROP_TAG_POINTERS(address) ((void*)((intptr_t)address & ~(intptr_t)1))

#define SPVM_IMPLEMENT_ENTER_SCOPE(mortal_stack, mortal_stack_top, mortal_stack_tops, mortal_stack_tops_index) (mortal_stack_tops[mortal_stack_tops_index] = mortal_stack_top)

#define SPVM_IMPLEMENT_PUSH_MORTAL(mortal_stack_typed_var_index, mortal_stack_top, object_vars_index) (mortal_stack_typed_var_index[mortal_stack_top++] = object_vars_index)

static inline void SPVM_IMPLEMENT_LEAVE_SCOPE(SPVM_ENV* env, SPVM_VALUE* stack, void** object_vars, int32_t* mortal_stack_typed_var_index, int32_t* mortal_stack_top_ptr, int32_t* mortal_stack_tops, int32_t mortal_stack_tops_index) {
  if (*mortal_stack_top_ptr > mortal_stack_tops[mortal_stack_tops_index]) {
    env->api->internal->leave_scope_local(env, stack, object_vars, mortal_stack_typed_var_index, mortal_stack_top_ptr, mortal_stack_tops, mortal_stack_tops_index);
  }
}

#define SPVM_IMPLEMENT_ADD_INT(out, in1, in2) (out = in1 + in2)

#define SPVM_IMPLEMENT_ADD_LONG(out, in1, in2) (out = in1 + in2)

#define SPVM_IMPLEMENT_ADD_FLOAT(out, in1, in2) (out = in1 + in2)

#define SPVM_IMPLEMENT_ADD_DOUBLE(out, in1, in2) (out = in1 + in2)

#define SPVM_IMPLEMENT_SUBTRACT_INT(out, in1, in2) (out = in1 - in2)

#define SPVM_IMPLEMENT_SUBTRACT_LONG(out, in1, in2) (out = in1 - in2)

#define SPVM_IMPLEMENT_SUBTRACT_FLOAT(out, in1, in2) (out = in1 - in2)

#define SPVM_IMPLEMENT_SUBTRACT_DOUBLE(out, in1, in2) (out = in1 - in2)

#define SPVM_IMPLEMENT_MULTIPLY_INT(out, in1, in2) (out = in1 * in2)

#define SPVM_IMPLEMENT_MULTIPLY_LONG(out, in1, in2) (out = in1 * in2)

#define SPVM_IMPLEMENT_MULTIPLY_FLOAT(out, in1, in2) (out = in1 * in2)

#define SPVM_IMPLEMENT_MULTIPLY_DOUBLE(out, in1, in2) (out = in1 * in2)

static inline void SPVM_IMPLEMENT_DIVIDE_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t in1, int32_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = in1 / in2;
  }
}

static inline void SPVM_IMPLEMENT_DIVIDE_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t in1, int64_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = in1 / in2;
  }
}

#define SPVM_IMPLEMENT_DIVIDE_FLOAT(out, in1, in2) (out = in1 / in2)

#define SPVM_IMPLEMENT_DIVIDE_DOUBLE(out, in1, in2) (out = in1 / in2)

static inline void SPVM_IMPLEMENT_DIVIDE_UNSIGNED_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t in1, int32_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = (uint32_t)in1 / (uint32_t)in2;
  }
}

static inline void SPVM_IMPLEMENT_DIVIDE_UNSIGNED_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t in1, int64_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = (uint64_t)in1 / (uint64_t)in2;
  }
}

static inline void SPVM_IMPLEMENT_MODULO_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t in1, int32_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    int32_t ret = in1 % in2;
    if ((in1 < 0) != (in2 < 0) && ret) { ret += in2; }
    *out = ret;
  }
}

static inline void SPVM_IMPLEMENT_MODULO_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t in1, int64_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    int64_t ret = in1 % in2;
    if ((in1 < 0) != (in2 < 0) && ret) { ret += in2; }
    *out = ret;
  }
}

static inline void SPVM_IMPLEMENT_MODULO_UNSIGNED_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t in1, int32_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = (uint32_t)in1 % (uint32_t)in2;
  }
}

static inline void SPVM_IMPLEMENT_MODULO_UNSIGNED_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t in1, int64_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = (uint64_t)in1 % (uint64_t)in2;
  }
}

#define SPVM_IMPLEMENT_LEFT_SHIFT_INT(out, in1, in2) (out = in1 << in2)
#define SPVM_IMPLEMENT_LEFT_SHIFT_LONG(out, in1, in2) (out = in1 << in2)

#define SPVM_IMPLEMENT_RIGHT_ARITHMETIC_SHIFT_INT(out, in1, in2) (out = in1 >> in2)
#define SPVM_IMPLEMENT_RIGHT_ARITHMETIC_SHIFT_LONG(out, in1, in2) (out = in1 >> in2)

#define SPVM_IMPLEMENT_RIGHT_LOGICAL_SHIFT_INT(out, in1, in2) (out = (int32_t)((uint32_t)in1 >> in2))
#define SPVM_IMPLEMENT_RIGHT_LOGICAL_SHIFT_LONG(out, in1, in2) (out = (int64_t)((uint64_t)in1 >> in2))

#define SPVM_IMPLEMENT_BIT_AND_INT(out, in1, in2) (out = in1 & in2)
#define SPVM_IMPLEMENT_BIT_AND_LONG(out, in1, in2) (out = in1 & in2)

#define SPVM_IMPLEMENT_BIT_OR_INT(out, in1, in2) (out = in1 | in2)
#define SPVM_IMPLEMENT_BIT_OR_LONG(out, in1, in2) (out = in1 | in2)

#define SPVM_IMPLEMENT_BIT_XOR_INT(out, in1, in2) (out = in1 ^ in2)
#define SPVM_IMPLEMENT_BIT_XOR_LONG(out, in1, in2) (out = in1 ^ in2)

#define SPVM_IMPLEMENT_MOVE_BYTE_ZERO(out) (out = 0)
#define SPVM_IMPLEMENT_MOVE_SHORT_ZERO(out) (out = 0)
#define SPVM_IMPLEMENT_MOVE_INT_ZERO(out) (out = 0)
#define SPVM_IMPLEMENT_MOVE_LONG_ZERO(out) (out = 0)
#define SPVM_IMPLEMENT_MOVE_FLOAT_ZERO(out) (out = 0)
#define SPVM_IMPLEMENT_MOVE_DOUBLE_ZERO(out) (out = 0)

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_BYTE_ZERO(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = 0;
  }
}

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_SHORT_ZERO(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = 0;
  }
}

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_INT_ZERO(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = 0;
  }
}

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_LONG_ZERO(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = 0;
  }
}

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_FLOAT_ZERO(SPVM_ENV* env, SPVM_VALUE* stack, float* out, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = 0;
  }
}

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_DOUBLE_ZERO(SPVM_ENV* env, SPVM_VALUE* stack, double* out, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = 0;
  }
}

#define SPVM_IMPLEMENT_MOVE_CONSTANT_BYTE(out, in) (out = in)
#define SPVM_IMPLEMENT_MOVE_CONSTANT_INT(out, in) (out = in)
#define SPVM_IMPLEMENT_MOVE_CONSTANT_LONG(out, in) (out = in)
#define SPVM_IMPLEMENT_MOVE_CONSTANT_FLOAT(out, in) (out = in)
#define SPVM_IMPLEMENT_MOVE_CONSTANT_DOUBLE(out, in) (out = in)

#define SPVM_IMPLEMENT_MOVE_BYTE(out, in) (out = in)
#define SPVM_IMPLEMENT_MOVE_SHORT(out, in) (out = in)
#define SPVM_IMPLEMENT_MOVE_INT(out, in) (out = in)
#define SPVM_IMPLEMENT_MOVE_LONG(out, in) (out = in)
#define SPVM_IMPLEMENT_MOVE_FLOAT(out, in) (out = in)
#define SPVM_IMPLEMENT_MOVE_DOUBLE(out, in) (out = in)
#define SPVM_IMPLEMENT_MOVE_OBJECT(env, stack, out, in) (env->assign_object(env, stack, out, in))

static inline void SPVM_IMPLEMENT_MOVE_OBJECT_WITH_TYPE_CHECK(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* in, void* dist_basic_type, int32_t dist_type_dimension, int32_t* error_id) {
  void* object = in;
  int32_t isa = env->isa(env, stack, object, dist_basic_type, dist_type_dimension);
  if (isa) {
    env->assign_object(env, stack, out, in);
  }
  else {
    int32_t scope_id = env->enter_scope(env, stack);
    
    void* obj_src_type_name = env->get_type_name(env, stack, object);
    const char* src_type_name = env->get_chars(env, stack, obj_src_type_name);
    const char* dist_basic_type_name = env->api->basic_type->get_name(env->runtime, dist_basic_type);
    void* obj_dist_type_name = env->get_compile_type_name(env, stack, dist_basic_type_name, dist_type_dimension, 0);
    const char* dist_type_name = env->get_chars(env, stack, obj_dist_type_name);
    char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
    snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ASSIGN_NOT_SATISFY_ASSIGNMENT_REQUIREMENT], src_type_name, dist_type_name);
    
    int32_t string_length = strlen(tmp_buffer);
    void* exception = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    
    env->leave_scope(env, stack, scope_id);
  }
}

static inline void SPVM_IMPLEMENT_MOVE_OBJECT_CHECK_READ_ONLY_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* in, int32_t* error_id) {
  
  void* string = in;
  if (env->is_string(env, stack, string) && env->is_read_only(env, stack, string)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ASSIGN_READ_ONLY_STRING_TO_MUTABLE_TYPE]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    env->assign_object(env, stack, out, string);
  }
}

#define SPVM_IMPLEMENT_MOVE_REF(out, in) (out = in)
#define SPVM_IMPLEMENT_MOVE_REF_UNDEF(out) (out = NULL)

#define SPVM_IMPLEMENT_BIT_NOT_INT(out, in) (out = ~in)
#define SPVM_IMPLEMENT_BIT_NOT_LONG(out, in) (out = ~in)
#define SPVM_IMPLEMENT_NEGATE_INT(out, in) (out = -in)
#define SPVM_IMPLEMENT_NEGATE_LONG(out, in) (out = -in)
#define SPVM_IMPLEMENT_NEGATE_FLOAT(out, in) (out = -in)
#define SPVM_IMPLEMENT_NEGATE_DOUBLE(out, in) (out = -in)

static inline void SPVM_IMPLEMENT_STRING_CONCAT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* in1, void* in2, int32_t* error_id) {
  void* string1 = in1;
  void* string2 = in2;
  if (string1 == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_STRING_CONCAT_LEFT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else if (string2 == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_STRING_CONCAT_RIGHT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    void* string3 = env->concat_no_mortal(env, stack, string1, string2);
    env->assign_object(env, stack, out, string3);
  }
}

#define SPVM_IMPLEMENT_CONDITION_EVALUATION_INT(out, in) (out = in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_LONG(out, in) (out = !!in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_FLOAT(out, in) (out = !!in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_DOUBLE(out, in) (out = !!in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_OBJECT(out, in) (out = !!in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_REF(out, in) (out = !!in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_BOOL_OBJECT(env, stack, out, in) (out = !!env->get_bool_object_value(env, stack, in))

#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_INT(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_LONG(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_FLOAT(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_DOUBLE(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_OBJECT(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_REF(out, in1, in2) (out = (in1 == in2))

#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_INT(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_LONG(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_FLOAT(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_DOUBLE(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_OBJECT(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_REF(out, in1, in2) (out = (in1 != in2))

#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_GT_INT(out, in1, in2) (out = (in1 > in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_GT_LONG(out, in1, in2) (out = (in1 > in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_GT_FLOAT(out, in1, in2) (out = (in1 > in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_GT_DOUBLE(out, in1, in2) (out = (in1 > in2))

#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_GE_INT(out, in1, in2) (out = (in1 >= in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_GE_LONG(out, in1, in2) (out = (in1 >= in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_GE_FLOAT(out, in1, in2) (out = (in1 >= in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_GE_DOUBLE(out, in1, in2) (out = (in1 >= in2))

#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_LT_INT(out, in1, in2) (out = (in1 < in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_LT_LONG(out, in1, in2) (out = (in1 < in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_LT_FLOAT(out, in1, in2) (out = (in1 < in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_LT_DOUBLE(out, in1, in2) (out = (in1 < in2))

#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_LE_INT(out, in1, in2) (out = (in1 <= in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_LE_LONG(out, in1, in2) (out = (in1 <= in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_LE_FLOAT(out, in1, in2) (out = (in1 <= in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_LE_DOUBLE(out, in1, in2) (out = (in1 <= in2))

#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_CMP_INT(out, in1, in2) (out = in1 > in2 ? 1 : in1 < in2 ? -1 : 0)
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_CMP_LONG(out, in1, in2) (out = in1 > in2 ? 1 : in1 < in2 ? -1 : 0)
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_CMP_FLOAT(out, in1, in2) (out = in1 > in2 ? 1 : in1 < in2 ? -1 : 0)
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_CMP_DOUBLE(out, in1, in2) (out = in1 > in2 ? 1 : in1 < in2 ? -1 : 0)

#define SPVM_IMPLEMENT_IS_UNDEF_OBJECT(out, in) (out = (in == NULL))
#define SPVM_IMPLEMENT_IS_UNDEF_REF(out, in) (out = (in == NULL))
#define SPVM_IMPLEMENT_IS_NOT_UNDEF_OBJECT(out, in) (out = (in != NULL))
#define SPVM_IMPLEMENT_IS_NOT_UNDEF_REF(out, in) (out = (in != NULL))

static inline void SPVM_IMPLEMENT_STRING_COMPARISON(SPVM_ENV* env, SPVM_VALUE* stack, int32_t comparison_op_id, int32_t* out, void* in1, void* in2, int32_t object_length_offset) {
  void* object1 = in1;
  void* object2 = in2;
  
  int32_t cmp = 0;
  if (object1 == NULL && object2 == NULL) {
    cmp = 0;
  }
  else if (object1 != NULL && object2 == NULL) {
    cmp = 1;
  }
  else if (object1 == NULL && object2 != NULL) {
    cmp = -1;
  }
  else {
    int32_t length1 = *(int32_t*)((intptr_t)object1 + object_length_offset);
    int32_t length2 = *(int32_t*)((intptr_t)object2 + object_length_offset);
    
    const char* bytes1 = env->get_chars(env, stack, object1);
    const char* bytes2 = env->get_chars(env, stack, object2);
    
    int32_t short_string_length = length1 < length2 ? length1 : length2;
    int32_t retval = memcmp(bytes1, bytes2, short_string_length);
    if (retval) {
      cmp = retval < 0 ? -1 : 1;
    }
    else if (length1 == length2) {
      cmp = 0;
    }
    else {
      cmp = length1 < length2 ? -1 : 1;
    }
  }
  
  int32_t flag;
  switch (comparison_op_id) {
    case SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_EQ: {
      flag = cmp == 0;
      break;
    }
    case SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_NE: {
      flag = cmp != 0;
      break;
    }
    case SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_GT: {
      flag = cmp > 0;
      break;
    }
    case SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_GE: {
      flag = cmp >= 0;
      break;
    }
    case SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_LT: {
      flag = cmp < 0;
      break;
    }
    case SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_LE: {
      flag = cmp <= 0;
      break;
    }
    case SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_CMP: {
      flag = cmp;
      break;
    }
  }
  
  *out = flag;
}

#define SPVM_IMPLEMENT_STRING_COMPARISON_EQ(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_EQ, out, in1, in2, object_length_offset))
#define SPVM_IMPLEMENT_STRING_COMPARISON_NE(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_NE, out, in1, in2, object_length_offset))
#define SPVM_IMPLEMENT_STRING_COMPARISON_GT(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_GT, out, in1, in2, object_length_offset))
#define SPVM_IMPLEMENT_STRING_COMPARISON_GE(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_GE, out, in1, in2, object_length_offset))
#define SPVM_IMPLEMENT_STRING_COMPARISON_LT(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_LT, out, in1, in2, object_length_offset))
#define SPVM_IMPLEMENT_STRING_COMPARISON_LE(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_LE, out, in1, in2, object_length_offset))
#define SPVM_IMPLEMENT_STRING_COMPARISON_CMP(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_CMP, out, in1, in2, object_length_offset))

static inline void SPVM_IMPLEMENT_NEW_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* basic_type, int32_t* error_id) {
  void* object = env->new_object_no_mortal(env, stack, basic_type);
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_OBJECT_FAILED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    // Push object
    env->assign_object(env, stack, out, object);
  }
}

static inline void SPVM_IMPLEMENT_NEW_OBJECT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* basic_type, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    void* object = env->new_object_array_no_mortal(env, stack, basic_type, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_MULDIM_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* basic_type, int32_t type_dimension, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    void* object = env->new_muldim_array_no_mortal(env, stack, basic_type, type_dimension, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_MULNUM_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* basic_type, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    void* object = env->new_mulnum_array_no_mortal(env, stack, basic_type, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_BYTE_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    void* object = env->new_byte_array_no_mortal(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_SHORT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    void* object = env->new_short_array_no_mortal(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_INT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    void* object = env->new_int_array_no_mortal(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_LONG_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    void* object = env->new_long_array_no_mortal(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_FLOAT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    void* object = env->new_float_array_no_mortal(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_DOUBLE_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    void* object = env->new_double_array_no_mortal(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, const char* constant_string, int32_t constant_string_length, int32_t* error_id) {
  void* string = env->new_string_no_mortal(env, stack, constant_string, constant_string_length);
  if (string == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_STRING_FAILED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    env->make_read_only(env, stack, string);
    env->assign_object(env, stack, out , string);
  }
}

static inline void SPVM_IMPLEMENT_NEW_STRING_LEN(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    void* string = env->new_string_no_mortal(env, stack, NULL, length);
    if (string == NULL) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_STRING_LEN_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, string);
    }
  }
  else {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_STRING_LEN_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

#define SPVM_IMPLEMENT_IS_READ_ONLY(env, stack, out, in) (out = env->is_read_only(env, stack, in))

#define SPVM_IMPLEMENT_IS_OPTIONS(env, stack, out, in) (out = env->is_options(env, stack, in))

#define SPVM_IMPLEMENT_MAKE_READ_ONLY(env, stack, in) (env->make_read_only(env, stack, in))

#define SPVM_IMPLEMENT_ENABLE_OPTIONS(env, stack, in) (env->enable_options(env, stack, in))

#define SPVM_IMPLEMENT_DISABLE_OPTIONS(env, stack, in) (env->disable_options(env, stack, in))

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void* array, int32_t index, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  
  int8_t element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((int8_t*)GET_DATA_ADDRESS(array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void* array, int32_t index, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  
  int16_t element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((int16_t*)GET_DATA_ADDRESS(array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* array, int32_t index, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  
  int32_t element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((int32_t*)GET_DATA_ADDRESS(array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, void* array, int32_t index, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  
  int64_t element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((int64_t*)GET_DATA_ADDRESS(array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, void* array, int32_t index, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  
  float element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((float*)GET_DATA_ADDRESS(array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, void* array, int32_t index, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  
  double element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((double*)GET_DATA_ADDRESS(array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* array, int32_t index, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  
  void* element = NULL;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      env->assign_object(env, stack, out, ((void**)GET_DATA_ADDRESS(array))[index]);
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int8_t in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int8_t*)GET_DATA_ADDRESS(array))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int16_t in, int32_t* error_id, int32_t object_header_short_size, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int16_t*)((intptr_t)array + object_header_short_size))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_INT(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int32_t in, int32_t* error_id, int32_t object_header_int_size, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int32_t*)((intptr_t)array + object_header_int_size))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_LONG(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int64_t in, int32_t* error_id, int32_t object_header_long_size, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int64_t*)((intptr_t)array + object_header_long_size))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, float in, int32_t* error_id, int32_t object_header_float_size, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((float*)((intptr_t)array + object_header_float_size))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, double in, int32_t* error_id, int32_t object_header_double_size, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((double*)((intptr_t)array + object_header_double_size))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      void** element_address = &((void**)GET_DATA_ADDRESS(array))[index];
      env->assign_object(env, stack, element_address, in);
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      void** element_address = &((void**)GET_DATA_ADDRESS(array))[index];
      void* object = in;
      int32_t elem_isa = env->elem_isa(env, stack, array, object);
      if (elem_isa) {
        env->assign_object(env, stack, element_address, object);
      }
      else {
        int32_t scope_id = env->enter_scope(env, stack);
        
        void* obj_src_type_name = env->get_type_name(env, stack, object);
        const char* src_type_name = env->get_chars(env, stack, obj_src_type_name);
        void* dist_basic_type = env->get_object_basic_type(env, stack, array);
        const char* dist_basic_type_name = env->api->basic_type->get_name(env->runtime, dist_basic_type);
        int32_t dist_type_dimension = env->get_object_type_dimension(env, stack, array) - 1;
        void* obj_dist_type_name = env->get_compile_type_name(env, stack, dist_basic_type_name, dist_type_dimension, 0);
        const char* dist_type_name = env->get_chars(env, stack, obj_dist_type_name);
        char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
        snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ASSIGN_NOT_SATISFY_ASSIGNMENT_REQUIREMENT], src_type_name, dist_type_name);
        
        int32_t string_length = strlen(tmp_buffer);
        void* exception = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
        env->set_exception(env, stack, exception);
        *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
        
        env->leave_scope(env, stack, scope_id);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_UNDEF(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      void* object_address = &((void**)GET_DATA_ADDRESS(array))[index];
      env->assign_object(env, stack, object_address, NULL);
    }
  }
}

static inline void SPVM_IMPLEMENT_ARRAY_LENGTH(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* array, int32_t* error_id, int32_t object_length_offset) {
  if (array == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int32_t*)((intptr_t)array + object_length_offset);
  }
}

static inline void SPVM_IMPLEMENT_STRING_LENGTH(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* string, int32_t object_length_offset) {
  if (string == NULL) {
    *out = 0;
  }
  else {
    *out = *(int32_t*)((intptr_t)string + object_length_offset);
  }
}

static inline void SPVM_IMPLEMENT_GET_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void* object, int32_t field_offset, int32_t* error_id, int32_t object_data_offset) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int8_t*)((intptr_t)object + object_data_offset + field_offset);
  }
}

static inline void SPVM_IMPLEMENT_GET_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void* object, int32_t field_offset, int32_t* error_id, int32_t object_header_short_size) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int16_t*)((intptr_t)object + object_header_short_size + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object, int32_t field_offset, int32_t* error_id, int32_t object_header_int_size) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int32_t*)((intptr_t)object + object_header_int_size + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, void* object, int32_t field_offset, int32_t* error_id, int32_t object_header_long_size) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int64_t*)((intptr_t)object + object_header_long_size + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, void* object, int32_t field_offset, int32_t* error_id, int32_t object_header_float_size) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(float*)((intptr_t)object + object_header_float_size + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, void* object, int32_t field_offset, int32_t* error_id, int32_t object_header_double_size) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(double*)((intptr_t)object + object_header_double_size + field_offset);
  }
}

static inline void SPVM_IMPLEMENT_GET_FIELD_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* object, int32_t field_offset, int32_t* error_id, int32_t object_data_offset) {  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    void** ref = (void**)((intptr_t)object + object_data_offset + field_offset);
    void* object = SPVM_IMPLEMENT_DROP_TAG_POINTERS(*ref);
    env->assign_object(env, stack, out, object);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_offset, int8_t in, int32_t* error_id, int32_t object_data_offset, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int8_t*)((intptr_t)object + object_data_offset + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(object, object_data_offset, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_offset, int16_t in, int32_t* error_id, int32_t object_data_offset, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int16_t*)((intptr_t)object + object_data_offset + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(object, object_data_offset, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_offset, int32_t in, int32_t* error_id, int32_t object_data_offset, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int32_t*)((intptr_t)object + object_data_offset + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(object, object_data_offset, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_offset, int64_t in, int32_t* error_id, int32_t object_data_offset, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int64_t*)((intptr_t)object + object_data_offset + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(object, object_data_offset, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_offset, float in, int32_t* error_id, int32_t object_data_offset, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(float*)((intptr_t)object + object_data_offset + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(object, object_data_offset, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_offset, double in, int32_t* error_id, int32_t object_data_offset, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(double*)((intptr_t)object + object_data_offset + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(object, object_data_offset, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_offset, void* in, int32_t* error_id, int32_t object_data_offset, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    void** ref = (void**)((intptr_t)object + object_data_offset + field_offset);
    env->assign_object(env, stack, ref, in);
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(object, object_data_offset, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_UNDEF(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_offset, int32_t* error_id, int32_t object_data_offset, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    void** ref = (void**)((intptr_t)object + object_data_offset + field_offset);
    env->assign_object(env, stack, ref, NULL);
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(object, object_data_offset, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_WEAKEN_FIELD(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_offset, int32_t* error_id, int32_t object_data_offset) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    void** ref = (void**)((intptr_t)object + object_data_offset + field_offset);
    int32_t status = env->weaken(env, stack, ref);
    if (status != 0) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_WEAKEN_BACK_REFERENCE_ALLOCATION_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
  }
}

static inline void SPVM_IMPLEMENT_UNWEAKEN_FIELD(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_offset, int32_t* error_id, int32_t object_data_offset) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    void** ref = (void**)((intptr_t)object + object_data_offset + field_offset);
    env->unweaken(env, stack, ref);
  }
}

static inline void SPVM_IMPLEMENT_ISWEAK_FIELD(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object, int32_t field_offset, int32_t* error_id, int32_t object_data_offset) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    void** ref = (void**)((intptr_t)object + object_data_offset + field_offset);
    *out = env->isweak(env, stack, ref);
  }
}

static inline void SPVM_IMPLEMENT_EXISTS(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object, int32_t field_exists_offset, int32_t field_exists_bit, int32_t* error_id, int32_t object_data_offset) {
  
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = SPVM_IMPLEMENT_GET_EXISTS_FLAG(object, object_data_offset, field_exists_offset, field_exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_DELETE(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int32_t* error_id) {
  
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    env->delete_field(env, stack, object, field);
  }
}

#define SPVM_IMPLEMENT_GET_CLASS_VAR_BYTE(env, stack, out, class_var) (out = env->get_class_var_byte(env, stack, class_var))
#define SPVM_IMPLEMENT_GET_CLASS_VAR_SHORT(env, stack, out, class_var) (out = env->get_class_var_short(env, stack, class_var))
#define SPVM_IMPLEMENT_GET_CLASS_VAR_INT(env, stack, out, class_var) (out = env->get_class_var_int(env, stack, class_var))
#define SPVM_IMPLEMENT_GET_CLASS_VAR_LONG(env, stack, out, class_var) (out = env->get_class_var_long(env, stack, class_var))
#define SPVM_IMPLEMENT_GET_CLASS_VAR_FLOAT(env, stack, out, class_var) (out = env->get_class_var_float(env, stack, class_var))
#define SPVM_IMPLEMENT_GET_CLASS_VAR_DOUBLE(env, stack, out, class_var) (out = env->get_class_var_double(env, stack, class_var))
#define SPVM_IMPLEMENT_GET_CLASS_VAR_OBJECT(env, stack, out, class_var) (env->assign_object(env, stack, out, env->get_class_var_object(env, stack, class_var)))

#define SPVM_IMPLEMENT_SET_CLASS_VAR_BYTE(env, stack, class_var, in) (env->set_class_var_byte(env, stack, class_var, in))
#define SPVM_IMPLEMENT_SET_CLASS_VAR_SHORT(env, stack, class_var, in) (env->set_class_var_short(env, stack, class_var, in))
#define SPVM_IMPLEMENT_SET_CLASS_VAR_INT(env, stack, class_var, in) (env->set_class_var_int(env, stack, class_var, in))
#define SPVM_IMPLEMENT_SET_CLASS_VAR_LONG(env, stack, class_var, in) (env->set_class_var_long(env, stack, class_var, in))
#define SPVM_IMPLEMENT_SET_CLASS_VAR_FLOAT(env, stack, class_var, in) (env->set_class_var_float(env, stack, class_var, in))
#define SPVM_IMPLEMENT_SET_CLASS_VAR_DOUBLE(env, stack, class_var, in) (env->set_class_var_double(env, stack, class_var, in))
#define SPVM_IMPLEMENT_SET_CLASS_VAR_OBJECT(env, stack, class_var, in) (env->assign_object(env, stack, env->get_class_var_object_ref(env, stack, class_var), in))
#define SPVM_IMPLEMENT_SET_CLASS_VAR_UNDEF(env, stack, class_var) (env->assign_object(env, stack, env->get_class_var_object_ref(env, stack, class_var), NULL))

#define SPVM_IMPLEMENT_GET_EXCEPTION_VAR(env, stack, out) (env->assign_object(env, stack, out, env->get_exception(env, stack)))
#define SPVM_IMPLEMENT_SET_EXCEPTION_VAR(env, stack, in) (env->set_exception(env, stack, in))
#define SPVM_IMPLEMENT_SET_EXCEPTION_VAR_UNDEF(env, stack) (env->set_exception(env, stack, NULL))

static inline void SPVM_IMPLEMENT_ISA(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object, void* dist_basic_type, int32_t dist_type_dimension) {
  if (object) {
    *out = env->isa(env, stack, object, dist_basic_type, dist_type_dimension);
  }
  else {
    *out = 0;
  }
}

static inline void SPVM_IMPLEMENT_ISA_ERROR(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* src_basic_type, void* dist_basic_type, int32_t dist_type_dimension) {
  *out = env->api->type->can_assign(env->runtime, dist_basic_type, dist_type_dimension, 0, src_basic_type, 0, 0);
}

static inline void SPVM_IMPLEMENT_IS_TYPE(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object, void* dist_basic_type, int32_t dist_type_dimension) {
  if (object) {
    *out = env->is_type(env, stack, object, dist_basic_type, dist_type_dimension);
  }
  else {
    *out = 0;
  }
}

static inline void SPVM_IMPLEMENT_IS_ERROR(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* src_basic_type, void* dist_basic_type, int32_t dist_type_dimension) {
  *out = (dist_basic_type == src_basic_type && dist_type_dimension == 0);
}

#define SPVM_IMPLEMENT_CAN(env, stack, out, object, method_name) (out = (env->get_instance_method(env, stack, object, method_name) != NULL))

static inline void SPVM_IMPLEMENT_PRINT(SPVM_ENV* env, SPVM_VALUE* stack, void* string) {
  env->print(env, stack, string);
}

static inline void SPVM_IMPLEMENT_SAY(SPVM_ENV* env, SPVM_VALUE* stack, void* string) {
  env->say(env, stack, string);
}

static inline void SPVM_IMPLEMENT_WARN(SPVM_ENV* env, SPVM_VALUE* stack, void* string, const char* basic_type_name, const char* method_name, const char* file, int32_t line) {
  env->warn(env, stack, string, basic_type_name, method_name, file, line);
}

#define SPVM_IMPLEMENT_CLEAR_EVAL_ERROR_ID(eval_error_id) (eval_error_id = 0)

#define SPVM_IMPLEMENT_GET_EVAL_ERROR_ID(out, eval_error_id) (out = eval_error_id)

#define SPVM_IMPLEMENT_SET_ERROR_ID(error_id, die_error_id) (error_id = die_error_id)

#define SPVM_IMPLEMENT_SET_EVAL_ERROR_ID(eval_error_id, die_error_id) (eval_error_id = die_error_id)

#define SPVM_IMPLEMENT_ARGS_WIDTH(env, stack, out) (out = env->args_width(env, stack))

#define SPVM_IMPLEMENT_GET_BASIC_TYPE_ID(env, stack, out, basic_type) (out = env->api->basic_type->get_id(env->runtime, basic_type))

static inline void SPVM_IMPLEMENT_TYPE_NAME(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* object) {
  if (object == NULL) {
    *out = NULL;
  }
  else {
    void* type_name = env->get_type_name_no_mortal(env, stack, object);
    env->assign_object(env, stack, out, type_name);
  }
}

static inline void SPVM_IMPLEMENT_DUMP(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* object) {
  void* dump = env->dump_no_mortal(env, stack, object);
  env->assign_object(env, stack, out, dump);
}

static inline void SPVM_IMPLEMENT_COPY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* object, int32_t* error_id) {
  void* object_copy = env->copy_no_mortal(env, stack, object);
  env->assign_object(env, stack, out, object_copy);
}

static inline void SPVM_IMPLEMENT_GET_ADDRESS(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* address) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  sprintf(tmp_buffer, "%p", address);
  
  void* object_address = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
  
  env->assign_object(env, stack, out, object_address);
}

#define SPVM_IMPLEMENT_REF_BYTE(out, in) (out = in)
#define SPVM_IMPLEMENT_REF_SHORT(out, in) (out = in)
#define SPVM_IMPLEMENT_REF_INT(out, in) (out = in)
#define SPVM_IMPLEMENT_REF_LONG(out, in) (out = in)
#define SPVM_IMPLEMENT_REF_FLOAT(out, in) (out = in)
#define SPVM_IMPLEMENT_REF_DOUBLE(out, in) (out = in)

static inline void SPVM_IMPLEMENT_GET_DEREF_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int8_t*)*(void**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_GET_DEREF_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int16_t*)*(void**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_GET_DEREF_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int32_t*)*(void**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_GET_DEREF_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, void** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int64_t*)*(void**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_GET_DEREF_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, void** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(float*)*(void**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_GET_DEREF_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, void** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(double*)*(void**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_SET_DEREF_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int8_t in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int8_t*)*(void**)out = in;
  }
  
}

static inline void SPVM_IMPLEMENT_SET_DEREF_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int16_t in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int16_t*)*(void**)out = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_DEREF_INT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int32_t*)*(void**)out = in;
  }
  
}

static inline void SPVM_IMPLEMENT_SET_DEREF_LONG(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int64_t in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int64_t*)*(void**)out = in;
  }
  
}

static inline void SPVM_IMPLEMENT_SET_DEREF_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, float in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(float*)*(void**)out = in;
  }
  
}

static inline void SPVM_IMPLEMENT_SET_DEREF_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, void** out, double in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(double*)*(void**)out = in;
  }
  
}

#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_BYTE(out, in, field_index) (out = *(in + field_index))
#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_SHORT(out, in, field_index) (out = *(in + field_index))
#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_INT(out, in, field_index) (out = *(in + field_index))
#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_LONG(out, in, field_index) (out = *(in + field_index))
#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_FLOAT(out, in, field_index) (out = *(in + field_index))
#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_DOUBLE(out, in, field_index) (out = *(in + field_index))

#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_BYTE(out, field_index, in) (*(out + field_index) = in)
#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_SHORT(out, field_index, in) (*(out + field_index) = in)
#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_INT(out, field_index, in) (*(out + field_index) = in)
#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_LONG(out, field_index, in) (*(out + field_index) = in)
#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_FLOAT(out, field_index, in) (*(out + field_index) = in)
#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_DOUBLE(out, field_index, in) (*(out + field_index) = in)

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, int8_t* in, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, int16_t* in, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t* in, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t* in, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, float* in, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_MOVE_MULNUM_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, double* in, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, int8_t* array, int32_t index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int8_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, int16_t* array, int32_t index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int16_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t* array, int32_t index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int32_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t* array, int32_t index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int64_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, float* array, int32_t index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((float*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, double* array, int32_t index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((double*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* array, int32_t index, int32_t fields_length, int8_t* in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int8_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* array, int32_t index, int32_t fields_length, int16_t* in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int16_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* array, int32_t index, int32_t fields_length, int32_t* in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int32_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* array, int32_t index, int32_t fields_length, int64_t* in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int64_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* array, int32_t index, int32_t fields_length, float* in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((float*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* array, int32_t index, int32_t fields_length, double* in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((double*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, int8_t* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((int8_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, int16_t* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((int16_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((int32_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((int64_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, float* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((float*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, double* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((double*)GET_DATA_ADDRESS(array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* array, int32_t index, int32_t field_index, int32_t fields_length, int8_t in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int8_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* array, int32_t index, int32_t field_index, int32_t fields_length, int16_t in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int16_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int32_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* array, int32_t index, int32_t field_index, int32_t fields_length, int64_t in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int64_t*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* array, int32_t index, int32_t field_index, int32_t fields_length, float in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((float*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* array, int32_t index, int32_t field_index, int32_t fields_length, double in, int32_t* error_id, int32_t object_data_offset, int32_t object_length_offset) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + object_length_offset), 0)) {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((double*)GET_DATA_ADDRESS(array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
      *(out + field_index) = *((int8_t*)mulnum_ref + field_index);
    }
  }
  
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
      *(out + field_index) = *((int16_t*)mulnum_ref + field_index);
    }
  }
  
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
      *(out + field_index) = *((int32_t*)mulnum_ref + field_index);
    }
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, void* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
      *(out + field_index) = *((int64_t*)mulnum_ref + field_index);
    }
  }
  
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, void* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
      *(out + field_index) = *((float*)mulnum_ref + field_index);
    }
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, void* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
      *(out + field_index) = *((double*)mulnum_ref + field_index);
    }
  }
  
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, int8_t* mulnum_ref, int32_t field_index, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((int8_t*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, int16_t* mulnum_ref, int32_t field_index, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((int16_t*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t* mulnum_ref, int32_t field_index, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((int32_t*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t* mulnum_ref, int32_t field_index, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((int64_t*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, float* mulnum_ref, int32_t field_index, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((float*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, double* mulnum_ref, int32_t field_index, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((double*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* mulnum_ref, int32_t field_index, int8_t in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *((int8_t*)mulnum_ref + field_index) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* mulnum_ref, int32_t field_index, int16_t in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *((int16_t*)mulnum_ref + field_index) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* mulnum_ref, int32_t field_index, int32_t in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *((int32_t*)mulnum_ref + field_index) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* mulnum_ref, int32_t field_index, int64_t in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *((int64_t*)mulnum_ref + field_index) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* mulnum_ref, int32_t field_index, float in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *((float*)mulnum_ref +field_index) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* mulnum_ref, int32_t field_index, double in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *((double*)mulnum_ref + field_index) = in;
  }
}

#define SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_SHORT(out, in) (out = (int16_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_INT(out, in) (out = (int32_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_LONG(out, in) (out = (int64_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_FLOAT(out, in) (out = (float)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_DOUBLE(out, in) (out = (double)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_BYTE(out, in) (out = (int8_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_INT(out, in) (out = (int32_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_LONG(out, in) (out = (int64_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_FLOAT(out, in) (out = (float)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_DOUBLE(out, in) (out = (double)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_BYTE(out, in) (out = (int8_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_SHORT(out, in) (out = (int16_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_LONG(out, in) (out = (int64_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_FLOAT(out, in) (out = (float)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_DOUBLE(out, in) (out = (double)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_BYTE(out, in) (out = (int8_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_SHORT(out, in) (out = (int16_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_INT(out, in) (out = (int32_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_FLOAT(out, in) (out = (float)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_DOUBLE(out, in) (out = (double)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_BYTE(out, in) (out = (int8_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_SHORT(out, in) (out = (int16_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_INT(out, in) (out = (int32_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_LONG(out, in) (out = (int64_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_DOUBLE(out, in) (out = (double)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_BYTE(out, in) (out = (int8_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_SHORT(out, in) (out = (int16_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_INT(out, in) (out = (int32_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_LONG(out, in) (out = (int64_t)in)
#define SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_FLOAT(out, in) (out = (float)in)

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int8_t value) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%" PRId8, value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int16_t value) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%" PRId16, value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t value) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%" PRId32, value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int64_t value) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%" PRId64, value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, float value) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%g", value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, double value) {
  
  char* tmp_buffer = env->get_stack_tmp_buffer(env, stack);
  
  snprintf(tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%g", value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void* src_string) {
  
  int64_t num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = strtoll(string, &end, 10);
    if (num > INT8_MAX) {
      num = INT8_MAX;
    }
    else if (num < INT8_MIN) {
      num = INT8_MIN;
    }
  }
  
  *out = (int8_t)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void* src_string) {
  
  int64_t num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = strtoll(string, &end, 10);
    if (num > INT16_MAX) {
      num = INT16_MAX;
    }
    else if (num < INT16_MIN) {
      num = INT16_MIN;
    }
  }
  
  *out = (int16_t)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* src_string) {
  
  int64_t num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = strtoll(string, &end, 10);
    if (num > INT32_MAX) {
      num = INT32_MAX;
    }
    else if (num < INT32_MIN) {
      num = INT32_MIN;
    }
  }
  
  *out = (int32_t)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, void* src_string) {
  
  int64_t num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = strtoll(string, &end, 10);
  }
  
  *out = (int64_t)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, void* src_string) {
  
  float num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = strtof(string, &end);
  }
  
  *out = (float)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, void* src_string) {
  
  double num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = strtod(string, &end);
  }
  
  *out = (double)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_BYTE_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* src_string) {
  
  if (src_string) {
    int32_t src_string_length = env->length(env, stack, src_string);
    const char* src_string_data = env->get_chars(env, stack, src_string);
    void* byte_array = env->new_byte_array_no_mortal(env, stack, src_string_length);
    int8_t* byte_array_data = env->get_elems_byte(env, stack, byte_array);
    memcpy(byte_array_data, src_string_data, src_string_length);
    env->assign_object(env, stack, out, byte_array);
  }
  else {
    env->assign_object(env, stack, out, NULL);
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_ARRAY_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* src_byte_array) {
  int32_t src_byte_array_length = env->length(env, stack, src_byte_array);
  int8_t* src_byte_array_data = env->get_elems_byte(env, stack, src_byte_array);
  void* string = env->new_string_no_mortal(env, stack, (const char*)src_byte_array_data, src_byte_array_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int8_t value, int32_t object_data_offset) {
  void* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS);
  void* object = env->new_object_no_mortal(env, stack, basic_type);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
  *(int8_t*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int16_t value, int32_t object_data_offset) {
  void* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS);
  void* object = env->new_object_no_mortal(env, stack, basic_type);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
  *(int16_t*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_INT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t value, int32_t object_data_offset) {
  void* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS);
  void* object = env->new_object_no_mortal(env, stack, basic_type);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
  *(int32_t*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_LONG_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int64_t value, int32_t object_data_offset) {
  void* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS);
  void* object = env->new_object_no_mortal(env, stack, basic_type);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
  *(int64_t*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, float value, int32_t object_data_offset) {
  void* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS);
  void* object = env->new_object_no_mortal(env, stack, basic_type);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
  *(float*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, double value, int32_t object_data_offset) {
  void* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS);
  void* object = env->new_object_no_mortal(env, stack, basic_type);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
  *(double*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void* object, int32_t* error_id, int32_t object_data_offset) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (env->is_type_by_name(env, stack, object, "Byte", 0)) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
      *out = *(int8_t*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void* object, int32_t* error_id, int32_t object_data_offset) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (env->is_type_by_name(env, stack, object, "Short", 0)) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
      *out = *(int16_t*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_INT_OBJECT_TO_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object, int32_t* error_id, int32_t object_data_offset) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (env->is_type_by_name(env, stack, object, "Int", 0)) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
      *out = *(int32_t*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_OBJECT_TO_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, void* object, int32_t* error_id, int32_t object_data_offset) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (env->is_type_by_name(env, stack, object, "Long", 0)) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
      *out = *(int64_t*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, void* object, int32_t* error_id, int32_t object_data_offset) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (env->is_type_by_name(env, stack, object, "Float", 0)) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
      *out = *(float*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, void* object, int32_t* error_id, int32_t object_data_offset) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (env->is_type_by_name(env, stack, object, "Double", 0)) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_data_offset);
      *out = *(double*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
  }
}

#define SPVM_IMPLEMENT_SET_STACK_BYTE(stack, stack_index, in) (*(int8_t*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_SHORT(stack, stack_index, in) (*(int16_t*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_INT(stack, stack_index, in) (*(int32_t*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_LONG(stack, stack_index, in) (*(int64_t*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_FLOAT(stack, stack_index, in) (*(float*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_DOUBLE(stack, stack_index, in) (*(double*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_OBJECT(stack, stack_index, in) (*(void**)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_REF(stack, stack_index, in) (*(void**)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_UNDEF(stack, stack_index) (*(void**)&stack[stack_index] = NULL)

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width, int8_t* in) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(int8_t*)&stack[stack_base + stack_index] = *(in + stack_index);
  }
}

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width, int16_t* in) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(int16_t*)&stack[stack_base + stack_index] = *(in + stack_index);
  }
}

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width, int32_t* in) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(int32_t*)&stack[stack_base + stack_index] = *(in + stack_index);
  }
}

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width, int64_t* in) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(int64_t*)&stack[stack_base + stack_index] = *(in + stack_index);
  }
}

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width, float* in) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(float*)&stack[stack_base + stack_index] = *(in + stack_index);
  }
}

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width, double* in) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(double*)&stack[stack_base + stack_index] = *(in + stack_index);
  }
}

#define SPVM_IMPLEMENT_GET_STACK_BYTE(out, stack, stack_index) (out = *(int8_t*)&stack[stack_index])
#define SPVM_IMPLEMENT_GET_STACK_SHORT(out, stack, stack_index) (out = *(int16_t*)&stack[stack_index])
#define SPVM_IMPLEMENT_GET_STACK_INT(out, stack, stack_index) (out = *(int32_t*)&stack[stack_index])
#define SPVM_IMPLEMENT_GET_STACK_LONG(out, stack, stack_index) (out = *(int64_t*)&stack[stack_index])
#define SPVM_IMPLEMENT_GET_STACK_FLOAT(out, stack, stack_index) (out = *(float*)&stack[stack_index])
#define SPVM_IMPLEMENT_GET_STACK_DOUBLE(out, stack, stack_index) (out = *(double*)&stack[stack_index])

static inline void SPVM_IMPLEMENT_GET_STACK_OBJECT(SPVM_ENV* env, void** out, SPVM_VALUE* stack, int32_t stack_index) {
  env->assign_object(env, stack, out, *(void**)&stack[stack_index]);
}

#define SPVM_IMPLEMENT_GET_STACK_REF(out, stack, stack_index) (out = *(void**)&stack[stack_index])

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_BYTE(SPVM_ENV* env, int8_t* out, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(out + stack_index) = *(int8_t*)&stack[(stack_base) + stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_SHORT(SPVM_ENV* env, int16_t* out, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(out + stack_index) = *(int16_t*)&stack[(stack_base) + stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_INT(SPVM_ENV* env, int32_t* out, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(out + stack_index) = *(int32_t*)&stack[(stack_base) + stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_LONG(SPVM_ENV* env, int64_t* out, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(out + stack_index) = *(int64_t*)&stack[(stack_base) + stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_FLOAT(SPVM_ENV* env, float* out, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(out + stack_index) = *(float*)&stack[(stack_base) + stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_DOUBLE(SPVM_ENV* env, double* out, SPVM_VALUE* stack, int32_t stack_base, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(out + stack_index) = *(double*)&stack[(stack_base) + stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_BYTE(SPVM_ENV* env, int8_t* out, SPVM_VALUE* stack, int32_t stack_index, int8_t default_value) {
  int32_t args_width = env->args_width(env, stack);
  if (stack_index >= args_width) {
    *out = default_value;
  }
  else {
    *out = *(int8_t*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_SHORT(SPVM_ENV* env, int16_t* out, SPVM_VALUE* stack, int32_t stack_index, int16_t default_value) {
  int32_t args_width = env->args_width(env, stack);
  if (stack_index >= args_width) {
    *out = default_value;
  }
  else {
    *out = *(int16_t*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_INT(SPVM_ENV* env, int32_t* out, SPVM_VALUE* stack, int32_t stack_index, int32_t default_value) {
  int32_t args_width = env->args_width(env, stack);
  if (stack_index >= args_width) {
    *out = default_value;
  }
  else {
    *out = *(int32_t*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_LONG(SPVM_ENV* env, int64_t* out, SPVM_VALUE* stack, int32_t stack_index, int64_t default_value) {
  int32_t args_width = env->args_width(env, stack);
  if (stack_index >= args_width) {
    *out = default_value;
  }
  else {
    *out = *(int64_t*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_FLOAT(SPVM_ENV* env, float* out, SPVM_VALUE* stack, int32_t stack_index, float default_value) {
  int32_t args_width = env->args_width(env, stack);
  if (stack_index >= args_width) {
    *out = default_value;
  }
  else {
    *out = *(float*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_DOUBLE(SPVM_ENV* env, double* out, SPVM_VALUE* stack, int32_t stack_index, double default_value) {
  int32_t args_width = env->args_width(env, stack);
  if (stack_index >= args_width) {
    *out = default_value;
  }
  else {
    *out = *(double*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_OBJECT(SPVM_ENV* env, void** out, SPVM_VALUE* stack, int32_t stack_index) {
  int32_t args_width = env->args_width(env, stack);
  if (stack_index >= args_width) {
    env->assign_object(env, stack, out, NULL);
  }
  else {
    env->assign_object(env, stack, out, *(void**)&stack[stack_index]);
  }
}

#define SPVM_IMPLEMENT_RETURN_BYTE(stack, in) (*(int8_t*)&stack[0] = in)
#define SPVM_IMPLEMENT_RETURN_SHORT(stack, in) (*(int16_t*)&stack[0] = in)
#define SPVM_IMPLEMENT_RETURN_INT(stack, in) (*(int32_t*)&stack[0] = in)
#define SPVM_IMPLEMENT_RETURN_LONG(stack, in) (*(int64_t*)&stack[0] = in)
#define SPVM_IMPLEMENT_RETURN_FLOAT(stack, in) (*(float*)&stack[0] = in)
#define SPVM_IMPLEMENT_RETURN_DOUBLE(stack, in) (*(double*)&stack[0] = in)

static inline void SPVM_IMPLEMENT_RETURN_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void* in) {
  *(void**)&stack[0] = in;
  if (in != NULL) {
    env->api->internal->inc_ref_count(env, stack, in);
  }
}

#define SPVM_IMPLEMENT_RETURN_UNDEF(stack) (*(void**)&stack[0] = NULL)

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* in, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(int8_t*)&stack[stack_index] = *(in + stack_index);
  }
}

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* in, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(int16_t*)&stack[stack_index] = *(in + stack_index);
  }
}

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* in, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(int32_t*)&stack[stack_index] = *(in + stack_index);
  }
}

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* in, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(int64_t*)&stack[stack_index] = *(in + stack_index);
  }
}

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* in, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(float*)&stack[stack_index] = *(in + stack_index);
  }
}

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* in, int32_t args_width) {
  for (int32_t stack_index = 0; stack_index < args_width; stack_index++) {
    *(double*)&stack[stack_index] = *(in + stack_index);
  }
}

#define SPVM_IMPLEMENT_CALL_CLASS_METHOD(env, stack, error_id, method, args_width) (error_id = env->call_method_no_mortal_no_check_args(env, stack, method, args_width))

#define SPVM_IMPLEMENT_CALL_INSTANCE_METHOD_STATIC(env, stack, error_id, method, args_width) (error_id = env->call_method_no_mortal_no_check_args(env, stack, method, args_width))

#define SPVM_IMPLEMENT_CALL_INSTANCE_METHOD(env, stack, error_id, method_name, args_width, decl_args_signature) (error_id = env->call_instance_method_no_mortal_less_check_args(env, stack, method_name, args_width, decl_args_signature))

#endif

// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_IMPLEMENT_H
#define SPVM_IMPLEMENT_H

// Do not include any header files.
// SPVM precompiled code will be executed in a security sandbox via JIT in the future.










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

#define GET_DATA_ADDRESS(env, stack, object) ((intptr_t)*(void**)((intptr_t)(SPVM_OBJ*)object + (intptr_t)env->api->runtime->object_data_offset))
#define GET_LENGTH(env, stack, object) (*(int32_t*)((intptr_t)(SPVM_OBJ*)object + (intptr_t)env->api->runtime->object_length_offset))
#define GET_CAPACITY(env, stack, object) (*(int32_t*)((intptr_t)(SPVM_OBJ*)object + (intptr_t)env->api->runtime->object_capacity_offset))

static inline SPVM_NATIVE_BASIC_TYPE* SPVM_IMPLEMENT_GET_BASIC_TYPE_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id) {
  
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_NATIVE_BASIC_TYPE* basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, basic_type_name);
  
  if (!basic_type) {
    SPVM_VALUE args[1];
    args[0].address = (void*)basic_type_name;
    env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_BASIC_TYPE_NOT_FOUND], args, 1);
    
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  
  return basic_type;
}

static inline SPVM_NATIVE_FIELD* SPVM_IMPLEMENT_GET_FIELD_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name, int32_t* error_id) {
  
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_NATIVE_FIELD* field = env->get_field_static(env, stack, basic_type_name, field_name);
  
  if (!field) {
    SPVM_VALUE args[2];
    args[0].address = (void*)basic_type_name;
    args[1].address = (void*)field_name;
    env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_FIELD_NOT_FOUND], args, 2);
    
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    return NULL;
  }
  
  return field;
}

static inline int32_t SPVM_IMPLEMENT_GET_FIELD_OFFSET_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name, int32_t* error_id) {
  
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_NATIVE_FIELD* field = env->get_field_static(env, stack, basic_type_name, field_name);
  
  if (!field) {
    SPVM_VALUE args[2];
    args[0].address = (void*)basic_type_name;
    args[1].address = (void*)field_name;
    env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_FIELD_NOT_FOUND], args, 2);
    
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    return -1;
  }
  
  int32_t field_offset = env->api->field->get_offset(env->runtime, field);
  
  return field_offset;
}

static inline int32_t SPVM_IMPLEMENT_GET_FIELD_EXISTS_OFFSET_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name, int32_t* error_id) {
  
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_NATIVE_FIELD* field = env->get_field_static(env, stack, basic_type_name, field_name);
  
  if (!field) {
    SPVM_VALUE args[2];
    args[0].address = (void*)basic_type_name;
    args[1].address = (void*)field_name;
    env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_FIELD_NOT_FOUND], args, 2);
    
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    return -1;
  }
  
  int32_t field_exists_offset = env->api->field->get_exists_offset(env->runtime, field);
  
  return field_exists_offset;
}

static inline int32_t SPVM_IMPLEMENT_GET_FIELD_EXISTS_BIT_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name, int32_t* error_id) {
  
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_NATIVE_FIELD* field = env->get_field_static(env, stack, basic_type_name, field_name);
  
  if (!field) {
    SPVM_VALUE args[2];
    args[0].address = (void*)basic_type_name;
    args[1].address = (void*)field_name;
    env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_FIELD_NOT_FOUND], args, 2);
    
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    return -1;
  }
  
  int32_t field_exists_bit = env->api->field->get_exists_bit(env->runtime, field);
  
  return field_exists_bit;
}

static inline SPVM_NATIVE_CLASS_VAR* SPVM_IMPLEMENT_GET_CLASS_VAR_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id) {
  
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_NATIVE_CLASS_VAR* class_var = env->get_class_var(env, stack, basic_type_name, class_var_name);
  
  if (!class_var) {
    SPVM_VALUE args[2];
    args[0].address = (void*)basic_type_name;
    args[1].address = (void*)class_var_name;
    env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_CLASS_VAR_NOT_FOUND], args, 2);
    
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  
  return class_var;
}

static inline SPVM_NATIVE_METHOD* SPVM_IMPLEMENT_GET_METHOD_BY_NAME(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t* error_id) {
  
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_NATIVE_METHOD* method = env->get_method(env, stack, basic_type_name, method_name);
  
  if (!method) {
    SPVM_VALUE args[2];
    args[0].address = (void*)basic_type_name;
    args[1].address = (void*)method_name;
    env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ERROR_METHOD_NOT_FOUND], args, 2);
    
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  
  return method;
}

static inline void SPVM_IMPLEMENT_MOVE_OBJECT_UNDEF(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** dist_address) {
  env->assign_object(env, stack, dist_address, NULL);
}

static inline void SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t exists_offset, int32_t exists_bit) {
  
  uint8_t* block = (uint8_t*)(GET_DATA_ADDRESS(env, stack, object) + exists_offset);
  
  *block |= (1 << exists_bit);
}

static inline void SPVM_IMPLEMENT_DISABLE_EXISTS_FLAG(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t exists_offset, int32_t exists_bit) {
  
  uint8_t* block = (uint8_t*)(GET_DATA_ADDRESS(env, stack, object) + exists_offset);
  
  *block &= ~(1 << exists_bit);
}

static inline int32_t SPVM_IMPLEMENT_GET_EXISTS_FLAG(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t exists_offset, int32_t exists_bit) {
  
  uint8_t* block = (uint8_t*)(GET_DATA_ADDRESS(env, stack, object) + exists_offset);
  
  int32_t flag = !!(*block & (1 << exists_bit));
  
  return flag;
}

#define SPVM_IMPLEMENT_DROP_TAG_POINTERS(address) ((SPVM_OBJ*)((intptr_t)address & ~(intptr_t)1))

#define SPVM_IMPLEMENT_ENTER_SCOPE(mortal_stack, mortal_stack_top, mortal_stack_tops, mortal_stack_tops_index) (mortal_stack_tops[mortal_stack_tops_index] = mortal_stack_top)

#define SPVM_IMPLEMENT_PUSH_MORTAL(mortal_stack_typed_var_index, mortal_stack_top, object_vars_index) (mortal_stack_typed_var_index[mortal_stack_top++] = object_vars_index)

static inline void SPVM_IMPLEMENT_LEAVE_SCOPE(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** object_vars, int32_t* mortal_stack_typed_var_index, int32_t* mortal_stack_top_ptr, int32_t* mortal_stack_tops, int32_t mortal_stack_tops_index) {
  if (*mortal_stack_top_ptr > mortal_stack_tops[mortal_stack_tops_index]) {
    env->api->internal->leave_scope_local(env, stack, (SPVM_OBJ**)object_vars, mortal_stack_typed_var_index, mortal_stack_top_ptr, mortal_stack_tops, mortal_stack_tops_index);
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

#define SPVM_IMPLEMENT_DIVIDE_FLOAT(out, in1, in2) (out = in1 / in2)
#define SPVM_IMPLEMENT_DIVIDE_DOUBLE(out, in1, in2) (out = in1 / in2)

static inline void SPVM_IMPLEMENT_DIVIDE_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t in1, int32_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = in1 / in2;
  }
}

static inline void SPVM_IMPLEMENT_DIVIDE_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t in1, int64_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = in1 / in2;
  }
}

static inline void SPVM_IMPLEMENT_DIVIDE_UNSIGNED_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t in1, int32_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = (uint32_t)in1 / (uint32_t)in2;
  }
}

static inline void SPVM_IMPLEMENT_DIVIDE_UNSIGNED_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t in1, int64_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = (uint64_t)in1 / (uint64_t)in2;
  }
}

static inline void SPVM_IMPLEMENT_MODULO_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t in1, int32_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
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
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
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
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = (uint32_t)in1 % (uint32_t)in2;
  }
}

static inline void SPVM_IMPLEMENT_MODULO_UNSIGNED_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t in1, int64_t in2, int32_t* error_id) {
  if (__builtin_expect(in2 == 0, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_DIVIDE_ZERO]);
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

static inline void SPVM_IMPLEMENT_MOVE_OBJECT_WITH_TYPE_CHECK(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_OBJ* in, SPVM_NATIVE_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension, int32_t* error_id) {
  SPVM_OBJ* object = in;
  int32_t isa = env->isa(env, stack, object, dist_basic_type, dist_type_dimension);
  if (isa) {
    env->assign_object(env, stack, out, in);
  }
  else {
    int32_t scope_id = env->enter_scope(env, stack);
    
    SPVM_OBJ* obj_src_type_name = env->get_type_name(env, stack, object);
    const char* src_type_name = env->get_chars(env, stack, obj_src_type_name);
    const char* dist_basic_type_name = env->api->basic_type->get_name(env->runtime, dist_basic_type);
    SPVM_OBJ* obj_dist_type_name = env->get_compile_type_name(env, stack, dist_basic_type_name, dist_type_dimension, 0);
    const char* dist_type_name = env->get_chars(env, stack, obj_dist_type_name);
    
    char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
    
    SPVM_VALUE args[2];
    args[0].address = (void*)src_type_name;
    args[1].address = (void*)dist_type_name;
    int32_t string_length = env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ASSIGN_NOT_SATISFY_ASSIGNMENT_REQUIREMENT], args, 2);
    
    SPVM_OBJ* exception = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    
    env->leave_scope(env, stack, scope_id);
  }
}

static inline void SPVM_IMPLEMENT_MOVE_OBJECT_CHECK_READ_ONLY_STRING(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_OBJ* in, int32_t* error_id) {
  
  SPVM_OBJ* string = in;
  if (string && env->is_read_only(env, stack, string)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ASSIGN_READ_ONLY_STRING_TO_MUTABLE_TYPE]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    env->assign_object(env, stack, out, string);
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_OBJ* in, int32_t is_mutable, int32_t* error_id) {
  
  SPVM_OBJ* object = in;
  if (!object) {
    env->assign_object(env, stack, out, object);
  }
  else if (is_mutable && env->is_read_only(env, stack, object)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ASSIGN_READ_ONLY_STRING_TO_MUTABLE_TYPE]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else if (env->is_numeric_object(env, stack, object)) {
    env->assign_object(env, stack, out, env->numeric_object_to_string_no_mortal(env, stack, object, error_id));
  }
  else if (!env->is_string(env, stack, object)) {
    int32_t scope_id = env->enter_scope(env, stack);
    
    SPVM_OBJ* obj_src_type_name = env->get_type_name(env, stack, object);
    const char* src_type_name = env->get_chars(env, stack, obj_src_type_name);
    const char* dist_basic_type_name = "string";
    SPVM_OBJ* obj_dist_type_name = env->get_compile_type_name(env, stack, dist_basic_type_name, 0, 0);
    const char* dist_type_name = env->get_chars(env, stack, obj_dist_type_name);
    
    char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
    
    SPVM_VALUE args[2];
    args[0].address = (void*)src_type_name;
    args[1].address = (void*)dist_type_name;
    int32_t string_length = env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ASSIGN_NOT_SATISFY_ASSIGNMENT_REQUIREMENT], args, 2);
    
    SPVM_OBJ* exception = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    
    env->leave_scope(env, stack, scope_id);
  }
  else {
    env->assign_object(env, stack, out, object);
  }
}

#define SPVM_IMPLEMENT_MOVE_REF(out, in) (out = (SPVM_REF*)in)
#define SPVM_IMPLEMENT_MOVE_REF_UNDEF(out) (out = (SPVM_REF*)NULL)

#define SPVM_IMPLEMENT_BIT_NOT_INT(out, in) (out = ~in)
#define SPVM_IMPLEMENT_BIT_NOT_LONG(out, in) (out = ~in)
#define SPVM_IMPLEMENT_NEGATE_INT(out, in) (out = -in)
#define SPVM_IMPLEMENT_NEGATE_LONG(out, in) (out = -in)
#define SPVM_IMPLEMENT_NEGATE_FLOAT(out, in) (out = -in)
#define SPVM_IMPLEMENT_NEGATE_DOUBLE(out, in) (out = -in)

static inline void SPVM_IMPLEMENT_STRING_CONCAT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_OBJ* in1, SPVM_OBJ* in2, int32_t* error_id) {
  SPVM_OBJ* string1 = in1;
  SPVM_OBJ* string2 = in2;
  if (string1 == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_STRING_CONCAT_LEFT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else if (string2 == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_STRING_CONCAT_RIGHT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    SPVM_OBJ* string3 = env->concat_no_mortal(env, stack, string1, string2);
    env->assign_object(env, stack, out, string3);
  }
}

#define SPVM_IMPLEMENT_CONDITION_EVALUATION_INT(out, in) (out = in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_LONG(out, in) (out = !!in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_FLOAT(out, in) (out = !!in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_DOUBLE(out, in) (out = !!in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_OBJECT(out, in) (out = !!(SPVM_OBJ*)in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_REF(out, in) (out = !!(SPVM_OBJ*)in)
#define SPVM_IMPLEMENT_CONDITION_EVALUATION_BOOL_OBJECT(env, stack, out, in) (out = !!env->get_bool_object_value(env, stack, (SPVM_OBJ*)in))

#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_INT(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_LONG(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_FLOAT(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_DOUBLE(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_OBJECT(out, in1, in2) (out = ((SPVM_OBJ*)in1 == (SPVM_OBJ*)in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_REF(out, in1, in2) (out = ((SPVM_OBJ*)in1 == (SPVM_OBJ*)in2))

#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_INT(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_LONG(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_FLOAT(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_DOUBLE(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_OBJECT(out, in1, in2) (out = ((SPVM_OBJ*)in1 != (SPVM_OBJ*)in2))
#define SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_REF(out, in1, in2) (out = ((SPVM_OBJ*)in1 != (SPVM_OBJ*)in2))

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

#define SPVM_IMPLEMENT_IS_UNDEF_OBJECT(out, in) (out = ((SPVM_OBJ*)in == NULL))
#define SPVM_IMPLEMENT_IS_UNDEF_REF(out, in) (out = ((SPVM_OBJ*)in == NULL))
#define SPVM_IMPLEMENT_IS_NOT_UNDEF_OBJECT(out, in) (out = ((SPVM_OBJ*)in != NULL))
#define SPVM_IMPLEMENT_IS_NOT_UNDEF_REF(out, in) (out = ((SPVM_OBJ*)in != NULL))

static inline void SPVM_IMPLEMENT_STRING_COMPARISON(SPVM_ENV* env, SPVM_VALUE* stack, int32_t comparison_op_id, int32_t* out, SPVM_OBJ* in1, SPVM_OBJ* in2) {
  SPVM_OBJ* object1 = in1;
  SPVM_OBJ* object2 = in2;
  
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
    int32_t length1 = GET_LENGTH(env, stack, object1);
    int32_t length2 = GET_LENGTH(env, stack, object2);
    
    const char* bytes1 = env->get_chars(env, stack, object1);
    const char* bytes2 = env->get_chars(env, stack, object2);
    
    int32_t short_string_length = length1 < length2 ? length1 : length2;
    int32_t retval = env->api->internal->c_memcmp(env, stack, bytes1, bytes2, short_string_length);
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
    default: {
      // Unexpected Error
      flag = 0;
    }
  }
  
  *out = flag;
}

#define SPVM_IMPLEMENT_STRING_COMPARISON_EQ(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_EQ, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_COMPARISON_NE(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_NE, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_COMPARISON_GT(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_GT, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_COMPARISON_GE(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_GE, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_COMPARISON_LT(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_LT, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_COMPARISON_LE(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_LE, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_COMPARISON_CMP(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON(env, stack, SPVM_IMPLEMENT_C_EXCEPTION_COMPARISON_CMP, out, in1, in2))

static inline void SPVM_IMPLEMENT_NEW_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_NATIVE_BASIC_TYPE* basic_type, int32_t* error_id) {
  SPVM_OBJ* object = env->new_object_no_mortal(env, stack, basic_type);
  if (object == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_OBJECT_FAILED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    // Push object
    env->assign_object(env, stack, out, object);
  }
}

static inline void SPVM_IMPLEMENT_NEW_OBJECT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_NATIVE_BASIC_TYPE* basic_type, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    SPVM_OBJ* object = env->new_object_array_no_mortal(env, stack, basic_type, length);
    if (object == NULL) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_MULDIM_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_NATIVE_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    SPVM_OBJ* object = env->new_muldim_array_no_mortal(env, stack, basic_type, type_dimension, length);
    if (object == NULL) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_MULNUM_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_NATIVE_BASIC_TYPE* basic_type, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    SPVM_OBJ* object = env->new_mulnum_array_no_mortal(env, stack, basic_type, length);
    if (object == NULL) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_BYTE_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    SPVM_OBJ* object = env->new_byte_array_no_mortal(env, stack, length);
    if (object == NULL) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_SHORT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    SPVM_OBJ* object = env->new_short_array_no_mortal(env, stack, length);
    if (object == NULL) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_INT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    SPVM_OBJ* object = env->new_int_array_no_mortal(env, stack, length);
    if (object == NULL) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_LONG_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    SPVM_OBJ* object = env->new_long_array_no_mortal(env, stack, length);
    if (object == NULL) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_FLOAT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    SPVM_OBJ* object = env->new_float_array_no_mortal(env, stack, length);
    if (object == NULL) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_DOUBLE_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    SPVM_OBJ* object = env->new_double_array_no_mortal(env, stack, length);
    if (object == NULL) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, object);
    }
  }
  else {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

static inline void SPVM_IMPLEMENT_NEW_STRING(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, const char* constant_string, int32_t constant_string_length, int32_t* error_id) {
  SPVM_OBJ* string = env->new_string_no_mortal(env, stack, constant_string, constant_string_length);
  if (string == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_STRING_FAILED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    env->make_read_only(env, stack, string);
    env->assign_object(env, stack, out , string);
  }
}

static inline void SPVM_IMPLEMENT_NEW_STRING_LEN(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int32_t length, int32_t* error_id) {
  if (length >= 0) {
    SPVM_OBJ* string = env->new_string_no_mortal(env, stack, NULL, length);
    if (string == NULL) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_STRING_LEN_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      env->assign_object(env, stack, out, string);
    }
  }
  else {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_NEW_STRING_LEN_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
}

#define SPVM_IMPLEMENT_IS_READ_ONLY(env, stack, out, in) (out = env->is_read_only(env, stack, in))

#define SPVM_IMPLEMENT_IS_FIXED_LENGTH(env, stack, out, in) (out = env->is_fixed_length(env, stack, in))

#define SPVM_IMPLEMENT_IS_OPTIONS(env, stack, out, in) (out = env->is_options(env, stack, in))

#define SPVM_IMPLEMENT_MAKE_READ_ONLY(env, stack, in) (env->make_read_only(env, stack, in))

#define SPVM_IMPLEMENT_MAKE_FIXED_LENGTH(env, stack, in) (env->make_fixed_length(env, stack, in))

#define SPVM_IMPLEMENT_ENABLE_OPTIONS(env, stack, in) (env->enable_options(env, stack, in))

#define SPVM_IMPLEMENT_DISABLE_OPTIONS(env, stack, in) (env->disable_options(env, stack, in))

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, SPVM_OBJ* array, int32_t index, int32_t* error_id) {
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((int8_t*)GET_DATA_ADDRESS(env, stack, array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, SPVM_OBJ* array, int32_t index, int32_t* error_id) {
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((int16_t*)GET_DATA_ADDRESS(env, stack, array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* array, int32_t index, int32_t* error_id) {
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((int32_t*)GET_DATA_ADDRESS(env, stack, array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, SPVM_OBJ* array, int32_t index, int32_t* error_id) {
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((int64_t*)GET_DATA_ADDRESS(env, stack, array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, SPVM_OBJ* array, int32_t index, int32_t* error_id) {
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((float*)GET_DATA_ADDRESS(env, stack, array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, SPVM_OBJ* array, int32_t index, int32_t* error_id) {
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      *out = ((double*)GET_DATA_ADDRESS(env, stack, array))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_OBJ* array, int32_t index, int32_t* error_id) {
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]));
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else { 
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]));
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else { 
      env->assign_object(env, stack, out, ((SPVM_OBJ**)GET_DATA_ADDRESS(env, stack, array))[index]);
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int8_t in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int8_t*)GET_DATA_ADDRESS(env, stack, array))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int16_t in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int16_t*)GET_DATA_ADDRESS(env, stack, array))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_INT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int32_t*)GET_DATA_ADDRESS(env, stack, array))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_LONG(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int64_t in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int64_t*)GET_DATA_ADDRESS(env, stack, array))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, float in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((float*)GET_DATA_ADDRESS(env, stack, array))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, double in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((double*)GET_DATA_ADDRESS(env, stack, array))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, SPVM_OBJ* in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      SPVM_OBJ** element_address = &((SPVM_OBJ**)GET_DATA_ADDRESS(env, stack, array))[index];
      env->assign_object(env, stack, element_address, in);
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, SPVM_OBJ* in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      SPVM_OBJ** element_address = &((SPVM_OBJ**)GET_DATA_ADDRESS(env, stack, array))[index];
      SPVM_OBJ* object = in;
      int32_t elem_isa = env->elem_isa(env, stack, array, object);
      if (elem_isa) {
        env->assign_object(env, stack, element_address, object);
      }
      else {
        int32_t scope_id = env->enter_scope(env, stack);
        
        SPVM_OBJ* obj_src_type_name = env->get_type_name(env, stack, object);
        const char* src_type_name = env->get_chars(env, stack, obj_src_type_name);
        SPVM_NATIVE_BASIC_TYPE* dist_basic_type = env->get_object_basic_type(env, stack, array);
        const char* dist_basic_type_name = env->api->basic_type->get_name(env->runtime, dist_basic_type);
        int32_t dist_type_dimension = env->get_object_type_dimension(env, stack, array) - 1;
        SPVM_OBJ* obj_dist_type_name = env->get_compile_type_name(env, stack, dist_basic_type_name, dist_type_dimension, 0);
        const char* dist_type_name = env->get_chars(env, stack, obj_dist_type_name);
        
        char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
        
        SPVM_VALUE args[2];
        args[0].address = (void*)src_type_name;
        args[1].address = (void*)dist_type_name;
        int32_t string_length = env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ASSIGN_NOT_SATISFY_ASSIGNMENT_REQUIREMENT], args, 2);
        
        SPVM_OBJ* exception = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
        env->set_exception(env, stack, exception);
        *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
        
        env->leave_scope(env, stack, scope_id);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_UNDEF(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      SPVM_OBJ** object_address = &((SPVM_OBJ**)GET_DATA_ADDRESS(env, stack, array))[index];
      env->assign_object(env, stack, object_address, NULL);
    }
  }
}

static inline void SPVM_IMPLEMENT_CALLER(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int32_t level, int32_t* error_id) {
  
  *out = env->caller(env, stack, level, error_id);
  if (*error_id) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)));
    env->set_exception(env, stack, exception);
  }
}

static inline void SPVM_IMPLEMENT_ARRAY_LENGTH(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* array, int32_t* error_id) {
  if (array == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = GET_LENGTH(env, stack, array);
  }
}

static inline void SPVM_IMPLEMENT_STRING_LENGTH(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* string) {
  if (string == NULL) {
    *out = 0;
  }
  else {
    *out = GET_LENGTH(env, stack, string);
  }
}

static inline void SPVM_IMPLEMENT_CAPACITY(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* object, int32_t* error_id) {
  if (object == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = GET_CAPACITY(env, stack, object);
  }
}

static inline void SPVM_IMPLEMENT_SET_LENGTH(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t length, int32_t* error_id) {
  if (object == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *error_id = env->set_length(env, stack, object, length);
  }
}

static inline void SPVM_IMPLEMENT_SET_CAPACITY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t capacity, int32_t* error_id) {
  if (object == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *error_id = env->set_capacity(env, stack, object, capacity);
  }
}

static inline void SPVM_IMPLEMENT_GET_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, SPVM_OBJ* object, int32_t field_offset, int32_t* error_id) {
  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int8_t*)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
  }
}

static inline void SPVM_IMPLEMENT_GET_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, SPVM_OBJ* object, int32_t field_offset, int32_t* error_id) {
  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int16_t*)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* object, int32_t field_offset, int32_t* error_id) {
  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int32_t*)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, SPVM_OBJ* object, int32_t field_offset, int32_t* error_id) {
  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int64_t*)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, SPVM_OBJ* object, int32_t field_offset, int32_t* error_id) {
  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(float*)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, SPVM_OBJ* object, int32_t field_offset, int32_t* error_id) {
  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(double*)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
  }
}

static inline void SPVM_IMPLEMENT_GET_FIELD_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_OBJ* object, int32_t field_offset, int32_t* error_id) {  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    SPVM_OBJ** ref = (SPVM_OBJ**)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
    SPVM_OBJ* field_object = SPVM_IMPLEMENT_DROP_TAG_POINTERS(*ref);
    env->assign_object(env, stack, out, field_object);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t field_offset, int8_t in, int32_t* error_id, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int8_t*)(GET_DATA_ADDRESS(env, stack, object) + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t field_offset, int16_t in, int32_t* error_id, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int16_t*)(GET_DATA_ADDRESS(env, stack, object) + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t field_offset, int32_t in, int32_t* error_id, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int32_t*)(GET_DATA_ADDRESS(env, stack, object) + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t field_offset, int64_t in, int32_t* error_id, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int64_t*)(GET_DATA_ADDRESS(env, stack, object) + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t field_offset, float in, int32_t* error_id, int32_t exists_offset, int32_t exists_bit) {
  
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(float*)(GET_DATA_ADDRESS(env, stack, object) + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t field_offset, double in, int32_t* error_id, int32_t exists_offset, int32_t exists_bit) {
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(double*)(GET_DATA_ADDRESS(env, stack, object) + field_offset) = in;
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t field_offset, SPVM_OBJ* in, int32_t* error_id, int32_t exists_offset, int32_t exists_bit) {
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    SPVM_OBJ** ref = (SPVM_OBJ**)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
    env->assign_object(env, stack, ref, in);
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_UNDEF(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t field_offset, int32_t* error_id, int32_t exists_offset, int32_t exists_bit) {
  if (__builtin_expect(object == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    SPVM_OBJ** ref = (SPVM_OBJ**)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
    env->assign_object(env, stack, ref, NULL);
    SPVM_IMPLEMENT_ENABLE_EXISTS_FLAG(env, stack, object, exists_offset, exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_WEAKEN_FIELD(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t field_offset, int32_t* error_id) {
  if (object == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    SPVM_OBJ** ref = (SPVM_OBJ**)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
    int32_t status = env->weaken(env, stack, (SPVM_OBJ**)ref);
    if (status != 0) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_WEAKEN_BACK_REFERENCE_ALLOCATION_FAILED]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
  }
}

static inline void SPVM_IMPLEMENT_UNWEAKEN_FIELD(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, int32_t field_offset, int32_t* error_id) {
  if (object == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    SPVM_OBJ** ref = (SPVM_OBJ**)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
    env->unweaken(env, stack, (SPVM_OBJ**)ref);
  }
}

static inline void SPVM_IMPLEMENT_ISWEAK_FIELD(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* object, int32_t field_offset, int32_t* error_id) {
  if (object == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    SPVM_OBJ** ref = (SPVM_OBJ**)(GET_DATA_ADDRESS(env, stack, object) + field_offset);
    *out = env->isweak(env, stack, (SPVM_OBJ**)ref);
  }
}

static inline void SPVM_IMPLEMENT_EXISTS(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* object, int32_t field_exists_offset, int32_t field_exists_bit, int32_t* error_id) {
  if (object == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = SPVM_IMPLEMENT_GET_EXISTS_FLAG(env, stack, object, field_exists_offset, field_exists_bit);
  }
}

static inline void SPVM_IMPLEMENT_DELETE(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* object, SPVM_NATIVE_FIELD* field, int32_t* error_id) {
  if (object == NULL) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
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

static inline void SPVM_IMPLEMENT_ISA(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* object, SPVM_NATIVE_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension) {
  if (object) {
    *out = env->isa(env, stack, object, dist_basic_type, dist_type_dimension);
  }
  else {
    *out = 0;
  }
}

static inline void SPVM_IMPLEMENT_ISA_ERROR(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_NATIVE_BASIC_TYPE* src_basic_type, SPVM_NATIVE_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension) {
  *out = env->api->type->can_assign(env->runtime, dist_basic_type, dist_type_dimension, 0, src_basic_type, 0, 0);
}

static inline void SPVM_IMPLEMENT_IS_TYPE(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* object, SPVM_NATIVE_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension) {
  if (object) {
    *out = env->is_type(env, stack, object, dist_basic_type, dist_type_dimension);
  }
  else {
    *out = 0;
  }
}

static inline void SPVM_IMPLEMENT_IS_ERROR(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_NATIVE_BASIC_TYPE* src_basic_type, SPVM_NATIVE_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension) {
  *out = (dist_basic_type == src_basic_type && dist_type_dimension == 0);
}

#define SPVM_IMPLEMENT_CAN(env, stack, out, object, method_name) (out = (env->get_instance_method(env, stack, object, method_name) != NULL))

static inline void SPVM_IMPLEMENT_PRINT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* string, int32_t is_stderr) {
  if (is_stderr) {
    env->print_stderr(env, stack, string);
  }
  else {
    env->print(env, stack, string);
  }
}

static inline void SPVM_IMPLEMENT_SAY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* string, int32_t is_stderr) {
  if (is_stderr) {
    env->say_stderr(env, stack, string);
  }
  else {
    env->say(env, stack, string);
  }
}

static inline void SPVM_IMPLEMENT_WARN(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* string, const char* func_name, const char* file, int32_t line) {
  env->warn(env, stack, string, func_name, file, line);
}

#define SPVM_IMPLEMENT_CLEAR_EVAL_ERROR_ID(eval_error_id) (eval_error_id = 0)
#define SPVM_IMPLEMENT_GET_EVAL_ERROR_ID(out, eval_error_id) (out = eval_error_id)
#define SPVM_IMPLEMENT_SET_ERROR_ID(error_id, die_error_id) (error_id = die_error_id)
#define SPVM_IMPLEMENT_SET_EVAL_ERROR_ID(eval_error_id, die_error_id) (eval_error_id = die_error_id)
#define SPVM_IMPLEMENT_ARGS_WIDTH(env, stack, out) (out = env->args_width(env, stack))
#define SPVM_IMPLEMENT_GET_BASIC_TYPE_ID(env, stack, out, basic_type_arg) ((out) = (env)->api->basic_type->get_id((env)->runtime, (basic_type_arg)))

static inline void SPVM_IMPLEMENT_TYPE_NAME(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_OBJ* object) {
  if (object == NULL) {
    *out = NULL;
  }
  else {
    SPVM_OBJ* type_name = env->get_type_name_no_mortal(env, stack, object);
    env->assign_object(env, stack, out, type_name);
  }
}

static inline void SPVM_IMPLEMENT_DUMP(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_OBJ* object) {
  SPVM_OBJ* dump = env->dump_no_mortal(env, stack, object);
  env->assign_object(env, stack, out, dump);
}

static inline void SPVM_IMPLEMENT_COPY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_OBJ* object, int32_t* error_id) {
  SPVM_OBJ* object_copy = env->copy_no_mortal(env, stack, object);
  env->assign_object(env, stack, out, object_copy);
}

static inline void SPVM_IMPLEMENT_GET_ADDRESS(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, void* address) {
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_VALUE args[1];
  args[0].address = address;
  int32_t string_length = env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%p", args, 1);
  
  SPVM_OBJ* object_address = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, object_address);
}

#define SPVM_IMPLEMENT_REF_BYTE(out, in) (out = (void*)(in))
#define SPVM_IMPLEMENT_REF_SHORT(out, in) (out = (void*)(in))
#define SPVM_IMPLEMENT_REF_INT(out, in) (out = (void*)(in))
#define SPVM_IMPLEMENT_REF_LONG(out, in) (out = (void*)(in))
#define SPVM_IMPLEMENT_REF_FLOAT(out, in) (out = (void*)(in))
#define SPVM_IMPLEMENT_REF_DOUBLE(out, in) (out = (void*)(in))

static inline void SPVM_IMPLEMENT_GET_DEREF_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, int8_t** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int8_t*)*(int8_t**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_GET_DEREF_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, int16_t** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int16_t*)*(int16_t**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_GET_DEREF_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int32_t*)*(int32_t**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_GET_DEREF_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(int64_t*)*(int64_t**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_GET_DEREF_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, float** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(float*)*(float**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_GET_DEREF_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, double** in, int32_t* error_id) {
  
  if (__builtin_expect(*in == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *(double*)*(double**)in;
  }
  
}

static inline void SPVM_IMPLEMENT_SET_DEREF_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t** out, int8_t in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int8_t*)*(int8_t**)out = in;
  }
  
}

static inline void SPVM_IMPLEMENT_SET_DEREF_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t** out, int16_t in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int16_t*)*(int16_t**)out = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_DEREF_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t** out, int32_t in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int32_t*)*(int32_t**)out = in;
  }
  
}

static inline void SPVM_IMPLEMENT_SET_DEREF_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t** out, int64_t in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(int64_t*)*(int64_t**)out = in;
  }
  
}

static inline void SPVM_IMPLEMENT_SET_DEREF_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float** out, float in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(float*)*(float**)out = in;
  }
  
}

static inline void SPVM_IMPLEMENT_SET_DEREF_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double** out, double in, int32_t* error_id) {
  
  if (__builtin_expect(*out == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *(double*)*(double**)out = in;
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

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, SPVM_OBJ* array, int32_t index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int8_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, SPVM_OBJ* array, int32_t index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int16_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* array, int32_t index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int32_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, SPVM_OBJ* array, int32_t index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int64_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, SPVM_OBJ* array, int32_t index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((float*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, SPVM_OBJ* array, int32_t index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((double*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t fields_length, int8_t* in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int8_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t fields_length, int16_t* in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int16_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_INT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t fields_length, int32_t* in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int32_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_LONG(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t fields_length, int64_t* in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int64_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t fields_length, float* in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((float*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t fields_length, double* in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((double*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((int8_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((int16_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((int32_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((int64_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((float*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error_id) {
  if (__builtin_expect(array == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      *out = ((double*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, int8_t in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int8_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, int16_t in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int16_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int32_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, int64_t in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((int64_t*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, float in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((float*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* array, int32_t index, int32_t field_index, int32_t fields_length, double in, int32_t* error_id) {
  if (__builtin_expect(!array, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (__builtin_expect(index < 0, 0)) {
      index += GET_LENGTH(env, stack, array);
    }
    if (__builtin_expect(index < 0 || index >= GET_LENGTH(env, stack, array), 0)) {
      SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_ELEMENT_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      ((double*)GET_DATA_ADDRESS(env, stack, array))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, int8_t* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
      *(out + field_index) = *((int8_t*)mulnum_ref + field_index);
    }
  }
  
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, int16_t* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
      *(out + field_index) = *((int16_t*)mulnum_ref + field_index);
    }
  }
  
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
      *(out + field_index) = *((int32_t*)mulnum_ref + field_index);
    }
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
      *(out + field_index) = *((int64_t*)mulnum_ref + field_index);
    }
  }
  
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, float* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
      *(out + field_index) = *((float*)mulnum_ref + field_index);
    }
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, double* mulnum_ref, int32_t fields_length, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
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
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((int8_t*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, int16_t* mulnum_ref, int32_t field_index, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((int16_t*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t* mulnum_ref, int32_t field_index, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((int32_t*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t* mulnum_ref, int32_t field_index, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((int64_t*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, float* mulnum_ref, int32_t field_index, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((float*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, double* mulnum_ref, int32_t field_index, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *out = *((double*)mulnum_ref + field_index);
  }
  
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* mulnum_ref, int32_t field_index, int8_t in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *((int8_t*)mulnum_ref + field_index) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* mulnum_ref, int32_t field_index, int16_t in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *((int16_t*)mulnum_ref + field_index) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* mulnum_ref, int32_t field_index, int32_t in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *((int32_t*)mulnum_ref + field_index) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* mulnum_ref, int32_t field_index, int64_t in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *((int64_t*)mulnum_ref + field_index) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* mulnum_ref, int32_t field_index, float in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    *((float*)mulnum_ref +field_index) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* mulnum_ref, int32_t field_index, double in, int32_t* error_id) {
  
  if (__builtin_expect(mulnum_ref == NULL, 0)) {
    SPVM_OBJ* exception = env->new_string_nolen_no_mortal(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_EXCEPTION_REF_UNDEFINED]);
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

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int8_t value) {
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_VALUE args[1];
  args[0].ival = (int32_t)value;
  int32_t string_length = env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%" PRId8, args, 1);
  
  SPVM_OBJ* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int16_t value) {
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_VALUE args[1];
  args[0].ival = (int32_t)value;
  int32_t string_length = env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%" PRId16, args, 1);
  
  SPVM_OBJ* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int32_t value) {
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_VALUE args[1];
  args[0].ival = value;
  int32_t string_length = env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%" PRId32, args, 1);
  
  SPVM_OBJ* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int64_t value) {
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_VALUE args[1];
  args[0].lval = value;
  int32_t string_length = env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%" PRId64, args, 1);
  
  SPVM_OBJ* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, float value) {
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_VALUE args[1];
  args[0].dval = (double)value;
  int32_t string_length = env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%g", args, 1);
  
  SPVM_OBJ* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, double value) {
  char* tmp_buffer = env->api->internal->get_stack_tmp_buffer(env, stack);
  
  SPVM_VALUE args[1];
  args[0].dval = value;
  int32_t string_length = env->api->internal->c_snprintf_len(env, stack, tmp_buffer, SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE, "%g", args, 1);
  
  SPVM_OBJ* string = env->new_string_no_mortal(env, stack, tmp_buffer, string_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, SPVM_OBJ* src_string) {
  
  int64_t num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = env->api->internal->c_strtoll(env, stack, string, &end, 10);
    if (num > INT8_MAX) {
      num = INT8_MAX;
    }
    else if (num < INT8_MIN) {
      num = INT8_MIN;
    }
  }
  
  *out = (int8_t)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, SPVM_OBJ* src_string) {
  
  int64_t num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = env->api->internal->c_strtoll(env, stack, string, &end, 10);
    if (num > INT16_MAX) {
      num = INT16_MAX;
    }
    else if (num < INT16_MIN) {
      num = INT16_MIN;
    }
  }
  
  *out = (int16_t)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* src_string) {
  
  int64_t num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = env->api->internal->c_strtoll(env, stack, string, &end, 10);
    if (num > INT32_MAX) {
      num = INT32_MAX;
    }
    else if (num < INT32_MIN) {
      num = INT32_MIN;
    }
  }
  
  *out = (int32_t)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, SPVM_OBJ* src_string) {
  
  int64_t num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = env->api->internal->c_strtoll(env, stack, string, &end, 10);
  }
  
  *out = (int64_t)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, SPVM_OBJ* src_string) {
  
  float num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = env->api->internal->c_strtof(env, stack, string, &end);
  }
  
  *out = (float)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, SPVM_OBJ* src_string) {
  
  double num = 0;
  if (src_string) {
    const char* string = env->get_chars(env, stack, src_string);
    
    char *end;
    num = env->api->internal->c_strtod(env, stack, string, &end);
  }
  
  *out = (double)num;
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_BYTE_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_OBJ* src_string) {
  
  if (src_string) {
    int32_t src_string_length = env->length(env, stack, src_string);
    const char* src_string_data = env->get_chars(env, stack, src_string);
    SPVM_OBJ* byte_array = env->new_byte_array_no_mortal(env, stack, src_string_length);
    int8_t* byte_array_data = env->get_elems_byte(env, stack, byte_array);
    env->api->internal->c_memcpy(env, stack, byte_array_data, src_string_data, src_string_length);
    env->assign_object(env, stack, out, byte_array);
  }
  else {
    env->assign_object(env, stack, out, NULL);
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_ARRAY_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, SPVM_OBJ* src_byte_array) {
  int32_t src_byte_array_length = env->length(env, stack, src_byte_array);
  int8_t* src_byte_array_data = env->get_elems_byte(env, stack, src_byte_array);
  SPVM_OBJ* string = env->new_string_no_mortal(env, stack, (const char*)src_byte_array_data, src_byte_array_length);
  env->assign_object(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int8_t value) {
  SPVM_NATIVE_BASIC_TYPE* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS);
  SPVM_OBJ* object = env->new_object_no_mortal(env, stack, basic_type);
  int8_t** fields = (int8_t**)(GET_DATA_ADDRESS(env, stack, object));
  *(int8_t*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int16_t value) {
  SPVM_NATIVE_BASIC_TYPE* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS);
  SPVM_OBJ* object = env->new_object_no_mortal(env, stack, basic_type);
  int16_t** fields = (int16_t**)(GET_DATA_ADDRESS(env, stack, object));
  *(int16_t*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_INT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int32_t value) {
  SPVM_NATIVE_BASIC_TYPE* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS);
  SPVM_OBJ* object = env->new_object_no_mortal(env, stack, basic_type);
  int32_t** fields = (int32_t**)(GET_DATA_ADDRESS(env, stack, object));
  *(int32_t*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_LONG_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, int64_t value) {
  SPVM_NATIVE_BASIC_TYPE* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS);
  SPVM_OBJ* object = env->new_object_no_mortal(env, stack, basic_type);
  int64_t** fields = (int64_t**)(GET_DATA_ADDRESS(env, stack, object));
  *(int64_t*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, float value) {
  SPVM_NATIVE_BASIC_TYPE* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS);
  SPVM_OBJ* object = env->new_object_no_mortal(env, stack, basic_type);
  float** fields = (float**)(GET_DATA_ADDRESS(env, stack, object));
  *(float*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ** out, double value) {
  SPVM_NATIVE_BASIC_TYPE* basic_type = env->api->runtime->get_basic_type_by_id(env->runtime, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS);
  SPVM_OBJ* object = env->new_object_no_mortal(env, stack, basic_type);
  double** fields = (double**)(GET_DATA_ADDRESS(env, stack, object));
  *(double*)&fields[0] = value;
  env->assign_object(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, SPVM_OBJ* object, int32_t* error_id) {
  
  *out = env->numeric_object_to_byte(env, stack, object, error_id);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, SPVM_OBJ* object, int32_t* error_id) {
  
  *out = env->numeric_object_to_short(env, stack, object, error_id);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, SPVM_OBJ* object, int32_t* error_id) {
  
  *out = env->numeric_object_to_int(env, stack, object, error_id);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, SPVM_OBJ* object, int32_t* error_id) {
  
  *out = env->numeric_object_to_long(env, stack, object, error_id);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, SPVM_OBJ* object, int32_t* error_id) {
  
  *out = env->numeric_object_to_float(env, stack, object, error_id);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, SPVM_OBJ* object, int32_t* error_id) {
  
  *out = env->numeric_object_to_double(env, stack, object, error_id);
}

#define SPVM_IMPLEMENT_SET_STACK_BYTE(stack, stack_index, in) (*(int8_t*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_SHORT(stack, stack_index, in) (*(int16_t*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_INT(stack, stack_index, in) (*(int32_t*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_LONG(stack, stack_index, in) (*(int64_t*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_FLOAT(stack, stack_index, in) (*(float*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_DOUBLE(stack, stack_index, in) (*(double*)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_OBJECT(stack, stack_index, in) (*(SPVM_OBJ**)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_REF(stack, stack_index, in) (*(SPVM_REF**)&stack[stack_index] = in)
#define SPVM_IMPLEMENT_SET_STACK_UNDEF(stack, stack_index) (*(SPVM_OBJ**)&stack[stack_index] = NULL)

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

static inline void SPVM_IMPLEMENT_GET_STACK_OBJECT(SPVM_ENV* env, SPVM_OBJ** out, SPVM_VALUE* stack, int32_t stack_index) {
  env->assign_object(env, stack, out, *(SPVM_OBJ**)&stack[stack_index]);
}

#define SPVM_IMPLEMENT_GET_STACK_REF(out, stack, stack_index) (out = *(SPVM_REF**)&stack[stack_index])

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

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_OBJECT(SPVM_ENV* env, SPVM_OBJ** out, SPVM_VALUE* stack, int32_t stack_index) {
  int32_t args_width = env->args_width(env, stack);
  if (stack_index >= args_width) {
    env->assign_object(env, stack, out, NULL);
  }
  else {
    env->assign_object(env, stack, out, *(SPVM_OBJ**)&stack[stack_index]);
  }
}

#define SPVM_IMPLEMENT_RETURN_BYTE(stack, in) (*(int8_t*)&stack[0] = in)
#define SPVM_IMPLEMENT_RETURN_SHORT(stack, in) (*(int16_t*)&stack[0] = in)
#define SPVM_IMPLEMENT_RETURN_INT(stack, in) (*(int32_t*)&stack[0] = in)
#define SPVM_IMPLEMENT_RETURN_LONG(stack, in) (*(int64_t*)&stack[0] = in)
#define SPVM_IMPLEMENT_RETURN_FLOAT(stack, in) (*(float*)&stack[0] = in)
#define SPVM_IMPLEMENT_RETURN_DOUBLE(stack, in) (*(double*)&stack[0] = in)

static inline void SPVM_IMPLEMENT_RETURN_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJ* in) {
  *(SPVM_OBJ**)&stack[0] = in;
  if (in != NULL) {
    env->api->internal->inc_ref_count(env, stack, in);
  }
}

#define SPVM_IMPLEMENT_RETURN_UNDEF(stack) (*(SPVM_OBJ**)&stack[0] = NULL)

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

#define SPVM_IMPLEMENT_CALL_CLASS_METHOD(env, stack, error_id, method, args_width, func_name, file, line) (error_id = env->call_method_no_mortal_no_check_args(env, stack, method, args_width, func_name, file, line))

#define SPVM_IMPLEMENT_CALL_INSTANCE_METHOD_STATIC(env, stack, error_id, method, args_width, func_name, file, line) (error_id = env->call_method_no_mortal_no_check_args(env, stack, method, args_width, func_name, file, line))

#define SPVM_IMPLEMENT_CALL_INSTANCE_METHOD(env, stack, error_id, method_name, args_width, decl_args_signature, func_name, file, line) (error_id = env->call_instance_method_no_mortal_less_check_args(env, stack, method_name, args_width, decl_args_signature, func_name, file, line))

#endif

#ifndef SPVM_IMPLEMENT_H
#define SPVM_IMPLEMENT_H

#include <inttypes.h>

enum {
  SPVM_IMPLEMENT_C_STRING_CALL_STACK_ALLOCATION_FAILED,
  SPVM_IMPLEMENT_C_STRING_VALUE_ASSIGN_NON_ASSIGNABLE_TYPE,
  SPVM_IMPLEMENT_C_STRING_ASSIGN_READ_ONLY_STRING_TO_MUTABLE_TYPE,
  SPVM_IMPLEMENT_C_STRING_DIVIDE_ZERO,
  SPVM_IMPLEMENT_C_STRING_CONCAT_LEFT_UNDEFINED,
  SPVM_IMPLEMENT_C_STRING_CONCAT_RIGHT_UNDEFINED,
  SPVM_IMPLEMENT_C_STRING_NEW_OBJECT_FAILED,
  SPVM_IMPLEMENT_C_STRING_NEW_ARRAY_FAILED,
  SPVM_IMPLEMENT_C_STRING_ARRRAY_LENGTH_SMALL,
  SPVM_IMPLEMENT_C_STRING_NEW_STRING_FAILED,
  SPVM_IMPLEMENT_C_STRING_STRING_LENGTH_SMALL,
  SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED,
  SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE,
  SPVM_IMPLEMENT_C_STRING_ELEMENT_ASSIGN_NON_ASSIGNABLE_TYPE,
  SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED,
  SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_FROM_UNDEF,
  SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE,
  SPVM_IMPLEMENT_C_STRING_WEAKEN_BACK_REFERENCE_ALLOCATION_FAILED,
  SPVM_IMPLEMENT_C_STRING_COPY_OPERAND_INVALID,
  SPVM_IMPLEMENT_C_STRING_ERROR_CODE_TOO_SMALL,
  SPVM_IMPLEMENT_C_STRING_WARN_AT,
  SPVM_IMPLEMENT_C_STRING_WARN_UNDEF,
  SPVM_IMPLEMENT_C_STRING_CALL_INSTANCE_METHOD_NOT_FOUND,
  SPVM_IMPLEMENT_C_STRING_ERROR_BASIC_TYPE_NOT_FOUND,
  SPVM_IMPLEMENT_C_STRING_ERROR_FIELD_NOT_FOUND,
  SPVM_IMPLEMENT_C_STRING_ERROR_CLASS_VAR_NOT_FOUND,
  SPVM_IMPLEMENT_C_STRING_ERROR_CLASS_NOT_FOUND,
  SPVM_IMPLEMENT_C_STRING_ERROR_METHOD_NOT_FOUND,
};

static const char* SPVM_IMPLEMENT_STRING_LITERALS[] = {
  "The memory allocation for the call stack failed",
  "The value can't be cast to the non-assignable type",
  "The read-only string can't be cast to the mutable string type",
  "Integral type values can't be divided by 0",
  "The left operand of the \".\" operator must be defined",
  "The right operand of the \".\" operator must be defined",
  "The object creating failed",
  "The array creating failed",
  "The length of the array must be greater than or equal to 0",
  "The string creating failed",
  "The length of the string must be greater than or equal to 0",
  "The array must be defined",
  "The index of the array access must be greater than or equal to 0 and less than the length of the array",
  "The element can't be assigned to the non-assignable type",
  "The invocant of the field access must be defined",
  "The unboxing conversion can't be performed on the undefined value",
  "The source of the unboxing conversion must be the corresponding numeric object type",
  "The memory allocation for the weaken back reference failed",
  "The operand of the copy operator must be a string type, a numeric type, or a multi numeric type",
  "The error code must be greater than or equal to 1",
  " at %s%s%s line %d\n",
  "Warning: something's wrong at %s%s%s line %d\n",
  "The implementation of the \"%s\" instance method defined in \"%s\" is not found",
  "The %s basic type is not found",
  "The %s field is not found",
  "The %s class variable in the %s class is not found",
  "The %s class is not found",
  "The %s method in the %s class is not found",
};

enum {
  SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_EQ,
  SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_NE,
  SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GT,
  SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GE,
  SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LT,
  SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LE,
  SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_CMP,
};

static inline int32_t SPVM_IMPLEMENT_GET_BASIC_TYPE_ID(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, char* message, int32_t* error) {

  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);

  if (basic_type_id < 0) {
    snprintf(message, 256, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ERROR_BASIC_TYPE_NOT_FOUND], basic_type_name);
    void* exception = env->new_string_nolen_raw(env, stack, message);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  
  return basic_type_id;
}

static inline int32_t SPVM_IMPLEMENT_GET_CLASS_ID_RET(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, char* message, int32_t* error) {

  int32_t class_id = env->get_class_id(env, stack, class_name);

  if (class_id < 0) {
    snprintf(message, 256, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ERROR_CLASS_NOT_FOUND], class_name);
    void* exception = env->new_string_nolen_raw(env, stack, message);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  
  return class_id;
}

static inline int32_t SPVM_IMPLEMENT_GET_FIELD_ID_STATIC(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* field_name, char* message, int32_t* error) {

  int32_t field_id = env->get_field_id_static(env, stack, class_name, field_name);
  
  if (field_id < 0) {
    snprintf(message, 256, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ERROR_FIELD_NOT_FOUND], field_name);
    void* exception = env->new_string_nolen_raw(env, stack, message);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  
  return field_id;
}

static inline int32_t SPVM_IMPLEMENT_GET_CLASS_VAR_ID(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, char* message, int32_t* error) {
  
  int32_t class_var_id = env->get_class_var_id(env, stack, class_name, class_var_name);
  
  if (class_var_id < 0) {
    snprintf(message, 256, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ERROR_CLASS_VAR_NOT_FOUND], class_var_name);
    void* exception = env->new_string_nolen_raw(env, stack, message);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  
  return class_var_id;
}

static inline int32_t SPVM_IMPLEMENT_GET_METHOD_ID(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name, char* message, int32_t* error) {

  int32_t method_id = env->get_method_id(env, stack, class_name, method_name);
  
  if (method_id < 0) {
    snprintf(message, 256, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ERROR_METHOD_NOT_FOUND], method_name);
    void* exception = env->new_string_nolen_raw(env, stack, message);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  
  return method_id;
}

//  "& ~(intptr_t)1" means dropping weaken flag
#define SPVM_IMPLEMENT_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, object) ((void*)((intptr_t)object & ~(intptr_t)1))

#define SPVM_IMPLEMENT_GET_REF_COUNT(env, stack, object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset)))

#define SPVM_IMPLEMENT_INC_REF_COUNT_ONLY(env, stack, object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))++)

static inline void SPVM_IMPLEMENT_INC_REF_COUNT(SPVM_ENV* env, SPVM_VALUE* stack, void* object) {
  if (object != NULL) {
    SPVM_IMPLEMENT_INC_REF_COUNT_ONLY(env, stack, object);
  }
}

#define SPVM_IMPLEMENT_DEC_REF_COUNT_ONLY(env, stack, object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))--)

static inline void SPVM_IMPLEMENT_DEC_REF_COUNT(SPVM_ENV* env, SPVM_VALUE* stack, void* object) {
  if (object != NULL) {
    if (SPVM_IMPLEMENT_GET_REF_COUNT(env, stack, object) > 1) { SPVM_IMPLEMENT_DEC_REF_COUNT_ONLY(env, stack, object); }
    else { env->dec_ref_count(env, stack, object); }
  }
}

#define SPVM_IMPLEMENT_ISWEAK(dist_address) (((intptr_t)*(void**)dist_address) & 1)

static inline void SPVM_IMPLEMENT_OBJECT_ASSIGN(SPVM_ENV* env, SPVM_VALUE* stack, void** dist_address, void* src_object) {
  void* tmp_object = SPVM_IMPLEMENT_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, src_object);
  if (tmp_object != NULL) {
    SPVM_IMPLEMENT_INC_REF_COUNT_ONLY(env, stack, tmp_object);
  }
  if (*(void**)(dist_address) != NULL) {
    if (__builtin_expect(SPVM_IMPLEMENT_ISWEAK(dist_address), 0)) { env->unweaken(env, stack, (void**)dist_address); }
    if (SPVM_IMPLEMENT_GET_REF_COUNT(env, stack, *(void**)(dist_address)) > 1) { SPVM_IMPLEMENT_DEC_REF_COUNT_ONLY(env, stack, *(void**)(dist_address)); }
    else { env->dec_ref_count(env, stack, *(void**)(dist_address)); }\
  }
  *(void**)(dist_address) = tmp_object;
}

static inline void SPVM_IMPLEMENT_LEAVE_SCOPE(SPVM_ENV* env, SPVM_VALUE* stack, void** object_vars, int32_t* mortal_stack, int32_t* mortal_stack_top_ptr, int32_t original_mortal_stack_top) {
  for (int32_t mortal_stack_index = original_mortal_stack_top; mortal_stack_index < *mortal_stack_top_ptr; mortal_stack_index++) {
    int32_t var_index = mortal_stack[mortal_stack_index];
    void** object_address = (void**)&object_vars[var_index];
    if (*object_address != NULL) {
      if (SPVM_IMPLEMENT_GET_REF_COUNT(env, stack, *object_address) > 1) { SPVM_IMPLEMENT_DEC_REF_COUNT_ONLY(env, stack, *object_address); }
      else { env->dec_ref_count(env, stack, *object_address); }
      *object_address = NULL;
    }
  }
  *mortal_stack_top_ptr = original_mortal_stack_top;
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

static inline void SPVM_IMPLEMENT_DIVIDE_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t in1, int32_t in2, int32_t* error) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = in1 / in2;
  }
}

static inline void SPVM_IMPLEMENT_DIVIDE_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t in1, int64_t in2, int32_t* error) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = in1 / in2;
  }
}

#define SPVM_IMPLEMENT_DIVIDE_FLOAT(out, in1, in2) (out = in1 / in2)

#define SPVM_IMPLEMENT_DIVIDE_DOUBLE(out, in1, in2) (out = in1 / in2)

static inline void SPVM_IMPLEMENT_DIVIDE_UNSIGNED_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t in1, int32_t in2, int32_t* error) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = (uint32_t)in1 / (uint32_t)in2;
  }
}

static inline void SPVM_IMPLEMENT_DIVIDE_UNSIGNED_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t in1, int64_t in2, int32_t* error) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = (uint64_t)in1 / (uint64_t)in2;
  }
}

static inline void SPVM_IMPLEMENT_REMAINDER_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t in1, int32_t in2, int32_t* error) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = in1 % in2;
  }
}

static inline void SPVM_IMPLEMENT_REMAINDER_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t in1, int64_t in2, int32_t* error) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = in1 % in2;
  }
}

static inline void SPVM_IMPLEMENT_REMAINDER_UNSIGNED_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t in1, int32_t in2, int32_t* error) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = (uint32_t)in1 % (uint32_t)in2;
  }
}

static inline void SPVM_IMPLEMENT_REMAINDER_UNSIGNED_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t in1, int64_t in2, int32_t* error) {
  if (__builtin_expect(in2 == 0, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_DIVIDE_ZERO]);
    env->set_exception(env, stack, exception);
    *error = 1;
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

#define SPVM_IMPLEMENT_PUSH_MORTAL(mortal_stack, mortal_stack_top, object_vars_index) (mortal_stack[mortal_stack_top++] = object_vars_index)

#define SPVM_IMPLEMENT_INIT_BYTE(out) (out = 0)
#define SPVM_IMPLEMENT_INIT_SHORT(out) (out = 0)
#define SPVM_IMPLEMENT_INIT_INT(out) (out = 0)
#define SPVM_IMPLEMENT_INIT_LONG(out) (out = 0)
#define SPVM_IMPLEMENT_INIT_FLOAT(out) (out = 0)
#define SPVM_IMPLEMENT_INIT_DOUBLE(out) (out = 0)

static inline void SPVM_IMPLEMENT_INIT_MULNUM_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = 0;
  }
}

static inline void SPVM_IMPLEMENT_INIT_MULNUM_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = 0;
  }
}

static inline void SPVM_IMPLEMENT_INIT_MULNUM_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = 0;
  }
}

static inline void SPVM_IMPLEMENT_INIT_MULNUM_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = 0;
  }
}

static inline void SPVM_IMPLEMENT_INIT_MULNUM_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = 0;
  }
}

static inline void SPVM_IMPLEMENT_INIT_MULNUM_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, int32_t fields_length) {
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
#define SPVM_IMPLEMENT_MOVE_OBJECT(env, stack, out, in) (SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, in))

static inline void SPVM_IMPLEMENT_MOVE_OBJECT_WITH_TYPE_CHECKING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* in, int32_t cast_basic_type_id, int32_t cast_type_dimension, int32_t* error) {
  void* object = in;
  int32_t isa = env->isa(env, stack, object, cast_basic_type_id, cast_type_dimension);
  if (isa) {
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, in);
  }
  else {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_VALUE_ASSIGN_NON_ASSIGNABLE_TYPE]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
}

static inline void SPVM_IMPLEMENT_MOVE_OBJECT_CHECK_READ_ONLY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* in, int32_t* error) {
  void* string = in;
  if (env->is_read_only(env, stack, string)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ASSIGN_READ_ONLY_STRING_TO_MUTABLE_TYPE]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, string);
  }
}

#define SPVM_IMPLEMENT_MOVE_REF(out, in) (out = in)

#define SPVM_IMPLEMENT_BIT_NOT_INT(out, in) (out = ~in)
#define SPVM_IMPLEMENT_BIT_NOT_LONG(out, in) (out = ~in)
#define SPVM_IMPLEMENT_NEGATE_INT(out, in) (out = -in)
#define SPVM_IMPLEMENT_NEGATE_LONG(out, in) (out = -in)
#define SPVM_IMPLEMENT_NEGATE_FLOAT(out, in) (out = -in)
#define SPVM_IMPLEMENT_NEGATE_DOUBLE(out, in) (out = -in)

static inline void SPVM_IMPLEMENT_CONCAT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* in1, void* in2, int32_t* error) {
  void* string1 = in1;
  void* string2 = in2;
  if (string1 == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_CONCAT_LEFT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else if (string2 == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_CONCAT_RIGHT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    void* string3 = env->concat_raw(env, stack, string1, string2);
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, string3);
  }
}

#define SPVM_IMPLEMENT_BOOL_CONVERSION_INT(out, in) (out = in)
#define SPVM_IMPLEMENT_BOOL_CONVERSION_LONG(out, in) (out = !!in)
#define SPVM_IMPLEMENT_BOOL_CONVERSION_FLOAT(out, in) (out = !!in)
#define SPVM_IMPLEMENT_BOOL_CONVERSION_DOUBLE(out, in) (out = !!in)
#define SPVM_IMPLEMENT_BOOL_CONVERSION_OBJECT(out, in) (out = !!in)
#define SPVM_IMPLEMENT_BOOL_CONVERSION_REF(out, in) (out = !!in)
#define SPVM_IMPLEMENT_BOOL_CONVERSION_BOOL_OBJECT(env, stack, out, in) (out = !!env->get_bool_object_value(env, stack, in))

#define SPVM_IMPLEMENT_EQ_INT(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_EQ_LONG(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_EQ_FLOAT(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_EQ_DOUBLE(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_EQ_OBJECT(out, in1, in2) (out = (in1 == in2))
#define SPVM_IMPLEMENT_EQ_REF(out, in1, in2) (out = (in1 == in2))

#define SPVM_IMPLEMENT_NE_INT(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NE_LONG(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NE_FLOAT(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NE_DOUBLE(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NE_OBJECT(out, in1, in2) (out = (in1 != in2))
#define SPVM_IMPLEMENT_NE_REF(out, in1, in2) (out = (in1 != in2))

#define SPVM_IMPLEMENT_GT_INT(out, in1, in2) (out = (in1 > in2))
#define SPVM_IMPLEMENT_GT_LONG(out, in1, in2) (out = (in1 > in2))
#define SPVM_IMPLEMENT_GT_FLOAT(out, in1, in2) (out = (in1 > in2))
#define SPVM_IMPLEMENT_GT_DOUBLE(out, in1, in2) (out = (in1 > in2))

#define SPVM_IMPLEMENT_GE_INT(out, in1, in2) (out = (in1 >= in2))
#define SPVM_IMPLEMENT_GE_LONG(out, in1, in2) (out = (in1 >= in2))
#define SPVM_IMPLEMENT_GE_FLOAT(out, in1, in2) (out = (in1 >= in2))
#define SPVM_IMPLEMENT_GE_DOUBLE(out, in1, in2) (out = (in1 >= in2))

#define SPVM_IMPLEMENT_LT_INT(out, in1, in2) (out = (in1 < in2))
#define SPVM_IMPLEMENT_LT_LONG(out, in1, in2) (out = (in1 < in2))
#define SPVM_IMPLEMENT_LT_FLOAT(out, in1, in2) (out = (in1 < in2))
#define SPVM_IMPLEMENT_LT_DOUBLE(out, in1, in2) (out = (in1 < in2))

#define SPVM_IMPLEMENT_LE_INT(out, in1, in2) (out = (in1 <= in2))
#define SPVM_IMPLEMENT_LE_LONG(out, in1, in2) (out = (in1 <= in2))
#define SPVM_IMPLEMENT_LE_FLOAT(out, in1, in2) (out = (in1 <= in2))
#define SPVM_IMPLEMENT_LE_DOUBLE(out, in1, in2) (out = (in1 <= in2))

#define SPVM_IMPLEMENT_CMP_INT(out, in1, in2) (out = in1 > in2 ? 1 : in1 < in2 ? -1 : 0)
#define SPVM_IMPLEMENT_CMP_LONG(out, in1, in2) (out = in1 > in2 ? 1 : in1 < in2 ? -1 : 0)
#define SPVM_IMPLEMENT_CMP_FLOAT(out, in1, in2) (out = in1 > in2 ? 1 : in1 < in2 ? -1 : 0)
#define SPVM_IMPLEMENT_CMP_DOUBLE(out, in1, in2) (out = in1 > in2 ? 1 : in1 < in2 ? -1 : 0)

#define SPVM_IMPLEMENT_IS_UNDEF(out, in) (out = in == NULL)
#define SPVM_IMPLEMENT_IS_NOT_UNDEF(out, in) (out = in != NULL)

static inline void SPVM_IMPLEMENT_STRING_COMPARISON_OP(SPVM_ENV* env, SPVM_VALUE* stack, int32_t comparison_op_id, int32_t* out, void* in1, void* in2) {
  void* object1 = in1;
  void* object2 = in2;
  
  int32_t flag = 0;
  if (object1 == NULL && object2 == NULL) {
   switch (comparison_op_id) {
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_EQ: {
        flag = 1;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_NE: {
        flag = 0;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GT: {
        flag = 0;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GE: {
        flag = 1;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LT: {
        flag = 0;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LE: {
        flag = 1;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_CMP: {
        flag = 0;
        break;
      }
    }
  }
  else if (object1 != NULL && object2 == NULL) {
    switch (comparison_op_id) {
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_EQ: {
        flag = 0;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_NE: {
        flag = 1;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GT: {
        flag = 1;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GE: {
        flag = 1;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LT: {
        flag = 0;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LE: {
        flag = 0;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_CMP: {
        flag = 1;
        break;
      }
    }
  }
  else if (object1 == NULL && object2 != NULL) {
    switch (comparison_op_id) {
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_EQ: {
        flag = 0;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_NE: {
        flag = 1;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GT: {
        flag = 0;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GE: {
        flag = 0;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LT: {
        flag = 1;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LE: {
        flag = 1;
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_CMP: {
        flag = -1;
        break;
      }
    }
  }
  else {
    int32_t length1 = *(int32_t*)((intptr_t)object1 + (intptr_t)env->object_length_offset);
    int32_t length2 = *(int32_t*)((intptr_t)object2 + (intptr_t)env->object_length_offset);
    
    const char* bytes1 = env->get_chars(env, stack, object1);
    const char* bytes2 = env->get_chars(env, stack, object2);
    
    int32_t short_string_length = length1 < length2 ? length1 : length2;
    int32_t retval = memcmp(bytes1, bytes2, short_string_length);
    int32_t cmp;
    if (retval) {
      cmp = retval < 0 ? -1 : 1;
    } else if (length1 == length2) {
      cmp = 0;
    } else {
      cmp = length1 < length2 ? -1 : 1;
    }
    
    switch (comparison_op_id) {
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_EQ: {
        flag = (cmp == 0);
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_NE: {
        flag = (cmp != 0);
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GT: {
        flag = (cmp == 1);
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GE: {
        flag = (cmp >= 0);
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LT: {
        flag = (cmp == -1);
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LE: {
        flag = (cmp <= 0);
        break;
      }
      case SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_CMP: {
        flag = cmp;
        break;
      }
    }
  }
  
  *out = flag;
}

#define SPVM_IMPLEMENT_STRING_EQ(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON_OP(env, stack, SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_EQ, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_NE(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON_OP(env, stack, SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_NE, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_GT(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON_OP(env, stack, SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GT, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_GE(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON_OP(env, stack, SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_GE, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_LT(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON_OP(env, stack, SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LT, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_LE(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON_OP(env, stack, SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_LE, out, in1, in2))
#define SPVM_IMPLEMENT_STRING_CMP(env, stack, out, in1, in2) (SPVM_IMPLEMENT_STRING_COMPARISON_OP(env, stack, SPVM_IMPLEMENT_C_COMPARISON_OP_STRING_CMP, out, in1, in2))

static inline void SPVM_IMPLEMENT_NEW_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t basic_type_id, int32_t* error) {
  void* object = env->new_object_raw(env, stack, basic_type_id);
  if (object == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_OBJECT_FAILED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    // Push object
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
  }
}

static inline void SPVM_IMPLEMENT_NEW_OBJECT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t basic_type_id, int32_t length, int32_t* error) {
  if (length >= 0) {
    void* object = env->new_object_array_raw(env, stack, basic_type_id, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
}

static inline void SPVM_IMPLEMENT_NEW_MULDIM_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t basic_type_id, int32_t element_dimension, int32_t length, int32_t* error) {
  if (length >= 0) {
    void* object = env->new_muldim_array_raw(env, stack, basic_type_id, element_dimension, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
}

static inline void SPVM_IMPLEMENT_NEW_MULNUM_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t basic_type_id, int32_t length, int32_t* error) {
  if (length >= 0) {
    void* object = env->new_mulnum_array_raw(env, stack, basic_type_id, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
}

static inline void SPVM_IMPLEMENT_NEW_BYTE_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error) {
  if (length >= 0) {
    void* object = env->new_byte_array_raw(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
}

static inline void SPVM_IMPLEMENT_NEW_SHORT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error) {
  if (length >= 0) {
    void* object = env->new_short_array_raw(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
}

static inline void SPVM_IMPLEMENT_NEW_INT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error) {
  if (length >= 0) {
    void* object = env->new_int_array_raw(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
}

static inline void SPVM_IMPLEMENT_NEW_LONG_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error) {
  if (length >= 0) {
    void* object = env->new_long_array_raw(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
}

static inline void SPVM_IMPLEMENT_NEW_FLOAT_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error) {
  if (length >= 0) {
    void* object = env->new_float_array_raw(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
}

static inline void SPVM_IMPLEMENT_NEW_DOUBLE_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error) {
  if (length >= 0) {
    void* object = env->new_double_array_raw(env, stack, length);
    if (object == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_ARRAY_FAILED]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
    }
  }
  else {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRRAY_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
}

static inline void SPVM_IMPLEMENT_NEW_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, const char* constant_string, int32_t constant_string_length, int32_t* error) {
  void* string = env->new_string_raw(env, stack, constant_string, constant_string_length);
  if (string == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_STRING_FAILED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    env->make_read_only(env, stack, string);
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out , string);
  }
}

static inline void SPVM_IMPLEMENT_NEW_STRING_LEN(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t length, int32_t* error) {
  if (length >= 0) {
    void* string = env->new_string_raw(env, stack, NULL, length);
    if (string == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_NEW_STRING_FAILED]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, string);
    }
  }
  else {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_STRING_LENGTH_SMALL]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
}

#define SPVM_IMPLEMENT_IS_READ_ONLY(env, stack, out, in) (out = env->is_read_only(env, stack, in))

#define SPVM_IMPLEMENT_MAKE_READ_ONLY(env, stack, in) (env->make_read_only(env, stack, in))

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void* array, int32_t index, int32_t* error, int32_t object_header_size) {
  
  int8_t element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]));
    *error = 1;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]));
      *error = 1;
    }
    else { 
      *out = ((int8_t*)((intptr_t)array + object_header_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void* array, int32_t index, int32_t* error, int32_t object_header_size) {
  
  int16_t element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]));
    *error = 1;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]));
      *error = 1;
    }
    else { 
      *out = ((int16_t*)((intptr_t)array + object_header_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* array, int32_t index, int32_t* error, int32_t object_header_size) {
  
  int32_t element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]));
    *error = 1;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]));
      *error = 1;
    }
    else { 
      *out = ((int32_t*)((intptr_t)array + object_header_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, void* array, int32_t index, int32_t* error, int32_t object_header_size) {
  
  int64_t element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]));
    *error = 1;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]));
      *error = 1;
    }
    else { 
      *out = ((int64_t*)((intptr_t)array + object_header_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, void* array, int32_t index, int32_t* error, int32_t object_header_size) {
  
  float element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]));
    *error = 1;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]));
      *error = 1;
    }
    else { 
      *out = ((float*)((intptr_t)array + object_header_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, void* array, int32_t index, int32_t* error, int32_t object_header_size) {
  
  double element = 0;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]));
    *error = 1;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]));
      *error = 1;
    }
    else { 
      *out = ((double*)((intptr_t)array + object_header_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* array, int32_t index, int32_t* error, int32_t object_header_size) {
  
  void* element = NULL;
  
  if (__builtin_expect(array == NULL, 0)) { 
    env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]));
    *error = 1;
  }
  else { 
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { 
      env->set_exception(env, stack, env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]));
      *error = 1;
    }
    else { 
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, ((void**)((intptr_t)array + object_header_size))[index]);
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int8_t in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((int8_t*)((intptr_t)array + object_header_size))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int16_t in, int32_t* error, int32_t object_header_short_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((int16_t*)((intptr_t)array + object_header_short_size))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_INT(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int32_t in, int32_t* error, int32_t object_header_int_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((int32_t*)((intptr_t)array + object_header_int_size))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_LONG(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int64_t in, int32_t* error, int32_t object_header_long_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((int64_t*)((intptr_t)array + object_header_long_size))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, float in, int32_t* error, int32_t object_header_float_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((float*)((intptr_t)array + object_header_float_size))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, double in, int32_t* error, int32_t object_header_double_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((double*)((intptr_t)array + object_header_double_size))[index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      void** element_address = &((void**)((intptr_t)array + object_header_size))[index];
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, element_address, in);
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      void** element_address = &((void**)((intptr_t)array + object_header_size))[index];
      void* object = in;
      int32_t elem_isa = env->elem_isa(env, stack, array, object);
      if (elem_isa) {
        SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, element_address, object);
      }
      else {
        void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ELEMENT_ASSIGN_NON_ASSIGNABLE_TYPE]);
        env->set_exception(env, stack, exception);
        *error = 1;
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_UNDEF(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      void* object_address = &((void**)((intptr_t)array + object_header_size))[index];
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, object_address, NULL);
    }
  }
}

static inline void SPVM_IMPLEMENT_ARRAY_LENGTH(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* array, int32_t* error) {
  if (array == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset);
  }
}

static inline void SPVM_IMPLEMENT_GET_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void* object, int32_t field_id, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = *(int8_t*)((intptr_t)object + object_header_size + field_offset);
  }
}

static inline void SPVM_IMPLEMENT_GET_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void* object, int32_t field_id, int32_t* error, int32_t object_header_short_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = *(int16_t*)((intptr_t)object + object_header_short_size + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object, int32_t field_id, int32_t* error, int32_t object_header_int_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = *(int32_t*)((intptr_t)object + object_header_int_size + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, void* object, int32_t field_id, int32_t* error, int32_t object_header_long_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = *(int64_t*)((intptr_t)object + object_header_long_size + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, void* object, int32_t field_id, int32_t* error, int32_t object_header_float_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = *(float*)((intptr_t)object + object_header_float_size + field_offset);
  }
}


static inline void SPVM_IMPLEMENT_GET_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, void* object, int32_t field_id, int32_t* error, int32_t object_header_double_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = *(double*)((intptr_t)object + object_header_double_size + field_offset);
  }
}

static inline void SPVM_IMPLEMENT_GET_FIELD_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* object, int32_t field_id, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    void* get_field_object = *(void**)((intptr_t)object + object_header_size + field_offset);
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, get_field_object);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int8_t in, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(int8_t*)((intptr_t)object + object_header_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int16_t in, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(int16_t*)((intptr_t)object + object_header_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int32_t in, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(int32_t*)((intptr_t)object + object_header_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int64_t in, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(int64_t*)((intptr_t)object + object_header_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, float in, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(float*)((intptr_t)object + object_header_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, double in, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(double*)((intptr_t)object + object_header_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, void* in, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    void* get_field_object_address = (void**)((intptr_t)object + object_header_size + field_offset);
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, get_field_object_address, in);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_UNDEF(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    void* get_field_object_address = (void**)((intptr_t)object + object_header_size + field_offset);
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, get_field_object_address, NULL);
  }
}

#define SPVM_IMPLEMENT_GET_CLASS_VAR_BYTE(env, stack, out, class_var_id) (out = *(int8_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id])
#define SPVM_IMPLEMENT_GET_CLASS_VAR_SHORT(env, stack, out, class_var_id) (out = *(int16_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id])
#define SPVM_IMPLEMENT_GET_CLASS_VAR_INT(env, stack, out, class_var_id) (out = *(int32_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id])
#define SPVM_IMPLEMENT_GET_CLASS_VAR_LONG(env, stack, out, class_var_id) (out = *(int64_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id])
#define SPVM_IMPLEMENT_GET_CLASS_VAR_FLOAT(env, stack, out, class_var_id) (out = *(float*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id])
#define SPVM_IMPLEMENT_GET_CLASS_VAR_DOUBLE(env, stack, out, class_var_id) (out = *(double*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id])
#define SPVM_IMPLEMENT_GET_CLASS_VAR_OBJECT(env, stack, out, class_var_id) (SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, *(void**)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id]))

#define SPVM_IMPLEMENT_SET_CLASS_VAR_BYTE(env, stack, class_var_id, in) (*(int8_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = in)
#define SPVM_IMPLEMENT_SET_CLASS_VAR_SHORT(env, stack, class_var_id, in) (*(int16_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = in)
#define SPVM_IMPLEMENT_SET_CLASS_VAR_INT(env, stack, class_var_id, in) (*(int32_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = in)
#define SPVM_IMPLEMENT_SET_CLASS_VAR_LONG(env, stack, class_var_id, in) (*(int64_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = in)
#define SPVM_IMPLEMENT_SET_CLASS_VAR_FLOAT(env, stack, class_var_id, in) (*(float*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = in)
#define SPVM_IMPLEMENT_SET_CLASS_VAR_DOUBLE(env, stack, class_var_id, in) (*(double*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = in)
#define SPVM_IMPLEMENT_SET_CLASS_VAR_OBJECT(env, stack, class_var_id, in) (SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, (void**)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id], in))
#define SPVM_IMPLEMENT_SET_CLASS_VAR_UNDEF(env, stack, class_var_id) (SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, (void**)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id], NULL))

#define SPVM_IMPLEMENT_GET_EXCEPTION_VAR(env, stack, out) (SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, env->get_exception(env, stack)))
#define SPVM_IMPLEMENT_SET_EXCEPTION_VAR(env, stack, in) (env->set_exception(env, stack, in))
#define SPVM_IMPLEMENT_SET_EXCEPTION_VAR_UNDEF(env, stack) (env->set_exception(env, stack, NULL))

static inline void SPVM_IMPLEMENT_ISA(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object, int32_t dist_basic_type_id, int32_t dist_type_dimension) {
  if (object) {
    *out = env->isa(env, stack, object, dist_basic_type_id, dist_type_dimension);
  }
  else {
    *out = 0;
  }
}

static inline void SPVM_IMPLEMENT_IS_TYPE(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object, int32_t dist_basic_type_id, int32_t dist_type_dimension) {
  if (object) {
    *out = env->is_type(env, stack, object, dist_basic_type_id, dist_type_dimension);
  }
  else {
    *out = 0;
  }
}

#define SPVM_IMPLEMENT_HAS_IMPL(env, stack, out, object, method_name) (out = env->get_instance_method_id(env, stack, object, method_name) >= 0)

static inline void SPVM_IMPLEMENT_PRINT(SPVM_ENV* env, SPVM_VALUE* stack, void* string) {
  if (string) {
    const char* bytes = env->get_chars(env, stack, string);
    int32_t string_length = env->length(env, stack, string);
    
    if (string_length > 0) {
      size_t ret = fwrite(bytes, 1, string_length, stdout);
    }
  }
}

static inline void SPVM_IMPLEMENT_SAY(SPVM_ENV* env, SPVM_VALUE* stack, void* string) {
  if (string) {
    const char* bytes = env->get_chars(env, stack, string);
    int32_t string_length = env->length(env, stack, string);
    
    if (string_length > 0) {
      size_t ret = fwrite(bytes, 1, string_length, stdout);
    }
  }
  fprintf(stdout, "\n");
}

static inline void SPVM_IMPLEMENT_WARN(SPVM_ENV* env, SPVM_VALUE* stack, void* string, const char* module_dir, const char* module_dir_sep, const char* module_rel_file, int32_t line) {
  int32_t empty_or_undef = 0;
  if (string) {
    const char* bytes = env->get_chars(env, stack, string);
    int32_t string_length = env->length(env, stack, string);

    if (string_length > 0) {
      size_t ret = fwrite(bytes, 1, string_length, stderr);
      // Add line and file information if last character is not '\n'
      int32_t add_line_file;
      if (bytes[string_length - 1] != '\n') {
        fprintf(stderr, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_WARN_AT], module_dir, module_dir_sep, module_rel_file, line);
      }
    }
    else {
      empty_or_undef = 1;
    }
  }
  else {
    empty_or_undef = 1;
  }

  if (empty_or_undef) {
    fprintf(stderr, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_WARN_UNDEF], module_dir, module_dir_sep, module_rel_file, line);
  }

  fflush(stderr);
}

#define SPVM_IMPLEMENT_GET_ERROR_CODE(out, error_code) (out = error_code)

static inline void SPVM_IMPLEMENT_SET_ERROR_CODE(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t* error_code, int32_t in, int32_t* error) {
  if (in < 1) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ERROR_CODE_TOO_SMALL]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *error_code = in;
    *out = *error_code;
  }
}

#define SPVM_IMPLEMENT_CLEAR_EVAL_ERROR(eval_error) (eval_error = 0)

#define SPVM_IMPLEMENT_GET_EVAL_ERROR(out, eval_error) (out = eval_error)

#define SPVM_IMPLEMENT_SET_ERROR(error, error_code) (error = error_code)

#define SPVM_IMPLEMENT_ITEMS(env, stack, out) (out = env->items(env, stack))

#define SPVM_IMPLEMENT_GET_CLASS_ID(out, class_id) (out = class_id)

static inline void SPVM_IMPLEMENT_REFOP(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* object) {
  if (object == NULL) {
    *out = NULL;
  }
  else {
    void* type_name = env->get_type_name_raw(env, stack, object);
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, type_name);
  }
}

static inline void SPVM_IMPLEMENT_DUMP(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* object) {
  void* dump = env->dump_raw(env, stack, object);
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, dump);
}

static inline void SPVM_IMPLEMENT_COPY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* object, int32_t* error) {
  if (object) {
    if (!(env->is_string(env, stack, object) || env->is_numeric_array(env, stack, object) || env->is_mulnum_array(env, stack, object))) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_COPY_OPERAND_INVALID]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      void* new_object_raw = env->copy_raw(env, stack, object);
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, new_object_raw);
    }
  }
  else {
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, NULL);
  }
}

#define SPVM_IMPLEMENT_REF_BYTE(out, in) (out = in)
#define SPVM_IMPLEMENT_REF_SHORT(out, in) (out = in)
#define SPVM_IMPLEMENT_REF_INT(out, in) (out = in)
#define SPVM_IMPLEMENT_REF_LONG(out, in) (out = in)
#define SPVM_IMPLEMENT_REF_FLOAT(out, in) (out = in)
#define SPVM_IMPLEMENT_REF_DOUBLE(out, in) (out = in)

#define SPVM_IMPLEMENT_GET_DEREF_BYTE(out, in) (out = *(int8_t*)*(void**)in)
#define SPVM_IMPLEMENT_GET_DEREF_SHORT(out, in) (out = *(int16_t*)*(void**)in)
#define SPVM_IMPLEMENT_GET_DEREF_INT(out, in) (out = *(int32_t*)*(void**)in)
#define SPVM_IMPLEMENT_GET_DEREF_LONG(out, in) (out = *(int64_t*)*(void**)in)
#define SPVM_IMPLEMENT_GET_DEREF_FLOAT(out, in) (out = *(float*)*(void**)in)
#define SPVM_IMPLEMENT_GET_DEREF_DOUBLE(out, in) (out = *(double*)*(void**)in)

#define SPVM_IMPLEMENT_SET_DEREF_BYTE(out, in) (*(int8_t*)*(void**)out = in)
#define SPVM_IMPLEMENT_SET_DEREF_SHORT(out, in) (*(int16_t*)*(void**)out = in)
#define SPVM_IMPLEMENT_SET_DEREF_INT(out, in) (*(int32_t*)*(void**)out = in)
#define SPVM_IMPLEMENT_SET_DEREF_LONG(out, in) (*(int64_t*)*(void**)out = in)
#define SPVM_IMPLEMENT_SET_DEREF_FLOAT(out, in) (*(float*)*(void**)out = in)
#define SPVM_IMPLEMENT_SET_DEREF_DOUBLE(out, in) (*(double*)*(void**)out = in)

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

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, int8_t* array, int32_t index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int8_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, int16_t* array, int32_t index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int16_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t* array, int32_t index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int32_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t* array, int32_t index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((int64_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, float* array, int32_t index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((float*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, double* array, int32_t index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        *(out + field_index) = ((double*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* array, int32_t index, int32_t fields_length, int8_t* in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int8_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* array, int32_t index, int32_t fields_length, int16_t* in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int16_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* array, int32_t index, int32_t fields_length, int32_t* in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int32_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* array, int32_t index, int32_t fields_length, int64_t* in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((int64_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* array, int32_t index, int32_t fields_length, float* in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((float*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* array, int32_t index, int32_t fields_length, double* in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      int32_t field_index;
      for (field_index = 0; field_index < fields_length; field_index++) {
        ((double*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = *(in + field_index);
      }
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, int8_t* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      *out = ((int8_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, int16_t* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      *out = ((int16_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, int32_t* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      *out = ((int32_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, int64_t* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      *out = ((int64_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, float* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      *out = ((float*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, double* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(array == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      *out = ((double*)((intptr_t)array + object_header_size))[fields_length * index + field_index];
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* array, int32_t index, int32_t field_index, int32_t fields_length, int8_t in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((int8_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* array, int32_t index, int32_t field_index, int32_t fields_length, int16_t in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((int16_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* array, int32_t index, int32_t field_index, int32_t fields_length, int32_t in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((int32_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* array, int32_t index, int32_t field_index, int32_t fields_length, int64_t in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((int64_t*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* array, int32_t index, int32_t field_index, int32_t fields_length, float in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((float*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* array, int32_t index, int32_t field_index, int32_t fields_length, double in, int32_t* error, int32_t object_header_size) {
  if (__builtin_expect(!array, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
    else {
      ((double*)((intptr_t)array + object_header_size))[fields_length * index + field_index] = in;
    }
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void* mulnum_ref, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *((int8_t*)mulnum_ref + field_index);
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void* mulnum_ref, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *((int16_t*)mulnum_ref + field_index);
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* mulnum_ref, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *((int32_t*)mulnum_ref + field_index);
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, void* mulnum_ref, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *((int64_t*)mulnum_ref + field_index);
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, void* mulnum_ref, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *((float*)mulnum_ref + field_index);
  }
}

static inline void SPVM_IMPLEMENT_DEREF_MULNUM_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, void* mulnum_ref, int32_t fields_length) {
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    *(out + field_index) = *((double*)mulnum_ref + field_index);
  }
}

#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_BYTE(out, mulnum_ref, field_index) (out = *((int8_t*)mulnum_ref +field_index))
#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_SHORT(out, mulnum_ref, field_index) (out = *((int16_t*)mulnum_ref +field_index))
#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_INT(out, mulnum_ref, field_index) (out = *((int32_t*)mulnum_ref +field_index))
#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_LONG(out, mulnum_ref, field_index) (out = *((int64_t*)mulnum_ref +field_index))
#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_FLOAT(out, mulnum_ref, field_index) (out = *((float*)mulnum_ref +field_index))
#define SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_DOUBLE(out, mulnum_ref, field_index) (out = *((double*)mulnum_ref +field_index))

#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_BYTE(mulnum_ref, field_index, in) (*((int8_t*)mulnum_ref +field_index) = in)
#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_SHORT(mulnum_ref, field_index, in) (*((int16_t*)mulnum_ref +field_index) = in)
#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_INT(mulnum_ref, field_index, in) (*((int32_t*)mulnum_ref +field_index) = in)
#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_LONG(mulnum_ref, field_index, in) (*((int64_t*)mulnum_ref +field_index) = in)
#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_FLOAT(mulnum_ref, field_index, in) (*((float*)mulnum_ref +field_index) = in)
#define SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_DOUBLE(mulnum_ref, field_index, in) (*((double*)mulnum_ref +field_index) = in)

static inline void SPVM_IMPLEMENT_WEAKEN_FIELD(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  if (object == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    void** get_field_object_address = (void**)((intptr_t)object + object_header_size + field_offset);
    int32_t status = env->weaken(env, stack, get_field_object_address);
    if (status != 0) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_WEAKEN_BACK_REFERENCE_ALLOCATION_FAILED]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
  }
}

static inline void SPVM_IMPLEMENT_UNWEAKEN_FIELD(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  if (object == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    void** get_field_object_address = (void**)((intptr_t)object + object_header_size + field_offset);
    env->unweaken(env, stack, get_field_object_address);
  }
}

static inline void SPVM_IMPLEMENT_ISWEAK_FIELD(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object, int32_t field_id, int32_t* error, int32_t object_header_size) {
  int32_t field_offset = env->get_field_offset(env, stack, field_id);
  if (object == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    void** get_field_object_address = (void**)((intptr_t)object + object_header_size + field_offset);
    *out = env->isweak(env, stack, get_field_object_address);
  }
}

static inline void SPVM_IMPLEMENT_REFCNT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object) {
  if (object == NULL) {
    *out = 0;
  }
  else {
    *out = env->get_ref_count(env, stack, object);
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

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int8_t value, char* tmp_buffer) {
  sprintf(tmp_buffer, "%" PRId8, value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int16_t value, char* tmp_buffer) {
  sprintf(tmp_buffer, "%" PRId16, value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t value, char* tmp_buffer) {
  sprintf(tmp_buffer, "%" PRId32, value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int64_t value, char* tmp_buffer) {
  sprintf(tmp_buffer, "%" PRId64, value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, float value, char* tmp_buffer) {
  sprintf(tmp_buffer, "%g", value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, double value, char* tmp_buffer) {
  sprintf(tmp_buffer, "%g", value);
  int32_t string_length = strlen(tmp_buffer);
  void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_BYTE_ARRAY(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* src_string) {
  int32_t src_string_length = env->length(env, stack, src_string);
  const char* src_string_data = env->get_chars(env, stack, src_string);
  void* byte_array = env->new_byte_array_raw(env, stack, src_string_length);
  int8_t* byte_array_data = env->get_elems_byte(env, stack, byte_array);
  memcpy(byte_array_data, src_string_data, src_string_length);
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, byte_array);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_ARRAY_TO_STRING(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* src_byte_array) {
  int32_t src_byte_array_length = env->length(env, stack, src_byte_array);
  int8_t* src_byte_array_data = env->get_elems_byte(env, stack, src_byte_array);
  void* string = env->new_string_raw(env, stack, (const char*)src_byte_array_data, src_byte_array_length);
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, string);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int8_t value, int32_t object_header_size) {
  int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS;
  void* object = env->new_object_raw(env, stack, basic_type_id);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
  *(int8_t*)&fields[0] = value;
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int16_t value, int32_t object_header_size) {
  int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS;
  void* object = env->new_object_raw(env, stack, basic_type_id);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
  *(int16_t*)&fields[0] = value;
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_INT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int32_t value, int32_t object_header_size) {
  int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS;
  void* object = env->new_object_raw(env, stack, basic_type_id);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
  *(int32_t*)&fields[0] = value;
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_LONG_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, int64_t value, int32_t object_header_size) {
  int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS;
  void* object = env->new_object_raw(env, stack, basic_type_id);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
  *(int64_t*)&fields[0] = value;
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, float value, int32_t object_header_size) {
  int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS;
  void* object = env->new_object_raw(env, stack, basic_type_id);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
  *(float*)&fields[0] = value;
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, double value, int32_t object_header_size) {
  int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS;
  void* object = env->new_object_raw(env, stack, basic_type_id);
  SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
  *(double*)&fields[0] = value;
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, object);
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void* object, int32_t* error, int32_t object_header_size) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
    int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
    if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS && object_type_dimension == 0) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
      *out = *(int8_t*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void* object, int32_t* error, int32_t object_header_size) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
    int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
    if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS && object_type_dimension == 0) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
      *out = *(int16_t*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_INT_OBJECT_TO_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* object, int32_t* error, int32_t object_header_size) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
    int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
    if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS && object_type_dimension == 0) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
      *out = *(int32_t*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_OBJECT_TO_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, void* object, int32_t* error, int32_t object_header_size) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
    int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
    if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS && object_type_dimension == 0) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
      *out = *(int64_t*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, void* object, int32_t* error, int32_t object_header_size) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
    int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
    if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS && object_type_dimension == 0) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
      *out = *(float*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error = 1;
    }
  }
}

static inline void SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, void* object, int32_t* error, int32_t object_header_size) {
  if (object == NULL) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_FROM_UNDEF]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
    int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
    if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS && object_type_dimension == 0) {
      SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_size);
      *out = *(double*)&fields[0];
    }
    else {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
      env->set_exception(env, stack, exception);
      *error = 1;
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

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_index, int32_t stack_length, int8_t* in) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(int8_t*)&stack[stack_index + field_index] = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_index, int32_t stack_length, int16_t* in) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(int16_t*)&stack[stack_index + field_index] = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_index, int32_t stack_length, int32_t* in) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(int32_t*)&stack[stack_index + field_index] = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_index, int32_t stack_length, int64_t* in) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(int64_t*)&stack[stack_index + field_index] = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_index, int32_t stack_length, float* in) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(float*)&stack[stack_index + field_index] = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_SET_STACK_MULNUM_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, int32_t stack_index, int32_t stack_length, double* in) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(double*)&stack[stack_index + field_index] = *(in + field_index);
  }
}

#define SPVM_IMPLEMENT_GET_STACK_BYTE(out, stack, stack_index) (out = *(int8_t*)&stack[stack_index])
#define SPVM_IMPLEMENT_GET_STACK_SHORT(out, stack, stack_index) (out = *(int16_t*)&stack[stack_index])
#define SPVM_IMPLEMENT_GET_STACK_INT(out, stack, stack_index) (out = *(int32_t*)&stack[stack_index])
#define SPVM_IMPLEMENT_GET_STACK_LONG(out, stack, stack_index) (out = *(int64_t*)&stack[stack_index])
#define SPVM_IMPLEMENT_GET_STACK_FLOAT(out, stack, stack_index) (out = *(float*)&stack[stack_index])
#define SPVM_IMPLEMENT_GET_STACK_DOUBLE(out, stack, stack_index) (out = *(double*)&stack[stack_index])

static inline void SPVM_IMPLEMENT_GET_STACK_OBJECT(SPVM_ENV* env, void** out, SPVM_VALUE* stack, int32_t stack_index) {
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, *(void**)&stack[stack_index]);
}

#define SPVM_IMPLEMENT_GET_STACK_REF(out, stack, stack_index) (out = *(void**)&stack[stack_index])

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_BYTE(SPVM_ENV* env, int8_t* out, SPVM_VALUE* stack, int32_t stack_index, int32_t type_stack_length) {
  for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
    *(out + field_index) = *(int8_t*)&stack[(stack_index) + field_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_SHORT(SPVM_ENV* env, int16_t* out, SPVM_VALUE* stack, int32_t stack_index, int32_t type_stack_length) {
  for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
    *(out + field_index) = *(int16_t*)&stack[(stack_index) + field_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_INT(SPVM_ENV* env, int32_t* out, SPVM_VALUE* stack, int32_t stack_index, int32_t type_stack_length) {
  for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
    *(out + field_index) = *(int32_t*)&stack[(stack_index) + field_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_LONG(SPVM_ENV* env, int64_t* out, SPVM_VALUE* stack, int32_t stack_index, int32_t type_stack_length) {
  for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
    *(out + field_index) = *(int64_t*)&stack[(stack_index) + field_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_FLOAT(SPVM_ENV* env, float* out, SPVM_VALUE* stack, int32_t stack_index, int32_t type_stack_length) {
  for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
    *(out + field_index) = *(float*)&stack[(stack_index) + field_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_MULNUM_DOUBLE(SPVM_ENV* env, double* out, SPVM_VALUE* stack, int32_t stack_index, int32_t type_stack_length) {
  for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
    *(out + field_index) = *(double*)&stack[(stack_index) + field_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_BYTE(SPVM_ENV* env, int8_t* out, SPVM_VALUE* stack, int32_t stack_index, int8_t default_value) {
  int32_t args_length = env->get_args_stack_length(env, stack);
  if (stack_index >= args_length) {
    *out = default_value;
  }
  else {
    *out = *(int8_t*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_SHORT(SPVM_ENV* env, int16_t* out, SPVM_VALUE* stack, int32_t stack_index, int16_t default_value) {
  int32_t args_length = env->get_args_stack_length(env, stack);
  if (stack_index >= args_length) {
    *out = default_value;
  }
  else {
    *out = *(int16_t*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_INT(SPVM_ENV* env, int32_t* out, SPVM_VALUE* stack, int32_t stack_index, int32_t default_value) {
  int32_t args_length = env->get_args_stack_length(env, stack);
  if (stack_index >= args_length) {
    *out = default_value;
  }
  else {
    *out = *(int32_t*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_LONG(SPVM_ENV* env, int64_t* out, SPVM_VALUE* stack, int32_t stack_index, int64_t default_value) {
  int32_t args_length = env->get_args_stack_length(env, stack);
  if (stack_index >= args_length) {
    *out = default_value;
  }
  else {
    *out = *(int64_t*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_FLOAT(SPVM_ENV* env, float* out, SPVM_VALUE* stack, int32_t stack_index, float default_value) {
  int32_t args_length = env->get_args_stack_length(env, stack);
  if (stack_index >= args_length) {
    *out = default_value;
  }
  else {
    *out = *(float*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_DOUBLE(SPVM_ENV* env, double* out, SPVM_VALUE* stack, int32_t stack_index, double default_value) {
  int32_t args_length = env->get_args_stack_length(env, stack);
  if (stack_index >= args_length) {
    *out = default_value;
  }
  else {
    *out = *(double*)&stack[stack_index];
  }
}

static inline void SPVM_IMPLEMENT_GET_STACK_OPTIONAL_OBJECT(SPVM_ENV* env, void** out, SPVM_VALUE* stack, int32_t stack_index) {
  int32_t args_length = env->get_args_stack_length(env, stack);
  if (stack_index >= args_length) {
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, NULL);
  }
  else {
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, *(void**)&stack[stack_index]);
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
    SPVM_IMPLEMENT_INC_REF_COUNT_ONLY(env, stack, in);
  }
}

#define SPVM_IMPLEMENT_RETURN_UNDEF(stack) (*(void**)&stack[0] = NULL)

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* in, int32_t stack_length) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(int8_t*)&stack[field_index] = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* in, int32_t stack_length) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(int16_t*)&stack[field_index] = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* in, int32_t stack_length) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(int32_t*)&stack[field_index] = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* in, int32_t stack_length) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(int64_t*)&stack[field_index] = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* in, int32_t stack_length) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(float*)&stack[field_index] = *(in + field_index);
  }
}

static inline void SPVM_IMPLEMENT_RETURN_MULNUM_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* in, int32_t stack_length) {
  for (int32_t field_index = 0; field_index < stack_length; field_index++) {
    *(double*)&stack[field_index] = *(in + field_index);
  }
}

#define SPVM_IMPLEMENT_CALL_CLASS_METHOD(env, stack, error, method_id, args_stack_length) (error = env->call_method(env, stack, method_id, args_stack_length))
#define SPVM_IMPLEMENT_CALL_INSTANCE_METHOD(env, stack, error, method_id, args_stack_length) (error = env->call_method(env, stack, method_id, args_stack_length))

static inline void SPVM_IMPLEMENT_CALL_INTERFACE_METHOD(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* interface_name, const char* method_name, int32_t args_stack_length, int32_t* error, char* tmp_buffer) {
  int32_t entity_method_id = env->get_instance_method_id(env, stack, object, method_name);
  if (entity_method_id < 0) {
    memset(tmp_buffer, sizeof(tmp_buffer), 0);
    snprintf(tmp_buffer, 255, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_CALL_INSTANCE_METHOD_NOT_FOUND], method_name, interface_name);
    void* exception = env->new_string_nolen_raw(env, stack, tmp_buffer);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  
  if (!*error) {
    *error = env->call_method(env, stack, entity_method_id, args_stack_length);
  }
}

#endif

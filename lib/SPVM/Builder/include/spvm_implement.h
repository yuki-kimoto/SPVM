#ifndef SPVM_IMPLEMENT_H
#define SPVM_IMPLEMENT_H

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

  int32_t basic_type_id = env->get_basic_type_id(env, basic_type_name);

  if (basic_type_id < 0) {
    snprintf(message, 256, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ERROR_BASIC_TYPE_NOT_FOUND], basic_type_name);
    void* exception = env->new_string_nolen_raw(env, stack, message);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  
  return basic_type_id;
}

static inline int32_t SPVM_IMPLEMENT_GET_FIELD_ID(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, char* message, int32_t* error) {

  int32_t field_id = env->get_field_id(env, object, field_name);

  if (field_id < 0) {
    snprintf(message, 256, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ERROR_FIELD_NOT_FOUND], field_name);
    void* exception = env->new_string_nolen_raw(env, stack, message);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  
  return field_id;
}

static inline int32_t SPVM_IMPLEMENT_GET_CLASS_VAR_ID(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, char* message, int32_t* error) {
  
  int32_t class_var_id = env->get_class_var_id(env, class_name, class_var_name);
  
  if (class_var_id < 0) {
    snprintf(message, 256, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_ERROR_CLASS_VAR_NOT_FOUND], class_var_name);
    void* exception = env->new_string_nolen_raw(env, stack, message);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  
  return class_var_id;
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

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void* array, int32_t index, int32_t* error, int32_t object_header_byte_size) {
  
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
      *out = ((int8_t*)((intptr_t)array + object_header_byte_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void* array, int32_t index, int32_t* error, int32_t object_header_byte_size) {
  
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
      *out = ((int16_t*)((intptr_t)array + object_header_byte_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_INT(SPVM_ENV* env, SPVM_VALUE* stack, int32_t* out, void* array, int32_t index, int32_t* error, int32_t object_header_byte_size) {
  
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
      *out = ((int32_t*)((intptr_t)array + object_header_byte_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_LONG(SPVM_ENV* env, SPVM_VALUE* stack, int64_t* out, void* array, int32_t index, int32_t* error, int32_t object_header_byte_size) {
  
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
      *out = ((int64_t*)((intptr_t)array + object_header_byte_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, float* out, void* array, int32_t index, int32_t* error, int32_t object_header_byte_size) {
  
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
      *out = ((float*)((intptr_t)array + object_header_byte_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, double* out, void* array, int32_t index, int32_t* error, int32_t object_header_byte_size) {
  
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
      *out = ((double*)((intptr_t)array + object_header_byte_size))[index];
    }
  }
}

static inline void SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* array, int32_t index, int32_t* error, int32_t object_header_byte_size) {
  
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
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, ((void**)((intptr_t)array + object_header_byte_size))[index]);
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int8_t in, int32_t* error, int32_t object_header_byte_size) {
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
      ((int8_t*)((intptr_t)array + object_header_byte_size))[index] = in;
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

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* in, int32_t* error, int32_t object_header_byte_size) {
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
      void** element_address = &((void**)((intptr_t)array + object_header_byte_size))[index];
      SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, element_address, in);
    }
  }
}

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* in, int32_t* error, int32_t object_header_byte_size) {
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
      void** element_address = &((void**)((intptr_t)array + object_header_byte_size))[index];
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

static inline void SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_UNDEF(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, int32_t* error, int32_t object_header_byte_size) {
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
      void* object_address = &((void**)((intptr_t)array + object_header_byte_size))[index];
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

static inline void SPVM_IMPLEMENT_GET_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, int8_t* out, void* object, int32_t field_id, int32_t* error, int32_t object_header_byte_size) {
  int32_t field_offset = env->get_field_offset(env, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = *(int8_t*)((intptr_t)object + object_header_byte_size + field_offset);
  }
}

static inline void SPVM_IMPLEMENT_GET_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, int16_t* out, void* object, int32_t field_id, int32_t* error, int32_t object_header_short_size) {
  int32_t field_offset = env->get_field_offset(env, field_id);
  
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
  int32_t field_offset = env->get_field_offset(env, field_id);
  
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
  int32_t field_offset = env->get_field_offset(env, field_id);
  
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
  int32_t field_offset = env->get_field_offset(env, field_id);
  
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
  int32_t field_offset = env->get_field_offset(env, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *out = *(double*)((intptr_t)object + object_header_double_size + field_offset);
  }
}

static inline void SPVM_IMPLEMENT_GET_FIELD_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void** out, void* object, int32_t field_id, int32_t* error, int32_t object_header_byte_size) {
  int32_t field_offset = env->get_field_offset(env, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    void* get_field_object = *(void**)((intptr_t)object + object_header_byte_size + field_offset);
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out, get_field_object);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_BYTE(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int8_t in, int32_t* error, int32_t object_header_byte_size) {
  int32_t field_offset = env->get_field_offset(env, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(int8_t*)((intptr_t)object + object_header_byte_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_SHORT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int16_t in, int32_t* error, int32_t object_header_byte_size) {
  int32_t field_offset = env->get_field_offset(env, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(int16_t*)((intptr_t)object + object_header_byte_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_INT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int32_t in, int32_t* error, int32_t object_header_byte_size) {
  int32_t field_offset = env->get_field_offset(env, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(int32_t*)((intptr_t)object + object_header_byte_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_LONG(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int64_t in, int32_t* error, int32_t object_header_byte_size) {
  int32_t field_offset = env->get_field_offset(env, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(int64_t*)((intptr_t)object + object_header_byte_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_FLOAT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, float in, int32_t* error, int32_t object_header_byte_size) {
  int32_t field_offset = env->get_field_offset(env, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(float*)((intptr_t)object + object_header_byte_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_DOUBLE(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, double in, int32_t* error, int32_t object_header_byte_size) {
  int32_t field_offset = env->get_field_offset(env, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    *(double*)((intptr_t)object + object_header_byte_size + field_offset) = in;
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_OBJECT(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, void* in, int32_t* error, int32_t object_header_byte_size) {
  int32_t field_offset = env->get_field_offset(env, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    void* get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + field_offset);
    SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, get_field_object_address, in);
  }
}

static inline void SPVM_IMPLEMENT_SET_FIELD_UNDEF(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int32_t* error, int32_t object_header_byte_size) {
  int32_t field_offset = env->get_field_offset(env, field_id);
  
  if (__builtin_expect(object == NULL, 0)) {
    void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED]);
    env->set_exception(env, stack, exception);
    *error = 1;
  }
  else {
    void* get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + field_offset);
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

#define SPVM_IMPLEMENT_HAS_IMPL(env, stack, out, object, method_name) (out = env->get_instance_method_id(env, object, method_name) >= 0)

#endif

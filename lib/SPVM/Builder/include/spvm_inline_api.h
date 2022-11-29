#ifndef SPVM_INLINE_API_H
#define SPVM_INLINE_API_H

//  "& ~(intptr_t)1" means dropping weaken flag
#define SPVM_INLINE_API_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, object) ((void*)((intptr_t)object & ~(intptr_t)1))
#define SPVM_INLINE_API_GET_REF_COUNT(env, stack, object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset)))
#define SPVM_INLINE_API_INC_REF_COUNT_ONLY(env, stack, object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))++)
#define SPVM_INLINE_API_INC_REF_COUNT(env, stack, object)\
do {\
  if (object != NULL) {\
    SPVM_INLINE_API_INC_REF_COUNT_ONLY(env, stack, object);\
  }\
} while (0)\

#define SPVM_INLINE_API_DEC_REF_COUNT_ONLY(env, stack, object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))--)
#define SPVM_INLINE_API_DEC_REF_COUNT(env, stack, object)\
do {\
  if (object != NULL) {\
    if (SPVM_INLINE_API_GET_REF_COUNT(env, stack, object) > 1) { SPVM_INLINE_API_DEC_REF_COUNT_ONLY(env, stack, object); }\
    else { env->dec_ref_count(env, stack, object); }\
  }\
} while (0)\

#define SPVM_INLINE_API_ISWEAK(dist_address) (((intptr_t)*(void**)dist_address) & 1)
#define SPVM_INLINE_API_OBJECT_ASSIGN(env, stack, dist_address, src_object) \
do {\
  void* tmp_object = SPVM_INLINE_API_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, src_object);\
  if (tmp_object != NULL) {\
    SPVM_INLINE_API_INC_REF_COUNT_ONLY(env, stack, tmp_object);\
  }\
  if (*(void**)(dist_address) != NULL) {\
    if (__builtin_expect(SPVM_INLINE_API_ISWEAK(dist_address), 0)) { env->unweaken(env, stack, (void**)dist_address); }\
    if (SPVM_INLINE_API_GET_REF_COUNT(env, stack, *(void**)(dist_address)) > 1) { SPVM_INLINE_API_DEC_REF_COUNT_ONLY(env, stack, *(void**)(dist_address)); }\
    else { env->dec_ref_count(env, stack, *(void**)(dist_address)); }\
  }\
  *(void**)(dist_address) = tmp_object;\
} while (0)\

enum {
  SPVM_INLINE_API_C_STRING_CALL_STACK_ALLOCATION_FAILED,
  SPVM_INLINE_API_C_STRING_VALUE_ASSIGN_NON_ASSIGNABLE_TYPE,
  SPVM_INLINE_API_C_STRING_ASSIGN_READ_ONLY_STRING_TO_MUTABLE_TYPE,
  SPVM_INLINE_API_C_STRING_DIVIDE_ZERO,
  SPVM_INLINE_API_C_STRING_CONCAT_LEFT_UNDEFINED,
  SPVM_INLINE_API_C_STRING_CONCAT_RIGHT_UNDEFINED,
  SPVM_INLINE_API_C_STRING_NEW_OBJECT_FAILED,
  SPVM_INLINE_API_C_STRING_NEW_ARRAY_FAILED,
  SPVM_INLINE_API_C_STRING_ARRRAY_LENGTH_SMALL,
  SPVM_INLINE_API_C_STRING_NEW_STRING_FAILED,
  SPVM_INLINE_API_C_STRING_STRING_LENGTH_SMALL,
  SPVM_INLINE_API_C_STRING_ARRAY_UNDEFINED,
  SPVM_INLINE_API_C_STRING_ARRAY_ACCESS_INDEX_OUT_OF_RANGE,
  SPVM_INLINE_API_C_STRING_ELEMENT_ASSIGN_NON_ASSIGNABLE_TYPE,
  SPVM_INLINE_API_C_STRING_FIELD_ACCESS_INVOCANT_UNDEFINED,
  SPVM_INLINE_API_C_STRING_UNBOXING_CONVERSION_FROM_UNDEF,
  SPVM_INLINE_API_C_STRING_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE,
  SPVM_INLINE_API_C_STRING_WEAKEN_BACK_REFERENCE_ALLOCATION_FAILED,
  SPVM_INLINE_API_C_STRING_COPY_OPERAND_INVALID,
  SPVM_INLINE_API_C_STRING_ERROR_CODE_TOO_SMALL,
  SPVM_INLINE_API_C_STRING_WARN_AT,
  SPVM_INLINE_API_C_STRING_WARN_UNDEF,
  SPVM_INLINE_API_C_STRING_CALL_INSTANCE_METHOD_NOT_FOUND,
};





static const char* SPVM_INLINE_API_STRING_LITERALS[] = {
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
};

static inline void SPVM_INLINE_API_LEAVE_SCOPE(SPVM_ENV* env, SPVM_VALUE* stack, void** object_vars, int32_t* mortal_stack, int32_t* mortal_stack_top_ptr, int32_t original_mortal_stack_top) {
  for (int32_t mortal_stack_index = original_mortal_stack_top; mortal_stack_index < *mortal_stack_top_ptr; mortal_stack_index++) {
    int32_t var_index = mortal_stack[mortal_stack_index];
    void** object_address = (void**)&object_vars[var_index];
    if (*object_address != NULL) {
      if (SPVM_INLINE_API_GET_REF_COUNT(env, stack, *object_address) > 1) { SPVM_INLINE_API_DEC_REF_COUNT_ONLY(env, stack, *object_address); }
      else { env->dec_ref_count(env, stack, *object_address); }
      *object_address = NULL;
    }
  }
  *mortal_stack_top_ptr = original_mortal_stack_top;
}

#endif

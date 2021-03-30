#ifndef SPVM_NATIVE_H
#define SPVM_NATIVE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct spvm_env;
typedef struct spvm_env SPVM_ENV;

typedef union spvm_value SPVM_VALUE;

union spvm_value {
  int8_t bval;
  int16_t sval;
  int32_t ival;
  int64_t lval;
  float fval;
  double dval;
  void* oval;
  int8_t* bref;
  int16_t* sref;
  int32_t* iref;
  int64_t* lref;
  float* fref;
  double* dref;
};

#define SPVM_NEW_POINTER(env, package_name, pointer, object_address, file, line) do {\
  int32_t id = env->get_basic_type_id(env, package_name);\
  if (id < 0) { return env->die(env, "Package \"%s\" not found", package_name, file, line); };\
  *object_address = env->new_pointer(env, id, pointer);\
} while (0)\

#define SPVM_SET_FIELD_BYTE(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "byte");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:byte", package_name, sub_name, file, line); };\
  env->set_field_byte(env, obj, id, value);\
} while (0)\

#define SPVM_SET_FIELD_SHORT(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "short");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:short", package_name, sub_name, file, line); };\
  env->set_field_short(env, obj, id, value);\
} while (0)\

#define SPVM_SET_FIELD_INT(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "int");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:int", package_name, sub_name, file, line); };\
  env->set_field_int(env, obj, id, value);\
} while (0)\

#define SPVM_SET_FIELD_LONG(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "long");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:long", package_name, sub_name, file, line); };\
  env->set_field_long(env, obj, id, value);\
} while (0)\

#define SPVM_SET_FIELD_FLOAT(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "float");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:float", package_name, sub_name, file, line); };\
  env->set_field_float(env, obj, id, value);\
} while (0)\

#define SPVM_SET_FIELD_DOUBLE(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "double");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:double", package_name, sub_name, file, line); };\
  env->set_field_double(env, obj, id, value);\
} while (0)\

#define SPVM_SET_FIELD_OBJECT(env, obj, package_name, sub_name, signature, value, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, signature);\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:%s", package_name, sub_name, signature, file, line); };\
  env->set_field_object(env, obj, id, value);\
} while (0)\

#define SPVM_GET_FIELD_BYTE(env, obj, package_name, sub_name, value_address, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "byte");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:byte", package_name, sub_name, file, line); };\
  *value_address = env->get_field_byte(env, obj, id);\
} while (0)\

#define SPVM_GET_FIELD_SHORT(env, obj, package_name, sub_name, value_address, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "short");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:short", package_name, sub_name, file, line); };\
  *value_address = env->get_field_short(env, obj, id);\
} while (0)\

#define SPVM_GET_FIELD_INT(env, obj, package_name, sub_name, value_address, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "int");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:int", package_name, sub_name, file, line); };\
  *value_address = env->get_field_int(env, obj, id);\
} while (0)\

#define SPVM_GET_FIELD_LONG(env, obj, package_name, sub_name, value_address, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "long");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:long", package_name, sub_name, file, line); };\
  *value_address = env->get_field_long(env, obj, id);\
} while (0)\

#define SPVM_GET_FIELD_FLOAT(env, obj, package_name, sub_name, value_address, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "float");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:float", package_name, sub_name, file, line); };\
  *value_address = env->get_field_float(env, obj, id);\
} while (0)\

#define SPVM_GET_FIELD_DOUBLE(env, obj, package_name, sub_name, value_address, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, "double");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:double", package_name, sub_name, file, line); };\
  *value_address = env->get_field_double(env, obj, id);\
} while (0)\

#define SPVM_GET_FIELD_OBJECT(env, obj, package_name, sub_name, signature, value_address, file, line) do {\
  int32_t id = env->get_field_id(env, package_name, sub_name, signature);\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:%s", package_name, sub_name, signature, file, line); };\
  *value_address = env->get_field_object(env, obj, id);\
} while (0)\

#define SPVM_SET_PACKAGE_VAR_BYTE(env, package_name, package_var_name, value, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "byte");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:byte", package_name, package_var_name, file, line); };\
  env->set_package_var_byte(env, id, value);\
} while (0)\

#define SPVM_SET_PACKAGE_VAR_SHORT(env, package_name, package_var_name, value, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "short");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:short", package_name, package_var_name, file, line); };\
  env->set_package_var_short(env, id, value);\
} while (0)\

#define SPVM_SET_PACKAGE_VAR_INT(env, package_name, package_var_name, value, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "int");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:int", package_name, package_var_name, file, line); };\
  env->set_package_var_int(env, id, value);\
} while (0)\

#define SPVM_SET_PACKAGE_VAR_LONG(env, package_name, package_var_name, value, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "long");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:long", package_name, package_var_name, file, line); };\
  env->set_package_var_long(env, id, value);\
} while (0)\

#define SPVM_SET_PACKAGE_VAR_FLOAT(env, package_name, package_var_name, value, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "float");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:float", package_name, package_var_name, file, line); };\
  env->set_package_var_float(env, id, value);\
} while (0)\

#define SPVM_SET_PACKAGE_VAR_DOUBLE(env, package_name, package_var_name, value, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "double");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:double", package_name, package_var_name, file, line); };\
  env->set_package_var_double(env, id, value);\
} while (0)\

#define SPVM_SET_PACKAGE_VAR_OBJECT(env, package_name, package_var_name, signature, value, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, signature);\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:%s", package_name, package_var_name, signature, file, line); };\
  env->set_package_var_object(env, id, value);\
} while (0)\

#define SPVM_GET_PACKAGE_VAR_BYTE(env, package_name, package_var_name, value_address, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "byte");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:byte", package_name, package_var_name, file, line); };\
  *value_address = env->get_package_var_byte(env, id);\
} while (0)\

#define SPVM_GET_PACKAGE_VAR_SHORT(env, package_name, package_var_name, value_address, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "short");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:short", package_name, package_var_name, file, line); };\
  *value_address = env->get_package_var_short(env, id);\
} while (0)\

#define SPVM_GET_PACKAGE_VAR_INT(env, package_name, package_var_name, value_address, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "int");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:int", package_name, package_var_name, file, line); };\
  *value_address = env->get_package_var_int(env, id);\
} while (0)\

#define SPVM_GET_PACKAGE_VAR_LONG(env, package_name, package_var_name, value_address, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "long");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:long", package_name, package_var_name, file, line); };\
  *value_address = env->get_package_var_long(env, id);\
} while (0)\

#define SPVM_GET_PACKAGE_VAR_FLOAT(env, package_name, package_var_name, value_address, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "float");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:float", package_name, package_var_name, file, line); };\
  *value_address = env->get_package_var_float(env, id);\
} while (0)\

#define SPVM_GET_PACKAGE_VAR_DOUBLE(env, package_name, package_var_name, value_address, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, "double");\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:double", package_name, package_var_name, file, line); };\
  *value_address = env->get_package_var_double(env, id);\
} while (0)\

#define SPVM_GET_PACKAGE_VAR_OBJECT(env, package_name, package_var_name, signature, value_address, file, line) do {\
  int32_t id = env->get_package_var_id(env, package_name, package_var_name, signature);\
  if (id < 0) { return env->die(env, "Field not found, package name:%s, sub name:%s, signature:%s", package_name, package_var_name, signature, file, line); };\
  *value_address = env->get_package_var_object(env, id);\
} while (0)\













































struct spvm_env {
  void* package_vars_heap;
  void* object_header_byte_size;
  void* object_weaken_backref_head_offset;
  void* object_ref_count_offset;
  void* object_basic_type_id_offset;
  void* object_type_dimension_offset;
  void* object_type_runtime_type_offset;
  void* object_type_flag_offset;
  void* object_length_offset;
  void* byte_object_basic_type_id;
  void* short_object_basic_type_id;
  void* int_object_basic_type_id;
  void* long_object_basic_type_id;
  void* float_object_basic_type_id;
  void* double_object_basic_type_id;
  void* compiler;
  void* exception_object;
  void* native_mortal_stack;
  void* native_mortal_stack_top;
  void* native_mortal_stack_capacity;
  int32_t (*get_basic_type_id)(SPVM_ENV* env, const char* basic_type_name);
  int32_t (*get_field_id)(SPVM_ENV* env, const char* package_name, const char* field_name, const char* signature);
  int32_t (*get_field_offset)(SPVM_ENV* env, int32_t field_id);
  int32_t (*get_package_var_id)(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature);
  int32_t (*get_sub_id)(SPVM_ENV* env, const char* package_name, const char* sub_name, const char* signature);
  int32_t (*get_method_sub_id)(SPVM_ENV* env, void* object, const char* sub_name, const char* signature);
  void* (*new_object_raw)(SPVM_ENV* env, int32_t basic_type_id);
  void* (*new_object)(SPVM_ENV* env, int32_t basic_type_id);
  void* (*new_byte_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_byte_array)(SPVM_ENV* env, int32_t length);
  void* (*new_short_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_short_array)(SPVM_ENV* env, int32_t length);
  void* (*new_int_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_int_array)(SPVM_ENV* env, int32_t length);
  void* (*new_long_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_long_array)(SPVM_ENV* env, int32_t length);
  void* (*new_float_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_float_array)(SPVM_ENV* env, int32_t length);
  void* (*new_double_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_double_array)(SPVM_ENV* env, int32_t length);
  void* (*new_object_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_object_array)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_muldim_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length);
  void* (*new_muldim_array)(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length);
  void* (*new_mulnum_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_mulnum_array)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_string_nolen_raw)(SPVM_ENV* env, const char* bytes);
  void* (*new_string_nolen)(SPVM_ENV* env, const char* bytes);
  void* (*new_string_raw)(SPVM_ENV* env, const char* bytes, int32_t length);
  void* (*new_string)(SPVM_ENV* env, const char* bytes, int32_t length);
  void* (*new_pointer_raw)(SPVM_ENV* env, int32_t basic_type_id, void* pointer);
  void* (*new_pointer)(SPVM_ENV* env, int32_t basic_type_id, void* pointer);
  void* (*concat_raw)(SPVM_ENV* env, void* string1, void* string2);
  void* (*concat)(SPVM_ENV* env, void* string1, void* string2);
  void* (*new_stack_trace_raw)(SPVM_ENV* env, void* exception, const char* package_name, const char* sub_name, const char* file, int32_t line);
  void* (*new_stack_trace)(SPVM_ENV* env, void* exception, const char* package_name, const char* sub_name, const char* file, int32_t line);
  int32_t (*length)(SPVM_ENV* env, void* array);
  int8_t* (*get_elems_byte)(SPVM_ENV* env, void* array);
  int16_t* (*get_elems_short)(SPVM_ENV* env, void* array);
  int32_t* (*get_elems_int)(SPVM_ENV* env, void* array);
  int64_t* (*get_elems_long)(SPVM_ENV* env, void* array);
  float* (*get_elems_float)(SPVM_ENV* env, void* array);
  double* (*get_elems_double)(SPVM_ENV* env, void* array);
  void* (*get_elem_object)(SPVM_ENV* env, void* array, int32_t index);
  void (*set_elem_object)(SPVM_ENV* env, void* array, int32_t index, void* value);
  int8_t (*get_field_byte)(SPVM_ENV* env, void* object, int32_t field_id);
  int16_t (*get_field_short)(SPVM_ENV* env, void* object, int32_t field_id);
  int32_t (*get_field_int)(SPVM_ENV* env, void* object, int32_t field_id);
  int64_t (*get_field_long)(SPVM_ENV* env, void* object, int32_t field_id);
  float (*get_field_float)(SPVM_ENV* env, void* object, int32_t field_id);
  double (*get_field_double)(SPVM_ENV* env, void* object, int32_t field_id);
  void* (*get_field_object)(SPVM_ENV* env, void* object, int32_t field_id);
  void (*set_field_byte)(SPVM_ENV* env, void* object, int32_t field_id, int8_t value);
  void (*set_field_short)(SPVM_ENV* env, void* object, int32_t field_id, int16_t value);
  void (*set_field_int)(SPVM_ENV* env, void* object, int32_t field_id, int32_t value);
  void (*set_field_long)(SPVM_ENV* env, void* object, int32_t field_id, int64_t value);
  void (*set_field_float)(SPVM_ENV* env, void* object, int32_t field_id, float value);
  void (*set_field_double)(SPVM_ENV* env, void* object, int32_t field_id, double value);
  void (*set_field_object)(SPVM_ENV* env, void* object, int32_t field_id, void* value);
  int8_t (*get_package_var_byte)(SPVM_ENV* env, int32_t pkgvar_id);
  int16_t (*get_package_var_short)(SPVM_ENV* env, int32_t pkgvar_id);
  int32_t (*get_package_var_int)(SPVM_ENV* env, int32_t pkgvar_id);
  int64_t (*get_package_var_long)(SPVM_ENV* env, int32_t pkgvar_id);
  float (*get_package_var_float)(SPVM_ENV* env, int32_t pkgvar_id);
  double (*get_package_var_double)(SPVM_ENV* env, int32_t pkgvar_id);
  void* (*get_package_var_object)(SPVM_ENV* env, int32_t pkgvar_id);
  void (*set_package_var_byte)(SPVM_ENV* env, int32_t pkgvar_id, int8_t value);
  void (*set_package_var_short)(SPVM_ENV* env, int32_t pkgvar_id, int16_t value);
  void (*set_package_var_int)(SPVM_ENV* env, int32_t pkgvar_id, int32_t value);
  void (*set_package_var_long)(SPVM_ENV* env, int32_t pkgvar_id, int64_t value);
  void (*set_package_var_float)(SPVM_ENV* env, int32_t pkgvar_id, float value);
  void (*set_package_var_double)(SPVM_ENV* env, int32_t pkgvar_id, double value);
  void (*set_package_var_object)(SPVM_ENV* env, int32_t pkgvar_id, void* value);
  void* (*get_pointer)(SPVM_ENV* env, void* pointer_object);
  void (*set_pointer)(SPVM_ENV* env, void* pointer_object, void* pointer);
  int32_t (*call_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  void* (*get_exception)(SPVM_ENV* env);
  int32_t (*set_exception)(SPVM_ENV* env, void* exception);
  int32_t (*get_ref_count)(SPVM_ENV* env, void* object);
  void (*inc_ref_count)(SPVM_ENV* env, void* object);
  void (*dec_ref_count)(SPVM_ENV* env, void* object);
  int32_t (*enter_scope)(SPVM_ENV* env);
  int32_t (*push_mortal)(SPVM_ENV* env, void* object);
  void (*leave_scope)(SPVM_ENV* env, int32_t scope_id);
  int32_t (*remove_mortal)(SPVM_ENV* env, int32_t scope_id, void* remove_object);
  int32_t (*is_type)(SPVM_ENV* env, void* object, int32_t basic_type_id, int32_t type_dimension);
  int32_t (*has_callback)(SPVM_ENV* env, void* object, int32_t callback_basic_type_id);
  int32_t (*get_object_basic_type_id)(SPVM_ENV* env, void* object);
  int32_t (*get_object_type_dimension)(SPVM_ENV* env, void* object);
  int32_t (*weaken)(SPVM_ENV* env, void** object_address);
  int32_t (*isweak)(SPVM_ENV* env, void** object);
  void (*unweaken)(SPVM_ENV* env, void** object_address);
  void* (*alloc_memory_block_zero)(SPVM_ENV* env, int64_t byte_size);
  void (*free_memory_block)(SPVM_ENV* env, void* block);
  int32_t (*get_memory_blocks_count)(SPVM_ENV* env);
  void* (*get_type_name_raw)(SPVM_ENV* env, void* object);
  void* (*get_type_name)(SPVM_ENV* env, void* object);
  SPVM_ENV* (*new_env)(SPVM_ENV* env);
  void (*free_env)(SPVM_ENV* env);
  int32_t memory_blocks_count;
  const char* (*get_chars)(SPVM_ENV* env, void* string_object);
  int32_t (*die)(SPVM_ENV* env, const char* message, ...);
  void* (*new_object_by_name)(SPVM_ENV* env, const char* package_name, int32_t* exception_flag, const char* file, int32_t line);
};
#endif

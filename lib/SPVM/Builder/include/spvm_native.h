#ifndef SPVM_NATIVE_H
#define SPVM_NATIVE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct SPVM_env;
typedef struct SPVM_env SPVM_ENV;

typedef union SPVM_value SPVM_VALUE;

union SPVM_value {
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

typedef int8_t SPVM_VALUE_byte;
typedef int16_t SPVM_VALUE_short;
typedef int32_t SPVM_VALUE_int;
typedef int64_t SPVM_VALUE_long;
typedef float SPVM_VALUE_float;
typedef double SPVM_VALUE_double;
typedef void* SPVM_VALUE_object;

#define SPVM_SUCCESS 0
#define SPVM_EXCEPTION 1

#define SPVM_DIE(message, ...) do {\
  void* buffer = env->alloc_memory_block_zero(env, 255);\
  snprintf(buffer, 255, message " at %s line %d", __VA_ARGS__);\
  void* exception = env->new_str_len_raw(env, buffer, strlen(buffer));\
  env->free_memory_block(env, buffer);\
  env->set_exception(env, exception);\
  return SPVM_EXCEPTION;\
} while (0)\

#define SPVM_NEW_OBJ(env, obj, package_name, file, line) do {\
  int32_t id = env->basic_type_id(env, package_name);\
  if (id < 0) { SPVM_DIE("Package \"%s\" not found", package_name, file, line); };\
  obj = env->new_obj(env, id);\
} while (0)\

#define SPVM_NEW_POINTER(env, obj, package_name, ptr, file, line) do {\
  int32_t id = env->basic_type_id(env, package_name);\
  if (id < 0) { SPVM_DIE("Package \"%s\" not found", package_name, file, line); };\
  obj = env->new_pointer(env, id, ptr);\
} while (0)\

#define SPVM_SET_BFIELD(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "byte");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:byte", package_name, sub_name, file, line); };\
  env->set_bfield(env, obj, id, value);\
} while (0)\

#define SPVM_SET_SFIELD(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "short");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:short", package_name, sub_name, file, line); };\
  env->set_sfield(env, obj, id, value);\
} while (0)\

#define SPVM_SET_IFIELD(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "int");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:int", package_name, sub_name, file, line); };\
  env->set_ifield(env, obj, id, value);\
} while (0)\

#define SPVM_SET_LFIELD(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "long");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:long", package_name, sub_name, file, line); };\
  env->set_lfield(env, obj, id, value);\
} while (0)\

#define SPVM_SET_FFIELD(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "float");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:float", package_name, sub_name, file, line); };\
  env->set_ffield(env, obj, id, value);\
} while (0)\

#define SPVM_SET_DFIELD(env, obj, package_name, sub_name, value, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "double");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:double", package_name, sub_name, file, line); };\
  env->set_dfield(env, obj, id, value);\
} while (0)\

#define SPVM_SET_OFIELD(env, obj, package_name, sub_name, signature, value, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, signature);\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:%s", package_name, sub_name, signature, file, line); };\
  env->set_ofield(env, obj, id, value);\
} while (0)\

#define SPVM_BFIELD(env, left, obj, package_name, sub_name, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "byte");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:byte", package_name, sub_name, file, line); };\
  left = env->bfield(env, obj, id);\
} while (0)\

#define SPVM_SFIELD(env, left, obj, package_name, sub_name, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "short");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:short", package_name, sub_name, file, line); };\
  left = env->sfield(env, obj, id);\
} while (0)\

#define SPVM_IFIELD(env, left, obj, package_name, sub_name, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "int");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:int", package_name, sub_name, file, line); };\
  left = env->ifield(env, obj, id);\
} while (0)\

#define SPVM_LFIELD(env, left, obj, package_name, sub_name, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "long");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:long", package_name, sub_name, file, line); };\
  left = env->lfield(env, obj, id);\
} while (0)\

#define SPVM_FFIELD(env, left, obj, package_name, sub_name, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "float");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:float", package_name, sub_name, file, line); };\
  left = env->ffield(env, obj, id);\
} while (0)\

#define SPVM_DFIELD(env, left, obj, package_name, sub_name, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, "double");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:double", package_name, sub_name, file, line); };\
  left = env->dfield(env, obj, id);\
} while (0)\

#define SPVM_OFIELD(env, left, obj, package_name, sub_name, signature, file, line) do {\
  int32_t id = env->field_id(env, package_name, sub_name, signature);\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:%s", package_name, sub_name, signature, file, line); };\
  left = env->ofield(env, obj, id);\
} while (0)\

#define SPVM_SET_BPKGVAR(env, package_name, sub_name, value, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "byte");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:byte", package_name, sub_name, file, line); };\
  env->set_bpkgvar(env, id, value);\
} while (0)\

#define SPVM_SET_SPKGVAR(env, package_name, sub_name, value, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "short");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:short", package_name, sub_name, file, line); };\
  env->set_spkgvar(env, id, value);\
} while (0)\

#define SPVM_SET_IPKGVAR(env, package_name, sub_name, value, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "int");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:int", package_name, sub_name, file, line); };\
  env->set_ipkgvar(env, id, value);\
} while (0)\

#define SPVM_SET_LPKGVAR(env, package_name, sub_name, value, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "long");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:long", package_name, sub_name, file, line); };\
  env->set_lpkgvar(env, id, value);\
} while (0)\

#define SPVM_SET_FPKGVAR(env, package_name, sub_name, value, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "float");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:float", package_name, sub_name, file, line); };\
  env->set_fpkgvar(env, id, value);\
} while (0)\

#define SPVM_SET_DPKGVAR(env, package_name, sub_name, value, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "double");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:double", package_name, sub_name, file, line); };\
  env->set_dpkgvar(env, id, value);\
} while (0)\

#define SPVM_SET_OPKGVAR(env, package_name, sub_name, signature, value, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, signature);\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:%s", package_name, sub_name, signature, file, line); };\
  env->set_opkgvar(env, id, value);\
} while (0)\

#define SPVM_BPKGVAR(env, left, package_name, sub_name, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "byte");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:byte", package_name, sub_name, file, line); };\
  left = env->bpkgvar(env, id);\
} while (0)\

#define SPVM_SPKGVAR(env, left, package_name, sub_name, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "short");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:short", package_name, sub_name, file, line); };\
  left = env->spkgvar(env, id);\
} while (0)\

#define SPVM_IPKGVAR(env, left, package_name, sub_name, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "int");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:int", package_name, sub_name, file, line); };\
  left = env->ipkgvar(env, id);\
} while (0)\

#define SPVM_LPKGVAR(env, left, package_name, sub_name, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "long");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:long", package_name, sub_name, file, line); };\
  left = env->lpkgvar(env, id);\
} while (0)\

#define SPVM_FPKGVAR(env, left, package_name, sub_name, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "float");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:float", package_name, sub_name, file, line); };\
  left = env->fpkgvar(env, id);\
} while (0)\

#define SPVM_DPKGVAR(env, left, package_name, sub_name, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, "double");\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:double", package_name, sub_name, file, line); };\
  left = env->dpkgvar(env, id);\
} while (0)\

#define SPVM_OPKGVAR(env, left, package_name, sub_name, signature, file, line) do {\
  int32_t id = env->pkgvar_id(env, package_name, sub_name, signature);\
  if (id < 0) { SPVM_DIE("Field not found, package name:%s, sub name:%s, signature:%s", package_name, sub_name, signature, file, line); };\
  left = env->opkgvar(env, id);\
} while (0)\

#define SPVM_CALL_SUB(env, exception_flag, package_name, sub_name, signature, stack, file, line) do {\
  int32_t id = env->method_sub_id(env, obj, package_name, sub_name, signature);\
  if (id < 0) { SPVM_DIE("Method not found, package name:%s, sub name:%s, signature:%s", package_name, sub_name, signature, file, line); };\
  int32_t exception_flag = env->call_sub(env, id, stack);\
  if (exception_flag) {\
    const char* message = env->belems(env, env->exception(env));\
    if (id < 0) { SPVM_DIE("%s", message, file, line); };\
    return SPVM_EXCEPTION;\
  }\
} while (0)\

#define SPVM_CALL_METHOD(env, sub_name, signature, stack, file, line) do {\
  void* obj = stack[0].oval;\
  int32_t id = env->method_sub_id(env, obj, sub_name, signature);\
  if (id < 0) { SPVM_DIE("Method not found, object:%p, sub name:%s, signature:%s", obj, sub_name, signature, file, line); };\
  env->call_sub(env, id, stack);\
  int32_t exception_flag = env->call_sub(env, id, stack);\
  if (exception_flag) {\
    const char* message = env->belems(env, env->exception(env));\
    if (id < 0) { SPVM_DIE("%s", message, file, line); };\
    return SPVM_EXCEPTION;\
  }\
} while (0)\















































struct SPVM_env {
  void* runtime_package_vars_heap_offset;
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
  void* runtime;
  void* exception_object;
  void* native_mortal_stack;
  void* native_mortal_stack_top;
  void* native_mortal_stack_capacity;
  int32_t (*basic_type_id)(SPVM_ENV* env, const char* basic_type_name);
  int32_t (*field_id)(SPVM_ENV* env, const char* package_name, const char* field_name, const char* signature);
  int32_t (*field_offset)(SPVM_ENV* env, int32_t field_id);
  int32_t (*pkgvar_id)(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature);
  int32_t (*sub_id)(SPVM_ENV* env, const char* package_name, const char* sub_name, const char* signature);
  int32_t (*method_sub_id)(SPVM_ENV* env, void* object, const char* sub_name, const char* signature);
  void* (*new_obj_raw)(SPVM_ENV* env, int32_t basic_type_id);
  void* (*new_obj)(SPVM_ENV* env, int32_t basic_type_id);
  void* (*new_barray_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_barray)(SPVM_ENV* env, int32_t length);
  void* (*new_sarray_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_sarray)(SPVM_ENV* env, int32_t length);
  void* (*new_iarray_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_iarray)(SPVM_ENV* env, int32_t length);
  void* (*new_larray_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_larray)(SPVM_ENV* env, int32_t length);
  void* (*new_farray_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_farray)(SPVM_ENV* env, int32_t length);
  void* (*new_darray_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_darray)(SPVM_ENV* env, int32_t length);
  void* (*new_oarray_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_oarray)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_marray_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length);
  void* (*new_marray)(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length);
  void* (*new_varray_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_varray)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_str_raw)(SPVM_ENV* env, const char* bytes);
  void* (*new_str)(SPVM_ENV* env, const char* bytes);
  void* (*new_str_len_raw)(SPVM_ENV* env, const char* bytes, int32_t length);
  void* (*new_str_len)(SPVM_ENV* env, const char* bytes, int32_t length);
  void* (*new_pointer_raw)(SPVM_ENV* env, int32_t basic_type_id, void* pointer);
  void* (*new_pointer)(SPVM_ENV* env, int32_t basic_type_id, void* pointer);
  void* (*concat_raw)(SPVM_ENV* env, void* string1, void* string2);
  void* (*concat)(SPVM_ENV* env, void* string1, void* string2);
  void* (*new_stack_trace_raw)(SPVM_ENV* env, void* exception, const char* package_name, const char* sub_name, const char* file, int32_t line);
  void* (*new_stack_trace)(SPVM_ENV* env, void* exception, const char* package_name, const char* sub_name, const char* file, int32_t line);
  int32_t (*len)(SPVM_ENV*, void*);
  int8_t* (*belems)(SPVM_ENV*, void*);
  int16_t* (*selems)(SPVM_ENV*, void*);
  int32_t* (*ielems)(SPVM_ENV*, void*);
  int64_t* (*lelems)(SPVM_ENV*, void*);
  float* (*felems)(SPVM_ENV*, void*);
  double* (*delems)(SPVM_ENV*, void*);
  void* (*oelem)(SPVM_ENV*, void*, int32_t index);
  void (*set_oelem)(SPVM_ENV*, void*, int32_t index, void* value);
  int8_t (*bfield)(SPVM_ENV*, void*, int32_t);
  int16_t (*sfield)(SPVM_ENV*, void*, int32_t);
  int32_t (*ifield)(SPVM_ENV*, void*, int32_t);
  int64_t (*lfield)(SPVM_ENV*, void*, int32_t);
  float (*ffield)(SPVM_ENV*, void*, int32_t);
  double (*dfield)(SPVM_ENV*, void*, int32_t);
  void* (*ofield)(SPVM_ENV*, void*, int32_t);
  void (*set_bfield)(SPVM_ENV*, void*, int32_t, int8_t);
  void (*set_sfield)(SPVM_ENV*, void*, int32_t, int16_t);
  void (*set_ifield)(SPVM_ENV*, void*, int32_t, int32_t);
  void (*set_lfield)(SPVM_ENV*, void*, int32_t, int64_t);
  void (*set_ffield)(SPVM_ENV*, void*, int32_t, float);
  void (*set_dfield)(SPVM_ENV*, void*, int32_t, double);
  void (*set_ofield)(SPVM_ENV*, void*, int32_t, void*);
  int8_t (*bpkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  int16_t (*spkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  int32_t (*ipkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  int64_t (*lpkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  float (*fpkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  double (*dpkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  void* (*opkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  void (*set_bpkgvar)(SPVM_ENV* env, int32_t pkgvar_id, int8_t value);
  void (*set_spkgvar)(SPVM_ENV* env, int32_t pkgvar_id, int16_t value);
  void (*set_ipkgvar)(SPVM_ENV* env, int32_t pkgvar_id, int32_t value);
  void (*set_lpkgvar)(SPVM_ENV* env, int32_t pkgvar_id, int64_t value);
  void (*set_fpkgvar)(SPVM_ENV* env, int32_t pkgvar_id, float value);
  void (*set_dpkgvar)(SPVM_ENV* env, int32_t pkgvar_id, double value);
  void (*set_opkgvar)(SPVM_ENV* env, int32_t pkgvar_id, void* value);
  void* (*pointer)(SPVM_ENV*, void*);
  void (*set_pointer)(SPVM_ENV*, void*, void*);
  int32_t (*call_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  void* (*exception)(SPVM_ENV* env);
  void (*set_exception)(SPVM_ENV* env, void* exception);
  int32_t (*ref_count)(SPVM_ENV* env, void* object);
  void (*inc_ref_count)(SPVM_ENV* env, void* object);
  void (*dec_ref_count)(SPVM_ENV* env, void* object);
  int32_t (*enter_scope)(SPVM_ENV* env);
  void (*push_mortal)(SPVM_ENV* env, void* object);
  void (*leave_scope)(SPVM_ENV* env, int32_t original_mortal_stack_top);
  int32_t (*remove_mortal)(SPVM_ENV* env, int32_t original_mortal_stack_top, void* remove_object);
  int32_t (*is_type)(SPVM_ENV*, void* object, int32_t basic_type_id, int32_t type_dimension);
  int32_t (*has_callback)(SPVM_ENV*, void* object, int32_t callback_basic_type_id);
  int32_t (*object_basic_type_id)(SPVM_ENV* env, void* object);
  int32_t (*object_type_dimension)(SPVM_ENV* env, void* object);
  void (*weaken)(SPVM_ENV* env, void** object_address);
  int32_t (*isweak)(SPVM_ENV* env, void** object);
  void (*unweaken)(SPVM_ENV* env, void** object_address);
  void* (*alloc_memory_block_zero)(SPVM_ENV* env, int64_t byte_size);
  void (*free_memory_block)(SPVM_ENV* env, void* block);
  int32_t (*memory_blocks_count)(SPVM_ENV* env);
  void* (*type_name_raw)(SPVM_ENV* env, void* object);
  void* (*type_name)(SPVM_ENV* env, void* object);
  void* (*new_env)(SPVM_ENV*);
  void (*free_env)(SPVM_ENV*);
  void* call_sub_depth;
};
#endif
